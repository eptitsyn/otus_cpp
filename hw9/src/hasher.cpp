//hasher
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <fstream>
#include <iostream>
#include <memory>

using boost::uuids::detail::sha1;

const int hash_blocksize = 1000;

std::unique_ptr<char[]> GetNextBlock(std::ifstream &handler)
{
    auto buffer = std::make_unique<char[]>(hash_blocksize);
    handler.read(buffer.get(), hash_blocksize);
    return buffer;
}

int main()
{
    std::ifstream handler("./test1.cpp", std::ios::binary);
    auto p = GetNextBlock(handler);

        sha1 hash;
        sha1::digest_type digest;

        hash.process_bytes(p.get(), hash_blocksize);
        hash.get_digest(digest);

    std::cout << std::hex << std::uppercase << digest[0] << std::endl;
    handler.close();
    return 0;
}