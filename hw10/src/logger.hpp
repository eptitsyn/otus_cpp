#pragma once

#include "tbb/concurrent_vector.h"
#include <sstream>
#include <string>

using namespace std;

class Logger
{
public:
    explicit Logger(ostream &output_stream) : os(output_stream) {};
    virtual ~Logger(){ 
        os << " main поток - " << main_str << " строк, " << main_cmd << " команд, " << main_blk <<" блок(ов)" << '\n';
        for(const auto &i: logqueue){
            os << i << '\n';
        }
    }
    void Log(const string &message);
    void Logmain_addstrings(size_t cnt){ main_str += cnt; };
    void Logmain_addcmds(size_t cnt){ main_cmd += cnt; }
    void Logmain_addblocks(size_t cnt){ main_blk += cnt; }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    ostream &os;
    tbb::concurrent_vector<std::string> logqueue;
    size_t main_str{0}, main_blk{0}, main_cmd{0};
};

void Logger::Log(const string &message)
{
    logqueue.emplace_back(message);
}
