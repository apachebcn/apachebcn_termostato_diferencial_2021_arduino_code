#define MENU_ELEMENTOS_TOTAL 94

byte Menu_nodo_ultimo = 0;
byte Menu_pos = 1;
struct MenuElementos
{
    byte type;
    byte abajo;
    byte derecha;
    byte valor;
} MenuElementos[(MENU_ELEMENTOS_TOTAL+1)];
