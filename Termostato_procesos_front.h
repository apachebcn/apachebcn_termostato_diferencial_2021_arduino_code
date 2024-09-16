
byte front_mensaje_info_lcd = 0;

void front_get_led_rele_en_evento(int dispositivo_entrada_id, char& icono_estado, byte& led_valor, byte& rele_valor);
void front_get_led_rele_en_forzado(int rele_num, char& icono_estado, byte& led_valor, byte& rele_valor);
void front_procesos();
void front_pantalla();
byte front_rele_forzado_valor_led(int);
void front_vincular_reles_forzados_con_leds();
void reset_front_timer();

