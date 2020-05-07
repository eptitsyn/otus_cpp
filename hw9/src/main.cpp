/*! 
 *  @brief Homework 9
*/
#include "bayan.hpp"

#include <boost/program_options.hpp>
#include <iostream>
#include <exception>

namespace std
{
std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &vec)
{
    for (const auto &item : vec)
    {
        os << item << " ";
    }
    return os;
}
} // namespace std

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    try
    {
        po::options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Help screen")
            ("include,i", po::value<std::vector<std::string>>()->multitoken(), "Directories to scan")
            ("exclude,e", po::value<std::vector<std::string>>()->multitoken()->default_value(std::vector<std::string>{}), "Directories to exclude")
            ("depth", po::value<size_t>()->default_value(3), "Depth")
            ("minsize", po::value<uintmax_t>()->default_value(1), "Minimum file size")
            ("filemasks", po::value<std::vector<std::string>>()->multitoken()->default_value(std::vector<std::string>{}), "Mask for files to scans")
            ("blocksize", po::value<size_t>()->default_value(512), "Block size in bytes")
            ("hash", po::value<std::string>()->default_value("crc32"), "Hash algo crc32/md5/sha1");

        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
            std::cout << desc << '\n';
        else if (vm.count("include"))
        {
            DuplicateSearcher dup(vm["include"].as<std::vector<std::string> >(),
                                vm["exclude"].as<std::vector<std::string> >(),
                                vm["filemasks"].as<std::vector<std::string> >(),
                                vm["blocksize"].as<size_t>(),
                                vm["depth"].as<size_t>(),
                                vm["minsize"].as<uintmax_t>(),
                                vm["hash"].as<std::string>()
            );
            dup.RunSearch();
            auto dups = dup.FindDuplicates();
            for(const auto &i : dups){
                std::cout << i.first << '\n';
                for(const auto& j : i.second){
                    std::cout << j << '\n';
                }
                std::cout << std::endl;
            }

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
