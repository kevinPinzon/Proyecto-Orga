#ifndef DNUEVO_H
#define DNUEVO_H

#include <QDialog>
#include <vector>
#include "campo.h"

namespace Ui {
using std::vector;
class Dnuevo;
}

class Dnuevo : public QDialog
{
    Q_OBJECT

public:
    explicit Dnuevo(QWidget *parent = 0);
    ~Dnuevo();
     vector<Campo> estructura;
    bool llavePrimariaDisponible=false;

private slots:
    void on_btn_agregarCampo_clicked();

    void on_btn_nuevoArchivo_clicked();

    void on_rb_int_clicked();

    void on_rb_char_clicked();

    void on_rb_decimal_clicked();

private:
    Ui::Dnuevo *ui;
};

#endif // DNUEVO_H
