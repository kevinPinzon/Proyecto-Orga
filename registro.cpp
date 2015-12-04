#include "registro.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "campo.h"

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
    if (edilson){//
        if(num < 10){
            ss << "00" << num;
        } else if (num <100){
            ss<<"0"<<num;
        } else {
            ss<<num;
        }
    } else {//para ID
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
            cout<<" tipo: "<<estructura.at(i).getFieldtype()<<endl;
            if(estructura.at(i).getFieldtype() == 4 )//ID
                ss<<inttoString(atoi(datos.at(i).c_str()), true);
            if (estructura.at(i).getFieldtype() == 1)//entero
                ss<<inttoString(atoi(datos.at(i).c_str()), false);
            if (estructura.at(i).getFieldtype() == 2){//texto
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
            if (estructura.at(i).getFieldtype()== 3){//decimal
                string numerodecimal, parteEntero, parteDecimal;
                int tamaodecimal = estructura.at(i).getSizedecimal();
                numerodecimal = datos.at(i);
                int pos1=0;
                pos1 = numerodecimal.find('.');
                parteEntero = numerodecimal.substr(0, pos1);
                pos1++;
                parteDecimal = numerodecimal.substr(pos1, numerodecimal.size()-pos1);
                ss<< inttoString(atoi(parteEntero.c_str()), false);
                ss<<".";
                for (int j=0; j < tamaodecimal; j++){
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
      cout<<" to string en archivo: "<<toStringArchivo(estructura)<<endl;
        archivo << toStringArchivo (estructura);
    }

    bool Registro::Leer(ifstream& archivo, vector<Campo> estructura){
        cout<<"ENTRO A LEER"<<endl;
        string linea, sublinea;
        char str[100];
        int pos1=0, pos2;
        if(archivo.is_open()){
            if (!archivo.getline(str, 100, '\t'))
                return false;
            linea = str;
            for (int i =0; i < estructura.size(); i++){
                pos2 = linea.find(',', pos1);
                sublinea = linea.substr(pos1, pos2-pos1);
                if (estructura.at(i).getFieldtype() == 1 || estructura.at(i).getFieldtype() == 4
                        || estructura.at(i).getFieldtype() == 3 ){
                    //cout << "es de tipo entero o ID " << endl;
                    while (sublinea[0] == '0'){
                        sublinea.erase(0,1);
                    }
                }
                if (estructura.at(i).getFieldtype() == 2){
                    pos1 = sublinea.find('-', 0);
                    sublinea.erase(pos1, sublinea.size()-pos1);
                }
                pos1 = pos2+1;
                cout << sublinea << endl;
                agregarDato(sublinea);
            }

            return true;
        }else{
            cout<<"No se pudo abrir el archivo para lectura de registros en el clase registro"<<endl;
            return false;
        }
}


    vector<string> Registro::getDatos(){
        return datos;
    }

    void Registro::agregarDato(string datoN){
        datos.push_back(datoN);
    }
    void Registro::clear(){
        datos.clear();
    }
