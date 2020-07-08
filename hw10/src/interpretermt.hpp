/*! @file interpreter.hpp
 *  @brief Класс интерпретатор
 */
#pragma once

#include "date.h" // date.h by Howard Hinnant
#include "tbb/concurrent_queue.h"

#include <atomic>
#include <condition_variable>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>


/*!
* @brief Непосредственно класс интерпретатор
*/
class Interpreter {
    struct Bulk {
        std::chrono::time_point<std::chrono::system_clock> starttime = std::chrono::system_clock::now();
        std::vector<std::string> commands;
        size_t bracket_level = 0;
        bool is_packet = false;
    };
    std::vector<class Observer*> views;
    std::shared_ptr<Bulk> current_bulk = std::make_unique<Bulk>();
    size_t BulkSize;
public:
    struct BulkOut{
        std::string commands;
        std::string time_str;
    };
private:
    std::shared_ptr<BulkOut> currentBulkOut; 

public:
    Interpreter(size_t size = 3) : BulkSize(size){};
    virtual ~Interpreter(){ 
        if(!current_bulk->is_packet)
            flush();
    }
    std::shared_ptr<BulkOut> getCurrentBulkOut(){ return currentBulkOut; }
/*!
* @brief добавить наблюдателей.
*/
    void attach(Observer *obs) {
        views.push_back(obs);
    }
/*!
* @brief Сделать вывод текущего балка
*/
    void flush(){
        currentBulkOut = std::make_shared<BulkOut>( BulkOut{getBulkAsString(), getBulkTime()} );
        if(current_bulk->commands.size() != 0) {
            notify();
        }
    }
/*!
* @brief Очистить текущий балк
*/
    void finishBulk(){
        flush();
        current_bulk.reset();
        current_bulk = std::make_unique<Bulk>();
    }

/*!
* @brief добавить комманду в балк
*/
    void addString(std::string str) {

        if(str == "{"){
            if(current_bulk->is_packet){
                ++(current_bulk->bracket_level);
            } else {
                finishBulk();
                current_bulk->is_packet = true;
            }
            return;
        }

        if(str == "}"){
            if(current_bulk->is_packet){
                if(current_bulk->bracket_level == 0) {
                    finishBulk();
                }  else 
                    --(current_bulk->bracket_level);
            }
            return;
        }

        //set first command time
        if(current_bulk->commands.size() == 0) {
            current_bulk->starttime = std::chrono::system_clock::now();
        }
        current_bulk->commands.emplace_back(str);

        if (!current_bulk->is_packet && current_bulk->commands.size() == BulkSize){
            finishBulk();
        }
    }
/*!
* @brief вернуть все команды из текущего балка строкой
*/
    std::string getBulkAsString() {     
        std::stringstream ss;
        ss << "bulk:";
        std::string comma = "";
        for(const auto &i : current_bulk->commands){

            ss << comma << ' ' << i;
            comma = ",";
        }
        return ss.str();
    }
/*!
* @brief вернуть время текущего балка строкой
*/
    std::string getBulkTime(){
        std::stringstream ss;

        namespace C = std::chrono;
        using namespace std::chrono_literals;

        auto tp = current_bulk->starttime + 3h;
        auto dp = date::floor<date::days>(tp);
        //auto ymd = date::year_month_day{dp};
        auto time = date::make_time(C::duration_cast<C::milliseconds>(tp-dp));
        
        ss << time.hours().count() << time.minutes().count() << time.seconds().count() << time.subseconds().count();
        return ss.str();
    }

    void notify();
};

/*!
* @brief Наблюдатели для вывода
*/
class Observer {
    Interpreter *model;
  public:
    Observer(Interpreter *model) : model(model) {
        model->attach(this);
    }
    virtual void update() = 0;
  protected:
    Interpreter *getSubject() {
        return model;
    }
};

void Interpreter::notify() {
  for (size_t i = 0; i < views.size(); ++i)
    views[i]->update();
}

/*!
* @brief Вывод в ostream
*/
class ostreamObserver: public Observer{
    std::ostream& stream;
    std::thread thread_;
    tbb::concurrent_queue<std::shared_ptr<Interpreter::BulkOut> > queue_;
    std::atomic<bool> stopflag_{false};
    std::condition_variable cv_;
    std::mutex mutex_;
public:
    ostreamObserver(Interpreter *model, std::ostream& stream) : Observer(model), stream(stream) {
        thread_ = std::thread(&ostreamObserver::Run, this);
    };
    virtual ~ostreamObserver(){
        stopflag_ = true;
        cv_.notify_all();
        thread_.join();
    }
    void update() override{
        queue_.push(getSubject()->getCurrentBulkOut());
        cv_.notify_one();
    }
private:
    void Run(){
        while(!stopflag_ || !queue_.empty()){
            std::unique_lock<decltype(mutex_)> l(mutex_);
            cv_.wait(l);
            while(!queue_.empty()){
                std::shared_ptr<Interpreter::BulkOut> obj;
                if(queue_.try_pop(obj)){
                    stream << obj.get()->commands;
                    stream << std::endl;
                }
            }
        }
    }

};

/*!
* @brief Вывод в fstream
*/
class fileObserver: public Observer{
    std::vector<std::thread> threads_;
    tbb::concurrent_queue<std::shared_ptr<Interpreter::BulkOut> > queue_;
    std::atomic<bool> stopflag_{false};
    std::condition_variable cv_;
    std::mutex mutex_;
public:
    fileObserver(Interpreter *model, size_t thread_count = 1) : Observer(model) {
        for(size_t i = 0; i < thread_count; ++i){
            threads_.emplace_back(std::thread(&fileObserver::Run, this));
        }
    };
    virtual ~fileObserver(){
        stopflag_ = true;
        cv_.notify_all();
        for(auto &i: threads_){
            i.join();
        }
    }
    void update() {
        queue_.push(getSubject()->getCurrentBulkOut());
        cv_.notify_one();
    }
private:
    void Run(){
        while(!stopflag_ || !queue_.empty()){
            std::unique_lock<decltype(mutex_)> l(mutex_);
            cv_.wait(l);
            while(!queue_.empty()){
                std::shared_ptr<Interpreter::BulkOut> obj;
                if(queue_.try_pop(obj)){
                    std::stringstream ss;
                    ss << "bulk" << obj.get()->time_str << "_" << std::hex << std::setw(4)
                    << std::hash<std::string>{}(obj.get()->commands) << ".log";
                    std::ofstream out(ss.str());
                    out << obj.get()->commands;
                    out.close();
                }
            }
        }
    }
};
