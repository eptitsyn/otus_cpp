/*! 
 *  @brief Алгоритмы хеширования
 */
#pragma once

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <iostream>

class IHasher
{
public:
    virtual unsigned int Hash(const char *buffer, unsigned int buffer_length) = 0;
};

class CRC32Hasher : public IHasher
{
public:
    virtual unsigned int Hash(const char *buffer, unsigned int buffer_length)
    {
        boost::crc_32_type result;
        result.process_bytes(buffer, buffer_length);
        return result.checksum();
    }
};

using boost::uuids::detail::md5;
class MD5Hasher : public IHasher
{
public:
    virtual unsigned int Hash(const char *buffer, unsigned int buffer_length){
        md5 hash;
        md5::digest_type digest;
        hash.process_bytes(buffer, buffer_length);
        hash.get_digest(digest);
        return digest[0];
    }
};

using boost::uuids::detail::sha1;
class SHA1Hasher : public IHasher
{
public:
    virtual unsigned int Hash(const char *buffer, unsigned int buffer_length){
        sha1 hash;
        sha1::digest_type digest;
        hash.process_bytes(buffer, buffer_length);
        hash.get_digest(digest);
        return digest[0];
    }
};
