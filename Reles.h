#define RELE_FLAG_AUTO_OFF 0
#define RELE_FLAG_FORZADO_ON 1
#define RELE_FLAG_FORZADO_OFF 2
#define RELE_FLAG_AUTO_ON 3

#define RELE_ACTIVADO_NADA                                  0
#define RELE_ACTIVADO_INICIO                                1
#define RELE_ACTIVADO_POR_BOMBA_1                           10
#define RELE_ACTIVADO_POR_BOMBA_PULSADA_1                   20
#define RELE_ACTIVADO_POR_AGUA                              30
#define RELE_ACTIVADO_POR_REFRIGERAR_COLECTOR_COLECTOR_1    40
#define RELE_ACTIVADO_POR_CALENTADOR_DEPOSITO               50
#define RELE_ACTIVADO_POR_FORZADO_MANUAL                    60
#define RELE_ACTIVADO_POR_EVENTO_1                          70

bool Reles_on_off = 0;
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define TOTAL_RELES 16
    byte Reles_estado[TOTAL_RELES];
    byte Reles_activado_por_dispositivo[TOTAL_RELES];
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define TOTAL_RELES 8
    byte Reles_estado[TOTAL_RELES];
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define REAL_REAL_SIGNAL_ON 0
    #define REAL_REAL_SIGNAL_OFF 1
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define REAL_REAL_SIGNAL_ON 0
    #define REAL_REAL_SIGNAL_OFF 1
#endif

class Reles
{

    private:

        static void _activar();
        static void _desactivar();
        static void _actuar_testing(byte, bool);
        static void _serial_print_debug_estado(byte);
        static void _serial_print_debug_dispositivo_activado_desde_rele(int);

    public:

        static void init();
        static bool disponible();
        static void actualiza_pin();
        static void set_valor(int, byte, byte);
        static void set_valores(byte);
        static byte get_valor(int);
        static void test();
        static void actuar();
        static byte GetBitArrayAsByte(byte*);
        static void serial_print_debug();
};
