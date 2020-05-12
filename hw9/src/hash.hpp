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
    virtual unsigned int Hash(const char *buffer, unsigned int buffer_length);
};

class MD5Hasher : public IHasher
{
public:
    virtual unsigned int Hash(const char *buffer, unsigned int buffer_length);
};

class SHA1Hasher : public IHasher
{
public:
    virtual unsigned int Hash(const char *buffer, unsigned int buffer_length);
};
