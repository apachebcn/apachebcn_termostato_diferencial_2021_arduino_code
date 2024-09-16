#define VALOR_RESET_O_ERROR -999

/*
*
* DISPOSITIVOS DE ENTRADA
*
*/

#define DISPOSITIVO_DE_ENTRADA_PRIMER_ID  100

#define ESTADO_DISPOSITIVO_DE_ENTRADA_DESACTIVADO       0
#define ESTADO_DISPOSITIVO_DE_ENTRADA_NO_DISPONIBLE     1
#define ESTADO_DISPOSITIVO_DE_ENTRADA_ERROR             2
#define ESTADO_DISPOSITIVO_DE_ENTRADA_DISPONIBLE        3

/*
*
* DISPOSITIVOS DE SALIDA
*
*/

#define DISPOSITIVO_DE_SALIDA_PRIMER_ID  200

#define ESTADO_DISPOSITIVO_DE_SALIDA_DESACTIVADO        0
#define ESTADO_DISPOSITIVO_DE_SALIDA_NO_DISPONIBLE      1
#define ESTADO_DISPOSITIVO_DE_SALIDA_DISPONIBLE         3


//byte forzar_dispositivos_de_salida_bits_[TOTAL_DISPOSITIVOS_DE_SALIDA];


class Dispositivos
{
    private:

        byte DE_estados_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];
        char DE_estados_icono_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];
        float DE_valores_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];
        float DE_valores_max_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];
        float DE_valores_min_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];

        byte DS_estados_bits_[TOTAL_DISPOSITIVOS_DE_SALIDA];
        byte DS_valores_bits_[TOTAL_DISPOSITIVOS_DE_SALIDA];

    public:

        bool _es_dispositivo_entrada(int dispositivo_id);
        bool _es_dispositivo_salida(int dispositivo_id);
        void _serial_alerta(const __FlashStringHelper* funcion_nombre, const __FlashStringHelper* dispositivo_tipo, int dispositivo_id);
        int _bit_dispositivo(int dispositivo_id);

        //getter
        byte get_estado(int dispositivo_id);
        char get_estado_icono(int dispositivo_id);
        float get_valor(int dispositivo_id); 
        float get_entrada_valor_min(int dispositivo_id);
        float get_entrada_valor_max(int dispositivo_id);
        int get_rele(int dispositivo_id);
        float get_entrada_valor(int dispositivo_id);
        void set_entrada_valor(int dispositivo_id, float valor);
        byte get_salida_valor(int dispositivo_id); 
        void set_salida_valor(int dispositivo_id, byte valor);

        //setters
        void set_estado(int dispositivo_id, byte valor);
        void set_estado_icono(int dispositivo_id, byte valor);
        void set_valor_min(int dispositivo_id, float valor);
        void set_valor_max(int dispositivo_id, float valor);
        void reset_valor_mins();
        void reset_valor_maxs();

        void init();

        bool inactivo(int dispositivo_id);
        bool disponible(int dispositivo_id);
        bool error(int dispositivo_id);
        int pertenece_a_grupo_de(int dispositivo_id);

        bool es_tipo_sonda(int dispositivo_id);
        void _serial_print_nombre_estado(byte estado);
        void serial_print_mensaje_sonda_no_seleccionada();
        void serial_print_imprimir_valor_temperatura(const __FlashStringHelper* etiqueta, float valor);
        const __FlashStringHelper* nombre(int dispositivo_id);
        const __FlashStringHelper* nombre_corto(int dispositivo_id);
        void serial_print_mensaje_dispositivo_apagado();
        void serial_print_mensaje_dispositivo_no_disponible();
        void serial_print_mensaje_depende_de_dispositivo(int dispositivo_id);
        void serial_print_sonda_datos(int dispositivo_id);
        void serial_print_debug_dispositivos_entrada();
        void serial_print_debug_dispositivos_salida();
        void serial_print_debug_dispositivos(int desde, int hasta);
} Dispositivos;