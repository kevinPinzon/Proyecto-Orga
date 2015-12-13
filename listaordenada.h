#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class ListaOrdenada{
        vector <int> lista;

public:
    ListaOrdenada();
    string toString();
    void agregar(int);//recibe un valor para insertar en forma ordenada
    void eliminarValor(int);//recibe de parámetro un valor que si esta en la lista debe ser eliminado
    int buscar(int);
    bool isEmpty();

    int cantidadNumerosSeguidosDesde(int);//esta funcion regresa la cantidad de numeros sucesivos que aparecen en la lista desde el parametro
    int posicionesAntesDe(int);//esta funcion regresa cuantos numeros hay en un itervalo donde los parametros son los extremos


};

#endif // LISTAORDENADA_H
