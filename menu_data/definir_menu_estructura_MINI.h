#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI

byte idx;
byte idx2;
byte bucle;
byte menu_next_subgroup = 0;

Menu::elemento_insertar(G_MENU,                                                 G_TIEMPOS, 0,                                   MENU_TYPE_GROUP, 0);

Menu::elemento_insertar(G_TIEMPOS,                                              BUZZER_ON_OFF, TIEMPO_LECTURAS_SEGUNDOS, MENU_TYPE_GROUP, 0);
    #include "Grupo_tiempos.h"

Menu::elemento_insertar(BUZZER_ON_OFF,                                          G_SONDAS, 0,                                        MENU_TYPE_ACTIVAR, 1);

Menu::elemento_insertar(G_SONDAS,                                               0, SONDAS_ON_OFF,                                   MENU_TYPE_GROUP, 0);
    Menu::elemento_insertar(SONDAS_ON_OFF,                                      SONDAS_ESCALA, 0,                                   MENU_TYPE_ACTIVAR, 1);
    Menu::elemento_insertar(SONDAS_ESCALA,                                      SONDA_COLECTOR_1_DIR, 0,                            MENU_TYPE_BOOL, 0);
    Menu::elemento_insertar(SONDA_COLECTOR_1_DIR,                               SONDA_DEPOSITO_DIR, 0,                              MENU_TYPE_SONDA_SELECTOR, 0);
    Menu::elemento_insertar(SONDA_DEPOSITO_DIR,                                 SONDA_ZTERMOSTATO_DIR, 0,                           MENU_TYPE_SONDA_SELECTOR, 0);
    Menu::elemento_insertar(SONDA_ZTERMOSTATO_DIR,                              SONDA_COLECTOR_1_DIR, 0,                            MENU_TYPE_SONDA_SELECTOR, 0);
    Menu::elemento_insertar(SONDA_COLECTOR_1_DIR,                               0, 0,                                               MENU_TYPE_SONDA_SELECTOR, 0);

Menu::elemento_insertar(G_DISPOSITIVOS_DE_SALIDA,                               G_EVENTOS, G_BOMBA_1,                           MENU_TYPE_GROUP, 0);

    menu_next_subgroup = G_REFRIGERAR_COLECTOR_1;
    #include "Grupo_bombas.h"

    #include "Grupo_refrigerar_colectores.h"

    Menu::elemento_insertar(0,                                                  G_REFRIGERAR_COLECTOR_1, CALENTADOR_DEPOSITO_ON_OFF, MENU_TYPE_GROUP, 0);
        #include "Grupo_calentador_deposito.h"

Menu::elemento_insertar(G_EVENTOS,                                              G_RELES, EVENTOS_ON_OFF,                            MENU_TYPE_GROUP, 0);
    #include "Grupo_eventos.h"

Menu::elemento_insertar(G_RELES,                                                C_TEST_RELES, RELES_ON_OFF,                                    MENU_TYPE_GROUP, 0);
    #include "Grupo_reles.h"

Menu::elemento_insertar(C_TEST_RELES,                                           C_SETUP_BORRAR, 0,                                  MENU_TYPE_FUNCTION, 0);
Menu::elemento_insertar(C_SETUP_BORRAR,                                         C_SETUP_GUARDAR, 0,                                 MENU_TYPE_FUNCTION, 0);
Menu::elemento_insertar(C_SETUP_GUARDAR,                                        C_RESET, 0,                                         MENU_TYPE_FUNCTION, 0);
Menu::elemento_insertar(C_RESET,                                                C_ABOUT, 0,                                         MENU_TYPE_FUNCTION, 0);

Menu::elemento_insertar(C_ABOUT,                                                0, 0,                                               MENU_TYPE_FUNCTION, 0);

#endif