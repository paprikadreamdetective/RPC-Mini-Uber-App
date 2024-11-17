struct Posicion {
    int x;
    int y;
};

struct InfoAuto {
    Posicion posicion;
    string tipoUber<10>;
    float tarifa;
    string placa<10>;
};

struct EstadoServicio {
    int viajesRealizados;
    int autosLibres;
    float gananciaTotal;
};


struct Auto {
    bool disponible;
    Posicion posicion;
    string tipoUber<10>;
    float tarifa;
    string placa<10>;
    float ganancias;
};


struct TerminarViajeArgs {
    Posicion posicionFinal;
    float costoViaje;
    string placas<10>;
};


program UBER_PROG {
    version UBER_VERS {
        InfoAuto SolicitarViaje(Posicion) = 1;
        void TerminarViaje(TerminarViajeArgs) = 2;
        EstadoServicio estadoServicio(void) = 3;
    } = 1;
} = 0x20000001;

