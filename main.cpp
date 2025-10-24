#include "QWidget"
#include "IAdePapi_installation.h"

#include <QApplication>


int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    QWidget *w = nullptr;
    w = new QWidget;
    IAdePapi_installation fenetre(w);

    return a.exec();
}
