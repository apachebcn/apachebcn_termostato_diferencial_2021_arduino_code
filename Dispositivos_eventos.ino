void Dispositivos_eventos::init()
{
    byte evento_id;
    for(evento_id = 0; evento_id < TOTAL_EVENTOS; evento_id++)
    {
        _estados_bits_[evento_id] = 0;
        _valores_bits_[evento_id] = 0;
    }
}

bool Dispositivos_eventos::activado(int evento_id)           {return Menu::get_valor(EVENTO_1_ON_OFF, evento_id);}
int Dispositivos_eventos::get_rele_num(int evento_id)        {return Menu::get_valor(EVENTO_1_RELE_NUM, evento_id);}
bool Dispositivos_eventos::get_rele_accion(int evento_id)    {return Menu::get_valor(EVENTO_1_RELE_ACCION, evento_id);}
int Dispositivos_eventos::get_dispositivo(int evento_id)     {return Menu::get_valor(EVENTO_1_DISPOSITIVO, evento_id);}
bool Dispositivos_eventos::get_alarma(int evento_id)         {return Menu::get_valor(EVENTO_1_ES_ALARMA, evento_id);}
bool Dispositivos_eventos::get_operacion(int evento_id)      {return Menu::get_valor(EVENTO_1_OPERACION, evento_id);}
int Dispositivos_eventos::get_valor(int evento_id)           {return Menu::get_valor(EVENTO_1_VALOR, evento_id);}
int Dispositivos_eventos::get_diff_off(int evento_id)        {return Menu::get_valor(EVENTO_1_DIFF_OFF, evento_id);}

bool Dispositivos_eventos::disponible(int dispositivo_id)
{
    for(byte evento_id = 0; evento_id < TOTAL_EVENTOS; evento_id++)
    {
        if (activado(evento_id))
        {
            if (get_dispositivo(evento_id) == dispositivo_id)
            {
                if (get_rele_num(evento_id)) return TRUE;
            }
        }
    }    
    return FALSE;
}

int Dispositivos_eventos::ultimo_ejecutando(int dispositivo_id, bool alarma)
{
    int evento_seleccionado = -1;
    for(byte evento_id = 0; evento_id < TOTAL_EVENTOS; evento_id++)
    {
        if (activado(evento_id) && valor(evento_id) && get_rele_num(evento_id))
        {
            if (get_dispositivo(evento_id) == dispositivo_id)
            {
                if (get_alarma(evento_id) == alarma)
                {
                    evento_seleccionado = evento_id;
                }
            }
        }
    }    
    return evento_seleccionado;
}

bool Dispositivos_eventos::_validar_operacion(bool evento_operacion, float valor_dispositivo, int valor_evento)
{
    if (evento_operacion == 0)
    {
        //evento_operacion <
        if (valor_dispositivo < valor_evento)
        {
            return 1;
        }
    }

    if (evento_operacion == 1)
    {
        //evento_operacion >
            if (valor_dispositivo > valor_evento)
            {
                return 1;
            }
    }

    return 0;
}

void Dispositivos_eventos::_serial_print_on_off(bool estado)
{
    if (estado) Serial_debug::print(F("ON")); else Serial_debug::print(F("OFF"));
}

void Dispositivos_eventos::calcular()
{
    if (FC::is_debug(DEBUG_EVENTOS))
    {
        Serial_debug::println(); Serial_debug::println(); Serial_debug::println(F("-- DEBUG EVENTOS --"));
    }

    byte evento_id;
    int dispositivo_id;
    bool evento_operacion_on;
    int evento_valor_on;
    int evento_valor_off;
    bool evento_operacion_off;
    int evento_rele_id;
    float valor_dispositivo;
    bool resultado;
    int diff;
    
    if (!Menu::get_valor(EVENTOS_ON_OFF))
    {
        // EVENTOS DESACTIVADOS
        Dispositivos_eventos::init();
        if (FC::is_debug(DEBUG_EVENTOS)) Serial_debug::println(F("Eventos Desactivados"));
        return;
    }

    if (!Menu::get_valor(RELES_ON_OFF))
    {
        // RELES OFF
        Dispositivos_eventos::init();
        if (FC::is_debug(DEBUG_EVENTOS)) Serial_debug::println(F("Ignorando eventos porque: Reles desactivados"));
        return;
    }

    for(evento_id = 0; evento_id < TOTAL_EVENTOS; evento_id++)
    {
        _estados_bits_[evento_id] = EVENTOS_ESTADO_OFF;
        if (FC::is_debug(DEBUG_EVENTOS))
        {
            Serial_debug::print(F("Evento")); 
            Serial_debug::write(' '); Serial_debug::write('#'); 
            Serial_debug::println(evento_id+1); 
            Serial_debug::write(' '); 
            Serial_debug::print(F("Estado")); Serial_debug::write(':'); Serial_debug::write(' '); 
        }

        if (!activado(evento_id))
        {
            // EVENTO DESACTIVADO
            if (FC::is_debug(DEBUG_EVENTOS)) 
            {
                Serial_debug::println(F("Desactivado"));
            }
            continue;
        }

        if (FC::is_debug(DEBUG_EVENTOS))
        {
            Serial_debug::println(F("Activado"));
        }

        dispositivo_id = get_dispositivo(evento_id);
        if (dispositivo_id < 0)
        {
            // NO SE HA INDICADO DISPOSITIVO
            if (FC::is_debug(DEBUG_EVENTOS)) 
            {
                Serial_debug::write(' '); 
                Serial_debug::println(F("IGNORAR EVENTO")); Serial_debug::write(':'); Serial_debug::write(' '); 
                Serial_debug::println(F("Dispositivo no seleccionado"));
            }
            continue;
        }
        if (FC::is_debug(DEBUG_EVENTOS))
        {
            Serial_debug::write(' '); 
            Serial_debug::print(F("Dispositivo asociado")); Serial_debug::write(':'); Serial_debug::write(' '); 
            Serial_debug::println(Dispositivos.nombre(dispositivo_id));
        }

        if (Dispositivos.inactivo(dispositivo_id))
        {
            // DISPOSITIVO NO ACTIVADO
            if (FC::is_debug(DEBUG_EVENTOS)) 
            {
                Serial_debug::write(' '); 
                Serial_debug::println(F("IGNORAR EVENTO")); Serial_debug::write(':'); Serial_debug::write(' '); 
                Serial_debug::println(F("Dispositivo desactivado"));
            }
            continue;
        }

        if (!Dispositivos.disponible(dispositivo_id))
        {
            // DISPOSITIVO NO DISPONIBLE
            if (FC::is_debug(DEBUG_EVENTOS)) 
            {
                Serial_debug::write(' '); 
                Serial_debug::println(F("IGNORAR EVENTO")); Serial_debug::write(':'); Serial_debug::write(' '); 
                Serial_debug::println(F("Dispositivo no disponible"));
            }
            continue;
        }

        _estados_bits_[evento_id] = EVENTOS_ESTADO_ON;
        evento_rele_id = get_rele_num(evento_id);
        valor_dispositivo = Dispositivos.get_entrada_valor(dispositivo_id);
        evento_operacion_on = get_operacion(evento_id);
        evento_valor_on = get_valor(evento_id);
        evento_valor_off = evento_valor_on;
        diff = get_diff_off(evento_id);
        if (diff)
        {
            if (evento_operacion_on == 0)
            {
                //<
                evento_valor_off = evento_valor_on + diff;
            }
            if (evento_operacion_on == 1) 
            {
                //>
                evento_valor_off = evento_valor_on - diff;
            }
        }
        if (FC::is_debug(DEBUG_EVENTOS)) 
        {
            Serial_debug::write(' '); 
            Serial_debug::print(F("Valor actual")); Serial_debug::write(':'); Serial_debug::write(' ');
            Serial_debug::println(get_valor(dispositivo_id)); 

            Serial_debug::write(' '); 
            Serial_debug::print(F("Activar cuando")); Serial_debug::write(':'); Serial_debug::write(' ');
            Serial_debug::print(valor_dispositivo); 
            if (evento_operacion_on) Serial_debug::write('>'); else Serial_debug::write('<');
            Serial_debug::print(evento_valor_on);
            if (get_alarma(evento_id))
            {
                Serial_debug::write(' '); 
                Serial_debug::print(F("CON ALARMA"));
            }
            Serial_debug::println(); Serial_debug::write(' '); 
            Serial_debug::print(F("Desactivar cuando")); Serial_debug::write(':'); Serial_debug::write(' ');
            Serial_debug::print(valor_dispositivo); 
            if (!evento_operacion_on) Serial_debug::write('>'); else Serial_debug::write('<');
            Serial_debug::println(evento_valor_off) ;
        }

        if (!evento_rele_id)
        {
            if (FC::is_debug(DEBUG_EVENTOS)) 
            {
                Serial_debug::println(F("Ignorando evento porque: Rele #0"));
            }
            continue;
        }

        evento_rele_id--;
        bool cambiar_valor;
        switch(valor(evento_id))
        {
            case 0:
                cambiar_valor = _validar_operacion(evento_operacion_on, valor_dispositivo, evento_valor_on);
                break;
            case 1:
                cambiar_valor = _validar_operacion(!evento_operacion_on, valor_dispositivo, evento_valor_off);
                break;
        }

        if (cambiar_valor)
        {
            if (FC::is_debug(DEBUG_EVENTOS))
            {
                Serial_debug::write(' '); 
                Serial_debug::print(F("Algoritmo cumplido, conmutar estado")); Serial_debug::write(':');  Serial_debug::write(' '); 
                _serial_print_on_off(_valores_bits_[evento_id]);
                Serial_debug::print(F(" => "));
                _serial_print_on_off(!_valores_bits_[evento_id]);
                Serial_debug::println();
            }
            _valores_bits_[evento_id] = !_valores_bits_[evento_id];
        }
    }

}
