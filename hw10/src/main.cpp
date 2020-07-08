/*! @file interpreter.hpp
 *  @brief Homework 7 main file
 */
#include "interpretermt.hpp"

#include <stdexcept>
#include <string>
#include <iostream>
#include <thread>


int main(int argc, char* argv[]){
    if(argc == 2){
        std::string arg = argv[1];
        int bulklength;
        try{
            std::size_t pos;
            bulklength = std::stoi(arg, &pos);
            if (pos < arg.size()) {
                std::cerr << "Trailing characters after number: " << arg << '\n';
            }
        } catch (std::invalid_argument const &ex) {
        std::cerr << "Invalid number: " << arg << '\n';
        } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << arg << '\n';
        };

        tbb::concurrent_queue<std::string> q1;
        //std::atomic<bool> eof{false};

        Interpreter subj(bulklength);
        ostreamObserver coutobserver(&subj, std::cout);


        std::string str;
        while(std::cin >> str)
        {
            subj.addString(str);
        }
    } else {
        std::cout << "set bulk length as argument" << std::endl;
    }
    return 0;
}
