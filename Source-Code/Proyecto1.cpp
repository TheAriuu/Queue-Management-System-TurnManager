#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>
#include "HeapPriorityQueue.h"
#include "Area.h"
#include "Servicio.h"

using namespace std;
ArrayList<TipoUsuario*> listaTiposUsuario(50);
ArrayList<Servicio*> listaServicios(50);
ArrayList<Area*> listaAreas(100);

void mostrarListaTiposUsuario() {
    cout << "\nTipos de usuario: " << endl;
    int i = 0;
    for (listaTiposUsuario.goToStart(); !listaTiposUsuario.atEnd(); listaTiposUsuario.next()) {
        TipoUsuario* t = listaTiposUsuario.getElement();
        cout << i << ". ";
        t->print();
        i++;
    }
}

void mostrarListaServicios() {
    cout << "\nLista de servicios: " << endl;
    int i = 0;
    for (listaServicios.goToStart(); !listaServicios.atEnd(); listaServicios.next()) {
        Servicio* s = listaServicios.getElement();
        cout << i << ". ";
        s->print();
        i++;
    }
}

void mostrarListaAreas() {
    cout << "\nLista de areas: " << endl;
    int i = 0;
    for (listaAreas.goToStart(); !listaAreas.atEnd(); listaAreas.next()) {
        Area* a = listaAreas.getElement();
        cout << i << ". ";
        a->print();
        i++;

        ArrayList<Tiquete*>* listaTiquetes = a->getListaTiquetes();
        cout << "\nCola de tiquetes: [";
        for (listaTiquetes->goToStart(); !listaTiquetes->atEnd(); listaTiquetes->next()) {
            Tiquete* t = listaTiquetes->getElement();
            cout << t->getCodigo() << ", ";
        }
        cout << "]\n" << endl;
    }
}

int obtenerHoraActual() {
    time_t now = time(0);
    tm local_time;
    localtime_s(&local_time, &now);
    int hour = local_time.tm_hour;
    int minute = local_time.tm_min;
    int second = local_time.tm_sec;
    return hour * 3600 + minute * 60 + second;
}

void cargarDatos() {
    TipoUsuario* t1 = new TipoUsuario("Adulto Mayor", 1);
    TipoUsuario* t2 = new TipoUsuario("Discapacitado", 1);
    TipoUsuario* t3 = new TipoUsuario("Menor de edad", 2);
    TipoUsuario* t4 = new TipoUsuario("Adulto joven", 3);
    listaTiposUsuario.append(t1);
    listaTiposUsuario.append(t2);
    listaTiposUsuario.append(t3);
    listaTiposUsuario.append(t4);

    Area* a1 = new Area("Servicio al cliente", "SC", 4);
    Area* a2 = new Area("Banca", "B", 3);
    listaAreas.append(a1);
    listaAreas.append(a2);

    Servicio* s1 = new Servicio("Reclamos", a1, 4);
    Servicio* s2 = new Servicio("Dudas", a1, 3);
    Servicio* s3 = new Servicio("Pago de facturas", a2, 2);
    Servicio* s4 = new Servicio("Retiro de tarjetas", a2, 1); 
    listaServicios.append(s1);
    listaServicios.append(s2);
    listaServicios.append(s3);
    listaServicios.append(s4);
}

void estadoColas() {
    mostrarListaAreas();
    cout << "\nPresione 1 para regresar al menu principal." << endl;
    string opcion;
    getline(cin,opcion);
    while (opcion != "1") {
        cout << "Opcion invalida, ingrese 1 para regresar al menu principal." << endl;
        getline(cin,opcion);
    }
    return;
}

void crearTiquete() {
    string opcion;
    while (opcion != "2") {
        try {
            cout << "\n1. Seleccionar tipo de cliente y servicio";
            cout << "\n2. Regresar" << endl;
            getline(cin, opcion);

            if (opcion == "1") {
                mostrarListaTiposUsuario();
                cout << "\nEscoga el tipo de usuario que es, digitanto el numero correspondiente: ";
                string tipoDeUsuario;
                getline(cin, tipoDeUsuario);
                listaTiposUsuario.goToPos(stoi(tipoDeUsuario));
                TipoUsuario* t = listaTiposUsuario.getElement();

                mostrarListaServicios();
                cout << "\nEscoga el servicio: ";
                string servicio;
                getline(cin, servicio);
                listaServicios.goToPos(stoi(servicio));
                Servicio* s = listaServicios.getElement();

                Area* a = s->getArea();
                Tiquete* tiquete = new Tiquete(t, s, a->getCodigo(), obtenerHoraActual());
                s->aumentarTiquetesSolicitados();
                t->aumentarTiquetesEmitidos();
                cout << "\nNuevo tiquete: ";
                tiquete->print();
                a->agregarTiquete(tiquete);
            }
            else if (opcion != "2") {
                cout << "Opcion invalida." << endl;
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void atender() {
    try {
        mostrarListaAreas();
        string numArea;
        string numVentanilla;
        cout << "Ingrese el numero de area: ";
        getline(cin, numArea);
        cout << "Ingrese el numero de ventanilla: ";
        getline(cin, numVentanilla);
        // obtengo el área
        listaAreas.goToPos(stoi(numArea));
        Area* a = listaAreas.getElement();
        // obtengo la ventanilla
        ArrayList<Ventanilla*>* listaVentanillas = a->getVentanillas();
        listaVentanillas->goToPos(stoi(numVentanilla) - 1);
        Ventanilla* v = listaVentanillas->getElement();
        //obtengo el próximo tiquete a atender
        HeapPriorityQueue<Tiquete*>* colaTiquetes = a->getColaTiquetes();
        if (colaTiquetes->isEmpty()) {
            cout << "No hay tiquetes por atender" << endl;
        }
        else {
            Tiquete* t = a->eliminarTiquete();
            v->atenderTiquete(t->getCodigo());
            t->setHoraAtendido(obtenerHoraActual());
            a->agregarTiqueteAtendido(t);
            cout << "Tiquete: " << t->getCodigo() << " atendido a las " << t->getHoraAtendido() << endl;
            //cout << "Tiempo de espera: " << t->calcularTiempoEspera() << endl;
        }
    } catch (exception e) {
        cout << "Error: " << e.what() << endl;
    }
}

void adminisitrarTiposUsuario() {
    string opcion;
    bool regresar = false;
    while (!regresar) {
        try {
            cout << "\n1. Agregar" << endl;
            cout << "2. Eliminar" << endl;
            cout << "3. Regresar" << endl;
            cout << "\nIngrese la opcion que desea realizar: ";
            getline(cin, opcion);
            if (opcion == "1") {
                string nombre;
                cout << "Ingrese el nombre del nuevo tipo de usuario: ";
                getline(cin, nombre);
                string prioridad;
                cout << "Ingrese la prioridad: ";
                getline(cin, prioridad);
                TipoUsuario* t = new TipoUsuario(nombre, stoi(prioridad));
                listaTiposUsuario.append(t);
                cout << "\nTipo de usuario agregado exitosamente" << endl;
            }
            else if (opcion == "2") {
                string tipoUsuarioABorrar;
                mostrarListaTiposUsuario();
                cout << "\nIngrese el numero de usuario que desea borrar: ";
                getline(cin, tipoUsuarioABorrar);
                string opcionBorrar;
                cout << "De verdad quiere borrar el tipo de usuario: " << tipoUsuarioABorrar << "?\n";
                cout << "Esto implica borrar los tiquetes relacionadas al tipo de usuario." << endl;
                cout << "Ingrese un 1 para confirmar o un 2 para cancelar" << endl;
                getline(cin, opcionBorrar);
                if (opcionBorrar == "1") {
                    listaTiposUsuario.goToPos(stoi(tipoUsuarioABorrar));
                    delete listaTiposUsuario.remove();
                    cout << "\nTipo de usuario " << tipoUsuarioABorrar << " eliminado exitosamente." << endl;
                }
                else if (opcionBorrar == "2") {
                    cout << "Accion cancelada" << endl;
                }
                else {
                    cout << "\nOpcion invalida." << endl;
                }
            }
            else if (opcion == "3") {
                regresar = true;
            }
            else {
                cout << "\nOpcion invalida." << endl;
            }
        } catch (exception e) {
            cout << "Error: " << e.what() << endl;
        } 
    }
}

void administrarAreas() {
    string opcion;
    bool regresar = false;
    while (!regresar) {
        try {
            cout << "\n1. Agregar" << endl;
            cout << "2. Modificar cantidad de ventanillas" << endl;
            cout << "3. Eliminar" << endl;
            cout << "4. Regresar" << endl;
            cout << "\nIngrese la opcion que desea realizar: ";
            getline(cin, opcion);
            if (opcion == "1") {
                string descripcion;
                string codigo;
                string cantidadVentanillas;
                cout << "\nIngrese la descripcion del area: ";
                getline(cin, descripcion);
                cout << "Ingrese el codigo del area: ";
                getline(cin, codigo);
                cout << "Ingrese la cantidad de ventanillas: ";
                getline(cin, cantidadVentanillas);
                Area* nuevaArea = new Area(descripcion, codigo, stoi(cantidadVentanillas));
                listaAreas.append(nuevaArea);
                cout << "\nArea nueva creada exitosamente." << endl;
            }
            else if (opcion == "2") {
                mostrarListaAreas();
                string numArea;
                string numVentanillas;
                cout << "\nIngrese el numero de area: ";
                getline(cin, numArea);
                listaAreas.goToPos(stoi(numArea));
                Area* area = listaAreas.getElement();
                cout << "Cantidad actual de ventanillas: " << area->getCantidadVentanillas() << endl;
                cout << "\nIngrese el nuevo numero de ventanillas: ";
                getline(cin, numVentanillas);
                area->eliminarVentanillas();
                area->modificarCantVentanillas(stoi(numVentanillas));
                cout << "Cantidad de ventanillas modificada exitosamente" << endl;
            }
            else if (opcion == "3") {
                mostrarListaAreas();
                string numArea;
                cout << "\nIngrese el numero de area que desea eliminar: ";
                getline(cin, numArea);
                string opcionBorrar;
                cout << "De verdad quiere borrar el area: " << numArea << "?\n";
                cout << "Esto implica borrar los servicios y ventanillas relacionadas al area." << endl;
                cout << "Ingrese un 1 para confirmar o un 2 para cancelar" << endl;
                getline(cin, opcionBorrar);
                if (opcionBorrar == "1") {
                    listaAreas.goToPos(stoi(numArea));
                    Area* areaAEliminar = listaAreas.getElement();
                    areaAEliminar->eliminarVentanillas();
                    ArrayList<Servicio*>* serviciosArea = areaAEliminar->getServicios();
                    for (listaServicios.goToStart(); !listaServicios.atEnd(); listaServicios.next()) {
                        Servicio* s = listaServicios.getElement();
                        if (s->getArea() == areaAEliminar) {
                            listaServicios.remove(); //al agregar delete da error.
                            listaServicios.goToStart();
                        }
                    }
                    areaAEliminar->eliminarServicios();
                    delete listaAreas.remove();
                    cout << "\nArea " << numArea << " eliminada exitosamente." << endl;
                }
                else if (opcionBorrar == "2") {
                    cout << "Accion cancelada" << endl;
                }
                else {
                    cout << "\nOpcion invalida." << endl;
                }
            }
            else if (opcion == "4") {
                regresar = true;
            }
            else {
                cout << "\nOpcion invalida." << endl;
            }
        } catch (exception e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void administrarServicios() {
    string opcion;
    bool regresar = false;
    while (!regresar) {
        try {
            cout << "\n1. Agregar" << endl;
            cout << "2. Eliminar" << endl;
            cout << "3. Reordenar" << endl;
            cout << "4. Regresar" << endl;
            cout << "\nIngrese la opcion que desea realizar: ";
            getline(cin, opcion);
            if (opcion == "1") {
                mostrarListaAreas();
                string numArea;
                string descripcion;
                string prioridad;
                cout << "\nIngrese el numero de area a la que desea agregar el sevicio: ";
                getline(cin, numArea);
                listaAreas.goToPos(stoi(numArea));
                Area* area = listaAreas.getElement();
                cout << "\nIngrese la descripcion del servicio: ";
                getline(cin, descripcion);
                cout << "\nIngrese la prioridad del servicio: ";
                getline(cin, prioridad);
                Servicio* nuevoServicio = new Servicio(descripcion, area, stoi(prioridad));
                listaServicios.append(nuevoServicio);
                cout << "Nuevo servicio creado exitosamente." << endl;
            }
            else if (opcion == "2") {
                mostrarListaServicios();
                string numServicio;
                cout << "\nIngrese el numero de servicio: ";
                getline(cin, numServicio);
                string opcionBorrar;
                cout << "De verdad quiere borrar el servicio: " << opcionBorrar << "?\n";
                cout << "Esto implica borrar los tiquetes relacionadas al servicio." << endl;
                cout << "Ingrese un 1 para confirmar o un 2 para cancelar" << endl;
                getline(cin, opcionBorrar);
                if (opcionBorrar == "1") {
                    listaServicios.goToPos(stoi(numServicio));
                    delete listaServicios.remove(); 
                    cout << "Servicio eliminado exitosamente." << endl;
                }
                else if (opcionBorrar == "2") {
                    cout << "Accion cancelada" << endl;
                }
                else {
                    cout << "\nOpcion invalida." << endl;
                }
            }
            else if (opcion == "3") {
                mostrarListaServicios();
                string numServicio;
                string posDestino;
                cout << "\nIngrese el numero de servicio a reubicar: ";
                getline(cin, numServicio);
                cout << "\nIngrese la posicion de destino: ";
                getline(cin, posDestino);
                listaServicios.goToPos(stoi(numServicio));
                Servicio* s = listaServicios.remove();
                listaServicios.goToPos(stoi(posDestino));
                listaServicios.insert(s);
                cout << "Servicio reubicado exitosamente." << endl;
            }
            else if (opcion == "4") {
                regresar = true;
            }
            else {
                cout << "\nOpcion invalida." << endl;
            }
        } catch (exception e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void limpiarColasEstadisticas() {
    for (listaAreas.goToStart(); !listaAreas.atEnd(); listaAreas.next()) {
        Area* area = listaAreas.getElement();
        ArrayList<Tiquete*>* listaTiquetes = area->getListaTiquetesAtendidos();
        for (listaTiquetes->goToStart(); !listaTiquetes->atEnd(); listaTiquetes->next())
            delete listaTiquetes->remove();
        listaTiquetes->clear();
    }
    cout << "Tiempos de espera reseteados." << endl;
    for (listaAreas.goToStart(); !listaAreas.atEnd(); listaAreas.next()) {
        Area* area = listaAreas.getElement();
        area->resetColas();
        area->resetTiquetesDispensados();
        ArrayList<Ventanilla*>* listaVentanillas = area->getVentanillas();
        for (listaVentanillas->goToStart(); !listaVentanillas->atEnd(); listaVentanillas->next()) {
            Ventanilla* v = listaVentanillas->getElement();
            v->resetTiquetesAtendidos();
            v->borrarTiqueteActual();
        }
    }
    cout << "Cola de tiquetes reseteada." << endl;
    cout << "Conteo de tiquetes dispensados por area reseteado." << endl;
    cout << "Tiquetes actuales de cada ventanilla reseteados." << endl;
    cout << "Conteo de tiquetes atendidos por ventanilla reseteado." << endl;
    for (listaServicios.goToStart(); !listaServicios.atEnd(); listaServicios.next()) {
        Servicio* s = listaServicios.getElement();
        s->resetTiquetesSolicitados();
    }
    cout << "Conteo de tiquetes solicitados por servicio reseteado." << endl;
    for (listaTiposUsuario.goToStart(); !listaTiposUsuario.atEnd(); listaTiposUsuario.next()) {
        TipoUsuario* t = listaTiposUsuario.getElement();
        t->resetTiquetesEmitidos();
    }
    cout << "Conteo de tiquetes emitidos por tipo de usuario reseteado." << endl;
}

void administracion() {
    string opcion;
    bool regresar = false;
    while (!regresar) {
        cout << "\n1. Tipos de usuario" << endl;
        cout << "2. Areas" << endl;
        cout << "3. Servicios disponibles" << endl;
        cout << "4. Limpiar colas y estadisticas" << endl;
        cout << "5. Regresar" << endl;
        cout << "\nIngrese una opcion: ";
        getline(cin,opcion);
        if (opcion == "1") {
            adminisitrarTiposUsuario();
        }
        else if (opcion == "2") {
            administrarAreas();
        }
        else if (opcion == "3") {
            administrarServicios();
        }
        else if (opcion == "4") {
            limpiarColasEstadisticas();
        }
        else if (opcion == "5") {
            regresar = true;
        }
        else {
            cout << "\nOpcion invalida." << endl;
        }
    }
}

void estadisticasSistema() {
    cout << "\nTIEMPO PROMEDIO DE ESPERA POR CADA AREA: ";
    for (listaAreas.goToStart(); !listaAreas.atEnd(); listaAreas.next()) {
        Area* area = listaAreas.getElement();
        ArrayList<Tiquete*>* listaTiquetes = area->getListaTiquetesAtendidos();
        int conteoTiempoEspera = 0;
        int cantidadTiquetes = listaTiquetes->getSize();
        for (listaTiquetes->goToStart(); !listaTiquetes->atEnd(); listaTiquetes->next()) {
            Tiquete* t = listaTiquetes->getElement();
            conteoTiempoEspera += t->calcularTiempoEspera();
        }
        int promedioTiempoEspera = cantidadTiquetes > 0 ? (conteoTiempoEspera / cantidadTiquetes) : 0;
        cout << "\nArea: " << area->getDescripcion() << ", Promedio de tiempo de espera: " << promedioTiempoEspera;
    }
    cout << "\n\nCANTIDAD DE TIQUETES DISPENSADOS POR AREA: ";
    for (listaAreas.goToStart(); !listaAreas.atEnd(); listaAreas.next()) {
        Area* area = listaAreas.getElement();
        cout << "\nCantidad de tiquetes dispensados por el area " << listaAreas.getPos() << ": " << area->getNumTiquetesDispensados();
    }
    cout << "\n\nCANTIDAD DE TIQUETES ATENDIDOS POR VENTANILLA: ";
    for (listaAreas.goToStart(); !listaAreas.atEnd(); listaAreas.next()) {
        Area* area = listaAreas.getElement();
        cout << "\n\nArea: " << area->getDescripcion();
        ArrayList<Ventanilla*>* listaVentanillas = area->getVentanillas();
        for (listaVentanillas->goToStart(); !listaVentanillas->atEnd(); listaVentanillas->next()) {
            Ventanilla* v = listaVentanillas->getElement();
            cout << "\nTiquetes atendidos por la ventanilla " << v->getNombre() << ": " << v->getNumTiquetesAtendidos();
            //delete listaVentanillas;
        }
    }
    cout << "\n\nCANTIDAD DE TIQUETES SOLICITADOS POR SERVICIO: ";
    for (listaServicios.goToStart(); !listaServicios.atEnd(); listaServicios.next()) {
        Servicio* s = listaServicios.getElement();
        cout << "\nCantidad de tiquetes solicitados para el servicio " << s->getDescripcion() << ": " << s->getNumTiquetesSolicitados();
    }
    cout << "\n\nCANTIDAD DE TIQUETES SOLICITADOS POR TIPO DE USUARIO: ";
    for (listaTiposUsuario.goToStart(); !listaTiposUsuario.atEnd(); listaTiposUsuario.next()) {
        TipoUsuario* t = listaTiposUsuario.getElement();
        cout << "\nCantidad de tiquetes solicitados para el tipo de usuario " << t->getDescripcion() << ": " << t->getNumTiquetesEmitidos();
    }
    cout << "\n\nPresione 1 para regresar al menu principal." << endl;
    string opcion;
    getline(cin, opcion);
    while (opcion != "1") {
        cout << "Opcion invalida, ingrese 1 para regresar al menu principal." << endl;
        getline(cin, opcion);
    }
    return;
}

void mostrarMenuPrincipal() {
    cout << "\nMenu Principal" << endl;
    cout << "1. Ver estado de las colas" << endl;
    cout << "2. Crear tiquete" << endl;
    cout << "3. Atender" << endl;
    cout << "4. Administracion" << endl;
    cout << "5. Estadisticas del sistema" << endl;
    cout << "6. Salir" << endl;
}


void menuPrincipal() {
    //cargarDatos();
    string opcion;
    bool salir = false;
    while (!salir) {
        mostrarMenuPrincipal();
        cout << "\nIngrese una opcion: ";
        getline(cin,opcion);
        if (opcion == "1") {
            estadoColas();
        }
        else if (opcion == "2") {
            crearTiquete();
        }
        else if (opcion == "3") {
            atender();
        }
        else if (opcion == "4") {
           administracion();
        }
        else if (opcion == "5") {
            estadisticasSistema();
        }
        else if (opcion == "6") {
            salir = true;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    }
}

int main() {
    menuPrincipal();
    try {
        listaTiposUsuario.goToStart();
        while (listaTiposUsuario.getSize() != 0) {
            delete listaTiposUsuario.remove();
        }
        listaServicios.goToStart();
        while (listaServicios.getSize() != 0) {
            delete listaServicios.remove();
        }
        listaAreas.goToStart(); 
        while (listaAreas.getSize() != 0) {
            delete listaAreas.remove();
        }
    }
    catch (exception e) {
        cout << "Error: " << e.what();
    }
    return 0;
}