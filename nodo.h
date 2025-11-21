#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    // Enlaces a los 4 vecinos del nodo (lista múltiplemente enlazada)
    Node* up;
    Node* down;
    Node* left;
    Node* right;

    // Lo que el usuario ve en pantalla (inicia como 'o')
    char visible;

    // Lo que realmente es la casilla:
    // ' ' vacío
    // '#' borde externo
    // '|' muro interno
    // 'T' tesoro (no visible inicialmente)
    // 'P' jugador (temporal, depende de movimiento)
    char realType;

    // Flags necesarios
    bool isBorder;       // Si es borde '#'
    bool isWall;         // Si es muro interno '|'
    bool hasTreasure;    // Si tiene tesoro oculto

    // Tipo de tesoro (Rubí, Perla, Ámbar, Diamante)
    std::string treasureType;

    // Constructor
    Node();

    // Cambiar lo que se muestra al destapar
    void reveal();

    // Reiniciar una casilla cuando se reinicia el tablero
    void resetVisible();
};

#endif
