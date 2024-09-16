#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

#define MENU_ELEMENTOS_TOTAL 321

#define MEGA_RELE_FORZADO_LED_OFF 0
#define MEGA_RELE_FORZADO_LED_SLOW 1
#define MEGA_RELE_FORZADO_LED_FAST 2

int Menu_nodo_ultimo = 0;
int Menu_pos = 1;
struct MenuElementos
{
    byte type;
    int abajo;
    int derecha;
    int valor;
} MenuElementos[(MENU_ELEMENTOS_TOTAL+1)];

#endif