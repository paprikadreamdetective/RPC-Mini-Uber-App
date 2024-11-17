#include "uber.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

float calcularDistancia(Posicion origen, Posicion destino) {
    float deltaX = destino.x - origen.x;
    float deltaY = destino.y - origen.y;
    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

/*
void pasajero(CLIENT *clnt) {
    Posicion origen = {rand() % 51, rand() % 51};
    Posicion destino = {rand() % 51, rand() % 51};

    InfoAuto *info = solicitarviaje_1(&origen, clnt);
    if (info == NULL) {
        printf("No hay autos disponibles.\n");
        return;
    }

    float distancia = calcularDistancia(origen, destino);
    float costo = distancia * info->tarifa;
    printf("Viaje asignado: Placa: %s, Tipo: %s, Costo: %.2f\n", info->placa, info->tipoUber, costo);

    sleep(distancia);
    terminarviaje_1(&destino, &costo, &info->placa, clnt);
    printf("Viaje terminado.\n");
}*/


void pasajero(CLIENT *clnt) {
    // Generar posiciones de origen y destino aleatorias
    Posicion origen = {rand() % 51, rand() % 51};
    Posicion destino = {rand() % 51, rand() % 51};

    // Llamar al procedimiento remoto para solicitar un viaje
    //InfoAuto *info = solicitarviaje_1(&origen, clnt);
    InfoAuto *info = solicitarviaje_1(&origen, clnt);
    //printf("PLacas: %s\n", info->placa);
    if (info == NULL) {
        printf("No hay autos disponibles.\n");
        return;
    }

    // Calcular la distancia y el costo del viaje
    float distancia = calcularDistancia(origen, destino);
    float costo = distancia * info->tarifa;
    printf("Viaje asignado: Placa: %s, Tipo: %s, Costo: %.2f\n", info->placa, info->tipoUber, costo);

    // Simular el tiempo de viaje
    sleep(distancia);

    // Preparar los argumentos para terminar el viaje
    TerminarViajeArgs args;
    args.posicionFinal = destino;
    args.costoViaje = costo;
    //strcpy(args.placas, info->placa); // Copiar las placas al campo correspondiente
    args.placas = strdup(info->placa); // Copiar las placas al campo correspondiente

    // Llamar al procedimiento remoto para terminar el viaje
    void *result = terminarviaje_1(&args, clnt);
    if (result == NULL) {
        clnt_perror(clnt, "Error al terminar el viaje");
        return;
    }

    printf("Viaje terminado.\n");
}

void administrador(CLIENT *clnt) {
    while (1) {
        EstadoServicio *estado = estadoservicio_1(NULL, clnt);
        if (estado != NULL) {
            printf("Viajes realizados: %d, Autos libres: %d, Ganancia total: %.2f\n",
                   estado->viajesRealizados, estado->autosLibres, estado->gananciaTotal);
        }
        sleep(2);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <host> <rol (pasajero|administrador)>\n", argv[0]);
        exit(1);
    }

    CLIENT *clnt = clnt_create(argv[1], UBER_PROG, UBER_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    if (strcmp(argv[2], "pasajero") == 0) {
        pasajero(clnt);
    } else if (strcmp(argv[2], "administrador") == 0) {
        administrador(clnt);
    } else {
        printf("Rol desconocido.\n");
    }

    clnt_destroy(clnt);
    return 0;
}

