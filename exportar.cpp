#include "exportar.h"
#include "ui_exportar.h"
#include <QMessageBox>

exportar::exportar(vector<Campo> estructura,vector<Registro> VRegistros,SpecialStack availlist,QString path,QWidget *parent) :
    QDialog(parent),ui(new Ui::exportar){
    ui->setupUi(this);
    this->availlist=availlist;
    this->estructura=estructura;
    this->VRegistros=VRegistros;
    this->path=path;
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
}

exportar::~exportar(){
    delete ui;
}

void exportar::on_btn_cerrar_clicked(){
    fileLEER.close();
    fileESCRIBIRExportar.close();
    this->close();
}

void exportar::on_btn_json_clicked(){
    stringstream ss;
    string nombre= ui->txt_nameArchivo->text().toStdString();
    int rrn=1;
    if(!nombre.empty()){
        ss<<nombre<<".dat";
        fileESCRIBIRExportar.open(ss.str().c_str(), ios::in | ios::out | ios::trunc);
        if(fileLEER.is_open() && fileESCRIBIRExportar.is_open()){
            fileLEER.seekg (0, fileLEER.end);//Move get cursor to the end of file.
            long length = ((long)fileLEER.tellg()-availlist.getOffsetRegistro())/availlist.getSizeRegistro();
            fileESCRIBIRExportar << "{\"Personas\":[\n";
            do{
                int offset=availlist.getOffsetRegistro()+rrn*availlist.getSizeRegistro();
                char bufferID[6];
                fileLEER.seekg(offset);
                fileLEER.read(bufferID,6);
                string strID(bufferID,6);

                char bufferName[30];
                fileLEER.seekg(offset+7);
                fileLEER.read(bufferName,30);
                string strName(bufferName,30);

                char bufferAge[3];
                fileLEER.seekg(offset+38);
                fileLEER.read(bufferAge,3);
                string strAge(bufferAge,3);

                char bufferIDC[6];
                fileLEER.seekg(offset+42);
                fileLEER.read(bufferIDC,6);
                string strIDC(bufferIDC,6);

                if(rrn == length-1){
                        fileESCRIBIRExportar << "{\"IdPersona\":\""<<strID<<"\", \"Nombre\":\""
                                             <<strName<<"\", \"Edad\":\""<<strAge<<"\", \"IdCiudad\":\""<<strIDC<<"\"}\n]}";
                }else{
                    fileESCRIBIRExportar << "{\"ID\":\""<<strID<<"\", \"Nombre\":\""
                                         <<strName<<"\", \"Edad\":\""<<strAge<<"\", \"IdCiudad\":\""<<strIDC<<"\"},\n";
                }
                rrn++;
            }while(rrn<length );
            cout << "finalizado la exportacion JSon"<<endl;
            cout<<"offset: "<<availlist.getOffsetRegistro()<<endl;
            cout<<"size de registro: "<<availlist.getSizeRegistro()<<endl;

            QMessageBox::information(this," BRILLANTE   "," Se ha exportado a JSon!  ");
            fileLEER.close();
            fileESCRIBIRExportar.close();
            this->close();
        }else{
        QMessageBox::warning(this," ERROR   "," No se pudieron abrir los archivos en JAson-Exportar    ");
        }
    }else{
        QMessageBox::warning(this," ERROR   "," Escriba un nombre para el nuevo archivo    ");
    }
}

void exportar::on_btn_xml_clicked(){

}
