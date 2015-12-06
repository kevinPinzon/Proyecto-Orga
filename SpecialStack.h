/*
SpecialStack.h
Esta clase represeta una pila pero se implementa con un stack(pila). Es especial porque va a tener unos metodos especiales que 
me van a hacer muy especial la nota de este proyecto :D . 
El metodo mas especial es el que indica cuantos espacios hay en el availlist antess de la posicion i que se escoje al listar 
los registros cuando el usuario escoje uno. 
*/
#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std; 

class SpecialStack{
		vector <int> availlist;
		/*
		todas las posiciones que metemos al availlist son en base a i del vector
		osea que empiezan desde 0, y llegan hasta size -1
		*/

	public: 
		SpecialStack();
		SpecialStack(int);

		string toString();
		int pop();
		void push(int);
		int peek();
		int posicionesAntesDe(int);
		bool isEmpty();
		void inicializar(ifstream&, int, int);
		/*parametros de inicializar	: 
		ifstream& file, int pos(que toma del header), int offsetRegistros, int sizeRegistro(es el tamaño del registro fijo ARLF) 
		*/
		int siguientePosicionDisponible(string);
		int cadena2Int(string);

};// fin clase SpecialStack
