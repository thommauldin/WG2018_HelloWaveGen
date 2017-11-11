/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#include<stdio.h>
#include<xparameters.h>
#include<xgpio.h>
XGpio e,rs,rw,lcd_data;
char reverse(char data)
{
     int i;
     int temp1;
     int temp2=0;
     for(i=0;i<8;i++)
     {
         temp1 = (data>>i)&1;
         temp2+= temp1 << (7-i);
     }
     return temp2;
}

void delay(int counter)
{
       while(counter) counter--;
}

void gpio_init (void)
{
    XGpio_Initialize(&e, XPAR_AXI_GPIO_1_DEVICE_ID);
    XGpio_Initialize(&rs, XPAR_AXI_GPIO_2_DEVICE_ID);
    XGpio_Initialize(&rw, XPAR_AXI_GPIO_0_DEVICE_ID);
    XGpio_Initialize(&lcd_data, XPAR_AXI_GPIO_3_DEVICE_ID);
     /*Set the all GPIOs as output*/
     XGpio_SetDataDirection(&e,1,0);
     XGpio_SetDataDirection(&rs,1,0);
     XGpio_SetDataDirection(&rw,1,0);
     XGpio_SetDataDirection(&lcd_data,1,0);
}
void lcd_command(char i)
{
     XGpio_DiscreteWrite(&lcd_data,1,reverse(i));
     XGpio_DiscreteWrite(&rs, 1, 0);
     XGpio_DiscreteWrite(&e, 1, 1);
     XGpio_DiscreteWrite(&e, 1, 0);
     delay(200000);
}

void lcd_write(char i)
{
      XGpio_DiscreteWrite(&lcd_data, 1, reverse(i));
      XGpio_DiscreteWrite(&rs, 1, 1);
      XGpio_DiscreteWrite(&e, 1, 1);
      XGpio_DiscreteWrite(&e, 1, 0);
      delay(200000);
}

void cursor(int row, int column)
{
      if(row==1)
            lcd_command(0x80|(column-1));
      if (row==2)
           lcd_command(0x80|(0x40+(column-1)));
}

int main(void)
{
       gpio_init();
       XGpio_DiscreteWrite(&rw,1,0);
       delay(20000);
       lcd_command(0x38);
       lcd_command(0x01);
       lcd_command(0x06);
       lcd_command(0x0F);

       lcd_write('F');
       lcd_write('P');
       lcd_write('G');
       lcd_write('A');
       cursor(2,1);
       lcd_write('C');
       lcd_write('E');
       lcd_write('N');
       lcd_write('T');
       lcd_write('E');
       lcd_write('R');
       return 0;
}
