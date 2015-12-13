#include "modificarregistro.h"
#include "ui_modificarregistro.h"

modificarRegistro::modificarRegistro(int pos,QWidget *parent) :
    QDialog(parent),ui(new Ui::modificarRegistro){
    this->pos=pos;
    ui->setupUi(this);
}

modificarRegistro::~modificarRegistro(){
    delete ui;
}
<<<<<<< HEAD
=======

void modificarRegistro::on_btn_modifRegistro_clicked(){

}

void modificarRegistro::on_btn_cerrar_clicked(){
    this->close();
}
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
