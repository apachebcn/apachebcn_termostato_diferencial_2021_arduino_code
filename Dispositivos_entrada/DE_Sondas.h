/*
*
*   DISPOSITIVO REAL SONDAS
*
*/

OneWire dallas_sondas_wires(PIN_SONDAS);

#define SONDAS_RESOLUCION 10

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define LAST_SONDA 12
    #define TOTAL_SONDAS_COLECTORES 3
    #define TOTAL_SONDAS_ZONAS 10
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define LAST_SONDA 6
    #define TOTAL_SONDAS_COLECTORES 1
#endif

struct SondasElementos
{
    byte dir[8];
//    byte estado;
//    int temp;
//    int stat_min;
//    int stat_max;
} SondasElementos[LAST_SONDA];

byte Sondas_total_escaneadas;
byte Sondas_deposito_dir[8] = {0,0,0,0,0,0,0,0};
byte Sondas_ztermostato_dir[8] = {0,0,0,0,0,0,0,0};
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    byte Sondas_lcd7_dir[8] = {0,0,0,0,0,0,0,0};
    byte Sondas_colector_dir[TOTAL_SONDAS_COLECTORES][8];
    byte Sondas_zona_dir[TOTAL_SONDAS_ZONAS][8];
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    byte Sondas_colector_dir[TOTAL_SONDAS_COLECTORES][8];
#endif

class Sondas
{
    private:

        static bool _activado();
        static void _print_resolution(byte resolution_num);
        static void _print_chip(const __FlashStringHelper* chip_name);
        static int _lee_temp(byte*, bool usa_debug);
        static void _WriteScratchPad(byte*);

    public:

        static void actualiza_pin();
        static void init();
        static bool test_dir(byte* sonda_addr);
        static float convert_temp(int);
        static void lcd_print_addr_dir(byte*);
        static void lcd_print_addr_sonda_id(int);
        static void serial_print_addr_dir(byte*);
        static void serial_print_addr_sonda_id(int);
        static bool test_addr_dir(byte*);
        static int buscar_addr_dir(byte*);
        static bool comparar_addr_dir(byte*, byte*);
        static void copiar_sonda_id_a(int, byte*);
        static void scan();
        static void esperar_disponibilidad();

        static float lee_la_sonda_dir(byte* dir, bool usa_debug);
        static float lee_la_sonda_num(int sonda_num, bool usa_debug);


};