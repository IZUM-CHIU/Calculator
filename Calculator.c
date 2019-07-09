#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<fcntl.h>
#include<time.h>
#include<sys/ioctl.h>
#include<errno.h>

#include "asm/arch/lib/creator_pxa270_lcd.h"
#include "asm/arch/lib/def.h"
#include "creator_lib.h"

int conversion(int num, int ord_nota, int new_nota)
{
	int buf = 0, i;
	for(i=1;num>0;i=i*ord_nota)
	{
		buf += (num % new_nota) * i;
		num = num / new_nota;
	}
	return buf;
}

int main(int argc,char **argv)
{
	unsigned char sw, op, output;
	int fd, ret, len1, len2, nota, rst;
	unsigned int key, num1, num2, ans;
	_7seg_info_t data;
	lcd_write_info_t bg, user;

	fd=open("/dev/lcd",O_RDWR);
	if(fd<0){
		printf("open /dev/lcd error\n");
		return -1;
	}
	ioctl(fd, _7SEG_IOCTL_ON, NULL);
	_7SEG_put_led(fd, _7SEG_ALL, 0x0000);
	HUHU_put_led(fd, 0x00);
	ioctl(fd, KEY_IOCTL_CLEAR, &key);
	LCD_fClearScreen(fd);

	//1-------------------------------------Teaching Animation-----------------------------------------
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);
	
	LCD_Cursor(fd, 3, 4);
	bg.Count = sprintf((char*)bg.Msg, "+-------+      | TOUCH |      |ANY KEY|      +-------+");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);

	Delay(3000);
	//ioctl(fd, LCD_IOCTL_CLEAR, &key);
	while((ret = ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key)) < 0)sleep(1);
	//2
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 4, 10);
	bg.Count = sprintf((char*)bg.Msg, "Hi!            /");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	//ioctl(fd, LCD_IOCTL_CLEAR, &key);
	while((ret = ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key)) < 0)sleep(1);
	//3
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 4, 7);
	bg.Count = sprintf((char*)bg.Msg, "Welcome to     this stupid    Scientific     Calculator           \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	while(ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0)sleep(3);
	//4
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 0, 6);
	bg.Count = sprintf((char*)bg.Msg, "You can use    \"Binary\"&      \"Decimal\"&     \"Octonary\"&    \"Hexadecimal\"      /");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	while(ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0)sleep(3);
	//5
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 3, 9);
	bg.Count = sprintf((char*)bg.Msg, "'SWITCH' can    change them          \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	while(ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0)sleep(3);
	//6
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 0, 7);
	bg.Count = sprintf((char*)bg.Msg, "'1' for \"10\"   '2' for \"2\"    '3' for \"8\"    '4' for \"16\"       /");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	while(ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0)sleep(3);
	//7
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 2, 4);
	bg.Count = sprintf((char*)bg.Msg, "And 'KEY'      'A' for \"+\"    'B' for \"-\"    'C' for \"*\"    'D' for \"/\"    '#' for \"=\"    '*' for \"Del\"          \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	while(ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0)sleep(3);
	//8
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 0, 8);
	bg.Count = sprintf((char*)bg.Msg, "\"Hexadecimal\"  A~F=           'SWITCH5'1~6       /");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-Do o\\        /0|=w=|       d- |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	while(ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0)sleep(3);
	//9
	ioctl(fd, LCD_IOCTL_CLEAR, NULL);

	LCD_Cursor(fd, 1, 8);
	bg.Count = sprintf((char*)bg.Msg, "+-----------+  |Let's use!!|  +-----------+     /     \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	LCD_Cursor(fd, 0, 12);
	bg.Count = sprintf((char*)bg.Msg, "A-A         C-D> <\\        /0|=o=|       do |   /        / \\");
	ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
	
	Delay(3000);
	while(ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0)sleep(3);
	//-------------------------------------Teaching Animation-----------------------------------------
	
	while(1)
	{	
		//background
		ioctl(fd, LCD_IOCTL_CLEAR, NULL);

		LCD_Cursor(fd, 4, 3);
		bg.Count = sprintf((char*)bg.Msg, "+-------+      |RST on |      |SWITCH8|      +-------+");
		ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
		LCD_Cursor(fd, 1, 11);
		bg.Count = sprintf((char*)bg.Msg, "--------------H              D              O              B");
		ret = ioctl(fd, LCD_IOCTL_WRITE, &bg);
		//reset
		op = ' ';
		len1 = 0;
		len2 = 0;
		num1 = 0;
		num2 = 0;
		ans = 0;
		//get Positional notation
		nota = 0;
		rst = 0; 
		while(!nota)
		{
			DIPSW_get_sw(fd, &sw);
			
			switch(sw)
			{
				case 0xfe://10	
					_7SEG_put_led(fd, _7SEG_ALL, 0x0010);
					HUHU_put_led(fd, ~sw);
					nota = 10;
					break;	
				case 0xfd://2
					_7SEG_put_led(fd, _7SEG_ALL, 0x0002);
					HUHU_put_led(fd, ~sw);
					nota = 2;
					break;	
				case 0xfb://8	
					_7SEG_put_led(fd, _7SEG_ALL, 0x0008);
					HUHU_put_led(fd, ~sw);
					nota = 8;
					break;	
				case 0xf7://16	
					_7SEG_put_led(fd, _7SEG_ALL, 0x0016);
					HUHU_put_led(fd, ~sw);
					nota = 16;
					break;		
				default:
					_7SEG_put_led(fd, _7SEG_ALL, 0x0000);
					HUHU_put_led(fd, 0x00);
					break;
			}
		}
		//to calculation
		while(!rst)
		{
			//get input
			ioctl(fd, KEY_IOCTL_CLEAR, &key);
			while((ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key) < 0) && !rst)
			{
				sleep(1);	
				DIPSW_get_sw(fd, &sw);
				switch(sw)
				{	
					case 0xf7://16	
						_7SEG_put_led(fd, _7SEG_ALL, 0x0016);
						HUHU_put_led(fd, ~sw);
						break;		
					case 0xef://+16
						if(nota == 16)
						{
							_7SEG_put_led(fd, _7SEG_ALL, 0x0016);
							HUHU_put_led(fd, ~sw);
							data.Mode = _7SEG_MODE_PATTERN;
							data.Which = _7SEG_D6_INDEX;
							data.Value = 0x46;
							ioctl(fd, _7SEG_IOCTL_SET, &data);
						}
						break;
					case 0x7f://clean
						_7SEG_put_led(fd, _7SEG_ALL, 0x0000);
						HUHU_put_led(fd, ~sw);
						rst = 1;
						break;
				}
			}

			if(((key & 0xff) > 47) && ((key & 0xff) < 58))//0~9
			{
				if((sw == 0xef) && (nota == 16))//10~15
				{	
					switch(key&0xff)
					{
						case '1':
							num1 = num1*nota+10;
							break;
						case '2':
							num1 = num1*nota+11;
							break;
						case '3':
							num1 = num1*nota+12;
							break;
						case '4':
							num1 = num1*nota+13;
							break;
						case '5':
							num1 = num1*nota+14;
							break;
						case '6':
							num1 = num1*nota+15;
							break;
					}
				}
				else
					num1 = num1*nota+(key&0xff)-48;
				len1 = len1 + 1;
				//user input
				LCD_Cursor(fd, 15-len1, 10);
				if(nota == 16)
					user.Count = sprintf((char*)user.Msg, "%x", num1);
				else
					user.Count = sprintf((char*)user.Msg, "%d", conversion(num1, 10, nota));
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
			}
			else if(((key & 0xff) > 64) && ((key & 0xff) < 69))//get operator
			{
				switch(key&0xff)
				{
					case 'A':
						op = '+';	
						break;
					case 'B':
						op = '-';	
						break;
					case 'C':
						op = '*';	
						break;
					case 'D':
						op = '/';	
						break;
				}
				num2 = num1;
				num1 = 0;
				len2 = len1;
				len1 = 0;

				LCD_Cursor(fd, 0, 10);
				user.Count = sprintf((char*)user.Msg, "%c", op);
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
				//user input
				LCD_Cursor(fd, 15-len2, 9);
				if(nota == 16)
					user.Count = sprintf((char*)user.Msg, "%x", num2);
				else
					user.Count = sprintf((char*)user.Msg, "%d", conversion(num2, 10, nota));
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
				LCD_Cursor(fd, 1, 10);
				user.Count = sprintf((char*)user.Msg, "              ");
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
			}
			else if(((key & 0xff) == '*') && (num1 > 0))//delete
			{
				num1= num1/nota;
				len1 = len1 - 1;
				
				LCD_Cursor(fd, 1, 10);
				user.Count = sprintf((char*)user.Msg, "              ");
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
				if(len1 > 0)
				{
					//user input
					LCD_Cursor(fd, 15-len1, 10);
					if(nota == 16)
						user.Count = sprintf((char*)user.Msg, "%x", num1);
					else
						user.Count = sprintf((char*)user.Msg, "%d", conversion(num1, 10, nota));
					ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
				}
			}
			else if((key & 0xff) == '#')//out answer
			{
				switch(op)
				{
					case '+':
						ans = num2 + num1;	
						break;
					case '-':
						ans = num2 - num1;	
						break;
					case '*':
						ans = num2 * num1;	
						break;
					case '/':
						ans = num2 / num1;	
						break;
				}
				//hexadecimal
				LCD_Cursor(fd, 1, 12);
				user.Count = sprintf((char*)user.Msg, "%x", ans);
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
				//decimal
				LCD_Cursor(fd, 1, 13);
				user.Count = sprintf((char*)user.Msg, "%d", ans);
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
				//octonary
				LCD_Cursor(fd, 1, 14);
				user.Count = sprintf((char*)user.Msg, "%d", conversion(ans, 10, 8));
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
				//binary
				LCD_Cursor(fd, 1, 15);
				user.Count = sprintf((char*)user.Msg, "%d", conversion(ans, 10, 2));
				ret = ioctl(fd, LCD_IOCTL_WRITE, &user);
			}
		}
	}
	close(fd);
	return 0;
}
