/*
 * BUZZER
*/
#define PIN_BUZZER                          26


/*
 * LEDS
*/
#define PIN_LED_IN_BOARD_LECTURAS           13
#define PIN_LED_LECTURAS                    11
#define PIN_LED_SERIAL_DATA                 10
#define PIN_LED_ALARMAS                     9
#define PIN_LED_BOMBA_1                     8
#define PIN_LED_BOMBA_2                     7
#define PIN_LED_BOMBA_3                     6
#define PIN_LED_AGUA                        5
#define PIN_LED_CALENTAR                    4
#define PIN_LED_ENFRIAR                     3
#define PIN_LED_SERIALDATA                  10


/*
* AGUA
*/
#define PIN_WATER_LEVEL_WRITE A13 //TRIGGER
#define PIN_WATER_LEVEL_READ A14 //ECHO
#define PIN_AGUA_STOP A15
#define PIN_AGUA_STOP A15


/*
 * LCD7
*/
#define PIN_DIGITAL_LCD7SEG_74HC595_DATA    A12 //PIN-14 / DS / SER / SCL / (serial data input) 
#define PIN_DIGITAL_LCD7SEG_74HC595_LATCH   A10 //PIN-12 / ST_CP / RCK / (storage register clock input) 
#define PIN_DIGITAL_LCD7SEG_74HC595_CLOCK   A11 //PIN-11 / SH_CP / SCK / (shift register clock input)
#define PIN_DIGITAL_LCD7SEG_BRILLO          2


/*
 * TECLADO
*/
#define PIN_ENCODER_A 19
#define PIN_ENCODER_B 18
#define PIN_TECLA_OK 40
#define PIN_TECLA_ATRAS 42


/*
 * SONDAS DALLAS DS
*/
#define PIN_SONDAS A9


/*
 * SONDAS DALLAS DE WILLI
*/
//#define PIN_SONDAS A8


/*
 * RELES
*/
byte reles_get_pin_num(byte rele_id)
{
    switch(rele_id)
    {
        case 0: return                      22;
        case 1: return                      24;
        case 2: return                      25;
        case 3: return                      23;
        case 4: return                      29;
        case 5: return                      27;
        case 6: return                      33;
        case 7: return                      31;
        case 8: return                      37;
        case 9: return                      35;
        case 10: return                     41;
        case 11: return                     39;
        case 12: return                     45;
        case 13: return                     43;
        case 14: return                     47;
        case 15: return                     49;
        default: return                     0;
    }
}
