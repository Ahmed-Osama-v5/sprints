/*
 * keypad.c
 *
 *  Created on: Mar 7, 2019
 *      Author: Ahmed
 */

#include <avr/io.h>
#include "keypad.h"

static  uint8_t debouncePA1(uint8_t mask)
{
  char ones=0, zeroes=0, i;
  for(i = 0; i < 70; i++){
    if(KEYPAD_PIN & mask){ // read pin == 1
      ones++;
    } else { // read pin == 0
      zeroes++;
    }

  }
  return (ones < zeroes);
}

 uint8_t GetKeyPressed()
{
	//static uint8_t  old_ch , timeupdate=0;
	uint8_t new_ch  ;
	//static uint8_t MaxWait=100 , ch_state_counter=0;
	//KEYPAD_DDR &= 0XC7;

	switch((KEYPAD_PIN & 0xF8))
	{
	case(LEFT_KEY):
		if(debouncePA1(LEFT_KEY));
		new_ch = LEFT;
		//*timeout = 0; // clears timeout counter
	  break;
	case(RIGHT_KEY):
		if(debouncePA1(RIGHT_KEY));
		new_ch = RIGHT ;
		//*timeout = 0; // clears timeout counter
	  break;
	case(UP_KEY):
		if(debouncePA1(UP_KEY));
		new_ch = UP ;
		//*timeout = 0; // clears timeout counter
	  break;
	case(DOWN_KEY):
	    if(debouncePA1(DOWN_KEY));
		new_ch = DOWN;
		//*timeout = 0; // clears timeout counter
	  break;
	case(OK_KEY):
	    if(debouncePA1(OK_KEY));
		new_ch = OK;
		//*timeout = 0; // clears timeout counter
	  break;
	default:
		new_ch = (KEYPAD_PIN & 0xF8);
	  break;

	}
/*
	if((old_ch == new_ch) && (timeupdate < MaxWait) ){
	timeupdate++;

	return 0xff;
	}
	else  {
		if( old_ch == new_ch )
			{
			   ch_state_counter++;
			 }
		else {
			   old_ch = new_ch;
			   ch_state_counter=0;
			 }
	   if(ch_state_counter > 4)
			MaxWait=35;
	   else MaxWait=70;

	   timeupdate = 0;
	}*/
	return new_ch;//Indicate No key pressed

	}

