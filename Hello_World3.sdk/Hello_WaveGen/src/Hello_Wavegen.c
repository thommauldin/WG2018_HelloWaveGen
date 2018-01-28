/*
 * /*
 * Hello_Wavegen.c
 *
 *  Created on: Nov 6, 2017
 *      Author: Thomas
 */

#include<stdio.h>
#include<xgpio.h>						// Obtain from https://github.com/Xilinx/embeddedsw
#include<xparameters.h>
#include "platform.h"
#include "xil_printf.h"
XGpio e,rs,rw,lcd_data,keypad;

/********************************Declare Functions************************************/
/*
 * Precondition: None
 * Postcondition: The Program is delayed by 1.17 X 10^-7s*input parameter
 */
void delay(int counter)
{
       while(counter) counter--;
}

/*
 * Precondition: Ports are set up, delay function declared, XGPIO header included
 * Postcondition: LCD display receives a command
 */
void lcd_command(char i)
{
     XGpio_DiscreteWrite(&lcd_data,1,i);
     XGpio_DiscreteWrite(&rs, 1, 0);
     XGpio_DiscreteWrite(&rw,1,0);						// Setup the LCD to read from FPGA
     XGpio_DiscreteWrite(&e, 1, 1);
     delay(100000);										// wait 1ms
     XGpio_DiscreteWrite(&e, 1, 0);
}

/*
 * Precondition: Ports are set up, delay function declared, XGPIO header included
 * Postcondition: LCD display will display a string
 */
void lcd_write(char *string, int c)						// Write a string to LCD
{
	  int i;
	  for (i=0; i < c; i++)								// c = number of characters, i = counter
	  {
      XGpio_DiscreteWrite(&lcd_data, 1,string[i]);
      XGpio_DiscreteWrite(&rs, 1, 1);
      XGpio_DiscreteWrite(&rw,1,0);						// Setup the LCD to read from FPGA
      XGpio_DiscreteWrite(&e, 1, 1);
      delay(100000);									// wait 1ms
      XGpio_DiscreteWrite(&e, 1, 0);
	  }
}

/*
 * Precondition: Ports are set up, delay function declared, XGPIO header included
 * Postcondition: LCD display will display a single character
 */
void lcd_write_char(char i)								// Write a character to LCD
{

      XGpio_DiscreteWrite(&lcd_data, 1,i);
      XGpio_DiscreteWrite(&rs, 1, 1);
      XGpio_DiscreteWrite(&rw,1,0);						// Setup the LCD to read from FPGA
      XGpio_DiscreteWrite(&e, 1, 1);
      delay(100000);									// wait 1ms
      XGpio_DiscreteWrite(&e, 1, 0);
}

/*
 * Precondition: 20X4 display used
 * Postcondition: LCD display cursor will be placed based on its row and column number
 */
void cursor(int row, int column)
{
      if(row==1)
      		lcd_command(0x80|(column-1));
      if (row==2)
      		lcd_command(0x80|(0x40+(column-1)));
	  if (row==3)
      		lcd_command(0x80|(0x14+(column-1)));
      if (row==4)
      		lcd_command(0x80|(0x54+(column-1)));
}

/*
 * Precondition: GPIO inputs are received from a keypad
 * Postcondition: Index is either incremented or decremented
 */
int leftRight(int key, int index, int row)
{
	int x;
	x = index;
	if (key == 2)										// Left selected
	{
		x = x - 1;
	} else if (key == 1) {								// Right selected
		x = x + 1;
	}
	if (row == 1)										// Check frequency index limits (1-16)
		{
			if (x == 0)
			{
				x = 16;
			} else if (x >= 17) {
				x = 1;
			}
		} else if (row == 2) {						// Check amplitude index limits (1-7)
			if (x == 0)
			{
				x = 7;
			} else if (x >= 8) {
				x = 1;
			}
		} else if (row == 3) {						// Check bank index limits (1-4)
			if (x == 0)
			{
				x = 4;
			} else if (x >= 5) {
				x = 1;
			}
		}
	return x;
}

/*
 * Precondition: None
 * Postcondition: The frequency is cycled
 */
char * cycleFreq(int freqCycle)
{
	if (freqCycle == 1)
	{
		return "1Hz   ";
	} else if (freqCycle == 2) {
		return "2Hz   ";
	} else if (freqCycle == 3) {
		return "5Hz   ";
	}else if (freqCycle == 4) {
		return "10Hz  ";
	}else if (freqCycle == 5) {
		return "20Hz  ";
	}else if (freqCycle == 6) {
		return "50Hz  ";
	}else if (freqCycle == 7) {
		return "100Hz ";
	}else if (freqCycle == 8) {
		return "200Hz ";
	}else if (freqCycle == 9) {
		return "500Hz ";
	}else if (freqCycle == 10) {
		return "1kHz  ";
	}else if (freqCycle == 11) {
		return "2kHz  ";
	}else if (freqCycle == 12) {
		return "5kHz  ";
	}else if (freqCycle == 13) {
		return "10kHz ";
	}else if (freqCycle == 14) {
		return "20kHz ";
	}else if (freqCycle == 15) {
		return "50kHz ";
	}else if (freqCycle == 16) {
		return "100kHz";
	} else {
		return "1Hz   ";
	}
}

/*
 * Precondition: None
 * Postcondition: The amplitude is cycled
 */
char * cycleAmp(int ampCycle)
{
	if (ampCycle == 1)
	{
		return "0.1V";
	} else if (ampCycle == 2) {
		return "0.2V";
	} else if (ampCycle == 3) {
		return "0.5V";
	} else if (ampCycle == 4) {
		return "1V  ";
	} else if (ampCycle == 5) {
		return "2V  ";
	} else if (ampCycle == 6) {
		return "5V  ";
	}else if (ampCycle == 7) {
		return "10V ";
	} else {
		return "0.1V";
	}
}

/*
 * Precondition: None
 * Postcondition: The bank is cycled
 */
char cycleBank(int bankCycle)
{
	if (bankCycle == 1)
	{
		return 'A';
	} else if (bankCycle == 2) {
		return 'B';
	} else if(bankCycle ==3) {
		return 'C';
	} else if (bankCycle == 4) {
		return 'D';
	} else {
		return 'A';
	}
}

/*
 * Precondition: LCD display has been initialized
 * Postcondition: The cursor is moved if up or down is selected on the keypad, the resulting row is returned
 */
int upDown(int key, int row)				// Check if up or down was selected on the keypad
{
	 int x;
	 x = row;
	 if (key == 8)							// Up selected
	 {
		 if (x == 1)
		 {
	      	x = 4;
	      	cursor(4,1);
		 } else if (x == 2) {
			x = 1;
			cursor(1,1);
		 } else if (x == 3) {
	        x = 2;
	        cursor(2,1);
	     } else {
	    	x = 3;
	        cursor(3,1);
	     }
	  } else if (key == 4) {				// Down selected
		if (x == 1)
		{
			x = 2;
			cursor(2,1);
		} else if (x == 2) {
			x = 3;
			cursor(3,1);
		} else if (x == 3) {
		    x = 4;
		    cursor(4,1);
		} else {
			x = 1;
		    cursor(1,1);
		}
	}
	return x;
}

/*
 * Precondition: The cursor is on a row that can be selected
 * Postcondition: return a new screen to be displayed if select was used
 */
char enter(int key, int row, int i)
{
	if (key == 10)
	{
		if (i == 1)								// Called by main menu
		{
			if (row == 3)						// Bank was selected
			{
				return 'B';						// Initialize bank detail screen
			} else if(row == 4) {				// Options was selected
				return 'O';						// Initialize options screen
			}
		} else if (i == 2) {
			return 'H';							// Return the selected bank to the main menu
		}
	}
	if ( i == 1)
	{
		return 'H';								// Return to the main menu if nothing was selected on main menu
	} else if (i == 2) {
		return 'B';								// Return to the bank menu if nothing was selected on bank menu
	}
}												// Caution does not impact the software

/*
 * Precondition: None
 * Postcondition: If home is selected, return to the home screen. If home is not selected,
 * 				  return to the previous screen.
 */
char return_home(int key, char display)
{
	if (key == 5 || display == 'H') 			// The home button was pressed or a bank was selected
	{
		return 'H';
	} else if (display == 'B') {
		return 'B';
	} else if (display == 'O'){
		return 'O';
	} else {
		return 'L';
	}
}

/*
 * Precondition: None
 * Postcondition: if the frequency has been changed, the display is updated
 */
void updateFrequency(char *frequency1, char *frequency2)
{
	   if (frequency1[0] != frequency2[0] || frequency1[1] != frequency2[1])
	   {
		   frequency1[0] = frequency2[0];
		   frequency1[1] = frequency2[1];
		   frequency1[2] = frequency2[2];
		   frequency1[3] = frequency2[3];
		   frequency1[4] = frequency2[4];
		   frequency1[5] = frequency2[5];
		   cursor(1,15);
		   lcd_write(frequency1,6);
		   cursor(1,1);					// Set cursor back to the F in Frequency
	   }
}

/*
 * Precondition: None
 * Postcondition: if the amplitude has been changed, the display is updated
 */
 void updateAmplitude(char *amplitude1, char *amplitude2)
{
	   if (amplitude1[0] != amplitude2[0] || amplitude1[2] != amplitude2[2])
	   {
		   amplitude1[0] = amplitude2[0];
		   amplitude1[1] = amplitude2[1];
		   amplitude1[2] = amplitude2[2];
		   amplitude1[3] = amplitude2[3];
		   cursor(2,15);
		   lcd_write(amplitude1,4);
		   cursor(2,1);					// Set cursor back to the A in Amplitude
	   }
}

/*
 * Precondition: None
 * Postcondition: if the bank has been changed, the display is updated
 */
char updateBank(char bank1, char bank2)
{
	   if (bank1 != bank2)
	   {
		   bank1 = bank2;
		   cursor(3,15);
		   lcd_write_char(bank1);
		   cursor(3,1);					// Set cursor back to the B in Bank
	   }
	   return bank1;
}

/*
 * Precondition: The LCD display has been initialized
 * Postcondition: The LCD display will display the main menu
 */
void home(char *frequency, char *amplitude, char bank)
{
	   lcd_write("Frequency", 9);
	   cursor(1,15);
	   lcd_write(frequency, 6);
	   cursor(2,1);
	   lcd_write("Amplitude", 9);
	   cursor(2,15);
	   lcd_write(amplitude, 4);
	   cursor(3,1);
	   lcd_write("Bank", 4);
	   cursor(3,15);
	   lcd_write_char(bank);
	   cursor(4,1);
	   lcd_write("Options", 7);
}

/*
 * Precondition: Options is selected on the main menu
 * Postcondition: The LCD display will display the options menu
 */
void options(void)
{
	   cursor(1,1);
	   lcd_write("Reserved for future",19);
	   cursor(3,9);
	   lcd_write("use", 3);
}

/*
 * Precondition: Bank has been selected on the main menu or the cursor is on A in the bank detail menu
 * Postcondition: The LCD display will display the bank detail menu for bank A
 */

void bankA(void)
{
        lcd_command(0x01);						// Clear screen
		lcd_write("A ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("Sine", 4);					// Bank A CH1 output name
		cursor(1,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("Square", 6);					// Bank A CH5 output name
		cursor(2,1);
		lcd_write("B ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("DC", 2);						// Bank A CH2 output name
		cursor(2,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("Triangle", 8);				// Bank A CH6 output name
		cursor(3,1);
		lcd_write("C ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("Sinc", 4);					// Bank A CH3 output name
		cursor(3,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("Sawtooth", 8);				// Bank A CH7 output name
		cursor(4,1);
		lcd_write("D ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("Noise", 5);					// Bank A CH4 output name
		cursor(4,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("Heart", 5);					// Bank A CH8 output name
		cursor(1,1);
}

/*
 * Precondition: Bank has been selected on the main menu and the user is on bank B
 * Postcondition: The LCD display will display the bank detail menu for bank B
 */

void bankB(void)
{
        lcd_command(0x01);						// Clear screen
		lcd_write("A ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh1", 8);				// Bank B CH1 output name
		cursor(1,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh5", 8);				// Bank B CH5 output name
		cursor(2,1);
		lcd_write("B ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh2", 8);				// Bank B CH2 output name
		cursor(2,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh6", 8);				// Bank B CH6 output name
		cursor(3,1);
		lcd_write("C ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh3", 8);				// Bank B CH3 output name
		cursor(3,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh7", 8);				// Bank B CH7 output name
		cursor(4,1);
		lcd_write("D ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh4", 8);				// Bank B CH4 output name
		cursor(4,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankBCh8", 8);				// Bank B CH8 output name
		cursor(2,1);
}

/*
 * Precondition: Bank has been selected on the main menu and the user is on C
 * Postcondition: The LCD display will display the bank detail menu for bank C
 */

void bankC(void)
{
        lcd_command(0x01);						// Clear screen
		lcd_write("A ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh1", 8);				// Bank C CH1 output name
		cursor(1,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh5", 8);				// Bank C CH5 output name
		cursor(2,1);
		lcd_write("B ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh2", 8);				// Bank C CH2 output name
		cursor(2,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh6", 8);				// Bank C CH6 output name
		cursor(3,1);
		lcd_write("C ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh3", 8);				// Bank C CH3 output name
		cursor(3,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh7", 8);				// Bank C CH7 output name
		cursor(4,1);
		lcd_write("D ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh4", 8);				// Bank C CH4 output name
		cursor(4,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankCCh8", 8);				// Bank C CH8 output name
		cursor(3,1);
}

/*
 * Precondition: Bank has been selected on the main menu and the user is on D
 * Postcondition: The LCD display will display the bank detail menu for bank D
 */

void bankD(void)
{
        lcd_command(0x01);						// Clear screen
		lcd_write("A ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh1", 8);				// Bank D CH1 output name
		cursor(1,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh5", 8);				// Bank D CH5 output name
		cursor(2,1);
		lcd_write("B ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh2", 8);				// Bank D CH2 output name
		cursor(2,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh6", 8);				// Bank D CH6 output name
		cursor(3,1);
		lcd_write("C ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh3", 8);				// Bank D CH3 output name
		cursor(3,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh7", 8);				// Bank D CH7 output name
		cursor(4,1);
		lcd_write("D ", 2);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh4", 8);				// Bank D CH4 output name
		cursor(4,12);
		lcd_write_char(0xA5);					// Bullet Point
		lcd_write("BankDCh8", 8);				// Bank D CH8 output name
		cursor(4,1);
}

/*
 * Precondition: The bank menu is displayed
 * Postcondition: If the row is changed, the bank details change
 */
char bank_details(int row, char bank1, char bank2)
{
	 if (row == 1)					// Bank A
	 {
	   bank2 = 'A';					// Cursor on A
	   if (bank1 != bank2)
	   {
		   bankA();					// Update screen to show bank A details
		   bank1 = bank2;			// Change reference bank
	   }
	 } else if (row == 2) {
	   bank2 = 'B';					// Cursor on B
	   if (bank1 != bank2)
	   {
	    bankB();					// Update screen to show bank B details
	    bank1 = bank2;				// Change reference bank
	   }
	 } else if (row == 3) {
	   bank2 = 'C';					// Cursor on C
	   if (bank1 != bank2)
	   {
		   bankC();					// Update screen to show bank C details
		   bank1 = bank2;			// Change reference bank
	   }
	 } else if (row == 4) {
	   bank2 = 'D';					// Cursor on D
	   if (bank1 != bank2)
	   {
	      bankD();					// Update screen to show bank D details
	      bank1 = bank2;			// Change reference bank
	   }
	 }
	 return bank2;
}

/*
 * Precondition: The bank is being changed from the bank menu
 * Postcondition: The bank on the main screen is synced with the bank selected on the bank menu
 */
int sync_bank(char bank2)
{
	if (bank2 == 'A')
	{
		return 1;
	} else if (bank2 == 'B') {
		return 2;
	} else if (bank2 == 'C') {
		return 3;
	} else {
		return 4;
	}
}

/*
 * Precondition: Bank menu is loaded
 * Postcondition: The correct details are loaded for the selected bank on the main menu and the row
 * 				  is adjusted accordingly
 */
int correct_bank(char bank2)
{
	   if (bank2 == 'A')
	   {
		   bankA();
		   return 1;
	   } else if (bank2 == 'B') {
		   bankB();
		   return 2;
	   } else if (bank2 == 'C') {
		   bankC();
		   return 3;
	   } else {
		   bankD();
		   return 4;
	   }
}

/*
 * Precondition: There is a problem with the switch function
 * Postcondition: "ERROR" is displayed on the display and the program ends
 */
void error(void)
{
	   lcd_write("ERROR", 5);
}

/*
 * Precondition: The device was powered on
 * Postcondition: A startup screen is shown for 2s
 */
void welcome_screen(void)
{
	cursor(2,1);
	lcd_write("AstroNova",9);
	cursor(3,1);
	lcd_write("Test & Measurement",18);
	delay(18000000);							// delay 2s
}

/*
 * Precondition: A low battery signal was received
 * Postcondition: The user is prompted to charge the device
 */
void low_battery(void)
{
	cursor(1,1);
	lcd_write("Battery low-Turn off",20);
	cursor(2,1);
	lcd_write("power or apply",14);
	cursor(3,1);
	lcd_write("external voltage as",19);
	cursor(4,1);
	lcd_write("soon as possible",16);
}

/*
 * Precondition: Hardware has been described in Vivado
 * Postcondition: The LCD is initialized
 */
void gpio_init (void)
{
     XGpio_Initialize(&e, XPAR_AXI_GPIO_1_DEVICE_ID);
     XGpio_Initialize(&rs, XPAR_AXI_GPIO_2_DEVICE_ID);
     XGpio_Initialize(&rw, XPAR_AXI_GPIO_0_DEVICE_ID);
     XGpio_Initialize(&lcd_data, XPAR_AXI_GPIO_3_DEVICE_ID);
     XGpio_Initialize(&keypad, XPAR_AXI_GPIO_4_DEVICE_ID);
//     XGpio_Initialize(&low_battery, XPAR_AXI_GPIO_5_DEVICE_ID);
     /*Set the GPIOs as output*/
     XGpio_SetDataDirection(&e,1,0);
     XGpio_SetDataDirection(&rs,1,0);
     XGpio_SetDataDirection(&rw,1,0);
     XGpio_SetDataDirection(&lcd_data,1,0);
     /*Set the GPIOs as input*/
     XGpio_SetDataDirection(&keypad,1,1);
//     XGpio_SetDataDirection(&low_battery,1,1);
}

/********************************Main Program************************************/

int main(void)
{
	   // Declare Variables
	   int freqCycle = 1;
	   int ampCycle = 1;
	   int bankCycle = 1;
	   int row = 1;
	   int dummy = 2;
	   int key;
	   char frequency1[6];
	   char *frequency2 = "1Hz   ";
	   char amplitude1[4];
	   char *amplitude2 = "0.1V";
	   char bank1 = 'A';
	   char bank2 = 'A';
	   char display = 'H';

	   // Set up display
       gpio_init();
       XGpio_DiscreteWrite(&e, 1, 0);
       delay(4500000);					// wait >40ms
       lcd_command(0x30);				// wake up 1
       delay(500000);					// wait 5ms
       lcd_command(0x30);				// wake up 2
       delay(1600);						// wait 160us
       lcd_command(0x30);				// wake up 3
       delay(1600);						// wait 160us
       lcd_command(0x38);				// Function set: 8-bit / 4 rows
       lcd_command(0x0D);				// Display ON; Blink ON
       lcd_command(0x06);				// Entry Mode Set
	   lcd_command(0x01);				// Clear screen
       welcome_screen();				// Display the startup screen

       while (dummy < 5)
       {
       switch (display)
       {
       	   case 'H': 									// Home Screen
       	       lcd_command(0x01);						// Clear screen
       	       home(frequency2, amplitude2, bank2);		// Initialize home menu
       		   cursor(1,1);								// Set cursor back to the start
      		   while (display == 'H')
      		   {
     				   key = XGpio_DiscreteRead(&keypad,1);
     				   if (key == 12)
     				   {
     					   display = 'L';				// Battery is low
     					   break;
     				   }
      				   row = upDown(key, row);
     				   delay(500000);					// Delay 5ms
      				   if (row == 1)
      				   {
          				   freqCycle = leftRight(key, freqCycle, 1);
      					   frequency2 = cycleFreq(freqCycle);
      					   updateFrequency(frequency1, frequency2);
      				   } else if (row == 2) {
          				   ampCycle = leftRight(key, ampCycle, 2);
      					   amplitude2 = cycleAmp(ampCycle);
      					   updateAmplitude(amplitude1, amplitude2);
      				   } else if (row == 3) {
          				   bankCycle = leftRight(key, bankCycle, 3);
      					   bank2 = cycleBank(bankCycle);
      					   bank1 = updateBank(bank1, bank2);
      					   display = enter(key, row, 1);
      				   } else if (row == 4) {
      					   display = enter(key,row, 1);
      				   }
     				   delay(800000);					// Delay 8ms for debounce (total of 13ms)
      		   }
       		   break;
       	   case 'B':									// Bank Screen
       		   row = correct_bank(bank2);
      		   while (display == 'B')
      		   {
     				   key = XGpio_DiscreteRead(&keypad,1);
     				   if (key == 12)
     				   {
     					   display = 'L';				// Battery is low
     					   break;
     				   }
      				   row = upDown(key, row);
     				   delay(500000);					// Delay 5ms
     				   bank2 = bank_details(row,bank2,bank2);
     				   bankCycle = sync_bank(bank2);
     				   display = enter(key,row,2);
     				   display = return_home(key,display);
      		   }
       		   break;
       	   case 'O':									// Options screen
       		   lcd_command(0x01);						// Clear screen
   			   options();
       		   while (display == 'O')
       		   {
       			   key = XGpio_DiscreteRead(&keypad,1);
 				   if (key == 12)
 				   {
 					   display = 'L';					// Battery is low
 					   break;
 				   }
       			   display = return_home(key,display);
       		   }
       		   break;
       	   case 'L':									// Low battery screen
       		   lcd_command(0x01);						// Clear screen
       		   low_battery();							// The battery needs to be charged
       		   while (display == 'L')
       		   {
       			   key = XGpio_DiscreteRead(&keypad,1);
       			   display = return_home(key,display);
       		   }
       		   break;
       	   default:
     		   error();
       		   dummy = 10;
       		   break;									// End program
       }
       }

// For Debug use only
       init_platform();

       print("Hello");

       cleanup_platform();

       return 0;
}

