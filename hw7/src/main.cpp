/*! @file interpreter.hpp
 *  @brief Homework 7 main file
 */
#include "interpreter.hpp"

#include <stdexcept>
#include <string>

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
        }

        Interpreter subj(bulklength);
        ostreamObserver coutObserver(&subj, std::cout);
        fileObserver fileObs(&subj);

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
