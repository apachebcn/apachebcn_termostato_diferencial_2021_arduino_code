void(* resetFunc) (void) = 0; //declare reset function @ address 0

//#include "Includes/OneWire/OneWire.h"
#include <OneWire.h>
#include <Wire.h> 

/*
* Detectar el modelo del arduino
*
*/
#ifdef __AVR_ATmega2560__
    #define IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #include "TermostatoDiferencial_pines_MEGA.h"
#else
    #define IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #include "TermostatoDiferencial_pines_MINI.h"
#endif

#include "TermostatoDiferencial.h"

void loop()
{
    Leds::refresca_tiks();
    Leds::refresca_leds();

    if (refresca_pantalla_timer_ > 0 && millis() > refresca_pantalla_timer_)
    {
        front_pantalla();
        refresca_pantalla_timer_ = 0;
    }


    /*
    *   procesa teclado
    *
    */
    Teclado::procesar_teclas();



    /*
    *   back procesos cada 250ms
    *
    */
    if ( FC::if_zero_or_diff_to_millis(ultima_lectura_ciclo_back_process_ms_timer_, 250) )
    {
        back_procesos();
    }

    /*
    *   front procesos parciales cada Xms (X se indica en la configuración)
    *
    */
    if ( FC::if_zero_or_diff_to_millis(ultima_lectura_ciclo_front_proceso_completo_ms_timer_, time_lecturas_ms()) )
    {
        front_procesos();
        ultima_lectura_ciclo_front_proceso_completo_ms_timer_ = millis();
        //reinicio el contador de proceso_parcial para no solapar
        ultima_lectura_ciclo_front_proceso_parcial_ms_timer_ = millis();
    }


    /*
    *   si bombas están procesando, correr front procesos cada 1000ms
    *
    */
    if ( FC::if_zero_or_diff_to_millis(ultima_lectura_ciclo_front_proceso_parcial_ms_timer_, 1000) )
    {
        if (back_procesos_comprueba_actividad_bombas())
        {
            front_procesos();
            ultima_lectura_ciclo_front_proceso_parcial_ms_timer_ = millis();
        }
    }

}

unsigned long time_lecturas_ms()
{
    unsigned long time_LECTURAS = Menu::get_valor(TIEMPO_LECTURAS_SEGUNDOS)*1000;
    if (!time_LECTURAS) time_LECTURAS = 5000;
    return time_LECTURAS;
}
