#ifndef DNUEVO_H
#define DNUEVO_H

#include <QDialog>

namespace Ui {
class Dnuevo;
}

class Dnuevo : public QDialog
{
    Q_OBJECT

public:
    explicit Dnuevo(QWidget *parent = 0);
    ~Dnuevo();

private slots:
    void on_btn_agregarCampo_clicked();

    void on_btn_nuevoArchivo_clicked();

private:
    Ui::Dnuevo *ui;
};

#endif // DNUEVO_H
