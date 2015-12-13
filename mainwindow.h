#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btn_salir_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
//falta terminar de modificar registro-------------------READY
//falta terminar de modificar campo----------------------READY
//falta hacer borrar campo-------------------------------READY
//falta terminar de cruzar archivos
//falta validar, que el ingreso de datos sea el que se espera----------READY
//validar que no se ejecuten botones como borrar, modificar registros, si no hay ningun registro en el vector.--------READY
//falta revisar el boton mostras mas registros-----------READY
//exportar json-------------------------------------------READY
//exportar xml
//exportar excel
