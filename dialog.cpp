#include "dialog.h"
#include "ui_dialog.h"
#include "qfiledialog.h"
#include <iostream>
#include "obj.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Obj File"), "/Users/", tr("OBJ Files (*.obj)"));
    bool exists = QFile(fileName).exists();

    if(exists) {
        QByteArray tmp = fileName.toLocal8Bit();
        const char* file = tmp.data();
        std::cout<<"ok!"<<std::endl;
        obj_file obj;
        obj.num_facets = 0;
        obj.num_vertex = 0;
        if(parse_num_vertex_facets(file, &obj)) {
            std::cout << "Error" << std::endl;
        } else {
            int err = init_obj_struct(&obj);
            if(!err) {
                parse_file(file, &obj);
                std::cout<<obj.num_vertex<<std::endl;
            }
        }
    }
}


void Dialog::on_pushButton_2_clicked()
{
    QApplication::exit(0);
}

