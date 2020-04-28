#pragma once

#include "date.h" // date.h by Howard Hinnant

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Subject {
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
    Subject(size_t size = 3) : BulkSize(size){};
    ~Subject(){ 
        if(!current_bulk->is_packet)
            flush();
    }
    void attach(Observer *obs) {
        views.push_back(obs);
    }
    void flush(){
        if(current_bulk->commands.size() != 0) {
            notify();
        }
    }
    void resetBulk(){
        flush();
        current_bulk.reset();
        current_bulk = std::make_unique<Bulk>();
    }

    void addString(std::string &str) {

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

class Observer {
    Subject *model;
  public:
    Observer(Subject *model) : model(model) {
        model->attach(this);
    }
    virtual void update() = 0;
  protected:
    Subject *getSubject() {
        return model;
    }
};

void Subject::notify() {
  for (size_t i = 0; i < views.size(); ++i)
    views[i]->update();
}

class ostreamObserver: public Observer{
    std::ostream& stream = std::cout;
public:
    ostreamObserver(Subject *model) : Observer(model) {};
    void update() {
        stream << getSubject()->getBulkAsString();
        //stream << '\n' << getSubject()->getBulkTime();
        stream << std::endl;
    }

};

class fileObserver: public Observer{
public:
    fileObserver(Subject *model) : Observer(model) {};
    void update() {
        std::ofstream out("bulk" + getSubject()->getBulkTime() + ".log");
        out << getSubject()->getBulkAsString();
        out.close();
    }
};