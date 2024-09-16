class FC
{

    public:

        static void delayMilisegundos(int);
        static void delayMicrosegundos(int tiempo);
        static bool if_zero_or_diff_to_millis(unsigned long, unsigned long);
        static bool if_diff_to_millis(unsigned long, unsigned long);
        static byte FlashStringHelper_len(const __FlashStringHelper*, byte);
        static byte Int_len(long);
        static void reset_remoto();
        static bool is_debug(int);
};