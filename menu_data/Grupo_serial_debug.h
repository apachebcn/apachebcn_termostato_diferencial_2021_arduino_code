Menu::elemento_insertar(SERIAL_DEBUG_ON_OFF,    SERIAL_DEBUG_BAUD, 0,       MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(SERIAL_DEBUG_BAUD,      DEBUG_SONDAS, 0,            MENU_TYPE_BAUD, 12);
Menu::elemento_insertar(DEBUG_SONDAS,           DEBUG_BOMBAS, 0,            MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(DEBUG_BOMBAS,           DEBUG_AGUA, 0,              MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(DEBUG_AGUA,             DEBUG_DISPOSITIVOS_IN, 0,   MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(DEBUG_DISPOSITIVOS_IN,  DEBUG_DISPOSITIVOS_OUT, 0,  MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(DEBUG_DISPOSITIVOS_OUT, DEBUG_EVENTOS, 0,           MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(DEBUG_EVENTOS,          DEBUG_ALARMAS, 0,           MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(DEBUG_ALARMAS,          DEBUG_RELES, 0,             MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(DEBUG_RELES,            0, 0,               		MENU_TYPE_ACTIVAR, 0);

