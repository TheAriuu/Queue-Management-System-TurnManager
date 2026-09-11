#pragma once
#include <string>
#include "Area.h"

using namespace std;
/*
La clase Ventanilla se encarga de inicializar ventanillas con un nombre (código de área + un consecutivo) y de 
llevar el control de que tiquete se está atendiendo. También tiene un atributo para saber la cantidad
de tiquetes que han sido atendidos en la ventanilla. Tiene métodos getters para obtener distintos datos 
y así ser utilizados en el menú principal además de un método para establecer que tiquete se está atendiendo.
También tiene métodos para resetear el consecutivo y devolverlo a 0 cada vez que se crean ventanillas en una
nueva área. Otro para reinicializar la cantidad de tiquetes atendidos en la ventanilla y otro para borrar el
tiquete actual.
*/
class Ventanilla {
private:
    static int consecutivo;
    int tiquetesAtendidos;
    string nombre;
    string codigoTiqueteActual;

public:
    Ventanilla(string codigo) {
        tiquetesAtendidos = 0;
        this->nombre = codigo + to_string(consecutivo);
        codigoTiqueteActual = "";
        consecutivo = consecutivo++;
    }
    
    static void resetConsecutivo() {
        consecutivo = 1;
    }

    void resetTiquetesAtendidos() {
        tiquetesAtendidos = 0;
    }
    
    void atenderTiquete(string codigoTiquete) {
        codigoTiqueteActual = codigoTiquete;
        tiquetesAtendidos++;
    }

    int getNumTiquetesAtendidos() {
        return tiquetesAtendidos;
    }

    string getNombre() {
        return nombre;
    }

    string getCodigoTiqueteActual() {
        return codigoTiqueteActual;
    }

    void borrarTiqueteActual() {
        codigoTiqueteActual = "";
    }

    void print() {
        cout << "\nVentanilla: " + nombre << endl;
        cout << "Tiquete actual: " + codigoTiqueteActual << endl;
    }
};

int Ventanilla::consecutivo = 1;