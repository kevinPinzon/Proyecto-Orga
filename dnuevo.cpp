#include <string>
#include "dnuevo.h"
#include "ui_dnuevo.h"
#include "campo.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;

Dnuevo::Dnuevo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dnuevo)
{
    ui->setupUi(this);
}

Dnuevo::~Dnuevo()
{
    delete ui;
}

void Dnuevo::on_btn_agregarCampo_clicked(){
    string nombreCampo=ui->txt_nameCampo->text().toStdString();
    int tipoCampo=-1;//1-entero,2-char,3-decimal
    if(ui->rb_int->isChecked())//ENTERO
        tipoCampo=1;
    if(ui->rb_char->isChecked())//CHAR
        tipoCampo=2;
    if (ui->rb_decimal->isChecked())//DECIMAL
        tipoCampo=3;
    if (ui->rb_ID->isChecked())//ID
        tipoCampo=4;

    int longitudCampo=ui->sp_longitud->value();
    int decimal=ui->sp_decimales->value();

    int llave=0;
    if(ui->rb_primaria->isChecked())
        llave=1;
    if (ui->rd_secundaria->isChecked())
        llave=2;
    //validar que no exista mas de una llave
    if(estructura.empty())
        llavePrimariaDisponible=true;
    else{
        Campo Campotemp;
        for(int i=0; i<estructura.size(); i++){
            Campotemp=estructura.at(i);
            cout<<"Campotemp "<<i<<" tiene: "<<Campotemp.getKeytype()<<endl;
            if(Campotemp.getKeytype()==1)
                llavePrimariaDisponible=false;
        }
    }
    //Campo field ("IDPersona", 1, 10, 0, 1);//(name,fieldtype,size,sizedecimal,keytype)
    if(llave==1){
        if(llavePrimariaDisponible){
            Campo campoNuevo(nombreCampo.c_str(),longitudCampo,tipoCampo,decimal,llave);
            estructura.push_back(campoNuevo);
        }if(!llavePrimariaDisponible)
            cout<<"Ya existe llave primaria"<<endl;
    }else if(llave==0|| llave==2){
        Campo campoNuevo(nombreCampo.c_str(),longitudCampo,tipoCampo,decimal,llave);
        estructura.push_back(campoNuevo);
    }



    ui->txt_nameCampo->setText(NULL);
    ui->sp_longitud->setValue(1);
}

void Dnuevo::on_btn_nuevoArchivo_clicked(){
    string nombreArchivo=ui->txt_nameArchivo->text().toStdString();
    stringstream nameA;
    nameA<<nombreArchivo<<".dat";
    ofstream archivo;
    Campo field;
    if(!estructura.empty()){
        archivo.open(nameA.str().c_str(), ios::in | ios::out | ios::trunc);
        cantidadCampos=estructura.size();
        archivo<<cantidadCampos;
        archivo<<",";
        for (int i = 0; i < estructura.size(); ++i){
                field = estructura.at(i);
                cout << field.toString() << endl;
                archivo << field;
            }

    archivo.close();
    }
    this->close();
}

void Dnuevo::on_rb_int_clicked(){
    ui->sp_decimales->setEnabled(false);
    ui->sp_longitud->setEnabled(false);

}

void Dnuevo::on_rb_char_clicked(){
    ui->sp_decimales->setEnabled(false);
    ui->sp_longitud->setEnabled(true);

}

void Dnuevo::on_rb_decimal_clicked(){
    ui->sp_decimales->setEnabled(true);
    ui->sp_longitud->setEnabled(false);

}


void Dnuevo::on_rb_ID_clicked(){
    ui->sp_decimales->setEnabled(false);
    ui->sp_longitud->setEnabled(false);
}
