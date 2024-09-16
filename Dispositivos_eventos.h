#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    #define TOTAL_EVENTOS 16
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    #define TOTAL_EVENTOS 4
#endif

#define EVENTOS_ESTADO_OFF 0
#define EVENTOS_ESTADO_ON 1

#define EVENTOS_VALOR_OFF 0
#define EVENTOS_VALOR_ON 1

class Dispositivos_eventos
{

    private:

        bool _estados_bits_[TOTAL_EVENTOS];
        bool _valores_bits_[TOTAL_EVENTOS];
        
        bool _validar_operacion(bool, float, int);
        void _serial_print_on_off(bool estado);

    public:

        void init();

        // GETTERS
        byte estado(int evento_id)               {return _estados_bits_[evento_id];}
        byte valor(int evento_id)                {return _valores_bits_[evento_id];}
        bool activado(int evento_id);
        int  get_rele_num(int evento_id);
        bool get_rele_accion(int evento_id);
        int  get_dispositivo(int evento_id);
        bool get_alarma(int evento_id);
        bool get_operacion(int evento_id);
        int  get_valor(int evento_id);
        int  get_diff_off(int evento_id);
        bool disponible(int dispositivo_id);
        int ultimo_ejecutando(int dispositivo_id, bool alarma);

        void calcular();
} Dispositivos_eventos;