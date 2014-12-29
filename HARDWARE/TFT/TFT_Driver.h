#ifndef __TFT_DRIVER_H
#define __TFT_DRIVER_H

//#define H_VIEW
//#define USB_HARDWARE_SPI

#ifdef H_VIEW
				#define X_MAX_PIXEL	        320
				#define Y_MAX_PIXEL	        240
#else
				#define X_MAX_PIXEL	        240
				#define Y_MAX_PIXEL	        320 
#endif

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111

#define TFT_CTRL   	  	GPIOB				//����TFT���ݶ˿�ΪPB��
#define TFT_CS        	GPIO_Pin_11 //MCU_PB11			��Ӧ��Һ����(����ģ��)TFT --CS
#define TFT_RST     	  GPIO_Pin_12	//MCU_PB12			��Ӧ��Һ����(����ģ��)TFT --RST
#define TFT_RS         	GPIO_Pin_10	//MCU_PB10			��Ӧ��Һ����(����ģ��)TFT --RS/DC
#define TFT_SDA        	GPIO_Pin_15	//MCU_PB15 MOSI	��Ӧ��Һ����(����ģ��)TFT --SDA 
#define TFT_SCL        	GPIO_Pin_13	//MCU_PB13			��Ӧ��Һ����(����ģ��)TFT --SCL
#define TFT_LED        	GPIO_Pin_9  //MCU_PB9   		��Ӧ��Һ����(����ģ��)TFT --PIN_LED��������
#define TFT_SDO        	GPIO_Pin_14	//MCU_PB14 MISO	��Ӧ��Һ����(����ģ��)TFT --SDO 

//Һ�����ƿ���1�������궨��
#define	TFT_CS_SET  	TFT_CTRL->BSRR=TFT_CS    
#define	TFT_RS_SET  	TFT_CTRL->BSRR=TFT_RS    
#define	TFT_SDA_SET  	TFT_CTRL->BSRR=TFT_SDA    
#define	TFT_SCL_SET  	TFT_CTRL->BSRR=TFT_SCL    
#define	TFT_RST_SET  	TFT_CTRL->BSRR=TFT_RST    
#define	TFT_LED_SET  	TFT_CTRL->BSRR=TFT_LED    

//Һ�����ƿ���0�������궨��
#define	TFT_CS_CLR  	TFT_CTRL->BRR=TFT_CS    
#define	TFT_RS_CLR  	TFT_CTRL->BRR=TFT_RS    
#define	TFT_SDA_CLR  	TFT_CTRL->BRR=TFT_SDA    
#define	TFT_SCL_CLR  	TFT_CTRL->BRR=TFT_SCL    
#define	TFT_RST_CLR  	TFT_CTRL->BRR=TFT_RST    
#define	TFT_LED_CLR  	TFT_CTRL->BRR=TFT_LED  

void TFT_Init(void);
void TFT_Clear(u16 Color);
void TFT_SetXY(u16 x,u16 y);
void TFT_DrawPoint(u16 x,u16 y,u16 Data);
u16 TFT_ReadPoint(u16 x,u16 y);

void TFT_Circle(u16 X,u16 Y,u16 R,u16 fc); 
void TFT_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);  
void TFT_box(u16 x, u16 y, u16 w, u16 h,u16 bc);
void TFT_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
void TFT_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void TFT_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void TFT_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num) ;

#endif
