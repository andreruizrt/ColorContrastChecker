#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDebug>

#include "include/contrastchecker.h"
#include "include/configavancadas/colorseletormodal.h"

MainWindow::MainWindow( QWidget* parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ) {
    ui->setupUi( this );

    QObject::connect( ui->btnCheck, SIGNAL(clicked()), this, SLOT(calculateAndResult()) );
    ColorSeletorModal* colorSeletorModal = new ColorSeletorModal( this );
    colorSeletorModal->show();
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::corFundoNome() {
    return ui->ledFundo->text();
}

QString MainWindow::corTextoNome() {
    return ui->ledTexto->text();
}

void MainWindow::calculateAndResult() {
    ContrastChecker contrastChecker;

    qreal texto = contrastChecker.luminance( corTextoNome() );
    qreal fundo = contrastChecker.luminance( corFundoNome() );

    qreal ratio = texto > fundo
                  ? ( ( fundo + 0.05 ) / ( texto + 0.05 ) )
                  : ( ( texto + 0.05 ) / ( fundo + 0.05 ) );

    qInfo() << "[RATIO]" << QString::number( ratio );

    ui->aaLargeTxt->setText( passOrFail( 0, ratio ) );
    ui->aaSmallTxt->setText( passOrFail( 1, ratio ) );
    ui->aaaLargeTxt->setText( passOrFail( 2, ratio ) );
    ui->aaaSmallTxt->setText( passOrFail( 3, ratio ) );

    calcPercentage();
}

QString MainWindow::passOrFail( int mode, const qreal ratio ) {
    switch ( mode ) {
        case 0:
            return ratio < 0.33333 ? "PASS" : "FAIL";
        case 1:
            return ratio < 0.22222 ? "PASS" : "FAIL";
        case 2:
            return ratio < 0.22222 ? "PASS" : "FAIL";
        case 3:
            return ratio < 0.14285 ? "PASS" : "FAIL";
        default:
            return "ERRO";
    }
}

void MainWindow::calcPercentage() {
    QStringList result;
    int counter = 0;
    result << ui->aaLargeTxt->text() << ui->aaSmallTxt->text()
           << ui->aaaLargeTxt->text() << ui->aaaSmallTxt->text();

    for ( QString texto: result ) {
        if ( texto == "PASS" ) counter++;
    }

    QString resultado = QString::number( ( counter / 4 ) * 100 );
    resultado.append( "%" );
    ui->lblPercentage->setText( resultado );
}
