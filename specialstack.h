#ifndef SPECIALSTACK_H
#define SPECIALSTACK_H
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
    int offsetRegistro;
    int sizeRegistro;
    int offsetAvaillist;//el offset justo donde comienza el availlist en el header
public:
    SpecialStack();
    SpecialStack(int);

    string toString();
    int pop();
    void push(int);
    int peek();
    int posicionesAntesDe(int);
    bool isEmpty();
    void inicializar(ifstream&, int, int, int);
    /*parametros de inicializar	:
    ifstream& file, int pos(que toma del header), int offsetRegistros, int sizeRegistro(es el tamaño del registro fijo ARLF)
    */
    int siguientePosicionDisponible(string);
    void actualizarRRN_HEADER(int,ofstream&);
    int getOffsetRegistro();
    int getSizeRegistro();
    void setOffsetRegistro(int);
    void setSizeRegistro(int);
    void setoffsetAvaillist(int);
};

#endif // SPECIALSTACK_H
