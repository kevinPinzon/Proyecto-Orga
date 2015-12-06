/*
SpecialStack.cpp
*/

#include "SpecialStack.h"

using namespace std; 

SpecialStack::SpecialStack(){
}//constructor por defecto no hace nada

SpecialStack::SpecialStack(int valorInicial){
	availlist.push_back(valorInicial);
}//constructor con un entero de argumento

string SpecialStack::toString(){
	stringstream ss; 
	for (int i=0; i < availlist.size(); i++)
		ss <<""<< availlist.at(i) << endl;
	return ss.str();
}//fin to string de availlist que imprime todo lo que hay en availlist

int SpecialStack::pop(){
	int siguienteElementoDisponible; 
	if (!availlist.empty()){
		siguienteElementoDisponible = availlist.back();
		availlist.pop_back();
	} else {
		siguienteElementoDisponible = -1;
	}
	
	return siguienteElementoDisponible;
}// fin poop :p

void SpecialStack::push(int valor){
	availlist.push_back(valor);

}// fin 

int SpecialStack::peek(){
	if (!availlist.empty())
		return availlist.back();
	return -1;
}// fin

int SpecialStack::posicionesAntesDe(int valor){//el valor que manda aqui es entero ya que es comparable
	int contador =-1;
	for (int i=0; i< availlist.size(); i++){
		if (availlist.at(i) <= valor)
			contador++;
	}
	cout << "Posiciones antes de " << valor << " = " << contador << endl; 
	return contador;
}

bool SpecialStack::isEmpty(){
	if (availlist.empty())
		return true;
	return false;
}

void SpecialStack::inicializar(ifstream& file, int offsetR, int sizeR){
	char str[20];
	string linea;
	file.clear();
	file.seekg(4, ios::beg);
	cout << "Cargando el availist Offset en: " << file.tellg() << endl;
	file.getline(str, 20, ';'); 
	cout << "Cargando el availist: " << str << endl;
	linea = str;
	int posDisp = cadena2Int(linea);
	cout << "posDisp que recibe en inicializar: " << posDisp << endl;

	if (file.is_open()){
		while (posDisp != -1){
			file.seekg(offsetR+(sizeR * posDisp ));
			file.getline(str, 20, ';');
			linea = str;
			cout << "En SpecialStack::inicializar " << linea << endl;
			//push(posDisp);
			availlist.insert(availlist.begin()+0, posDisp);
			posDisp = siguientePosicionDisponible(linea);
		}
		//push(posDisp);
		availlist.insert(availlist.begin()+0, posDisp);
	} else {
		cerr << "ERROR: no se pudo abrir el archivo para lectura de levantar header" << endl;
	}

}

int SpecialStack::siguientePosicionDisponible(string linea){
	linea.erase(0,1);
	//linea.erase(linea.size(), 1);
	cout << "En SpecialStack::siguientePosicionDisponible " << linea << endl;
	return atoi(linea.c_str());
}

int SpecialStack::cadena2Int(string linea){
	while (linea[0] == '0')
		linea.erase(0,1); 
	return atoi(linea.c_str());
}