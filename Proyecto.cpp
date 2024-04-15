#include <iostream>
#include <list>
#include <string>

using namespace std;

// Estructura para representar un pasajero
struct Pasajero {
    string nombre;
    int asiento;
};

// Estructura para representar una amenidad
struct Amenidad {
    string nombre;
    int cantidad;
    Amenidad* siguiente;
};

// Definicion de la estructura de un vagon
struct Vagon {
    string nombre;
    Vagon* siguiente;
    Vagon* anterior;
    Amenidad* primeraAmenidad;
    list<Pasajero> pasajeros;
};

// Estructura para representar el tren
struct Tren {
    Vagon* primero;
    Vagon* ultimo;
    // Constructor
    Tren() {
        primero = nullptr;
        ultimo = nullptr;
    }
};

// Funcion para agregar un nuevo vagon a la lista
void agregarVagon(Tren& tren, string nombre) {
    Vagon* nuevoVagon = new Vagon;
    nuevoVagon->nombre = nombre;
    nuevoVagon->siguiente = nullptr;
    nuevoVagon->anterior = nullptr;
    nuevoVagon->primeraAmenidad = nullptr;
    nuevoVagon->pasajeros = list<Pasajero>();

    if (tren.primero == nullptr) {
        tren.primero = nuevoVagon;
        tren.ultimo = nuevoVagon;
    } else {
        tren.ultimo->siguiente = nuevoVagon;
        nuevoVagon->anterior = tren.ultimo;
        tren.ultimo = nuevoVagon;
    }
}

// Funcion para eliminar el ultimo vagon de la lista
void eliminarUltimoVagon(Tren& tren) {
    if (tren.ultimo != nullptr) {
        if (tren.ultimo == tren.primero) {
            delete tren.ultimo;
            tren.primero = tren.ultimo = nullptr;
        } else {
            Vagon* temp = tren.ultimo;
            tren.ultimo = tren.ultimo->anterior;
            tren.ultimo->siguiente = nullptr;
            delete temp;
        }
    }
}

// Funcion para mostrar todos los vagones en la lista
void mostrarVagones(const Tren& tren) {
    cout << "Lista de Vagones:" << endl;
    Vagon* actual = tren.primero;
    while (actual != nullptr) {
        cout << "- " << actual->nombre << endl;
        actual = actual->siguiente;
    }
    cout << endl;
}

// Funcion para modificar un vagon
void modificarVagon(Vagon* vagon, string nuevoNombre) {
    vagon->nombre = nuevoNombre;
}

// Funcion para agregar una amenidad a un vagon
void agregarAmenidad(Vagon* vagon, string nombre, int cantidad) {
    Amenidad* nuevaAmenidad = new Amenidad;
    nuevaAmenidad->nombre = nombre;
    nuevaAmenidad->cantidad = cantidad;

    if (vagon->primeraAmenidad == nullptr) {
        vagon->primeraAmenidad = nuevaAmenidad;
    } else {
        nuevaAmenidad->siguiente = vagon->primeraAmenidad;
        vagon->primeraAmenidad = nuevaAmenidad;
    }
}

// Funcion para mostrar las amenidades de un vagon
void mostrarAmenidades(const Vagon& vagon) {
    cout << "Amenidades en el vagon " << vagon.nombre << ":" << endl;
    Amenidad* actual = vagon.primeraAmenidad;
    while (actual != nullptr) {
        cout << "- " << actual->nombre << ": " << actual->cantidad << endl;
        actual = actual->siguiente;
    }
    cout << endl;
}

// Funcion para agregar un pasajero a un vagon
void agregarPasajero(Vagon* vagon, string nombre, int asiento) {
    Pasajero nuevoPasajero;
    nuevoPasajero.nombre = nombre;
    nuevoPasajero.asiento = asiento;
    vagon->pasajeros.push_back(nuevoPasajero);
}

// Funcion para mostrar los pasajeros de un vagon
void mostrarPasajeros(const Vagon& vagon) {
    cout << "Pasajeros en el vagon " << vagon.nombre << ":" << endl;
    for (const auto& pasajero : vagon.pasajeros) {
        cout << "- " << pasajero.nombre << " (Asiento: " << pasajero.asiento << ")" << endl;
    }
    cout << endl;
}

int main() {
    Tren tren;

    int opcion;
    string nombreVagon;
    string nombreAmenidad;
    int cantidadAmenidad;
    string nombrePasajero;
    int asientoPasajero;

    do {
        cout << "\n*******************************************\n";
        cout << "1 : Agregar Vagon \n";
        cout << "2 : Eliminar Ultimo Vagon \n";
        cout << "3 : Mostrar Vagones \n";
        cout << "4 : Agregar Amenidad a Vagon \n";
        cout << "5 : Mostrar Amenidades de Vagon \n";
        cout << "6 : Agregar Pasajero a Vagon \n";
        cout << "7 : Mostrar Pasajeros de Vagon \n";
        cout << "8 : Salir \n";

        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;
        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre del nuevo vagon: ";
                cin >> nombreVagon;
                agregarVagon(tren, nombreVagon);
                cout << "Vagon agregado correctamente." << endl;
                break;
            case 2:
                eliminarUltimoVagon(tren);
                cout << "Ultimo vagon eliminado correctamente." << endl;
                break;
            case 3:
                mostrarVagones(tren);
                break;
            case 4:
                cout << "Ingrese el nombre del vagon: ";
                cin >> nombreVagon;
                cout << "Ingrese el nombre de la amenidad: ";
                cin >> nombreAmenidad;
                cout << "Ingrese la cantidad de la amenidad: ";
                cin >> cantidadAmenidad;
                // Buscar el vagon por nombre y agregar la amenidad
                agregarAmenidad(tren.primero, nombreAmenidad, cantidadAmenidad);
                cout << "Amenidad agregada correctamente al vagon." << endl;
                break;
            case 5:
                cout << "Ingrese el nombre del vagon: ";
                cin >> nombreVagon;
                // Buscar el vagon por nombre y mostrar sus amenidades
                // Por simplicidad, se asume que el vagon existe
                mostrarAmenidades(*tren.primero);
                break;
            case 6:
                cout << "Ingrese el nombre del vagon: ";
                cin >> nombreVagon;
                cout << "Ingrese el nombre del pasajero: ";
                cin >> nombrePasajero;
                cout << "Ingrese el numero de asiento: ";
                cin >> asientoPasajero;
                // Buscar el vagon por nombre y agregar el pasajero
                // Por simplicidad, se asume que el vagon existe
                agregarPasajero(tren.primero, nombrePasajero, asientoPasajero);
                cout << "Pasajero agregado correctamente al vagon." << endl;
                break;
            case 7:
                cout << "Ingrese el nombre del vagon: ";
                cin >> nombreVagon;
                // Buscar el vagon por nombre y mostrar sus pasajeros
                // Por simplicidad, se asume que el vagon existe
                mostrarPasajeros(*tren.primero);
                break;
            case 8:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida\n";
                break;
            case 9:
                cout << "Ingrese el nombre del vagon que desea modificar: ";
                cin >> nombreVagon;
                cout << "Ingrese el nuevo nombre para el vagon: ";
                cin >> nuevoNombre;
                modificarVagon(tren.primero, nuevoNombre);
                cout << "Nombre del vagon modificado correctamente." << endl;
                break;
        }
    } while (opcion != 8);

    return 0;
}
