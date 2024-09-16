unsigned long ultima_lectura_ciclo_back_process_ms_timer_ = 0;
unsigned long ultima_lectura_ciclo_front_proceso_completo_ms_timer_ = 0;
unsigned long ultima_lectura_ciclo_front_proceso_parcial_ms_timer_ = 0;
bool latido = 0;
bool corriendo_procesos_back = 0;
bool corriendo_procesos_front = 0;
unsigned long refresca_pantalla_timer_ = 0;


/*
* CARGAR DISPOSITIVOS DE ENTRADA
*
*/
#include "Dispositivos_entrada/DE_Sondas.h"
#include "DE_Agua.h"



/*
* CARGAR DISPOSITIVOS DE SALIDA
*
*/
#include "Dispositivos_salida/DS_Bombas.h"
#include "Dispositivos_salida/DS_Calentador.h"
#include "Dispositivos_salida/DS_Refrigerador.h"



/*
* Fichero de textos lingüisticos
*
*/
#include "frases_lang_es.h"


/*
* Fichero de funciones comunes
*
*/
#include "Funciones_comunes.h"


/*
* Fichero que define la version
*
*/
#include "version.h"


/*
* 
*
*/
#include "setup.h"


/*
* Cargar el objeto Dispositivos de Entrada
*
*/
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #include "Dispositivos_entrada/Dispositivos_entrada_MEGA.h"
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #include "Dispositivos_entrada/Dispositivos_entrada_MINI.h"
#endif
#include "Dispositivos_entrada/Dispositivos_entrada.h"


/*
* Cargar el objeto Dispositivos_eventos
*
*/
#include "Dispositivos_eventos.h"


/*
* Cargar el objeto Dispositivos de Salida
*
*/
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #include "Dispositivos_salida/Dispositivos_salida_MEGA.h"
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #include "Dispositivos_salida/Dispositivos_salida_MINI.h"
#endif
#include "Dispositivos_salida/Dispositivos_salida.h"


/*
* Cargar el objeto Dispositivos
*
*/
#include "Dispositivos.h"


/*
* Cargar el objeto Buzzer
*
*/
#include "Buzzer.h"


/*
* Cargar el objeto Dispositivos_alarmas
*
*/
#include "Dispositivos_alarmas.h"


/*
* Cargar el objeto Reles
*
*/
#include "Reles.h"


/*
* Cargar el objeto Menu grupal
*
*/
#include "Menu_grupal.h"


/*
* Cargar el objetos de Menu
*
*/
#include "Menu.h"


/*
* Cargar textos linguisticos de Menu
*
*/
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #include "menu_data/definir_menu_frases_ES_MEGA.h"
#endif
#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #include "menu_data/definir_menu_frases_ES_MINI.h"
#endif


/*
* Cargar el objeto Serial
*
*/
#include "Serial_debug.h"


/*
* Cargar el objeto Pantalla
*
*/
#include "Pantalla.h"


/*
* Cargar el objeto Teclado
*
*/
#include "Teclado.h"


/*
* Cargar el objeto Leds
*
*/
#include "Leds.h"


/*
* Cargar 'Watchdog'
*
*/
#include "Watchdog.h"


#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

    /*
    * Cargar el objeto Lcd7
    *
    */
    #include "Lcd7.h"

#endif

#include "Termostato_procesos_back.h"
#include "Termostato_procesos_front.h"
