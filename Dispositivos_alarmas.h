#define ALARMA_OFF 0
#define ALARMA_POR_ERROR 1
#define ALARMA_POR_EVENTO_DE_DECESO 2
#define ALARMA_POR_EVENTO_DE_EXCESO 3



unsigned long Dispositivos_alarmas_inicio_buzzer_timer_ = 0;

class Dispositivos_alarmas
{
    private:

        byte _alarmas_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];
        byte _alarmas_recordadas_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];
        bool _alarmas_silenciadas_bits_[TOTAL_DISPOSITIVOS_DE_ENTRADA];

    public:

        void init();
        byte get_alarma(int dispositivo_id);
        byte get_alarma_recordada(int dispositivo_id);
        byte get_alarma_silenciada(int dispositivo_id);
        void set_alarma(int dispositivo_id, byte valor);
        void set_alarma_recordada(int dispositivo_id, byte valor);
        void set_alarma_silenciada(int dispositivo_id, byte valor);
        void reset();
        void set_estado(int, byte);
        void actuar();
        bool existe_alarma_no_silenciada();
        bool todas_silenciadas();
        bool existe_alarma_recordada();
        void silenciar();

        const __FlashStringHelper* nombre(byte alarma_id);
        void serial_print_debug();
} Dispositivos_alarmas;