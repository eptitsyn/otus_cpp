//
// #include <boost/program_options/cmdline.hpp>
// namespace po = boost::program_options;

#include "interpreter.hpp"

int main(int argc, char* argv[]){
    Subject subj(3);
    ostreamObserver coutObserver(&subj);
    fileObserver fileObs(&subj);

    std::string str;
    while(std::cin >> str)
    {
        subj.addString(str);
    }
    return 0;
}