#include "file.hpp"

namespace fs = boost::filesystem;

bool hashblock::operator==(const hashblock &other) const
{
    return data == other.data;
}
bool hashblock::operator!=(const hashblock &other) const
{
    return !(*this == other);
}
/*! 
*  @brief const comparsion for unordered_set
*/
bool File::operator==(const File &other) const
{
    return fs::equivalent(path, other.path);
}
/*! 
*  @brief getter for size of calculated hash
*/
size_t File::GetHashDataSize() const
{
    return hash_data.size();
}
/*! 
*  @brief getter for filesize
*/
uintmax_t File::GetFileSize() const
{
    return filesize;
}
/*! 
*  @brief getter for path
*/
fs::path File::GetPath() const
{
    return path;
}
/*! 
*  @brief Открыть файл и перейти в место последнего невычесленного блока
*/
void File::OpenHandle()
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
void File::CloseHandle()
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
std::unique_ptr<char[]> File::GetNextBlock()
{
    OpenHandle();
    auto buffer = std::make_unique<char[]>(blocksize);
    file_handle->read(buffer.get(), blocksize);
    return buffer;
}

/*! 
*  @brief Вычислить следующий блок хеша.
*/
void File::CalcNextHash()
{
    hash_data.emplace_back(hashblock{hasher->Hash(GetNextBlock().get(), blocksize)});
}

/*! 
*  @brief Вычислить хеш до блока N включительно.
*/
hashblock File::CalcHashblock(size_t addr)
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
hashblock File::GetHashblock(size_t addr)
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
bool File::EqualByHashTo(File &other)
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
