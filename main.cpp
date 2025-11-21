//
// main.cpp
//


#include "Tablero.h"
using namespace std;

#include <iostream>
#include <string>
#include <limits>
#include "Tablero.h"
#include "Jugador.h"
#include "scoreBoard.h"


int main() {
    scoreBoard scoreboard;
    bool salirPrograma = false;

    while (!salirPrograma) {
        std::cout << "==============================\n";
        std::cout << "   JUEGO DE LOS LABERINTOS   \n";
        std::cout << "==============================\n\n";

        std::string nombreJugador;
        std::cout << "Ingresa tu nombre: ";
        std::getline(std::cin, nombreJugador);
        if (nombreJugador.empty()) {
            // Si el buffer quedó raro por un enter previo
            std::getline(std::cin, nombreJugador);
        }

        // Crear tablero y preparar partida
        Tablero tablero;
        tablero.colocarMurosInternos(16);
        tablero.colocarTesoros(10);

        // Crear jugador
        Jugador jugador(nombreJugador);
        Node* inicio = tablero.obtenerNodoAleatorioLibre(nullptr);
        jugador.setPosicionInicial(inicio);

        bool finPartida = false;
        bool abandono = false;

        while (!finPartida) {
            std::cout << "\nTablero (visible):\n";
            tablero.imprimirVisible();

            std::cout << "Jugador: " << jugador.getNombre()
                      << " | Puntaje: " << jugador.getPuntaje()
                      << " | Tesoros en pila: " << jugador.getCantidadTesoros()
                      << " | Tesoros recogidos: " << jugador.getTesorosRecogidos()
                      << "/10"
                      << "\n";

            if (jugador.getTesorosRecogidos() >= 10) {
                std::cout << "\n*** ¡Has recogido los 10 tesoros ocultos! ***\n";
                finPartida = true;
                break;
            }

            std::cout << "Movimiento (W/A/S/D), T=ver tesoros, X=usar tesoro, Q=abandonar partida: ";
            char opcion;
            std::cin >> opcion;

            switch (opcion) {
                case 'W':
                case 'w':
                    jugador.moverArriba();
                    break;
                case 'S':
                case 's':
                    jugador.moverAbajo();
                    break;
                case 'A':
                case 'a':
                    jugador.moverIzquierda();
                    break;
                case 'D':
                case 'd':
                    jugador.moverDerecha();
                    break;
                case 'T':
                case 't':
                    jugador.mostrarTesoros();
                    break;
                case 'X':
                case 'x':
                    jugador.usarTesoro(tablero);
                    break;
                case 'Q':
                case 'q':
                    std::cout << "Has abandonado la partida.\n";
                    finPartida = true;
                    abandono = true;
                    break;
                default:
                    std::cout << "Opcion invalida.\n";
                    break;
            }
        }

        // Solo registramos el puntaje si el jugador terminó recogiendo los 10 tesoros
        if (!abandono && jugador.getTesorosRecogidos() >= 10) {
            int puntajeFinal = jugador.getPuntaje();
            std::cout << "\nTu puntaje final es: " << puntajeFinal << " (menos es mejor)\n";
            scoreboard.registrarPuntaje(jugador.getNombre(), puntajeFinal);
            std::cout << "Puntaje registrado en el scoreboard.\n";
        } else {
            std::cout << "Partida no completada, no se registra puntaje.\n";
        }

        // Menú de consultas de scoreboard
        bool salirMenu = false;
        while (!salirMenu) {
            std::cout << "\n=== MENU POST-PARTIDA ===\n";
            std::cout << "1. Consultar mi mejor puntaje\n";
            std::cout << "2. Consultar puntaje de otro jugador\n";
            std::cout << "3. Ver todos los puntajes ordenados\n";
            std::cout << "4. Jugar otra partida\n";
            std::cout << "5. Salir del juego\n";
            std::cout << "Selecciona una opcion: ";

            int opcionMenu;
            std::cin >> opcionMenu;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

            switch (opcionMenu) {
                case 1: {
                    int punt;
                    if (scoreboard.obtenerPuntaje(jugador.getNombre(), punt)) {
                        std::cout << "Tu mejor puntaje registrado es: " << punt << "\n";
                    } else {
                        std::cout << "Aun no tienes puntaje registrado.\n";
                    }
                    break;
                }
                case 2: {
                    std::string nombreConsulta;
                    std::cout << "Ingresa el nombre del jugador a consultar: ";
                    std::getline(std::cin, nombreConsulta);
                    if (nombreConsulta.empty()) {
                        std::getline(std::cin, nombreConsulta);
                    }
                    int punt;
                    if (scoreboard.obtenerPuntaje(nombreConsulta, punt)) {
                        std::cout << "Mejor puntaje de " << nombreConsulta << " es: " << punt << "\n";
                    } else {
                        std::cout << "No hay puntaje registrado para ese jugador.\n";
                    }
                    break;
                }
                case 3:
                    scoreboard.imprimirTodosOrdenados();
                    break;
                case 4:
                    salirMenu = true;       // volvemos al while grande (nueva partida)
                    break;
                case 5:
                    salirMenu = true;
                    salirPrograma = true;   // terminamos todo el programa
                    break;
                default:
                    std::cout << "Opcion invalida.\n";
                    break;
            }
        }
    }

    std::cout << "\nGracias por jugar.\n";
    return 0;
}


