#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Estructura para representar un esbirro
struct Esbirro {
    int vida; //Puntos de vida del esbirro
    int ataque;//Daño que puede causar al mechón
    bool es_cano;//Si el esbirro es cano (puede dividirse)
    int ataques_recibidos;//Veces que ha sido atacado por el mechón

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
    while (!cola.empty() && vida_mechon > 0) { //Mientras queden esbirros y el mechon siga vivo, continua la batalla
        Esbirro* actual = cola.front();
        cola.pop(); //Se saca el primer esbirro de la cola

        // 1. El mechón ataca primero
        int danio_causado = min(poder_ataque, actual->vida);
        actual->vida -= danio_causado;
        actual->ataques_recibidos++;
        danio_total += danio_causado; //Se suma el daño al total y se registra el daño recibido       

        // 2. Verificar si el esbirro murió
        if (actual->vida <= 0) {
            esbirros_eliminados++;//Si el esbirro muere, se incrementa el contador de esbirros eliminados
            // Aumentar poder de ataque después de 5 esbirros eliminados
            if (esbirros_eliminados % 5 == 0) {
                poder_ataque++;
            }
            delete actual;//Se libera memoria del esbirro y se salta a la siguiente iteración
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
        cola.push(actual);//vuelve al final de la cola
    }

    // Limpieza de memoria
    while (!cola.empty()) {//Se limpian los esbirros restantes que quedaron en la cola
        delete cola.front();
        cola.pop();
    }

    // Impresión de resultados
    cout << danio_total << endl;//Daño total que hizo el mechon
    cout << (vida_mechon > 0 ? "EZ pizi" : "RIP mechon") << endl;//Se imprime si sobrevivió o no

    return 0;
}