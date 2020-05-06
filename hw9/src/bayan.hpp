/*! 
 *  @brief DuplicateSearcher class
*/
#pragma once

#include "file.hpp"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace fs = boost::filesystem;

class DuplicateSearcher
{
    std::vector<fs::path> scan_dirs;
    std::vector<fs::path> exclude_dirs;
    std::vector<std::string> filemasks;
    size_t fileread_block_size = 5;
    size_t scan_depth = 3;

    std::unordered_set<File> files;

    struct DuplicateRecord
    {
        fs::path file;
        std::vector<fs::path> duplicates;
    };

    std::vector<DuplicateRecord> duplicates;

    bool FilenameSatisfiesFilemask(const std::string &filename, const std::vector<std::string> &filemasks)
    {
        //todo
        return true;
    }

    void AddFile(fs::path p)
    {
        if (fs::exists(p) && fs::is_regular_file(p))
        {
            files.emplace(File(fs::weakly_canonical(p), fs::file_size(p), fileread_block_size));
        }
    }

    void AddFileFiltered(fs::path p)
    {
        if (FilenameSatisfiesFilemask(p.filename().string(), filemasks))
        {
            AddFile(p);
        }
    }

    void ScanPath(fs::path p, size_t depth)
    {
        if (fs::exists(p))
        {
            if (fs::is_regular_file(p))
                AddFileFiltered(p);
            //todo: add symlinks;
            else if (fs::is_directory(p) && depth > 0)
            {
                //todo: check exclude
                for (const fs::directory_entry &x : fs::directory_iterator(p))
                {
                    ScanPath(x.path(), depth - 1);
                }
            }
        }
    };

public:
    std::vector<DuplicateRecord> FindDuplicates(const std::unordered_set<File> &files)
    {
        std::vector<DuplicateRecord> result;
        if (files.size() < 2)
            return result;
        for (auto first = std::begin(files); first != end(files); ++first)
        {
            for (auto second = std::next(first); second != end(files); ++second)
            {
                //if(*first == *second)
            }
        }
    }


    void SetScanDirs(std::vector<std::string> dirs)
    {
        scan_dirs = VectorStrToPath(dirs);
    }

    void SetExcludeDirs(std::vector<std::string> dirs)
    {
        exclude_dirs = VectorStrToPath(dirs);
    }
    void Run()
    {
        for (const auto &i : scan_dirs)
        {
            ScanPath(i, scan_depth);
        }

        for (const auto &i : files)
        {
            std::cout << i.GetPath() << '\n';
        }
        //scan every dir
        //
    }
};