#include "./time.h"
#include "./rtc.h"
#include "./io.h"
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 16000000
#include <util/delay.h>

/*Retorna o número de dias a partir de uma data específica
http://howardhinnant.github.io/date_algorithms.html#civil_from_days*/
uint32_t days_from(uint16_t y, uint8_t m, uint8_t d) {
    y -= m <= 2;
    uint32_t era = (y >= 0 ? y : y-399) / 400; //Número da era (será multiplicado por     400 pois a cada 400 anos o calendário gregoriano se repete, estranho não)
    uint32_t yoe = (y - era * 400);      // [0, 399]
    uint32_t doy = (153*(m > 2 ? m-3 : m+9) + 2)/5 + d-1;  // [0, 365]
    uint32_t doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
    return era * 146097 + doe - 719468;
}
uint32_t get_timestamp(){
    uint32_t timestamp = 0;
    time_struct *now = getCurrentTime();
    timestamp = days_from((uint16_t)(now->ano + 2000), now->mes, now->data);
    timestamp -= days_from(2000, 1, 1);
    timestamp *= DAY_SECONDS;
    timestamp += ((uint32_t)now->horas * HOUR_SECONDS) + ((uint32_t)now->minutos * 60) + (uint32_t)now->segundos;
    free(now);

    return timestamp;
}

uint16_t *date_of(uint32_t unix_epoch_days){
    uint16_t *date_fields = malloc(sizeof(uint16_t) * 3);
    unix_epoch_days += 719468;
    uint32_t era = (unix_epoch_days >= 0 ? unix_epoch_days : unix_epoch_days - 146096    ) / 146097;
    uint32_t doe = (unix_epoch_days - era * 146097);          // [0, 146096]
    uint32_t yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
    uint32_t y = yoe + era * 400;
    uint32_t doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
    uint32_t mp = (5*doy + 2)/153;                                   // [0, 11]
    uint32_t d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
    uint32_t m = mp < 10 ? mp+3 : mp-9;                            // [1, 12]
    date_fields[0] = (uint16_t)(y + (m <= 2));
    date_fields[1] = (uint16_t)m;
    date_fields[2] = (uint16_t)d;
    return date_fields;
}

char *get_formatted_timestamp(uint32_t timestamp){
    char *str = malloc(sizeof(char) * 20);
    timestamp += (days_from(2000, 1, 1) * DAY_SECONDS);
    uint32_t seconds_current_day = timestamp % DAY_SECONDS; //segundos do dia atual
    uint32_t epoch_days = timestamp / DAY_SECONDS; //dias desde 1/1/1970 (UNIX EPOCH)
    uint16_t *date_fields = date_of(epoch_days);
    uint8_t hours_current_day = seconds_current_day / HOUR_SECONDS;
    seconds_current_day %= HOUR_SECONDS;
    uint8_t minutes_current_day = seconds_current_day / 60;
    seconds_current_day %= 60;

    sprintf(str, "%02d/%02d/%02d-%02d:%02d:%02d",date_fields[2], date_fields[1], date_fields[0], hours_current_day, minutes_current_day, (uint8_t)seconds_current_day);
    free(date_fields);
    return str; 
}
