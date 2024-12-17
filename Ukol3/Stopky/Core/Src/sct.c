


#include "main.h"
#include "sct.h"

static const uint32_t reg_values[5][10] = {
		{
				//PCDE--------GFAB @ DIS1
				0b0111000000000111 << 16,
				0b0100000000000001 << 16,
				0b0011000000001011 << 16,
				0b0110000000001011 << 16,
				0b0100000000001101 << 16,
				0b0110000000001110 << 16,
				0b0111000000001110 << 16,
				0b0100000000000011 << 16,
				0b0111000000001111 << 16,
				0b0110000000001111 << 16,
		},

		{
				//----PCDEGFAB---- @ DIS2
				0b0000011101110000 << 0,
				0b0000010000010000 << 0,
				0b0000001110110000 << 0,
				0b0000011010110000 << 0,
				0b0000010011010000 << 0,
				0b0000011011100000 << 0,
				0b0000011111100000 << 0,
				0b0000010000110000 << 0,
				0b0000011111110000 << 0,
				0b0000011011110000 << 0,
		},

		{
				//PCDE--------GFAB @ DIS3
				0b0111000000000111 << 0,
				0b0100000000000001 << 0,
				0b0011000000001011 << 0,
				0b0110000000001011 << 0,
				0b0100000000001101 << 0,
				0b0110000000001110 << 0,
				0b0111000000001110 << 0,
				0b0100000000000011 << 0,
				0b0111000000001111 << 0,
				0b0110000000001111 << 0,
		},

		{
				//----43215678---- @ LED
				0b0000000000000000 << 16,
				0b0000000100000000 << 16,
				0b0000001100000000 << 16,
				0b0000011100000000 << 16,
				0b0000111100000000 << 16,
				0b0000111110000000 << 16,
				0b0000111111000000 << 16,
				0b0000111111100000 << 16,
				0b0000111111110000 << 16,
		},
		{
				//----43215678---- @ LED
				0b0000000000000000 << 16,
				0b0000000100000000 << 16,
				0b0000001000000000 << 16,
				0b0000010000000000 << 16,
				0b0000100000000000 << 16,
				0b0000000010000000 << 16,
				0b0000000001000000 << 16,
				0b0000000000100000 << 16,
				0b0000000000010000 << 16,
		},
};

void sct_init(void){

	sct_led(0);

}

void sct_led(uint32_t value){

	//uint8_t bit_out;
	//uint32_t LSB_mask = 0x0001;

	for(uint8_t i=0; i < sizeof(value) * 8; i++){

		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, value & 1);

		value >>= 1;

		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);

	}

	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);

}


void sct_value(uint16_t value, uint8_t led, uint8_t decPoint){

	uint32_t reg = 0;

	if(decPoint > 0 && decPoint <= 3)
	{
		switch(decPoint)
		{
		case 1:
			reg |= 0b1000000000000000 << 16;
			break;
		case 2:
			reg |= 0b0000100000000000 << 0;
			break;
		case 3:
			reg |= 0b1000000000000000 << 0;
			break;
		}
	}

	reg |= reg_values[0][value / 100 % 10];
	reg |= reg_values[1][value / 10  % 10];
	reg |= reg_values[2][value / 1   % 10];
	reg |= reg_values[3][led];

	sct_led(reg);

}

void sct_bargraph (uint8_t ledNum){

	uint32_t reg = 0;
	reg |= reg_values[4][ledNum];
	sct_led(reg);

}

//
void sct_universal_bargraph (uint8_t ledBinaryIndex){

	uint32_t reg = 0;
	for(uint8_t i = 1; i <=8; i++)
	{
		if(ledBinaryIndex & 0b1)
		{
			reg |= reg_values[4][i];
		}
		ledBinaryIndex >>= 1;
	}

	sct_led(reg);

}




