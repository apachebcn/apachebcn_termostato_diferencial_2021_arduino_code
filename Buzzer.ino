bool Buzzer::disponible()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        return (bool)Menu::get_valor(BUZZER_ON_OFF);
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        return TRUE;
    #endif
}

void Buzzer::actualiza_pin()
{
    if (disponible())
    {
        _activar();
    }
    else
    {
        _desactivar();
    }
}

void Buzzer::_activar()
{
    pinMode(PIN_BUZZER, OUTPUT);
}

void Buzzer::_desactivar()
{
    pinMode(PIN_BUZZER, 0);
}

void Buzzer::test(bool forzar_por_testing)
{
    if (!disponible() && !forzar_por_testing) 
    {
        return;
    }
    if (!disponible() && forzar_por_testing)
    {
        _activar();
    }
    tone(PIN_BUZZER, NOTE_DS6, 50); FC::delayMilisegundos(100);
    tone(PIN_BUZZER, NOTE_DS7, 50); FC::delayMilisegundos(100);
    tone(PIN_BUZZER, NOTE_DS8, 50); FC::delayMilisegundos(100);
    noTone(PIN_BUZZER);
    if (!disponible() && forzar_por_testing)
    {
        _desactivar();
    }
}

void Buzzer::beep_error()
{
    if (!disponible()) return;
    if (alarma_sonando()) return;
    on(); FC::delayMilisegundos(50); off(); FC::delayMilisegundos(30); 
    on(); FC::delayMilisegundos(50); off(); FC::delayMilisegundos(30); 
    on(); FC::delayMilisegundos(50); off(); FC::delayMilisegundos(30); 
}

void Buzzer::beep()
{
    if (!disponible()) return;
    if (alarma_sonando()) return;
    Pantalla::encender();
    on();
    FC::delayMilisegundos(2);
    off();
}

void Buzzer::beep_ultracorto()
{
    if (!disponible()) return;
    on();
    FC::delayMicrosegundos(25);
    off();
}

void Buzzer::beep_bloqueo()
{
    if (!disponible()) return;
    if (alarma_sonando()) return;
    beep();
}

void Buzzer::on()
{
    if (!disponible()) return;
    if (alarma_sonando()) return;
    digitalWrite(PIN_BUZZER, 1); 
}

void Buzzer::off()
{
    if (!disponible()) return;
    if (alarma_sonando()) return;
    digitalWrite(PIN_BUZZER, 0); 
}

void Buzzer::alarma_sonar()
{
    if (!disponible()) 
    {
        digitalWrite(PIN_BUZZER, 0); 
        return;
    }
    if (Buzzer::alarma_sonando())
    {
        digitalWrite(PIN_BUZZER, 1); 
    }
    else
    {
        digitalWrite(PIN_BUZZER, 0); 
    }
}

bool Buzzer::alarma_sonando()
{
    if (!Dispositivos_alarmas.existe_alarma_no_silenciada()) return FALSE;
    if (!Leds_tick_slow) return FALSE;
    if (Menu::get_valor(TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS))
    {
        if ( FC::if_diff_to_millis(Dispositivos_alarmas_inicio_buzzer_timer_, (1000*Menu::get_valor(TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS))) ) 
        {
            return FALSE;
        }
    }
    return TRUE;
}
