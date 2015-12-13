#include "agregarregistro.h"
#include "ui_agregarregistro.h"
#include <QFile>
#include <QTextStream>
<<<<<<< HEAD
=======
#include<QItemSelection>
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>
<<<<<<< HEAD

#include "campo.h"
#include"registro.h"

AgregarRegistro::AgregarRegistro(QString path,vector<Campo> estructura,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarRegistro)
{
    ui->setupUi(this);
    this->path=path;
    this->estructura=estructura;
=======
#include <QMessageBox>
#include <stdlib.h>
#include "campo.h"
#include"registro.h"

AgregarRegistro::AgregarRegistro(SpecialStack availlist,QString path,vector<Campo> estructura,vector<Registro> VRegistros,QWidget *parent) :
    QDialog(parent),ui(new Ui::AgregarRegistro){
    this->availlist=availlist;
    ui->setupUi(this);
    this->path=path;
    fileESCRIBIR.open(this->path.toStdString().c_str(), ios::in | ios::out);
    this->estructura=estructura;
    this->VRegistros=VRegistros;
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
    hacerTabla();
}

void AgregarRegistro::hacerTabla(){
    QTableWidget* tabla=ui->tw_registroAdd;
    do{
        tabla->removeRow(0);
    }while(tabla->rowCount());
    QStringList encabezados;
    Campo temp;
    string tempCadena;
    int posTemp;
    for (int cont = 0; cont < estructura.size(); ++cont) {
        temp=estructura.at(cont);
        tempCadena=temp.getName();
        posTemp=tempCadena.find('-');
        tempCadena=tempCadena.substr(0,posTemp);
        QString str(tempCadena.c_str());
        encabezados.append(str);
    }
    tabla->setColumnCount(estructura.size());
    tabla->setHorizontalHeaderLabels(encabezados);
    ui->tw_registroAdd->setRowCount(ui->tw_registroAdd->rowCount()+1);

}

<<<<<<< HEAD
Registro AgregarRegistro::actualizarTabla(){
    return registro;
=======
vector<Registro> AgregarRegistro::actualizarRegistro(){
    return VRegistros;
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
}

AgregarRegistro::~AgregarRegistro()
{
    delete ui;
}

void AgregarRegistro::on_btn_agregarRegi_clicked(){
    QTableWidgetItem *itemTemp;
<<<<<<< HEAD
    for(int j=0; j<ui->tw_registroAdd->columnCount(); j++){
        itemTemp = ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,j);
        registro.agregarDato(itemTemp->text().toStdString());
    }
    if (fileESCRIBIR.is_open()){
            registro.Escribir(fileESCRIBIR, estructura);
            actualizarTabla();
        }
    else{
        fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out | ios::app);
        if (fileESCRIBIR.is_open()){
                registro.Escribir(fileESCRIBIR, estructura);
                actualizarTabla();
            }
    }
    seAgrego=true;
    this->close();
=======
    //VALIDACIONES
    //para mejorar la validacion de llaves, se necesita indices.

    int posLLave;
    for(int i=0; i<estructura.size(); i++){
        if(estructura.at(i).getKeytype()==1)
            posLLave=i;
    }
    if(ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,posLLave)->text().isEmpty()){
        QMessageBox::critical(this,"No se ingreso el registro","     Necesita digitar una llave para el nuevo registro    ");
    }else{
        registro.clear();
        itemTemp = ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,posLLave);
        bool llaveDisponible=true;
        int llaveNueva= atoi(itemTemp->text().toStdString().c_str());
        double llaveVal=0.00;
        int llaveRegistrada=0;
        for(int j=0; j<VRegistros.size(); j++){
            llaveRegistrada=atoi(VRegistros.at(j).getDatos().at(posLLave).c_str());
            llaveVal=(llaveRegistrada/llaveNueva);
            if(llaveVal==1.00)
                llaveDisponible=false;
        }
        if(llaveDisponible){
            for(int j=0; j<ui->tw_registroAdd->columnCount(); j++){
                    itemTemp = ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,j);
                    registro.agregarDato(itemTemp->text().toStdString());
                    seAgrego=true;

            }
            //AVAILLIST
            cout<<"Registro toString en agregar: "<<registro.toString()<<endl;
            cout<<"Registro toStringArchivo en agregar: "<<registro.toStringArchivo(estructura)<<endl;
            bool cambiarHeaderAvail=false;
            if(availlist.peek()== -1 ){//si el availlist devuelve -1, se agrega alfinal y listo
                cout<<"availlist tiene -1"<<endl;
                fileESCRIBIR.seekp(availlist.getOffsetRegistro()+
                                   (availlist.getSizeRegistro()*(VRegistros.size())));
                VRegistros.push_back(registro);
            }else{//si el availist devuelve distinto a -1
                cout<<"availlist tiene distinto a -1"<<endl;
                cout << "La posicion que sale peek del availlist: "<<availlist.peek()<<endl;
                int sigPosDisponibleArchivo=availlist.peek();
                int posAntes = availlist.buscarVIP(sigPosDisponibleArchivo)-1;
                int posVector = sigPosDisponibleArchivo - posAntes;
                availlist.pop();
                cout << "La posicion con la que se trabaja del availlist: "<<sigPosDisponibleArchivo<<endl;
                fileESCRIBIR.seekp(availlist.getOffsetRegistro()+sigPosDisponibleArchivo*availlist.getSizeRegistro());
                cambiarHeaderAvail=true;

                if(posVector <= 0){
                    VRegistros.insert(VRegistros.begin()+0,registro);
                }else{
                    if(posVector >= VRegistros.size()){
                        VRegistros.push_back(registro);
                    }else{
                        VRegistros.insert(VRegistros.begin()+posVector,registro);
                    }
                }
            }
            if (fileESCRIBIR.is_open()){
                cout<<"apunto de escribir"<<endl;
                registro.Escribir(fileESCRIBIR, estructura);
                actualizarRegistro();
                registro.clear();
                if(cambiarHeaderAvail){
                    fileESCRIBIR.seekp(4);
                    fileESCRIBIR<< availlist.headAvaillistArchivo(availlist.peek());
                    QMessageBox::information(this," BRILLANTE   "," Se agrego el registro    ");
                    this->close();
                }else{
                QMessageBox::information(this," BRILLANTE   "," Se agrego el registro    ");
                this->close();
                }
            }else
                QMessageBox::critical(this,"ERROR","     No se pudo abrir el archivo para escritura en agregarRegistro    ");
        }else{
        QMessageBox::critical(this,"No se ingreso el registro","     La llave que desea ingresar ya esta siendo utilizada por otro registro    ");
        itemTemp->setText(NULL);
        }
    }
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
}


void AgregarRegistro::on_btn_cerrar_clicked(){
    if (fileESCRIBIR.is_open())
        fileESCRIBIR.close();
    seAgrego=false;
    this->close();
}
