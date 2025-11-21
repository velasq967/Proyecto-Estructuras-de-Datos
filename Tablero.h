//
// Tablero.h
//

#ifndef PROYECTO_ESTRUCTURAS_TABLERO_H
#define PROYECTO_ESTRUCTURAS_TABLERO_H

#include <vector>
#include <string>
#include "Node.h"

class Tablero {
private:
    static const int FILAS = 9;
    static const int COLUMNAS = 9;

    // Nodo superior izquierdo del tablero
    Node* head;

    // Contenedor auxiliar de todos los nodos (para construir y utilidades)
    std::vector<Node*> nodos;

    // Métodos internos de construcción
    void crearNodos();
    void enlazarNodos();
    void configurarBordes();

public:
    Tablero();
    ~Tablero();

    // Acceso básico
    Node* getHead() const;
    Node* getNode(int fila, int columna) const;

    // Muros internos
    void colocarMurosInternos(int cantidadMuros = 16);

    // TESOROS
    void colocarTesoros(int cantidadTesoros = 10);
    void reubicarTesoro(const std::string& tipoTesoro, Node* posicionJugador);

    // Utilidades para efectos de tesoros
    void resetearVisibles(bool mantenerMurosVisibles = false);
    void eliminarMurosAleatorios(int cantidad);
    Node* obtenerNodoAleatorioLibre(Node* posicionJugador = nullptr);

    // Impresiones
    void imprimirVisible() const;
    void imprimirReal() const;
};

#endif //PROYECTO_ESTRUCTURAS_TABLERO_H
