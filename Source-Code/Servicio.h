#pragma once
#include <string>
#include <iostream>

using namespace std;
/*
La clase Servicio se encargar de inicializar un servicio con su descripción y prioridad, además 
de asociarlo con el área en la que se atiende, también tiene un contador tiquetesSolicitados para llevar
la cuenta de la cantidad de tiquetes que han sido solicitados para el servicio.
Tiene distintos métodos getters que permiten extraer y utilizar los datos además de métodos 
para modificar la prioridad y área del servicio. Tiene otros métodos que sirven para aumentar,
 reinicializar u obtener el número de tiquetes solicitados para el servicio.
*/
class Area;

class Servicio
{
private:
    string descripcion;
    Area* area;
    int prioridad;
    int tiquetesSolicitados;

public:
    Servicio(string descripcion, Area* area, int prioridad) {
        this->descripcion = descripcion;
        this->area = area;
        this->prioridad = prioridad;
        tiquetesSolicitados = 0;
    }

    string getDescripcion() {
        return descripcion;
    }

    void setDescripcion(string descripcion) {
        this->descripcion = descripcion;
    }

    Area* getArea() {
        return area;
    }

    void setArea(Area* area) {
        this->area = area;
    }

    int getPrioridad() {
        return prioridad;
    }

    void setPrioridad(int prioridad) {
        this->prioridad = prioridad;
    }

    void aumentarTiquetesSolicitados() {
        tiquetesSolicitados++;
    }

    void resetTiquetesSolicitados() {
        tiquetesSolicitados = 0;
    }

    int getNumTiquetesSolicitados() {
        return tiquetesSolicitados;
    }

    void print() {
        cout << descripcion << endl;
        //cout << "Prioridad: " << prioridad << endl;
    }
};

