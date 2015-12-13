#include "buscarrecord.h"
#include "ui_buscarrecord.h"

buscarRecord::buscarRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buscarRecord)
{
    ui->setupUi(this);
}

buscarRecord::~buscarRecord()
{
    delete ui;
}

void buscarRecord::on_btn_cerrar_clicked(){
    this->close();
}
