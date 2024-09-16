byte Pantalla::iniciar()
{
    byte error, address;

    Wire.begin();

    for(address = 1; address < 127; address++ ) 
    {
        // The i2c_scanner uses the return valor of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            lcd._Addr = address;
            lcd.begin(PANTALLA_ANCHO_PX, PANTALLA_ALTO_PX);
            Pantalla::encender();
            return address;
        }
    }
    return 0;
}

void Pantalla::cargar_iconos()
{
    byte icon[8];

    icon[0] = B00100; icon[1] = B01110; icon[2] = B11111; icon[3] = B00100; icon[4] = B00100; icon[5] = B00100; icon[6] = B00100; icon[7] = B00100;
    lcd.createChar(ICON_UP, icon);

    icon[0] = 0b00100; icon[1] = 0b00100; icon[2] = 0b00100; icon[3] = 0b00100; icon[4] = 0b00100; icon[5] = 0b11111; icon[6] = 0b01110; icon[7] = 0b00100;
    lcd.createChar(ICON_DOWN, icon);

    icon[0] = 0b00000; icon[1] = 0b00000; icon[2] = 0b00100; icon[3] = 0b00110; icon[4] = 0b11111; icon[5] = 0b00110; icon[6] = 0b00100; icon[7] = 0b00000;
    lcd.createChar(ICON_RIGHT, icon);

    icon[0] = 0x0; icon[1] = 0xe; icon[2] = 0x15; icon[3] = 0x17; icon[4] = 0x11; icon[5] = 0xe; icon[6] = 0x0; icon[7] = 0x0;
    lcd.createChar(ICON_WAITING, icon);
    
    icon[0] = B00100; icon[1] = B01010; icon[2] = B01010; icon[3] = B01110; icon[4] = B01110; icon[5] = B11111; icon[6] = B11111; icon[7] = B01110;
    lcd.createChar(ICON_TEMP, icon);

    icon[0] = 0b00000; icon[1] = 0b00000; icon[2] = 0b01110; icon[3] = 0b01110; icon[4] = 0b01110; icon[5] = 0b01110; icon[6] = 0b00000; icon[7] = 0b00000;
    lcd.createChar(ICON_STOP, icon);

    icon[0] = B10000; icon[1] = B11000; icon[2] = B11100; icon[3] = B11110; icon[4] = B11100; icon[5] = B11000; icon[6] = B10000; icon[7] = B00000;
    lcd.createChar(ICON_PLAY, icon);

    icon[0] = B10000; icon[1] = B11000; icon[2] = B11100; icon[3] = B11110; icon[4] = B11100; icon[5] = B11000; icon[6] = B10000; icon[7] = B00000;
    lcd.createChar(ICON_PLAY, icon);

    icon[0] = 0x4; icon[1] = 0xe; icon[2] = 0xe; icon[3] = 0xe; icon[4] = 0x1f; icon[5] = 0x0; icon[6] = 0x4; icon[7] = 0;
    lcd.createChar(ICON_ALARM, icon);

}

void Pantalla::borrar_fila(byte fila)
{
    borrar_media_fila(0, fila); borrar_media_fila((PANTALLA_ANCHO_PX/2), fila);
    lcd.setCursor(0, fila);
}
    
void Pantalla::borrar_media_fila(byte x, byte y)
{
    lcd.setCursor(x, y);
    for(byte i=0; i < PANTALLA_ANCHO_PX/2; i++)
    {
        lcd.write(' ');
    }
    lcd.setCursor(x, y);
}

void Pantalla::print_centrado(const __FlashStringHelper* texto, byte pos_y)
{
    borrar_fila(pos_y);
    PGM_P p = reinterpret_cast<PGM_P>(texto);
    byte longitud = FC::FlashStringHelper_len(texto, PANTALLA_ANCHO_PX);
    byte pos_x;
    byte cursor_x;
    float medio_frase = (float)longitud / 2;
    byte round = round(medio_frase);
    pos_x = (PANTALLA_ANCHO_PX/2)-round;
    cursor_x = pos_x;
    for(byte l=0; l<longitud; l++)
    {
        if (cursor_x < (PANTALLA_ANCHO_PX))
        {
            char caracter = pgm_read_byte(p);
            if (caracter == 0) continue;
            if (caracter == '\0') continue;
            lcd.setCursor(cursor_x, pos_y);
            lcd.print(caracter);
            cursor_x++; p++;
        }
    }
}

void Pantalla::mostrar_visor_reles()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        borrar_fila(3);
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        borrar_fila(1);
    #endif

    if (!Menu::get_valor(RELES_ON_OFF))
    {
        lcd.print(F("RELES OFF"));
        return;
    }

    for(byte bucle = 0; bucle < TOTAL_RELES; bucle++)
    {
        switch(Reles::get_valor(bucle))
        {
            case RELE_FLAG_FORZADO_ON:
                lcd.write(ICON_UP); 
                break;
            case RELE_FLAG_FORZADO_OFF:
                lcd.write(ICON_DOWN); 
                break;
            case RELE_FLAG_AUTO_ON:
                lcd.write('1'); 
                break;
            case RELE_FLAG_AUTO_OFF:
                lcd.write('0'); 
                break;
        }
    }
}

void Pantalla::encender()
{
    Pantalla_luz = 1;
    lcd.backlight();
    Pantalla_luz_timer_ = millis();
}

void Pantalla::apagar()
{
    Pantalla_luz = 0;
    lcd.noBacklight();
}

void Pantalla::borrar()
{
    lcd.clear();    
}

void Pantalla::insertar_info_msg(byte mensaje_id)
{
    front_mensaje_info_lcd = mensaje_id; //Mensajes definidos en Pantalla.h
    refresca_pantalla_timer_ = millis()+1500;
}

void Pantalla::mostrar_info_msg()
{
    if (!front_mensaje_info_lcd) return;

    // IMPRIME EN LCD MENSAJE INFO EN LA ULTIMA FILA
    switch(front_mensaje_info_lcd)
    {
        case MENSAJE_INFO_RESET:
            Pantalla::print_centrado(F("RESET"), DISPLAY_INFO_POS_Y);
            break;
        case MENSAJE_INFO_SILENCIAR:
            Pantalla::print_centrado(F("SILENCIAR"), DISPLAY_INFO_POS_Y);
            break;
        case MENSAJE_BLOQUEAR_TECLADO:
            Pantalla::print_centrado(F("BLOQUEADO"), DISPLAY_INFO_POS_Y);
            break;
    }
    front_mensaje_info_lcd = 0;
}

void Pantalla::mostrar_modo_vista()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        switch(Pantalla_modo_vista)
        {
            case VISTA_NORMAL: 
                print_centrado(F("NORMAL"), DISPLAY_INFO_POS_Y);
                break;
            case VISTA_ALARMAS: 
                print_centrado(F("ALARMAS"), DISPLAY_INFO_POS_Y);
                break;
            case VISTA_EVENTOS:
                print_centrado(F("EVENTOS"), DISPLAY_INFO_POS_Y);
                break;
            case VISTA_STAT_MAX:
                print_centrado(F("MAX"), DISPLAY_INFO_POS_Y);
                break;
            case VISTA_STAT_MIN:
                print_centrado(F("MIN"), DISPLAY_INFO_POS_Y);
                break;
            case VISTA_SONDAS:
                print_centrado(F("SONDAS"), DISPLAY_INFO_POS_Y);
                break;
        }
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        switch(Pantalla_modo_vista)
        {
            case VISTA_NORMAL:
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 0); lcd.print(F("|N"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 1); lcd.print(F("|O"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 2); lcd.print(F("|R"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 3); lcd.print(F("|M"));
                break;

            case VISTA_ALARMAS:
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 0); lcd.print(F("|A"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 1); lcd.print(F("|L"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 2); lcd.print(F("|R"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 3); lcd.print(F("|M"));
                break;

            case VISTA_EVENTOS:
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 0); lcd.print(F("|E"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 1); lcd.print(F("|V"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 2); lcd.print(F("|E"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 3); lcd.print(F("|N"));
                break;

            case VISTA_STAT_MIN:
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 0); lcd.print(F("|M"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 1); lcd.print(F("|I"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 2); lcd.print(F("|N"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 3); lcd.print(F("| "));
                break;

            case VISTA_STAT_MAX:
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 0); lcd.print(F("|M"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 1); lcd.print(F("|A"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 2); lcd.print(F("|X"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 3); lcd.print(F("| "));
                break;

            case VISTA_SONDAS:
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 0); lcd.print(F("|S"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 1); lcd.print(F("|O"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 2); lcd.print(F("|N"));
                lcd.setCursor(PANTALLA_ANCHO_PX - 2, 3); lcd.print(F("|D"));
                break;
        }
    #endif

    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        refresca_pantalla_timer_ = millis()+1500;
    #endif
}

void Pantalla::print_pantalla_eventos()
{
    if (!Menu::get_valor(EVENTOS_ON_OFF))
    {
        lcd.print(F("EVENTOS OFF"));
        return;
    }
    if (!Menu::get_valor(RELES_ON_OFF))
    {
        lcd.print(F("RELES OFF"));
        return;
    }
    bool activado;
    int rele_num;
    for(int i=0; i < TOTAL_EVENTOS; i++)
    {

        if (!Dispositivos_eventos.activado(i))
        {
            lcd.print(ICON_DOWN);
            continue;
        }        
        int evento_rele_id = Dispositivos_eventos.get_rele_num(i);
        if (!evento_rele_id)
        {
            lcd.print(ICON_DOWN);
            continue;
        }
        if (Reles::get_valor(evento_rele_id))
        {
            lcd.print(ICON_UP);
            continue;
        }
        lcd.print(ICON_DOWN);
    }
}

int Pantalla::_get_dec(float valor)
{
    valor = abs(valor);
    int p_ent = (int)valor;
    float p_dec;
    p_dec = (valor - p_ent);
    p_dec *= 10;
    p_ent = (int)p_dec;
    return p_ent;
}

void Pantalla::visor_sondas()
{
    byte lcd_x = 0;
    byte lcd_y = 0;

    borrar();

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        borrar_fila(DISPLAY_INFO_POS_Y);
    #endif

    if (!Sondas_total_escaneadas)
    {
        lcd.setCursor(0, 0);
        lcd.print(F("CERO SONDAS"));
        return;
    }
    Pantalla::borrar_fila(lcd_y);
    byte imprimido_por_fila = 0;
    float temp;
    for(byte bucle = 0; bucle < Sondas_total_escaneadas; bucle++)
    {
        lcd.setCursor(lcd_x, lcd_y);

        temp = Sondas::lee_la_sonda_num(bucle, 0);
        if (temp == VALOR_RESET_O_ERROR)
        {
            lcd.print(F("ERR"));
        }
        else
        {
            sprintf(Pantalla_buffer_segmento, "%d.%d%c", (int)temp, _get_dec(temp), (char)223);
            lcd.print(Pantalla_buffer_segmento);
        }
        imprimido_por_fila++;
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            lcd_x += 6;
            if (imprimido_por_fila == 3)
        #endif
        #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
            lcd_x += 6;
            if (imprimido_por_fila == 3)
        #endif
        {
            lcd_x = 0;
            lcd_y++;
            imprimido_por_fila = 0;
            borrar_fila(lcd_y);
        }
    }
}

void Pantalla::ver_about()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        lcd.clear();
        Pantalla::print_centrado(F("-misolarcasero.com-"), 0);
        Pantalla::print_centrado(F("apachebcn@gmail.com"), 1);
        Pantalla::print_centrado(F("PEDRO REINA ROJAS"), 2);
        lcd.setCursor(0, 3);
        lcd.write(' ');
        lcd.print(VERSION);
        lcd.print(F(" parche "));
        lcd.print(PARCHE);
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        lcd.clear();
        lcd.print(VERSION);
        lcd.write(' ');
        lcd.print(PARCHE);
        Pantalla::print_centrado(F("apachebcn@gmail"), 1);
    #endif
}
