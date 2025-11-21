//
// Tablero.cpp
//

#include "Tablero.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Función auxiliar para tipo de tesoro aleatorio
static std::string tipoTesoroAleatorio() {
    int r = std::rand() % 4;
    switch (r) {
        case 0: return "Rubi";
        case 1: return "Diamante";
        case 2: return "Perla";
        default: return "Ambar";
    }
}

Tablero::Tablero() : head(nullptr) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    crearNodos();
    enlazarNodos();
    configurarBordes();
}

Tablero::~Tablero() {
    for (Node* n : nodos) {
        delete n;
    }
    nodos.clear();
    head = nullptr;
}

// ===================== CONSTRUCCIÓN DEL TABLERO ===================== //

void Tablero::crearNodos() {
    nodos.reserve(FILAS * COLUMNAS);

    for (int i = 0; i < FILAS * COLUMNAS; ++i) {
        Node* nuevo = new Node();
        nodos.push_back(nuevo);
    }

    head = nodos[0];
}

void Tablero::enlazarNodos() {
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS; ++col) {
            int index = fila * COLUMNAS + col;
            Node* actual = nodos[index];

            // Arriba
            if (fila > 0) {
                actual->up = nodos[(fila - 1) * COLUMNAS + col];
            }

            // Abajo
            if (fila < FILAS - 1) {
                actual->down = nodos[(fila + 1) * COLUMNAS + col];
            }

            // Izquierda
            if (col > 0) {
                actual->left = nodos[fila * COLUMNAS + (col - 1)];
            }

            // Derecha
            if (col < COLUMNAS - 1) {
                actual->right = nodos[fila * COLUMNAS + (col + 1)];
            }
        }
    }
}

void Tablero::configurarBordes() {
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS; ++col) {
            Node* actual = getNode(fila, col);

            bool esBordeSuperior = (fila == 0);
            bool esBordeInferior = (fila == FILAS - 1);
            bool esBordeIzquierdo = (col == 0);
            bool esBordeDerecho = (col == COLUMNAS - 1);

            if (esBordeSuperior || esBordeInferior || esBordeIzquierdo || esBordeDerecho) {
                actual->isBorder = true;
                actual->realType = '#';
                actual->visible = '#';
            }
        }
    }
}

// ===================== MÉTODOS PÚBLICOS BÁSICOS ===================== //

Node* Tablero::getHead() const {
    return head;
}

Node* Tablero::getNode(int fila, int columna) const {
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
        return nullptr;
    }
    int index = fila * COLUMNAS + columna;
    return nodos[index];
}

// ===================== MUROS INTERNOS ===================== //

void Tablero::colocarMurosInternos(int cantidadMuros) {
    int colocados = 0;

    while (colocados < cantidadMuros) {
        int fila = std::rand() % FILAS;
        int col = std::rand() % COLUMNAS;

        Node* actual = getNode(fila, col);

        if (actual->isBorder) continue;
        if (actual->isWall) continue;

        actual->isWall = true;
        actual->realType = '|';
        // visible sigue siendo 'o' hasta que se destape
        colocados++;
    }
}

// ===================== TESOROS ===================== //

void Tablero::colocarTesoros(int cantidadTesoros) {
    int colocados = 0;

    while (colocados < cantidadTesoros) {
        int fila = std::rand() % FILAS;
        int col = std::rand() % COLUMNAS;

        Node* actual = getNode(fila, col);

        if (actual->isBorder) continue;
        if (actual->isWall) continue;
        if (actual->hasTreasure) continue;

        actual->hasTreasure = true;
        actual->treasureType = tipoTesoroAleatorio();
        actual->realType = 'T';   // tipo real, pero NO se muestra al jugador
        // visible = 'o' porque está oculto

        colocados++;
    }
}

void Tablero::reubicarTesoro(const std::string& tipoTesoro, Node* posicionJugador) {
    Node* nodo = obtenerNodoAleatorioLibre(posicionJugador);
    if (!nodo) {
        std::cout << "No se encontro un nodo libre para reubicar el tesoro.\n";
        return;
    }

    nodo->hasTreasure = true;
    nodo->treasureType = tipoTesoro;
    nodo->realType = 'T';
    nodo->visible = 'o';
}

// ===================== UTILIDADES PARA EFECTOS ===================== //

void Tablero::resetearVisibles(bool mantenerMurosVisibles) {
    for (Node* n : nodos) {
        if (n->isBorder) {
            n->visible = '#';
        } else {
            n->visible = 'o'; // casilla tapada
        }

        if (mantenerMurosVisibles && n->isWall) {
            n->visible = '|';
        }
    }
}

void Tablero::eliminarMurosAleatorios(int cantidad) {
    // recolectar todos los nodos que son muros
    std::vector<Node*> muros;
    for (Node* n : nodos) {
        if (n->isWall) {
            muros.push_back(n);
        }
    }

    if (muros.empty()) return;

    int aEliminar = std::min(cantidad, static_cast<int>(muros.size()));

    for (int i = 0; i < aEliminar; ++i) {
        int ind

