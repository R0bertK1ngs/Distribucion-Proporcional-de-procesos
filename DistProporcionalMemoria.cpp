#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

//          Integrantes
//          Robert Reyes
//          Diego Fariña
//          Jorge Lagos
//          Claudio Martinez

/*
Dado un sistema multiprogramado monoprocesador, de un ambiente de paginación, con una RAM de 2MB, y se ejecutan procesos, 
determine a través de una rutina programada en C++, 
cuanto tiempo le lleva al sistema en ejecutar los procesos (TurnaRound Time), ingresados al sistema.
Considere:
• Distribución Proporcional, Tamaño bloque de Memoria=512 bytes
• Datos de entrada: Nombre Proceso, tamaño en bytes, KB, MB o GB; Tiempo de acceso mls,
Tiempo de transferencia en mls y tiempo promedio de ejecución en mls. (máximo 6 procesos)
• Datos de Salida: Tiempo de Fallas, TurnaRound Time por proceso
*/



using namespace std;

struct Proceso {
    string nombre;
    long tamano; // en Bytes
    long tiempoAcceso; // en milisegundos
    long tiempoTransferencia; // en milisegundos
    long tiempoEjecucion; // en milisegundos
    long paginas;
    long bloques;
    long turnAroundTime; // en milisegundos
    long tiempoFallas; // en milisegundos
};

const long TAMANO_PAGINA = 512; // Tamaño de la página en bytes
const long TAMANO_RAM = 2 * 1024 * 1024; // Tamaño de la RAM en bytes (2MB)
const long BLOQUES_DISPONIBLES = TAMANO_RAM / TAMANO_PAGINA;

int convertirTamanoB(int tamano, string unidad) {
    if (unidad == "a") return tamano;
    if (unidad == "b") return tamano * 1024; // KB
    if (unidad == "c") return tamano * 1024 * 1024; // MB
    if (unidad == "d") return tamano * 1024 * 1024 * 1024; // GB
    return tamano; // por defecto se asume que está en Bytes
}

void calcularBloques(vector<Proceso>& procesos) {
    long NumeroPaginas = 0;

    for (auto& p : procesos) { // obtener numero de paginas
        float pag = static_cast<float>(p.tamano) / TAMANO_PAGINA;
        p.paginas = static_cast<long>(ceil(pag)); // Truncar hacia arriba
        NumeroPaginas += p.paginas;
    }
    cout << "Numero de pagina totales " << NumeroPaginas << "\n"; 
    for (auto& p : procesos) { // obtener numero de bloques asignados
        float bloq = (static_cast<float>(p.paginas) / NumeroPaginas) * BLOQUES_DISPONIBLES;
        if (bloq <= 1) {
            p.bloques = 1;
        } else {
            p.bloques = static_cast<long>(floor(bloq)); // truncar hacia abajo
        }
    }
}

void calcularFallosDePagina(vector<Proceso>& procesos) {
    for (auto& p : procesos) {
        float Slots = static_cast<float>(p.paginas) / p.bloques;
        long SlotsEntero = static_cast<long>(floor(Slots)); //truncar hacia abajo
        p.tiempoFallas = 2 * p.paginas * (p.tiempoAcceso + p.tiempoTransferencia);
    }
}

void calcularTurnaroundTime(vector<Proceso>& procesos) {
    for (auto& p : procesos) {
        p.turnAroundTime = p.tiempoFallas + (p.paginas * p.tiempoEjecucion);
    }
}

int main() {
    int maxProcesos = 0;
    while (true) {
        cout << "|-----------------------------------------|" 
        << "\n Ingresar numero de procesos (max 6): ";
        cin >> maxProcesos;
        if (cin.fail() || maxProcesos < 1 || maxProcesos > 6) {
            cout << "Ingresar un valor valido (1-6)" << endl;
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
        } else {
            break; // La entrada es válida, salir del bucle
        }
    }

    vector<Proceso> procesos;
    cin.ignore();

    for (int i = 0; i < maxProcesos; ++i) {
        Proceso p;
        string unidad;
        cout << "Distribucion proporcional de procesos\n"
             << "|-----------------------------------------|" << 
             "\n Ingrese el nombre del proceso " << i + 1 << ": ";
        getline(cin, p.nombre);

        // Validar unidad de tamaño
        while (true) {
            cout << "\n Ingrese la unidad de tamano:\n" 
                 << "|-----------------Opciones----------------|\n" 
                 << "        a)Bytes b)KB c)MB d)GB" 
                 << "\nAlternativa: ";
            cin >> unidad;
            if (unidad == "a" || unidad == "b" || unidad == "c" || unidad == "d") {
                break; // Unidad válida
            } else {
                cout << "Unidad no valida. Ingrese una unidad valida (a, b, c, d)" << endl;
            }
        }

        // Validar tamaño del proceso
        while (true) {
            cout << "|------------------------------------|\n" 
                 << " Ingrese el tamano del proceso: ";
            cin >> p.tamano;
            if (cin.fail() || p.tamano <= 0) {
                cout << "Ingresar un tamaño valido (entero positivo)" << endl;
                cin.clear(); // Limpia el estado de error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            } else {
                p.tamano = convertirTamanoB(p.tamano, unidad);
                break; // Tamaño válido
            }
        }

        // Validar tiempo de acceso
        while (true) {
            cout << " Ingrese el tiempo de acceso (en ms): ";
            cin >> p.tiempoAcceso;
            if (cin.fail() || p.tiempoAcceso <= 0) {
                cout << "Ingresar un tiempo valido (entero positivo)" << endl;
                cin.clear(); // Limpia el estado de error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            } else {
                break; // Tiempo de acceso válido
            }
        }

        // Validar tiempo de transferencia
        while (true) {
            cout << " Ingrese el tiempo de transferencia (en ms): ";
            cin >> p.tiempoTransferencia;
            if (cin.fail() || p.tiempoTransferencia <= 0) {
                cout << "Ingresar un tiempo valido (entero positivo)" << endl;
                cin.clear(); // Limpia el estado de error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            } else {
                break; // Tiempo de transferencia válido
            }
        }

        // Validar tiempo de ejecución
        while (true) {
            cout << " Ingrese el tiempo promedio de ejecucion (en ms): ";
            cin >> p.tiempoEjecucion;
            if (cin.fail() || p.tiempoEjecucion <= 0) {
                cout << "Ingresar un tiempo valido (entero positivo)" << endl;
                cin.clear(); // Limpia el estado de error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            } else {
                break; // Tiempo de ejecución válido
            }
        }
        procesos.push_back(p);
        cin.ignore();
    }

    calcularBloques(procesos);
    calcularFallosDePagina(procesos);
    calcularTurnaroundTime(procesos);

    cout << "\nResultados:\n";
    for (const auto& p : procesos) {
        cout << " Proceso " << p.nombre 
             << " - Tiempo de Fallas: " << p.tiempoFallas << " ms (" << p.tiempoFallas / 60000 << " minutos), "
             << " Turnaround Time: " << p.turnAroundTime << " ms (" << p.turnAroundTime / 60000 << " minutos)\n";
    }
    return 0;
}
