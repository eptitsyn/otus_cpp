/*! 
 *  @brief Алгоритмы хеширования
 */
#include "hash.hpp"

digest CRC32Hasher::Hash(const char *buffer, unsigned int buffer_length)
    {
        boost::crc_32_type result;
        result.process_bytes(buffer, buffer_length);
        return {result.checksum()};
    }

using boost::uuids::detail::md5;
digest MD5Hasher::Hash(const char *buffer, unsigned int buffer_length){
        md5 hash;
        md5::digest_type digest;
        hash.process_bytes(buffer, buffer_length);
        hash.get_digest(digest);
        return std::vector(std::begin(digest), std::end(digest));
    }

using boost::uuids::detail::sha1;
digest SHA1Hasher::Hash(const char *buffer, unsigned int buffer_length){
        sha1 hash;
        sha1::digest_type digest;
        hash.process_bytes(buffer, buffer_length);
        hash.get_digest(digest);
        return std::vector(std::begin(digest), std::end(digest));
    }
