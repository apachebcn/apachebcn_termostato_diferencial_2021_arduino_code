#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

int idx;
int idx2;
byte bucle;
int menu_next_subgroup = 0;

Menu::elemento_insertar(G_MENU,                                                 G_TIEMPOS, 0,                                           MENU_TYPE_GROUP, 0);

Menu::elemento_insertar(G_TIEMPOS,                                              G_INTERACTIVO, TIEMPO_LECTURAS_SEGUNDOS,                MENU_TYPE_GROUP, 0);
    #include "Grupo_tiempos.h"


Menu::elemento_insertar(G_INTERACTIVO,                                          G_DISPOSITIVOS_DE_ENTRADA, G_LEDS,                      MENU_TYPE_GROUP, 0);

    Menu::elemento_insertar(G_LEDS,                                             G_LCD_7, LEDS_BRILLO,                                   MENU_TYPE_GROUP, 0);
        Menu::elemento_insertar(LEDS_BRILLO,                                    LEDS_RELES_FORZADO_ON, 0,                               MENU_TYPE_0_TO_10, 5);
        Menu::elemento_insertar(LEDS_RELES_FORZADO_ON,                          LEDS_RELES_FORZADO_OFF, 0,                              MENU_TYPE_RELE_FORZADO_MODO_LED, 2);
        Menu::elemento_insertar(LEDS_RELES_FORZADO_OFF,                         LEDS_VINCULAR_RELES_EVENTOS, 0,                        MENU_TYPE_RELE_FORZADO_MODO_LED, 0);
        Menu::elemento_insertar(LEDS_VINCULAR_RELES_EVENTOS,                    LEDS_VINCULAR_RELES_FORZADOS, 0,                        MENU_TYPE_BOOL, 0);
        Menu::elemento_insertar(LEDS_VINCULAR_RELES_FORZADOS,                   0, 0,                                                   MENU_TYPE_BOOL, 0);

    Menu::elemento_insertar(G_LCD_7,                                            BUZZER_ON_OFF, LCD_7_ON_OFF,                            MENU_TYPE_GROUP, 0);
        Menu::elemento_insertar(LCD_7_ON_OFF,                                   LCD_7_DIR, 0,                                           MENU_TYPE_ACTIVAR, 0);
        Menu::elemento_insertar(LCD_7_DIR,                                      LCD_7_BRILLO, 0,                                        MENU_TYPE_SONDA_SELECTOR, 0);
        Menu::elemento_insertar(LCD_7_BRILLO,                                   0, 0,                                                   MENU_TYPE_0_TO_10, 5);

    Menu::elemento_insertar(BUZZER_ON_OFF,                                      0, 0,                                                   MENU_TYPE_ACTIVAR, 1);

Menu::elemento_insertar(G_DISPOSITIVOS_DE_ENTRADA,                              G_DISPOSITIVOS_DE_SALIDA, G_SONDAS,                     MENU_TYPE_GROUP, 0);

    Menu::elemento_insertar(G_SONDAS,                                           G_AGUA, SONDAS_ON_OFF,                                  MENU_TYPE_GROUP, 0);
        Menu::elemento_insertar(SONDAS_ON_OFF,                                  SONDAS_ESCALA, 0,                                       MENU_TYPE_ACTIVAR, 1);
        Menu::elemento_insertar(SONDAS_ESCALA,                                  SONDA_DEPOSITO_DIR, 0,                                  MENU_TYPE_BOOL, 0);
        Menu::elemento_insertar(SONDA_DEPOSITO_DIR,                             SONDA_ZTERMOSTATO_DIR, 0,                               MENU_TYPE_SONDA_SELECTOR, 0);
        Menu::elemento_insertar(SONDA_ZTERMOSTATO_DIR,                          G_SONDA_COLECTOR_1, 0,                                  MENU_TYPE_SONDA_SELECTOR, 0);
        menu_next_subgroup = G_SONDA_ZONA_1;
        #include "Grupo_sondas_colectores.h"
        #include "Grupo_sondas_zonas.h"

    Menu::elemento_insertar(G_AGUA,                                             0, AGUA_ON_OFF,                                         MENU_TYPE_GROUP, 0);
        #include "Grupo_agua.h"

Menu::elemento_insertar(G_DISPOSITIVOS_DE_SALIDA,                               G_EVENTOS, G_BOMBAS,                               MENU_TYPE_GROUP, 0);

    Menu::elemento_insertar(G_BOMBAS,                                           G_REFRIGERAR_COLECTORES, G_BOMBA_1,                     MENU_TYPE_GROUP, 0);
        #include "Grupo_bombas.h"

    Menu::elemento_insertar(G_REFRIGERAR_COLECTORES,                            G_CALENTADOR_DEPOSITO, G_REFRIGERAR_COLECTOR_1,         MENU_TYPE_GROUP, 0);
        #include "Grupo_refrigerar_colectores.h"

    Menu::elemento_insertar(G_CALENTADOR_DEPOSITO,                              0, CALENTADOR_DEPOSITO_ON_OFF,                          MENU_TYPE_GROUP, 0);
        #include "Grupo_calentador_deposito.h"

Menu::elemento_insertar(G_EVENTOS,                                              G_RELES, EVENTOS_ON_OFF,                                MENU_TYPE_GROUP, 0);
    #include "Grupo_eventos.h"

Menu::elemento_insertar(G_RELES,                                                G_SERIAL_DEBUG, RELES_ON_OFF,                           MENU_TYPE_GROUP, 0);
    #include "Grupo_reles.h"

Menu::elemento_insertar(G_TESTS,                                                C_SETUP_BORRAR, C_TEST_BUZZER,                          MENU_TYPE_GROUP, 0);
    Menu::elemento_insertar(C_TEST_BUZZER,                                      C_TEST_LEDS, 0,                                         MENU_TYPE_FUNCTION, 0);
    Menu::elemento_insertar(C_TEST_LEDS,                                        C_TEST_LCD_7, 0,                                        MENU_TYPE_FUNCTION, 0);
    Menu::elemento_insertar(C_TEST_LCD_7,                                       C_TEST_RELES, 0,                                        MENU_TYPE_FUNCTION, 0);
    Menu::elemento_insertar(C_TEST_RELES,                                       0, 0,                                                   MENU_TYPE_FUNCTION, 0);

Menu::elemento_insertar(C_SETUP_BORRAR,                                         C_SETUP_GUARDAR, 0,                                     MENU_TYPE_FUNCTION, 0);
Menu::elemento_insertar(C_SETUP_GUARDAR,                                        C_RESET, 0,                                             MENU_TYPE_FUNCTION, 0);
Menu::elemento_insertar(C_RESET,                                                C_ABOUT, 0,                                             MENU_TYPE_FUNCTION, 0);

Menu::elemento_insertar(C_ABOUT,                                                0, 0,                                                   MENU_TYPE_FUNCTION, 0);

#endif