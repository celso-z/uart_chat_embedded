#include "./time.h"
#include "./rtc.h"
#include "../io.h"
#include <stdlib.h>

char* data_fields_to_str(uint8_t data_fields[6]){
    char *formatted_string = malloc(sizeof(char) * 19);
    int digit_index = 0; //ESSE AQUI É PARA CONTROLAR O DIGITO
    char digit_ascii[2];
    int str_index = 0; //Esse aqui é pra controlar a string
    for(int i = 0; i < 6; i++){//ESSE AQUI É PARA CONTROLAR O X
        uint8_t x = data_fields[i];
        while(x > 0){
            uint8_t digit = x%10;
            digit_ascii[digit_index] = '0' + digit;
            digit_index++;
            x /= 10;
        }
        if(digit_index == 1){
            formatted_string[str_index] = '0';
        }
        else{
            formatted_string[str_index] = digit_ascii[1];
        }
        str_index++;
        formatted_string[str_index] = digit_ascii[0];
        str_index++;
        if(i < 2){
            formatted_string[str_index] = '/';
        }else if(i == 2){
            formatted_string[str_index] = '-';
        }else if(i < 5){
            formatted_string[str_index] = ':';
        }else{
            formatted_string[str_index] = '\0';
        }
        str_index++;
        digit_index = 0;
        
    }
    return formatted_string;
}

uint32_t get_y2k_timestamp(){
    uint32_t y2k_timestamp = 0;

    time_struct *now = getCurrentTime();
    y2k_timestamp = now->ano * 365 * DAY_SECONDS;
    y2k_timestamp += (now->mes - 1) * 30 * DAY_SECONDS;
    y2k_timestamp += (now->data - 1) * DAY_SECONDS;
    y2k_timestamp += now->horas * HOUR_SECONDS;
    y2k_timestamp += now->minutos * 60;
    y2k_timestamp += now->segundos;
    free(now);

    return y2k_timestamp;
}

//UTILIZA MALLOC
char *get_formatted_timestamp(uint32_t timestamp){
    char *str;
    uint8_t data_fields[6] = {0,1,1,0,0,0};

    data_fields[0] += timestamp / (365 * DAY_SECONDS);
    timestamp = timestamp % (365 * DAY_SECONDS);
    data_fields[1] += timestamp / (30 * DAY_SECONDS);
    timestamp = timestamp % (30 * DAY_SECONDS);
    data_fields[2] += timestamp / DAY_SECONDS;
    timestamp = timestamp % DAY_SECONDS;
    data_fields[3] += timestamp / HOUR_SECONDS;
    timestamp = timestamp % HOUR_SECONDS;
    data_fields[4] += timestamp / 60;
    timestamp = timestamp % 60;
    data_fields[5] += timestamp;
    str = data_fields_to_str(data_fields);
    
    return str;
}
