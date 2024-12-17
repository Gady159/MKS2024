/*
 * sct.h
 *
 *  Created on: Oct 9, 2024
 *      Author: 240612
 */


#ifndef SRC_SCT_H_
#define SRC_SCT_H_

void sct_init(void);

void sct_led(uint32_t value);

void sct_value(uint16_t value, uint8_t led, uint8_t decPoint);

void sct_bargraph (uint8_t ledNum);

void sct_universal_bargraph (uint8_t ledBinaryIndex);

#endif /* SRC_SCT_H_ */


