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
#include "Registro.h"

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;

Registro::Registro(){
}

string Registro::toString()const{
	cout << "size de vector datos " << datos.size() << endl; 
	stringstream ss; 
	for (int i=0; i<datos.size(); i++)
		ss<<datos.at(i)<<" ";
	return ss.str();
}

string Registro::inttoString(int num, bool edilson) const{
	stringstream ss; 
	if (edilson){//edilson es true todo lo que no sea ID
		if(num < 10){
			ss << "00" << num;
		} else if (num <100){
			ss<<"0"<<num;
		} else {
			ss<<num;
		}
	} else {//edilson es false y para ID
		if(num < 10){
			ss << "00000" << num;
		} else if (num <100){
			ss<<"0000"<<num;
		} else if (num < 1000){
			ss<<"000"<<num;
		} else if (num < 10000){
			ss<<"00"<<num;
		} else if (num < 100000){
			ss<<"0"<<num;
		} else {
			ss<<num;
		}
	}
	return ss.str();
}

	
string Registro::toStringArchivo(vector<Campo> estructura)const{
	stringstream ss;
	//string valor; aqui pongo el string en datos.at(i)
	for (int i=0; i<datos.size(); i++){
		if (estructura.at(i).getFieldtype() == 0)//entero
			ss<<inttoString(atoi(datos.at(i).c_str()), false);
		if (estructura.at(i).getFieldtype() == 1){//texto
			bool bandera = true;
			int sizeTemp=estructura.at(i).getSize();
			for (int j = 0; j < sizeTemp; ++j){
				if (datos.at(i)[j] == '\0')
					bandera = false;
				if (bandera){
					ss << datos.at(i)[j]; 
				} else {
					ss<<'-';
				}
			}
		}
		if (estructura.at(i).getFieldtype()== 2){//decimal
			string numerodecimal, parteEntero, parteDecimal;
			int tamañodecimal = estructura.at(i).getSizedecimal();
			numerodecimal = datos.at(i);
			int pos1=0;
			pos1 = numerodecimal.find('.');
			parteEntero = numerodecimal.substr(0, pos1);
			pos1++;
			parteDecimal = numerodecimal.substr(pos1, numerodecimal.size()-pos1);
			ss<< inttoString(atoi(parteEntero.c_str()), false);
			ss<<".";
			for (int j=0; j < tamañodecimal; j++){
				bool bandera = true;
				if (j >= parteDecimal.size())
					bandera = false; 
				if (bandera){
					ss << parteDecimal[j];
				} else {
					ss << "0";
				}
			}
		}
		if (i < datos.size()-1){
			ss << ",";
		} else {
			ss << "\t";
		}
	}
	return ss.str();
}

void Registro::Escribir(ofstream& archivo, vector<Campo> estructura){
	archivo << toStringArchivo (estructura);
}

void Registro::Leer(ifstream& archivo, vector<Campo> estructura){

}
vector<string> Registro::getDatos(){
	return datos;
}	

void Registro::agregarDato(string datoN){
	datos.push_back(datoN);
	cout << "size de datos "<<datos.size()<< endl; 
}
