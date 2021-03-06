#ifndef MAIN_DEFINE_H
#define MAIN_DEFINE_H

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//#define Chinese
#define English

#define HID_QUEUE_DEPTH					50

#define FLASH_ADDRESS_SIGN_DATA	0x0801F000 //签名结果地址
#define FLASH_ADDRESS_FLAG_JUMP	0x0801FC00 //跳转标识
#define	FLASH_ADDRESS_SCENE		  0x0801FE00 //现场数据地址
#define FLASH_ADDRESS_PACK		  0x08010000 //扇区4
#define FLASH_DATA_SECTOR				FLASH_SECTOR_4

#define FLASH_ADDRESS_NEODUN	  0x08020000 //扇区5+扇区6
#define FLASH_ADDRESS_APP1		  0x08060000 //扇区7
#define FLASH_SECTOR_APP1				FLASH_SECTOR_7
#define FLASH_ADDRESS_APP2		  0x08080000 //扇区8
#define FLASH_SECTOR_APP2				FLASH_SECTOR_8
#define FLASH_ADDRESS_APP3		  0x080A0000 //扇区9
#define FLASH_SECTOR_APP3				FLASH_SECTOR_9
#define FLASH_ADDRESS_APP4		  0x080C0000 //扇区10
#define FLASH_SECTOR_APP4				FLASH_SECTOR_10
#define FLASH_ADDRESS_APP5		  0x080E0000 //扇区11
#define FLASH_SECTOR_APP5				FLASH_SECTOR_11

#define COIN_TYPE_OFFSET				0x1FFFC
#define COIN_VERSION_OFFSET			0x1FFFE

//程序版本号，高4位主版本号，低4位次版本号
#define	VERSION_NEODUN				0x0100
#define VERSION_NEO						0x0100
#define	VERSION_NEODUN_STR		"V1.0"
#define VERSION_NEO_STR				"V1.0"
//宏开关
//#define printf_debug
#define HID_Delay
//宏定义
#define ADDR_XiaoYi 					0x0101
#define ADDR_SIZE   					40
#define SLOT_FLAG							14
#define DISPLAY_ERROR_TIME		2000
#define INPUT_TIME_DIV				1000
#define SYSTEM_BASE_TIME			1
#define MOTOR_TIME  					80
#define KEY_VALID_TIME				30

#define HID_MAX_DATA_LEN			64*1024
#define DATA_PACK_SIZE				50
#define HID_SEND_DELAY				15

//错误码
#define ERR_DATA_HASH					0x0100
#define ERR_NO_SPACE_INSTALL	0x0101
#define ERR_COIN_RUNNING			0x0102
#define ERR_COIN_TYPE					0x0103
#define ERR_VERIFY_FAIED			0x0104
#define ERR_KEY_MAX_COUNT			0x0201
#define	ERR_EXIST_KEY					0x0202
#define	ERR_SAME_ADD_NAME			0x0203
#define ERR_UNKNOW_COIN				0x0204
#define ERR_KEY_FORMAT				0x0205
#define ERR_UNKONW_ADD				0x0206
#define ERR_UNKNOW_KEY				0x0301
#define ERR_MULTI_SIGN				0x0302
#define ERR_DATA_PACK					0x0303
#define ERR_USER_REFUSE				0x0401
#define ERR_TIME_OUT					0x0501
#define ERR_PLUGS_DATALEN			0x0601
#define ERR_PLUGS_PACKERR			0x0602
#define ERR_PLUGS_PRIKEY			0x0603
#define ERR_PLUGS_SIGN				0x0604

//币种
#define COIN_NEO							"NEO"
#define COIN_BTC							"BTC"
#define COIN_ETH							"ETH"

//返回值
enum
{
		NEO_SUCCESS			= 0,
		NEO_USER_REFUSE = 1,
		NEO_TIME_OUT		= 2,
};

//按键标识
typedef union
{
		struct
		{
				volatile	uint8_t key_state:1;	//防误按的标志位
				volatile	uint8_t left:1;				//左按键标识
				volatile	uint8_t middle:1;			//中间按键标识
				volatile	uint8_t right:1;			//右边按键标识
		}flag;
		uint8_t data;
}KEY_FLAG;

//设置标识
typedef union
{
		struct
		{
				uint8_t usb_offline:1;							//0表示连上USB，1表示没连上USB			
				uint8_t usb_state_pre:1;						//USB前时刻的状态
		}flag;
		uint8_t data;
}SET_FLAG;

//密码标识
typedef union
{
		struct
		{
				uint8_t poweron:1;				//开机密码验证
				uint8_t sign_data:1;			//交易签名验证标志位
				uint8_t add_address:1;		//增加地址验证标志位
				uint8_t del_address:1;		//删除地址验证标志位

		}flag;
		uint8_t data;
}PASSPORT_FLAG;

//时间控制
typedef struct
{
		uint8_t ready;								//是否需要计时
		uint8_t time;									//计时时间
		uint8_t timeout;							//是否超时
}TIME_CONTROL;

//系统标识
typedef struct
{
		uint8_t	new_wallet; 			//1表示新钱包，0表示旧钱包
		uint8_t	update;						//1表示需要升级，0表示不需要升级
		uint8_t	language;					//1表示英文，0表示中文
		uint8_t count;						//地址数量
		uint8_t errornum;					//密码错误次数
		uint8_t	sn[12];						//单片机唯一SN码
		uint8_t pin[8];
}SYSTEM_NEODUN;

//HID数据解析结构体
typedef struct
{
		uint32_t	dataLen;			
		uint16_t 	packIndex;
		uint16_t  packCount;
		uint16_t 	notifySerial;		
		uint16_t	reqSerial;
		uint8_t	  Pack_ID;
		uint8_t 	hashRecord[32];	
}DATA_HID_RECORD;

//密码设置
typedef struct
{
		uint8_t state;
		uint8_t	MingWen[32];
		uint8_t	NewMingWen[32];
}PASSPORT_SET_INFO;

//为地址显示开辟内存
typedef struct
{
		uint8_t	hide;							//隐藏属性	
		uint8_t	len_name;					//地址名称长度
		char 		name[7];					//地址名称
		uint8_t	content[25];			//Base58前的地址数据
		uint8_t	address[40];			//Base58后的字符地址数据
}ADDRESS;

//系统插件信息,缺省值为0xFFFF,
typedef struct
{
		uint16_t count;						
		uint16_t coin1;						//类型
		uint16_t version1;				//版本
		uint16_t coin2;
		uint16_t version2;
		uint16_t coin3;
		uint16_t version3;
		uint16_t coin4;
		uint16_t version4;
		uint16_t coin5;
		uint16_t version5;
}COIN;

typedef struct
{
		uint8_t randoma[32];
		uint8_t pubkeyA[65];
		uint8_t hashA[32];
		uint8_t pubkeyB[64];		
		uint8_t keyM[32];
}SECURE_PIPE;

typedef struct
{
	uint8_t data[64];
	uint8_t len;
}HID_RECV_DATA;

enum TimerFunction
{
		OLED_INPUT_TIME = 0,
		KEY_TIME 				= 1,
};

//HID数据
extern volatile uint32_t hid_index_read;
extern volatile uint32_t hid_index_write;
extern HID_RECV_DATA hid_recv_data[HID_QUEUE_DEPTH];

extern volatile 	uint32_t 	system_base_time;
extern uint8_t					SysFlagType;
extern KEY_FLAG 				Key_Flag;
extern SET_FLAG 				Set_Flag;
extern SYSTEM_NEODUN 		Neo_System;
extern PASSPORT_FLAG 		Passport_Flag;
extern DATA_HID_RECORD	HidData;
extern ADDRESS					showaddress[5];
extern COIN							coinrecord;
extern SECURE_PIPE			secure_pipe;
extern volatile 	uint32_t 	moter_delay;
extern volatile 	uint8_t 	task_1s_flag;

//声明ASCII库
extern uint8_t ASC8X16[];
extern uint8_t HZ12X12_S[];

//声明图片
extern uint8_t gImage_emptypin[72];
extern uint8_t gImage_fullpin[72];
extern uint8_t gImage_Set[512];
extern uint8_t gImage_triangle_up[128];
extern uint8_t gImage_triangle_down[128];
extern uint8_t gImage_Address[512];
extern uint8_t gImage_Address_hide[512];
extern uint8_t gImage_arrow_left[128];
extern uint8_t gImage_arrow_right[128];
extern uint8_t gImage_arrow_fill_left[128];
extern uint8_t gImage_arrow_fill_right[128];
extern uint8_t gImage_Usb[288];
extern uint8_t gImage_delete[64];

//ASCII图片声明
extern unsigned char aBitmapDot[16];
extern unsigned char ABitmapDot[16];
extern unsigned char AboutBitmapDot[80];
extern unsigned char AddressBitmapDot[112];
extern unsigned char addressBitmapDot[112];
extern unsigned char againBitmapDot[80];
extern unsigned char AllBitmapDot[32];
extern unsigned char allBitmapDot[32];
extern unsigned char AllowBitmapDot[80];
extern unsigned char andBitmapDot[48];
extern unsigned char anyBitmapDot[48];
extern unsigned char APPBitmapDot[48];
extern unsigned char appsBitmapDot[64];
extern unsigned char AreBitmapDot[48];
extern unsigned char attemptsBitmapDot[128];
extern unsigned char availableBitmapDot[112];
extern unsigned char BackBitmapDot[64];
extern unsigned char beBitmapDot[32];
extern unsigned char beenBitmapDot[64];
extern unsigned char belowBitmapDot[80];
extern unsigned char CancelBitmapDot[96];
extern unsigned char cancelBitmapDot[96];
extern unsigned char changepinBitmapDot[144];
extern unsigned char change_pinBitmapDot[128];
extern unsigned char checkBitmapDot[80];
extern unsigned char codeBitmapDot[64];
extern unsigned char confirmBitmapDot[96];
extern unsigned char ConfirmBitmapDot[96];
extern unsigned char containBitmapDot[96];
extern unsigned char dataBitmapDot[64];
extern unsigned char didBitmapDot[48];
extern unsigned char DoBitmapDot[32];
extern unsigned char doesBitmapDot[64];
extern unsigned char eraseBitmapDot[80];
extern unsigned char erasedBitmapDot[96];
extern unsigned char ErasingBitmapDot[96];
extern unsigned char ERRORBitmapDot[80];
extern unsigned char firmwareBitmapDot[112];
extern unsigned char FirmwareBitmapDot[112];
extern unsigned char forBitmapDot[48];
extern unsigned char FromBitmapDot[64];
extern unsigned char fromBitmapDot[64];
extern unsigned char hasBitmapDot[48];
extern unsigned char haveBitmapDot[64];
extern unsigned char HelpBitmapDot[64];
extern unsigned char helpBitmapDot[64];
extern unsigned char HideBitmapDot[64];
extern unsigned char hideBitmapDot[64];
extern unsigned char importBitmapDot[80];
extern unsigned char ImportingBitmapDot[128];
extern unsigned char incorrect_BitmapDot[128];
extern unsigned char IncorrectBitmapDot[128];
extern unsigned char inBitmapDot[32];
extern unsigned char irreversibleBitmapDot[144];
extern unsigned char IsolateBitmapDot[96];
extern unsigned char isBitmapDot[32];
extern unsigned char ItBitmapDot[32];
extern unsigned char keyBitmapDot[48];
extern unsigned char keysBitmapDot[64];
extern unsigned char leftBitmapDot[48];
extern unsigned char ManagerBitmapDot[112];
extern unsigned char manyBitmapDot[80];
extern unsigned char matchBitmapDot[80];
extern unsigned char NEODUNBitmapDot[96];
extern unsigned char newBitmapDot[48];
extern unsigned char NoNameBitmapDot[96];
extern unsigned char NoneBitmapDot[64];
extern unsigned char notBitmapDot[48];
extern unsigned char officialBitmapDot[96];
extern unsigned char OKBitmapDot[32];
extern unsigned char onlyBitmapDot[64];
extern unsigned char ourBitmapDot[48];
extern unsigned char PINBitmapDot[48];
extern unsigned char PINsBitmapDot[48];
extern unsigned char PleaseBitmapDot[96];
extern unsigned char pleaseBitmapDot[96];
extern unsigned char proceedBitmapDot[112];
extern unsigned char reimportBitmapDot[112];
extern unsigned char requiredBitmapDot[112];
extern unsigned char ResetBitmapDot[80];
extern unsigned char resetBitmapDot[80];
extern unsigned char ResetallBitmapDot[128];
extern unsigned char SecurityBitmapDot[112];
extern unsigned char seenBitmapDot[64];
extern unsigned char SendBitmapDot[64];
extern unsigned char set_BitmapDot[48];
extern unsigned char SetBitmapDot[48];
extern unsigned char SettingsBitmapDot[112];
extern unsigned char signedBitmapDot[96];
extern unsigned char successfulBitmapDot[144];
extern unsigned char sureBitmapDot[64];
extern unsigned char theBitmapDot[48];
extern unsigned char ThisBitmapDot[64];
extern unsigned char toBitmapDot[32];
extern unsigned char TooBitmapDot[48];
extern unsigned char TransactionBitmapDot[160];
extern unsigned char tryBitmapDot[48];
extern unsigned char unhideBitmapDot[96];
extern unsigned char UnhideBitmapDot[96];
extern unsigned char updateBitmapDot[96];
extern unsigned char usingBitmapDot[80];
extern unsigned char VersionBitmapDot[96];
extern unsigned char VisitBitmapDot[64];
extern unsigned char walletBitmapDot[80];
extern unsigned char WalletBitmapDot[80];
extern unsigned char wantBitmapDot[64];
extern unsigned char websiteBitmapDot[112];
extern unsigned char welcomeBitmapDot[128];
extern unsigned char willBitmapDot[48];
extern unsigned char wwwBitmapDot[224];
extern unsigned char YouBitmapDot[48];
extern unsigned char youBitmapDot[48];
extern unsigned char YourBitmapDot[64];

void Sys_Data_Init(void);

#endif

