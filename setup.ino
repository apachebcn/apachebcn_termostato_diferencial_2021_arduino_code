void setup()
{

    /*
    * FORZAR SERIAL DEBUG
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        bool FORCE_SERIAL_DEBUG = 0;
    #endif


    bool boton_pulsado;
    bool debug_boot = 0;
    bool ignorar_eprom = 0;

    /*
    * INICIAR TECLADO
    *
    */
    Teclado::inicia_pin();


    /*
    * DEBUG BOOT
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        boton_pulsado = digitalRead(PIN_TECLA_OK);
        if (boton_pulsado)
        {
            debug_boot = 1;
            FORCE_SERIAL_DEBUG = 1;
        }
    #endif


    /*
    * BOTON DE ATRÁS - RESET CONFIG
    *
    */
    boton_pulsado = digitalRead(PIN_TECLA_ATRAS);
    #ifdef DEVELOP_AUTO_RESET_CONFIG
        boton_pulsado = 1;
    #endif
    if (boton_pulsado) ignorar_eprom = 1;


    /*
    * INICIAR SERIAL DATA DE FORMA FORZADA
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (FORCE_SERIAL_DEBUG)
        {
            Serial_debug::forzar_on();
        }
    #endif


    /*
    * BUSCAR E INICIA PANTALLA I2C
    *
    */
    if (debug_boot)
    {
        Serial_debug::print(F("Pantalla I2C "));
        Serial_debug::println(F("Buscando"));
    }
    byte address = Pantalla::iniciar();
    if (debug_boot)
    {
        Serial_debug::print(F("Pantalla I2C "));
        Serial_debug::print(F("Encontrada en "));
        if (address<16) Serial_debug::write('0');
        Serial_debug::println(address);
    }
    Pantalla::cargar_iconos();
 


    /*
    * SALUDO PANTALLA
    *
    */
    Pantalla::ver_about();
    

    /*
    * MODO SOLO TEST TECLADO
    *
    */
    #ifdef DEVELOP_SOLO_TEST_TECLADO
        lcd.clear();
        lcd.print(F("TESTING KEYS"));
        return;
    #endif


    /*
    * INICIA WIRE
    *
    */
    Wire.begin();




    /*
    * INICIADORES
    *
    */
    Sondas::init();
    Dispositivos_alarmas.init();
    Reles::init();
    Bombas::init();
    Dispositivos.init();



    /*
    * CARGAR ESTRUCTURA DE MENU
    *
    */
    if (debug_boot)
    {
        Serial_debug::println(F("Cargando estructura de menu"));
    }
    Menu_pos = 1;
    Menu_activo = 0;
    Menu_editando = 0;

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        #include "menu_data/definir_menu_estructura_MEGA.h"
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        #include "menu_data/definir_menu_estructura_MINI.h"
    #endif

    if (debug_boot)
    {
        Serial_debug::println();
        Serial_debug::println(F("Cargar Valores por defecto"));
    }

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        #include "menu_data/definir_menu_valores_personalizados_MEGA.h"
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        #include "menu_data/definir_menu_valores_personalizados_MINI.h"
    #endif



    /*
    * CARGAR EPROM
    *
    */
    if (ignorar_eprom)
    { 
        if (debug_boot)
        {
            Serial_debug::print(F("Tecla de atras pulsada, "));
            Serial_debug::println(F("Ignorando EPROM"));
        }
        Pantalla::borrar();
        Pantalla::print_centrado(F("Ignorando EPROM"), 0);
        FC::delayMilisegundos(2000);
    }
    else
    {
        Menu_eprom::load();
    }



    /*
    * INICIA PIN SERIAL_DEBUG
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (!FORCE_SERIAL_DEBUG)
        {
            Serial_debug::inicia_pin();
        }
    #endif



    /*
    * VOLCAR A SERIAL DATA LA CARGA DE MENU
    *
    */
    if (debug_boot)
    {
        Menu::volcar();
    }



    /*
    * INICIA BUZZER
    *
    */
    Buzzer::actualiza_pin();



    /*
    * INICIA PINS RELÉS
    *
    */
    Reles::actualiza_pin(); 



    /*
    * INICIA SONDAS DALLAS
    *
    */
    Sondas::actualiza_pin();
    Sondas::scan();



    /*
    * INICIA LEDS
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (debug_boot)
        {
            Serial_debug::println(F("Iniciando pines PWM para leds"));
        }
    #endif
    Leds::inicia_pin();



    /*
    * DEMO LEDS
    *
    */
    Leds::test();



    /*
    * DEMO BUZZER
    *
    */
    Buzzer::test(0);



    /*
    * INICIA LEDS 7
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (debug_boot)
        {
            Serial_debug::println(F("Iniciando Lcd7"));
        }
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Lcd7::actualiza_pin();
    #endif


    /*
    * DEMO LCD7
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (Menu::get_valor(LCD_7_ON_OFF))
        {
            Lcd7::demo(); 
        }
    #endif


    /*
    * INICIA PINS AGUA Y AGUA STOP
    *
    */
    /*
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (debug_boot)
        {
            Serial_debug::println(F("Iniciando Agua"));
        }
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Agua::actualiza_pin();
    #endif
    */


    /*
    * PAUSA PARA INICIAR PINES Y VER BIENVENIDA EN PANTALLA
    *
    */
    FC::delayMilisegundos(200);


    /*
    * INICIAR BOMBAS
    *
    */
    /*
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (debug_boot)
        {
            Serial_debug::println(F("Iniciando Bombas"));
        }
    #endif
    byte bomba_id = 0;
    for(byte bomba_id = 0; bomba_id < TOTAL_SONDAS_COLECTORES; bomba_id++)
    {
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (debug_boot)
        {
            Serial_debug::print(F("Inicio objeto Bombas num "));
            Serial_debug::print(bomba_id);
            Serial_debug::print(F(" mostrara en lcd(0,"));
            Serial_debug::print(bomba_id);
            Serial_debug::println(F(")"));
        }
        #endif
        Bombas[bomba_id].set_vars(
            0,          //cursor_x
            bomba_id,  //cursor_y
            bomba_id   //bomba_id
            );
    }
    */


    /*
    * ENCENDER Y BORRAR PANTALLA
    *
    */
    Pantalla::encender();
    #ifdef DEVELOP_VISTA_INICIAL_FORZADA_VISTA_SONDAS
        Menu::set_valor(RELES_VISOR, 1);
    #endif



    /*
    * ESPERA AL INICIO DE SONDAS
    *
    */
    if (Menu::get_valor(SONDAS_ON_OFF))
    {
        Sondas::esperar_disponibilidad();
    }

    Pantalla::encender();


    /*
    * WATCHDOG
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (debug_boot)
        {
            Serial_debug::println();
            Serial_debug::println(F("WatchDog Start"));
        }
    #endif
    watchdogSetup();

    ultima_lectura_ciclo_front_proceso_completo_ms_timer_ = 0;

    if (debug_boot)
    {
        Serial_debug::println(F("Fin setup"));
    }


}

