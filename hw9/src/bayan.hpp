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
    /*! 
 *  @brief dirs for scanning
*/
    std::vector<fs::path> scan_dirs;
    /*! 
 *  @brief dirs for exclusion
*/
    std::vector<fs::path> exclude_dirs;
/*! 
 *  @brief filemasks to scan
*/
    std::vector<boost::regex> filemasks;
/*! 
 *  @brief hash block size when comparing
*/
    size_t block_size;
/*! 
 *  @brief max directory scan depth.
*/
    size_t scan_depth;
/*! 
 *  @brief minimum file size to include in scan
*/
    uintmax_t min_file_size;
/*! 
 *  @brief storage of info about scanned files
*/
    std::vector<File> files;
/*! 
 *  @brief storage of canonical paths to eclude duplicates
*/
    std::unordered_set<std::string> files_canonical;
/*! 
 *  @brief hasher class
*/
    IHasher *hasher;
/*! 
 *  @brief settter for hasher
*/
    void SetHasher(std::string hstr);
/*! 
 *  @brief is path contaned in excluded
*/
    bool InExcluded(fs::path p);
/*! 
 *  @brief does filename satisfies filemask
*/
    bool FilenameSatisfiesFilemask(const std::string &filename);
/*! 
 *  @brief add file to scan
*/
    void AddFile(fs::path p);
/*! 
 *  @brief check exclusion & filemask and then add file to scan
*/
    void AddFileFiltered(fs::path p);
/*! 
 *  @brief function for recursive scan
*/
    void ScanPath(fs::path p, size_t depth);
/*! 
 *  @brief run search
*/
    void RunSearch();

public:
    DuplicateSearcher(std::vector<std::string> scan_dirs, std::vector<std::string> exclude_dirs, std::vector<std::string> filemasks_,
                      size_t block_size, size_t scan_depth, uintmax_t min_file_size, std::string hasher);
/*! 
 *  @brief do search on files
*/
    std::unordered_map<std::string, std::vector<std::string>> FindDuplicates();
/*! 
 *  @brief setter for directories for scanning
*/
    void SetScanDirs(std::vector<std::string> dirs);
/*! 
 *  @brief setter for exclusion directories
*/
    void SetExcludeDirs(std::vector<std::string> dirs);
};
