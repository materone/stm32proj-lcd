#include "stm32f10x.h"
#include "TFT_Driver.h"
#include "delay.h"
#include "usart.h"

//#include "stm32f10x_conf.h"
#include "ff.h"
#include "SPI_MSD0_Driver.h"
#include <string.h>

GPIO_InitTypeDef GPIO_InitStructure;

void Delayms(__IO uint32_t nCount);
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

void Redraw_Mainmenu(void)
{
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,0,BLUE,GRAY0,"全动电子技术");
	TFT_DrawFont_GBK16(16,20,RED,GRAY0,"液晶测试程序");
	DisplayButtonDown(15,38,113,58); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,40,YELLOW,GRAY0,"颜色填充测试");
	DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,70,BLUE,GRAY0,"文字显示测试");
	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,100,RED,GRAY0,"图片显示测试");

	TFT_DrawFont_GBK16(16,120,BLUE,GRAY0,"S1:Move.    ");
	TFT_DrawFont_GBK16(16,140,RED,GRAY0, "S2:Sellect  ");
	//delay_ms(1000);
	//delay_ms(1000);

	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[5]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[4]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[3]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[2]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[1]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[0]);	
}

void Num_Test(void)
{
	u8 i=0;
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
	delay_ms(1000);
	TFT_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
	TFT_DrawFont_Num32((i%3)*40,32*(i/3)+30,RED,GRAY0,Num[i+1]);
	delay_ms(100);
	}
	delay_ms(1000);
	
}
//文字显示测试全动电子技术商城因为专注所以专业
void Font_Test(void)
{
	u8 x_offset;
#ifdef H_VIEW  //如果定义了横屏显示
	x_offset=40;
#else
	x_offset=0;
#endif
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,10,BLUE,GRAY0,  "   文字显示测试   ");

	delay_ms(1000);
	TFT_Clear(WHITE);
	TFT_DrawFont_GBK16(x_offset,10,RED,WHITE,  "     全动电子技术有限公司      ");
	TFT_DrawFont_GBK16(x_offset,30,RED,WHITE,  "         QDtech .,LTD         ");
	TFT_DrawFont_GBK24(x_offset,50,BLUE,WHITE, "           欢迎您            ");
	TFT_DrawFont_GBK16(x_offset,100,GREEN,WHITE,   "     全程技术支持     ");	
	TFT_DrawFont_GBK16(x_offset,120,RED,YELLOW,   "http://qdtech.taobao.com");
	TFT_DrawFont_GBK16(x_offset,140,RED,YELLOW,   "E-Mail:QDtech2008@gmail.com");
	TFT_DrawFont_GBK16(x_offset,160,RED,YELLOW,   "技术交流群:324828016");	
	TFT_DrawFont_GBK16(x_offset,180,BLUE,WHITE,   "Tel:15989313508 ");
	delay_ms(3000);	
	

}

void Color_Test(void)
{
//	u8 i=2;
	TFT_Clear(GRAY0);
	
	TFT_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
//	delay_ms(1000);

	//while(i--)
	//{
	  TFT_Clear(WHITE);
	  TFT_Clear(BLACK);
	  TFT_Clear(RED);
  	TFT_Clear(GREEN);
  	TFT_Clear(BLUE);
	//}		
}

//u16 ID=0;
int main(void)
{
  //uint16_t a;
  /* System Clocks Configuration **********************************************/
  SystemInit();
  delay_init(12);//延时初始化 
	uart_init(9600);
	printf("Test Begin\r\n");
  while(1) 
  {
		TFT_Init();			
		TFT_Clear(WHITE);
		TFT_LED_SET;
		
		Redraw_Mainmenu();//简单菜单测试
		Color_Test();//简单刷屏测试
		Num_Test();//数码管字体显示
		Font_Test();//中英文测试  
			
		TFT_Clear(WHITE);  
		//delay_ms(1000);
		delay_ms(1000);
		TFT_Clear(WHITE);  
		TFT_DrawFont_GBK16(10,50,BLUE,GRAY0,"测试成功.");
		delay_ms(1000);
		testsd();
  }
 
}

FATFS fs;         /* Work area (file system object) for logical drive */
FIL fsrc, fdst;      /* file objects */
FRESULT res;
UINT br,bw;
char path0[512]="0:";
char buffer[4096];   /* file copy buffer */
uint8_t textFileBuffer[] = "中英文测试字符串 \r\nChinese and English test strings \r\n";
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
  * @函数名称	Delay
  * @函数说明   实现延时功能 
  * @输入参数   nCount: 延时时间参数，数值越大延时时间越长 
  * @输出参数   无
  * @返回参数   无
  * @注意事项	无
  *****************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
/*******************************************************************************
  * @函数名称	scan_files
  * @函数说明   搜索文件目录下所有文件 
  * @输入参数   path: 根目录 
  * @输出参数   无
  * @返回参数   FRESULT
  * @注意事项	无
  *****************************************************************************/
FRESULT scan_files (
    char* path        /* Start node to be scanned (also used as work area) */
)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    char *fn;   /* This function is assuming non-Unicode cfg. */
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fname[0] == '.') continue;             /* Ignore dot entry */
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                sprintf(&path[i], "/%s", fn);
				printf("scan file - %s\n\r",path);
                res = scan_files(path);
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                printf("scan file - %s/%s\n\r", path, fn);
            }
        }
    }else{
		printf("scan files error : %d\n\r",res);
	}

    return res;
}
/*******************************************************************************
  * @函数名称	SD_TotalSize
  * @函数说明   文件空间占用情况 
  * @输入参数   无 
  * @输出参数   无
  * @返回参数   1: 成功 
  				0: 失败
  * @注意事项	无
  *****************************************************************************/
int SD_TotalSize(char *path)
{
    FATFS *fs;
    DWORD fre_clust;        

    res = f_getfree(path, &fre_clust, &fs);  /* 必须是根目录，选择磁盘0 */
    if ( res==FR_OK ) 
    {
	  printf("\n\rget %s drive space.\n\r",path);
	  /* Print free space in unit of MB (assuming 512 bytes/sector) */
      printf("%d MB total drive space.\r\n"
           "%d MB available.\r\n",
           ( (fs->n_fatent - 2) * fs->csize ) / 2 /1024 , (fre_clust * fs->csize) / 2 /1024 );
		
	  return 1;
	}
	else
	{ 
	  printf("\n\rGet total drive space faild!\n\r");
	  return 0;   
	}
}


int testsd()
{

	printf("\x0c\0");printf("\x0c\0");//超级终端清屏
	printf("\033[1;40;32m");//设置超级终端背景为黑色，字符为绿色
	printf("\r\n*******************************************************************************");
	printf("\r\n************************ Copyright 2009-2012, ViewTool ************************");
	printf("\r\n*************************** http://www.viewtool.com ***************************");
	printf("\r\n***************************** All Rights Reserved *****************************");
	printf("\r\n*******************************************************************************");
	printf("\r\n");
	//配置SPI1接口
	MSD0_SPI_Configuration();
	//挂载文件系统
	res = f_mount(0,&fs);
	if(res != FR_OK){
		printf("mount filesystem 0 failed : %d\n\r",res);
	}
	//写文件测试
	printf("write file test......\n\r");
    res = f_open(&fdst, "0:/1.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(res != FR_OK){
		printf("open file error : %d\n\r",res);
	}else{
	    res = f_write(&fdst, textFileBuffer, sizeof(textFileBuffer), &bw);               /* Write it to the dst file */
		if(res == FR_OK){
			printf("write data ok! %d\n\r",bw);
		}else{
			printf("write data error : %d\n\r",res);
		}
		/*close file */
		f_close(&fdst);
	}

	//读文件测试
	printf("read file test......\n\r");
    res = f_open(&fsrc, "0:/1.txt", FA_OPEN_EXISTING | FA_READ);
    if(res != FR_OK){
		printf("open file error : %d\n\r",res);
	}else{
	    res = f_read(&fsrc, buffer, sizeof(textFileBuffer), &br);     /* Read a chunk of src file */
		if(res==FR_OK){
			printf("read data num : %d\n\r",br);
			printf("%s\n\r",buffer);
		}else{
			printf("read file error : %d\n\r",res);
		}
		/*close file */
		f_close(&fsrc);
	}
	//扫描已经存在的文件
	printf("\n\rbegin scan files path0......\n\r");
	scan_files(path0);

	SD_TotalSize(path0);//获取SD容量
	while(1)
	{
		//printf("Test in while\n\r");
		Delay(100000);

	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  报告在检查参数发生错误时的源文件名和错误行数
  * @param  file 源文件名
  * @param  line 错误所在行数 
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* 用户可以增加自己的代码用于报告错误的文件名和所在行数,
       例如：printf("错误参数值: 文件名 %s 在 %d行\r\n", file, line) */

    /* 无限循环 */
    while (1)
    {
    }
}
#endif



