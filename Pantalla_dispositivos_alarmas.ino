void Pantalla::print_pantalla_alarmas()
{
    byte id;
    byte posX;
    byte posY;
    bool decimales;
    char icono_dispositivo;
    char icono_caracter_sufijo;
    int dispositivo_entrada_id;
    int dispositivo_salida_id;
    bool activado;
    bool disponible;
    bool error;

    Pantalla::borrar();

    /* 
    * IMPRIMIR SONDAS COLECTORES
    */
    for(id = 0; id < TOTAL_SONDAS_COLECTORES; id++)
    {
        posX = 0; posY = id;
        lcd.setCursor(posX, posY);
        dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_COLECTOR_1+id;
        lcd.write('C'); lcd.write(' ');
        Pantalla::_print_pantalla_alarmas_valor(dispositivo_entrada_id);
    }

    /* 
    * IMPRIMIR SONDA Z-TERMOSTATO
    */
    posX = (PANTALLA_ANCHO_PX/2); posY = 0;
    lcd.setCursor(posX, posY);
    dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO;
    lcd.write(ICON_TEMP); lcd.write(' ');
    Pantalla::_print_pantalla_alarmas_valor(dispositivo_entrada_id);

    /* 
    * IMPRIMIR SONDAS DEPOSITO
    */
    posX = (PANTALLA_ANCHO_PX/2); posY = 1;
    lcd.setCursor(posX, posY);
    dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_DEPOSITO;
    lcd.write('D'); lcd.write(' ');
    Pantalla::_print_pantalla_alarmas_valor(dispositivo_entrada_id);

    /* 
    * IMPRIMIR AGUA
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        posX = (PANTALLA_ANCHO_PX/2); posY = 2;
        lcd.setCursor(posX, posY);
        lcd.write('A'); lcd.write(' ');
        Pantalla::_print_pantalla_alarmas_valor(dispositivo_entrada_id);
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        _imprime_dispositivo_inactivado(posX, posY, icono_dispositivo);
    #endif

    /* 
    * IMPRIMIR SONDAS ZONAS 1 Y 2
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        for(id = 0; id < 2; id++)
        {
            posX = (PANTALLA_ANCHO_PX/2)*id; posY = 3;
            lcd.setCursor(posX, posY);
            dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_ZONA_1+id;
            lcd.write('Z'); lcd.write(' ');
            Pantalla::_print_pantalla_alarmas_valor(dispositivo_entrada_id);
        }
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        borrar_media_fila(0, 1);
    #endif
}

