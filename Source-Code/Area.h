#pragma once
#include <string>
#include "Ventanilla.h"
#include "Tiquete.h"
#include "Servicio.h"
#include "ArrayList.h"
#include "HeapPriorityQueue.h"

using namespace std;
/*
La clase Area se encarga de inicializar un área con su descripcion, código, cantidad de ventanillas,
y tiquetes dispensados por el área, también almacena varias listas con las ventanillas que tiene, los 
servicios que se atienden en esa área y una cola de prioridad con los tiquetes que se tienen que atender.
Además se maneja una lista paralela a la cola de tiquetes para imprimir y manejar los datos, cada vez que
una se modifica la otra también.
Tiene métodos getters para obtener los diferentes datos del área y utilizarlos en la interfaz, además cuenta
con métodos para agregar un servicios y tiquetes al área, reinicializar la cantidad de tiquetes dispensados,
modificar la cantidad de ventanillas, eliminar un tiquete, las ventanillas o servicios y finalmente un método
para reinicializar la cola de prioridad de tiquetes.
*/
class Area
{
public:
	string descripcion;
	string codigo;
	int cantidadVentanillas;
	int tiquetesDispensados;
	ArrayList<Ventanilla*>* ventanillas;
	ArrayList<Servicio*>* servicios;
	HeapPriorityQueue<Tiquete*>* tiquetes;
	ArrayList<Tiquete*>* copiaTiquetes;
	ArrayList<Tiquete*>* tiquetesAtendidos;

public:
	Area(string descripcion, string codigo, int cantidadVentanillas) {
		this->descripcion = descripcion;
		this->codigo = codigo;
		this->cantidadVentanillas = cantidadVentanillas;
		tiquetesDispensados = 0;
		ventanillas = new ArrayList<Ventanilla*>(cantidadVentanillas);
		servicios = new ArrayList<Servicio*>(100);
		tiquetes = new HeapPriorityQueue<Tiquete*>(300);
		copiaTiquetes = new ArrayList<Tiquete*>(300);
		tiquetesAtendidos = new ArrayList<Tiquete*>(300);
		Ventanilla::resetConsecutivo();
		for (int i = 0; i < cantidadVentanillas; i++) {
			Ventanilla* v = new Ventanilla(codigo);
			ventanillas->append(v);
		}
	}

	~Area() {
		delete ventanillas;
		delete servicios;
		delete tiquetes;
		delete copiaTiquetes;
		delete tiquetesAtendidos;
	}

	string getDescripcion() {
		return descripcion;
	}

	string getCodigo() {
		return codigo;
	}

	int getCantidadVentanillas() {
		return cantidadVentanillas;
	}

	int getNumTiquetesDispensados() {
		return tiquetesDispensados;
	}

	ArrayList<Ventanilla*>* getVentanillas() {
		return ventanillas;
	}

	ArrayList<Servicio*>* getServicios() {
		return servicios;
	}

	HeapPriorityQueue<Tiquete*>* getColaTiquetes() {
		return tiquetes;
	}

	ArrayList<Tiquete*>* getListaTiquetes() {
		return copiaTiquetes;
	}

	ArrayList<Tiquete*>* getListaTiquetesAtendidos() {
		return tiquetesAtendidos;
	}

	void agregarServicio(Servicio* servicio) {
		servicios->append(servicio);
	}

	void agregarTiquete(Tiquete* tiquete) {
		tiquetes->insert(tiquete, tiquete->getPrioridad());
		copiaTiquetes->append(tiquete);
		tiquetesDispensados++;
	}

	void agregarTiqueteAtendido(Tiquete* tiquete) {
		tiquetesAtendidos->append(tiquete);
	}

	void resetTiquetesDispensados() {
		tiquetesDispensados = 0;
	}

	void modificarCantVentanillas(int numVentanillas) {
		cantidadVentanillas = numVentanillas;
		Ventanilla::resetConsecutivo();
		for (int i = 0; i < numVentanillas; i++) {
			Ventanilla* v = new Ventanilla(codigo);
			ventanillas->append(v);
		}
	}

	Tiquete* eliminarTiquete() {
		Tiquete* tiqueteAEliminar = tiquetes->removeMin();
		int i = copiaTiquetes->indexOf(tiqueteAEliminar);
		copiaTiquetes->goToPos(i);
		copiaTiquetes->remove();
		return tiqueteAEliminar;
	}

	void eliminarVentanillas() {
		for (ventanillas->goToStart(); !ventanillas->atEnd(); ventanillas->next()) {
			delete ventanillas->remove();
		}
		ventanillas->clear();
	}

	void eliminarServicios() {
		servicios->clear();
	}

	void resetColas() {
		while (!tiquetes->isEmpty()) {
			delete tiquetes->removeMin();
		}
		copiaTiquetes->clear(); // no le hago delete porque necesito seguir teniendo la referencia para imprimir-
	}

	void print() {
		cout << "Area: " << descripcion << endl;
		cout << "Cantidad de ventanillas: " << cantidadVentanillas << endl;
		//cout << "Codigo de area: " << codigo << endl
		for (ventanillas->goToStart(); !ventanillas->atEnd(); ventanillas->next()) {
			Ventanilla* v = ventanillas->getElement();
			v->print();
		}
	}	

};

