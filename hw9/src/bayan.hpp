/*! 
 *  @brief DuplicateSearcher class
*/
#pragma once

#include "file.hpp"
#include "hash.hpp"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/unordered_set.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fs = boost::filesystem;

class DuplicateSearcher
{
    std::vector<fs::path> scan_dirs;
    std::vector<fs::path> exclude_dirs;
    std::vector<boost::regex> filemasks;
    size_t block_size;
    size_t scan_depth;
    uintmax_t min_file_size;
    std::vector<File> files;
    std::unordered_set<std::string> files_canonical;
    IHasher *hasher;
    void SetHasher(std::string hstr);
    bool InExcluded(fs::path p);
    bool FilenameSatisfiesFilemask(const std::string &filename);
    void AddFile(fs::path p);
    void AddFileFiltered(fs::path p);
    void ScanPath(fs::path p, size_t depth);

public:
    DuplicateSearcher(std::vector<std::string> scan_dirs, std::vector<std::string> exclude_dirs, std::vector<std::string> filemasks_,
                      size_t block_size, size_t scan_depth, uintmax_t min_file_size, std::string hasher);
    std::unordered_map<std::string, std::vector<std::string>> FindDuplicates();
    void SetScanDirs(std::vector<std::string> dirs);
    void SetExcludeDirs(std::vector<std::string> dirs);
    void RunSearch();
};
