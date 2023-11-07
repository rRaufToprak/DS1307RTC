/*
 * ds1307.c
 * 
 * Created on: 28.10.2023
 * Author: rRaufToprak
*/

#include "ds1307.h"
#include "main.h"
#include "stm32f1xx_hal.h"

I2C_HandleTypeDef hi2c1;


uint8_t testDs1307(){
	HAL_StatusTypeDef status;
	uint16_t ready;
	status = HAL_I2C_IsDeviceReady(&hi2c1, (0x68<<1), 5, 1000);

	if(status == HAL_OK){
		ready =1;
	}else{
		ready =0;
	}
	return ready;
}
void startDs1307(){
	uint8_t byte;
	uint8_t readCh[1];
	HAL_I2C_Mem_Read(&hi2c1, 0x68<<1, 0x00, 1, readCh, 1, 1000);
	byte = readCh[0] & 0x7F; // Set CH bit 0
	readCh[0] = byte;
	HAL_I2C_Mem_Write(&hi2c1, 0x68<<1, 0x00, 1, readCh, 1, 1000);
}
void stopDs1307(){
	uint8_t byte;
	uint8_t readCh[1];
	HAL_I2C_Mem_Read(&hi2c1, 0x68<<1, 0x00, 1, readCh, 1, 1000);
	byte = readCh[0] | 0x80; // Set CH bit 1
	readCh[0] = byte;
	HAL_I2C_Mem_Write(&hi2c1, 0x68<<1, 0x00, 1, readCh, 1, 1000);
}
int decodeBCD(uint8_t bcd)
{
  return(((bcd & 0xF0)>>4)*10)+(bcd & 0x0F);
}
uint8_t encodeDEC(int dec)
{
  return (dec%10+((dec/10)<<4));
}
void setSecond(uint8_t second){
	uint8_t secondBcd = encodeDEC(second);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, SECONDS, 1, &secondBcd, 1, 1000);
}
void setMinute(uint8_t minute){
	uint8_t minuteBcd = encodeDEC(minute);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, MINUTES, 1, &minuteBcd, 1, 1000);
}
void setHour(uint8_t hour){
	uint8_t hourBcd = encodeDEC(hour);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, HOURS, 1, &hourBcd, 1, 1000);
}
void setDay(uint8_t day){
	uint8_t dayBcd = encodeDEC(day);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, DAYS, 1, &dayBcd, 1, 1000);
}
void setDate(uint8_t date){
	uint8_t dateBcd = encodeDEC(date);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, DATES, 1, &dateBcd, 1, 1000);
}
void setMonth(uint8_t month){
	uint8_t monthBcd = encodeDEC(month);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, MONTHS, 1, &monthBcd, 1, 1000);
}
void setYear(uint16_t year){
	uint8_t yearBcd = encodeDEC(year);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, YEARS, 1, &yearBcd, 1, 1000);
}
void setTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint16_t year ){
	stopDs1307();
	uint8_t timeBuff[7];
	timeBuff[0] = encodeDEC(second);
	timeBuff[1] = encodeDEC(minute);
	timeBuff[2] = encodeDEC(hour);
	timeBuff[3] = encodeDEC(day);
	timeBuff[4] = encodeDEC(date);
	timeBuff[5] = encodeDEC(month);
	timeBuff[6] = encodeDEC(year);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, SECONDS, 1, &timeBuff[0], 1, 1000);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, MINUTES, 1, &timeBuff[1], 1, 1000);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, HOURS, 1, &timeBuff[2], 1, 1000);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, DAYS, 1, &timeBuff[3], 1, 1000);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, DATES, 1, &timeBuff[4], 1, 1000);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, MONTHS, 1, &timeBuff[5], 1, 1000);
	HAL_I2C_Mem_Write(DS1307I2C, DS1307ADDR, YEARS, 1, &timeBuff[6], 1, 1000);
	startDs1307();
}
uint8_t getSecond(){
	uint8_t secondBcd;
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, SECONDS, 1, &secondBcd, 1, 1000);
	uint8_t second = decodeBCD(secondBcd);
	
	return second;
}
uint8_t getMinute(){
	uint8_t minuteBcd;
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, MINUTES, 1, &minuteBcd, 1, 1000);
	uint8_t minute = decodeBCD(minuteBcd);
	
	return minute;
}
uint8_t getHour(){
	uint8_t hourBcd;
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, HOURS, 1, &hourBcd, 1, 1000);
	uint8_t hour = decodeBCD(hourBcd);
	
	return hour;
}
uint8_t getDay(){
	uint8_t dayBcd;
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, DAYS, 1, &dayBcd, 1, 1000);
	uint8_t day = decodeBCD(dayBcd);
	
	return day;
}
uint8_t getDate(){
	uint8_t dateBcd;
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, DATES, 1, &dateBcd, 1, 1000);
	uint8_t date = decodeBCD(dateBcd);
	
	return date;
}
uint8_t getMonth(){
	uint8_t monthBcd;
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, MONTHS, 1, &monthBcd, 1, 1000);
	uint8_t month = decodeBCD(monthBcd);
	
	return month;
}
uint16_t getYear(){
	uint8_t yearBcd;
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, YEARS, 1, &yearBcd, 1, 1000);
	uint16_t year = decodeBCD(yearBcd);
	
	return year;
}
void getTime(uint8_t timeBuff[7]){
	uint8_t timeBcd[7];
	HAL_I2C_Mem_Read(DS1307I2C, DS1307ADDR, SECONDS, 7, timeBcd, 7, 1000);
	timeBuff[0] = decodeBCD(timeBcd[0]);
	timeBuff[1] = decodeBCD(timeBcd[1]);
	timeBuff[2] = decodeBCD(timeBcd[2]);
	timeBuff[3] = decodeBCD(timeBcd[3]);
	timeBuff[4] = decodeBCD(timeBcd[4]);
	timeBuff[5] = decodeBCD(timeBcd[5]);
	timeBuff[6] = decodeBCD(timeBcd[6]);
}

