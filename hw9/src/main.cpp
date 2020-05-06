/*! 
 *  @brief Homework 9
*/

#include "bayan.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <exception>

namespace po = boost::program_options;

int main(int argc, char* argv[]){    
    try
    {
        po::options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Help screen")
            ("include,i", po::value<std::vector<std::string> >()->multitoken(), "Directories to scan")
            ("exclude,e", po::value<std::vector<std::string> >()->multitoken(), "Directories to exclude")
            ("depth", po::value<size_t>()->default_value(0), "Depth")
            ("minsize", po::value<size_t>()->default_value(1), "Minimum file size")
            ("filemasks", po::value<std::vector<std::string> >()->multitoken(), "Mask for files to scans")
            ("blocksize", po::value<size_t>()->default_value(512), "Block size in bytes")
            ("hash", po::value<std::string>()->default_value("crc32"), "Hash algo crc32/md5/sha1")
            ;


        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
            std::cout << desc << '\n';
        else if (vm.count("include")){
            
        }
        //     std::cout << "Age: " << vm["age"].as<int>() << '\n';
        // else if (vm.count("pi"))
        //     std::cout << "Pi: " << vm["pi"].as<float>() << '\n';
        // for(const auto& i: vm["include"].as<std::vector<std::string> >()){
        //     std::cout << i << '\n';
        // }
    }
    catch (const po::error &ex)
    {
    std::cerr << ex.what() << '\n';
    }
}
