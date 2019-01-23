#define F_CPU 8000000UL                    /* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>                        /* Include AVR std. library file */
#include <util/delay.h>                    /* Include inbuilt defined Delay header file */

#define LCD_Dir  DDRA                    /* Define LCD data port direction */
#define LCD_Port PORTA                    /* Define LCD data port */
#define RS PA1                            /* Define Register Select (data reg./command reg.) signal pin */
#define EN PA3                             /* Define Enable signal pin */
 

void LCD_Command( unsigned char cmnd )
{
    LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
    LCD_Port &= ~ (1<<RS);                /* RS=0, command reg. */
    LCD_Port |= (1<<EN);                /* Enable pulse */
    _delay_us(1);
    LCD_Port &= ~ (1<<EN);

    _delay_us(200);

    LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
    LCD_Port |= (1<<EN);
    _delay_us(1);
    LCD_Port &= ~ (1<<EN);
    _delay_ms(2);
}


void LCD_Char( unsigned char data )
{
    LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
    LCD_Port |= (1<<RS);                /* RS=1, data reg. */
    LCD_Port|= (1<<EN);
    _delay_us(1);
    LCD_Port &= ~ (1<<EN);

    _delay_us(200);

    LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
    LCD_Port |= (1<<EN);
    _delay_us(1);
    LCD_Port &= ~ (1<<EN);
    _delay_ms(2);
}

void LCD_Init (void)                    /* LCD Initialize function */
{
    LCD_Dir = 0xFF;                        /* Make LCD command port direction as o/p */
    _delay_ms(20);                        /* LCD Power ON delay always >15ms */
    
    LCD_Command(0x33);
    LCD_Command(0x32);                    /* send for 4 bit initialization of LCD  */
    LCD_Command(0x28);                  /* Use 2 line and initialize 5*7 matrix in (4-bit mode)*/
    LCD_Command(0x0c);                  /* Display on cursor off*/
    LCD_Command(0x06);                  /* Increment cursor (shift cursor to right)*/
    LCD_Command(0x01);                  /* Clear display screen*/
    _delay_ms(2);
    LCD_Command (0x80);                    /* Cursor 1st row 0th position */
}


void LCD_String (char *str)                /* Send string to LCD function */
{
    int i;
    for(i=0;str[i]!=0;i++)                /* Send each char of string till the NULL */
    {
        LCD_Char (str[i]);
    }
}

void LCD_String_xy (char row, char pos, char *str)    /* Send string to LCD with xy position */
{
    if (row == 0 && pos<16)
    LCD_Command((pos & 0x0F)|0x80);        /* Command of first row and required position<16 */
    else if (row == 1 && pos<16)
    LCD_Command((pos & 0x0F)|0xC0);        /* Command of first row and required position<16 */
    LCD_String(str);                    /* Call LCD string function */
}

void LCD_Clear()
{
    LCD_Command (0x01);                    /* Clear display */
    _delay_ms(2);
    LCD_Command (0x80);                    /* Cursor 1st row 0th position */
}

void mult(int a,int b){
	int c=0;
	c=a*b;
	// LCD_Command((0 & 0x0F)|0xC0); 
	 LCD_String("=");
     //LCD_Char(48+ c);
	 char temp[20];
	 sprintf(temp , "%d" , c);
	LCD_String(temp);
	// LCD_Clear();

}
void add(int a,int b){
	int c=0;
	c=a+b;
	// LCD_Command((0 & 0x0F)|0xC0); 
	 LCD_String("=");
    // LCD_Char(48+ c);
	char temp[20];
	 sprintf(temp , "%d" , c);
	 LCD_String(temp);
	// LCD_Clear();

}
void div(int a,int b){
	int c=0;
	c=a/b;
	 //LCD_Command((0 & 0x0F)|0xC0); 
	 LCD_String("=");
   //  LCD_Char(48+ c);
   char temp[20];
	 sprintf(temp , "%d" , c);
	 LCD_String(temp);
	 //LCD_Clear();

}
void min(int a,int b){
	int c=0;
	c=a-b;
//	 LCD_Command((0 & 0x0F)|0xC0); 
	 LCD_String("=");
   //  LCD_Char(48+ c);
   char temp[20];
	 sprintf(temp , "%d" , c);
	 LCD_String(temp);
	// LCD_Clear();

}
 
int main()
{
    DDRC =  0b11100000;
    PORTC = 0b11111111;

    LCD_Init();
    
    //LCD_String("Hello world!");
    int sum=0;
	int flag=0;
	int sum2=0;
	int a=0;

	
    while (1){


        PORTC = 0b01111111;
		_delay_ms(10);
        if ( (PINC & 0b00000001) == 0 ){
           // LCD_Command((0 & 0x0F)|0xC0); 
            LCD_String("1");
			//LCD_String_xy(1,0,'3');
			if(flag==0)
			sum=(sum*10) + 1;
			else
			sum2=(sum2 * 10)+1;
        }
        if ( (PINC & 0b00000010) == 0 ){
           // LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'4');        
            LCD_String("4");
			if(flag==0)
			sum=(sum*10) + 4;
			else
			sum2=(sum2 * 10)+4;
        }
        if ( (PINC & 0b00000100) == 0 ){
           // LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'7');        
            LCD_String("7");
			if(flag==0)
			sum=(sum*10) + 7;
			else
			sum2=(sum2 * 10)+7;
        }
		 if ( (PINC & 0b00001000) == 0 ){
           // LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'7');        
            LCD_String("*");
			flag=1;
			a++;
        }

        PORTC = 0b10111111;
		_delay_ms(10);
        if ( (PINC & 0b00000001) == 0 ){
          //  LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'1');        
            LCD_String("2");
			if(flag==0)
			sum=(sum*10) + 2;
			else
			sum2=(sum2 * 10)+2;
        }
        if ( (PINC & 0b00000010) == 0 ){
          //  LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'5');        
            LCD_String("5");
			if(flag==0)
			sum=(sum*10) + 5;
			else
			sum2=(sum2 * 10)+5;
        }
        if ( (PINC & 0b00000100) == 0 ){
           // LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'8');        
            LCD_String("8");
			if(flag==0)
			sum=(sum*10) + 8;
			else
			sum2=(sum2 * 10)+8;
        }
        if ( (PINC & 0b00001000) == 0 ){
          //  LCD_Command((0 & 0x0F)|0xC0);
		    //LCD_String_xy(1,0,'0');        
            LCD_String("0");
			if(flag==0)
			sum=(sum*10) + 0;
			else
			sum2=(sum2 * 10)+0;
        }
        
        PORTC = 0b11011111;
		_delay_ms(10);

        if ( (PINC & 0b00000001) == 0 ){
           // LCD_Command((0 & 0x0F)|0xC0);  
			//LCD_String_xy(1,0,'2');      
            LCD_String("3");
			if(flag==0)
			sum=(sum*10) + 3;
			else
			sum2=(sum2 * 10)+3;
        }
        if ( (PINC & 0b00000010) == 0 ){
          //  LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'6');        
            LCD_String("6");
			if(flag==0)
			sum=(sum*10) + 6;
			else
			sum2=(sum2 * 10)+6;
        }
        if ( (PINC & 0b00000100) == 0 ){
          //  LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'9');        
            LCD_String("9");
			if(flag==0)
			sum=(sum*10) + 9;
			else
			sum2=(sum2 * 10)+9;
        }
		if ( (PINC & 0b00001000) == 0 ){
         //   LCD_Command((0 & 0x0F)|0xC0);
			//LCD_String_xy(1,0,'6');        
            //LCD_String("=");
			flag=0;
			int m=sum;
			int v=sum2;
			sum=0;
			sum2=0;
			
			if(a==1)
			mult(m,v);
			if(a==2)
			add(m,v);
			if(a==3)
			div(m,v);
			if(a==4)
			min(m,v);
			a=0;
			sum=0;
			sum2=0;
 			_delay_ms(80);
			LCD_Clear();

        
    } 

	}

	return 0 ;
}




    
	/*

   	while (1){
        PORTC = 0b01111111;
		_delay_ms(50);
        if ( (PINC & 0b00010000) == 0b00000000 ){
            LCD_String_xy(1,0,'3');
        }
        if ( (PINC & 0b00001000) == 0b00000000 ){
            LCD_String_xy(1,0,'4');
        }
        if ( (PINC & 0b00000100) == 0b00000000 ){
            LCD_String_xy(1,0,'7');
        }

        PORTC = 0b10111111;
		_delay_ms(50);
        if ( (PINC & 0b00010000) == 0b00000000 ){
            LCD_String_xy(1,0,'1');
        }
        if ( (PINC & 0b00001000) == 0b00000000 ){
            LCD_String_xy(1,0,'5');
        }
        if ( (PINC & 0b00000100) == 0b00000000 ){
            LCD_String_xy(1,0,'8');
        }
        if ( (PINC & 0b00000010) == 0b00000000 ){
            LCD_String_xy(1,0,'0');
        }
        
        PORTC = 0b11011111;
		_delay_ms(50);
        if ( (PINC & 0b00010000) == 0b00000000 ){
            LCD_String_xy(1,0,'2');
        }
        if ( (PINC & 0b00001000) == 0b00000000 ){
            LCD_String_xy(1,0,'6');
        }
        if ( (PINC & 0b00000100) == 0b00000000 ){
            LCD_String_xy(1,0,'9');
        }

        
    }
	*/

	

