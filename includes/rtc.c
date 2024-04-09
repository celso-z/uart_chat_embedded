#include "./rtc.h"
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

void init_connection(){
    RTC_DATA_REGISTER = 0x07;
    RESET_LOW();
    CLOCK_LOW();
    IO_LOW();
}

void init_transfer(){
    CLOCK_LOW();
    RESET_LOW();
    RESET_HIGH();
    _delay_us(4);
}

//Recebe o byte data do rtc
uint8_t byte_from_rtc(){
    uint8_t result = 0, TmpByte = 0;

    IO_IN();
	for(uint8_t i = 0; i < 8; ++i) //get byte 
	{
        CLOCK_HIGH();
		_delay_us(2);
        CLOCK_LOW();
		_delay_us(2);
		if(RTC_PIN & 0x04)
			TmpByte = 1;
		TmpByte <<= 7;
		result >>= 1;
		result |= TmpByte;
	}
    return result;
}

//Envia o byte data para o rtc
void byte_to_rtc(uint8_t data)	
{
    IO_OUT();

	for(uint8_t i = 0; i < 8; ++i)
	{
        IO_LOW()
		if(data & 0x01)
		{
            IO_HIGH();
		}
        CLOCK_LOW();
		_delay_us(2);
        CLOCK_HIGH();
		_delay_us(2);
		data >>= 1;
	}
}

uint8_t get_register(OperationCode op){
    uint8_t result = 0;

    init_transfer();
    byte_to_rtc(op);
    result = byte_from_rtc();
    RESET_LOW();
    CLOCK_LOW();
    return result; 
}

void set_register(OperationCode op, uint8_t data){
    init_transfer();
    byte_to_rtc(op); 
    byte_to_rtc(data); 
    RESET_LOW();
    CLOCK_LOW();
}

uint8_t parse_register_value(OperationCode op, uint8_t data){
    switch(op){
        case LE_SEG:
        case LE_MIN: {
            data = (data & 0x0F) + ((data & 0x70)>>4)*10;
            break;
        }
        case LE_HORA: 
        case LE_DATA: {
            data = ((data & 0x0F) + ((data & 0x30)>>4)*10);
            break;
        }
        case LE_MES: {
            data = ((data & 0x0F) + ((data & 0x10)>>4)*10);
            break;
        }
        case LE_DIA: {
            data = (data & 0x07);
            break;
        }
        case LE_ANO: {
            data = (data & 0x0f) + ((data & 0xf0) >> 4) * 10;
            break;
        }
    }
    return data;
}

uint8_t data_from_rtc(OperationCode op){
    uint8_t result = 0;

    if(op % 2 == 0 || op < 0x80 || op > 0x91) return -1; //BAD OPERATION CODE
    result = get_register(op);
    return parse_register_value(op, result);
}

uint8_t parse_data_to_register(OperationCode op, uint8_t data){
    switch(op){
        case ESCREVE_SEG:
        case ESCREVE_MIN:{
            data = (((data/10)<<4) & 0x70 | (data%10));
            break;
        }
        case ESCREVE_HORA:
        case ESCREVE_DATA:{
            data = ((((data/10)<<4) & 0x30) | (data%10));
            break;
        }
        case ESCREVE_MES:{
            data = (((data/10)<<4) & 0x10 | (data%10));
            break;
        }
        case ESCREVE_DIA:{
            data = data & 0x03;
            break;
        }
        case ESCREVE_ANO:{
            data = (((data/10)<<4) & 0xF0 | (data%10));
            break;
        }
    }
    return data;
}

uint8_t data_to_rtc(OperationCode op, uint8_t data){
    if(op % 2 == 1 || op < 0x80 || op > 0x91) return -1; //BAD OPERATION CODE
    data = parse_data_to_register(op, data);
    set_register(op, data);
    return 0;
}

time_struct *getCurrentTime(){
    time_struct *time = (time_struct *)malloc(sizeof(time_struct));

    if(time == NULL) return NULL;
    init_connection();
    updateCurrentTime(time);
    return time;
}

void updateCurrentTime(time_struct *time){
    time->segundos = data_from_rtc(LE_SEG);
    time->minutos = data_from_rtc(LE_MIN);
    time->horas = data_from_rtc(LE_HORA);
    time->data = data_from_rtc(LE_DATA);
    time->mes = data_from_rtc(LE_MES);
    time->dia = data_from_rtc(LE_DIA);
    time->ano = data_from_rtc(LE_ANO);
}

/*
int main(){
    init_connection();
    data_to_rtc(ESCREVE_ANO, 24);
    data_to_rtc(ESCREVE_MES, 3);
    data_to_rtc(ESCREVE_DATA, 29);
    data_to_rtc(ESCREVE_DIA, 7);
    data_to_rtc(ESCREVE_HORA, 9);
    data_to_rtc(ESCREVE_MIN, 20);
    data_to_rtc(ESCREVE_SEG, 0);
    
    while(1){
        
    }
    return 0;
}
*/
