/*! 
 *  @brief Алгоритмы хеширования
 */
#include "hash.hpp"

unsigned int CRC32Hasher::Hash(const char *buffer, unsigned int buffer_length)
    {
        boost::crc_32_type result;
        result.process_bytes(buffer, buffer_length);
        return result.checksum();
    }

using boost::uuids::detail::md5;
unsigned int MD5Hasher::Hash(const char *buffer, unsigned int buffer_length){
        md5 hash;
        md5::digest_type digest;
        hash.process_bytes(buffer, buffer_length);
        hash.get_digest(digest);
        return digest[0];
    }

using boost::uuids::detail::sha1;
unsigned int SHA1Hasher::Hash(const char *buffer, unsigned int buffer_length){
        sha1 hash;
        sha1::digest_type digest;
        hash.process_bytes(buffer, buffer_length);
        hash.get_digest(digest);
        return digest[0];
    }
