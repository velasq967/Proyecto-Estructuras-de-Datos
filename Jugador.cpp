//
// Jugador.cpp
//

#include "Jugador.h"
#include "Tablero.h"
#include <iostream>
#include <cstdlib>

// ===================== CONSTRUCTOR ===================== //

Jugador::Jugador(const std::string& nombre)
    : nombre(nombre),
      posicion(nullptr),
      puntaje(0),
      tesorosRecogidos(0) {
}

// ===================== GETTERS ===================== //

const std::string& Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntaje() const {
    return puntaje;
}

Node* Jugador::getPosicion() const {
    return posicion;
}

int Jugador::getCantidadTesoros() const {
    return static_cast<int>(tesoros.size());
}

int Jugador::getTesorosRecogidos() const {
    return tesorosRecogidos;
}

// ===================== POSICIÓN INICIAL ===================== //

void Jugador::setPosicionInicial(Node* nodoInicio) {
    if (!nodoInicio) {
        std::cerr << "Error: nodo inicial nulo para el jugador.\n";
        return;
    }

    if (nodoInicio->isBorder || nodoInicio->isWall) {
        std::cerr << "Error: nodo inicial invalido (borde o muro).\n";
        return;
    }

    posicion = nodoInicio;
    dibujarEnTablero();
}

void Jugador::dibujarEnTablero() {
    if (!posicion) return;
    posicion->visible = 'P';
}

// ===================== MOVIMIENTOS ===================== //

bool Jugador::moverA(Node* destino) {
    // Cada intento de movimiento suma 1 punto
    puntaje++;

    if (!posicion) {
        std::cerr << "Error: el jugador no tiene posicion inicial.\n";
        return false;
    }

    if (destino == nullptr) {
        std::cout << "No puedes moverte fuera del tablero.\n";
        return false;
    }

    if (destino->isBorder) {
        std::cout << "Hay una pared externa, no puedes pasar.\n";
        return false;
    }

    if (destino->isWall) {
        destino->reveal();  // visible = '|'
        std::cout << "Te has encontrado con un muro, no puedes pasar.\n";
        return false;
    }

    // Movimiento válido:
    // 1. Destapamos donde estaba el jugador
    posicion->reveal();

    // 2. Actualizamos posicion
    posicion = destino;

    // 3. Si hay tesoro, lo recogemos
    if (posicion->hasTreasure) {
        std::cout << "Has encontrado un " << posicion->treasureType << "!\n";
        tesoros.push(posicion->treasureType);
        tesorosRecogidos++;

        // La casilla deja de tener tesoro (queda como espacio vacio)
        posicion->hasTreasure = false;
        posicion->treasureType.clear();
        posicion->realType = ' ';
    }

    // 4. Dibujamos al jugador en la nueva casilla
    posicion->visible = 'P';

    return true;
}

bool Jugador::moverArriba() {
    if (!posicion) return false;
    return moverA(posicion->up);
}

bool Jugador::moverAbajo() {
    if (!posicion) return false;
    return moverA(posicion->down);
}

bool Jugador::moverIzquierda() {
    if (!posicion) return false;
    return moverA(posicion->left);
}

bool Jugador::moverDerecha() {
    if (!posicion) return false;
    return moverA(posicion->right);
}

// ===================== TESOROS ===================== //

void Jugador::mostrarTesoros() const {
    if (tesoros.empty()) {
        std::cout << "No tienes tesoros recolectados.\n";
        return;
    }

    std::stack<std::string> copia = tesoros;
    std::cout << "Tesoros (del mas reciente al primero):\n";
    int i = 1;
    while (!copia.empty()) {
        std::cout << i << ". " << copia.top() << "\n";
        copia.pop();
        i++;
    }
}

bool Jugador::usarTesoro(Tablero& tablero) {
    if (tesoros.empty()) {
        std::cout << "No tienes tesoros para usar.\n";
        return false;
    }

    if (!posicion) {
        std::cout << "El jugador no tiene posicion valida.\n";
        return false;
    }

    std::string tipo = tesoros.top();
    tesoros.pop();

    std::cout << "Usando tesoro: " << tipo << "\n";

    // 1. Reubicar el tesoro en el laberinto
    tablero.reubicarTesoro(tipo, posicion);

    // 2. Reiniciar visibles (los muros pueden quedar expuestos: opcional)
    tablero.resetearVisibles(true);

    // 3. Efectos especificos por tipo

    if (tipo == "Rubi") {
        // a. Se reduce a la mitad los puntos
        puntaje /= 2;
        std::cout << "Efecto Rubi: tu puntaje se reduce a la mitad.\n";
    } else if (tipo == "Diamante") {
        // b. Elimina 2 muros
        tablero.eliminarMurosAleatorios(2);
        std::cout << "Efecto Diamante: se eliminaron 2 muros del laberinto.\n";
    } else if (tipo == "Perla") {
        // c. Aleatorio: puntaje = 0 o puntaje *= 2
        int r = std::rand() % 2;
        if (r == 0) {
            puntaje = 0;
            std::cout << "Efecto Perla: tu puntaje se ha reducido a cero.\n";
        } else {
            puntaje *= 2;
            std::cout << "Efecto Perla: tu puntaje se ha multiplicado por 2.\n";
        }
    } else if (tipo == "Ambar") {
        // d. Teletransportar al jugador a una casilla aleatoria
        Node* destino = tablero.obtenerNodoAleatorioLibre(posicion);
        if (destino) {
            posicion = destino;
            std::cout << "Efecto Ambar: has sido teletransportado a otra parte del laberinto.\n";
        } else {
            std::cout << "No se encontro un lugar adecuado para teletransportarte.\n";
        }
    }

    // 4. Después de resetear el tablero, volvemos a dibujar al jugador
    posicion->visible = 'P';

    return true;
}
