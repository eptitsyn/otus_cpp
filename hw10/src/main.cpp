/*! @file interpreter.hpp
 *  @brief Homework 7 main file
 */
#include "interpretermt.hpp"

#include <stdexcept>
#include <string>
#include <iostream>

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

        
        Interpreter subj(bulklength);
        ostreamObserver coutobserver(&subj, std::cout);
        fileObserver fileobserver(&subj, 2);

        size_t string_counter = 0;
        std::string str;
        while(std::cin >> str)
        {
            subj.addString(str);
            ++string_counter;
        }
        logger.Logmain_addstrings(string_counter);
    } else {
        std::cout << "set bulk length as argument" << std::endl;
    }
    return 0;
}
