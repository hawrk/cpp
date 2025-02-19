/*
 * @Author: hawrkchen
 * @Date: 2024-12-06 11:51:21
 * @Description: 
 * @FilePath: /hv_demo/test/test_crypto_suite.cpp
 */
#include "../common/crypto_suite.hpp"

int main()  
{
    auto [prikey, pubkey] = g_crypto_suite.generate_key_pair();
    std::cout << "公钥：" << pubkey << std::endl;
    std::cout << "私钥：" << prikey << std::endl;

    std::string plain_text = "我是一只小小鸟";
    std::string sign = g_crypto_suite.rsa_signature_data(plain_text, prikey);
    std::cout << "签名：" << sign << std::endl;

    // verify signature
    if(g_crypto_suite.rsa_verify_signature(plain_text, sign, pubkey))
    {
        std::cout << "签名验证成功！" << std::endl;
    }
    else
    {
        std::cout << "签名验证失败！" << std::endl;
    }


    std::string out = g_crypto_suite.aes_encrypt("我是一只小小鸟", "0123456789abcdef");
    std::cout << "加密结果：" << out << std::endl;

    std::string in = g_crypto_suite.aes_decrypt(out, "0123456789abcdef");
    std::cout << "解密结果：" << in << std::endl;


    std::string out2 = g_crypto_suite.des_encrypt("我是一只小小鸟", "01234567");
    std::cout << "加密结果2:" << out2 << std::endl;

    std::string in2 = g_crypto_suite.des_decrypt(out2, "01234567");
    std::cout << "解密结果2:" << in2 << std::endl;
    return 0;


}