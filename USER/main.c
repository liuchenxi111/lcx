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
 	imginfo=(HEADCOLOR*)gImage_image1;	//�õ��ļ���Ϣ 
	delay_init();		                  //��ʱ��ʼ��
	uart_init(9600);                 //����1��ʼ��   
	LED_Init();			                    //LED��ʼ��
 	LCD_Init(); 	                      //LCD��ʼ��					   
	srand(imginfo->h*imginfo->w);
 
		if(i==0)
		{
			LCD_Clear(0X0000);//����  
			if(imginfo->w>=240||imginfo->h>=360)
			{
				POINT_COLOR=RED;   	
				delay_ms(200);
				LCD_ShowString(10,70,200,16,16,"The Picture is too large");	
				delay_ms(200);
			}  
			x0=x;y0=y;
			while((x+imginfo->w)>lcddev.width||x==x0)//������Ļ�ߴ���
			{
				x=rand();//��������xֵ
			}
			while((y+imginfo->h)>lcddev.height||y==y0)//������Ļ�ߴ���
			{
				y=rand();//��������yֵ
			}  
			image_display(x,y,(u8*)gImage_image1);//��ָ����ַ��ʾͼƬ
		}
  NVIC_Configuration();	 	    	  
  EXTIX_Init();		 
	POINT_COLOR=RED;//��������Ϊ
	while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	{ 
		LCD_ShowString(100,240,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(100,240,200,16,16,"RTC Trying...");	
	}		    						
	//��ʾʱ��
	POINT_COLOR=BLACK;//��������Ϊ					 
	LCD_ShowString(80,235,200,16,16,"    -  -");	   
	LCD_ShowString(80,267,200,16,16,"  :  :  ");	 		    
	while(1)
	{   delay_ms(500);
		  ClockMaker();	
		  ClockMention();							  
	}			
}

	



