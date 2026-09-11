#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include "TipoUsuario.h"
#include "Servicio.h"


class Area;
/*
La clase Tiquete se encarga de crear un tiquete con un código (código de área + consecutivo que empieza en 100), 
un tipo de usuario, ervicio y área asociados, y también se inicializa con una hora y tiene una prioridad
definida por la prioridad del tipo de usuario por 10 + la prioridad del servicio.
Tiene varios métodos getters para realizar operaciones con los datos en el menú principal.
*/
class Tiquete
{
private:
	static int consecutivo;
	string codigo;
	TipoUsuario* tipoUsuario;
	Servicio* servicio;
	Area* area;
	int horaCreacion;
	int horaAtendido;
	int horaEspera;
	int prioridadFinal;

public:
	Tiquete(TipoUsuario* tipoUsuario, Servicio* servicio, string codigoArea, int hora) {
		this->tipoUsuario = tipoUsuario;
		this->servicio = servicio;
		this->area = servicio->getArea();
		this->horaCreacion = hora;
		horaAtendido = 0;
		horaEspera = 0;
		this->codigo = codigoArea + to_string(consecutivo);
		prioridadFinal = tipoUsuario->getPrioridad() * 10 + servicio->getPrioridad();
		consecutivo++;
	}

	string getCodigo() {
		return codigo;
	}

	int getPrioridad() {
		return prioridadFinal;
	}
	
	Area* getArea() {
		return area;
	}

	TipoUsuario* getTipoUsuario() {
		return tipoUsuario;
	}

	Servicio* getServicio() {
		return servicio;
	}

	int getHora() {
		return horaCreacion;
	}

	string getHoraAtendido() {
		return convertirAStrHora(horaAtendido);
	}

	void setHoraAtendido(int hora) {
		horaAtendido = hora;
	}

	int calcularTiempoEspera() {
		horaEspera = horaAtendido - horaCreacion;
		return horaEspera;
	}

	string convertirAStrHora(int tiempoSegundos) {
		int horas = tiempoSegundos / 3600;
		int minutos = (tiempoSegundos % 3600) / 60;
		int segundos = tiempoSegundos % 60;

		stringstream ss;
		ss << setw(2) << setfill('0') << horas << ":"
			<< setw(2) << setfill('0') << minutos << ":"
			<< setw(2) << setfill('0') << segundos;

		return ss.str();
	}

	void print() {
		cout << "\nCodigo del tiquete: " << codigo;
		cout << "\nHora: " << convertirAStrHora(horaCreacion);
		cout << "\nPrioridad " << prioridadFinal << endl;
	}
};

int Tiquete::consecutivo = 100;