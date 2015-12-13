#include <string>
#include "dnuevo.h"
#include "ui_dnuevo.h"
#include "campo.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QMessageBox>

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

    Campo Campotemp;
    string nombreCampo=ui->txt_nameCampo->text().toStdString();
    int tipoCampo=-1;//1-entero 2-char  3-decimal   4-ID
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
    //VALIDACIONES
    if(nombreCampo.empty()){
<<<<<<< HEAD
        QMessageBox::information(this,"Error","Es necesario que escriba un nombre para el campo");
=======
        QMessageBox::warning(this,"Error","Es necesario que escriba un nombre para el campo");
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
    }else{

        if(estructura.empty())
            llavePrimariaDisponible=true;
        else{
            for(int i=0; i<estructura.size(); i++){
                Campotemp=estructura.at(i);
                if(Campotemp.getKeytype()==1)
                    llavePrimariaDisponible=false;
            }
        }
        //Campo field ("IDPersona", 1, 10, 0, 1);//(name,fieldtype,size,sizedecimal,keytype)
        bool primeraValidacion=false,segundaValidacion=true;
        if(llave==1){
            if(llavePrimariaDisponible)
                primeraValidacion=true;
            if(!llavePrimariaDisponible){
<<<<<<< HEAD
                QMessageBox::information(this,"Error"," Ya existe un campo que es llave primaria");
=======
                QMessageBox::warning(this,"Error"," Ya existe un campo que es llave primaria");
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

            }
            if(primeraValidacion)
                llavePrimariaDisponible=false;
        }else if(llave!=1)
            primeraValidacion=true;


        if(primeraValidacion){
            if(!estructura.empty()){
                for(int i=0; i<estructura.size(); i++){
                    if(nombreCampo.compare(estructura.at(i).getName())==0)
                        segundaValidacion=false;
                }
            }
        }
        if(segundaValidacion && primeraValidacion){
            Campo campoNuevo(nombreCampo.c_str(),tipoCampo,longitudCampo,decimal,llave);
            estructura.push_back(campoNuevo);
        }else{
            stringstream ss;
            ss<<"   Ya existe un campo con el nombre: "<<nombreCampo;
<<<<<<< HEAD
            QMessageBox::information(this,"Error",ss.str().c_str());
=======
            QMessageBox::warning(this,"Error",ss.str().c_str());
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
        }

        ui->txt_nameCampo->setText(NULL);
        ui->sp_longitud->setValue(1);
    }
}

void Dnuevo::on_btn_nuevoArchivo_clicked(){
<<<<<<< HEAD
=======
    availlist.push(-1);
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
    string nombreArchivo=ui->txt_nameArchivo->text().toStdString();
    stringstream nameA;
    nameA<<nombreArchivo<<".dat";
    ofstream archivo;
    Campo field;
    if(nombreArchivo.empty()){
<<<<<<< HEAD
        QMessageBox::information(this,"Error","Es necesario que escriba un nombre para el archivo");
=======
        QMessageBox::warning(this,"Error","Es necesario que escriba un nombre para el archivo");
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
    }else{
        if(!estructura.empty()){
            if(!llavePrimariaDisponible){
                archivo.open(nameA.str().c_str(), ios::in | ios::out | ios::trunc);
                cantidadCampos=estructura.size();
<<<<<<< HEAD
                archivo<<cantidadCampos;
                archivo<<",";
                for (int i = 0; i < estructura.size(); ++i){
                        field = estructura.at(i);
                       // cout << field.toString() << endl;
                        archivo << field;
=======
                cout<<"antes de escribir cantidad de campos"<<endl;
                if(cantidadCampos<10){
                    archivo << "00"<<cantidadCampos << ',' << availlist.headAvaillistArchivo(availlist.peek()) << ';';
                }else{
                    archivo << "0"<<cantidadCampos << ',' << availlist.headAvaillistArchivo(availlist.peek()) << ';';
                }for (int i = 0; i < estructura.size(); ++i){
                        archivo << estructura.at(i);
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
                    }
                llavePrimariaDisponible=true;
                archivo.close();
                this->close();
            }else
<<<<<<< HEAD
            QMessageBox::information(this,"Error","Necesita crear un campo que sea llave primaria");
        }else{
            QMessageBox::information(this,"Error","Necesita crear al menos un campo");
=======
            QMessageBox::warning(this,"Error","Necesita crear un campo que sea llave primaria");
        }else{
            QMessageBox::warning(this,"Error","Necesita crear al menos un campo");
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
        }


    }
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
