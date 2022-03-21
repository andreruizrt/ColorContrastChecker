#include "include/configavancadas/colorseletormodal.h"
#include "ui_colorseletormodal.h"

#include <QGraphicsProxyWidget>

#include <include/contrastchecker.h>

namespace  {
constexpr const int QTD_TONS = 9;
constexpr const int BUTTON_WIDTH  = 40;
constexpr const int IMAGE_WIDTH = 800;
constexpr const int BUTTON_SPACE_BETWEEN = 3;
constexpr const int IMAGE_HEIGHT = 512;
constexpr const int ELLIPSE_WIDTH = 300;
constexpr const int ELLIPSE_HEIGHT= 300;
constexpr const int ICONE_CORES_PREDEFINIDAS_WIDTH = 20;
constexpr const int ICONE_CORES_PREDEFINIDAS_HEIGHT = 20;
constexpr const int POSICAO_PRIMEIRO_BUTTON = -150;
constexpr const int PUSHBUTTON_WIDTH = 318;
constexpr const int QGRAPHICPROXY_HEIGHT = 38;
constexpr const int QGRAPHICPROXY_SPACING_WIDGET = 50;
constexpr const char* QGRAPHICVIEW_STYLESHEET = "padding: 20px; border-top: 1px solid #ACACAC; background: transparent;";
constexpr const char* COLOR_PREVIEW_STYLESHEET = "background: %0; border: 3px solid #ACACAC; border-radius: 15px;";
constexpr const qreal QGRAPHICPROXY_POS_Y = 0.0;
constexpr const qreal ROTATION_ANGLE = 90.0;
constexpr const qreal MULTIPLICADOR_TONALIDADE = 0.1;
constexpr const qreal TONALIDADE_INICIAL = 0.1;
constexpr const qreal SATURACAO = 0.9;
const QStringList CORES_PREDEFINIDAS = {
    "#78909C",
    "#BDBDBD",
    "#8D6E63",
    "#E76A42",
    "#F0A425",
    "#F8C927",
    "#FFEE58",
    "#D4E157",
    "#9CCC65",
    "#69BB6A",
    "#58A89A",
    "#65C8DB",
    "#52B7F6",
    "#42A5F5",
    "#5C8BC0",
    "#7E57C2",
    "#AD5ABC",
    "#E4587A",
    "#E55150"
};
}

ColorSeletorModal::ColorSeletorModal( QWidget* parent ) :
    ui( new Ui::ColorSeletorModal ),
    _coresHex( CORES_PREDEFINIDAS ) {
    ui->setupUi( this );

    this->setWindowModality( Qt::ApplicationModal );
    this->setFixedSize( parent->size() );

    ui->wdgColorSeletorCenterModal->setAttribute( Qt::WA_NoSystemBackground );

    QObject::connect( ui->lwdCoresPadrao, &QListWidget::currentRowChanged,
                      this, &ColorSeletorModal::setTextoEVariacaoCorPredefinida );

    setCoresPredefinidas();
    setVariacoesCor( QColor( "#BBBBBB" ) );
}

ColorSeletorModal::~ColorSeletorModal() {
    delete ui;
}

void ColorSeletorModal::setCoresPredefinidas() const {
    ui->lwdCoresPadrao->clear();

    for ( QString colorName : _coresHex ) {
        QColor color( colorName );
        QIcon icon = criarIcone( color );

        QListWidgetItem* item = new QListWidgetItem( icon, nullptr );
        item->setSizeHint( QSize( ICONE_CORES_PREDEFINIDAS_WIDTH, ICONE_CORES_PREDEFINIDAS_HEIGHT ) );
        ui->lwdCoresPadrao->addItem( item );
    }
}

QIcon ColorSeletorModal::criarIcone( const QColor& cor ) const {
    QImage image( IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_ARGB32_Premultiplied );
    image.fill( Qt::transparent );

    QPainter painter( &image );
    QBrush brush( cor );
    painter.setBrush( brush );
    painter.drawEllipse( 0, 0, ELLIPSE_WIDTH, ELLIPSE_HEIGHT );
    QPixmap pixmap;

    pixmap.convertFromImage( image );
    QIcon icon( pixmap );

    return icon;
}

void ColorSeletorModal::setVariacoesCor( const QColor& cor ) const {
    qreal qGraphicProxyPosX = POSICAO_PRIMEIRO_BUTTON;
    QGraphicsScene* view = new QGraphicsScene();

    ui->gvwVariacaoCor->items().clear();
    ui->gvwVariacaoCor->setStyleSheet( QGRAPHICVIEW_STYLESHEET );

    for ( int i = 0; i <= QTD_TONS; i++ ) {
        QColor color = criarVariacaoCorBotao( i, cor );
        ContrastChecker contrastChecker;
        bool passou = contrastChecker.calcRatio( color.name() );

        if ( !passou ) {
            QPushButton* button = criarBotaoComCor( i, cor );
            QGraphicsProxyWidget* qGraphicsProxyWidget = view->addWidget( button );

            qGraphicsProxyWidget->resize( PUSHBUTTON_WIDTH - QGRAPHICPROXY_SPACING_WIDGET, QGRAPHICPROXY_HEIGHT );
            qGraphicsProxyWidget->setPos( qGraphicProxyPosX, QGRAPHICPROXY_POS_Y );
            qGraphicsProxyWidget->setRotation( ROTATION_ANGLE );

            ui->gvwVariacaoCor->setScene( view );

            qGraphicProxyPosX += BUTTON_WIDTH + BUTTON_SPACE_BETWEEN;
        }
    }
}

QPushButton* ColorSeletorModal::criarBotaoComCor( const int& posicao, const QColor& cor ) const {
    QPushButton* botao = new QPushButton();
    botao->setAutoFillBackground( true );

    QColor corBotao = criarVariacaoCorBotao( posicao, cor );
    botao->setPalette( criarPaletaBotao( corBotao ) );
    botao->setText( criarTextoNomeCor( corBotao ) );
    conectarSetTextoCorBotao( botao, corBotao.name() );

    return botao;
}

QColor ColorSeletorModal::criarVariacaoCorBotao( const int& posicao, const QColor& cor ) const {
    qreal alphaF = gerarValorDeClaridadeCor( posicao );
    return gerarCorHsvComAlpha( cor, alphaF );
}

qreal ColorSeletorModal::gerarValorDeClaridadeCor( const int& posicao ) const {
    return posicao == 0 ? ( MULTIPLICADOR_TONALIDADE / 2 + TONALIDADE_INICIAL ) : MULTIPLICADOR_TONALIDADE* posicao + TONALIDADE_INICIAL;
}

QColor ColorSeletorModal::gerarCorHsvComAlpha( const QColor& cor, const qreal& alphaF ) const {
    QColor corHsv = cor.toHsv();
    corHsv.setHsvF( corHsv.hueF(), SATURACAO, alphaF );

    return corHsv;
}

QPalette ColorSeletorModal::criarPaletaBotao( const QColor& cor ) const {
    QPalette paletaButton;
    paletaButton.setColor( QPalette::Button, cor );
    paletaButton.setColor( QPalette::ButtonText, Qt::black );

    return paletaButton;
}

void ColorSeletorModal::conectarSetTextoCorBotao( QPushButton* botao, const QString& nomeCor ) const {
    QObject::connect( botao, &QPushButton::clicked, this, [this, nomeCor] {
//        setColorName( nomeCor );
    } );
}

QString ColorSeletorModal::criarTextoNomeCor( const QColor& cor ) const {
    QString nomeCor = cor.name();
    return nomeCor.toUpper();
}

void ColorSeletorModal::setTextoEVariacaoCorPredefinida( const int& posicao ) {
//    setColorName( _coresHex.at( posicao ) );
    setVariacoesCor( _coresHex.at( posicao ) );
}
