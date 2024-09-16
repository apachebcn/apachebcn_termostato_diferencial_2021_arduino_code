Menu::elemento_insertar(AGUA_ON_OFF,                                        AGUA_RELE_NUM, 0,                                  MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(AGUA_RELE_NUM,                                      AGUA_ALTURA_PUNTOS, 0,                                                   MENU_TYPE_RELE_SELECTOR, 0); 
Menu::elemento_insertar(AGUA_ALTURA_PUNTOS,                                 AGUA_CAPACIDAD_TOTAL, 0,                                MENU_TYPE_2_TO_255, 10);
Menu::elemento_insertar(AGUA_CAPACIDAD_TOTAL,                               AGUA_TECHO_VIRTUAL, 0,                                  MENU_TYPE_1_TO_32000, 200);
Menu::elemento_insertar(AGUA_TECHO_VIRTUAL,                                 AGUA_SUELO_VIRTUAL, 0,                                  MENU_TYPE_0_TO_255, 9);
Menu::elemento_insertar(AGUA_SUELO_VIRTUAL,                                 AGUA_MANTENER_TEMP_ON_OFF, 0,                           MENU_TYPE_1_TO_255, 1);
Menu::elemento_insertar(AGUA_MANTENER_TEMP_ON_OFF,                          AGUA_STOP_ON_OFF, AGUA_MANTENER_TEMP,                   MENU_TYPE_ACTIVAR, 0); 
    Menu::elemento_insertar(AGUA_MANTENER_TEMP,                             0, 0,                                                   MENU_TYPE_MINUS_255_TO_255, 0); 
Menu::elemento_insertar(AGUA_STOP_ON_OFF,                                   AGUA_ESCALA, 0,                                         MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(AGUA_ESCALA,                                        0, 0,                                       MENU_TYPE_BOOL, 0); 

