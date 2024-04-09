#ifndef _RTC_H_ 
#define _RTC_H_ 

#include <inttypes.h>

#define RTC_PORT PORTB
#define RTC_DATA_REGISTER DDRB
#define RTC_PIN PINB

#define RESET_HIGH() RTC_PORT |= 0x01;
#define RESET_LOW() RTC_PORT &= ~(0x01);
#define CLOCK_HIGH() RTC_PORT |= 0x02;
#define CLOCK_LOW() RTC_PORT &= ~(0x02);
#define IO_HIGH() RTC_PORT |= 0x04;
#define IO_LOW() RTC_PORT &= ~(0x04);
#define IO_OUT() RTC_DATA_REGISTER |= 0x04;
#define IO_IN() RTC_DATA_REGISTER &= ~(0x04);

typedef enum{
    SEGUNDA = 1, TERCA, QUARTA, QUINTA, SEXTA, SABADO, DOMINGO
} DiaSemana; 

typedef enum{
   ESCREVE_SEG = 0x80, LE_SEG, ESCREVE_MIN, LE_MIN, ESCREVE_HORA, LE_HORA, ESCREVE_DATA, LE_DATA, ESCREVE_MES, LE_MES, ESCREVE_DIA, LE_DIA, ESCREVE_ANO, LE_ANO
} OperationCode;

typedef struct{
   uint8_t segundos; 
   uint8_t minutos; 
   uint8_t horas; 
   uint8_t data;
   uint8_t mes; 
   uint8_t dia;
   uint8_t ano;
}time_struct;

time_struct *getCurrentTime(); 
void updateCurrentTime(time_struct *time);
#endif 
