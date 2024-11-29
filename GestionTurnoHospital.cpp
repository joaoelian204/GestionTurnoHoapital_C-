
#include <iostream>
#include <string>
using namespace std;

// Clase Paciente
struct Paciente {
    int numero_turno;
    string nombre;
    string condicion_medica; // leve, grave, crítica
    Paciente* siguiente;
    Paciente* anterior; // Solo se usará en lista doblemente enlazada

    Paciente(int turno, string nom, string cond) 
        : numero_turno(turno), nombre(nom), condicion_medica(cond), siguiente(nullptr), anterior(nullptr) {}
};

// Lista Circular Simple para pacientes generales
class ListaCircularSimple {
private:
    Paciente* ultimo;

public:
    ListaCircularSimple() : ultimo(nullptr) {}

    void registrarPaciente(int turno, string nombre, string condicion) {
        Paciente* nuevo = new Paciente(turno, nombre, condicion);
        if (!ultimo) {
            ultimo = nuevo;
            nuevo->siguiente = nuevo;
        } else {
            nuevo->siguiente = ultimo->siguiente;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        cout << "Paciente " << nombre << " registrado en la lista general." << endl;
    }

    void atenderPaciente() {
        if (!ultimo) {
            cout << "No hay pacientes en la fila general." << endl;
            return;
        }
        Paciente* primero = ultimo->siguiente;
        cout << "Atendiendo a: " << primero->nombre << endl;

        if (primero == ultimo) {
            delete primero;
            ultimo = nullptr;
        } else {
            ultimo->siguiente = primero->siguiente;
            delete primero;
        }
    }

    void mostrarFila() {
        if (!ultimo) {
            cout << "No hay pacientes en la fila general." << endl;
            return;
        }
        Paciente* actual = ultimo->siguiente;
        do {
            cout << "Turno: " << actual->numero_turno << ", Nombre: " << actual->nombre 
                << ", Condición: " << actual->condicion_medica << endl;
            actual = actual->siguiente;
        } while (actual != ultimo->siguiente);
    }
};

// Lista Circular Doble para pacientes prioritarios
class ListaCircularDoble {
private:
    Paciente* ultimo;

public:
    ListaCircularDoble() : ultimo(nullptr) {}

    void registrarPaciente(int turno, string nombre, string condicion) {
        Paciente* nuevo = new Paciente(turno, nombre, condicion);
        if (!ultimo) {
            ultimo = nuevo;
            nuevo->siguiente = nuevo;
            nuevo->anterior = nuevo;
        } else {
            nuevo->siguiente = ultimo->siguiente;
            nuevo->anterior = ultimo;
            ultimo->siguiente->anterior = nuevo;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        cout << "Paciente " << nombre << " registrado en la lista prioritaria." << endl;
    }

    void atenderPaciente() {
        if (!ultimo) {
            cout << "No hay pacientes en la fila prioritaria." << endl;
            return;
        }
        Paciente* primero = ultimo->siguiente;
        cout << "Atendiendo a: " << primero->nombre << endl;

        if (primero == ultimo) {
            delete primero;
            ultimo = nullptr;
        } else {
            ultimo->siguiente = primero->siguiente;
            primero->siguiente->anterior = ultimo;
            delete primero;
        }
    }

    void mostrarFila() {
        if (!ultimo) {
            cout << "No hay pacientes en la fila prioritaria." << endl;
            return;
        }
        Paciente* actual = ultimo->siguiente;
        do {
            cout << "Turno: " << actual->numero_turno << ", Nombre: " << actual->nombre 
                << ", Condición: " << actual->condicion_medica << endl;
            actual = actual->siguiente;
        } while (actual != ultimo->siguiente);
    }
};

// Funcionalidad del menú
void menu() {
    ListaCircularSimple listaGeneral;
    ListaCircularDoble listaPrioritaria;
    int opcion, turno = 1;

    do {
        cout << "\n--- Gestión de Turnos ---\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Mover paciente a lista prioritaria\n";
        cout << "3. Atender paciente\n";
        cout << "4. Mostrar filas\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre, condicion;
            cout << "Nombre del paciente: ";
            cin >> nombre;
            cout << "Condición médica (leve, grave, crítica): ";
            cin >> condicion;
            if (condicion == "leve") {
                listaGeneral.registrarPaciente(turno++, nombre, condicion);
            } else {
                listaPrioritaria.registrarPaciente(turno++, nombre, condicion);
            }
        } else if (opcion == 2) {
            // Simulación: mover paciente de general a prioritario
            cout << "Función no implementada completamente en este bloque inicial." << endl;
        } else if (opcion == 3) {
            int tipo;
            cout << "Atender de: 1) General, 2) Prioritario: ";
            cin >> tipo;
            if (tipo == 1) {
                listaGeneral.atenderPaciente();
            } else if (tipo == 2) {
                listaPrioritaria.atenderPaciente();
            } else {
                cout << "Opción inválida." << endl;
            }
        } else if (opcion == 4) {
            cout << "\nPacientes en fila general:\n";
            listaGeneral.mostrarFila();
            cout << "\nPacientes en fila prioritaria:\n";
            listaPrioritaria.mostrarFila();
        } else if (opcion != 5) {
            cout << "Opción inválida, intente de nuevo." << endl;
        }
    } while (opcion != 5);

    cout << "Gracias por usar el sistema." << endl;
}

int main() {
    menu();
    return 0;
}
