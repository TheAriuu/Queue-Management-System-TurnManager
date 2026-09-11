#pragma once
#include <string>

using namespace std;
/*
La clase TipoUsuario es la más sencilla y se encarga de inicializar un tipo de usuario con su
descripción, prioridad y contador de tiquetes emitidos, tiene métodos para obtener los datos, 
(la descripción, la prioridad y la cantidad de tiquetes emitidos para el tipo de usuario) y
así permitir el uso de estos.
Tiene otros métodos para aumentar la cantidad de tiquetes emitidos o reinicializarla.
*/
class TipoUsuario
{
private:
	string descripcion;
	int prioridad;
	int tiquetesEmitidos;

public:
	TipoUsuario(string descripcion, int prioridad) {
		this->descripcion = descripcion;
		this->prioridad = prioridad;
		tiquetesEmitidos = 0;
	}

	string getDescripcion() {
		return descripcion;
	}

	int getPrioridad() {
		return prioridad;
	}

	int getNumTiquetesEmitidos() {
		return tiquetesEmitidos;
	}

	void aumentarTiquetesEmitidos() {
		tiquetesEmitidos++;
	}

	void resetTiquetesEmitidos() {
		tiquetesEmitidos = 0;
	}

	void print() {
		cout << descripcion << endl;
		//cout << "Prioridad: " << prioridad << endl;
	}
};