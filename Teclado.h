#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #include <Encoder.h>
    #define ROTARY_PASOS 3
    volatile int PIN_ENCODER_A_Last = HIGH;
    volatile int PIN_ENCODER_A_Actual = HIGH;
    volatile byte encoder_dir = 0;
    Encoder Rotary_1(PIN_ENCODER_A, PIN_ENCODER_B);
#endif

#ifndef Teclado_h
#define Teclado_h
#endif

#define SIGN_TECLA_OK 2
#define SIGN_TECLA_ATRAS 3
#define SIGN_TECLA_ABAJO 4
#define SIGN_TECLA_ARRIBA 5

#define SERIAL_TECLA_OK 53
#define SERIAL_TECLA_ATRAS 48
#define SERIAL_TECLA_ABAJO 56
#define SERIAL_TECLA_ARRIBA 50

byte Teclado_tecla_soltada = 0;
byte Teclado_tecla_pulsada = 0;
byte Teclado_tecla_sosteniendo = 0;
unsigned long Teclado_sosteniendo_timer_ = 0;
unsigned long Teclado_ultimo_evento_timer_ = 0;

byte Teclado_locked_keys = 0;
bool Teclado_ignorar_teclado_corto = 0;

class Teclado
{

    private:
        
        static bool _revivir_pantalla();

    public:

        static void inicia_pin();
        static void reset();
        static void bloquear();
        static byte get_rotary_encoder();
        static byte get_serial_keys();

        static void procesar_teclas();
        static void procesar_teclas_cortas(byte key_push);
        static void procesar_teclas_menu_dentro(byte &key_push);
        static void procesar_teclas_largas(byte& tecla_sosteniendo);
        static void incrementa_vista();
        static void decrementa_vista();
};

