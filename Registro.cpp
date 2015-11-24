/*
Registro.cpp
*/

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Campo.h"
#include <vector>
#include <sstream>

using std::vetor;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;

Registro::Registro(){
}

string Registro::toString()const{
	stringstream ss; 
	for (int i=0; i<datos.size(); i++)
		ss<<datos.at(i)<<" ";
	return ss.str();
}

string inttoString(int valor) const{
	stringstream ss; 
	if (valor <10){
		ss<<"00"<<valor;
	} else if (valor <100){
		ss<<"0"<<valor;
	} else {
		ss<<valor;
	}
	return ss.str();
}
	
string Registro::toStringArchivo(vector<Campo> estructura)const{
	stringstream ss;
	for (int i=0; i<datos.size(); i++){
		if (estructura.at(i).getFieldtype == 0)//entero
			ss<<inttoString(atoi(datos.at(i)))<<",";
		if (estructura.at(i).getFieldtype == 1){//texto
			bool bandera = true;
			int sizeTemp=estructura.at(i).getSize();
			for (int j = 0; j < sizeTemp; ++j){
				if (datos.at(i)[j] == '\0')
					bandera = false;
				if (bandera){
					ss << name[i]; 
				} else {
					ss<<'-';
				}
			}
		}
		if (estructura.at(i).getFieldtype == 2){//decimal

		}
	}
}

void Registro::Escribir(ofstream&, vector<Campo>){

}

void Registro::Leer(ifstream&, vector<Campo>){

}