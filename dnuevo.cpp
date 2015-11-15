#include <string>
#include "dnuevo.h"
#include "ui_dnuevo.h"

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
    bool tipoCampo=false;//true es entero,false char
    if(ui->rb_int->isChecked())
        tipoCampo=true;
    int longitudCampo=ui->sp_longitud->value();
    bool llave=ui->cbx_llave->isChecked();
    //validar que no exista mas de una llave


    ui->txt_nameCampo->setText(NULL);
    ui->sp_longitud->setValue(1);
}

void Dnuevo::on_btn_nuevoArchivo_clicked(){
    string nombreCampo=ui->txt_nameCampo->text().toStdString();


    this->close();
}
