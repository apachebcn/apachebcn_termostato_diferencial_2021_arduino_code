void Pantalla::imprime_dispositivos_valores(byte modo_vista)
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

    /* 
    * IMPRIMIR SONDAS COLECTORES
    */
    for(id = 0; id < TOTAL_SONDAS_COLECTORES; id++)
    {
        posX = 0; posY = id;
        decimales = 1;
        dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_COLECTOR_1+id;
        icono_dispositivo = 'C';
        icono_caracter_sufijo = (char)223;
        Pantalla::_imprime_dispositivo_id(
            modo_vista, 
            posX, 
            posY, 
            decimales, 
            dispositivo_entrada_id, 
            icono_dispositivo, 
            icono_caracter_sufijo);
    }

    /* 
    * IMPRIMIR SONDA Z-TERMOSTATO
    */
    posX = (PANTALLA_ANCHO_PX/2); posY = 0;
    decimales = 1;
    dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO;
    icono_dispositivo = ICON_TEMP;
    icono_caracter_sufijo = (char)223;
    Pantalla::_imprime_dispositivo_id(
        modo_vista, 
        posX, 
        posY, 
        decimales, 
        dispositivo_entrada_id, 
        icono_dispositivo, 
        icono_caracter_sufijo);

    /* 
    * IMPRIMIR SONDAS DEPOSITO
    */
    posX = (PANTALLA_ANCHO_PX/2); posY = 1;
    decimales = 1;
    dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_DEPOSITO;
    icono_dispositivo = 'D';
    icono_caracter_sufijo = (char)223;
    Pantalla::_imprime_dispositivo_id(
        modo_vista, 
        posX, 
        posY, 
        decimales, 
        dispositivo_entrada_id, 
        icono_dispositivo, 
        icono_caracter_sufijo);

    /* 
    * IMPRIMIR AGUA
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        posX = (PANTALLA_ANCHO_PX/2); posY = 2;
        decimales = 0;
        icono_caracter_sufijo = 'L';
        icono_dispositivo  = 'A';
        dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_AGUA;
        dispositivo_salida_id = DISPOSITIVO_DE_SALIDA_AGUA;
        Pantalla::_imprime_dispositivo_id(
            modo_vista, 
            posX, 
            posY, 
            decimales, 
            dispositivo_entrada_id, 
            icono_dispositivo, 
            icono_caracter_sufijo);
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
            decimales = 1;
            icono_dispositivo = 'Z';
            icono_caracter_sufijo = (char)223;
            dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_ZONA_1+id;
            Pantalla::_imprime_dispositivo_id(
                modo_vista, 
                posX, 
                posY, 
                decimales, 
                dispositivo_entrada_id, 
                icono_dispositivo, 
                icono_caracter_sufijo);
        }
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        borrar_media_fila(0, 1);
    #endif
}
