/*
 * @Author: hawrkchen
 * @Date: 2024-12-05 15:07:08
 * @Description: 
 * @FilePath: /hv_demo/common/crypto_suite.cpp
 */

#include "crypto_suite.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/des.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>


std::string CryptoSuite::base64_encode(const std::string& input)
{   
    BIO* bio, *b64;
    BUF_MEM* buffer;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);  // 去掉换行符
    BIO_write(bio, input.c_str(), input.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &buffer);

    std::string output(buffer->data, buffer->length);   
    BIO_free_all(bio);
    BUF_MEM_free(buffer);

    return output;

}

std::string CryptoSuite::base64_decode(const std::string& input)
{
    BIO* bio, *b64;
    char* buffer = new char[input.length()];
    memset(buffer, 0, input.length());

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf((void*)input.c_str(), input.length());
    bio = BIO_push(b64, bio);

    // 启动解密
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);  // 去掉换行符
    int decode_len = BIO_read(bio, buffer, input.length());

    std::string output(buffer, decode_len);
    BIO_free_all(bio);
    delete[] buffer;

    return output;
}

std::string CryptoSuite::get_md5_string(const char* data) 
{
   unsigned char md5_digest[MD5_DIGEST_LENGTH];
   MD5((unsigned char*)data, strlen(data), md5_digest);

   char buf[2 * MD5_DIGEST_LENGTH + 1] = {0};
   for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
      sprintf(buf + i * 2, "%02x", md5_digest[i]);
   }
   return std::string(buf);
}

std::string CryptoSuite::get_file_md5(const std::string& file_name)
{
    std::ifstream ifs(file_name.c_str(), std::ios::in | std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return "";
    }

    MD5_CTX context;
    MD5_Init(&context);

    ifs.seekg(0, ifs.end);
    const auto file_size = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    char buffer[1024] = {0};
    unsigned long long total_count = 0;
    decltype(ifs.good()) read_count = 0;

    while(ifs.good()) {

        ifs.read(buffer, sizeof(buffer));
        MD5_Update(&context, buffer, ifs.gcount());

        read_count = ifs.gcount();
        total_count += read_count;
    }

    ifs.close();

    if(total_count != (unsigned long long)file_size) {
        std::cerr << "Failed to read file: " << file_name << std::endl;
        return "";
    }

    unsigned char md5_digest[MD5_DIGEST_LENGTH] = {0};
    MD5_Final(md5_digest, &context);

    std::ostringstream oss;
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)md5_digest[i];
    }
    return oss.str();
}


void CryptoSuite::get_sha256_string(const char* data,std::string& out) 
{
    unsigned char sha256_digest[33] = {0};
    SHA256((unsigned char*)data, strlen(data), sha256_digest);

    char buf[65] = {0};
    char tmp[3] = {0};
    for (int i = 0; i < 32; i++) {
        sprintf(tmp, "%02x", sha256_digest[i]);
        strcat(buf, tmp);
    }
    buf[32] = '\0';
    out = std::string(buf);
}

std::string CryptoSuite::des_encrypt(const std::string& plain_text, const std::string& key)
{
    std::string cipher_text; // 密文

    DES_cblock key_cblock;
    memset(key_cblock, 0, sizeof(key_cblock));

    if(key.length() <= 8) {
        memcpy(key_cblock, key.c_str(), key.length());
    } else {
        memcpy(key_cblock, key.c_str(), 8);
    }

    // 密钥转换
    DES_key_schedule key_schedule;
    DES_set_key_unchecked(&key_cblock, &key_schedule);

    const_DES_cblock plain_block;  // input
    DES_cblock cipher_block;   // output 
    std::vector<unsigned char> plain_vec;
    unsigned char tmp[8] = {0};

    for(size_t ikun = 0; ikun < plain_text.length()/8; ikun ++) {
        memcpy(plain_block, plain_text.c_str() + ikun*8, 8);
        DES_ecb_encrypt(&plain_block, &cipher_block, &key_schedule, DES_ENCRYPT);
        memcpy(tmp, cipher_block, 8);
        
        for(int j = 0; j < 8; j++) {
            plain_vec.push_back(tmp[j]);
        }
    }

    if(plain_text.length() % 8 != 0) {
        int remain_len = plain_text.length()/8 * 8;
        int remain_byte = plain_text.length() - remain_len;
        memset(plain_block, 0, sizeof(plain_block));
        memcpy(plain_block, plain_text.c_str() + remain_len, remain_byte);
        // 加密
        DES_ecb_encrypt(&plain_block, &cipher_block, &key_schedule, DES_ENCRYPT);
        memcpy(tmp, cipher_block, 8);
        for(int jkun = 0; jkun < 8; jkun++) {
            plain_vec.push_back(tmp[jkun]);
        }
    }

    cipher_text.assign(plain_vec.begin(), plain_vec.end());
    return cipher_text;
}

std::string CryptoSuite::des_decrypt(const std::string& cipher_text, const std::string& key)
{
    std::string plain_text; // 明文

    DES_cblock key_cblock;
    memset(key_cblock, 0, sizeof(key_cblock));

    if(key.length() <= 8) {
        memcpy(key_cblock, key.c_str(), key.length());
    } else {
        memcpy(key_cblock, key.c_str(), 8);
    }

    // 密钥转换
    DES_key_schedule key_schedule;
    DES_set_key_unchecked(&key_cblock, &key_schedule);

    const_DES_cblock cipher_block;  // input
    DES_cblock plain_block;   // output 
    std::vector<unsigned char> plain_vec;
    unsigned char tmp[8] = {0};

    for(size_t ikun = 0; ikun < cipher_text.length()/8; ikun ++) {
        memcpy(cipher_block, cipher_text.c_str() + ikun*8, 8);
        DES_ecb_encrypt(&cipher_block, &plain_block, &key_schedule, DES_DECRYPT);
        memcpy(tmp, plain_block, 8);
        
        for(int j = 0; j < 8; j++) {
            plain_vec.push_back(tmp[j]);
        }
    }

    if(cipher_text.length() % 8 != 0) {
        int remain_len = cipher_text.length()/8 * 8;
        int remain_byte = cipher_text.length() - remain_len;
        memset(cipher_block, 0, sizeof(cipher_block));
        memcpy(cipher_block, cipher_text.c_str() + remain_len, remain_byte);
        // 解密
        DES_ecb_encrypt(&cipher_block, &plain_block, &key_schedule, DES_DECRYPT);
        memcpy(tmp, plain_block, 8);
        for(int jkun = 0; jkun < 8; jkun++) {
            plain_vec.push_back(tmp[jkun]);
        }
    }

    plain_text.assign(plain_vec.begin(), plain_vec.end());
    return plain_text;
}

std::string CryptoSuite::aes_encrypt(const std::string& plain_text, const std::string& key)
{
    if(key.length() != 16) {
        std::cerr << "AES key length should be 16 bytes" << std::endl;
        return "";
    }
    // 生成随机16字节IV
    std::vector<unsigned char> iv(16, 0);
    RAND_bytes(iv.data(), iv.size());

    // 初始化上下文
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(ctx == nullptr) {
        std::cerr << "Failed to create cipher context" << std::endl;
        return "";
    }

    // 设置加密算法为AES-128-CBC
    const EVP_CIPHER* cipher = EVP_aes_128_cbc();
    if(cipher == nullptr) {
        std::cerr << "Failed to create cipher" << std::endl;
        return "";
    }

    // 设置密钥和IV
    int ret = EVP_EncryptInit_ex(ctx, cipher, nullptr, (const unsigned char*)key.c_str(), (const unsigned char*)iv.data());
    if(ret != 1) {
        std::cerr << "Failed to initialize cipher context" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    // 加密
    int outlen = 0;
    int ciphertext_len;
    std::vector<unsigned char> cipher_vec(plain_text.length() + AES_BLOCK_SIZE, 0);
    ret = EVP_EncryptUpdate(ctx, cipher_vec.data(), &outlen, (const unsigned char*)plain_text.c_str(), plain_text.length());
    if(ret != 1) {
        std::cerr << "Failed to encrypt data" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    ciphertext_len = outlen;

    //完成加密
    ret = EVP_EncryptFinal_ex(ctx, cipher_vec.data() + outlen, &outlen);
    if(ret != 1) {  
        std::cerr << "Failed to finalize encryption" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    ciphertext_len += outlen;

    // 释放上下文
    EVP_CIPHER_CTX_free(ctx);

    // 合并IV和密文
    std::string cipher_text(iv.begin(), iv.end());
    cipher_text.append((char*)cipher_vec.data(), ciphertext_len);

    return cipher_text;

}

std::string CryptoSuite::aes_decrypt(const std::string& cipher_text, const std::string& key)
{
    if(key.length() != 16) {
        std::cerr << "AES key length should be 16 bytes" << std::endl;
        return "";
    }
    if(cipher_text.length() < 16) {
        std::cerr << "Cipher text length should be greater than 16 bytes" << std::endl;
        return "";
    }
    // 获取IV
    std::vector<unsigned char> iv(cipher_text.begin(), cipher_text.begin() + 16);
    std::string encrypted_text(cipher_text.begin() + 16, cipher_text.end());   // 截取密文
    // 初始化上下文
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(ctx == nullptr) {
        std::cerr << "Failed to create cipher context" << std::endl;
        return "";
    }
   // 设置加密算法为AES-128-CBC
    const EVP_CIPHER* cipher = EVP_aes_128_cbc();
    if(cipher == nullptr) {
        std::cerr << "Failed to create cipher" << std::endl;
        return "";
    }
    // 设置密钥和IV
    int ret = EVP_DecryptInit_ex(ctx, cipher, nullptr, (const unsigned char*)key.c_str(), (const unsigned char*)iv.data());
    if(ret != 1) {
        std::cerr << "Failed to initialize cipher context" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    // 解密
    int outlen = 0;
    int plaintext_len;
    std::vector<unsigned char> plain_vec(encrypted_text.length(), 0);
    // 解密数据
    ret = EVP_DecryptUpdate(ctx, plain_vec.data(), &outlen, (const unsigned char*)encrypted_text.c_str(), encrypted_text.length());
    if(ret != 1) {
        std::cerr << "Failed to decrypt data" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    plaintext_len = outlen;
    // 完成解密
    ret = EVP_DecryptFinal_ex(ctx, plain_vec.data() + outlen, &outlen);
    if(ret != 1) {
        std::cerr << "Failed to finalize decryption" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    plaintext_len += outlen;
    // 释放上下文
    EVP_CIPHER_CTX_free(ctx);
    // 转换为字符串
    std::string plain_text((char*)plain_vec.data(), plaintext_len);
    return plain_text;  

}

std::tuple<std::string, std::string> CryptoSuite::generate_key_pair()
{
    // 生成RSA密钥对
    RSA* rsa = RSA_new();
    if(rsa == nullptr) {
        std::cerr << "Failed to create RSA key pair" << std::endl;
        return std::make_tuple("", "");
    }
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);
    
    if(RSA_generate_key_ex(rsa, 2048, e, nullptr) != 1) {
        std::cerr << "Failed to generate RSA key pair" << std::endl;
        RSA_free(rsa);
        BN_free(e);
        return std::make_tuple("", "");
    }

    // 私钥
    BIO* private_key_bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(private_key_bio, rsa, nullptr, nullptr, 0, nullptr, nullptr);
    char* private_key_str = nullptr;
    long private_key_len = BIO_get_mem_data(private_key_bio, &private_key_str);
    std::string private_key(private_key_str, private_key_len);

    // 公钥
    BIO* public_key_bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(public_key_bio, rsa);
    char* public_key_str = nullptr;
    long public_key_len = BIO_get_mem_data(public_key_bio, &public_key_str);
    std::string public_key(public_key_str, public_key_len);

    // 释放资源
    BIO_free_all(private_key_bio);
    BIO_free_all(public_key_bio);
    RSA_free(rsa);    
    BN_free(e);
    
    return std::make_tuple(private_key, public_key);
}

std::string CryptoSuite::rsa_signature_data(const std::string& data, const std::string& private_key)
{
    // 加载私钥
    RSA* rsa = nullptr;
    BIO* private_key_bio = BIO_new_mem_buf((void*)private_key.c_str(), private_key.length());
    rsa = PEM_read_bio_RSAPrivateKey(private_key_bio, &rsa, nullptr, nullptr);
    if(rsa == nullptr) {
        std::cerr << "Failed to load private key" << std::endl;
        BIO_free_all(private_key_bio);
        return "";
    }

    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256((unsigned char*)data.c_str(), data.length(), hash);
    // 签名
    unsigned char* signature = new unsigned char[RSA_size(rsa)];
    unsigned int signature_len;
    RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &signature_len, rsa);
    std::string signatureResult((char*)signature, signature_len);

    // 释放资源
    delete[] signature;
    BIO_free_all(private_key_bio);
    RSA_free(rsa);

    return signatureResult;
}

bool CryptoSuite::rsa_verify_signature(const std::string& data, const std::string& signature, 
    const std::string& public_key)
{
    // 加载公钥
    RSA* rsa = nullptr;
    BIO* public_key_bio = BIO_new_mem_buf((void*)public_key.c_str(), public_key.length()); 
    rsa = PEM_read_bio_RSAPublicKey(public_key_bio, &rsa, nullptr, nullptr);
    if(rsa == nullptr) {
        std::cerr << "Failed to load public key" << std::endl;
        BIO_free_all(public_key_bio);
        return false;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256((unsigned char*)data.c_str(), data.length(), hash);
    // 验证签名
    int result = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, (unsigned char*)signature.c_str(), signature.length(), rsa);
    if(result != 1) {
        std::cerr << "Failed to verify signature" << std::endl;
        BIO_free_all(public_key_bio);
        RSA_free(rsa);
        return false;
    }   
    
    // 释放资源
    BIO_free_all(public_key_bio);
    RSA_free(rsa);

    return true;
}
