#include "Node.h"

Node::Node() {
    // Enlaces
    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;

    // Inicialmente el jugador ve todo tapado
    visible = 'o';

    // Estado real de la casilla
    realType = ' ';  // Comienza como casilla vacía

    // Flags
    isBorder = false;
    isWall = false;
    hasTreasure = false;

    treasureType = "";
}

// Cambia el carácter visible para que el jugador vea la casilla real
void Node::reveal() {
    // Si es tesoro, NO se muestra 'T', se muestra espacio ' '
    // porque los tesoros están ocultos
    if (hasTreasure) {
        visible = ' ';
        return;
    }
    visible = realType;
}

// Reinicia lo visible a 'o' (para cuando se usa un tesoro que reinicia el mapa)
void Node::resetVisible() {
    visible = 'o';
}
