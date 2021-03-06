
/////////////////////////////////////////////////////////////////////////
// 汉字字模表    // 晶奥科技                                                      
// 汉字库: 宋体12.dot 实际点阵 16*12  16列（字为12列右4列空） 12行  
//横向取模左高位,数据排列:从左到右从上到下          
/////////////////////////////////////////////////////////////////////////
unsigned char  HZ12X12_S[] =          // 数据表
{
//-- 没 -- 0
      0x40,0x80,0x27,0xC0,0x04,0x80,0x84,0xF0,
      0x48,0x00,0x27,0xC0,0x24,0x40,0xC2,0x80,
      0x41,0x00,0x42,0x80,0x44,0x70,0x58,0x20,
//-- 有 -- 1
      0x04,0x00,0x04,0x20,0xFF,0xF0,0x08,0x00,
      0x1F,0xC0,0x30,0x40,0x5F,0xC0,0x90,0x40,
      0x1F,0xC0,0x10,0x40,0x11,0x40,0x10,0x80,
//-- 安 -- 2
      0x04,0x00,0x7F,0xF0,0x40,0x10,0x84,0x20,
      0x04,0x00,0xFF,0xF0,0x08,0x80,0x10,0x80,
      0x19,0x00,0x07,0x00,0x18,0xC0,0xE0,0x20,
//-- 装 -- 3
      0x11,0x00,0x91,0x40,0x5F,0xF0,0x31,0x00,
      0xD7,0xE0,0x14,0x00,0xFF,0xF0,0x0A,0x40,
      0x32,0x80,0xD1,0x00,0x14,0xC0,0x18,0x30,
//-- 程 -- 4
      0x1B,0xE0,0xE2,0x20,0x22,0x20,0xFB,0xE0,
      0x20,0x00,0x67,0xF0,0x70,0x80,0xA8,0x80,
      0xA3,0xE0,0x20,0x80,0x20,0xA0,0x2F,0xF0,
//-- 序 -- 5
      0x02,0x20,0x7F,0xF0,0x40,0x00,0x5F,0xE0,
      0x42,0x80,0x41,0x00,0x5F,0xF0,0x41,0x20,
      0x41,0x00,0x41,0x00,0x45,0x00,0x82,0x00,
//-- 是 -- 6
      0x1F,0x80,0x10,0x80,0x1F,0x80,0x10,0x80,
      0x1F,0x80,0x00,0x20,0xFF,0xF0,0x02,0x00,
      0x13,0xE0,0x12,0x00,0x2E,0x00,0xC3,0xF0,
//-- 否 -- 7
      0x00,0x20,0xFF,0xF0,0x04,0x00,0x0D,0x80,
      0x14,0x60,0x64,0x30,0x84,0x40,0x3F,0xC0,
      0x20,0x40,0x20,0x40,0x3F,0xC0,0x20,0x40,
//-- 进 -- 8
      0x02,0x40,0x42,0x40,0x2F,0xF0,0x02,0x40,
      0x02,0x40,0xE2,0x40,0x2F,0xF0,0x22,0x40,
      0x24,0x40,0x28,0x40,0x50,0x00,0x8F,0xF0,
//-- 行 -- 9
      0x10,0x40,0x27,0xE0,0xD0,0x00,0x10,0x00,
      0x2F,0xF0,0x60,0x40,0xA0,0x40,0x20,0x40,
      0x20,0x40,0x20,0x40,0x22,0x40,0x21,0x80,
//-- 等 -- 10
      0x21,0x00,0x3D,0xF0,0x52,0x80,0x84,0x00,
      0x3F,0xE0,0x04,0x00,0xFF,0xF0,0x00,0x80,
      0x7F,0xE0,0x10,0x80,0x08,0x80,0x03,0x00,
//-- 待 -- 11
      0x11,0x00,0x21,0x40,0x47,0xE0,0x11,0x00,
      0x2F,0xF0,0x60,0x40,0xAF,0xF0,0x20,0x40,
      0x24,0x40,0x24,0x40,0x21,0x40,0x20,0x80,
//-- 更 -- 12
      0x00,0x20,0xFF,0xF0,0x04,0x00,0x3F,0xC0,
      0x24,0x40,0x3F,0xC0,0x24,0x40,0x3F,0xC0,
      0x14,0x00,0x0C,0x00,0x1B,0x00,0xE0,0xF0,
//-- 新 -- 13
      0x10,0x30,0xFD,0xC0,0x49,0x00,0x29,0x00,
      0xFF,0xF0,0x11,0x20,0x7D,0x20,0x11,0x20,
      0x59,0x20,0x55,0x20,0x92,0x20,0x34,0x20		
};
