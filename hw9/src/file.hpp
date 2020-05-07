#include "hash.hpp"

#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>

namespace fs = boost::filesystem;



struct hashblock
{
    unsigned int data;
    bool operator==(const hashblock &other) const { return data == other.data; }
    bool operator!=(const hashblock &other) const { return !(*this == other); }
};

class File
{
    fs::path canonical_path;
    //fs::path path;
    uintmax_t filesize;

    std::vector<hashblock> hash_data;
    IHasher *hasher;

    uintmax_t blocksize;
    std::unique_ptr<std::ifstream> file_handle;

public:
    bool in_result = false;
    const size_t blockcount;
    File(fs::path canonical_path, uintmax_t size, uintmax_t hash_blocksize, IHasher* hasher) //
    : canonical_path(canonical_path), filesize(size), blocksize(hash_blocksize), 
    blockcount((size + hash_blocksize - 1) / hash_blocksize), hasher(hasher)
    {};

/*! 
*  @brief const comparsion for unordered set
*/
    bool operator==(const File &other) const
    {
        return canonical_path == other.canonical_path;
    }

    size_t GetHashDataSize() const { return hash_data.size(); }
    uintmax_t GetFileSize() const { return filesize; }
    fs::path GetPath() const { return canonical_path; }

/*! 
*  @brief Открыть файл и перейти в место последнего невычесленного блока
*/
    void OpenHandle()
    {
        if (!file_handle)
        {
            file_handle = std::make_unique<std::ifstream>(GetPath().string());
            file_handle.get()->seekg(hash_data.size() * blocksize);
        }
    }
/*! 
*  @brief закрыть файл
*/
    void CloseHandle()
    {
        if (file_handle != nullptr)
        {
            file_handle->close();
            delete file_handle.release();
        }
    }

/*! 
*  @brief Получить следующий блок из файла
*/
    std::unique_ptr<char[]> GetNextBlock()
    {
        OpenHandle();
        auto buffer = std::make_unique<char[]>(blocksize);
        file_handle->read(buffer.get(), blocksize);
        return buffer;
    }

/*! 
*  @brief Вычислить следующий блок хеша.
*/
    void CalcNextHash()
    {
        hash_data.emplace_back(hashblock{hasher->Hash(GetNextBlock().get(), blocksize)});
    }

    /*! 
*  @brief Вычислить хеш до блока N включительно.
*/
    hashblock CalcHashblock(size_t addr)
    {
        //std::cout << "hash " << addr << '\n';
        while (hash_data.size() <= addr)
        {
            CalcNextHash();
        }
        return hash_data.back();
    }

    /*! 
*  @brief get N-th hashblock
*/
    hashblock GetHashblock(size_t addr)
    {
        if (addr >= blockcount)
            throw;
        if (addr < hash_data.size())
            return hash_data[addr];
        else
            return CalcHashblock(addr);
    }

    /*! 
*  @brief Compare by hash with other File
*/
    bool EqualByHashTo(File &other)
    {
        if (this->GetFileSize() != other.GetFileSize())
            return false;
        for (size_t i = 0; i < blockcount; ++i)
        {
            if (GetHashblock(i) != other.GetHashblock(i))
            {
                CloseHandle();
                other.CloseHandle();
                return false;
            }
        }
        CloseHandle();
        other.CloseHandle();
        return true;
    }
};

/*! 
 *  @brief hash opertor for unordered_map
*/
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
