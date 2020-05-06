#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include <unordered_set>
#include <iterator>
#include <memory>

#include <boost/crc.hpp>

namespace fs = boost::filesystem;
using std::cout;

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

struct hashblock
{
    unsigned int data;
    bool operator==(const hashblock &other) const { return data == other.data; }
    bool operator!=(const hashblock &other) const { return !(*this == other); }
};

class File
{
    fs::path canonical_path;
    uintmax_t filesize;

    std::vector<hashblock> hash_data;
    uintmax_t hash_blocksize;
    std::unique_ptr<std::ifstream> f_handle;

public:
    bool added_to_duplicates = false;
    const size_t hash_blockcount;
    File(fs::path p, uintmax_t size, uintmax_t hash_blocksize) : canonical_path(p), filesize(size), hash_blocksize(hash_blocksize), hash_blockcount((size + hash_blocksize - 1) / hash_blocksize){};

    //const comparsion for unordered set
    bool operator==(const File &other) const
    {
        return canonical_path == other.canonical_path;
    }

    size_t GetHashDataSize() const { return hash_data.size(); }
    uintmax_t GetFileSize() const { return filesize; }
    fs::path GetPath() const { return canonical_path; }

    void OpenHandle()
    {
        if (f_handle != nullptr)
            f_handle = std::make_unique<std::ifstream>(GetPath().string());
    }
    void CloseHandle()
    {
        if (f_handle != nullptr)
        {
            f_handle->close();
            delete f_handle.release();
        }
    }

    std::unique_ptr<char[]> GetNextBlock()
    {
        OpenHandle();
        auto buffer = std::make_unique<char[]>(hash_blocksize);
        f_handle->read(buffer.get(), hash_blocksize);
        return buffer;
    }

    void CalcNextHash()
    {
        if (GetHashDataSize() < hash_blockcount)
        {
            
        }
        else
        {
            throw;
        }
    }

    hashblock CalcHashblock(size_t addr)
    {
        //todo
        hashblock result;
        ///calc hash

        return result;
    }
    hashblock GetHashblock(size_t addr)
    {
        if (addr >= hash_blockcount)
            throw;
        if (addr < hash_data.size())
        {
            return hash_data[addr];
        }
        else
        {
            return CalcHashblock(addr);
        }
    }
};

namespace std
{
template <>
struct hash<File>
{
    size_t operator()(const File &obj) const
    {
        return hash<string>()(obj.GetPath().string());
    }
};
} // namespace std

//template<std::function Hash >
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
                for (const fs::directory_entry &x : fs::directory_iterator(p))
                {
                    ScanPath(x.path(), depth - 1);
                }
            }
        }
    };

public:
    bool HashCompare(File &f1, File &f2)
    {
        if (f1.GetFileSize() != f2.GetFileSize())
            return false;
        for (size_t i = 0; i < f1.hash_blockcount; ++i)
        {
            if (f1.GetHashblock(i) != f2.GetHashblock(i))
                return false;
        }
        return true;
    }

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
            cout << i.GetPath() << '\n';
        }
        //scan every dir
        //
    }
};

int main()
{
    DuplicateSearcher dups;
    // dups.SetScanDirs({"./test_data"});
    // dups.Run();
    int hbs = 100;
    auto p1 = fs::path("./aaa.txt");
    auto p2 = fs::path("./bbb.txt");
    File f1(fs::weakly_canonical(p1), fs::file_size(p1), hbs);
    File f2(fs::weakly_canonical(p2), fs::file_size(p2), hbs);
    bool result = dups.HashCompare(f1, f2);
    cout << result << std::endl;
    return 0;
}