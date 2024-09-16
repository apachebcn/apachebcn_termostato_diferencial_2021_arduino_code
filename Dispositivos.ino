bool Dispositivos::_es_dispositivo_entrada(int dispositivo_id)
{
    if (dispositivo_id >= DISPOSITIVO_DE_ENTRADA_PRIMER_ID && dispositivo_id <= (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA)) 
    {
        return TRUE;
    }
    return FALSE;
}

bool Dispositivos::_es_dispositivo_salida(int dispositivo_id)
{
    if (dispositivo_id >= DISPOSITIVO_DE_SALIDA_PRIMER_ID && dispositivo_id <= (DISPOSITIVO_DE_SALIDA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_SALIDA))
    {
        return TRUE;
    }
    return FALSE;
}

void Dispositivos::_serial_alerta(const __FlashStringHelper* funcion_nombre, const __FlashStringHelper* dispositivo_tipo, int dispositivo_id)
{
    Serial_debug::println();
    Serial_debug::print(F("ALERTA"));
    Serial_debug::write(':');
    Serial_debug::write(' ');
    Serial_debug::print(F("Dispositivos")); Serial_debug::write(':'); Serial_debug::write(':');
    Serial_debug::print(funcion_nombre);
    Serial_debug::write(' ');
    Serial_debug::print(dispositivo_tipo);
    Serial_debug::write(' ');
    Serial_debug::print(F("dispositivo_id"));
    Serial_debug::write(':');
    Serial_debug::write(' ');
    Serial_debug::print(dispositivo_id);
    Serial_debug::println(dispositivo_tipo);

    lcd.clear();
    lcd.print(F("Serial-Alerta "));
    lcd.print(dispositivo_id);
    delay(1000);
}

int Dispositivos::_bit_dispositivo(int dispositivo_id)
{
    int bit;
    if (_es_dispositivo_entrada(dispositivo_id)) 
    {
        bit = (dispositivo_id-DISPOSITIVO_DE_ENTRADA_PRIMER_ID);
        if (bit > TOTAL_DISPOSITIVOS_DE_ENTRADA-1)
        {
            _serial_alerta(F("bit_dispositivo"), F("DISPOSITIVOS DE ENTRADA"), dispositivo_id);
            return 0;
        }
        return bit;
    }
    bit = (dispositivo_id-DISPOSITIVO_DE_SALIDA_PRIMER_ID);
    if (bit > TOTAL_DISPOSITIVOS_DE_SALIDA-1)
    {
        _serial_alerta(F("bit_dispositivo"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
        return 0;
    }
    return bit;
}

byte Dispositivos::get_estado(int dispositivo_id) 
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        return DE_estados_bits_[_bit_dispositivo(dispositivo_id)];
    }
    else
    {
        return DS_estados_bits_[_bit_dispositivo(dispositivo_id)];
    }
}

char Dispositivos::get_estado_icono(int dispositivo_id) 
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        return DE_estados_icono_bits_[_bit_dispositivo(dispositivo_id)];
    }
    else
    {
        _serial_alerta(F("get_estado_icono"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
        return ' ';
    }
}

float Dispositivos::get_entrada_valor(int dispositivo_id) 
{
    if (!_es_dispositivo_entrada(dispositivo_id))
    {
        _serial_alerta(F("entrada::get_valor"), F("DISPOSITIVOS DE ENTRADA"), dispositivo_id);
        return 0;
    }
    int bit = _bit_dispositivo(dispositivo_id);
    return DE_valores_bits_[bit];
}

void Dispositivos::set_entrada_valor(int dispositivo_id, float valor)
{
    if (!_es_dispositivo_entrada(dispositivo_id))
    {
        _serial_alerta(F("entrada::set_valor"), F("DISPOSITIVOS DE ENTRADA"), dispositivo_id);
        return;
    }
    int bit = _bit_dispositivo(dispositivo_id);
    DE_valores_bits_[bit] = valor;
}

float Dispositivos::get_entrada_valor_min(int dispositivo_id) 
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        return DE_valores_min_bits_[_bit_dispositivo(dispositivo_id)];
    }
    else
    {
        _serial_alerta(F("get_entrada_valor_min"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
        return 0;
    }
}

float Dispositivos::get_entrada_valor_max(int dispositivo_id) 
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        return DE_valores_max_bits_[_bit_dispositivo(dispositivo_id)];
    }
    else
    {
        _serial_alerta(F("get_entrada_valor_max"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
        return 0;
    }
}

byte Dispositivos::get_salida_valor(int dispositivo_id) 
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        _serial_alerta(F("salida::get_valor"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
        return 0;
    }
    int bit = _bit_dispositivo(dispositivo_id);
    return DS_valores_bits_[bit];
}

void Dispositivos::set_salida_valor(int dispositivo_id, byte valor)
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        _serial_alerta(F("salida::set_valor"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
        return;
    }
    int bit = _bit_dispositivo(dispositivo_id);
    DS_valores_bits_[bit] = valor;
}

int Dispositivos::get_rele(int dispositivo_id)
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        _serial_alerta(F("get_rele"), F("DISPOSITIVOS DE ENTRADA"), dispositivo_id);
        return 0;
    }

    if (!Menu::get_valor(RELES_ON_OFF)) return 0;

    int dispositivo_grupo_id = pertenece_a_grupo_de(dispositivo_id);
    int rele_id = 0;
    switch(dispositivo_grupo_id)
    {
        case DISPOSITIVO_DE_SALIDA_BOMBA_1:
            rele_id = Menu::get_valor(BOMBA_1_RELE_NUM, (dispositivo_id-DISPOSITIVO_DE_SALIDA_BOMBA_1));
            break;

        case DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1:
            rele_id = Menu::get_valor(BOMBA_1_RELE_NUM, (dispositivo_id-DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1));
            break;

        case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1:
            rele_id = Menu::get_valor(REFRIGERAR_COLECTOR_1_RELE_NUM, (dispositivo_id-DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1));
            break;

        case DISPOSITIVO_DE_SALIDA_CALENTADOR:
            rele_id = Menu::get_valor(CALENTADOR_DEPOSITO_RELE_NUM);
            break;

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_SALIDA_AGUA:         
                rele_id = Menu::get_valor(AGUA_RELE_NUM);
                break;
        #endif
    }
    return rele_id-1; //DISPOSITIVO SIN RELE
}

void Dispositivos::set_estado(int dispositivo_id, byte valor) 
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        DE_estados_bits_[_bit_dispositivo(dispositivo_id)] = valor;
    }
    else
    {
        DS_estados_bits_[_bit_dispositivo(dispositivo_id)] = valor;
    }
}

void Dispositivos::set_estado_icono(int dispositivo_id, byte valor) 
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        DE_estados_icono_bits_[_bit_dispositivo(dispositivo_id)] = valor;
    }
    else
    {
        _serial_alerta(F("set_estado_icono"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
    }
}

void Dispositivos::set_valor_min(int dispositivo_id, float valor)
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        int bit = _bit_dispositivo(dispositivo_id);
        DE_valores_min_bits_[bit] = valor;
    }
    else
    {
        _serial_alerta(F("set_valor_min"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
    }
}

void Dispositivos::set_valor_max(int dispositivo_id, float valor)
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        int bit = _bit_dispositivo(dispositivo_id);
        DE_valores_max_bits_[bit] = valor;
    }
    else
    {
        _serial_alerta(F("set_valor_max"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
    }
}

void Dispositivos::reset_valor_mins()
{
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++) 
    {
        int bit = _bit_dispositivo(dispositivo_id);
        DE_valores_min_bits_[bit] = VALOR_RESET_O_ERROR;
    }
}

void Dispositivos::reset_valor_maxs()
{
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++) 
    {
        DE_valores_max_bits_[_bit_dispositivo(dispositivo_id)] = VALOR_RESET_O_ERROR;
    }
}

void Dispositivos::init()
{
    int dispositivo_id;
    for(dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        set_estado(dispositivo_id, 0);
        set_estado_icono(dispositivo_id, ' ');
        Dispositivos::set_entrada_valor(dispositivo_id, VALOR_RESET_O_ERROR);
        set_valor_max(dispositivo_id, VALOR_RESET_O_ERROR);
        set_valor_min(dispositivo_id, VALOR_RESET_O_ERROR);
    }
    for(dispositivo_id = DISPOSITIVO_DE_SALIDA_PRIMER_ID; dispositivo_id < (TOTAL_DISPOSITIVOS_DE_SALIDA+DISPOSITIVO_DE_SALIDA_PRIMER_ID); dispositivo_id++)
    {
        set_estado(dispositivo_id, 0);
        set_salida_valor(dispositivo_id, 0);
    }
}

bool Dispositivos::inactivo(int dispositivo_id)
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        if (get_estado(dispositivo_id) == ESTADO_DISPOSITIVO_DE_ENTRADA_DESACTIVADO) return TRUE;
    }
    else
    {
        if (get_estado(dispositivo_id) == ESTADO_DISPOSITIVO_DE_SALIDA_DESACTIVADO) return TRUE;
    }
    return FALSE;
}

bool Dispositivos::disponible(int dispositivo_id)
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        if (get_estado(dispositivo_id) == ESTADO_DISPOSITIVO_DE_ENTRADA_DISPONIBLE) return TRUE;
    }
    else
    {
        if (get_estado(dispositivo_id) == ESTADO_DISPOSITIVO_DE_SALIDA_DISPONIBLE) return TRUE;
    }
    return FALSE;
}

bool Dispositivos::error(int dispositivo_id)
{
    if (_es_dispositivo_entrada(dispositivo_id))
    {
        if (get_estado(dispositivo_id) == ESTADO_DISPOSITIVO_DE_ENTRADA_ERROR) return TRUE;
    }
    else
    {
        _serial_alerta(F("error"), F("DISPOSITIVOS DE SALIDA"), dispositivo_id);
    }
    return FALSE;
}

int Dispositivos::pertenece_a_grupo_de(int dispositivo_id)
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (dispositivo_id >= DISPOSITIVO_DE_ENTRADA_ZONA_1 && dispositivo_id <= (DISPOSITIVO_DE_ENTRADA_ZONA_1+TOTAL_SONDAS_ZONAS-1))
        {
            return DISPOSITIVO_DE_ENTRADA_ZONA_1;
        }
        if (dispositivo_id >= DISPOSITIVO_DE_ENTRADA_COLECTOR_1 && dispositivo_id <= (DISPOSITIVO_DE_ENTRADA_COLECTOR_1+TOTAL_SONDAS_COLECTORES-1))
        {
            return DISPOSITIVO_DE_ENTRADA_COLECTOR_1;
        }
        if (dispositivo_id >= DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1 && dispositivo_id <= (DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1+TOTAL_SONDAS_COLECTORES-1))
        {
            return DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1;
        }
        if (dispositivo_id >= DISPOSITIVO_DE_SALIDA_BOMBA_1 && dispositivo_id <= (DISPOSITIVO_DE_SALIDA_BOMBA_1+TOTAL_SONDAS_COLECTORES-1))
        {
            return DISPOSITIVO_DE_SALIDA_BOMBA_1;
        }
        if (dispositivo_id >= DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1 && dispositivo_id <= (DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1+TOTAL_SONDAS_COLECTORES-1))
        {
            return DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1;
        }
    #endif
    return dispositivo_id;
}

bool Dispositivos::es_tipo_sonda(int dispositivo_id)
{
    if (!_es_dispositivo_entrada(dispositivo_id)) return FALSE;
    int dispositivo_grupo_id = pertenece_a_grupo_de(dispositivo_id);
    switch(dispositivo_grupo_id)
    {
        case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:
        case DISPOSITIVO_DE_ENTRADA_DEPOSITO:
        case DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO:
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_ENTRADA_ZONA_1:
            case DISPOSITIVO_DE_ENTRADA_LCD7:
        #endif
        return TRUE;
    }
    return FALSE;
}

void Dispositivos::_serial_print_nombre_estado(byte estado)
{
    switch(estado)
    {
        //case ESTADO_DISPOSITIVO_DE_SALIDA_DESACTIVADO:      
        case ESTADO_DISPOSITIVO_DE_ENTRADA_DESACTIVADO:     
            Serial_debug::print(F("DESACTIVADO"));
            return;
        //case ESTADO_DISPOSITIVO_DE_ENTRADA_DISPONIBLE:      
        case ESTADO_DISPOSITIVO_DE_SALIDA_DISPONIBLE:       
            Serial_debug::print(F("DISPONIBLE"));
            return;
        //case ESTADO_DISPOSITIVO_DE_ENTRADA_NO_DISPONIBLE:   
        case ESTADO_DISPOSITIVO_DE_SALIDA_NO_DISPONIBLE:   
            Serial_debug::print(F("NO DISPONIBLE"));
            return;
        case ESTADO_DISPOSITIVO_DE_ENTRADA_ERROR:           
            Serial_debug::print(F("ERROR"));
            return;
    }

    if (_es_dispositivo_entrada(estado))
    {
        serial_print_mensaje_depende_de_dispositivo(estado);
        return;
    }

    if (_es_dispositivo_salida(estado))
    {
        serial_print_mensaje_depende_de_dispositivo(estado);
        return;
    }

    Serial_debug::print(F("?"));
    return;
}

void Dispositivos::serial_print_mensaje_sonda_no_seleccionada()
{
    Serial_debug::write(' ');
    Serial_debug::write('[');
    Serial_debug::print(F("SONDA NO SELECCIONADA"));
    Serial_debug::write(']');
}

void Dispositivos::serial_print_imprimir_valor_temperatura(const __FlashStringHelper* etiqueta, float valor)
{
    Serial_debug::write(' '); 
    Serial_debug::print(etiqueta); 
    Serial_debug::write(':'); 
    if (valor == VALOR_RESET_O_ERROR)
    {
        Serial_debug::write('-');
    }
    else
    {
        Serial_debug::print((valor));
    }
}

const __FlashStringHelper* Dispositivos::nombre(int dispositivo_id)
{
    switch(dispositivo_id)
    {
        case DISPOSITIVO_DE_ENTRADA_DEPOSITO:               return F("Deposito"); 
        case DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO:            return F("Z-Termostato");
        case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:             return F("Colector-1");
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_ENTRADA_COLECTOR_2:         return F("Colector-2");
            case DISPOSITIVO_DE_ENTRADA_COLECTOR_3:         return F("Colector-3");
            case DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1:     return F("Pulsada-1");
            case DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_2:     return F("Pulsada-2");
            case DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_3:     return F("Pulsada-3");
            case DISPOSITIVO_DE_ENTRADA_ZONA_1:             return F("Zona-1");
            case DISPOSITIVO_DE_ENTRADA_ZONA_2:             return F("Zona-2");
            case DISPOSITIVO_DE_ENTRADA_ZONA_3:             return F("Zona-3");
            case DISPOSITIVO_DE_ENTRADA_ZONA_4:             return F("Zona-4");
            case DISPOSITIVO_DE_ENTRADA_ZONA_5:             return F("Zona-5");
            case DISPOSITIVO_DE_ENTRADA_ZONA_6:             return F("Zona-6");
            case DISPOSITIVO_DE_ENTRADA_ZONA_7:             return F("Zona-7");
            case DISPOSITIVO_DE_ENTRADA_ZONA_8:             return F("Zona-8");
            case DISPOSITIVO_DE_ENTRADA_ZONA_9:             return F("Zona-9");
            case DISPOSITIVO_DE_ENTRADA_ZONA_10:            return F("Zona-10");
            case DISPOSITIVO_DE_ENTRADA_AGUA:               return F("Agua");
            case DISPOSITIVO_DE_ENTRADA_LCD7:               return F("Lcd-7");
        #endif
        case -1:                                            return F("Nada");
        case DISPOSITIVO_DE_SALIDA_CALENTADOR:              return F("Calentador");
        case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1:          return F("Refrigerador-1");
        case DISPOSITIVO_DE_SALIDA_BOMBA_1:                 return F("Bomba-1");
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_SALIDA_BOMBA_2:             return F("Bomba-2");
            case DISPOSITIVO_DE_SALIDA_BOMBA_3:             return F("Bomba-3");
            case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_2:      return F("Refrigerador-2");
            case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_3:      return F("Refrigerador-3");
            case DISPOSITIVO_DE_SALIDA_AGUA:                return F("Agua");
        #endif
        }
    return F("?");
}

const __FlashStringHelper* Dispositivos::nombre_corto(int dispositivo_id)
{
    switch(dispositivo_id)
    {
        case DISPOSITIVO_DE_ENTRADA_DEPOSITO:             return F("Dep"); 
        case DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO:          return F("Z-Term");
        case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:           return F("Col1");
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_ENTRADA_AGUA:             return F("Agua");
            case DISPOSITIVO_DE_ENTRADA_LCD7:             return F("Lcd7");
            case DISPOSITIVO_DE_ENTRADA_COLECTOR_2:       return F("Col2");
            case DISPOSITIVO_DE_ENTRADA_COLECTOR_3:       return F("Col3");
            case DISPOSITIVO_DE_ENTRADA_ZONA_1:           return F("Zona1");
            case DISPOSITIVO_DE_ENTRADA_ZONA_2:           return F("Zona2");
            case DISPOSITIVO_DE_ENTRADA_ZONA_3:           return F("Zona3");
            case DISPOSITIVO_DE_ENTRADA_ZONA_4:           return F("Zona4");
            case DISPOSITIVO_DE_ENTRADA_ZONA_5:           return F("Zona5");
            case DISPOSITIVO_DE_ENTRADA_ZONA_6:           return F("Zona6");
            case DISPOSITIVO_DE_ENTRADA_ZONA_7:           return F("Zona7");
            case DISPOSITIVO_DE_ENTRADA_ZONA_8:           return F("Zona8");
            case DISPOSITIVO_DE_ENTRADA_ZONA_9:           return F("Zona9");
            case DISPOSITIVO_DE_ENTRADA_ZONA_10:          return F("Zona10");
        #endif
        }
    return F("?");
}

void Dispositivos::serial_print_mensaje_dispositivo_apagado()
{
    Serial_debug::write(' ');
    Serial_debug::write('[');
    Serial_debug::print(F("DISPOSITIVO APAGADO"));
    Serial_debug::write(']');
}

void Dispositivos::serial_print_mensaje_dispositivo_no_disponible()
{
    Serial_debug::write(' ');
    Serial_debug::write('[');
    Serial_debug::print(F("DISPOSITIVO NO DISPONIBLE"));
    Serial_debug::write(']');
}

void Dispositivos::serial_print_mensaje_depende_de_dispositivo(int dispositivo_id)
{
    Serial_debug::write(' ');
    Serial_debug::print(F("DEPENDE DEL DISPOSITIVO")); 
    Serial_debug::write(' '); Serial_debug::write('-'); 
    Serial_debug::print(nombre(dispositivo_id)); 
    Serial_debug::write('-'); Serial_debug::write(' '); 
    Serial_debug::print(F("(PERO NO ESTA DISPONIBLE)")); 
}

void Dispositivos::serial_print_sonda_datos(int dispositivo_id)
{
    // MOSTRAR SONDA DIR
    Serial_debug::write(' ');
    Serial_debug::print(F("Sonda-dir")); Serial_debug::write(':'); Serial_debug::write(' '); Serial_debug::write('#'); 
    int dispositivo_grupo_id = pertenece_a_grupo_de(dispositivo_id);
    switch(dispositivo_grupo_id)
    {
        case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:
            Sondas::serial_print_addr_dir(Sondas_colector_dir[dispositivo_id-dispositivo_grupo_id]);
            break;

        case DISPOSITIVO_DE_ENTRADA_DEPOSITO:
            Sondas::serial_print_addr_dir(Sondas_deposito_dir);
            break;

        case DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO:
            Sondas::serial_print_addr_dir(Sondas_ztermostato_dir);
            break;

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_ENTRADA_LCD7:
                Sondas::serial_print_addr_dir(Sondas_lcd7_dir);
                break;

            case DISPOSITIVO_DE_ENTRADA_ZONA_1:
                Sondas::serial_print_addr_dir(Sondas_zona_dir[dispositivo_id-dispositivo_grupo_id]);
                break;
        #endif
        default: Serial_debug::print(dispositivo_id);Serial_debug::print(F("?"));
    }

    Serial_debug::write(' '); 
    
    Serial_debug::print(F("Valor"));       
    Serial_debug::write(':'); Serial_debug::write(' '); Serial_debug::print(Dispositivos::get_entrada_valor(dispositivo_id));
    Serial_debug::write(';'); Serial_debug::write(' '); 

    Serial_debug::print(F("Min"));         
    Serial_debug::write(':'); Serial_debug::print(get_entrada_valor_min(dispositivo_id));
    Serial_debug::write(';'); Serial_debug::write(' '); 

    Serial_debug::print(F("Max"));         
    Serial_debug::write(':'); Serial_debug::print(get_entrada_valor_max(dispositivo_id));
    Serial_debug::write(';'); Serial_debug::write(' '); 
}

void Dispositivos::serial_print_debug_dispositivos_entrada()
{
    Serial_debug::println(); Serial_debug::println(); 
    Serial_debug::write('-'); Serial_debug::write('-'); Serial_debug::write(' ');
    Serial_debug::print(F("DEBUG DISPOSITIVOS DE")); Serial_debug::write(' '); 
    Serial_debug::print(F("ENTRADA"));
    Serial_debug::write(' '); Serial_debug::write('-'); Serial_debug::write('-');
    Serial_debug::println();
    int desde = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; 
    int hasta = DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA;
    serial_print_debug_dispositivos(desde, hasta);
}

void Dispositivos::serial_print_debug_dispositivos_salida()
{
    Serial_debug::println(); Serial_debug::println(); 
    Serial_debug::write('-'); Serial_debug::write('-'); Serial_debug::write(' ');
    Serial_debug::print(F("DEBUG DISPOSITIVOS DE")); Serial_debug::write(' '); 
    Serial_debug::print(F("SALIDA"));
    Serial_debug::write(' '); Serial_debug::write('-'); Serial_debug::write('-');
    Serial_debug::println();
    int desde = DISPOSITIVO_DE_SALIDA_PRIMER_ID; 
    int hasta = DISPOSITIVO_DE_SALIDA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_SALIDA;
    serial_print_debug_dispositivos(desde, hasta);
}

void Dispositivos::serial_print_debug_dispositivos(int desde, int hasta)
{

    int dispositivo_id;
    for(dispositivo_id = desde; dispositivo_id < hasta; dispositivo_id++)
    {
        Serial_debug::print(F("Dispositivo")); Serial_debug::write(':'); Serial_debug::write(' ');
        Serial_debug::print(nombre(dispositivo_id)); Serial_debug::write(';'); Serial_debug::write(' ');
        Serial_debug::print(F("Estado")); Serial_debug::write(':'); Serial_debug::write(' ');
        _serial_print_nombre_estado(get_estado(dispositivo_id));
        Serial_debug::write(';'); Serial_debug::write(' ');

        if (_es_dispositivo_entrada(dispositivo_id))
        {
            if (es_tipo_sonda(dispositivo_id))
            {
                serial_print_sonda_datos(dispositivo_id);
            }
            else
            {
                Serial_debug::print(F("Valor")); Serial_debug::write(':'); Serial_debug::write(' ');
                Serial_debug::print(Dispositivos::get_entrada_valor(dispositivo_id));
                Serial_debug::write(';'); Serial_debug::write(' ');
            }
        }
        else
        {
            Serial_debug::print(F("Valor")); Serial_debug::write(':'); Serial_debug::write(' ');
            Serial_debug::print(Dispositivos::get_salida_valor(dispositivo_id));
            Serial_debug::write(';'); Serial_debug::write(' ');
        }
        
        if (_es_dispositivo_salida(dispositivo_id))
        {
            Serial_debug::print(F("Rele")); Serial_debug::write(':'); Serial_debug::write(' '); Serial_debug::write('#');
            Serial_debug::print(get_rele(dispositivo_id)+1);
            Serial_debug::write(';');
        }

        Serial_debug::println();
    }
}