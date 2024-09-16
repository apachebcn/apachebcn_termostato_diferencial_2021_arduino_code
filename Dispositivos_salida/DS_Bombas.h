class Bombas
{
    private:
        static void _init();
        static void _serial_print_mensaje_dispositivo_no_activado(int dispositivo_id, const __FlashStringHelper*  dispositivo_nombre);
        static void _serial_print_mensaje_dispositivo_no_disponible(int dispositivo_id, const __FlashStringHelper*  dispositivo_nombre);
        static void _calculo_proceso(int bomba_id);
        static void _procesa_bomba(int bomba_id);

    public:

        static void init();

        //BOMBA
        static void cancelar(int bomba_id);
        static void actualizar(byte bomba_id);
        static void accion_forzar(int bomba_id);


};
