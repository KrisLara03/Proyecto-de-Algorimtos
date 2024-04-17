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
//Función para agregar una amenidad a un vagón
//Agregar amenidad
void agregarAmenidad(Vagon* vagon) {
    Amenidad* nuevaAmenidad = new Amenidad; // Crear una nueva amenidad
    cout << "Ingrese el nombre de la amenidad: ";
    cin.ignore(); // Limpiar el buffer de entrada antes de getline()
    getline(cin, nuevaAmenidad->nombre); // Leer la línea completa
    cout << "Ingrese la cantidad de la amenidad: ";
    cin >> nuevaAmenidad->cantidad;

    // Limpiar el buffer de entrada después de leer el entero
    cin.ignore();

    // Agregar la nueva amenidad al vagón
    if (vagon->primerAmenidad == nullptr) {
        vagon->primerAmenidad = nuevaAmenidad;
        nuevaAmenidad->siguiente = nullptr;
    } else {
        Amenidad* ultimaAmenidad = vagon->primerAmenidad;
        while (ultimaAmenidad->siguiente != nullptr) {
            ultimaAmenidad = ultimaAmenidad->siguiente;
        }
        ultimaAmenidad->siguiente = nuevaAmenidad;
        nuevaAmenidad->siguiente = nullptr;
    }

    cout << "Amenidad agregada con exito al vagon " << vagon->nombre << ".\n";
    return;
}

//Eliminar amenidad
void eliminarAmenidad(Vagon* vagon, const string& nombreAmenidad) {
    if (vagon->primerAmenidad == nullptr) {
        cout << "No hay amenidades en este vagon." << endl;
        return;
    }

    Amenidad* anterior = nullptr;
    Amenidad* actual = vagon->primerAmenidad;
    // Buscar la amenidad por nombre
    while (actual != nullptr && actual->nombre != nombreAmenidad) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si no se encontró la amenidad
    if (actual == nullptr) {
        cout << "La amenidad especificada no se encontro." << endl;
        return;
    }

    // Eliminar la amenidad
    if (anterior == nullptr) {
        vagon->primerAmenidad = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    delete actual;

    cout << "Amenidad eliminada con exito." << endl;
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
        cout << "No hay amenidades en este vagon." << endl;
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
    cout << "La amenidad especificada no se encontro." << endl;
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
// Distribución de pasajeros
void distribucionPasajerosPorVagon(Vagon* primero) {
    Vagon* actual = primero;
    int totalPasajeros = 0; // Variable para almacenar el total de pasajeros

    if (actual == nullptr) {
        cout << "No hay vagones en el tren.\n";
    } else {
        cout << "Reporte de distribucion de pasajeros:\n";
        do {
            int numPasajeros = actual->pasajeros.size(); // Obtenemos la cantidad de pasajeros en el vagón actual
            cout << "Vagon " << actual->nombre << ": " << numPasajeros << " pasajeros\n";
            totalPasajeros += numPasajeros; // Sumamos al total de pasajeros
            actual = actual->siguiente;
        } while (actual != primero); 

        // Mostramos el total de pasajeros en el tren
        cout << "Total de pasajeros en el Tren: " << totalPasajeros << "\n";
    }
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
        cout << "6. Modificar Amenidad" << endl;
        cout << "7. Mostrar Amenidades" << endl;
        cout << "8. Eliminar Amenidad" << endl;
        cout << "9. Modificar Nombre del Vagon" << endl;
        cout << "10. Volver al Menu de Ingreso" << endl;
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
                    continue;
                } else {
                    cout << "No hay un vagon actual para agregar amenidades." << endl;
                }
                break;
            }
            case 6: {
                if (vagonActual) {
                    string nombreAmenidad;
                    cout << "Ingrese el nombre de la amenidad a modificar: ";
                    cin >> nombreAmenidad;
                    modificarAmenidad(vagonActual, nombreAmenidad);
                } else {
                    cout << "No hay un vagon actual para modificar amenidades." << endl;
                }
                break;
            }
             case 7: {
                if (vagonActual) {
                    listarAmenidades(vagonActual);
                } else {
                    cout << "No hay un vagon actual para mostrar amenidades." << endl;
                }
                break;
            }
            case 8: {
                if (vagonActual) {
                    string nombreAmenidad;
                    cout << "Ingrese el nombre de la amenidad a eliminar: ";
                    cin >> nombreAmenidad;
                    eliminarAmenidad(vagonActual, nombreAmenidad);
                    continue;
                } else {
                    cout << "No hay un vagon actual para eliminar amenidades." << endl;
                }
                break;
            }
            case 9: {
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
            case 10: {
                cout << "Volviendo al Menu de Ingreso..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
                break;
            }
        }
    } while (opcion != 10);
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
        cout << "4. Distribucion de Pasajeros por Vagon" << endl; 
        cout << "5. Volver al Menu de Ingreso" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
    listarAmenidades(primerVagon); // Listar todas las amenidades disponibles en el tren
    cout << "Seleccione una amenidad para obtener el total en todos los vagones: ";
    string nombreAmenidad;
    cin >> nombreAmenidad;

    int totalAmenidad = 0;
    Vagon* actual = primerVagon;
    do {
        Amenidad* amenidadActual = actual->primerAmenidad;
        while (amenidadActual != nullptr) {
            if (amenidadActual->nombre == nombreAmenidad) {
                totalAmenidad += amenidadActual->cantidad;
            }
            amenidadActual = amenidadActual->siguiente;
        }
        actual = actual->siguiente;
    } while (actual != primerVagon);

    cout << "Calculando total de " << nombreAmenidad << " en todos los vagones..." << endl;
    cout << "Reporte de " << nombreAmenidad << ":" << endl;
    actual = primerVagon;
    do {
        Amenidad* amenidadActual = actual->primerAmenidad;
        while (amenidadActual != nullptr) {
            if (amenidadActual->nombre == nombreAmenidad) {
                cout << "Vagon " << actual->nombre << ": " << amenidadActual->cantidad << " " << nombreAmenidad << endl;
            }
              amenidadActual = amenidadActual->siguiente;
            }
              actual = actual->siguiente;
    } while (actual != primerVagon);

                cout << "Total de " << nombreAmenidad << " en el Tren: " << totalAmenidad << endl;
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
                distribucionPasajerosPorVagon(vagonActual);   
                break;
            }
             case 5: {
                cout << "Volviendo al Menu de Ingreso..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
                break;
            }
        }
    } while (opcion != 5);
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
    Vagon* primerVagon = nullptr;

    // Mostrar el menú de ingreso
    mostrarMenuIngreso(primerVagon);

    return 0;
}

