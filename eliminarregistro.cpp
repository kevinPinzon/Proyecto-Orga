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
    fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
    ui->sp_elimRecord->setMinimum(1);
    ui->sp_elimRecord->setMaximum(VRegistros.size());
    hacerTabla();
}

eliminarRegistro::~eliminarRegistro(){
    delete ui;
}

void eliminarRegistro::on_btn_visualizar_clicked(){//muestra el registro
    RRNaBorrar=ui->sp_elimRecord->value();
    cout<<RRNaBorrar<<" ESTE ES EL RRN SIN RESTAR"<<endl;
    RRNaBorrar--;//le bajo uno para que ya este en termino de i que usamos para los fors donde i=0
    if (!(RRNaBorrar < 0 || RRNaBorrar >= VRegistros.size())){	//validado que la pos 1 - registros.zise()
        if (!availlist.isEmpty()){
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
    if (!(RRNaBorrar < 0 || RRNaBorrar >= VRegistros.size())){	//validado que la pos 1 - registros.zise()
        int sigPosDisp = availlist.peek();
        string alBorrado = toStringArchivoD1RD(sigPosDisp);
        int posArchivo = availlist.posicionArchivo(RRNaBorrar);

        if (fileESCRIBIR.is_open()){
            fileESCRIBIR.clear();
            fileESCRIBIR.seekp(availlist.getOffsetRegistro()+(availlist.getSizeRegistro()*(posArchivo)));
            fileESCRIBIR<<alBorrado;
            cout<<"availlist peek primero es: "<<availlist.peek()<<endl;
            availlist.push(posArchivo);
            cout<<"availlist peek ahora es: "<<availlist.peek()<<endl;
            cout<<"rrnaBorrar es: "<<RRNaBorrar<<endl;
            fileESCRIBIR.seekp(4);
            cout<<"headavaillistarchivo, va a mandar a fileEscribir: "<<availlist.headAvaillistArchivo(posArchivo)<<endl;
            fileESCRIBIR << availlist.headAvaillistArchivo(posArchivo);
            VRegistros.erase(VRegistros.begin()+RRNaBorrar);//borra el registro del vector en memoria
        }else
            QMessageBox::warning(this,"ERROR","       No se ha podido abrir el archivo para escritura en borrarRegistro  ");
        this->close();
    }else
        QMessageBox::critical(this,"ERROR","    La posicionque ha ingresado es invalida ");
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

SpecialStack eliminarRegistro::actualizarAvaillist(){
    return availlist;
}
