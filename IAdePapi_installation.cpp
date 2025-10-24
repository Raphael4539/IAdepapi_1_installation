

#include "IAdePapi_installation.h"


IAdePapi_installation::IAdePapi_installation(QWidget *parent): QWidget(parent){


    m_DirChoisi = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
    tr( "/home"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    qDebug() << "DirChoisi: " << m_DirChoisi ;

    m_qFile = new QFile();
    m_qFile->copy("C:/Users/bmjri/Documents/IAdepapi_1/train-labels-idx1-ubyte",
        m_DirChoisi + "/train-labels-idx1-ubyte_1");
    m_qDir = new QDir();

    m_DirExemples = m_DirChoisi +"/data_BcdToOutput";
    if(!m_qDir->mkdir(m_DirExemples)) QMessageBox::information(this,tr("Information"),
                                        tr(" le dossier /data_BcdToOutput_1 existe"));
    m_qDir->cd(m_DirChoisi + "/data_BcdToOutput_1");

    qDebug() << "m_DirExemples " << m_DirExemples;
 //   m_qFile->copy("C:/Users/bmjri/Documents/IAdepapi_1/XORNew.txt",
 //   m_DirExemples + "/XORNew.txt");
    createExemplesFileForBcdToOutput(this, m_DirChoisi,  m_DirExemples, 300);

    m_DirExemples = m_DirChoisi + "/data_XORNew";
    if(!m_qDir->mkdir(m_DirExemples)) QMessageBox::information(this,tr( "Information"),
                                                tr("le dossier /data_XORNew existe"));
    m_qDir->cd(m_DirChoisi + "/data_XORNew_1");

    qDebug() << "m_DirExemples " << m_DirExemples;
    createExemplesFileForXORFunction(this, m_DirChoisi,  m_DirExemples, 300);

    m_DirExemples = m_DirChoisi + "/data_ORNew";
    if(!m_qDir->mkdir(m_DirExemples)) QMessageBox::information(this,tr( "Information"),
        tr(" le dossier /data_ORNew existe"));
    m_qDir->cd(m_DirChoisi + "/data_ORNew_1");

    qDebug() << "m_DirExemples " << m_DirExemples;
    createExemplesFileForORFunction(this, m_DirChoisi,  m_DirExemples, 300);

    m_DirExemples = m_DirChoisi + "/data_decimalToBCD";
    if(!m_qDir->mkdir(m_DirExemples)) QMessageBox::information(this,tr( "Information"),
                             tr(" le dossier /data_decimalToBCD existe"));
    m_qDir->cd(m_DirChoisi + "/data_decimalToBCD_1");

    qDebug() << "m_DirExemples " << m_DirExemples;
    createExemplesFileForDecimalToBCDFunction(this, m_DirChoisi,  m_DirExemples, 300);

    m_DirParam = m_DirChoisi + "/data_MNIST";
    if(!m_qDir->mkdir(m_DirParam)) QMessageBox::information(this,tr( "Information"),
                                    tr(" le dossier /data_MNIST existe"));
    m_qDir->cd(m_DirChoisi + "/data_MNIST");

    qDebug() << "m_DirExemples " << m_DirExemples;
    createParametreFileForMNISTFunction(this, m_DirParam, 5000);

}

IAdePapi_installation::~IAdePapi_installation(){};

void IAdePapi_installation::createExemplesFileForBcdToOutput(QWidget *a,QString DirLabel,
        QString DirExemple, quint32 nberOfExemples){
    /*
     On crée un fichier d'exemples pour l'entrainement d'une fonction
        "binary coded decimal (0..9) vers decimal (10 sorties)
     à partir des labels" de MNIST
    */
    quint32 magicNumber, nberOfItems;
    quint8 leLabel;
    QFile fichierLabel(DirLabel + "/train-labels-idx1-ubyte_1" );
    if(!fichierLabel.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(a,tr( "Attention "),
            tr(" Ouverture du fichier train-labels impossible "));
    } else {
        QFile fichierEx(DirExemple + "/BcdToOutput.txt");
        if(!fichierEx.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(a,tr( "Attention "),
                tr(" Ecriture du fichier BcdToOutput.txt impossible "));}
        else {
            QDataStream monLabel(&fichierLabel);
            monLabel >> magicNumber;
            monLabel >> nberOfItems;
            QTextStream monFlux(&fichierEx);
            monFlux << "nbrExemples= " << nberOfExemples << " 4 10 \n \n";
                                                // 4 entrees, 10 sorties
            for (quint32 i = 0; i<nberOfExemples;i++){
                monLabel >> leLabel;
                switch (leLabel){
                case 0:
                    monFlux << "0 0 0 0 \n 0 0 0 0 0 0 0 0 0 1 \n \n";
                    break;
                case 1: monFlux << " 0 0 0 1 \n 0 0 0 0 0 0 0 0 1 0 \n \n";
                    break;
                case 2: monFlux << " 0 0 1 0 \n 0 0 0 0 0 0 0 1 0 0 \n \n";
                    break;
                case 3: monFlux << " 0 0 1 1 \n 0 0 0 0 0 0 1 0 0 0 \n \n";
                    break;
                case 4: monFlux << " 0 1 0 0 \n 0 0 0 0 0 1 0 0 0 0 \n \n";
                    break;
                case 5: monFlux << " 0 1 0 1 \n 0 0 0 0 1 0 0 0 0 0 \n \n";
                    break;
                case 6: monFlux << " 0 1 1 0 \n 0 0 0 1 0 0 0 0 0 0 \n \n";
                    break;
                case 7: monFlux << " 0 1 1 1 \n 0 0 1 0 0 0 0 0 0 0 \n \n";
                    break;
                case 8: monFlux << " 1 0 0 0 \n 0 1 0 0 0 0 0 0 0 0 \n \n";
                    break;
                case 9: monFlux << " 1 0 0 1 \n 1 0 0 0 0 0 0 0 0 0 \n \n";
                }
            }
        fichierEx.close();
        }
    fichierLabel.close();
    }
}

void IAdePapi_installation::createExemplesFileForXORFunction(QWidget *a,
    QString DirLabel, QString DirExemple, quint32 nberOfExemples){
    /*
     On crée un fichier d'exemples pour l'entrainement d'une fonction XOR
     à partir des labels" de MNIST
    */
    quint32 magicNumber, nberOfItems;
    quint8 leLabel;
    QFile fichierLabel(DirLabel + "/train-labels-idx1-ubyte_1" );
    if(!fichierLabel.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(a,tr( "Attention "),
            tr(" Ouverture du fichier train-labels impossible "));
    } else {
        QFile fichierEx(DirExemple + "/XORNew.txt");
        if(!fichierEx.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(a,tr( "Attention "),
                tr(" Ecriture du fichier des exemples impossible "));}
        else {
            QDataStream monLabel(&fichierLabel);
            monLabel >> magicNumber;
            monLabel >> nberOfItems;
            QTextStream monFlux(&fichierEx);
            monFlux << "nbrExemples= " << nberOfExemples << " 2  1 \n \n";
                                                    // 2 entrees, 1 sorties
            for (quint32 i = 0; i<nberOfExemples;i++){
                    monLabel >> leLabel;
                    switch (leLabel){
                case 0:
                    monFlux << "0 0  \n 0  \n \n";
                    i++;
                    break;
                case 1:
                    monFlux << "0 1 \n 1 \n \n";
                    i++;
                    break;
                case 2:
                    monFlux << "1 0 \n 1 \n \n";
                    i++;
                    break;
                case 3:
                    monFlux << "1 1 \n 0 \n \n";
                    i++;
                    break;
                default: i++;
            }
        }
        fichierEx.close();
        }
    fichierLabel.close();
    }
}

void IAdePapi_installation::createExemplesFileForORFunction(QWidget *a,
    QString DirLabel, QString DirExemple, quint32 nberOfExemples){
    /*
     On crée un fichier d'exemples pour l'entra^inement d'une fonction OR
     à partir des labels" de MNIST
    */

    quint32 magicNumber, nberOfItems;
    quint8 leLabel;
    QFile fichierLabel(DirLabel + "/train-labels-idx1-ubyte_1" );
    if(!fichierLabel.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(a,tr( "Attention "),
                             tr(" Ouverture du fichier train-labels impossible "));
    } else {
        QFile fichierEx(DirExemple + "/ORNew.txt");
        if(!fichierEx.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(a,tr( "Attention "),
                tr(" Ecriture du fichier ORNew.txt impossible "));}
        else {
            QDataStream monLabel(&fichierLabel);
            monLabel >> magicNumber;
            monLabel >> nberOfItems;
            QTextStream monFlux(&fichierEx);
            monFlux << "nbrExemples= " << nberOfExemples << " 2  1 \n \n";
                                            // 2 entrees, 1 sorties
            for (quint32 i = 0; i<nberOfExemples;i++){
                monLabel >> leLabel;
                switch (leLabel){
                case 0:
                    monFlux << "0 0  \n 0  \n \n"; i++;
                    break;
                case 1: monFlux << "0 1 \n 1 \n \n"; i++;
                    break;
                case 2: monFlux << "1 0 \n 1 \n \n"; i++;
                    break;
                case 3: monFlux << "1 1 \n 1 \n \n"; i++;
                    break;
                default: i++;
                }
            }
            fichierEx.close();
        }
        fichierLabel.close();
    }
}

void IAdePapi_installation::createExemplesFileForDecimalToBCDFunction(QWidget *a,
        QString DirLabel, QString DirExemple, quint32 nberOfExemples){
    /*
     On crée un fichier d'exemples pour l'entra^inement d'une fonction
        "binary coded decimal (0..9) vers decimal (10 sorties)
     à partir des labels" de MNIST
    */

    quint32 magicNumber, nberOfItems;
    quint8 leLabel;
    QFile fichierLabel(DirLabel + "/train-labels-idx1-ubyte_1" );
    if(!fichierLabel.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(a,tr( "Attention "),
            tr(" Ouverture du fichier train-labels impossible "));
    } else {
        QFile fichierEx(DirExemple + "/decimalToBCD.txt");
        if(!fichierEx.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(a,tr( "Attention "),
                tr(" Ecriture du fichier decimalToBCD.txt impossible "));}
        else {
            QDataStream monLabel(&fichierLabel);
            monLabel >> magicNumber;
            monLabel >> nberOfItems;
            QTextStream monFlux(&fichierEx);
            monFlux << "nbrExemples= " << nberOfExemples << " 10  4 \n \n";
                                                    // 10 entrees, 4 sorties
            for (quint32 i = 0; i<nberOfExemples;i++){
                monLabel >> leLabel;
                switch (leLabel){
               case 0:
                    monFlux << " 0 0 0 0 0 0 0 0 0 1 \n 0 0 0 0 \n \n";
                    break;
                case 1: monFlux << " 0 0 0 0 0 0 0 0 1 0 \n 0 0 0 1 \n \n";
                    break;
                case 2: monFlux << " 0 0 0 0 0 0 0 1 0 0 \n 0 0 1 0 \n \n";
                    break;
                case 3: monFlux << " 0 0 0 0 0 0 1 0 0 0 \n 0 0 1 1 \n \n";
                    break;
                case 4: monFlux << " 0 0 0 0 0 1 0 0 0 0 \n 0 1 0 0 \n \n";
                    break;
                case 5: monFlux << " 0 0 0 0 1 0 0 0 0 0 \n 0 1 0 1 \n \n";
                    break;
                case 6: monFlux << " 0 0 0 1 0 0 0 0 0 0 \n 0 1 1 0 \n \n";
                    break;
                case 7: monFlux << " 0 0 1 0 0 0 0 0 0 0 \n 0 1 1 1 \n \n";
                    break;
                case 8: monFlux << " 0 1 0 0 0 0 0 0 0 0 \n 1 0 0 0 \n \n";
                    break;
                case 9: monFlux << " 1 0 0 0 0 0 0 0 0 0 \n 1 0 0 1 \n \n";
                }
            }
            fichierEx.close();
        }
        fichierLabel.close();
    }
}

void IAdePapi_installation::createParametreFileForMNISTFunction(QWidget *a,
    QString DirParam, quint32 nberOfImages){
    QFile f(DirParam + "/MNIST_7x3_14x3.txt");              //f(m_fileName);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(a,tr( "Attention "),
                            tr(" Ecriture du fichier MNIST_7x3_14x3.txt impossible "));}
    else {
        QTextStream fluxMNIST(&f);           //(&m_fileName);

        fluxMNIST << "\n" <<  "  nberOfImages= " << nberOfImages;
        fluxMNIST << "     nberOfConvolutions= " << 2 <<  "\n" ;
        fluxMNIST  << "  nberOfPixels= " <<  28 <<  "\n\n\n";

        // Convolution 1

        fluxMNIST << "   featurePadding= " << "true";
        fluxMNIST << "   stride=  " << 1;
        fluxMNIST << "       nberOfFilters=  " << 7 << "\n";
        fluxMNIST << "   filterType=  " << 3  ;
        fluxMNIST << "           maxPool= " << " true" ;
        fluxMNIST << "      RELU= " << " true" << "\n";
        fluxMNIST << "   stridePooling= " << 2;
        fluxMNIST << "         poolingPair= "  << " true";
        fluxMNIST << "\n\n\n";

        // Convolution 2

        fluxMNIST << "   featurePadding= " << "false";
        fluxMNIST << "   stride=  " << 1;
        fluxMNIST << "       nberOfFilters=  " << 14 << "\n";
        fluxMNIST << "   filterType=  " << 3  ;
        fluxMNIST << "           maxPool= " << " true" ;
        fluxMNIST << "      RELU= " << " true" << "\n";
        fluxMNIST << "   stridePooling= " << 2;
        fluxMNIST << "         poolingPair= "  << " false";
        fluxMNIST << "\n\n\n";

        f.close();
    }
}
