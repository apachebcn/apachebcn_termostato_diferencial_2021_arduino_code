#define LED_OFF 0
#define LED_ON 1
#define LED_BLINK_SLOW 2
#define LED_BLINK_FAST 3

//MAPA DE LEDS DE ARDUINO PRO MINI
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define BIT_LED_ALARMAS                     0
    #define BIT_LED_LECTURAS                    1
    #define BIT_LED_BOMBA_1                     2
    #define BIT_LED_BOMBA_1_PULSADA             3
    #define BIT_LED_CALENTADOR_REFRIGERADOR     4
#endif

//MAPA DE LEDS DE ARDUINO MEGA
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define BIT_LED_SERIALDATA        0
    #define BIT_LED_LECTURAS          1
    #define BIT_LED_ALARMAS           2
    #define BIT_LED_BOMBA_1           3
    #define BIT_LED_BOMBA_2           4
    #define BIT_LED_BOMBA_3           5
    #define BIT_LED_CALENTADOR        6
    #define BIT_LED_REFRIGERADOR      7
    #define BIT_LED_AGUA              8
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define LAST_BIT_LEDS 5
    byte Leds_bits_state[LAST_BIT_LEDS] = {0,0,0,0,0};
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define LAST_BIT_LEDS 9
    byte Leds_bits_state[LAST_BIT_LEDS] = {0,0,0,0,0,0,0,0,0};
#endif

unsigned long Leds_refresh_150_timer_;
unsigned long Leds_refresh_500_timer_;
bool Leds_tick_fast;
bool Leds_tick_slow;

class Leds
{
    private:

        static byte _bit_to_pin(byte bit);
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            static byte _brillo_map(byte percent);
            static void _test_MEGA();
        #endif
        #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
            static void _test_MINI();
        #endif

    public:

        static void inicia_pin();
        static byte coge_estado_cuando_forzado_on();
        static byte coge_estado_cuando_forzado_off();
        static void set_bit(byte bit, byte valor);
        static void set_bits(byte valor);
        static void refresca_leds();
        static void refresca_led(byte bit, byte value_state);
        static void refresca_tiks();
        static void brillo_refresca_muestra(int);
        static void test();
        static void latido(bool valor);

        static void set_alarmas(byte);
        static void set_lecturas(byte);
        static void set_bomba(byte, byte);
        static void set_bomba_pulsada(byte, byte);
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            static void set_calentador(byte);
            static void set_refrigerador(byte);
            static void set_agua(byte);
        #endif
        #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
            static void set_calentador_refrigerador(byte);
        #endif
        static void set_alarma(byte);
};
