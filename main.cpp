#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Estructura para representar un esbirro
struct Esbirro {
    int vida;
    int ataque;
    bool es_cano;
    int ataques_recibidos;

    // Constructor
    Esbirro(int v, int a, bool c) : vida(v), ataque(a), es_cano(c), ataques_recibidos(0) {}
};

int main() {
    // Lectura de datos de entrada
    int vida_mechon, num_esbirros;
    cin >> vida_mechon;      // Vida inicial del mechón
    cin >> num_esbirros;     // Cantidad total de esbirros

    // Vectores para almacenar las características de los esbirros
    vector<int> vidas(num_esbirros);     // Puntos de vida de cada esbirro
    vector<int> ataques(num_esbirros);   // Puntos de ataque de cada esbirro
    vector<int> canos(num_esbirros);     // Si el esbirro es CANO (1) o no (0)

    // Lectura de las características de los esbirros
    for (int i = 0; i < num_esbirros; i++) cin >> vidas[i];
    for (int i = 0; i < num_esbirros; i++) cin >> ataques[i];
    for (int i = 0; i < num_esbirros; i++) cin >> canos[i];

    // Cola para manejar el orden de los esbirros
    queue<Esbirro*> cola;
    for (int i = 0; i < num_esbirros; i++) {
        cola.push(new Esbirro(vidas[i], ataques[i], canos[i] == 1));
    }

    // Variables para el seguimiento de la batalla
    int danio_total = 0;         // Daño total causado por el mechón
    int esbirros_eliminados = 0; // Contador de esbirros eliminados
    int poder_ataque = 2;        // Poder de ataque inicial del mechón

    // Simulación de la batalla
    while (!cola.empty() && vida_mechon > 0) {
        Esbirro* actual = cola.front();
        cola.pop();

        // 1. El mechón ataca primero
        int danio_causado = min(poder_ataque, actual->vida);
        actual->vida -= danio_causado;
        actual->ataques_recibidos++;
        danio_total += danio_causado;        

        // 2. Verificar si el esbirro murió
        if (actual->vida <= 0) {
            esbirros_eliminados++;
            // Aumentar poder de ataque después de 5 esbirros eliminados
            if (esbirros_eliminados % 5 == 0) {
                poder_ataque++;
            }
            delete actual;
            continue;
        }

        

        // 3. Verificar si es CANO y debe dividirse
        if (actual->es_cano && actual->ataques_recibidos == 2) {
            // Crear dos nuevos esbirros con stats reducidos
            if (actual->vida > 1 && actual->ataque > 1) {
                cola.push(new Esbirro(actual->vida - 1, actual->ataque - 1, false));
                cola.push(new Esbirro(actual->vida - 1, actual->ataque - 1, false));
            }
            delete actual;
            continue;
        }

        // 4. Si el esbirro sobrevive y no se divide, ataca al mechón
        vida_mechon -= actual->ataque;
        cola.push(actual);
    }

    // Limpieza de memoria
    while (!cola.empty()) {
        delete cola.front();
        cola.pop();
    }

    // Impresión de resultados
    cout << danio_total << endl;
    cout << (vida_mechon > 0 ? "EZ pizi" : "RIP mechon") << endl;

    return 0;
}