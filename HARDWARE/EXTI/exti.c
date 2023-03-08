#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_exti.h"
#include "rtc.h"
#include "lcd.h"
int flage;
int t=0;
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{   
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	  KEY_Init();//��ʼ��������Ӧioģʽ

    //GPIOC.5 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.0	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
}

 
void EXTI0_IRQHandler(void)
{ 
	int i=0;
  delay_ms(10);    
	if(WK_UP==1)
	{	  
    t++;
    if(t==7)
       t=0;
	  if(t==1)
	 {
       flage=1;
       for(i=0;i<5;i++)
      { 
				POINT_COLOR=WHITE;
		    LCD_ShowNum(80,235,calendar.w_year,4,16);
		    delay_ms(200);
		    POINT_COLOR=0xFF99FF;
		    LCD_ShowNum(80,235,calendar.w_year,4,16);
		    delay_ms(200);
	    }
    }	
	  if(t==2)
	 {
       flage=2;
       for(i=0;i<5;i++)
      { 
				POINT_COLOR=WHITE;
		    LCD_ShowNum(120,235,calendar.w_month,2,16);
		    delay_ms(200);
		    POINT_COLOR=0xFF99FF;
		    LCD_ShowNum(120,235,calendar.w_month,2,16);
		    delay_ms(200);
	    }
    }
     if(t==3)
	  {
       flage=3;
       for(i=0;i<5;i++)
      { 
				POINT_COLOR=WHITE;
		    LCD_ShowNum(144,235,calendar.w_date,2,16);
		    delay_ms(200);
		    POINT_COLOR=0xFF99FF;
		    LCD_ShowNum(144,235,calendar.w_date,2,16);
		    delay_ms(200);
	    }
     }
     if(t==4)
	  {
       flage=4;
       for(i=0;i<5;i++)
      { 
				POINT_COLOR=WHITE;
		    LCD_ShowNum(80,270,calendar.hour,2,16);
		    delay_ms(200);
		    POINT_COLOR=0xFF99FF;
        LCD_ShowNum(80,270,calendar.hour,2,16);
		    delay_ms(200);
	     }
     }	
     if(t==5)
	  {
       flage=5;
       for(i=0;i<5;i++)
      { 
				POINT_COLOR=WHITE;
		    LCD_ShowNum(104,270,calendar.min,2,16);
		    delay_ms(200);
		    POINT_COLOR=0xFF99FF;
		    LCD_ShowNum(104,270,calendar.min,2,16);
		    delay_ms(200);
	    }
    }	
     if(t==6)
	  {
      flage=6;
      for(i=0;i<5;i++)
     { 
			 POINT_COLOR=WHITE;
		   LCD_ShowNum(128,270,calendar.sec,2,16);
		   delay_ms(200);
		   POINT_COLOR=0xFF99FF;
		   LCD_ShowNum(128,270,calendar.sec,2,16);
		   delay_ms(200);
	   }
    }		 
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
	LCD_Fill(25,110,215,120,WHITE);
	LCD_Fill(30,100,210,110,WHITE);
	LCD_Fill(35,90,205,100,WHITE);
	LCD_Fill(40,80,200,90,WHITE);
	LCD_Fill(45,70,195,80,WHITE);
	LCD_Fill(50,60,190,70,WHITE);
	LCD_Fill(55,50,185,60,WHITE);
	LCD_Fill(70,40,170,50,WHITE);
	LCD_Fill(90,30,150,40,WHITE);
	LCD_Fill(115,28,135,30,WHITE);  
	LCD_Fill(25,120,215,130,WHITE);
	LCD_Fill(30,130,210,140,WHITE);
	LCD_Fill(35,140,205,150,WHITE);
	LCD_Fill(40,150,200,160,WHITE);
	LCD_Fill(45,160,195,170,WHITE);
	LCD_Fill(50,170,190,180,WHITE);
	LCD_Fill(55,180,185,190,WHITE);
	LCD_Fill(70,190,170,200,WHITE);
	LCD_Fill(90,200,150,210,WHITE);
	LCD_Fill(115,210,135,212,WHITE);   
}

void EXTI9_5_IRQHandler(void)
{	   
	int n=0;		
	delay_ms(10);   //����			 
	if(KEY0==0)	
 {
		if(flage==1)
		   calendar.w_year=calendar.w_year-1;
	  if(flage==2)
		   calendar.w_month=calendar.w_month-1;
		   if(calendar.w_month<1)
		      calendar.w_month=12;
		if(flage==3)
	{    calendar.w_date=calendar.w_date-1;
	     if(calendar.w_month==1|calendar.w_month==3|calendar.w_month==5|calendar.w_month==7|calendar.w_month==8|calendar.w_month==10|calendar.w_month==12)
      {
          if(calendar.w_date<1)
             calendar.w_date=31;
      } 
		   if(calendar.w_month==4|calendar.w_month==6|calendar.w_month==9|calendar.w_month==11)
      {
          if(calendar.w_date<1)
             calendar.w_date=30;
      }
       if(calendar.w_month==2)
      {
          if(calendar.w_year%40)
         {
             if(calendar.w_year%1000)
            {
                if(calendar.w_date<1)
                   calendar.w_date=29;
            }
          }
          else
	       {
            if(calendar.w_date<1)
               calendar.w_date=28;
         }
       }
   }
   if(flage==4)
  {
		  calendar.hour=calendar.hour-1;
			if(calendar.hour==0)
			   calendar.hour=23;
  }
   if(flage==5)
  {
      calendar.min--;
		  if(calendar.min==0)
				 calendar.min=59;
  }
   if(flage==6)
  {
		  calendar.sec--;
      if(calendar.sec==0)
         calendar.sec=59;
  }
   RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
}
				EXTI_ClearITPendingBit(EXTI_Line5); //���LINE5�ϵ��жϱ�־λ
			  LCD_Fill(25,110,215,120,WHITE);
		    LCD_Fill(30,100,210,110,WHITE);
		    LCD_Fill(35,90,205,100,WHITE);
		    LCD_Fill(40,80,200,90,WHITE);
		    LCD_Fill(45,70,195,80,WHITE);
		    LCD_Fill(50,60,190,70,WHITE);
		    LCD_Fill(55,50,185,60,WHITE);
		    LCD_Fill(70,40,170,50,WHITE);
		    LCD_Fill(90,30,150,40,WHITE);
		    LCD_Fill(115,28,135,30,WHITE);  
		    LCD_Fill(25,120,215,130,WHITE);
		    LCD_Fill(30,130,210,140,WHITE);
				LCD_Fill(35,140,205,150,WHITE);
				LCD_Fill(40,150,200,160,WHITE);
				LCD_Fill(45,160,195,170,WHITE);
				LCD_Fill(50,170,190,180,WHITE);
				LCD_Fill(55,180,185,190,WHITE);
				LCD_Fill(70,190,170,200,WHITE);
				LCD_Fill(90,200,150,210,WHITE);
				LCD_Fill(115,210,135,212,WHITE);   
}

void EXTI15_10_IRQHandler()
{ 
	  int m=0;
    delay_ms(10);    //����			 
    if(KEY1==0)	
	 {
      if(flage==1)
     {
				calendar.w_year=calendar.w_year+1;
     }
			if(flage==2)
		 {
		    calendar.w_month++;
				if(calendar.w_month>12)
       {
					 calendar.w_month=1;
			 }
		 }
      if(flage==3)
     {
         calendar.w_date++;
         if(calendar.w_month==1|calendar.w_month==3|calendar.w_month==5|calendar.w_month==7|calendar.w_month==8|calendar.w_month==10|calendar.w_month==12)
        {
            if(calendar.w_date>31)
							 calendar.w_date=1;
				}
				 if(calendar.w_month==4|calendar.w_month==6|calendar.w_month==9|calendar.w_month==11)
        {   
	          if(calendar.w_date>30)
						calendar.w_date=1;
				}
         if(calendar.w_month==2)
				{
					  if(calendar.w_year%40)
					 {
							if(calendar.w_year%1000)
             {   
								if(calendar.w_date>29)
									 calendar.w_date=1;
						 }
					 }
				    else
			     {
              if(calendar.w_date>28)
                 calendar.w_date=1;
			     }
        }
      }
      if(flage==4)
     {  
        calendar.hour=calendar.hour+1;
        if(calendar.hour>24)
           calendar.hour=1;
     }
      if(flage==5)
     {
        calendar.min++;
        if(calendar.min>59)
           calendar.min=0;
     } 
      if(flage==6)
     {
        calendar.sec++;
        if(calendar.sec>59)
           calendar.sec=0;
     } 
		 RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);	
   }      
		    EXTI_ClearITPendingBit(EXTI_Line15); 
		    LCD_Fill(25,110,215,120,WHITE);
		    LCD_Fill(30,100,210,110,WHITE);
		    LCD_Fill(35,90,205,100,WHITE);
		    LCD_Fill(40,80,200,90,WHITE);
		    LCD_Fill(45,70,195,80,WHITE);
		    LCD_Fill(50,60,190,70,WHITE);
		    LCD_Fill(55,50,185,60,WHITE);
		    LCD_Fill(70,40,170,50,WHITE);
		    LCD_Fill(90,30,150,40,WHITE);
		    LCD_Fill(115,28,135,30,WHITE);  
		    LCD_Fill(25,120,215,130,WHITE);
		    LCD_Fill(30,130,210,140,WHITE);
				LCD_Fill(35,140,205,150,WHITE);
				LCD_Fill(40,150,200,160,WHITE);
				LCD_Fill(45,160,195,170,WHITE);
				LCD_Fill(50,170,190,180,WHITE);
				LCD_Fill(55,180,185,190,WHITE);
				LCD_Fill(70,190,170,200,WHITE);
				LCD_Fill(90,200,150,210,WHITE);
				LCD_Fill(115,210,135,212,WHITE);  
}
		

