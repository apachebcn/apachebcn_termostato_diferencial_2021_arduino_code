    /*
    *
    * SI ES ARDUINO MEGA ACTIVO EL "ABLE_SERIAL_DEBUG"
    * SI NO SE HABILITA QUEDARÁN ANULADAS TODAS LAS FUNCIONALIDADES DE SERIAL_DATA
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        #define ABLE_SERIAL_DEBUG
    #endif


    /*
    *
    * ARDUINO MINI PRO NO NECESITA FUNCIONES SERIAL_DATA
    * DEJAR DESACTIVADO PARA LIBERAR MEMORIA
    * ACTIVAR SÓLO PARA DEPURACIONES
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        //#define ABLE_SERIAL_DEBUG
    #endif


//#define DEVELOP_AUTO_RESET_CONFIG

//#define DEVELOP_VISTA_INICIAL_FORZADA_VISTA_SONDAS

//#define DEVELOP_SOLO_TEST_TECLADO

bool able_serial()
{
    #ifdef ABLE_SERIAL_DEBUG
        return 1;
    #endif
    return 0;
}

bool debug_setup() //Incluir en serial_forzado()
{
    #ifdef DEBUG_SETUP
        return 1;
    #endif
    return 0;
}

#define LANG_ES 1

#define ON HIGH
#define OFF LOW

