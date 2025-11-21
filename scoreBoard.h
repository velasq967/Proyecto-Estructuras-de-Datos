//
// ScoreBoard.h
//

#ifndef PROYECTO_ESTRUCTURAS_SCOREBOARD_H
#define PROYECTO_ESTRUCTURAS_SCOREBOARD_H

#include <string>
#include <unordered_map>

class ScoreBoard {
private:
    // nombreJugador -> mejor puntaje (menor número de movimientos)
    std::unordered_map<std::string, int> mejoresPuntajes;

public:
    // Registra un puntaje para un jugador.
    // Si el jugador no existe, lo crea.
    // Si ya existe, conserva SIEMPRE el mejor puntaje (el menor).
    void registrarPuntaje(const std::string& nombre, int puntaje);

    // Devuelve true si el jugador existe en el registro y coloca su puntaje en "puntaje".
    bool obtenerPuntaje(const std::string& nombre, int& puntaje) const;

    // Imprime todos los jugadores ordenados del menor puntaje al mayor.
    void imprimirTodosOrdenados() const;
};

#endif //PROYECTO_ESTRUCTURAS_SCOREBOARD_H
