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
};

// Clase para representar un vagón
class Vagon {
private:
    string nombre;
    list<Amenidad> amenidades;
    list<Pasajero> pasajeros;
public:
    // Constructor
    Vagon(string nombre) : nombre(nombre) {}

    // Métodos para gestionar amenidades
    void agregarAmenidad(string nombre, int cantidad) {
        amenidades.push_back({nombre, cantidad});
    }

    void mostrarAmenidades() const {
        for (const auto& amenidad : amenidades) {
            cout << amenidad.nombre << ": " << amenidad.cantidad << endl;
        }
    }

    // Métodos para gestionar pasajeros
    void agregarPasajero(string nombre, int asiento) {
        pasajeros.push_back({nombre, asiento});
    }

    void mostrarPasajeros() const {
        for (const auto& pasajero : pasajeros) {
            cout << pasajero.nombre << " - Asiento: " << pasajero.asiento << endl;
        }
    }

    // Obtener nombre del vagón
    string getNombre() const {
        return nombre;
    }
};

// Clase para representar un tren
class Tren {
private:
    list<Vagon> vagones;
public:
    // Métodos para gestionar los vagones
    void agregarVagon(string nombre) {
        vagones.push_back(Vagon(nombre));
    }

    void mostrarVagones() const {
        for (const auto& vagon : vagones) {
            cout << "Vagon: " << vagon.getNombre() << endl;
            vagon.mostrarAmenidades();
            vagon.mostrarPasajeros();
            cout << endl;
        }
    }
};

int main() {
    Tren tren;

    tren.agregarVagon("Vagon 1");
    tren.agregarVagon("Vagon 2");

    tren.mostrarVagones();

    return 0;
}
