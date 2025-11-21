//
// Jugador.h
//

#ifndef PROYECTO_ESTRUCTURAS_JUGADOR_H
#define PROYECTO_ESTRUCTURAS_JUGADOR_H

#include <string>
#include <stack>
#include "nodo.h"

class Tablero; // Declaración adelantada para evitar dependencia circular

class Jugador {
private:
    std::string nombre;
    Node* posicion;         // Nodo actual del jugador
    int puntaje;            // Cada intento de movimiento suma 1

    std::stack<std::string> tesoros;  // Pila LIFO de tesoros recogidos
    int tesorosRecogidos;             // Conteo total recogidos

    bool moverA(Node* destino);

public:
    explicit Jugador(const std::string& nombre);

    const std::string& getNombre() const;
    int getPuntaje() const;
    Node* getPosicion() const;
    int getCantidadTesoros() const;
    int getTesorosRecogidos() const;

    void setPosicionInicial(Node* nodoInicio);
    void dibujarEnTablero();

    // Movimientos (W, A, S, D)
    bool moverArriba();
    bool moverAbajo();
    bool moverIzquierda();
    bool moverDerecha();

    // TESOROS
    void mostrarTesoros() const;
    bool usarTesoro(Tablero& tablero);

};

#endif //PROYECTO_ESTRUCTURAS_JUGADOR_H
