#include "eliminarregistro.h"
#include "ui_eliminarregistro.h"
#include <QFile>
#include <QTextStream>
#include<QItemSelection>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>
#include <QMessageBox>
#include <stdlib.h>
#include "campo.h"
#include"registro.h"
#include <iostream>
#include <fstream>

using namespace std;

eliminarRegistro::eliminarRegistro(SpecialStack availlist,vector<Campo> estructura,vector<Registro> VRegistros,QString path,QWidget *parent)
    :QDialog(parent),ui(new Ui::eliminarRegistro){
    ui->setupUi(this);
    this->availlist=availlist;
    this->estructura=estructura;
    this->VRegistros=VRegistros;
    this->path=path;
    ui->sp_elimRecord->setMinimum(1);
    ui->sp_elimRecord->setMaximum(VRegistros.size()+1);
    hacerTabla();
}

eliminarRegistro::~eliminarRegistro(){
    delete ui;
}

void eliminarRegistro::on_btn_visualizar_clicked(){
    RRNaBorrar=ui->sp_elimRecord->value();
    RRNaBorrar--;//le bajo uno para que ya este en termino de i que usamos para los fors donde i=0
    if (!(RRNaBorrar < 0 || RRNaBorrar >= VRegistros.size())){	//validado que la pos 1 - registros.zise()
        if (!availlist.isEmpty() || availlist.peek()==-100000){
            ui->tw_registroElim->setRowCount(ui->tw_registroElim->rowCount());
            Registro registroTemp;
            string cadenaTemp;
            registroTemp=VRegistros.at(RRNaBorrar);
            ui->tw_registroElim->setEnabled(true);
            for(int columnas=0; columnas<ui->tw_registroElim->columnCount(); columnas++){
                cadenaTemp=registroTemp.getDatos().at(columnas);
                cout<<registroTemp.getDatos().at(columnas)<<endl;
                ui->tw_registroElim->setItem(0,columnas,new QTableWidgetItem(cadenaTemp.data()));
            }
            ui->tw_registroElim->setEnabled(false);
        } else//else para cuando esta vacío el availist que no deberia de estar porque deberia de estar -1
            cout << "EL AVAILLIST ESTA COMPLETAMENTE VACIO" << endl;
    }else
        QMessageBox::critical(this,"ERROR","    La posicionque ha ingresado es invalida ");
}

vector<Registro> eliminarRegistro::actualizarRegistros(){
    return VRegistros;
}

string eliminarRegistro::toStringArchivoD1RD(int posicion){//devuelve la cadena que va en el registro borrado
    stringstream ss;
    ss<<"*"<<posicion<<";";
    return ss.str();
}

void eliminarRegistro::on_btn_borrarRecord_clicked(){
    int sigPosDisp = availlist.peek();
    string alBorrado = toStringArchivoD1RD(sigPosDisp);
    if (fileESCRIBIR.is_open()){
        fileESCRIBIR.clear();
        fileESCRIBIR.seekp(availlist.getOffsetRegistro()+
                           (availlist.getSizeRegistro()*((RRNaBorrar)+availlist.posicionesAntesDe(RRNaBorrar))));
        cout<<"se escribira en: "<<fileESCRIBIR.tellp()<<endl;
        fileESCRIBIR << alBorrado;//ya marqué el registro borrado
        availlist.push(RRNaBorrar);//actualizamos el availlist
        availlist.actualizarRRN_HEADER(RRNaBorrar,fileESCRIBIR);
        //registros.at(pos).clear();
        VRegistros.erase(VRegistros.begin()+RRNaBorrar);//borra el registro del vector en memoria
    }else{
        fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
        fileESCRIBIR.clear();
        fileESCRIBIR.seekp(availlist.getOffsetRegistro()+
                               (availlist.getSizeRegistro()*(RRNaBorrar+availlist.posicionesAntesDe(RRNaBorrar))));
        if (fileESCRIBIR.is_open()){
            fileESCRIBIR << alBorrado;//ya marqué el registro borrado
            availlist.push(RRNaBorrar);//actualizamos el availlist
            availlist.actualizarRRN_HEADER(RRNaBorrar,fileESCRIBIR);
            //registros.at(pos).clear();
            VRegistros.erase(VRegistros.begin()+RRNaBorrar);//borra el registro del vector en memoria
        }else
            QMessageBox::warning(this,"ERROR","       No se ha podido abrir el archivo para escritura  ");
    }
    this->close();
}

void eliminarRegistro::hacerTabla(){
    QTableWidget* tabla=ui->tw_registroElim;
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
        ui->tw_registroElim->setRowCount(ui->tw_registroElim->rowCount()+1);
        ui->tw_registroElim->setEnabled(false);

}

void eliminarRegistro::on_btn_cancelar_clicked(){
    this->close();
}
