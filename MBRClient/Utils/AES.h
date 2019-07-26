////////////////////////////////////////////////////////////
// base64.h

// 参考文章：http://www.cstc.net.cn/docs/docs.php?id=202

//************************************************************************/
//    base64编码表
// 
//		0 A 17 R 34 i 51 z 
//		1 B 18 S 35 j 52 0 
//		2 C 19 T 36 k 53 1 
//		3 D 20 U 37 l 54 2 
//		4 E 21 V 38 m 55 3 
//		5 F 22 W 39 n 56 4 
//		6 G 23 X 40 o 57 5 
//		7 H 24 Y 41 p 58 6 
//		8 I 25 Z 42 q 59 7 
//		9 J 26 a 43 r 60 8 
//		10 K 27 b 44 s 61 9 
//		11 L 28 c 45 t 62 + 
//		12 M 29 d 46 u 63 / 
//		13 N 30 e 47 v (pad) = 
//		14 O 31 f 48 w 
//		15 P 32 g 49 x 
//		16 Q 33 h 50 y 
//
// base64编码步骤：
// 
//		原文：
//
//		你好
//		C4 E3 BA C3
//		11000100 11100011 10111010 11000011
//		00110001 00001110 00001110 00111010
//		49       14							（十进制）
//		x        O        O        6		字符
//		01111000 01001111 01001111 00110110
//		78									（十六进制）
//		xOO6
//
//		解码：
//		xOO6
//		78 4f 4f 36
//		01111000 01001111 01001111 00110110
//		49       14 
//		00110001 00001110 00001110 00111010   31 0e 0e 3a
//
//		11000100 11100011 10111010
//		C4       E3       BA
//

// 编码后的长度一般比原文多占1/3的存储空间，请保证base64code有足够的空间
// 解码后的长度一般比原文少用占1/4的存储空间，请保证buf有足够的空间

#ifndef __AEYEBASE64HELPER_H__
#define __AEYEBASE64HELPER_H__


#define ENCRYPT 0  
#define DECRYPT 1  

#define ECB 0  
#define CBC 1  

#define KEY_LEN_8 8  
#define KEY_LEN_16 16  
#define KEY_LEN_24 24  

#define PAD_ISO_1   0  
#define PAD_ISO_2   1  
#define PAD_PKCS_7  2  
typedef char (*PSubKey)[16][48];  

class  AES {
public:
	AES();
	virtual ~AES();
public:

  
    /*解密后,将填充的字符去掉*/  
    void RunRsm(char* Text);  
  
    /*将48位的明文密钥转换成24的字符串密钥*/  
    int CovertKey(char* iKey, char *oKey);  
  
    /******************************************************************* 
      函 数 名 称:  RunPad 
      功 能 描 述：  根据协议对加密前的数据进行填充 
      参 数 说 明：  bType   :类型：PAD类型 
                    In      :数据串指针 
                    Out     :填充输出串指针 
                    in_len  :数据的长度 
                    padlen  :(in,out)输出buffer的长度，填充后的长度 
 
      返回值 说明：   char    :是否填充成功 
    *******************************************************************/  
    int RunPad(int nType,const char* In,unsigned in_len,char* Out,int* padlen);  
  
    /******************************************************************* 
    函 数 名 称:    Run1Des 
    功 能 描 述：    执行单DES算法对文本加解密 
    参 数 说 明：    bType   :类型：加密ENCRYPT，解密DECRYPT 
                    bMode   :模式：ECB,CBC 
                    In      :待加密串指针 
                    in_len  :待加密串的长度，同时Out的缓冲区大小应大于或者等于in_len 
                    Key     :密钥(可为8位,16位,24位)支持3密钥 
                    key_len :密钥长度，多出24位部分将被自动裁减 
                    Out     :待输出串指针 
                    out_len :输出缓存大小 
                    cvecstr :8字节随即字符串 
 
    返回值 说明： int     :是否加密成功，1：成功，0：失败 
    *******************************************************************/  
    int Run1Des(int bType, int bMode, const char *In, unsigned int in_len, const char *Key, unsigned int key_len, char* Out, unsigned int out_len, const char cvecstr[8]);  
  
    /******************************************************************* 
      函 数 名 称:  Run3Des 
      功 能 描 述：  执行3DES算法对文本加解密 
      参 数 说 明：  bType   :类型：加密ENCRYPT，解密DECRYPT 
                    bMode   :模式：ECB,CBC 
                    In      :待加密串指针 
                    in_len  :待加密串的长度，同时Out的缓冲区大小应大于或者等于in_len 
                    Key     :密钥(可为8位,16位,24位)支持3密钥 
                    key_len :密钥长度，多出24位部分将被自动裁减 
                    Out     :待输出串指针 
                    out_len :输出缓存大小 
                    cvecstr :8字节随即字符串 
 
      返回值 说明：   int     :是否加密成功，1：成功，0：失败 
 
      作       者:    huangjf 
      更 新 日 期：  2009.6.17 
 
      3DES(加密) = DES(key1, 加密) DES(key2, 解密)  DES(key3, 加密) 
      3DES(解密) = DES(key3, 解密) DES(key2, 加密)  DES(key1, 解密) 
      每个KEY为64位，总共可以有192位的KEY, 但一般都只使用128位的key 
      如果只用128位密钥，则key3 = key1 
 
    *******************************************************************/  
    int Run3Des(int bType, int bMode, const char *In, unsigned int in_len, const char *Key, unsigned int key_len, char* Out, unsigned int out_len, const char cvecstr[8]);  
  
    /******************************************************************* 
    函 数 名 称:    Crypt3Des 
    功 能 描 述：    实现3DES的加解密 
    参 数 说 明：    type    :类型：加密ENCRYPT，解密DECRYPT 
                    in      :待加密串指针或者待解密的密码字符串指针 
                    Out     :加密后的密码或者解密后的明文 
                    Key     :密钥(48位的ASCII字符串) 
 
    返回值 说明： 
                    0:成功 
                    -1:非法的密钥长度 
                    -2:密钥含有非16进制字符 
                    -3:明文填充失败 
                    -4:加解密失败 
                    -5:非法的操作类型 
    *******************************************************************/  
    int Crypt3Des(int type,char* in,int nsrclen,char* key,char* out,int & outLen);

    unsigned char GetByte(char *s);  
	void MyDesInit(int* cryptmode,int* padmode,char* cvec);
};

#endif
