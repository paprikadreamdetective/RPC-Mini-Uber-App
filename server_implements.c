#include "uber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define N 8 // Número de autos
/*
typedef struct {
    bool disponible;
    struct Posicion posicion;
    char tipoUber[10];
    float tarifa;
    char placa[10];
    float ganancias;
} Auto;*/

//Auto autos[N];


Auto autos[N] = {
    {true, {10, 20}, "UberPlanet", 15.0, "001ABC", 0.0},
    {true, {30, 40}, "UberXL", 10.0, "002ABC", 0.0},
    {true, {50, 60}, "UberBlack", 25.0, "003ABC", 0.0},
    {true, {70, 80}, "UberXL", 20.0, "004ABC", 0.0},
    {true, {90, 100}, "UberPlanet", 12.5, "005ABC", 0.0},
    {true, {110, 120}, "UberBlack", 30.0, "006ABC", 0.0},
    {true, {130, 140}, "UberPlanet", 18.0, "007ABC", 0.0},
    {true, {150, 160}, "UberXL", 22.0, "008ABC", 0.0}
};

//static InfoAuto *info;

int viajesRealizados = 0;
float gananciaTotal = 0.0;

// Generar datos iniciales
void inicializarAutos() {
    const char *tipos[] = {"UberPlanet", "UberXL", "UberBlack"};
    const float tarifas[] = {10.0, 15.0, 25.0};
    for (int i = 0; i < N; i++) {
        autos[i].disponible = true;
        autos[i].posicion.x = rand() % 51;
        autos[i].posicion.y = rand() % 51;
        strcpy(autos[i].tipoUber, tipos[rand() % 3]);
        autos[i].tarifa = tarifas[rand() % 3];
        sprintf(autos[i].placa, "%03dABC", i + 1);
        autos[i].ganancias = 0.0;


 // Agregar impresión para verificar la inicialización
        printf("Auto %d: Placa: %s, Tipo: %s, Tarifa: %.2f, Posición: (%d, %d)\n", 
                i, autos[i].placa, autos[i].tipoUber, autos[i].tarifa, 
                autos[i].posicion.x, autos[i].posicion.y);


    }
}

// Calcular distancia entre dos posiciones
float calcularDistancia(struct Posicion a, struct Posicion b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

InfoAuto *solicitarviaje_1_svc(Posicion *posicionPasajero, struct svc_req *req) {
    static InfoAuto info;
    int mejorAuto = -1;
    float menorDistancia = 1e9;


 if (posicionPasajero == NULL) {
        fprintf(stderr, "Error: posicionPasajero es NULL\n");
        return NULL;
    }


    for (int i = 0; i < N; i++) {
        if (autos[i].disponible) {
            /*float distancia = calcularDistancia(*posicionPasajero, autos[i].posicion);
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                mejorAuto = i;
		printf("Mejor auto: %d\n", mejorAuto);
            }*/
		mejorAuto = i;
		printf("Mejor auto: %d\n", mejorAuto);
        	break;
	}
    }

    if (mejorAuto == -1) {
	printf("NO hay autos disponibles \n");
    	return NULL;
    }
    printf("DIsponible: 0 no - 1 si: %d \n", autos[mejorAuto].disponible);
    autos[mejorAuto].disponible = false;
    printf("DIsponible: 0 no - 1 si: %d \n", autos[mejorAuto].disponible);
    info.posicion = autos[mejorAuto].posicion;

    info.tipoUber = strdup(autos[mejorAuto].tipoUber);
    printf("Tipo Uber: %s\n", info.tipoUber);
    info.tarifa = autos[mejorAuto].tarifa;
    info.placa = strdup(autos[mejorAuto].placa);
    printf("Mejor Auto: %d\n", mejorAuto); 
    return &info;
}

void *terminarviaje_1_svc(TerminarViajeArgs *args, struct svc_req *req) {
    
static char dummy; // Dummy para devolver un puntero válido

    // Usa los campos del struct args
    Posicion posicionFinal = args->posicionFinal;
    float costoViaje = args->costoViaje;
    char *placas = args->placas;

    // Implementa la lógica para registrar el fin del viaje
    printf("Viaje terminado.\n");
    printf("Posición final: (%d, %d)\n", posicionFinal.x, posicionFinal.y);
    printf("Costo del viaje: %.2f\n", costoViaje);
    printf("Placas: %s\n", placas);

    // Devuelve un puntero válido


    for (int i = 0; i < N; i++) {
        if (strcmp(autos[i].placa, placas) == 0) {
            autos[i].disponible = true;
            autos[i].posicion = posicionFinal;
            autos[i].ganancias += costoViaje;
            viajesRealizados++;
            gananciaTotal += costoViaje;
            break;
        }
    }
 



/*		
    for (int i = 0; i < N; i++) {
        if (strcmp(autos[i].placa, *placas) == 0) {
            autos[i].disponible = true;
            autos[i].posicion = *posicionFinal;
            autos[i].ganancias += *costoViaje;
            viajesRealizados++;
            gananciaTotal += *costoViaje;
            break;
        }
    }*/
    //return NULL;
    return &dummy;
}

EstadoServicio *estadoservicio_1_svc(void *argp, struct svc_req *req) {
    static EstadoServicio estado;
    int libres = 0;
    for (int i = 0; i < N; i++) {
        if (autos[i].disponible) libres++;
    }

    estado.viajesRealizados = viajesRealizados;
    estado.autosLibres = libres;
    estado.gananciaTotal = gananciaTotal;
    return &estado;
}

