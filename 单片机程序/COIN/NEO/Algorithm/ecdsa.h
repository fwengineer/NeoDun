#ifndef __ECDSA_H
#define __ECDSA_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

#define   CONCAT(A, B)               (A ## B)
#define   _HASH_INIT(e)              CONCAT(e, _Init)
#define   _HASH_APPEND(e)            CONCAT(e, _Append)
#define   _HASH_FINISH(e)            CONCAT(e, _Finish)

#if       ECC_HASH == SHA256
#define   HASH_INIT(x)               _HASH_INIT(SHA256)(x)
#define   HASH_FINISH(x, y, z)       _HASH_FINISH(SHA256)(x, y, z) 
#define   HASH_APPEND(x, y, z)       _HASH_APPEND(SHA256)(x, y, z) 
#define   CRL_HASH_SIZE              CRL_SHA256_SIZE
#define   HASHctx_stt                SHA256ctx_stt
#elif     ECC_HASH == SHA1
#define   HASH_INIT(x)               _HASH_INIT(SHA1)(x)
#define   HASH_FINISH(x, y, z)       _HASH_FINISH(SHA1)(x, y, z)
#define   HASH_APPEND(x, y, z)       _HASH_APPEND(SHA1)(x, y, z) 
#define   CRL_HASH_SIZE              CRL_SHA1_SIZE
#define   HASHctx_stt                SHA1ctx_stt
#elif     ECC_HASH == SHA224
#define   HASH_INIT(x)               _HASH_INIT(SHA224)(x)
#define   HASH_FINISH(x, y, z)       _HASH_FINISH(SHA224)(x, y, z)
#define   HASH_APPEND(x, y, z)       _HASH_APPEND(SHA224)(x, y, z)
#define   CRL_HASH_SIZE              CRL_SHA224_SIZE
#define   HASHctx_stt                SHA224ctx_stt
#elif     ECC_HASH == MD5
#define   HASH_INIT(x)               _HASH_INIT(MD5)(x)
#define   HASH_FINISH(x, y, z)       _HASH_FINISH(MD5)(x, y, z) 
#define   HASH_APPEND(x, y, z)       _HASH_APPEND(MD5)(x, y, z) 
#define   CRL_HASH_SIZE              CRL_MD5_SIZE
#define   HASHctx_stt                MD5ctx_stt
#else 
#error    "Not define ECC_HASH !"
#endif 


//ecc需要用到的空间
#define          ECC_STORE_SPACE             3584
// hash算法里面有MD5, SHA1, SHA224 or SHA256
#define          ECC_HASH                    SHA256     //定义HASH算法为SHA256  
//签名方式
#define          ECC_SIGN_ALGORITHM          ECDSA


//定义椭圆参数的结构体
//参数a，p，n是必须的，GX，GY也是必须的，
//指针无值需要赋值为空, 长度为0
typedef struct 
{
	uint8_t *p_a;
	uint8_t *p_p;
	uint8_t *p_b;
	uint8_t *p_n;
	uint8_t *p_Gx;
	uint8_t *p_Gy;
	int32_t a_size;
	int32_t b_size;	
	int32_t p_size;
	int32_t n_size;
	int32_t Gx_size;
	int32_t Gy_size;
}EC_Para;


//公钥结构体
typedef struct 
{
	uint8_t *pub_x;
	uint8_t *pub_y;
	int32_t pub_xSize;
	int32_t pub_ySize;
}Pub_Key_Para;


//私钥结构体
typedef struct 
{
	uint8_t *priv;
	int32_t priv_size;
}Priv_Key_Para;


//私钥结构体
typedef struct 
{
	uint8_t *g_x;
	uint8_t *g_y;
	int32_t g_xSize;
	int32_t g_ySize;
}G_Para;


//签名结构体
typedef struct  
{
	uint8_t *sign_r;
	uint8_t *sign_s;
	int32_t sign_rSize;
	int32_t sign_sSize;
}Sign_Para;


//摘要结构体
typedef struct  
{
	uint8_t *digt;
	int32_t digest_size;
}Digest_Para;


//输入信息结构体
typedef struct  
{
	uint8_t *input_msg;
	int32_t inputMsg_size;
}InputMsg_Para;


//ecc签名函数
int32_t Alg_ECDSASignData(uint8_t *dataIn,int dataInLen,uint8_t *dataOut,int *dataoutLen,uint8_t *PriveKEY);

//ecc签名测试函数
void Test_Ecc_Sign_Data(void);

//哈希算法
int32_t Alg_HashData(uint8_t *dataIn,int dataInLen,uint8_t *dataOut,int *dataoutLen);

//从私钥得到公钥
int32_t ECCGetPublickeyFromPrivateKey_OLD(uint8_t *PrivateKey,uint8_t *Publickey);
int32_t Alg_GetPublicFromPrivate(uint8_t *PrivateKey,uint8_t Publickey[65],uint8_t state);

#endif
