//#define DEBUG_MENU

#define MENU_TYPE_GROUP             0
#define MENU_TYPE_FUNCTION          1
#define MENU_TYPE_BOOL              2
#define MENU_TYPE_ACTIVAR           3
#define MENU_TYPE_DISPOSITIVO       4
#define MENU_TYPE_DISPOSITIVO_RELE_ACCION       5
#define MENU_TYPE_SONDA_SELECTOR    6
#define MENU_TYPE_EVENTO_RELE_ACCION 7
#define MENU_TYPE_RELE_SELECTOR     8
#define MENU_TYPE_0_TO_2            9
#define MENU_TYPE_0_TO_4            10
#define MENU_TYPE_0_TO_6            11 
#define MENU_TYPE_0_TO_10           12
#define MENU_TYPE_0_TO_255          13
#define MENU_TYPE_0_TO_100          14
#define MENU_TYPE_1_TO_100          15
#define MENU_TYPE_1_TO_30           16
#define MENU_TYPE_1_TO_255          17
#define MENU_TYPE_2_TO_255          18
#define MENU_TYPE_1_TO_32000        19
#define MENU_TYPE_MINUS_255_TO_255  20
#define MENU_TYPE_RELE_ESTADO       21

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define MENU_TYPE_BAUD       100
    #define MENU_TYPE_RELE_FORZADO_MODO_LED         101
#endif 

// CARGAR ESTRUCTURAS DE LOS MENUS
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #include "menu_data/definir_menu_vars_MEGA.h"
    #include "menu_data/definir_menu_defines_MEGA.h"
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #include "menu_data/definir_menu_vars_MINI.h"
    #include "menu_data/definir_menu_defines_MINI.h"
#endif

#include "Menu_eprom.h"
#include "Menu_imprimir_fila.h"
#include "Menu_editor.h"
#include "Menu_eventos.h"
#include "Menu_dispositivos_disponibles.h"

bool Menu_activo = 0;
int Menu_edicion_valor;
int menu_total_reles_vinculados;

class Menu
{
    private:

        static void _comprobar_elemento_id(int);
        static void _error_grave_desbordamiento_de_tipo(const __FlashStringHelper*, int, int);
        static const __FlashStringHelper* _type_label(int);
        static int _tiene_elemento_arriba(int);
        static int _tiene_elemento_izquierda(int);
        static int _tiene_elemento_atras(int);
        static int _tiene_elemento_abajo(int);
        static int _tiene_elemento_derecha(int);
        static void imprimir();
        static void _mostrar_reles_vinculados_MINI(int);
        static void _mostrar_reles_vinculados_MEGA(int);
        static bool grupo_eventos(int);
        static bool grupo_evento(int);
        static void _contar_reles_vinculados_1_enable(int, int);
        static void _contar_reles_vinculados_2_enables(int, int, int);
        static void _contar_reles_vinculados_3_enables(int, int, int, int);

    public:

        friend class Menu_eventos;
        friend class Menu_editor;
        friend class Menu_eprom;

        static void entrar();
        static void salir();
        static int get_valor(int);
        static int get_valor(int, int);
        static int get_entrada_valor_minimo(int);
        static int get_entrada_valor_minimo(int, int);
        static int get_entrada_valor_maximo(int);
        static int get_entrada_valor_maximo(int, int);
        static byte elemento_type(int);
        static void set_valor(int, int);
        static void elemento_insertar(int, int, int, byte, int);
        static bool functions(int);
        static int reget_sonda_id(int);

        static void volcar();

        static void mostrar_nav_icons();

        static bool is_config_type_editable(int);
        static void imprime_menu_array_vars();

        static void print_err(int, byte, const __FlashStringHelper*, int);
        static void print_err(int, byte);

} Menu;










