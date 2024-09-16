#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI

const __FlashStringHelper* config_get_label(int node_id)
{
    switch(node_id)
    {
        case G_MENU:                                                            return F("-- MENU --");

        case G_TIEMPOS:                                                         return F("TIEMPOS");
        case TIEMPO_LECTURAS_SEGUNDOS:                                                          return F("Lecturas");
        case TIEMPO_LUZ_PANTALLA_SEGUNDOS:                                               return F("Luz pantalla");
        case TIEMPO_MENU_LIBERAR_SEGUNDOS:                                                       return F("Menu liberar");
        case TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS:                               return F("Buzzer silenciar");

        case G_DISPOSITIVOS_DE_SALIDA:                                            return F("D. SALIDA");

        case G_SONDAS:                                                          return F("SONDAS");
        case SONDAS_ON_OFF:                                                     return F("Activo");
        case SONDAS_ESCALA:                                                     return F("Escala");

        case SONDA_COLECTOR_1_DIR:                                              return F("COLECTOR");
        case SONDA_DEPOSITO_DIR:                                                return F("DEPOSITO");
        case SONDA_ZTERMOSTATO_DIR:                                             return F("Z-TERM");

        case G_CONTROL_BOMBA_1:                                                 return F("CONTROL");

        case CONTROL_BOMBA_1_DIFF_TO_ON:                                           return F("Col-Dep > ON");
        case CONTROL_BOMBA_1_DIFF_TO_OFF:                                          return F("Col-Dep < OFF");
        case 
        CONTROL_BOMBA_1_STOP_SI_ZTERM_MAYOR_DE_TEMP:                            return F("STOP ZTerm >");
        case 
        CONTROL_BOMBA_1_RUN_SI_COLECTOR_MENOR_DE_TEMP:                          return F("RUN Col <");
        case G_BOMBA_1:                                                         return F("BOMBA");
        case BOMBA_1_ON_OFF:                                                    return F("Activa");
        case BOMBA_1_RELE_NUM:                                                  return F("Rele");
        case CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_BOMBEO:                               return F("Pulso ON");
        case CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_PAUSA:                                return F("Pulso OFF");

        case G_CALENTADOR_DEPOSITO:                                                  return F("CALENT DEP");
        case CALENTADOR_DEPOSITO_ON_OFF:                                        return F("Activo");
        case CALENTADOR_DEPOSITO_SI_TEMP_INFERIOR_A:                            return F("Deposito <");
        case CALENTADOR_DEPOSITO_DIFF_OFF:                                      return F("Retrasa OFF");
        case CALENTADOR_DEPOSITO_AHORRO_ON_OFF:                                 return F("OFF con bomba");
        case CALENTADOR_DEPOSITO_RELE_NUM:                                      return F("Rele");

        case REFRIGERAR_COLECTOR_1_ON_OFF:                                             return F("Activo");
        case REFRIGERAR_COLECTOR_1_SI_TEMP_SUPERIOR_A:                                 return F("Colector 1 >");
        case REFRIGERAR_COLECTOR_1_DIFF_OFF:                                           return F("Retrasa OFF");
        case REFRIGERAR_COLECTOR_1_AHORRO_ON_OFF:                                      return F("OFF con bomba");
        case REFRIGERAR_COLECTOR_1_RELE_NUM:                                           return F("Rele");

        case G_EVENTOS:                                                         return F("EVENTOS");

        case G_EVENTO_1:                                                        return F("EVENTO-1");
        case G_EVENTO_2:                                                        return F("EVENTO-2");
        case G_EVENTO_3:                                                        return F("EVENTO-3");
        case G_EVENTO_4:                                                        return F("EVENTO-4");

        case RELES_ON_OFF:                                                      return F("RELES");
        case RELES_VISOR:                                                       return F("Visualizar");

        case C_TEST_RELES:                                                      return F("Test Reles");
        case C_SETUP_BORRAR:                                                    return F("Borrar");
        case C_SETUP_GUARDAR:                                                   return F("Guardar");

        case C_ABOUT:                                                           return F("About");

        case C_RESET:                                                           return F("Reiniciar");
        default:                                                                return F("????");
    }

    int idx;
    for(byte bucle=0; bucle < TOTAL_EVENTOS; bucle++)
    {
        idx = Menu::get_valor(EVENTO_1_ON_OFF, bucle);
        if (node_id == idx) return F("Activo");

        idx++; //EVENTO_1_DISPOSITIVO
        if (node_id == idx) return F("Disp");

        idx++; // = Menu_grupal::get_id(EVENTO_1_OPERACION, bucle);
        if (node_id == idx) return F("Operacion");

        idx++; // = Menu_grupal::get_id(EVENTO_1_VALOR, bucle);
        if (node_id == idx) return F("Valor");

        idx++; // = Menu_grupal::get_id(EVENTO_1_DIFF_OFF, bucle);
        if (node_id == idx) return F("Retrasa OFF");

        idx++; // = Menu_grupal::get_id(EVENTO_1_ES_ALARMA, bucle);
        if (node_id == idx) return F("Sonar alarma");

        idx++; // = Menu_grupal::get_id(EVENTO_1_RELE_ACCION, bucle);
        if (node_id == idx) return F("Rele Accion");

        idx++; // = Menu_grupal::get_id(EVENTO_1_RELE_NUM, bucle);
        if (node_id == idx) return F("Rele");
    }
}

#endif