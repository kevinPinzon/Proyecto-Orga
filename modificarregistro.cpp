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
