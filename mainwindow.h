#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

    QString corFundoNome();
    QString corTextoNome();
    QString passOrFail( int mode, const qreal ratio );
    void calcPercentage();
private:
    Ui::MainWindow* ui;

private slots:
    void calculateAndResult();
};
#endif // MAINWINDOW_H
