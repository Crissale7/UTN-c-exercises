// Asistencia mecánica.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <queue>
#include <string>
#include <ctime>

using namespace std;

struct Movil {
    int idMovil;
    char conductor[100];
    int zona;
    char celular[50];
};

struct Abonado {
    int idAbo;
    char nombre[100];
    char celular[50];
    bool cuotasAlDia;
};

void notificarAsignacion(string celularDestino, int nroCaso, string nombre) {
    // envia un SMS al celular especificado como parametro
}

int getTime() {
    // retorna la hora actual expresada en milisegundos
}

int main() {
    queue<int> abonados;
    queue<int> moviles;

    while (true) {
        cout << "Ingrese 1 si llama un abonado, 2 si llama un móvil o 3 para finalizar el programa: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            int idAbo;
            int zona;
            bool cuotasAlDia;

            cout << "Ingrese el número de abonado (idAbo): ";
            cin >> idAbo;

            cout << "Ingrese la zona en la que se encuentra el abonado (0-9): ";
            cin >> zona;

            cout << "¿El abonado tiene sus cuotas al día? (1 para sí, 0 para no): ";
            cin >> cuotasAlDia;

            if (cuotasAlDia) {
                abonados.push(idAbo);
                cout << "El abonado ha sido agregado a la cola de espera." << endl;
                // Calcular tiempo aproximado de espera y notificar al abonado
                notificarAsignacion("celular del abonado", -1, "nombre del conductor del móvil");
            }
            else {
                cout << "El abonado no tiene sus cuotas al día." << endl;
            }
        }
        else if (opcion == 2) {
            int idMovil;

            cout << "Ingrese el número de caso que acaba de resolver el móvil: ";
            cin >> idMovil;

            moviles.push(idMovil);
            cout << "El móvil ha sido agregado a la cola de espera." << endl;
            // Calcular tiempo aproximado de espera y notificar al móvil
            notificarAsignacion("celular del conductor del móvil", -1, "nombre del abonado que lo está esperando");
        }
        else if (opcion == 3) {
            break;
        }
        else {
            cout << "Opción inválida." << endl;
        }

        // Verificar si es posible realizar una asignación móvil/abonado y notificar a ambos involucrados vía mensaje de texto (SMS) al celular.
        if (!abonados.empty() && !moviles.empty()) {
            int idAbo = abonados.front();
            int idMovil = moviles.front();

            // Realizar asignación móvil/abonado
            abonados.pop();
            moviles.pop();

            // Notificar al abonado y al móvil
            notificarAsignacion("celular del abonado", idMovil, "nombre del conductor del móvil");
            notificarAsignacion("celular del conductor del móvil", -1, "nombre del abonado que lo está esperando");
        }
    }

    return 0;
}

// punto 2
#include <iostream>
#include <queue>
#include <string>
#include <ctime>

using namespace std;

struct Movil {
    int idMovil;
    char conductor[100];
    int zona;
    char celular[50];
};

struct Abonado {
    int idAbo;
    char nombre[100];
    char celular[50];
    bool cuotasAlDia;
};

void notificarAsignacion(string celularDestino, int nroCaso, string nombre) {
    // envia un SMS al celular especificado como parametro
}

int getTime() {
    // retorna la hora actual expresada en milisegundos
}

struct Caso {
    int nroCaso;
    int tiempoAtencion;
};

int main() {
    queue<int> abonados;
    queue<int> moviles;

    while (true) {
        cout << "Ingrese 1 si llama un abonado, 2 si llama un móvil o 3 para finalizar el programa: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            int idAbo;
            int zona;
            bool cuotasAlDia;

            cout << "Ingrese el número de abonado (idAbo): ";
            cin >> idAbo;

            cout << "Ingrese la zona en la que se encuentra el abonado (0-9): ";
            cin >> zona;

            cout << "¿El abonado tiene sus cuotas al día? (1 para sí, 0 para no): ";
            cin >> cuotasAlDia;

            if (cuotasAlDia) {
                abonados.push(idAbo);
                cout << "El abonado ha sido agregado a la cola de espera." << endl;
                // Calcular tiempo aproximado de espera y notificar al abonado
                notificarAsignacion("celular del abonado", -1, "nombre del conductor del móvil");
            }
            else {
                cout << "El abonado no tiene sus cuotas al día." << endl;
            }
        }
        else if (opcion == 2) {
            int idMovil;

            cout << "Ingrese el número de caso que acaba de resolver el móvil: ";
            cin >> idMovil;

            moviles.push(idMovil);
            cout << "El móvil ha sido agregado a la cola de espera." << endl;
            // Calcular tiempo aproximado de espera y notificar al móvil
            notificarAsignacion("celular del conductor del móvil", -1, "nombre del abonado que lo está esperando");
        }
        else if (opcion == 3) {
            break;
        }
        else {
            cout << "Opción inválida." << endl;
        }

        // Verificar si es posible realizar una asignación móvil/abonado y notificar a ambos involucrados vía mensaje de texto (SMS) al celular.
        if (!abonados.empty() && !moviles.empty()) {
            int idAbo = abonados.front();
            int idMovil = moviles.front();

            // Realizar asignación móvil/abonado
            abonados.pop();
            moviles.pop();

            // Notificar al abonado y al móvil
            notificarAsignacion("celular del abonado", idMovil, "nombre del conductor del móvil");
            notificarAsignacion("celular del conductor del móvil", -1, "nombre del abonado que lo está esperando");
        }
    }

    // Calcular promedio de tiempo de atención para cada zona
    const int CANT_ZONAS = 10;
    float promedios[CANT_ZONAS] = { 0 };
    int cantCasos[CANT_ZONAS] = { 0 };
    Caso casosAtendidos[1000];
    int cantCasosAtendidos = 0;

    for (int i = 0; i < cantCasosAtendidos; i++) {
        Caso caso = casosAtendidos[i];
        promedios[caso.zona] += caso.tiempoAtencion;
        cantCasos[caso.zona]++;
    }

    for (int i = 0; i < CANT_ZONAS; i);