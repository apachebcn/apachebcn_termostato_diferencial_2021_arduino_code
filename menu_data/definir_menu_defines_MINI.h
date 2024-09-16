#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
/*
	NO ELIMINAR LOS DEBUG_* CON VALOR 0, NECESITAN SU DEFINICIÓN PARA QUE EVITAR ERRORES EN LOS IF QUE IMPRIMEN DEBUG POR EL SERIAL
*/
#define DEBUG_SONDAS 0
#define DEBUG_BOMBAS 0
#define DEBUG_EVENTOS 0
#define DEBUG_RELES 0

#define	G_MENU	1
#define	G_TIEMPOS	2
#define	TIEMPO_LECTURAS_SEGUNDOS	3
#define	TIEMPO_LUZ_PANTALLA_SEGUNDOS	4
#define	TIEMPO_MENU_LIBERAR_SEGUNDOS	5
#define	TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS	6
#define	BUZZER_ON_OFF	7
#define	G_SONDAS	8
#define	SONDAS_ON_OFF	9
#define	SONDAS_ESCALA	10
#define	SONDA_DEPOSITO_DIR	11
#define	SONDA_ZTERMOSTATO_DIR	12
#define	G_SONDA_COLECTOR_1	13
#define	SONDA_COLECTOR_1_ON_OFF	14
#define	SONDA_COLECTOR_1_DIR	15
#define	G_DISPOSITIVOS_DE_SALIDA	16
#define	G_BOMBA_1	17
#define	BOMBA_1_ON_OFF	18
#define	BOMBA_1_RELE_NUM	19
#define	G_CONTROL_BOMBA_1	20
#define	CONTROL_BOMBA_1_DIFF_TO_ON	21
#define	CONTROL_BOMBA_1_DIFF_TO_OFF	22
#define	CONTROL_BOMBA_1_RUN_SI_COLECTOR_MENOR_DE_TEMP	23
#define	CONTROL_BOMBA_1_STOP_SI_ZTERM_MAYOR_DE_TEMP	24
#define	CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_BOMBEO	25
#define	CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_PAUSA	26
#define	G_REFRIGERAR_COLECTORES	27
#define	G_REFRIGERAR_COLECTOR_1	28
#define	REFRIGERAR_COLECTOR_1_ON_OFF	29
#define	REFRIGERAR_COLECTOR_1_RELE_NUM	30
#define	REFRIGERAR_COLECTOR_1_SI_TEMP_SUPERIOR_A	31
#define	REFRIGERAR_COLECTOR_1_DIFF_OFF	32
#define	REFRIGERAR_COLECTOR_1_AHORRO_ON_OFF	33
#define	G_CALENTADOR_DEPOSITO	34
#define	CALENTADOR_DEPOSITO_ON_OFF	35
#define	CALENTADOR_DEPOSITO_RELE_NUM	36
#define	CALENTADOR_DEPOSITO_SI_TEMP_INFERIOR_A	37
#define	CALENTADOR_DEPOSITO_DIFF_OFF	38
#define	CALENTADOR_DEPOSITO_AHORRO_ON_OFF	39
#define	G_EVENTOS	40
#define	EVENTOS_ON_OFF	41
#define	G_EVENTO_1	42
#define	EVENTO_1_ON_OFF	43
#define	EVENTO_1_DISPOSITIVO	44
#define	EVENTO_1_RELE_NUM	45
#define	EVENTO_1_RELE_ACCION	46
#define	EVENTO_1_ES_ALARMA	47
#define	EVENTO_1_OPERACION	48
#define	EVENTO_1_VALOR	49
#define	EVENTO_1_DIFF_OFF	50
#define	G_EVENTO_2	51
#define	EVENTO_2_ON_OFF	52
#define	EVENTO_2_DISPOSITIVO	53
#define	EVENTO_2_RELE_NUM	54
#define	EVENTO_2_RELE_ACCION	55
#define	EVENTO_2_ES_ALARMA	56
#define	EVENTO_2_OPERACION	57
#define	EVENTO_2_VALOR	58
#define	EVENTO_2_DIFF_OFF	59
#define	G_EVENTO_3	60
#define	EVENTO_3_ON_OFF	61
#define	EVENTO_3_DISPOSITIVO	62
#define	EVENTO_3_RELE_NUM	63
#define	EVENTO_3_RELE_ACCION	64
#define	EVENTO_3_ES_ALARMA	65
#define	EVENTO_3_OPERACION	66
#define	EVENTO_3_VALOR	67
#define	EVENTO_3_DIFF_OFF	68
#define	G_EVENTO_4	69
#define	EVENTO_4_ON_OFF	70
#define	EVENTO_4_DISPOSITIVO	71
#define	EVENTO_4_RELE_NUM	72
#define	EVENTO_4_RELE_ACCION	73
#define	EVENTO_4_ES_ALARMA	74
#define	EVENTO_4_OPERACION	75
#define	EVENTO_4_VALOR	76
#define	EVENTO_4_DIFF_OFF	77
#define	G_RELES	78
#define	RELES_ON_OFF	79
#define	RELES_VISOR	80
#define	G_RELES_ESTADOS	81
#define	RELE_ESTADO_1	82
#define	RELE_ESTADO_2	83
#define	RELE_ESTADO_3	84
#define	RELE_ESTADO_4	85
#define	RELE_ESTADO_5	86
#define	RELE_ESTADO_6	87
#define	RELE_ESTADO_7	88
#define	RELE_ESTADO_8	89
#define	C_TEST_RELES	90
#define	C_SETUP_BORRAR	91
#define	C_SETUP_GUARDAR	92
#define	C_RESET	93
#define	C_ABOUT	94

#endif