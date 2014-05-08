/***************************************************************************/
// ������ϴ�豸������
// ģ�飺Һ������
// �ļ���ra8806.c
// ���ߣ������D
// �汾��V0.02
// ���ڣ�2013��11��8��
// ���ܣ�Һ������
// оƬ��STC12C5A60S2
// ���룺Keil uVision3 V3.90
/***************************************************************************/

#include <reg52.h>
#include <basefunc.h>
#include <fonts.h>
#include <ra8806.h> 
#include <parameter.h>

/***************************************************************************/
// Һ�����Ŷ���	
/***************************************************************************/
#define lcd_data P0
sbit REST	= P2^7;   // REST���ǽӿ��е�RST
sbit BUSY	= P2^6;   //BUSY���ǽӿ��е�BUSY
sbit CS		= P2^5;   // CS���ǽӿ��е�CS1
sbit RD0  	= P2^4;  // RD0���ǽӿ��е�RD
sbit WR0  	= P2^3;  // WR0���ǽӿ��е�WR
sbit CD		= P2^2;   // CD ���ǽӿ��е�RS






/***************************************************************************/
// Һ��д�������
// ����������
// ����ֵ����	
/***************************************************************************/
void LCD_CmdWrite(uchar cmd)
{
	CS=0;
	RD0 = 1;
	CD = 1;		
	WR0 = 0;
	lcd_data = cmd;
	//delay_us(2); 
	WR0 = 0;
	WR0 = 1;
	CS = 1;
}

/***************************************************************************/
// Һ��д�����ݺ���
// ����������
// ����ֵ����	
/***************************************************************************/
void LCD_DataWrite(uchar wdata)
{
	while(!BUSY);
	CS=0;
	RD0 = 1;
	CD = 0;		
	lcd_data = wdata; 
	WR0 = 0;
	//delay_us(10); 
	WR0 = 1;
	CS = 1;
}

/***************************************************************************/
// Һ����ȡ�����
// ��������ַ
// ����ֵ������
/***************************************************************************/
uchar LCD_CmdRead(uchar Addr)
{  
	uchar Data;  
	CS=0;
	CD=1;
	RD0=1;
	lcd_data=Addr;
	WR0=0;
	WR0=1;
	lcd_data=0XFF;
	CD=0;
	WR0=1;
	RD0=1;
	RD0=0;
	Data=lcd_data;
	return Data;
}

/***************************************************************************/
// Һ����ȡ���ݺ���
// ��������
// ����ֵ������
/***************************************************************************/
/*
uchar LCD_DataRead()
{
	uchar Data;
	lcd_data = 0x00;
	WR0 = 1;
	CS = 0;
	CD  = 0;
	RD0 = 0;
	Data = lcd_data;
	RD0 = 1;	
	CS = 1;			
	//CD = 1;
	lcd_data = 0xff;
	return Data;
}
*/

/***************************************************************************/
// Һ����ʼ������
// ��������
// ����ֵ����
/***************************************************************************/
void lcd_inital()
{ 
	REST = 0;
	delay_ms(50);
	REST = 1;
	delay_ms(50);
	LCD_CmdWrite(WLCR);		//[00H] , Default --> 0x00
	LCD_DataWrite(0x04);
	
	LCD_CmdWrite(MISC);		//[01H] , Default --> 0x00
	LCD_DataWrite(0x08);
	
	LCD_CmdWrite(ADSR);		//[03H] , Default --> 0x00 
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(INTR);		//[0FH] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(WCCR);		//[10H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(CHWI);		//[11H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(MAMR);		//[12H] , Default --> 0x11 
	LCD_DataWrite(0x11);
	
	LCD_CmdWrite(AWRR);		//[20H] , Default --> 0x27
	LCD_DataWrite(39);
	
	LCD_CmdWrite(DWWR);		//[21H] , Default --> 0x27
	LCD_DataWrite(39);
	
	LCD_CmdWrite(AWBR);		//[30H] , Default --> 0xEF	
	LCD_DataWrite(239);
	
	LCD_CmdWrite(DWHR);		//[31H] , Default --> 0xEF
	LCD_DataWrite(239);
	
	LCD_CmdWrite(AWLR);		//[40H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(AWTR);		//[50H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(CURX);		//[60H] , Default --> 0x00 
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(BGSG);		//[61H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(EDSG);		//[62H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(CURY);		//[70H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(BGCM);		//[71H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(EDCM);		//[72H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(BTMR);		//[80H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(ITCR);		//[90H] , Default --> 0x00    ��Ҫ����
	LCD_DataWrite(0x80);
	
	LCD_CmdWrite(PNTR);		//[E0H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(FNCR);		//[F0H] , Default --> 0x00
	LCD_DataWrite(0x00);
	
	LCD_CmdWrite(FVHT);		//[F1H] , Default --> 0x00
	LCD_DataWrite(0x00);
}

/***************************************************************************/
// Һ��X,Y���궨λ
// ������x����  y����
// ����ֵ����
/***************************************************************************/
void LCD_GotoXY(uchar xx,uchar yy)
{
	LCD_CmdWrite(CURX); 
	LCD_DataWrite(xx);
	LCD_CmdWrite(CURY);  
	LCD_DataWrite(yy);
}

/***************************************************************************/
// Һ����ͼģʽ
// ��������
// ����ֵ����
/***************************************************************************/
void LCD_Graphic(void)
{
	uchar temp;
	temp=LCD_CmdRead(WLCR);
	temp &=0xf7;
	LCD_CmdWrite(WLCR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// Һ������ģʽ
// ��������
// ����ֵ����
/***************************************************************************/
void LCD_Text(void)
{
	uchar temp;
	temp=LCD_CmdRead(WLCR);
	temp |=0x08;
	LCD_CmdWrite(WLCR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// Һ��DDRAM1 ��ʾ
// ��������
// ����ֵ����
/***************************************************************************/
void Only_Show_Page1(void)
{
	uchar temp;
	temp=LCD_CmdRead(MAMR);
	temp &=0x9f;
	temp |=0x10;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// Һ��DDRAM2 ��ʾ
// ��������
// ����ֵ����
/***************************************************************************/
/*
void Only_Show_Page2(void)
{
	uchar temp;
	temp=LCD_CmdRead(MAMR);
	temp &=0xaf;
	temp |=0x20;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}
*/

/***************************************************************************/
// Һ��DDRAM1��DDRAM2 ˫ͼ����ʾ
// ��������
// ����ֵ����
/***************************************************************************/
void Show_Two_Layer(void)
{
	uchar temp;	
	temp=LCD_CmdRead(MAMR);
	temp &=0xbf;
	temp |=0x30;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// Һ��DDRAM1��DDRAM2 OR��ʽ��ʾ
// ��������
// ����ֵ����
/***************************************************************************/
/*
void OR_Two_Layer(void)
{
	uchar temp;	
	temp=LCD_CmdRead(MAMR);
	temp &=0xf3;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}
*/

/***************************************************************************/
// Һ��DDRAM1��DDRAM2 XOR��ʽ��ʾ
// ��������
// ����ֵ����
/***************************************************************************/
void XOR_Two_Layer(void)
{
	uchar temp;	
	temp=LCD_CmdRead(MAMR);
	temp &=0xf7;
	temp |=0x04;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// Һ��DDRAM1��DDRAM2 NOR��ʽ��ʾ
// ��������
// ����ֵ����
/***************************************************************************/
/*
void NOR_Two_Layer(void)
{
	uchar temp;	
	temp=LCD_CmdRead(MAMR);
	temp &=0xfb;
	temp |=0x08;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}
*/

/***************************************************************************/
// Һ��DDRAM1��DDRAM2 AND��ʽ��ʾ
// ��������
// ����ֵ����
/***************************************************************************/
/*
void AND_Two_Layer(void)
{
	uchar temp;	
	temp=LCD_CmdRead(MAMR);
	temp |=0x0c;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}
*/

/***************************************************************************/
// Һ����ȡDDRAM1
// ��������
// ����ֵ����
/***************************************************************************/
void Access_Page1(void)
{
	uchar temp;	
	temp=LCD_CmdRead(MAMR);
	temp &=0xfd;
	temp |=0x01;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// ��ȡDDRAM2
// ��������
// ����ֵ����
/***************************************************************************/
void Access_Page2(void)
{
	uchar temp;	
	temp=LCD_CmdRead(MAMR);
	temp &=0xfe;
	temp |=0x02;
	LCD_CmdWrite(MAMR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// Һ������
// ��������
// ����ֵ����
/***************************************************************************/
void clear(void)
{ 
	LCD_Graphic();     //ѡ���ͼģʽ     
	LCD_CmdWrite(PNTR);
	LCD_DataWrite(0x00);
	LCD_CmdWrite(FNCR);
	LCD_DataWrite(0xa8);
	//delay_ms(3);
}


/***************************************************************************/
// Һ��������ʾ
// ��������
// ����ֵ����
/***************************************************************************/
/*
void display_all()
{
	LCD_Graphic();
	LCD_CmdWrite(PNTR);
	LCD_DataWrite(0xff);     //ȫ����0xff
	LCD_CmdWrite(FNCR);
	LCD_DataWrite(0xa8);
	//delay_ms(3);
}
*/

/***************************************************************************/
// Һ��ȫ��������ʾ
// ��������
// ����ֵ����
/***************************************************************************/
void normal_data(void)
{
	uchar temp;
	temp=LCD_CmdRead(WLCR);  //��WLCR�Ĵ�������
	temp &=0xfe;
	LCD_CmdWrite(WLCR);
	LCD_DataWrite(temp);     
}

/***************************************************************************/
// Һ��ȫ��������ʾ
// ��������
// ����ֵ����
/***************************************************************************/
/*
void reverse_data(void)
{
	uchar temp;
	temp=LCD_CmdRead(WLCR);  //��WLCR�Ĵ�������
	temp |=0x01;
	LCD_CmdWrite(WLCR);
	LCD_DataWrite(temp);     
}
*/

/***************************************************************************/
// Һ�����ݷ�������
// ��������
// ����ֵ����
/***************************************************************************/
/*
void LCD_Inv(void)
{
	uchar temp;	
	temp=LCD_CmdRead(0x10);
	temp |=0x20;
	LCD_CmdWrite(0x10);
	LCD_DataWrite(temp); 
}
*/

/***************************************************************************/
// Һ��������������
// ��������
// ����ֵ����
/***************************************************************************/
void LCD_NoInv(void)
{
	uchar temp;	
	temp=LCD_CmdRead(WCCR);
	temp &=0xdf;
	LCD_CmdWrite(WCCR);
	LCD_DataWrite(temp); 
}

/***************************************************************************/
// Һ���ַ��Ŵ�i��
// �������Ŵ���1~4
// ����ֵ����
/***************************************************************************/
void enlarge(uchar i)
{  
	switch(i)
	{
		case 0x01:
			LCD_CmdWrite(FVHT);
			LCD_DataWrite(0x00);  
		break;
		case 0x02:
			LCD_CmdWrite(FVHT);
			LCD_DataWrite(0x50);  
		break;
		case 0x03:
			LCD_CmdWrite(FVHT);
			LCD_DataWrite(0xa0); 
		break;
		case 0x04:
			LCD_CmdWrite(FVHT);
			LCD_DataWrite(0xf0); 
		break;
	}
}

/***************************************************************************/
// Һ����һ�����
// ��������
// ����ֵ����
/***************************************************************************/
/*
void display_biao(void)
{
	uint n0,n1;
	LCD_Graphic();   //ѡ���ͼģʽ
	LCD_GotoXY(0x00,0x00);   //�趨X,Y����λ��
	LCD_CmdWrite(MWCR);
	for(n0=0;n0<40;n0++)
	{
		LCD_DataWrite(0xff);
	}
	for(n0=0;n0<31;n0++)		
	{
		for(n1=0;n1<40;n1++)
		{
			if (n1==0) LCD_DataWrite(0x80);
			else if (n1==39) LCD_DataWrite(0x01);
			else LCD_DataWrite(0x00);
		}
	}
	for(n0=0;n0<40;n0++)
	{
		LCD_DataWrite(0xff);
	}
	for(n0=0;n0<(125);n0++)		
	{
		for(n1=0;n1<40;n1++)
		{
			if (n1==0)          LCD_DataWrite(0x80);
			else if (n1==39) LCD_DataWrite(0x01);
			else                LCD_DataWrite(0x00);
		}
	}
	for(n0=0;n0<40;n0++)
	{
		LCD_DataWrite(0xff);
	}
}
*/
/***************************************************************************/
// Һ����ָ�������괦��ʾ�ַ���
// ������x����  y����  �ַ�������
// ����ֵ����
/***************************************************************************/
void LCD_ShowStr(uchar xxx,uchar yyy,uchar *text)
{ 
	LCD_Text();   //ѡ���ı�ģʽ
	LCD_GotoXY(xxx,yyy);   //�趨X,Y����λ�� 
	LCD_CmdWrite(MWCR);
	while(*text != '\0')          
	{
		LCD_DataWrite(*text++);
	}
}

/***************************************************************************/
// Һ����ָ�������괦��ʾ�ַ�
// ������x����  y����  �ַ�
// ����ֵ����
/***************************************************************************/
void LCD_ShowChar(uchar xxx,uchar yyy,uchar text)
{ 
	LCD_Text();   //ѡ���ı�ģʽ
	LCD_GotoXY(xxx,yyy);   //�趨X,Y����λ�� 
	LCD_CmdWrite(MWCR);
	LCD_DataWrite(text);
}

/***************************************************************************/
// Һ����ʾ�����ֿ���ַ�
// ������
// ����ֵ����
/***************************************************************************/
/*
void display_word(const uchar *cha, int count )
{
	uint iiii=0;
	LCD_Text();  //ѡ���ı�ģʽ
	LCD_GotoXY(0x00,0x00);   //�趨X,Y����λ�� 
	LCD_CmdWrite(MWCR); 
	for(iiii=0;iiii<count;iiii++)
	{
		LCD_DataWrite(*cha++);
	}   
}
*/
/***************************************************************************/
// ��ʾһ�б߿�
// ������x��ʼ����0~39  y��ʼ����0~239  ���  �߶� ��ɫ1����2����  
// ����ֵ����
/***************************************************************************/
void display_kuang(uchar x_star,uchar y_star,uchar w,uchar h, uchar color)
{
	uchar width,heigh;      //i��ʾ��,j��ʾ��
	LCD_Graphic();   //ѡ���ͼģʽ
	for(heigh=0;heigh<h;heigh++)
	{  
		if(heigh==0)
		{
			LCD_GotoXY(x_star,y_star+heigh);   //�趨X,Y��ʼ����λ��  
			for(width=0;width<w;width++)
			{ 
				LCD_CmdWrite(MWCR); 
				LCD_DataWrite(0xff);
			}
		}
		else if((heigh>0)&&(heigh<(h-1)))
		{
			LCD_GotoXY(x_star,y_star+heigh);   //�趨X,Y��ʼ����λ��    
			LCD_CmdWrite(MWCR);   
			if(color)
			{
				LCD_DataWrite(0x80);
				for(width=1;width<(w-1);width++)
				{
					LCD_DataWrite(0x00);
				}
				LCD_DataWrite(0x01);
			}
			else
			{
				LCD_DataWrite(0xff);
				for(width=1;width<(w-1);width++)
				{
					LCD_DataWrite(0xff);
				}
				LCD_DataWrite(0xff);				
			}
		}
		else if(heigh==(h-1))
		{
			LCD_GotoXY(x_star,y_star+heigh);   //�趨X,Y��ʼ����λ��  
			for(width=0;width<w;width++)
			{      
				LCD_CmdWrite(MWCR);
				LCD_DataWrite(0xff);
			}
		}
	}
}       

/***************************************************************************/
// ��ʾͼƬ
// ������x_star:0~39;y_star:0~239 w:0~39;h:0~239 
// ����ֵ����
/***************************************************************************/
void drow_picture(uchar x, uchar y, uchar w, uchar h, uchar *pData)
{
	uchar i, j;
	LCD_Graphic(); 
	for(i=0;i<h;i++)
	{
		for(j=0; j<w; j++)
		{
			LCD_GotoXY(x+j,y+i); 
			LCD_CmdWrite(MWCR);   
			LCD_DataWrite(*pData++); 
		}
	}
}

/***************************************************************************/
// ��㺯��
// ������x���� y����
// ����ֵ����
/***************************************************************************/
/*
void drow_point(uint x, uint y)
{
	uchar temp, temp1= x/8;
	LCD_Graphic();
	LCD_GotoXY(temp1,y); 
	LCD_CmdWrite(MRCR);	//�ڴ���� 
	temp = LCD_DataRead();
	LCD_GotoXY(temp1,y); 
	LCD_CmdWrite(MWCR);   
	LCD_DataWrite(temp | (1<<7-x%8)); 
}
*/

/***************************************************************************/
// ����ߺ���
// ������x��ʼ���� y��ʼ���� x��ֹ����
// ����ֵ����
/***************************************************************************/
/*
void drow_row_line(uint x0, uint y0, uint x1)
{
	uint temp;
	if(x0>x1)
	{
		temp = x1;
		x1 = x0;
		x0 = temp;
	}
	while(x1>=x0)
	{
		drow_point(x0, y0);
		x0++;
	}
}
*/

/***************************************************************************/
// �����ߺ���
// ������x��ʼ���� y��ʼ���� y��ֹ����
// ����ֵ����
/***************************************************************************/
/*
void drow_column_line(uint x0, uint y0, uint y1)
{
	uint temp;
	if(y0>y1)
	{
		temp = y1;
		y1 = y0;
		y0 = temp;
	}
	do
	{
		drow_point(x0, y0);
		y0++;
	}
	while(y1>=y0);
}
*/

/***************************************************************************/
// ����Բ�Ǿ���
// ������x��ʼ���� y��ʼ���� ��� �߶� ��ɫ1����2����
// ����ֵ����
/***************************************************************************/
void display_r_kuang(uchar x_star,uchar y_star,uchar w,uchar h,uchar color)
{
	if(color)
	{
		display_kuang(x_star,y_star,w,h,1);
		drow_picture(x_star, y_star, 1, 8, RoundedTLB);
		drow_picture(x_star,  y_star+h-8, 1, 8, RoundedBLB);
		drow_picture(x_star+w-1, y_star, 1, 8, RoundedTRB);
		drow_picture(x_star+w-1, y_star+h-8, 1, 8, RoundedBRB);
	}
	else
	{
		display_kuang(x_star,y_star,w,h,0);
		drow_picture(x_star, y_star, 1, 8, RoundedTLF);
		drow_picture(x_star,  y_star+h-8, 1, 8, RoundedBLF);
		drow_picture(x_star+w-1, y_star, 1, 8, RoundedTRF);
		drow_picture(x_star+w-1, y_star+h-8, 1, 8, RoundedBRF);		
	}
}

/***************************************************************************/
// �������Բ�Ǿ���
// ������x��ʼ���� y��ʼ���� ��� �߶� ��ɫ1����2����
// ����ֵ����
/***************************************************************************/
/*
void display_rl_kuang(uchar x_star,uchar y_star,uchar w,uchar h,uchar color)
{
	if(color)
	{
		display_kuang(x_star,y_star,w,h,1);
		drow_picture(x_star, y_star, 1, 8, RoundedTLB);
		drow_picture(x_star,  y_star+h-8, 1, 8, RoundedBLB);
	}
	else
	{
		display_kuang(x_star,y_star,w,h,0);
		drow_picture(x_star, y_star, 1, 8, RoundedTLF);
		drow_picture(x_star,  y_star+h-8, 1, 8, RoundedBLF);
	}
}
*/

/***************************************************************************/
// �����Ҳ�Բ�Ǿ���
// ������x��ʼ���� y��ʼ���� ��� �߶� ��ɫ1����2����
// ����ֵ����
/***************************************************************************/
/*
void display_rr_kuang(uchar x_star,uchar y_star,uchar w,uchar h,uchar color)
{
	if(color)
	{
		display_kuang(x_star,y_star,w,h,1);
		drow_picture(x_star+w-1, y_star, 1, 8, RoundedTRB);
		drow_picture(x_star+w-1, y_star+h-8, 1, 8, RoundedBRB);
	}
	else
	{
		display_kuang(x_star,y_star,w,h,0);
		drow_picture(x_star+w-1, y_star, 1, 8, RoundedTRF);
		drow_picture(x_star+w-1, y_star+h-8, 1, 8, RoundedBRF);		
	}
}
*/

/***************************************************************************/
// ��������
// ��������
// ����ֵ����
/***************************************************************************/
void Enable_TP(void)
{
	uchar temp;
	temp=LCD_CmdRead(TPCR1);
	temp|=0x80;
	LCD_CmdWrite(TPCR1);
	LCD_DataWrite(temp);
}

/***************************************************************************/
// �����������жϷ�ʽ
// ��������
// ����ֵ����
/***************************************************************************/
void Enable_Maunal_TP(void)
{
	uchar temp;
	temp=LCD_CmdRead(TPCR2);
	temp|=0x80;
	LCD_CmdWrite(TPCR2);
	LCD_DataWrite(temp);
}

/***************************************************************************/
// ���������жϷ�ʽ
// ��������
// ����ֵ����
/***************************************************************************/
/*
void Enable_interrput_TP(void)
{
	uchar temp;
	temp=LCD_CmdRead(INTR);
	temp|=0x10;
	LCD_CmdWrite(INTR);
	LCD_DataWrite(temp);
}
*/

/***************************************************************************/
// ���ô������ж�
// ��������
// ����ֵ����
/***************************************************************************/
/*
void Disable_interrput_TP(void)
{
	uchar temp;
	temp=LCD_CmdRead(INTR);
	temp&=0xef;
	LCD_CmdWrite(INTR);
	LCD_DataWrite(temp);
}
*/

/***************************************************************************/
// 
// ��������
// ����ֵ����
/***************************************************************************/
void Switch_Latch_X_data(void)
{
	uchar temp;
	temp=LCD_CmdRead(TPCR2);
	temp&=0xFE;
	temp|=0x02;
	LCD_CmdWrite(TPCR2);
	LCD_DataWrite(temp);
}

/***************************************************************************/
// 
// ��������
// ����ֵ����
/***************************************************************************/
void Switch_Latch_Y_data(void)
{
	uchar temp;
	temp=LCD_CmdRead(TPCR2);
	temp|=0x01;
	temp|=0x02;
	LCD_CmdWrite(TPCR2);
	LCD_DataWrite(temp);
}

/***************************************************************************/
// x����ֵת��
// ��������
// ����ֵ����
/***************************************************************************/
uint trans_tpx(uint x)
{
	long tp_x;
	long temp;
	temp=(((long)x)-x_tps0)*320;
	tp_x=temp/x_tps;
	return tp_x;
}

/***************************************************************************/
// y����ֵת��
// ��������
// ����ֵ����
/***************************************************************************/
uint trans_tpy(uint y)
{
	long tp_y;
	long temp;
	temp=(((long)y)-y_tps0)*240;
	tp_y=temp/y_tps;
	return tp_y;
}

/***************************************************************************/
// ��ȡ������ֵ
// ����������x���� ����y����
// ����ֵ��result_data
//						0�޴��� 
//						1�����涨ʱ���� 
//						2���������Զ� 
//						3�������°ఴ�� 
//						4������ػ�״̬ȡ���°� 
//						5���ý���һ�Ų�ѡ��  
//						6���ý�����Ų�ѡ�� 
//						7���ý������Ų�ѡ�� 
//						8���ý����ĺŲ�ѡ��  
//						9���ý�����Ų�ѡ��  
//						10���ý������Ų�ѡ��
//						11���ý����һ����
//						12���ý����һ����
//						13���ý��汣��
//						14���ý��淵��
//						15����ȡ�����淵��
/***************************************************************************/
uchar getTP_Value(uint x_temp, uint y_temp)
{
	uchar result_data = 0;
	if(displayMode == MainDisplayMode) //������������ʾ
	{
		if(x_temp>0 && x_temp<96 && y_temp>208 && y_temp<240) //��ʱ����
		{
			if(runMode == ManualMode)
			{
				result_data = 1;
			}
		}
		else if(x_temp>104 && x_temp<208 && y_temp>208 && y_temp<240) //���Զ�
		{
			result_data = 2;
		}
		else if(x_temp>216 && x_temp<312 && y_temp>208 && y_temp<240) //�°ఴ��
		{
			if(runMode == AutoMode) //ֻ���Զ�ģʽ������ܵ���°ఴť
			{
				result_data = 3;
			}
		}
	}
	else if(displayMode == PowerOffing) //���������ڹػ�
	{
		if(x_temp>216 && x_temp<312 && y_temp>208 && y_temp<240) //ȡ���°�
		{
			result_data = 4;
		}
	}
	else if(displayMode == Setting) //���ý���������ʾ
	{
		if(x_temp>40 && x_temp<72 && y_temp>74 && y_temp<174) //һ�Ų�ѡ�� 
		{
			result_data = 5;
		}
		else if(x_temp>80 && x_temp<112 && y_temp>74 && y_temp<174) //���Ų�ѡ�� 
		{
			result_data = 6;
		}
		else if(x_temp>120 && x_temp<152 && y_temp>74 && y_temp<174) //���Ų�ѡ�� 
		{
			result_data = 7;
		}
		else if(x_temp>160 && x_temp<192 && y_temp>74 && y_temp<174) //�ĺŲ�ѡ��  
		{
			result_data = 8;
		}
		else if(x_temp>200 && x_temp<232 && y_temp>74 && y_temp<174) //��Ų�ѡ��  
		{
			result_data = 9;
		}
		else if(x_temp>240 && x_temp<272 && y_temp>74 && y_temp<174) //���Ų�ѡ��
		{
			result_data = 10;
		}
		else if(x_temp>160 && x_temp<216 && y_temp>12 && y_temp<60) //��һ����
		{
			result_data = 11;
		}
		else if(x_temp>232 && x_temp<288 && y_temp>12 && y_temp<60) //��һ����
		{
			result_data = 12;
		}
		else if(x_temp>112 && x_temp<208 && y_temp>208 && y_temp<240) //����
		{
			result_data = 13;
		}
		else if(x_temp>216 && x_temp<312 && y_temp>208 && y_temp<240) //����
		{
			result_data = 14;
		}
	}
	else if(displayMode == SettingSaved)//���ñ���ɹ�
	{
		if(x_temp>216 && x_temp<312 && y_temp>208 && y_temp<240) //����
		{
			result_data = 15;
		}
	}
	return result_data;
}

/***************************************************************************/
// �ֶ�ģʽ��ѯ���Դ�����
// ��������
// ����ֵ��result_data 
/***************************************************************************/
uchar tp_ManualMode()
{
	uchar Touch_Sta_Valid,INT_Sta,count,X1,Y1,X2,Y2,temp,result_data=0;
	uint X,Y,x_temp,y_temp;
	Touch_Sta_Valid=0;
	LCD_CmdWrite(TPCR2);
	LCD_DataWrite(0x81);
	LCD_CmdWrite(0xff); 
	LCD_DataWrite(0xff);  //д���������˼������д����ʱ����æ��ȷ����ʱra8806�Ƿ����ڲ�����״̬
	INT_Sta=LCD_CmdRead(INTR);
	if((INT_Sta&0x08)==0x08)
	{
		for(count=0;count<50;count++)
		{
			INT_Sta=LCD_CmdRead(INTR);
			if(INT_Sta==0)
			{
				Touch_Sta_Valid=0;
				break;
			}
			if(count==49)
			{
				Touch_Sta_Valid=1;
			}
		}
		if(Touch_Sta_Valid)
		{
			Switch_Latch_X_data();
			delay_us(100);
			Switch_Latch_Y_data();	
			delay_us(100);
			X1=LCD_CmdRead(TPXR);
			LCD_CmdWrite(0xff); 
			LCD_DataWrite(0xff);
			Y1=LCD_CmdRead(TPYR);
			LCD_CmdWrite(0xff); 
			LCD_DataWrite(0xff);
			X2=LCD_CmdRead(TPZR)&0x03;
			LCD_CmdWrite(0xff); 
			LCD_DataWrite(0xff);
			Y2=LCD_CmdRead(TPZR)&0x0c;
			LCD_CmdWrite(0xff); 
			LCD_DataWrite(0xff);
			X = (((unsigned int)X1&0x00ff)<<2) | ((unsigned int)X2&0x0003);
			Y = (((unsigned int)Y1&0x00ff)<<2) | (((unsigned int)Y2&0x000C) >> 2);
			if((X<948)&&(X>94)&&(Y<944)&&(Y>92))
			{
				x_temp=trans_tpx(X);
				y_temp=trans_tpy(Y);
				result_data = getTP_Value(x_temp, y_temp);
			}
		}
		temp=LCD_CmdRead(INTR)&0xfe;
		LCD_CmdWrite(INTR);
		LCD_DataWrite(temp);
	}
	return result_data;
}

/***************************************************************************/
// ��ʾ���ý���
// ������0��������  1����ɹ���ʾ  2����ʧ����ʾ 3���ڱ�����ʾ
// ����ֵ����
/***************************************************************************/
void SettingDisplay(uchar settingStatus)
{	
	uchar i, currentTimeCount;
	Access_Page2(); //��ȡDDRAM2
	clear(); 
	//�Ӽ�ʱ�䰴ť
	display_r_kuang(20,12,7,48,1);
	display_r_kuang(29,12,7,48,1);
	//���òۿ�
	for(i=0; i<8; i++)
	{
		if(cistern[i].isCurrentlSetting)
		{
			display_kuang(i*5,74,4,100,0);
		}
		else
		{
			display_kuang(i*5,74,4,100,1);
		}
	}
	//����
	if(displayMode == Setting)
	{
		display_r_kuang(14,208,12,32,1);
	}
	display_r_kuang(27,208,12,32,1);
	//��ʾ��
	if(settingStatus)
	{
		display_r_kuang(9,72,22,64,1);	//����ɹ���ʾ
	}

	Access_Page1(); //��ȡDDRAM1
	clear();
	normal_data();
	LCD_NoInv();
	//����
	LCD_ShowStr(1,8,"��ʱ����:");
	//�Ӽ�ʱ�䰴ť
	LCD_ShowStr(21,18,"�� һ");
	LCD_ShowStr(21,38,"�� ��");
	LCD_ShowStr(30,18,"�� һ");
	LCD_ShowStr(30,38,"�� ��");
	//���òۿ�
	LCD_ShowStr(1,96,"δ");
	LCD_ShowStr(1,116,"��");
	LCD_ShowStr(1,136,"��");
	//���òۿ�
	for(i=1; i<7; i++)
	{
		currentTimeCount = cistern[i].perSettingTime/60;
		LCD_ShowChar(1+5*i,96,currentTimeCount/10+48);
		LCD_ShowChar(2+5*i,96,currentTimeCount%10+48);
		LCD_ShowStr(1+5*i,116,"��");
		LCD_ShowStr(1+5*i,136,"��");
	}
	LCD_ShowStr(36,96,"δ");
	LCD_ShowStr(36,116,"��");
	LCD_ShowStr(36,136,"��");
	//�ۺ�
	LCD_ShowStr(1,180,"��");
	LCD_ShowStr(6,180,"1");
	LCD_ShowStr(11,180,"2");
	LCD_ShowStr(16,180,"3");
	LCD_ShowStr(21,180,"4");
	LCD_ShowStr(26,180,"5");
	LCD_ShowStr(31,180,"6");
	LCD_ShowStr(36,180,"��");
	//����
	if(displayMode == Setting)
	{
		LCD_ShowStr(17,216,"��  ��");
	}
	LCD_ShowStr(30,216,"��  ��");
	//��ʾ
	if(settingStatus)
	{
		display_r_kuang(9,72,22,64,0);	//����ɹ���ʾ
		display_kuang(10,80,20,48,1);	//����ɹ���ʾ
		if(settingStatus == 1)
			LCD_ShowStr(14,96,"�� �� �� ��");   //����ɹ���ʾ
		else if(settingStatus == 2)
			LCD_ShowStr(14,96,"�� �� ʧ ��");   //����ʧ����ʾ
		else
			LCD_ShowStr(14,96,"�� �� ��...");   //����ʧ����ʾ
	}

	XOR_Two_Layer();//DDRAM1 OR DDRAM2
	Show_Two_Layer();//DDRAM1��DDRAM2ͬʱ��ʾ
}

/***************************************************************************/
// ��������
// ��������
// ����ֵ����
/***************************************************************************/
void PowerOnDisplay()
{
	Access_Page2();
	LCD_NoInv();
	clear();
	Access_Page1();
	LCD_NoInv();
	clear();
	Only_Show_Page1();
	//enlarge(2);
	//LCD_ShowStr(0x02,0x00,"��Ϫ��Խ�Ļ������");
	enlarge(1);
	LCD_ShowStr(0x04,0x35,"��ϵ��:½־��");
	LCD_ShowStr(0x04,0x53,"��ϵ�绰: 13567402367");
}

/***************************************************************************/
// ��ʾ������
// ������0������ʾ 1���ڹػ� 2�ػ��ɹ�
// ����ֵ����
/***************************************************************************/
void MainDisplay(uchar displayStatus)
{
	uchar i, currentTimeCount;
	Access_Page2(); //��ȡDDRAM2
	clear(); 
	//״̬��ʾ
	display_kuang(0,0,8, 32, 1);
	display_kuang(8,0,8, 32, 1);
	//��е��λ����ʾ
	for(i=0; i<8; i++)
	{
		drow_picture(2+i*5, 42, 1, 8, HollowPrism);	
		drow_picture(2+i*5, 58, 1, 8, HollowPrism);	
	}
	if(manipulator.currentPosition%2 == 0)
	{
		if(manipulator.manipulatorPosition == Top)
		{
			drow_picture(2+manipulator.currentPosition/2*5, 42, 1, 8, SolidPrism);
		}
		else if(manipulator.manipulatorPosition == Bottom)
		{
			drow_picture(2+manipulator.currentPosition/2*5, 58, 1, 8, SolidPrism);	
		}
	}
	else
	{
		if(manipulator.manipulatorPosition == Top)
		{
			drow_picture(4+manipulator.currentPosition/2*5, 42, 1, 8, SolidPrism);
		}
		else if(manipulator.manipulatorPosition == Bottom)
		{
			drow_picture(4+manipulator.currentPosition/2*5, 58, 1, 8, SolidPrism);	
		}
	}
	//��״̬��ʾ
	for(i=0; i<8; i++)
	{
		if(cistern[i].cisternStatus)
		{
			display_kuang(5*i,74,4,100,0);	
		}
		else
		{
			display_kuang(5*i,74,4,100,1);
		}
	}
	//������ʾ
	if(displayStatus == 0)
	{
		if(runMode == ManualMode)
		{
			display_r_kuang(0,208,12,32,1);	
		}
		display_r_kuang(13,208,13,32,1);
	}
	if(runMode == AutoMode && displayStatus != 2) //ֻ���Զ�ģʽ������ܵ���°ఴť
	{
		display_r_kuang(27,208,12,32,1);
	}
	
	//��ʾ��Ϣ
	if(displayStatus)
	{
		display_r_kuang(9,72,22,64,1);
	}

	Access_Page1();//��ȡDDRAM1
	clear();
	normal_data();
	LCD_NoInv();
	//״̬��ʾ
	LCD_ShowStr(2,8,"״̬");
	if(runMode == AutoMode)
		LCD_ShowStr(10,8,"�Զ�");
	else
		LCD_ShowStr(10,8,"�ֶ�");

	//��е�۶�����ʾ
	LCD_ShowStr(22,8,"��е�۶���:");
	switch(manipulator.manipulaterStatus)
	{
		case Stop:
			LCD_ShowStr(34,8,"����");
		break;
		case GoEntrance:
			LCD_ShowStr(34,8,"<---");
		break;
		case GoOutfall:
			LCD_ShowStr(34,8,"--->");
		break;
		case GoUp:
			LCD_ShowStr(34,8,"����");
		break;
		case GoDown:
			LCD_ShowStr(34,8,"����");
		break;
		default:
			LCD_ShowStr(34,8,"����");
	}
	//��״̬��ʾ
	for(i=0; i<8; i++)
	{
		if(cistern[i].cisternStatus == Empty)
		{
			LCD_ShowStr(1+5*i,100,"��");
			LCD_ShowStr(1+5*i,132,"��");
		}
		else if(cistern[i].cisternStatus == Ready)
		{
			LCD_ShowStr(1+5*i,100,"��");
			LCD_ShowStr(1+5*i,132,"��");
		}
		else
		{	
			if(i != 0 && i != 7)// ���ڳ��ڲ���ʱ�����
			{
				currentTimeCount = (cistern[i].settingTime - cistern[i].currentTime)/60;
				LCD_ShowChar(1+5*i,96,currentTimeCount/10+48);
				LCD_ShowChar(2+5*i,96,currentTimeCount%10+48);
				LCD_ShowStr(1+5*i,116,"��");
				LCD_ShowStr(1+5*i,136,"��");	
			}
			else
			{
				LCD_ShowStr(1+5*i,100,"æ");
				LCD_ShowStr(1+5*i,132,"µ");
			}		
		}
	}
	LCD_ShowStr(1,180,"��");
	LCD_ShowStr(6,180,"1");
	LCD_ShowStr(11,180,"2");
	LCD_ShowStr(16,180,"3");
	LCD_ShowStr(21,180,"4");
	LCD_ShowStr(26,180,"5");
	LCD_ShowStr(31,180,"6");
	LCD_ShowStr(36,180,"��");
	//������ʾ
	if(displayStatus == 0)
	{
		if(runMode == ManualMode)
		{
			LCD_ShowStr(2,216,"��ʱ����");
		}
		LCD_ShowStr(15,216,"�ֶ�/�Զ�");
	}
	if(displayStatus == 1)
	{
		LCD_ShowStr(29,216,"ȡ���°�");
	}
	else if(displayStatus == 0 && runMode == AutoMode)//ֻ���Զ�ģʽ������ܵ���°ఴť
	{
		LCD_ShowStr(29,216,"�°ఴ��");
	}
	//��ʾ��Ϣ
	if(displayStatus)
	{
		display_r_kuang(9,72,22,64,0);
		display_kuang(10,80,20,48,1);
		if(displayStatus == 1)
			LCD_ShowStr(14,96,"�� �� ��...");
		else
			LCD_ShowStr(14,96,"�� �� �� ��"); 
	}

	XOR_Two_Layer();//DDRAM1 OR DDRAM2
	Show_Two_Layer();//DDRAM1��DDRAM2ͬʱ��ʾ
}

/***************************************************************************/
// ��е��״̬ˢ��
// ��������
// ����ֵ����
/**************************************************************************/
void ManipulatorStatusDisplay(void)
{
	Access_Page1();//��ȡDDRAM1
	normal_data();
	LCD_NoInv();
	//��е�۶�����ʾ
	switch(manipulator.manipulaterStatus)
	{
		case Stop:
			LCD_ShowStr(34,8,"����");
		break;
		case GoEntrance:
			LCD_ShowStr(34,8,"<---");
		break;
		case GoOutfall:
			LCD_ShowStr(34,8,"--->");
		break;
		case GoUp:
			LCD_ShowStr(34,8,"����");
		break;
		case GoDown:
			LCD_ShowStr(34,8,"����");
		break;
		default:
			LCD_ShowStr(34,8,"����");
	}
}

/***************************************************************************/
// ������ť���Ժ���
// ����������ֵ
// ����ֵ����
/***************************************************************************/
void TP_Response(uchar tpValue)
{
	Access_Page2(); //��ȡDDRAM2	
	switch(tpValue)
	{
		case 1:
			display_r_kuang(0,208,12,32,0);	
		break;
		case 2:
			display_r_kuang(13,208,13,32,0);
		break;
		case 3:
			display_r_kuang(27,208,12,32,0);
		break;
		case 4:
			display_r_kuang(27,208,12,32,0);
		break;
		case 11:
			display_r_kuang(20,12,7,48,0);
		break;
		case 12:
			display_r_kuang(29,12,7,48,0);
		break;
		case 13:
			display_r_kuang(14,208,12,32,0);
		break;
		case 14:
			display_r_kuang(27,208,12,32,0);
		break;
		case 15:
			display_r_kuang(27,208,12,32,0);
		break;
	}
}
