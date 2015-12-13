#ifndef BUSCARRECORD_H
#define BUSCARRECORD_H

#include <QDialog>

namespace Ui {
class buscarRecord;
}

class buscarRecord : public QDialog
{
    Q_OBJECT

public:
    explicit buscarRecord(QWidget *parent = 0);
    ~buscarRecord();

private slots:
    void on_btn_cerrar_clicked();

private:
    Ui::buscarRecord *ui;
};

#endif // BUSCARRECORD_H
