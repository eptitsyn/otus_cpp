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
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>

namespace fs = boost::filesystem;

class DuplicateSearcher
{
    std::vector<fs::path> scan_dirs;
    std::vector<fs::path> exclude_dirs;
    std::vector<std::string> filemasks;
    size_t block_size;
    size_t scan_depth;
    uintmax_t min_file_size;

    std::vector<File> files;
    std::unordered_set<std::string> files_canonical;

    IHasher *hasher;

    std::vector<fs::path> VectorStrToPath(const std::vector<std::string> &other)
    {
        std::vector<fs::path> result;
        result.reserve(other.size());
        for (const auto &i : other)
        {
            result.emplace_back(fs::path(i));
        }
        return result;
    }

    void SetHasher(std::string hstr)
    {
        if (hstr == "md5")
        {
            hasher = new MD5Hasher();
        }
        else if (hstr == "sha1")
        {
            hasher = new SHA1Hasher();
        }
        else
        {
            hasher = new CRC32Hasher();
        }
    }

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
            if (files_canonical.find(fs::weakly_canonical(p).string()) == files_canonical.end())
            {
                files_canonical.insert(fs::weakly_canonical(p).string());
                files.emplace_back(File(p.string(), fs::file_size(p), block_size, hasher));
            };
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
            {
                if (fs::file_size(p) >= min_file_size)
                    AddFileFiltered(p);
            }
            else if (fs::is_directory(p) && depth > 0)
            {
                //todo: add symlinks;
                //todo: check exclude
                for (const fs::directory_entry &x : fs::directory_iterator(p))
                {
                    ScanPath(x.path(), depth - 1);
                }
            }
        }
    };

public:
    DuplicateSearcher(std::vector<std::string> scan_dirs, std::vector<std::string> exclude_dirs, std::vector<std::string> filemasks,
                      size_t block_size, size_t scan_depth, uintmax_t min_file_size, std::string hasher)
        : scan_dirs(VectorStrToPath(scan_dirs)), exclude_dirs(VectorStrToPath(exclude_dirs)), filemasks(filemasks), block_size(block_size),
          scan_depth(scan_depth), min_file_size(min_file_size)
    {
        SetHasher(hasher);
    };
    std::unordered_map<std::string, std::vector<std::string>> FindDuplicates()
    {
        std::unordered_map<std::string, std::vector<std::string>> result;

        if (files.size() < 2)
            return result;
        for (auto first = std::begin(files); first != end(files); ++first)
        {
            if (!first->in_result)
                for (auto second = std::next(first); second != end(files); ++second)
                {
                    if (!second->in_result && first->EqualByHashTo(*second))
                    {
                        result[first->GetPath().string()].push_back(second->GetPath().string());
                        second->in_result = true;
                    }
                }
        }
        return result;
    }

    void SetScanDirs(std::vector<std::string> dirs)
    {
        scan_dirs = VectorStrToPath(dirs);
    }

    void SetExcludeDirs(std::vector<std::string> dirs)
    {
        exclude_dirs = VectorStrToPath(dirs);
    }
    //std::vector<std::vector<std::string>> GetDuplicates()
    void RunSearch()
    {
        for (const auto &i : scan_dirs)
        {
            ScanPath(i, scan_depth);
        }

        // for (const auto &i : files)
        // {
        //     std::cout << i.GetPath() << '\n';
        // }
        //scan every dir
        //
    }
};