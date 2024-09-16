#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

const __FlashStringHelper* config_get_label(int node_id)
{
    switch(node_id)
    {
        case G_MENU:                                                            return F("-- MENU --");

        case G_TIEMPOS:                                                         return F("TIEMPOS");
        case TIEMPO_LECTURAS_SEGUNDOS:                                          return F("Lecturas");
        case TIEMPO_MENU_LIBERAR_SEGUNDOS:                                      return F("Salir menu");
        case TIEMPO_LUZ_PANTALLA_SEGUNDOS:                                      return F("Luz pantalla");
        case TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS:                               return F("Buzzer silenciar");

        case G_INTERACTIVO:                                                     return F("INTERACTIVO");
        case G_DISPOSITIVOS_DE_ENTRADA:                                         return F("DISP ENTRADA");
        case G_DISPOSITIVOS_DE_SALIDA:                                          return F("DISP SALIDA");
        
        case G_LEDS:                                                            return F("LEDS");
        case LEDS_BRILLO:                                                       return F("LEDS BRILLO");
        case LEDS_RELES_FORZADO_ON:                                             return F("Reles F-ON");
        case LEDS_RELES_FORZADO_OFF:                                            return F("Reles F-OFF");
        case LEDS_VINCULAR_RELES_FORZADOS:                                      return F("V.R Forzados");
        case LEDS_VINCULAR_RELES_EVENTOS:                                       return F("V.R Eventos");

        case G_LCD_7:                                                           return F("LCD_7");
        case LCD_7_ON_OFF:                                                      return F("Activo");
        case LCD_7_BRILLO:                                                      return F("LCD_7 BRILLO");
        case LCD_7_DIR:                                                         return F("Sel.sonda");

        case BUZZER_ON_OFF:                                                     return F("BUZZER");

        case G_RELES:                                                           return F("RELES");
        case RELES_ON_OFF:                                                      return F("Activo");
        case RELES_VISOR:                                                       return F("Visualizar");

        case G_RELES_ESTADOS:                                                   return F("RELES ESTADOS");
        case RELE_ESTADO_1:                                                     return F("Estado 1");
        case RELE_ESTADO_2:                                                     return F("Estado 2");
        case RELE_ESTADO_3:                                                     return F("Estado 3");
        case RELE_ESTADO_4:                                                     return F("Estado 4");
        case RELE_ESTADO_5:                                                     return F("Estado 5");
        case RELE_ESTADO_6:                                                     return F("Estado 6");
        case RELE_ESTADO_7:                                                     return F("Estado 7");
        case RELE_ESTADO_8:                                                     return F("Estado 8");
        case RELE_ESTADO_9:                                                     return F("Estado 9");
        case RELE_ESTADO_10:                                                    return F("Estado 10");
        case RELE_ESTADO_11:                                                    return F("Estado 11");
        case RELE_ESTADO_12:                                                    return F("Estado 12");
        case RELE_ESTADO_13:                                                    return F("Estado 13");
        case RELE_ESTADO_14:                                                    return F("Estado 14");
        case RELE_ESTADO_15:                                                    return F("Estado 15");
        case RELE_ESTADO_16:                                                    return F("Estado 16");

        case G_SONDAS:                                                          return F("SONDAS");
        case SONDAS_ON_OFF:                                                     return F("Activo");
        case SONDAS_ESCALA:                                                     return F("Escala");

        case G_SONDA_COLECTOR_1:                                                return F("COLECTOR 1");
        case G_SONDA_COLECTOR_2:                                                return F("COLECTOR 2");
        case G_SONDA_COLECTOR_3:                                                return F("COLECTOR 3");

        case SONDA_COLECTOR_1_ON_OFF:                                           
        case SONDA_COLECTOR_2_ON_OFF:                                           
        case SONDA_COLECTOR_3_ON_OFF:                                           return F("Activo");
        case SONDA_COLECTOR_1_DIR:                                              
        case SONDA_COLECTOR_2_DIR:                                              
        case SONDA_COLECTOR_3_DIR:                                              return F("Sel.sonda");
        case G_CONTROL_BOMBA_1:                                                 
        case G_CONTROL_BOMBA_2:                                                 
        case G_CONTROL_BOMBA_3:                                                 return F("CONTROL");
        case CONTROL_BOMBA_1_DIFF_TO_ON:                                        
        case CONTROL_BOMBA_2_DIFF_TO_ON:                                        
        case CONTROL_BOMBA_3_DIFF_TO_ON:                                        return F("Col-Dep > ON");
        case CONTROL_BOMBA_1_DIFF_TO_OFF:                                       
        case CONTROL_BOMBA_2_DIFF_TO_OFF:                                       
        case CONTROL_BOMBA_3_DIFF_TO_OFF:                                       return F("Col-Dep < OFF");
        case CONTROL_BOMBA_1_STOP_SI_ZTERM_MAYOR_DE_TEMP:                       
        case CONTROL_BOMBA_2_STOP_SI_ZTERM_MAYOR_DE_TEMP:                       
        case CONTROL_BOMBA_3_STOP_SI_ZTERM_MAYOR_DE_TEMP:                       return F("STOP ZTerm >");
        case CONTROL_BOMBA_1_RUN_SI_COLECTOR_MENOR_DE_TEMP:                     
        case CONTROL_BOMBA_2_RUN_SI_COLECTOR_MENOR_DE_TEMP:                     
        case CONTROL_BOMBA_3_RUN_SI_COLECTOR_MENOR_DE_TEMP:                     return F("RUN Col <");

        case G_BOMBAS:                                                          return F("BOMBAS");
        case G_BOMBA_1:                                                         return F("BOMBA 1");
        case G_BOMBA_2:                                                         return F("BOMBA 2");
        case G_BOMBA_3:                                                         return F("BOMBA 3");
        case BOMBA_1_ON_OFF:                                                    
        case BOMBA_2_ON_OFF:                                                    
        case BOMBA_3_ON_OFF:                                                    return F("Activo");
        case BOMBA_1_RELE_NUM:                                                  
        case BOMBA_2_RELE_NUM:                                                  
        case BOMBA_3_RELE_NUM:                                                  return F("Rele");
        case CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_BOMBEO:                       
        case CONTROL_BOMBA_2_TIEMPO_PULSADO_CICLO_BOMBEO:   
        case CONTROL_BOMBA_3_TIEMPO_PULSADO_CICLO_BOMBEO:                       return F("Pulso ON");
        case CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_PAUSA:                        
        case CONTROL_BOMBA_2_TIEMPO_PULSADO_CICLO_PAUSA:    
        case CONTROL_BOMBA_3_TIEMPO_PULSADO_CICLO_PAUSA:                        return F("Pulso OFF");
        
        case SONDA_DEPOSITO_DIR:                                                return F("Deposito");
        case SONDA_ZTERMOSTATO_DIR:                                             return F("Z-Termostato");
        case G_SONDA_ZONA_1:                            return F("Zona 1");
        case G_SONDA_ZONA_2:                            return F("Zona 2");
        case G_SONDA_ZONA_3:                            return F("Zona 3");
        case G_SONDA_ZONA_4:                            return F("Zona 4");
        case G_SONDA_ZONA_5:                            return F("Zona 5");
        case G_SONDA_ZONA_6:                            return F("Zona 6");
        case G_SONDA_ZONA_7:                            return F("Zona 7");
        case G_SONDA_ZONA_8:                            return F("Zona 8");
        case G_SONDA_ZONA_9:                            return F("Zona 9");
        case G_SONDA_ZONA_10:                           return F("Zona 10");



        case G_AGUA:                                    return F("AGUA");
        case AGUA_ON_OFF:                               return F("Activo");
        case AGUA_STOP_ON_OFF:                          return F("Agua stop pin");
        case AGUA_ALTURA_PUNTOS:                        return F("Sensor puntos");
        case AGUA_CAPACIDAD_TOTAL:                      return F("Capacidad");
        case AGUA_TECHO_VIRTUAL:                        return F("Techo");
        case AGUA_SUELO_VIRTUAL:                        return F("Suelo");
        case AGUA_MANTENER_TEMP_ON_OFF:                 return F("Confort");
        case AGUA_MANTENER_TEMP:                        return F("Confort mantener");
        case AGUA_ESCALA:                               return F("Agua Escala");
        case AGUA_RELE_NUM:                             return F("Rele");

        case G_CALENTADOR_DEPOSITO:                     return F("CALENTAR DEP");
        case CALENTADOR_DEPOSITO_ON_OFF:                return F("Activo");
        case CALENTADOR_DEPOSITO_SI_TEMP_INFERIOR_A:    return F("Deposito <");
        case CALENTADOR_DEPOSITO_DIFF_OFF:              return F("Retrasa OFF");
        case CALENTADOR_DEPOSITO_AHORRO_ON_OFF:         return F("Parar con bombeo");
        case CALENTADOR_DEPOSITO_RELE_NUM:              return F("Rele");

        case G_REFRIGERAR_COLECTORES:                   return F("ENFRIAR COLS");

        case G_REFRIGERAR_COLECTOR_1:                                                  return F("ENFRIAR COL 1");
        case REFRIGERAR_COLECTOR_1_ON_OFF:                                             return F("Activo");
        case REFRIGERAR_COLECTOR_1_SI_TEMP_SUPERIOR_A:                                 return F("Colector 1 >");
        case REFRIGERAR_COLECTOR_1_DIFF_OFF:                                           return F("Retrasa OFF");
        case REFRIGERAR_COLECTOR_1_AHORRO_ON_OFF:                                      return F("Parar con bombeo");
        case REFRIGERAR_COLECTOR_1_RELE_NUM:            return F("Rele");

        case G_REFRIGERAR_COLECTOR_2:                   return F("ENFRIAR COL 2");
        case REFRIGERAR_COLECTOR_2_ON_OFF:              return F("Activo");
        case REFRIGERAR_COLECTOR_2_SI_TEMP_SUPERIOR_A:  return F("Colector 2 >");
        case REFRIGERAR_COLECTOR_2_DIFF_OFF:            return F("Retrasa OFF");
        case REFRIGERAR_COLECTOR_2_AHORRO_ON_OFF:       return F("Parar con bombeo");
        case REFRIGERAR_COLECTOR_2_RELE_NUM:            return F("Rele");

        case G_REFRIGERAR_COLECTOR_3:                   return F("ENFRIAR COL 3");
        case REFRIGERAR_COLECTOR_3_ON_OFF:              return F("Activo");
        case REFRIGERAR_COLECTOR_3_SI_TEMP_SUPERIOR_A:  return F("Colector 3 >");
        case REFRIGERAR_COLECTOR_3_DIFF_OFF:            return F("Retrasa OFF");
        case REFRIGERAR_COLECTOR_3_AHORRO_ON_OFF:       return F("Parar con bombeo");
        case REFRIGERAR_COLECTOR_3_RELE_NUM:            return F("Rele");

        case EVENTOS_ON_OFF:                            return F("Activo");
        case G_EVENTOS:                                 return F("EVENTOS");

        case G_EVENTO_1:                                return F("EV-1");
        case G_EVENTO_2:                                return F("EV-2");
        case G_EVENTO_3:                                return F("EV-3");
        case G_EVENTO_4:                                return F("EV-4");
        case G_EVENTO_5:                                return F("EV-5");
        case G_EVENTO_6:                                return F("EV-6");
        case G_EVENTO_7:                                return F("EV-7");
        case G_EVENTO_8:                                return F("EV-8");
        case G_EVENTO_9:                                return F("EV-9");
        case G_EVENTO_10:                               return F("EV-10");
        case G_EVENTO_11:                               return F("EV-11");
        case G_EVENTO_12:                               return F("EV-12");
        case G_EVENTO_13:                               return F("EV-13");
        case G_EVENTO_14:                               return F("EV-14");
        case G_EVENTO_15:                               return F("EV-15");
        case G_EVENTO_16:                               return F("EV-16");
        
        case G_SERIAL_DEBUG:                            return F("SERIAL DEBUG");

        case SERIAL_DEBUG_BAUD:
        case SERIAL_BAUD:                               return F("Baudios");

        case SERIAL_DEBUG_ON_OFF:                       return F("Activado");
        case SERIAL_ON_OFF:                             return F("Activado");
        case SERIAL_OUT_ON_OFF:                         return F("Enviar");
        case SERIAL_IN_ON_OFF:                          return F("Recibir");

        case DEBUG_SONDAS:                              return F("Sondas");
        case DEBUG_BOMBAS:                              return F("Bombas");
        case DEBUG_AGUA:                                return F("Agua");
        case DEBUG_DISPOSITIVOS_IN:                     return F("Dispositivos IN");
        case DEBUG_DISPOSITIVOS_OUT:                    return F("Dispositivos OUT");
        case DEBUG_EVENTOS:                             return F("Eventos");
        case DEBUG_ALARMAS:                             return F("Alarmas");
        case DEBUG_RELES:                               return F("Reles");

        case C_SETUP_BORRAR:                            return F("Borrar Setup");
        case C_SETUP_GUARDAR:                           return F("Guardar Setup");
        case G_TESTS:                                   return F("TESTS");
        case C_TEST_BUZZER:                             return F("Buzzer");
        case C_TEST_LEDS:                               return F("Leds");
        case C_TEST_LCD_7:                              return F("Lcd 7");
        case C_TEST_RELES:                              return F("Reles");
        case C_ABOUT:                                   return F("About");
        case C_RESET:                                   return F("Reiniciar");

    }


    int idx;
    for(byte bucle=0; bucle < TOTAL_EVENTOS; bucle++)
    {
        idx = Menu_grupal::get_id(EVENTO_1_ON_OFF, bucle);
        if (node_id == idx) return F("Activo");

        idx = Menu_grupal::get_id(EVENTO_1_DISPOSITIVO, bucle);
        if (node_id == idx) return F("Dispositivo");

        idx = Menu_grupal::get_id(EVENTO_1_OPERACION, bucle);
        if (node_id == idx) return F("Operacion");

        idx = Menu_grupal::get_id(EVENTO_1_VALOR, bucle);
        if (node_id == idx) return F("Valor");

        idx = Menu_grupal::get_id(EVENTO_1_DIFF_OFF, bucle);
        if (node_id == idx) return F("Retrasa OFF");

        idx = Menu_grupal::get_id(EVENTO_1_ES_ALARMA, bucle);
        if (node_id == idx) return F("Sonar alarma");

        idx = Menu_grupal::get_id(EVENTO_1_RELE_ACCION, bucle);
        if (node_id == idx) return F("Rele Accion");

        idx = Menu_grupal::get_id(EVENTO_1_RELE_NUM, bucle);
        if (node_id == idx) return F("Rele");
    }

    for(byte bucle=0; bucle < TOTAL_SONDAS_ZONAS; bucle++)
    {
        idx = Menu_grupal::get_id(SONDA_ZONA_1_ON_OFF, bucle);
        if (node_id == idx) return F("Activo");
        idx = Menu_grupal::get_id(SONDA_ZONA_1_DIR, bucle);
        if (node_id == idx) return F("Sel.sonda");
    }

    return F("????");

}


#endif