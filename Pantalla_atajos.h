#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    byte Pantalla_vista_atajos_activado = 0;
    int Pantalla_vista_atajos_item = 0;
    //int Pantalla_vista_atajos_pos_y = 0;

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define VISTA_ATAJOS_ACTIVAR_RELES      0
    #define VISTA_ATAJOS_MOSTRAR_RELES      1
    #define VISTA_ATAJOS_FORZAR_AGUA        2
    #define VISTA_ATAJOS_FORZAR_BOMBA_1     3
    #define VISTA_ATAJOS_FORZAR_BOMBA_2     4
    #define VISTA_ATAJOS_FORZAR_BOMBA_3     5
    #define VISTA_ATAJOS_FORZAR_RELE_1      6
    #define VISTA_ATAJOS_LAST (VISTA_ATAJOS_FORZAR_RELE_1+(TOTAL_RELES-1))
#endif



    class Pantalla_atajos
    {
        public:
            static void print_pantalla_atajos(int);
            static void print_pantalla_atajos_validar();
    };
#endif
