#include <iostream>
#include <string>
#include <algorithm> // Para usar transform
using namespace std;

// Clase Paciente
struct Paciente {
    int numero_turno;
    string nombre;
    string condicion_medica; // leve, grave, crítica
    Paciente* siguiente;
    Paciente* anterior; // Solo usado en lista doblemente enlazada

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
        if (!ultimo) { // Lista vacía
            ultimo = nuevo;
            nuevo->siguiente = nuevo;
        } else { // Lista no vacía
            nuevo->siguiente = ultimo->siguiente;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        cout << "Paciente " << nombre << " registrado en la lista general." << endl;
    }

    Paciente* atenderPaciente() {
        if (!ultimo) {
            cout << "No hay pacientes en la fila general." << endl;
            return nullptr;
        }
        Paciente* primero = ultimo->siguiente;
        if (primero == ultimo) {
            ultimo = nullptr; // Solo un paciente
        } else {
            ultimo->siguiente = primero->siguiente;
        }
        cout << "Atendiendo a: " << primero->nombre << endl;
        return primero;
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

    Paciente* moverPaciente() {
        if (!ultimo) {
            cout << "No hay pacientes para mover en la fila general." << endl;
            return nullptr;
        }
        return atenderPaciente(); // Remueve y retorna el paciente atendido
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
        if (!ultimo) { // Lista vacía
            ultimo = nuevo;
            nuevo->siguiente = nuevo;
            nuevo->anterior = nuevo;
        } else { // Lista no vacía
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
        if (primero == ultimo) {
            ultimo = nullptr; // Solo un paciente
        } else {
            ultimo->siguiente = primero->siguiente;
            primero->siguiente->anterior = ultimo;
        }
        cout << "Atendiendo a: " << primero->nombre << endl;
        delete primero; // Liberar memoria
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

    void registrarDesdeListaGeneral(Paciente* paciente) {
        if (paciente) {
            registrarPaciente(paciente->numero_turno, paciente->nombre, paciente->condicion_medica);
            delete paciente; // Liberar memoria
        }
    }
};

// Función del menú interactivo
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
            cin >> ws; // Limpiar espacios iniciales
            getline(cin, nombre); // Capturar nombres con espacios
            cout << "Condición médica (leve, grave, crítica): ";
            cin >> ws;
            getline(cin, condicion);

            // Convertir a minúsculas para validación
            transform(condicion.begin(), condicion.end(), condicion.begin(), ::tolower);

            if (condicion == "leve") {
                listaGeneral.registrarPaciente(turno++, nombre, condicion);
            } else if (condicion == "grave" || condicion == "crítica") {
                listaPrioritaria.registrarPaciente(turno++, nombre, condicion);
            } else {
                cout << "Condición médica no válida. Intente nuevamente." << endl;
            }
        } else if (opcion == 2) {
            Paciente* pacienteMovido = listaGeneral.moverPaciente();
            if (pacienteMovido) {
                listaPrioritaria.registrarDesdeListaGeneral(pacienteMovido);
            }
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
