#pragma once
#include "hash.hpp"

#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>

namespace fs = boost::filesystem;

/*! 
*  @brief single hash node
*/
struct hashblock
{
    unsigned int data;
    bool operator==(const hashblock &other) const;
    bool operator!=(const hashblock &other) const;
};

    /*! 
*  @brief class for file with hash comparsion
*/
class File
{
    fs::path path;
    uintmax_t filesize;
    std::vector<hashblock> hash_data;
    uintmax_t blocksize;
    IHasher *hasher;
    std::unique_ptr<std::ifstream> file_handle;

public:
    bool in_result = false;
    const size_t blockcount;
    File(fs::path path, uintmax_t size, uintmax_t hash_blocksize, IHasher *hasher) //
        : path(path), filesize(size), blocksize(hash_blocksize), hasher(hasher),
          blockcount((size + hash_blocksize - 1) / hash_blocksize){};

    /*! 
*  @brief const comparsion for unordered_set
*/
    bool operator==(const File &other) const;
    size_t GetHashDataSize() const;
    uintmax_t GetFileSize() const;
    fs::path GetPath() const;

    /*! 
*  @brief Открыть файл и перейти в место последнего невычесленного блока
*/
    void OpenHandle();
    /*! 
*  @brief закрыть файл
*/
    void CloseHandle();
    /*! 
*  @brief Получить следующий блок из файла
*/
    std::unique_ptr<char[]> GetNextBlock();
    /*! 
*  @brief Вычислить следующий блок хеша.
*/
    void CalcNextHash();
    /*! 
*  @brief Вычислить хеш до блока N включительно.
*/
    hashblock CalcHashblock(size_t addr);
    /*! 
*  @brief get N-th hashblock
*/
    hashblock GetHashblock(size_t addr);
    /*! 
*  @brief Compare by hash with other File
*/
    bool EqualByHashTo(File &other);
};
