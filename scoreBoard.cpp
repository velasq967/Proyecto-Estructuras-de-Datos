//
// ScoreBoard.cpp
//

#include "scoreBoard.h"
#include <vector>
#include <algorithm>
#include <iostream>

void scoreBoard::registrarPuntaje(const std::string& nombre, int puntaje) {
    auto it = mejoresPuntajes.find(nombre);
    if (it == mejoresPuntajes.end()) {
        // Jugador nuevo
        mejoresPuntajes[nombre] = puntaje;
    } else {
        // Ya existe, guardamos el mejor puntaje (el menor)
        if (puntaje < it->second) {
            it->second = puntaje;
        }
    }
}

bool scoreBoard::obtenerPuntaje(const std::string& nombre, int& puntaje) const {
    auto it = mejoresPuntajes.find(nombre);
    if (it == mejoresPuntajes.end()) {
        return false;
    }
    puntaje = it->second;
    return true;
}

void scoreBoard::imprimirTodosOrdenados() const {
    if (mejoresPuntajes.empty()) {
        std::cout << "No hay puntajes registrados.\n";
        return;
    }

    // Pasamos el map a un vector para poder ordenar
    std::vector<std::pair<std::string, int>> lista;
    lista.reserve(mejoresPuntajes.size());

    for (const auto& par : mejoresPuntajes) {
        lista.emplace_back(par.first, par.second);
    }

    // Ordenar por puntaje ascendente (menor a mayor)
    std::sort(lista.begin(), lista.end(),
              [](const auto& a, const auto& b) {
                  return a.second < b.second;
              });

    std::cout << "=== ScoreBoard (mejores puntajes) ===\n";
    for (const auto& par : lista) {
        std::cout << "Jugador: " << par.first
                  << " | Puntaje: " << par.second << "\n";
    }
}
