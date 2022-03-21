#ifndef COLORSELETORMODAL_H
#define COLORSELETORMODAL_H

#include <QPushButton>
#include <QWidget>

namespace Ui { class ColorSeletorModal; }

class ColorSeletorModal : public QWidget {
    Q_OBJECT
public:
    explicit ColorSeletorModal( QWidget* parent = nullptr );
    ~ColorSeletorModal();

private:
    void setCoresPredefinidas() const;
    QIcon criarIcone( const QColor& cor ) const;
    void setVariacoesCor( const QColor& cor ) const;
    QPushButton* criarBotaoComCor( const int& posicao, const QColor& cor ) const;
    QColor criarVariacaoCorBotao( const int& posicao, const QColor& cor ) const;
    qreal gerarValorDeClaridadeCor( const int& posicao ) const;
    QColor gerarCorHsvComAlpha( const QColor& cor, const qreal& alphaF ) const;
    QPalette criarPaletaBotao( const QColor& cor ) const;

    void conectarSetTextoCorBotao( QPushButton* botao, const QString& nomeCor ) const;
    QString criarTextoNomeCor( const QColor& cor ) const;

private:
    Ui::ColorSeletorModal* ui;
    int _keyCancelar;
    QString _corAnterior;
    QStringList _coresHex;

private slots:
    void setTextoEVariacaoCorPredefinida( const int& posicao );

};

#endif // COLORSELETORMODAL_H
