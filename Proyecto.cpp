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



//krisbell


#include <iostream>
#include <list>
#include <string>
#include <set>

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



















// Definición de la estructura de un vagón
struct Vagon {

    string nombre;
    list<Pasajero> pasajeros;
    list<Amenidad> amenidades;
    Vagon* siguiente;
    Vagon* anterior;
};

// Función para agregar un nuevo vagon a la lista
void agregarVagon(Vagon*& primero, Vagon*& ultimo, string nombre) {
    Vagon* nuevoVagon = new Vagon;
    nuevoVagon->nombre = nombre;
    nuevoVagon->siguiente = nullptr;
    nuevoVagon->anterior = nullptr;

    if (primero == nullptr) {
        primero = ultimo = nuevoVagon;
    } else {
        ultimo->siguiente = nuevoVagon;
        nuevoVagon->anterior = ultimo;
        ultimo = nuevoVagon;
    }
}

// Función para eliminar el último vagon de la lista
void eliminarUltimoVagon(Vagon*& primero, Vagon*& ultimo) {
    if (ultimo != nullptr) {
        if (ultimo == primero) {
            delete ultimo;
            primero = ultimo = nullptr;
        } else {
            Vagon* temp = ultimo;
            ultimo = ultimo->anterior;
            ultimo->siguiente = nullptr;
            delete temp;
        }
    }
}

// Función para mostrar todos los vagones en la lista
void mostrarVagones(Vagon* primero) {
    cout << "Lista de Vagones:" << endl;
    Vagon* actual = primero;
    while (actual != nullptr) {
        cout << "- " << actual->nombre << endl;
        actual = actual->siguiente;
    }
}
//Administración de información:

// Función para verificar si hay vagones en la lista del tren
bool hayVagones(Vagon* primero) {
    return primero != nullptr;
}

//Gestión de pasajeros

//Agrega pasajero
void agregarPasajero(Vagon* vagon) {
    Pasajero nuevoPasajero;
    cout << "Ingrese el nombre del pasajero: ";
    getline(cin, nuevoPasajero.nombre);
    cout << "Ingrese el numero de asiento del pasajero: ";
    cin >> nuevoPasajero.asiento;

    vagon->pasajeros.push_back(nuevoPasajero);
    cin.ignore(); // Limpiar el buffer de entrada
}
//Elimina pasajero
void eliminarPasajero(Vagon* vagon, const string& nombrePasajero) {
    vagon->pasajeros.remove_if([&](const Pasajero& p) { return p.nombre == nombrePasajero; });
}
//Muestra pasajero
void mostrarPasajeros(Vagon* vagon) {
    cout << "Lista de Pasajeros en el Vagon " << vagon->nombre << ":" << endl;
    for (const auto& pasajero : vagon->pasajeros) {
        cout << "- Nombre: " << pasajero.nombre << ", Asiento: " << pasajero.asiento << endl;
    }
}

// Gestion de amenidades

//Agregar amenidad
void agregarAmenidad(Vagon* vagon) {
    Amenidad nuevaAmenidad;
    cout << "Ingrese el nombre de la nueva amenidad: ";
    getline(cin, nuevaAmenidad.nombre);
    cout << "Ingrese la cantidad disponible de la amenidad: ";
    cin >> nuevaAmenidad.cantidad;

    vagon->amenidades.push_back(nuevaAmenidad);
    cin.ignore(); // Limpiar el buffer de entrada
}

// Eliminar amenidad
void eliminarAmenidad(Vagon* vagon, const string& nombreAmenidad) {
    vagon->amenidades.remove_if([&](const Amenidad& a) { return a.nombre == nombreAmenidad; });
}



//Funciones para modificar información de los vagones, amenidades y pasajeros

//Modificar vagones
void modificarNombreVagon(Vagon* vagon, const string& nuevoNombre) {
    if (vagon != nullptr) {
        vagon->nombre = nuevoNombre;
    }
}

// Modificar pasajero
void modificarPasajero(Vagon* vagon, const string& nombreActual, const string& nuevoNombre, int nuevoAsiento) {
    for (auto& pasajero : vagon->pasajeros) {
        if (pasajero.nombre == nombreActual) {
            pasajero.nombre = nuevoNombre;
            pasajero.asiento = nuevoAsiento;
            break;
        }
    }
}

// Modificar Amenidad
void modificarAmenidad(Vagon* vagon, const string& nombreAmenidad, const string& nuevoNombre, int nuevaCantidad) {
    for (auto& amenidad : vagon->amenidades) {
        if (amenidad.nombre == nombreAmenidad) {
            amenidad.nombre = nuevoNombre;
            amenidad.cantidad = nuevaCantidad;
            break;
        }
    }
}

//Consultas

//Amenidades
void listarAmenidades(Vagon* primero) {
    set<string> amenidadesUnicas;
    Vagon* actual = primero;
    while (actual != nullptr) {
        for (const auto& amenidad : actual->amenidades) {
            amenidadesUnicas.insert(amenidad.nombre);
        }
        actual = actual->siguiente;
    }

    cout << "Amenidades disponibles en el tren:" << endl;
    for (const auto& amenidad : amenidadesUnicas) {
        cout << "- " << amenidad << endl;
    }
}
//Total pasajeros
int contarTotalPasajeros(Vagon* primero) {
    int totalPasajeros = 0;
    Vagon* actual = primero;
    while (actual != nullptr) {
        totalPasajeros += actual->pasajeros.size();
        actual = actual->siguiente;
    }
    return totalPasajeros;
}
//Vagon con más pasajeros
string vagonConMasPasajeros(Vagon* primero) {
    if (!primero) return "No hay vagones";

    string nombreVagonConMasPasajeros = "";
    int maxPasajeros = 0;
    Vagon* actual = primero;
    while (actual != nullptr) {
        int cuentaPasajeros = actual->pasajeros.size();
        if (cuentaPasajeros > maxPasajeros) {
            maxPasajeros = cuentaPasajeros;
            nombreVagonConMasPasajeros = actual->nombre;
        }
        actual = actual->siguiente;
    }

    return nombreVagonConMasPasajeros;
}

// Función para mostrar el menú de administración de información
void mostrarMenuAdministracion(Vagon*& vagonActual) {
    int opcion;
    do {
        cout << "\nMenú de Administración de Información:" << endl;
        cout << "Vagon Actual: " << (vagonActual ? vagonActual->nombre : "Ninguno") << endl;
        cout << "1. Agregar Pasajero" << endl;
        cout << "2. Eliminar Pasajero" << endl;
        cout << "3. Mostrar Pasajeros" << endl;
        cout << "4. Agregar Amenidad" << endl;
        cout << "5. Eliminar Amenidad" << endl;
        cout << "6. Modificar Nombre del Vagon" << endl;
        cout << "7. Volver al Menu de Ingreso" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                if (vagonActual) {
                    agregarPasajero(vagonActual);
                } else {
                    cout << "No hay un vagon actual para agregar pasajeros." << endl;
                }
                break;
            }
            case 2: {
                if (vagonActual) {
                    string nombrePasajero;
                    cout << "Ingrese el nombre del pasajero a eliminar: ";
                    cin >> nombrePasajero;
                    eliminarPasajero(vagonActual, nombrePasajero);
                } else {
                    cout << "No hay un vagon actual para eliminar pasajeros." << endl;
                }
                break;
            }
            case 3: {
                if (vagonActual) {
                    mostrarPasajeros(vagonActual);
                } else {
                    cout << "No hay un vagon actual para mostrar pasajeros." << endl;
                }
                break;
            }
            case 4: {
                if (vagonActual) {
                    agregarAmenidad(vagonActual);
                } else {
                    cout << "No hay un vagon actual para agregar amenidades." << endl;
                }
                break;
            }
            case 5: {
                if (vagonActual) {
                    string nombreAmenidad;
                    cout << "Ingrese el nombre de la amenidad a eliminar: ";
                    cin >> nombreAmenidad;
                    eliminarAmenidad(vagonActual, nombreAmenidad);
                } else {
                    cout << "No hay un vagon actual para eliminar amenidades." << endl;
                }
                break;
            }
            case 6: {
                if (vagonActual) {
                    string nuevoNombreVagon;
                    cout << "Ingrese el nuevo nombre para el vagon: ";
                    cin >> nuevoNombreVagon;
                    modificarNombreVagon(vagonActual, nuevoNombreVagon);
                } else {
                    cout << "No hay un vagon actual para modificar el nombre." << endl;
                }
                break;
            }
            case 7: {
                cout << "Volviendo al Menu de Ingreso..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, seleccione una opción valida." << endl;
                break;
            }
        }
    } while (opcion != 7);
}

// Función para mostrar el menú de generación de reportes
void mostrarMenuReportes(Vagon*& vagonActual) {
    int opcion;
    do {
        cout << "\nMenu de Generacion de Reportes:" << endl;
        cout << "Vagon Actual: " << (vagonActual ? vagonActual->nombre : "Ninguno") << endl;
        cout << "1. Reporte de Amenidades Totales por Tipo" << endl;
        cout << "2. Numero Total de Pasajeros" << endl;
        cout << "3. Vagon con mas Pasajeros" << endl;
        cout << "4. Volver al Menu de Ingreso" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                listarAmenidades(vagonActual);
                break;
            }
            case 2: {
                cout << "Numero total de pasajeros: " << contarTotalPasajeros(vagonActual) << endl;
                break;
            }
            case 3: {
                cout << "Vagon con mas pasajeros: " << vagonConMasPasajeros(vagonActual) << endl;
                break;
            }
            case 4: {
                cout << "Volviendo al Menu de Ingreso..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
                break;
            }
        }
    } while (opcion != 4);
}

// Función para mostrar el menú completo de ingreso
void mostrarMenuIngreso(Vagon*& vagonActual) {
    int opcion;
    do {
        cout << "\nMenu de Ingreso:" << endl;
        cout << "1. Administracion de Informacion" << endl;
        cout << "2. Generacion de Reportes" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Si no hay vagones en la lista del tren, informar al usuario y salir
                if (!hayVagones(vagonActual)) {
                    cout << "No hay vagones en la lista del tren." << endl;
                    cout << "Debe crear el primer vagon para comenzar la gestion." << endl;
                    break;
                }
                // Mostrar el menú de administración de información
                mostrarMenuAdministracion(vagonActual);
                break;
            }
            case 2: {
                // Mostrar el menú de generación de reportes
                mostrarMenuReportes(vagonActual);
                break;
            }
            case 0: {
                cout << "Saliendo del sistema..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
                break;
            }
        }
    } while (opcion != 0);
}

int main() {
    Vagon* primerVagón = nullptr;

    // Mostrar el menú de ingreso
    mostrarMenuIngreso(primerVagón);

    return 0;
}

