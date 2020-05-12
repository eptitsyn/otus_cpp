#include "bayan.hpp"

namespace fs = boost::filesystem;

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

void DuplicateSearcher::SetHasher(std::string hstr)
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

bool DuplicateSearcher::InExcluded(fs::path p)
{
    for (const auto &i : exclude_dirs)
    {
        if (fs::equivalent(p, i))
            return true;
    }
    return false;
}

bool DuplicateSearcher::FilenameSatisfiesFilemask(const std::string &filename)
{
    if (filemasks.size() == 0)
        return true;
    for (const auto &i : filemasks)
    {
        if (boost::regex_match(filename, i))
            return true;
    }
    return false;
}

void DuplicateSearcher::AddFile(fs::path p)
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

void DuplicateSearcher::AddFileFiltered(fs::path p)
{
    if (FilenameSatisfiesFilemask(p.filename().string()))
    {
        AddFile(p);
    }
}

void DuplicateSearcher::ScanPath(fs::path p, size_t depth)
{
    if (fs::exists(p) && !InExcluded(p))
    {
        if (fs::is_regular_file(p))
        {
            if (fs::file_size(p) >= min_file_size)
                AddFileFiltered(p);
        }
        else if (fs::is_directory(p) && depth > 0)
        {
            for (const fs::directory_entry &x : fs::directory_iterator(p))
            {
                ScanPath(x.path(), depth - 1);
            }
        }
    }
};

DuplicateSearcher::DuplicateSearcher(std::vector<std::string> scan_dirs, std::vector<std::string> exclude_dirs, std::vector<std::string> filemasks_,
                                     size_t block_size, size_t scan_depth, uintmax_t min_file_size, std::string hasher)
    : scan_dirs(VectorStrToPath(scan_dirs)), exclude_dirs(VectorStrToPath(exclude_dirs)), block_size(block_size),
      scan_depth(scan_depth), min_file_size(min_file_size)
{
    SetHasher(hasher);
    //set regex
    for (const auto &i : filemasks_)
    {
        filemasks.emplace_back(boost::regex(i));
    }
};

std::unordered_map<std::string, std::vector<std::string>> DuplicateSearcher::FindDuplicates()
{
    RunSearch();
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

void DuplicateSearcher::SetScanDirs(std::vector<std::string> dirs)
{
    scan_dirs = VectorStrToPath(dirs);
}

void DuplicateSearcher::SetExcludeDirs(std::vector<std::string> dirs)
{
    exclude_dirs = VectorStrToPath(dirs);
}

void DuplicateSearcher::RunSearch()
{
    for (const auto &i : scan_dirs)
    {
        ScanPath(i, scan_depth);
    }
}
