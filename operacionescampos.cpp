#include "operacionescampos.h"
#include "ui_operacionescampos.h"

OperacionesCampos::OperacionesCampos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperacionesCampos)
{
    ui->setupUi(this);
}

OperacionesCampos::~OperacionesCampos()
{
    delete ui;
}
