#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"
#include "math.h"
#include "stm32f10x_exti.h"
#include "exti.h"
#include "key.h"
#include "image2lcd.h"
#include "stdlib.h"

extern const u8 gImage_image1[];
 int main(void)
{  u8 i=0;
	HEADCOLOR *imginfo;
	u16 x=0,y=0;
	u16 x0,y0;
 	imginfo=(HEADCOLOR*)gImage_image1;	//得到文件信息 
	delay_init();		                  //延时初始化
	uart_init(9600);                 //串口1初始化   
	LED_Init();			                    //LED初始化
 	LCD_Init(); 	                      //LCD初始化					   
	srand(imginfo->h*imginfo->w);
 
		if(i==0)
		{
			LCD_Clear(0X0000);//黑屏  
			if(imginfo->w>=240||imginfo->h>=360)
			{
				POINT_COLOR=RED;   	
				delay_ms(200);
				LCD_ShowString(10,70,200,16,16,"The Picture is too large");	
				delay_ms(200);
			}  
			x0=x;y0=y;
			while((x+imginfo->w)>lcddev.width||x==x0)//超过屏幕尺寸了
			{
				x=rand();//获得随机的x值
			}
			while((y+imginfo->h)>lcddev.height||y==y0)//超过屏幕尺寸了
			{
				y=rand();//获得随机的y值
			}  
			image_display(x,y,(u8*)gImage_image1);//在指定地址显示图片
		}
  NVIC_Configuration();	 	    	  
  EXTIX_Init();		 
	POINT_COLOR=RED;//设置字体为
	while(RTC_Init())		//RTC初始化	，一定要初始化成功
	{ 
		LCD_ShowString(100,240,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(100,240,200,16,16,"RTC Trying...");	
	}		    						
	//显示时间
	POINT_COLOR=BLACK;//设置字体为					 
	LCD_ShowString(80,235,200,16,16,"    -  -");	   
	LCD_ShowString(80,267,200,16,16,"  :  :  ");	 		    
	while(1)
	{   delay_ms(500);
		  ClockMaker();	
		  ClockMention();							  
	}			
}

	



