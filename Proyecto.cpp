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
    Amenidad* siguiente;
};

// Definición de la estructura de un vagón
struct Vagon {

    string nombre;
    list<Pasajero> pasajeros;
    Amenidad* primerAmenidad;
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
    cout << "Ingrese el nombre del pasajero: " << endl;
    getline(cin, nuevoPasajero.nombre);
    cout << "Ingrese el numero de asiento del pasajero: "<< endl;
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
     Amenidad* nuevaAmenidad = new Amenidad();
    if (vagon->primerAmenidad == nullptr) {
        vagon->primerAmenidad = nuevaAmenidad;
        nuevaAmenidad->siguiente = nuevaAmenidad;
}else {
    Amenidad* ultimoAmenidad = vagon->primerAmenidad;
        while (ultimoAmenidad->siguiente != vagon->primerAmenidad) {
            ultimoAmenidad = ultimoAmenidad->siguiente;
        }
        nuevaAmenidad->siguiente = vagon->primerAmenidad;
        ultimoAmenidad->siguiente = nuevaAmenidad;
    }
}
// Eliminar amenidad
void eliminarAmenidad(Vagon* vagon, const string& nombreAmenidad) {
    if (vagon->primerAmenidad == nullptr) {
        return;
    }

    Amenidad* anterior = nullptr;
    Amenidad* actual = vagon->primerAmenidad;
    // Buscar la amenidad por nombre
    while (actual->nombre != nombreAmenidad) {
        // Si se alcanza el primer nodo de nuevo, se ha recorrido toda la lista circular
        if (actual->siguiente == vagon->primerAmenidad) {
            cout << "La amenidad especificada no se encontró." << endl;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    // Eliminar el nodo de amenidad
    if (actual == vagon->primerAmenidad) {
        vagon->primerAmenidad = actual->siguiente;
    }
    if (anterior != nullptr) {
        anterior->siguiente = actual->siguiente;
    }
    delete actual; 
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
    // Si la lista de amenidades está vacía, salir
    if (vagon->primerAmenidad == nullptr) {
        cout << "No hay amenidades en este vagón." << endl;
        return;
    }

    Amenidad* actual = vagon->primerAmenidad;
    // Buscar la amenidad por nombre
    do {
        if (actual->nombre == nombreAmenidad) {
            // Modificar el nombre y la cantidad de la amenidad
            actual->nombre = nuevoNombre;
            actual->cantidad = nuevaCantidad;
            cout << "Amenidad modificada exitosamente." << endl;
            return;
        }
        actual = actual->siguiente;
    } while (actual != vagon->primerAmenidad);
    cout << "La amenidad especificada no se encontró." << endl;
}


//Consultas

//Amenidades
void listarAmenidades(Vagon* primero) {
    // Si no hay vagones en la lista del tren, informar al usuario y salir
    if (primero == nullptr) {
        cout << "No hay vagones en la lista del tren." << endl;
        return;
    }

    cout << "Amenidades disponibles en el tren:" << endl;
    Vagon* actual = primero;
    do {
        // Si el vagón actual tiene amenidades, mostrarlas
        if (actual->primerAmenidad != nullptr) {
            Amenidad* amenidadActual = actual->primerAmenidad;
            do {
                cout << "- " << amenidadActual->nombre << endl;
                amenidadActual = amenidadActual->siguiente;
            } while (amenidadActual != actual->primerAmenidad);
        }
        actual = actual->siguiente;
    } while (actual != primero);
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
        cout << "\nMenu de Administracion de Informacion:" << endl;
        cout << "Vagon Actual: " << (vagonActual ? vagonActual->nombre : "Ninguno") << endl;
        cout << "1. Agregar Vagon" << endl;
        cout << "2. Agregar Pasajero" << endl;
        cout << "3. Eliminar Pasajero" << endl;
        cout << "4. Mostrar Pasajeros" << endl;
        cout << "5. Agregar Amenidad" << endl;
        cout << "6. Eliminar Amenidad" << endl;
        cout << "7. Modificar Nombre del Vagon" << endl;
        cout << "8. Volver al Menu de Ingreso" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombreNuevoVagon;
                cout << "Ingrese el nombre del nuevo vagon: ";
                cin >> nombreNuevoVagon;
                agregarVagon(vagonActual, vagonActual, nombreNuevoVagon);
                cout << "Nuevo vagon agregado con exito." << endl;
                break;
            }
            case 2: {
                if (vagonActual) {
                    agregarPasajero(vagonActual);
                } else {
                    cout << "No hay un vagon actual para agregar pasajeros." << endl;
                }
                break;
            }
            case 3: {
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
            case 4: {
                if (vagonActual) {
                    mostrarPasajeros(vagonActual);
                } else {
                    cout << "No hay un vagon actual para mostrar pasajeros." << endl;
                }
                break;
            }
            case 5: {
                if (vagonActual) {
                    agregarAmenidad(vagonActual);
                } else {
                    cout << "No hay un vagon actual para agregar amenidades." << endl;
                }
                break;
            }
            case 6: {
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
            case 7: {
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
            case 8: {
                cout << "Volviendo al Menu de Ingreso..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
                break;
            }
        }
    } while (opcion != 8);
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
                    
                }
                //Mostrar el menú de administración de información
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