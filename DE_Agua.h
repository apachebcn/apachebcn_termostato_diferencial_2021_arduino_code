class Agua
{

    private:

        static bool _activado();

    public:

        static void actualiza_pin();
        static bool activado();
        static bool ok();

        static void resetea_stats_min();
        static void resetea_stats_max();

        static float valor();
        static float valor_max();
        static float valor_min();

        static void accion_forzar();

};