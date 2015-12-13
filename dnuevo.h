#ifndef DNUEVO_H
#define DNUEVO_H

#include <QDialog>
<<<<<<< HEAD
#include <vector>
#include "campo.h"
#include <stack>
=======
#include <QFile>
#include <vector>
#include "campo.h"
#include <stack>
#include"specialstack.h"
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

namespace Ui {
    using std::vector;
    using std::stack;

    class Dnuevo;
}

class Dnuevo : public QDialog{
    Q_OBJECT

public:
    explicit Dnuevo(QWidget *parent = 0);
    ~Dnuevo();
     vector<Campo> estructura;
    bool llavePrimariaDisponible=true;
<<<<<<< HEAD
    int cantidadCampos;
    stack <int> availlist;//declaración del availlist
=======
    int cantidadCampos=0;
    SpecialStack availlist;//declaración del availlist
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

private slots:
    void on_btn_agregarCampo_clicked();

    void on_btn_nuevoArchivo_clicked();

    void on_rb_int_clicked();

    void on_rb_char_clicked();

    void on_rb_decimal_clicked();

    void on_rb_ID_clicked();

    void on_rb_primaria_clicked();

private:
    Ui::Dnuevo *ui;
};

#endif // DNUEVO_H
