/*
 * ds1307.h
 * 
 * Created on: 28.10.2023
 * Author: rRaufToprak
*/

#ifndef DS1307_H
#define DS1307_H

#include "main.h"

#define DS1307ADDR 0x68<<1
#define DS1307I2C &hi2c1
#define SECONDS 0x00
#define MINUTES 0x01
#define HOURS 0x02
#define DAYS 0x03
#define DATES 0x04
#define MONTHS 0x05
#define YEARS 0x06
#define SQWE 0x07

extern I2C_HandleTypeDef hi2c1;

int decodeBCD(uint8_t bcd);//Convert data BCD to decimal.
uint8_t encodeDEC(int dec);//Convert data decimal to BCD.

uint8_t testDs1307(void);//Test DS1307
void startDs1307(void);//Sets the CH bit to 0.
void stopDs1307(void);//Sets the CH bit to 1.

void getTime(uint8_t timeBuff[7]);
uint16_t getYear(void);
uint8_t getMonth(void);
uint8_t getDate(void);
uint8_t getDay(void);
uint8_t getHour(void);
uint8_t getMinute(void);
uint8_t getSecond(void);

void setTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint16_t year );
void setYear(uint16_t year);
void setMonth(uint8_t month);
void setDate(uint8_t date);
void setDay(uint8_t day);
void setHour(uint8_t hour);
void setMinute(uint8_t minute);
void setSecond(uint8_t second);


#endif
