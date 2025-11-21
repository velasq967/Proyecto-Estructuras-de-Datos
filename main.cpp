


#include "Tablero.h"
using namespace std;

int main() {

    return 0;
}

void iniciar_juego() {

    Tablero tablero = Tablero();

    bool ContinuarJuego = true;
    while (ContinuarJuego) {
        tablero.mostrar_tablero();
    }
}