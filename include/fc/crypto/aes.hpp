#pragma once
#include <fc/crypto/sha512.hpp>
#include <fc/crypto/sha256.hpp>
#include <fc/uint128.hpp>
#include <fc/fwd.hpp>
#include <vector>

namespace fc {
    class path;

    class aes_encoder
    {
       public:
         aes_encoder( const fc::sha256& key, const fc::uint128& init_value );
         ~aes_encoder();
     
         uint32_t encode( const char* plaintxt, uint32_t len, const char* ciphertxt );
         uint32_t final_encode( const char* ciphertxt );

       private:
         struct      impl;
         fc::fwd<impl,96> my;
    };

    int aes_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                    unsigned char *iv, unsigned char *ciphertext);

    std::vector<char> aes_encrypt( const fc::sha512& key, const std::vector<char>& plain_text  );
    std::vector<char> aes_decrypt( const fc::sha512& key, const std::vector<char>& cipher_text );

    /** encrypts plain_text and then includes a checksum that enables us to verify the integrety of
     * the file / key prior to decryption. 
     */
    void              aes_save( const fc::path& file, const fc::sha512& key, std::vector<char> plain_text );

    /**
     *  recovers the plain_text saved via aes_save()
     */
    std::vector<char> aes_load( const fc::path& file, const fc::sha512& key );

} // namespace fc 
