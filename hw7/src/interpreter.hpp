/*! @file interpreter.hpp
 *  @brief Класс интерпретатор
 */
#pragma once

#include "date.h" // date.h by Howard Hinnant

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


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
    std::unique_ptr<Bulk> current_bulk = std::make_unique<Bulk>();
    size_t BulkSize;
public:
    Interpreter(size_t size = 3) : BulkSize(size){};
    ~Interpreter(){ 
        if(!current_bulk->is_packet)
            flush();
    }
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
        if(current_bulk->commands.size() != 0) {
            notify();
        }
    }
/*!
* @brief Очистить текущий балк
*/
    void resetBulk(){
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
                resetBulk();
                current_bulk->is_packet = true;
            }
            return;
        }

        if(str == "}"){
            if(current_bulk->is_packet){
                if(current_bulk->bracket_level == 0) {
                    resetBulk();
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
            resetBulk();
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
public:
    ostreamObserver(Interpreter *model, std::ostream& stream) : Observer(model), stream(stream) {};
    void update() {
        stream << getSubject()->getBulkAsString();
        //stream << '\n' << getSubject()->getBulkTime();
        stream << std::endl;
    }

};

/*!
* @brief Вывод в fstream
*/
class fileObserver: public Observer{
public:
    fileObserver(Interpreter *model) : Observer(model) {};
    void update() {
        std::ofstream out("bulk" + getSubject()->getBulkTime() + ".log");
        out << getSubject()->getBulkAsString();
        out.close();
    }
};