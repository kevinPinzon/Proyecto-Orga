#include "operacionescampos.h"
#include "ui_operacionescampos.h"
#include "campo.h"
#include<QStandardItemModel>
#include<QComboBox>
#include <QDebug>
#include <QFile>
#include <vector>
#include <sstream>
#include <QMessageBox>

using namespace std;

OperacionesCampos::OperacionesCampos(QString path,vector <Campo> estructura,QWidget *parent):QDialog(parent),ui(new Ui::OperacionesCampos){
    this->estructura=estructura;
    ui->setupUi(this);
    llenarComboBoxCampos();
    this->path=path;
}

OperacionesCampos::~OperacionesCampos(){
    delete ui;
}

void OperacionesCampos::llenarComboBoxCampos(){
    string temp;
    for(int i=0; i<estructura.size(); i++){
        temp=estructura.at(i).getName();
        ui->cb_campos->addItem(temp.c_str());
    }
}

void OperacionesCampos::on_btn_modificarCampo_clicked(){

}

void OperacionesCampos::on_btn_eliminarCampo_clicked(){

}

void OperacionesCampos::on_btn_cerrar_clicked(){
    this->close();
}

void OperacionesCampos::on_cb_campos_currentIndexChanged(int index){
    Campo temp;
    this->index=index;
    temp=estructura.at(index);
    ui->txt_nameCampo->setText(temp.getName());
    cout<<temp.getFieldtype()<<endl;
    if(temp.getFieldtype()==1){
       ui->rb_int->setChecked(true);
       ui->sp_decimales->setEnabled(false);
       ui->sp_longitud->setEnabled(false);
    }

    if(temp.getFieldtype()==2){
        ui->rb_char->setChecked(true);
        ui->sp_decimales->setEnabled(false);
        ui->sp_longitud->setEnabled(true);
        ui->sp_longitud->setValue(temp.getSize());
    }

    if(temp.getFieldtype()==3){
       ui->rb_decimal->setChecked(true);
       ui->sp_decimales->setEnabled(true);
       ui->sp_decimales->setValue(temp.getSizedecimal());
       ui->sp_longitud->setVisible(false);
    }

    if(temp.getFieldtype()==4){
       ui->rb_ID->setChecked(true);
       ui->sp_decimales->setEnabled(false);
       ui->sp_longitud->setEnabled(false);
    }

    if(temp.getKeytype()==0)
        ui->rb_noEsLLave->setChecked(true);
    if(temp.getKeytype()==1)
        ui->rb_primaria->setChecked(true);
    if(temp.getKeytype()==2)
        ui->rb_secundaria->setChecked(true);


}











