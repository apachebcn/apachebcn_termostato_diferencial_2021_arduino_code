#include "Pantalla_atajos.h"

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define PANTALLA_ANCHO_PX	20
    #define PANTALLA_ALTO_PX	4
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define PANTALLA_ANCHO_PX	16
    #define PANTALLA_ALTO_PX	2
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define DISPLAY_INFO_POS_Y 3
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define DISPLAY_INFO_POS_Y 1
#endif

#define MENSAJE_INFO_RESET 1
#define MENSAJE_INFO_SILENCIAR 2
#define MENSAJE_BLOQUEAR_TECLADO 3

#ifndef Pantalla_h
#define Pantalla_h
#endif

#define ICON_UP         1
#define ICON_DOWN       2
#define ICON_RIGHT      3
#define ICON_WAITING    4
#define ICON_TEMP       5
#define ICON_STOP       6
#define ICON_PLAY       7
#define ICON_ALARM      8

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define VISTA_NORMAL 0
    #define VISTA_STAT_MAX 1
    #define VISTA_STAT_MIN 2
    #define VISTA_ALARMAS 3
    #define VISTA_EVENTOS 4
    #define VISTA_SONDAS 5
    #define VISTA_LAST 5
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define VISTA_NORMAL 0
    #define VISTA_STAT_MIN 1
    #define VISTA_STAT_MAX 2
    #define VISTA_EVENTOS 3
    #define VISTA_ALARMAS 4
    #define VISTA_SONDAS 5
    #define VISTA_LAST 5
#endif

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, PANTALLA_ANCHO_PX, PANTALLA_ALTO_PX);

char Pantalla_buffer_segmento[(PANTALLA_ANCHO_PX/2)+1];
bool Pantalla_luz = 0;
unsigned long Pantalla_luz_timer_;
byte Pantalla_modo_vista = VISTA_NORMAL;

class Pantalla
{
    private:

        static int _get_dec(float);
        static void _imprime_dispositivo_valor(byte modo_vista, byte posX, byte posY, int dispositivo_entrada_id, char icono_dispositivo, char icono_caracter_sufijo, bool decimales);
        static void _imprime_dispositivo_indisponible(byte posX, byte posY, char icono_dispositivo);
        static void _imprime_dispositivo_inactivado(byte posX, byte posY, char icono_dispositivo);
        static void _imprime_dispositivo_error(byte posX, byte posY, char icono_dispositivo);
        static void _imprime_dispositivo_id(byte modo_vista, byte posX, byte posY, bool decimales, int dispositivo_entrada_id, char icono_dispositivo, char icono_caracter_sufijo);
        static void _print_pantalla_alarmas_valor(int);

    public:

        static void ver_about();
        static byte iniciar();
        static void apagar();
        static void encender();
        static void cargar_iconos();
        static void borrar();
        static void borrar_fila(byte);
        static void borrar_media_fila(byte x, byte y);
        static void print_centrado(const __FlashStringHelper*, byte);
        static void mostrar_visor_reles();

        static void insertar_info_msg(byte);
        static void mostrar_info_msg();
        static void mostrar_modo_vista();

        static void print_pantalla_alarmas();
        static void print_pantalla_eventos();
        static void imprime_dispositivos_valores(byte);


        static void visor_sondas();

};

