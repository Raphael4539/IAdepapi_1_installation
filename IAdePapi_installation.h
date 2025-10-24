#ifndef IADEPAPI_INSTALLATION_H
#define IADEPAPI_INSTALLATION_H


#include <QFileDialog>
#include <QDialog>
#include<QString>
#include <QDebug>
#include<QFile>
#include<QDir>
#include<QMessageBox>

class IAdePapi_installation : public QWidget{
    Q_OBJECT

public:

    IAdePapi_installation(QWidget *parent = nullptr);
    ~IAdePapi_installation();
    void createExemplesFileForBcdToOutput(QWidget *a, QString DirLabel,
        QString DirExemple, quint32 nberOfExemples);
    void createExemplesFileForXORFunction(QWidget *a, QString DirLabel,
        QString DirExemple, quint32 nberOfExemples);
    void createExemplesFileForORFunction(QWidget *a, QString DirLabel,
        QString DirExemple, quint32 nberOfExemples);
    void createExemplesFileForDecimalToBCDFunction(QWidget *a, QString DirLabel,
        QString DirExemple, quint32 nberOfExemples);
    void createParametreFileForMNISTFunction(QWidget *a,
        QString DirParam, quint32 nberOfImages);

private:

    QFileDialog *m_fileDialog;
    QDialog     *m_dialog;
    QFile       *m_qFile;
    QDir        *m_qDir;
    QString     m_DirChoisi, m_DirExemples, m_DirParam;
};

#endif // IADEPAPI_INSTALLATION_H
