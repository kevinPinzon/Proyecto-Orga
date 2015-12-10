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
	ss << "VIPList\n" << VIPList.toString();
	return ss.str();
}//fin to string de availlist que imprime todo lo que hay en availlist

int SpecialStack::pop(){
	int siguienteElementoDisponible; 
	if (!availlist.empty()){
		siguienteElementoDisponible = availlist.back();
		availlist.pop_back();
		if (!VIPList.isEmpty())
			VIPList.eliminarValor(siguienteElementoDisponible);
		else 
			cerr << "ERROR: ListaOrdenada VIPList esta vacia en pop de SpecialStack." << endl; 
	} else {
		siguienteElementoDisponible = -1;
	}
	
	return siguienteElementoDisponible;
}// fin poop :p

void SpecialStack::push(int valor){
	availlist.push_back(valor);
	VIPList.agregar(valor);
}// fin 

int SpecialStack::peek(){
	if (!availlist.empty())
		return availlist.back();
	return -1;
}// fin

int SpecialStack::posicionArchivo(int pos){//el valor que retorna aqui es la verdadera posicion en el archivo del registro que 
	//escogio el usuario para borrar del vector de registros
	int RBCD0 = VIPList.cantidadNumerosSeguidosDesde(0);//registros borrados continuos desde cero
	if (RBCD0<0){//significa que no ha borrado el registro 0
		RBCD0=0;
	}
	int posAntes = VIPList.posicionesAntesDe(pos + RBCD0);
	int posArchivo = posAntes+pos;
	cout << "EN SpecialStack::posicionArchivo -> pos : " << pos << "\tRDCD0 : " << RBCD0 << "\tposAntes : " << posAntes << "\tposArchivi : " << posArchivo << endl;
	return posArchivo;
}

bool SpecialStack::isEmpty(){
	if (availlist.empty())
		return true;
	return false;
}

void SpecialStack::inicializar(ifstream& file, int offsetR, int sizeR){
	char str[20];
	string linea;
	if (file.is_open()){
		file.clear();
		file.seekg(4, ios::beg);//coloca el offset donde esta el head del availlist en el header
		file.getline(str, 20, ';'); 
		linea = str;
		int posDisp = cadena2Int(linea);//aqui toma el head del availlist
	
		while (posDisp != -1){
			cout << "En SpecialStack::inicializar pos que recibe : " << posDisp << endl; 
			file.seekg(offsetR+(sizeR * posDisp ));// se va a la poscion en el archvo que indica posDisp
			file.getline(str, 20, ';');
			linea = str;
			availlist.insert(availlist.begin()+0, posDisp);//agrega la poscion al availlist
			VIPList.agregar(posDisp);//agrega la posicion al VIPList que es la lista ordenada de las posciones en el availlist
			posDisp = siguientePosicionDisponible(linea);
		}
		availlist.insert(availlist.begin()+0, posDisp);
		VIPList.agregar(posDisp);
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

int SpecialStack::buscarVIP(int valor){
	return VIPList.buscar(valor);
}