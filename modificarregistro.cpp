#include "modificarregistro.h"
#include "ui_modificarregistro.h"
#include <QFile>
#include <QTextStream>
#include<QItemSelection>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>
#include <QMessageBox>
#include <stdlib.h>

modificarRegistro::modificarRegistro(SpecialStack availlist,vector<Registro> VRegistros,vector<Campo> estructura,QString path,QWidget *parent) :
    QDialog(parent),ui(new Ui::modificarRegistro){
    ui->setupUi(this);
    this->estructura=estructura;
    this->VRegistros=VRegistros;
    this->path=path;
    this->availlist=availlist;
    fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
    ui->sp_modifRecord->setMinimum(1);
    ui->sp_modifRecord->setMaximum(VRegistros.size());
    hacerTabla();

}

modificarRegistro::~modificarRegistro(){
    delete ui;
}

void modificarRegistro::on_btn_modifRegistro_clicked(){
    //se capturan los datos de la table

    if (!(RRNaModificar < 0 || RRNaModificar >= VRegistros.size())){	//validado que la pos 1 - registros.zise()
        QTableWidgetItem *itemTemp;
        int posLLave;
        for(int i=0; i<estructura.size(); i++){
            if(estructura.at(i).getKeytype()==1)
                posLLave=i;
        }
        registro.clear();
        itemTemp = ui->tw_registroMod->item(ui->tw_registroMod->rowCount()-1,posLLave);
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
            for(int j=0; j<ui->tw_registroMod->columnCount(); j++){
                    itemTemp = ui->tw_registroMod->item(ui->tw_registroMod->rowCount()-1,j);
                    registro.agregarDato(itemTemp->text().toStdString());
            }
            int posTempavail = availlist.peek();

            if (posTempavail == -1 ){
                fileESCRIBIR.clear();
                fileESCRIBIR.seekp(0, ios::beg);//setea el offset al comienzo del archivo)
                fileESCRIBIR.seekp(availlist.getOffsetRegistro()+(availlist.getSizeRegistro()*(RRNaModificar)));
                VRegistros.erase(VRegistros.begin()+RRNaModificar);
                VRegistros.insert(VRegistros.begin()+RRNaModificar,registro);
            }else{
                fileESCRIBIR.clear();
                fileESCRIBIR.seekp(0, ios::beg);//setea el offset al comienzo del archivo)
                int posArchivo =availlist.posicionArchivo(RRNaModificar);
                fileESCRIBIR.seekp(posArchivo);
                VRegistros.erase(VRegistros.begin()+RRNaModificar);
                VRegistros.insert(VRegistros.begin()+RRNaModificar,registro);
            }
            if (fileESCRIBIR.is_open()){
                registro.Escribir(fileESCRIBIR,estructura);
                registro.clear();
                this->close();
                QMessageBox::information(this," BRILLANTE   "," Se modifico el registro exitosamente!   ");
            }else
                QMessageBox::critical(this,"ERROR","     No se pudo abrir el archivo para escritura en modificar registro    ");
        }else{
           QMessageBox::critical(this,"ERROR","     La llave no esta disponible    ");
           itemTemp->setText(NULL);
        }

    }else
        QMessageBox::critical(this,"ERROR","    La posicionque ha ingresado es invalida ");
}


void modificarRegistro::on_btn_cerrar_clicked(){
    this->close();
}

void modificarRegistro::on_btn_visualizar_clicked(){
    RRNaModificar=ui->sp_modifRecord->value();
    cout<<RRNaModificar<<" ESTE ES EL RRN SIN RESTAR"<<endl;
    RRNaModificar--;//le bajo uno para que ya este en termino de i que usamos para los fors donde i=0
    if (!(RRNaModificar < 0 || RRNaModificar >= VRegistros.size())){	//validado que la pos 1 - registros.zise()
            ui->tw_registroMod->setRowCount(ui->tw_registroMod->rowCount());
            Registro registroTemp;
            string cadenaTemp;
            registroTemp=VRegistros.at(RRNaModificar);
            ui->tw_registroMod->setEnabled(true);
            for(int columnas=0; columnas<ui->tw_registroMod->columnCount(); columnas++){
                cadenaTemp=registroTemp.getDatos().at(columnas);
                cout<<registroTemp.getDatos().at(columnas)<<endl;
                ui->tw_registroMod->setItem(0,columnas,new QTableWidgetItem(cadenaTemp.data()));
            }
            ui->tw_registroMod->setEnabled(true);
    }else
        QMessageBox::critical(this,"ERROR","    La posicionque ha ingresado es invalida ");
}

void modificarRegistro::hacerTabla(){
    QTableWidget* tabla=ui->tw_registroMod;
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
        tabla->setRowCount(tabla->rowCount()+1);
        tabla->setEnabled(true);
}
vector<Registro> modificarRegistro::actualizarRegistros(){
    return VRegistros;
}

