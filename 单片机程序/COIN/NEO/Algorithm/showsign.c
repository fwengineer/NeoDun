#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "showsign.h"
#include "math.h"
#include "getaddress.h"

char Dec[BUFSIZ];				//存储10进制的大数
char Hex[BUFSIZ];				//存储16进制的大数
char final[BUFSIZ] = "";//存储最终的字符串商
char Alphabet[58] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
char finaladdress[50] = "";  //存储最终的字符地址
int index_add = 0;      //字符地址对应的索引

/******************************************************************
*	函数名：	GetIndexFromBuff
*	函数说明：查询字符在数组中的下标
* 输入参数：buff	查询数组
                        ch		要查询的字符
* 输出参数：index 返回查询到的索引
*******************************************************************/
int GetIndexFromBuff(char *buff,char ch)
{
        int index = 0;
        int i;
        for(i=0;i<strlen(buff);i++)
        {
                if(buff[i] == ch)
                {
                        index = i;
                        break;
                }
        }
        return index;
}

/******************************************************************
*	函数名：	Ascii2Dec
*	函数说明：查询Ascii表示的字符对应的10进制数
* 输入参数：ch		输入字符
* 输出参数：value 输出10进制数
*******************************************************************/
int Ascii2Dec(char ch)
{
        int value=0;
        switch (ch)
        {
              case '0':
                        value = 0;
                        break;
              case '1':
                        value = 1;
                        break;
              case '2':
                        value = 2;
                        break;
              case '3':
                        value = 3;
                        break;
              case '4':
                        value = 4;
                        break;
              case '5':
                        value = 5;
                        break;
              case '6':
                        value = 6;
                        break;
              case '7':
                        value = 7;
                        break;
              case '8':
                        value = 8;
                        break;
              case '9':
                        value = 9;
                        break;
              case 'a':
              case 'A':
                        value = 10;
                        break;
              case 'b':
              case 'B':
                        value = 11;
                        break;
              case 'c':
              case 'C':
                        value = 12;
                        break;
              case 'd':
              case 'D':
                        value = 13;
                        break;
              case 'e':
              case 'E':
                        value = 14;
                        break;
              case 'f':
              case 'F':
                        value = 15;
                        break;
                default:
                        printf("Not a ascii char!!!\r\n");
                        break;
        }
        return value;
}
/******************************************************************
*	函数名：	ReverseArray
*	函数说明：对字符数组进行对称翻转
* 输入参数：buf	输入字符数组
* 输出参数：
*******************************************************************/
void ReverseArray(char *buf)//翻转数组
{
    int i;
    char x;
    int len =0;

    len = strlen(buf);

    for(i=0;i<len/2;i++)
    {
        x = buf[i];
        buf[i] = buf[len-i-1];
        buf[len-i-1] = x;
    }
}
/******************************************************************
*	函数名：	bigdiv
*	函数说明：对字符数组表示的大数进行除法运算
* 输入参数：diva	除数字符数组
                        lena	除数数组长度
                        divb	被除数字符数组
                        lenb	被除数数组长度
* 输出参数：len	是返回商的长度
*******************************************************************/
int bigdiv(char *diva,int lena,char *divb,int lenb)
{
    int i=0,j=0,k=0,len=0;
    int yushu[2] = {0,0};
        char result_tmp[BUFSIZ];//存储临时的商值，即进入strcmp循环的次数

//		printf("lena = %d",lena);
//		printf("   lenb = %d\r\n",lenb);
//		puts(diva);
//		printf("\r\ndiva\r\n");
//		puts(divb);
//		printf("\r\ndivb\r\n");

    memset(final,0,512);
    //死循环只有当lena和lenb相等时跳出循环，因为会不断的在divb数组前加0所以该数组的长度会不断的
    //变化，当两者相等时说明已经无法再作减法
    while(1)
    {
        result_tmp[k]=0;
        //strcmp函数的比较方式是从前到后依次比较，如果相等则向后移动一位，一旦发现不等
        //则立即返回忽略后面的所有数据
        while(strcmp(diva,divb)>=0)//比较最高位，需不需要通过移位，来做减法
        {
            i=0;
            while(1)
            {
                if(diva[i]=='0')//去除diva高位前面的0，减少计算0的步数
                {
                    i++;
                }
                else
                {
                    j = i;//去除divb高位填充的0
                    break;
                }
            }

            for(;i<lenb;i++)//做减法
                diva[i]=diva[i]-divb[i]+'0';

            for(i=lenb-1;i>j;i--)//每作一组减法就整理数组
            {
                if(diva[i]<'0')
                {
                    diva[i]+=10;
                    diva[i-1]--;
                }
            }
            result_tmp[k]++;
        }
        k++;
        if(lena == lenb)
            break;
        for(i=lenb-1;i>=0;i--)//将divb中的元素先后移位，同时扩大divb长度并且在divb前端补一位0
            divb[i+1]=divb[i];
        divb[0]='0';//由于数组后移所以divb[0]每次移动后都为空，所以每次用0补齐
        lenb++;
        divb[lenb]='\0';//在结尾加上字符串的结束标记
    }

    i=0;j=0;
    while(result_tmp[i]==0)//得到正确计算商的值所需的索引，不为0开始
        {
        i++;
        }

    for(;i<k;i++)//得到最终字符形式的商
    {
        final[j++]=result_tmp[i]+'0';
    }
    len = j;//len是返回商的长度

    j=0;
    while(diva[j]=='0') //得到计算余数所需的索引
        {
                j++;
        }
    if(j==lena)//全为0的特殊情况，即除数为0
    {
//        printf("0\n");
        finaladdress[index_add] = '1';
        index_add++;
        return len;
    }
    i=0;
    for(;j<lena;j++)
    {
        yushu[i] = diva[j] - '0';
        i++;
    }

    if(i==1)
    {
        finaladdress[index_add] = Alphabet[yushu[0]];
    }
    else if(i==2)
    {
        finaladdress[index_add] = Alphabet[yushu[0]*10+yushu[1]];
    }
    else
    {
                printf("Error！！！\r\n");
    }

    index_add++;
    return len;
}
/******************************************************************
*	函数名：	DecTOAddress
*	函数说明：将10进制表示的大数字符数组进行Base58编码
* 输入参数：str	输入数组
* 输出参数：
*******************************************************************/
void DecTOAddress(char *str)//将10进制大数转换成地址
{
    int lena,lenb,i,len;
    int value = 0;
    char sa[BUFSIZ] = "";
    char sb[BUFSIZ] = "58";
        memset(finaladdress,0,512);

    for(i=0;i<strlen(str);i++)
        {
                sa[i] = str[i];
        }

    do
    {
        lena=strlen(sa);
        lenb=strlen(sb);
        len = bigdiv(sa,lena,sb,lenb);

        memset(sa,0,512);
        for(i=0;i<len;i++)
            sa[i] = final[i];

        if(len == 2)
            value = (final[0]-'0')*10 + final[1]-'0';
        if(len == 1)
            value = final[0]-'0';

        memset(sb,0,512);
        strcpy(sb,"58");
    }while((len > 2)||(value > 58));

    finaladdress[index_add] = Alphabet[value];//添加最后一个余数的遍历
    ReverseArray(finaladdress);
    index_add = 0;
}
/******************************************************************
*	函数名：	strupr
*	函数说明：将16进制字符数组中的大写字符改为小写字符
* 输入参数：buff	输入数组
* 输出参数：
*******************************************************************/
void strlwr(char *buff)
{
    int i;
    int len=strlen(buff);

    for(i=0;i<len;i++)
    {
        if((buff[i] >= 'A')&&(buff[i] <= 'F'))
        {
            buff[i] = buff[i]+32;
        }
    }
}
/******************************************************************
*	函数名：	strupr
*	函数说明：将16进制字符数组中的小写字符改为大写字符
* 输入参数：buff	输入数组
* 输出参数：
*******************************************************************/
void strupr(char *buff)
{
    int i;
    int len=strlen(buff);

    for(i=0;i<len;i++)
    {
        if(buff[i] >= 'a')
        {
            buff[i] = buff[i]-32;
        }
    }
}
/******************************************************************
*	函数名：	HexToDec
*	函数说明：将字符数组表示的大数,进行16进制转10进制
* 输入参数：src			输入数组
                        result	输出结果数组
* 输出参数：
*******************************************************************/
void HexToDec(char *src,char *result)//16进制转10进制
{
    char pn_Result[BUFSIZ];
    char pn_old[BUFSIZ];
    unsigned char num,rn,c,len,m=0,i,j;
        char str[80];

    len=strlen(src);
        for(c=0;c<len;c++)
                str[c] = src[c];
    for(c=0; c<len; c++)
        {
        if(!isxdigit(str[c]))//检查是否为16进制数
        {
            printf("      Sorry! You are errer. Can only enter hexadecimal digit!!!\r\n");
            return;
        }
        }
    strcpy(pn_old,str);
    strupr(str);
        i=0;
    while((c=str[i])!=0)
    {
        if(c=='0')//不够除10的商为0
        {
            i++;
            continue;//更新c值，做新的计算
        }
        num=c-(c<='9' ? '0' : 0x37);
                //字符数组，从左往右除10得到余数
        for(j=i;;j++)
        {
            c=num/10;
            str[j]=c+(c<=9 ? '0' : 0x37);
            rn=num%10;
            if((c=str[j+1])==0)//算到数组末端，退出for循环
                break;
            num=16*rn+c-(c<='9' ? '0' : 0x37);
        }
        pn_Result[m++]=rn+'0';//记录每次的余数
    }
    pn_Result[m]=0;//数组末尾添加0

        ReverseArray(pn_Result);
    strcpy(result,pn_Result);
//		printf("result:%s\r\n",result);
}
/******************************************************************
*	函数名：	Div
*	函数说明：大数字符数组的除法计算，s1整除2，商放入s2中
* 输入参数：s1	存储除数的大数字符数组
                        s2	存储商的大数字符数组
* 输出参数：
*******************************************************************/
void Div(char s1[],char s2[])
{
    int i,j,k,t,yu;
    if((s1[0]<'2')&&(strlen(s1)==1))
    {
        s2[0]='0';
        s2[15]=0;
    }
    else
    {
        k=strlen(s1);
        j=0;
        yu = (s1[0]-48)%2;
        if(s1[0]>'1')
            s2[j++]=(s1[0]-48)/2+48;
        for(i=1;i<k;i++)
        {
            t=yu*10+s1[i]-48;
            if(t<2)
            {
                s2[j++]='0';
                yu=t%2;
            }
            else
            {
                s2[j++]=t/2+48;
                yu=t%2;
            }
        }
        s2[j]=0;
    }
}
/******************************************************************
*	函数名：	DecToHex
*	函数说明：将字符数组表示的大数,进行2进制转16进制
* 输入参数：s2 	2进制大数数组
                        s16	16进制大数数组
* 输出参数：
*******************************************************************/
void convert2to16(char s2[],char s16[])//将2进制转换为16进制
{
    int i,len,t,k,j;
    char s[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    len=strlen(s2);
    t=0;
    k=1;
    j=0;

    if(len%4!=0)
    {
        for(i=len%4-1;i>=0;i--)
        {
            t += (s2[i]-48)*k;
            k=k*2;
        }
        s16[j++]=s[t];
    }

    for(i=len%4;i<len;i+=4)
    {
        t=(s2[i]-48)*8+(s2[i+1]-48)*4+(s2[i+2]-48)*2+(s2[i+3]-48)*1;
        s16[j++]=s[t];
    }
    s16[j]=0;
}
/******************************************************************
*	函数名：	DecToHex
*	函数说明：将字符数组表示的大数,进行10进制转16进制
* 输入参数：buff 输入数组
* 输出参数：
*******************************************************************/
void DecToHex(char *str,char *result)
{
    char shang[BUFSIZ] = "";
        char two[BUFSIZ] = "";
        char sixteen[BUFSIZ] = "";//记录待转换的数据
    int i=0,Len;

    do
    {
        Div(str,shang);
        Len=strlen(str);
        two[i++]=str[Len-1]%2+48;
        strcpy(str,shang);
    }while(str[0]!='0');

    two[i]=0;
    ReverseArray(two);
    convert2to16(two,sixteen);
        for(i=0;i<strlen(sixteen);i++)
                result[i] = sixteen[i];
//		printf("sixteen:%s\r\n",sixteen);
}
/******************************************************************
*	函数名：	Convert2address
*	函数说明：将字符数组表示的大数转换成地址
* 输入参数：buff 输入数组
* 输出参数：
*******************************************************************/
void Convert2address(char *buff)
{
        printf("buff:%s\r\n",buff);
    HexToDec(buff,Dec);
        printf("Dec:%s\r\n",Dec);
    DecTOAddress(Dec);
}
/******************************************************************
*	函数名：	HexToString
*	函数说明：将输入16进制数组，转换成字符数组
* 输入参数：src		输入16进制数组
                        len		转换的长度
                        desc	输出数组
* 输出参数：
*******************************************************************/
void HexToString(uint8_t *src,int len,char *desc)
{
        int i;
        for(i=0;i<len;i++)
        {
                desc[2*i] = src[i]/16 + (src[i]/16 <= 9 ? '0' : 0x37);
                desc[2*i+1] = src[i]%16 + (src[i]%16 <= 9 ? '0' : 0x37);
        }
}
/******************************************************************
*	函数名：	StringToHex
*	函数说明：将输入字符数组，转换成16进制的数组
* 输入参数：src		输入字符数组
                        len		转换的长度
                        desc	输出数组
* 输出参数：
*******************************************************************/
void StringToHex(char *src,int len,uint8_t *desc)
{
        int i;
        for(i=0;i<len;i++)
        {
                desc[i] = Ascii2Dec(src[2*i])*16+Ascii2Dec(src[2*i+1]);
        }
}
/******************************************************************
*	函数名：	ReverseString
*	函数说明：将输入字符数组，以字节反转
* 输入参数：buf 输入数组
* 输出参数：
*******************************************************************/
void ReverseString(char *buf)
{
        int i;
        int len = strlen(buf);
        char ch1,ch2;
        for(i=0;i<len/4;i++)
        {
                ch1 = buf[2*i];
                ch2 = buf[2*i+1];

                buf[2*i] = buf[len-2*i-2];
                buf[2*i+1] = buf[len-2*i-1];

                buf[len-2*i-2] = ch1;
                buf[len-2*i-1] = ch2;
        }
}
/******************************************************************
*	函数名：	CountMoney
*	函数说明：解析数组字符串对应的钱的数额
* 输入参数：buff 输入数组
* 输出参数：value 浮点数类型的钱
*******************************************************************/
uint64_t CountMoney(uint8_t *buff)
{
		int i;
	  int64_t num=0;
		char result[16] = "";
	
		HexToString(buff,8,result);
		for(i=0;i<16;i++)
		{
				num += Ascii2Dec(result[15-i])*pow(16,i);
		}
	
		return num;
}

/******************************************************************
*	函数名：	CountMoney
*	函数说明：解析数组字符串对应的钱的数额
* 输入参数：buff 输入数组
* 输出参数：value 浮点数类型的钱
*******************************************************************/
uint64_t Nep5CountMoney(uint8_t *buff,int len)
{
		int i;
	  uint64_t num=0;

	
		for(i=0;i<len;i++)
		{
				num += buff[i]<<(8*i);
		}
	
		return num;
}

/******************************************************************
*	函数名：	ReadByteLengthIndex
*	函数说明：计算长度标识符fd不同类型占用的字节长度
* 输入参数：fd 长度标识符
* 输出参数：index 占用的字节长度
*******************************************************************/
int ReadByteLengthIndex(int fb)
{
        int index=0;
        if(fb == 0xfd)
                index = 2;
        else if(fb == 0xfe)
                index = 4;
        else if(fb == 0xff)
                index = 8;
        else
                index = 0;
        return index;
}
/******************************************************************
*	函数名：	ReadByteLength
*	函数说明：计算需要读取数组的字节长度
* 输入参数：buff	需要处理的数组
                        start	开始的指针位置
                        max		读取的最大字节长度
                        fb		长度类型判断
* 输出参数：value 需要读取的长度值，以字节为单位
*******************************************************************/
uint64_t ReadByteLength(uint8_t *buff,int start,int max,int fb)
{
        uint64_t value;
        if(fb == 0xfd)
        {
                value = (buff[start]/16)*pow(16,3) + (buff[start+1]%16)*pow(16,2) + (buff[start+2]/16)*pow(16,1) + (buff[start+3]%16)*pow(16,0);
        }
        else if(fb == 0xfe)
        {
                value = (buff[start]/16)*pow(16,7) + (buff[start+1]%16)*pow(16,6) + (buff[start+2]/16)*pow(16,5) + (buff[start+3]%16)*pow(16,4)
                                +(buff[start+4]/16)*pow(16,3) + (buff[start+5]%16)*pow(16,2) + (buff[start+6]/16)*pow(16,1) + (buff[start+7]%16)*pow(16,0);
        }
        else if(fb == 0xff)
        {
                value = (buff[start]/16)*pow(16,15) + (buff[start+1]%16)*pow(16,14) + (buff[start+2]/16)*pow(16,13) + (buff[start+3]%16)*pow(16,12)
                                +(buff[start+4]/16)*pow(16,11) + (buff[start+5]%16)*pow(16,10) + (buff[start+6]/16)*pow(16,9) + (buff[start+7]%16)*pow(16,8)
                                +(buff[start+8]/16)*pow(16,7) + (buff[start+9]%16)*pow(16,6) + (buff[start+10]/16)*pow(16,5) + (buff[start+11]%16)*pow(16,4)
                                +(buff[start+12]/16)*pow(16,3) + (buff[start+13]%16)*pow(16,2) + (buff[start+14]/16)*pow(16,1) + (buff[start+15]%16)*pow(16,0);
        }
        else
                value = fb;
        if((value > max )|| (value == 0))
                return 0;//出错
        return value;
}

static unsigned char GetAssetID(unsigned char *assetID)
{
		unsigned char gas[32] = {0x60,0x2c,0x79,0x71,0x8b,0x16,0xe4,0x42,0xde,0x58,0x77,0x8e,0x14,0x8d,0x0b,0x10,
														 0x84,0xe3,0xb2,0xdf,0xfd,0x5d,0xe6,0xb7,0xb1,0x6c,0xee,0x79,0x69,0x28,0x2d,0xe7};
		unsigned char neo[32] = {0xc5,0x6f,0x33,0xfc,0x6e,0xcf,0xcd,0x0c,0x22,0x5c,0x4a,0xb3,0x56,0xfe,0xe5,0x93,
														 0x90,0xaf,0x85,0x60,0xbe,0x0e,0x93,0x0f,0xae,0xbe,0x74,0xa6,0xda,0xff,0x7c,0x9b};
		int i;
		
		for(i=0;i<32;i++)
		{
				if(assetID[i] != gas[i])
						break;
		}
		if(i == 32)
				return 0;
		
		for(i=0;i<32;i++)
		{
				if(assetID[i] != neo[i])
						break;
		}											 
		if(i == 32)
				return 1;	
		else
				return 0xff;
}

static unsigned char Nep5GetAssetID(unsigned char *assetID)
{
		unsigned char nnc[20] = {0xfc,0x73,0x2e,0xde,0xe1,0xef,0xdf,0x96,0x8c,0x23,
														 0xc2,0x0a,0x96,0x28,0xea,0xa5,0xa6,0xcc,0xb9,0x34};
		unsigned char cpx[20] = {0xc8,0x8a,0xca,0xae,0x8a,0x03,0x62,0xcd,0xbd,0xed,
														 0xdd,0xf0,0x08,0x3c,0x45,0x2a,0x3a,0x8b,0xb7,0xb8};		
		
		int i;
		
		for(i=0;i<20;i++)
		{
				if(assetID[19-i] != nnc[i])
						break;
		}
		if(i == 20)
				return 2;
		
		for(i=0;i<20;i++)
		{
				if(assetID[19-i] != cpx[i])
						break;
		}
		if(i == 20)
				return 3;
		
		return 0xff;
}
/******************************************************************
*	函数名：	Alg_ShowSignData
*	函数说明：解释签名函数
* 输入参数：dataIn    输入数组
                     dataInLen 输入数组长度
* 输出参数：0表示解释成功，1表示解释出错
*******************************************************************/
int Alg_ShowSignData(uint8_t *dataIn,int dataInLen,SIGN_Out_Para *SIGN_Out)
{
		int i,j,index=0,index_type=0,length=0,fb=0;
		//通用的数据结构，数组和变量定义
		int type,Version,countAttributes,countInputs,countOutputs;
		//nep5 局部变量
		DATA_NODE nep5_data[20];
		int nep5_index,extra_len,nep5_temp_len;
		uint8_t nep5assetid[20];
	
		uint8_t Input[32];
		uint8_t buff_money[8];
		uint8_t address_data[21] = {0x17};
		uint8_t result_address[25];
		SIGN_Out_Data sign_data;
		memset(&sign_data,0,sizeof(sign_data));
		
		//交易类型
		type = dataIn[0];
		SIGN_Out->type = type;
		//Version
		Version = dataIn[1];
		SIGN_Out->version = Version;

		//不同交易类型的数据结构不一样，额外数据需要处理
		switch (type)
		{
						case 0x00://MinerTransaction
						{
										if(Version == 0)
										{
														sign_data.Nonce = (dataIn[2]/16)*pow(16,7) + (dataIn[2]%16)*pow(16,6) + (dataIn[3]/16)*pow(16,5) + (dataIn[3]%16)*pow(16,4)
																						+(dataIn[4]/16)*pow(16,3) + (dataIn[4]%16)*pow(16,2) + (dataIn[5]/16)*pow(16,1) + (dataIn[5]%16)*pow(16,0);
														index_type = 4;
														break;
										}
										else
										{
														return 1;
										}
						}
						case 0x01://IssueTransaction
						{
										if(Version > 1)
										{
														return 1;
										}
										break;
						}
						case 0x02://ClaimTransaction
						{
										if(Version == 0)
										{
														for(i=0;i<34;i++)
														{
																		sign_data.Claims[i] = dataIn[2+i];
														}
														if(sizeof(sign_data.Claims) == 0)
																		return 1;
														index_type = 34;
														break;
										}
										else
										{
														return 1;
										}
						}
						case 0x20://EnrollmentTransaction
						{
										if(Version == 0)
										{
														for(i=0;i<64;i++)
														{
																		sign_data.PublicKey[i] = dataIn[2+i];
														}
														index_type = 64;
														break;
										}
										else
										{
														return 1;
										}
						}
						case 0x40://RegisterTransaction
						{
										if(Version == 0)
										{
														sign_data.AssetType = dataIn[2];
														index_type += 1;
														//Name:
														fb = dataIn[2+index_type];
														length = ReadByteLength(dataIn,3+index_type,1024,fb);
														if(length == 0)	return 1;
														index_type += 1 + ReadByteLengthIndex(fb);
														index_type += length;
														//Amount
														sign_data.Amount = (dataIn[index_type+2]/16)*pow(16,15) + (dataIn[index_type+2]%16)*pow(16,14) + (dataIn[index_type+3]/16)*pow(16,13) + (dataIn[index_type+3]%16)*pow(16,12)
																						+(dataIn[index_type+4]/16)*pow(16,11) + (dataIn[index_type+4]%16)*pow(16,10) + (dataIn[index_type+5]/16)*pow(16,9) + (dataIn[index_type+5]%16)*pow(16,8)
																						+(dataIn[index_type+6]/16)*pow(16,7) + (dataIn[index_type+6]%16)*pow(16,6) + (dataIn[index_type+7]/16)*pow(16,5) + (dataIn[index_type+7]%16)*pow(16,4)
																						+(dataIn[index_type+8]/16)*pow(16,3) + (dataIn[index_type+8]%16)*pow(16,2) + (dataIn[index_type+9]/16)*pow(16,1) + (dataIn[index_type+9]%16)*pow(16,0);
														index_type += 8;
														//Precision
														sign_data.Precision = dataIn[index_type+2];
														index_type += 1;
														//Owner
														for(i=0;i<33;i++)
														{
																		sign_data.Owner[i] = dataIn[i+index_type+2];
														}
														index_type += 33;
														//Admin
														for(i=0;i<20;i++)
														{
																		sign_data.Admin[i] = dataIn[i+index_type+2];
														}
														index_type += 20;
														break;
										}
										else
										{
														return 1;
										}
						}
						case 0x80://ContractTransaction  最常见的合约交易	 没有自己的独特处理
						{
										if(Version != 0)
										{
														return 1;
										}
										break;
						}
						case 0xd0://PublishTransaction
						{
										if(Version > 1)
										{
														return 1;
										}
										for(i=0;i<3;i++)
										{
														sign_data.Code[i] = dataIn[2+i];
										}
										if(Version == 1)
										{
														sign_data.NeedStorage = dataIn[5];
										}
										else
										{
														sign_data.NeedStorage = 0;
										}
										index_type += 4;
										//NameP:
										fb = dataIn[2+index_type];
										length = ReadByteLength(dataIn,3+index_type,252,fb);
										if(length == 0)	return 1;
										index_type += 1 + ReadByteLengthIndex(fb);
										index_type += length;
										//CodeVersion
										fb = dataIn[2+index_type];
										length = ReadByteLength(dataIn,3+index_type,252,fb);
										if(length == 0)	return 1;
										index_type += 1 + ReadByteLengthIndex(fb);
										index_type += length;
										//Author
										fb = dataIn[2+index_type];
										length = ReadByteLength(dataIn,3+index_type,252,fb);
										if(length == 0)	return 1;
										index_type += 1 + ReadByteLengthIndex(fb);
										index_type += length;
										//Email
										fb = dataIn[2+index_type];
										length = ReadByteLength(dataIn,3+index_type,252,fb);
										if(length == 0)	return 1;
										index_type += 1 + ReadByteLengthIndex(fb);
										index_type += length;
										//Description
										fb = dataIn[2+index_type];
										length = ReadByteLength(dataIn,3+index_type,65536,fb);
										if(length == 0)	return 1;
										index_type += 1 + ReadByteLengthIndex(fb);
										index_type += length;
										break;
						}
						case 0xd1://InvocationTransaction
						{
								nep5_index = 0;
								index_type += 2;
								extra_len = dataIn[index_type];
								index_type += 1;
								while(extra_len>0)
								{
										nep5_temp_len = dataIn[index_type];
										if((nep5_temp_len>PUSH0)&&(nep5_temp_len<PUSHBYTES75))
										{
												index_type += 1;
												nep5_data[nep5_index].len = nep5_temp_len;
												nep5_data[nep5_index].data = dataIn + index_type;
												index_type += nep5_temp_len;
												nep5_index += 1;
												extra_len -=  nep5_temp_len + 1;
										}
										else if(nep5_temp_len == APPCALL)
										{
												index_type += 1;
												nep5_data[nep5_index].len = 20;
												nep5_data[nep5_index].data = dataIn + index_type;		
												index_type += 20;
												nep5_index += 1;
												extra_len -=  20 + 1;
										}
										else
										{
												index_type += 1;
												nep5_data[nep5_index].len = 1;
												nep5_data[nep5_index].data = dataIn + index_type;									
												nep5_index += 1;
												extra_len -= 1;
										}		
								}
								//money
								SIGN_Out->money[1] = Nep5CountMoney(nep5_data[nep5_index-7].data,nep5_data[nep5_index-7].len);
								//address
								for(j=0;j<20;j++)
								{
										address_data[1+j] = nep5_data[nep5_index-6].data[j];
								}
								Base58_25Bytes(address_data,21,result_address);
								memmove(SIGN_Out->address[1],result_address,25);
								for(j=0;j<20;j++)
								{
										address_data[1+j] = nep5_data[nep5_index-5].data[j];
								}
								Base58_25Bytes(address_data,21,result_address);
								memmove(SIGN_Out->address[0],result_address,25);
								//assetid
								memmove(nep5assetid,nep5_data[nep5_index-1].data,20);
								SIGN_Out->coin = Nep5GetAssetID(nep5assetid);
								if(SIGN_Out->coin == 0xff)
										return 1;
								index_type -= 2;
								return 0;
						}
						default:
										printf("Type Error!!!");
										return 1;
		}

		//countAttributes
		countAttributes = dataIn[2+index_type];
		SIGN_Out->countAttributes = countAttributes;

		//countInputs
		countInputs = dataIn[3+index_type];
		SIGN_Out->countInputs = countInputs;
		index = 4+index_type;
		for(i=0;i<countInputs;i++)
		{
						for(j=0;j<32;j++)
								Input[31-j]=dataIn[index+j+34*i];
						memset(Input,0,32);//清空数组
		}
		index += 34*countInputs;

		//countOutputs
		countOutputs = dataIn[index];
		SIGN_Out->countOutputs = countOutputs;
		index += 1;

		for(i=0;i<countOutputs;i++)
		{
				//记录assetID
				for(j=0;j<32;j++)
						SIGN_Out->assetid[i][31-j] = dataIn[index+j+60*i];
				//判断assetID
				if(type == 0x80)
						SIGN_Out->coin = GetAssetID(SIGN_Out->assetid[i]);
				//计算money
				for(j=0;j<8;j++)
				{
						buff_money[7-j] = dataIn[index+32+60*i+j];
				}
				SIGN_Out->money[i] = CountMoney(buff_money);
				//计算地址
				for(j=0;j<20;j++)
				{
						address_data[1+j] = dataIn[index+40+60*i+j];
				}
				Base58_25Bytes(address_data,21,result_address);
				memmove(SIGN_Out->address[i],result_address,25);	
		}
		index += 60*countOutputs;

		if(index == dataInLen)
		{
						return 0;
		}
		else
		{
						return 1;
		}
}


