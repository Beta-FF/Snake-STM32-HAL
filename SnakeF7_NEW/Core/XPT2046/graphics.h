#define PIC_WIDTH 12 // 12*8=96
#define PIC_HEIGHT 64

const unsigned char Image_snake_logo[64*12] = {
0X00,0X18,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X0E,
0X00,0X3C,0X00,0X00,0X00,0X08,0X06,0X00,0X03,0XC0,0X01,0XF3,
0X00,0XFC,0X00,0X01,0XE0,0X38,0X0E,0X01,0X0F,0XC0,0X1F,0X03,
0X01,0XFC,0X07,0X03,0XE0,0XFC,0X3E,0X03,0X9F,0XE1,0XF0,0X03,
0X03,0XFE,0X3F,0X03,0XE1,0XFC,0X7E,0X07,0XDF,0XFF,0X00,0X03,
0X07,0XFE,0X3F,0X03,0XE1,0XFC,0X7E,0X07,0XEF,0XF0,0X00,0X1F,
0X0F,0XFE,0X3F,0X87,0XE3,0XFC,0X3F,0X0F,0XDE,0X40,0X06,0X3E,
0X1F,0XFC,0X3F,0X87,0XC3,0XFC,0X3F,0X1F,0XBC,0X40,0X3E,0X30,
0X1F,0XE0,0X3F,0XC7,0XC7,0XFE,0X07,0X3F,0X70,0X60,0X3E,0X30,
0X3F,0XC0,0X7F,0XC7,0XC7,0XDE,0X17,0X7E,0XF0,0X3E,0X32,0X30,
0X3F,0X00,0X7F,0XC7,0XC7,0X9E,0X77,0XFE,0XF0,0X1E,0X32,0X30,
0X7E,0X00,0X7F,0XE7,0XCF,0X9F,0XFB,0XFC,0XF1,0X02,0X32,0X30,
0X7C,0X00,0X3D,0XE7,0XCF,0X8F,0XFB,0XF8,0XF7,0X82,0X32,0X30,
0XF8,0X1F,0X9D,0XF7,0XDF,0X0F,0XFB,0XF0,0X7F,0X82,0X32,0X30,
0XF9,0XFF,0XDC,0XF7,0XDF,0X1F,0XE3,0XF0,0X7E,0X02,0X32,0X30,
0XFF,0XFF,0XDC,0XFF,0XDF,0X7F,0X8F,0XF8,0X7C,0X02,0X32,0X3E,
0XFF,0XFF,0XDC,0X7F,0XDF,0XFF,0X8F,0XFC,0X3C,0XE2,0X32,0X33,
0X7E,0X0F,0XDC,0X3F,0XBF,0XFF,0XCF,0XFE,0X3D,0XE2,0X3C,0X03,
0X00,0X1F,0XDC,0X3F,0XBF,0XC7,0XCF,0XBF,0X3F,0XE2,0X30,0X03,
0X00,0X3F,0XBC,0X1F,0XBE,0X07,0XCF,0X9F,0X1F,0XCE,0X00,0X1F,
0X00,0X7F,0XBC,0X1C,0X3E,0X02,0X07,0X8E,0X1F,0X30,0X00,0XFE,
0X01,0XFF,0X7C,0X00,0XFE,0X00,0XF7,0X84,0X1E,0X20,0X07,0XF0,
0X07,0XFE,0XF0,0X00,0XFC,0X03,0X90,0X80,0X08,0X20,0X3F,0X80,
0X3F,0XFC,0XC0,0X00,0X10,0X06,0X1E,0X00,0X00,0X31,0XFC,0X00,
0X3F,0XF8,0X00,0X00,0X07,0XBC,0XE3,0XF0,0X00,0X1F,0XE0,0X00,
0X3F,0XE0,0X00,0X00,0X0C,0X61,0X80,0X18,0X00,0X0F,0X00,0X00,
0X3F,0X80,0X00,0X00,0X0B,0X13,0X80,0X08,0X00,0X04,0X00,0X00,
0X1E,0X00,0X00,0X00,0X0D,0X85,0XA0,0X0C,0X00,0X00,0X00,0X00,
0X18,0X00,0X00,0XFF,0XF5,0XA8,0X47,0X84,0X00,0X00,0X00,0X00,
0X00,0X00,0X07,0XAA,0XAE,0X33,0X0D,0X06,0X00,0X00,0X00,0X00,
0X00,0X00,0X3D,0X55,0X78,0X00,0X01,0X82,0X00,0X00,0X00,0X00,
0X00,0X01,0XEA,0XAB,0XC0,0X00,0X00,0X86,0X00,0X00,0X00,0X00,
0X00,0X0F,0X55,0X57,0XFF,0XE0,0X03,0XFF,0X80,0X00,0X00,0X00,
0X00,0X1A,0XAA,0XBF,0X00,0X11,0XFE,0X2A,0XF0,0X00,0X00,0X00,
0X00,0X35,0X57,0XE1,0X80,0X07,0X20,0X35,0X58,0X00,0X00,0X00,
0X00,0X6A,0XBC,0X00,0XE0,0X1A,0X60,0X6A,0XAC,0X00,0X00,0X00,
0X00,0X5F,0XE7,0X00,0X5F,0XF2,0XC0,0XFD,0X7F,0XF0,0X00,0X00,
0X00,0X75,0XED,0X00,0X4B,0X0B,0X81,0X83,0XC0,0X1C,0X00,0X00,
0X00,0XEE,0XBB,0X00,0X2B,0X07,0X03,0X0E,0X00,0X07,0X0E,0X00,
0X00,0XD1,0XD6,0X00,0X1B,0X06,0X06,0X38,0X00,0X01,0X31,0X00,
0X03,0XA8,0XEB,0X00,0X07,0X0C,0X0C,0X60,0X1F,0XE0,0XE0,0X80,
0X0F,0X55,0XFF,0XC0,0X0D,0X18,0X18,0XC0,0XFD,0X70,0XD8,0X40,
0X1A,0XAB,0XEB,0XFF,0XD1,0X30,0X31,0X83,0X9A,0XD0,0X4C,0X20,
0X35,0XF5,0X57,0X55,0X42,0X60,0X63,0X06,0XED,0X58,0X7E,0X10,
0X2B,0XBA,0XAA,0XAA,0XC0,0XC0,0XC6,0X0D,0X8A,0XE8,0X4F,0X10,
0X37,0XD5,0X55,0X55,0XC1,0X81,0X84,0X1A,0X3D,0X7D,0X61,0X0C,
0X2A,0XAA,0XAA,0XAB,0X83,0X03,0X0C,0X36,0XFA,0XFA,0X7D,0X8A,
0X35,0XD5,0XFF,0X7E,0X86,0X06,0X08,0X64,0X7F,0XF5,0XF9,0X8A,
0X2A,0XFF,0XC9,0XC4,0X8C,0X0C,0X08,0X46,0X87,0XFF,0X83,0X84,
0X1D,0X7F,0XC9,0X05,0X18,0X19,0XE8,0X63,0X40,0X00,0X15,0XC4,
0X0E,0XBF,0XEA,0XF6,0X10,0X33,0XE8,0X32,0XA0,0X00,0X6B,0XC6,
0X01,0XD7,0XE4,0X10,0XB0,0X67,0XEC,0X19,0X7E,0X01,0XF7,0XC2,
0X00,0XEB,0XF8,0XDF,0X20,0XCF,0XE6,0X0C,0XA3,0XFF,0X2B,0XE2,
0X02,0X35,0XF5,0X5F,0X60,0X9F,0XF3,0X06,0X40,0X00,0X57,0XE2,
0X1F,0X9A,0XC6,0X4F,0X41,0X9F,0XF9,0X83,0X20,0X00,0XAB,0XE2,
0X7F,0XCD,0X6F,0XEF,0X41,0X8F,0XFC,0XC9,0X90,0X00,0X37,0XE2,
0XFF,0XE6,0XBE,0XAF,0X41,0XE3,0XFE,0X68,0X8F,0X03,0XEC,0XE2,
0XFF,0XF3,0X5F,0X6F,0X41,0X38,0X1E,0X30,0XD1,0XFE,0X56,0X62,
0XFF,0XF9,0XAF,0XCF,0X60,0X0F,0XC0,0XE0,0X48,0X01,0X2D,0X24,
0XFF,0XFC,0XEF,0X9F,0X30,0X00,0X7F,0X80,0X50,0X00,0X58,0XF9,
0X7F,0XFE,0X06,0X3F,0X98,0X00,0X00,0X00,0XDF,0X03,0XE0,0X03,
0X1F,0XFF,0XF7,0X3F,0XCF,0X00,0X00,0X01,0X81,0XFE,0X0F,0XFE,
0X03,0XFF,0XF7,0X9F,0XE1,0XF0,0X00,0X0F,0X3C,0X00,0XFF,0XF0,
0X00,0X3F,0XFA,0X5F,0XFC,0X1F,0XFF,0XF8,0X7F,0XFF,0XFF,0X00
};

const unsigned char Image_big_turtle[64] = {
0XFE,0X00,0X1E,0X00,0XFE,0X00,0X1E,0X00,0XFE,0X00,0X1E,0X00,0XFE,0X00,0X1E,0X00,
0XFE,0X01,0XFF,0XE0,0XFE,0X01,0XFF,0XE0,0XFE,0X01,0XFF,0XE0,0XFE,0X01,0XFF,0XE0,
0X01,0XFF,0XFF,0XFE,0X01,0XFF,0XFF,0XFE,0X01,0XFF,0XFF,0XFE,0X01,0XFF,0XFF,0XFE,
0X00,0X01,0XE1,0XE0,0X00,0X01,0XE1,0XE0,0X00,0X01,0XE1,0XE0,0X00,0X01,0XE1,0XE0,
};

const unsigned char Image_head_U[8] = { 0X00,0X00,0X3C,0X3C,0X3C,0X3C,0XCC,0XCC };
const unsigned char Image_head_L[8] = { 0X03,0X03,0X3C,0X3C,0X3F,0X3F,0X00,0X00 };
const unsigned char Image_head_R[8] = { 0XC0,0XC0,0X3C,0X3C,0XFC,0XFC,0X00,0X00 };
const unsigned char Image_head_D[8] = { 0X33,0X33,0X3C,0X3C,0X3C,0X3C,0X00,0X00 };

const unsigned char Image_body_U_D[8] = { 0X3C,0X3C,0X30,0X30,0X0C,0X0C,0X3C,0X3C };
const unsigned char Image_body_L_R[8] = { 0X00,0X00,0XCF,0XCF,0XF3,0XF3,0X00,0X00 };

const unsigned char Image_body_food_L_R[8] = { 0X3C,0X3C,0XCF,0XCF,0XF3,0XF3,0X3C,0X3C };
const unsigned char Image_body_food_U_D[8] = { 0X3C,0X3C,0XCF,0XCF,0XF3,0XF3,0X3C,0X3C,};

const unsigned char Image_body_DtoR[8] = { 0X00,0X00,0X0F,0X0F,0X33,0X33,0X3C,0X3C };
const unsigned char Image_body_DtoL[8] = { 0X00,0X00,0XF0,0XF0,0XCC,0XCC,0X3C,0X3C };
const unsigned char Image_body_UtoL[8] = { 0X3C,0X3C,0XCC,0XCC,0XF0,0XF0,0X00,0X00 };
const unsigned char Image_body_UtoR[8] = { 0X3C,0X3C,0X33,0X33,0X0F,0X0F,0X00,0X00 };

const unsigned char Image_tail_U[8] = { 0X3C,0X3C,0X3C,0X0C,0X0C,0X0C,0X0C,0X0C };
const unsigned char Image_tail_L[8] = { 0X00,0X00,0XC0,0XC0,0XFC,0XFC,0X00,0X00 };
const unsigned char Image_tail_R[8] = { 0X00,0X00,0X07,0X07,0XFF,0XFF,0X00,0X00 };
const unsigned char Image_tail_D[8] = { 0X30,0X30,0X30,0X30,0X30,0X3C,0X3C,0X3C };

const unsigned char Image_food[8] = { 0X00,0X18,0X18,0X66,0X66,0X18,0X18,0X00 };

const unsigned char Image_turtle[32] = {
0X00,0X00,0X00,0X00,0X00,0XE0,0X00,0XE0,
0XF3,0XF8,0XF7,0XF8,0XF7,0XFC,0XFF,0XFC,
0X1F,0XFC,0X07,0X38,0X07,0X38,0X07,0X38,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
};

const unsigned char Image_Block[32] = {
0X00,0X00,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X00,0X00,
0X00,0X00,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X7E,0X00,0X00,
};