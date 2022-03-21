#ifndef CONFIGAVANCADASWIDGET_H
#define CONFIGAVANCADASWIDGET_H

#include <QButtonGroup>
#include <QPushButton>

#include <odin-line-edit-label/odinlineeditlabel.h>

#include <caixa-core-model/configavancadas/cores/configuracaocormodel.h>
#include <caixa-core-controller/configavancadas/paletasistemacontroller.h>

#include "menu/abstractmenuwidget.h"

using caixa::core::controller::PaletaSistemaController;
using caixa::core::model::ConfiguracaoCorModel;

namespace Ui { class ConfigAvancadasWidget; }
class ConfigAvancadasWidget : public AbstractMenuWidget {
    Q_OBJECT
public:
    explicit ConfigAvancadasWidget( QWidget* parent = nullptr );
    ~ConfigAvancadasWidget();

    void onStartOpcao() override;
    void reajustFocus() override;
    bool beforeExit() override;

private:
    void enableComponents( const bool& state );
    void setButtonBackgroundColor( QPushButton* button, const QString& color );
    void loadConfigAndUpdateButtons();
    void carregarPaletteNoApp() const;
    bool isPersonalizado() const;
    QString escolherCor( const QPushButton* button );
    QString getButtonTextColor( const QString& colorName );
    void setButtonBackgroundAndTextColor( QPushButton* button, const QString& color );
    void hideBtnDefinirCores() const;
    void atualizarComponentes() const;
    void salvarAndTestar();

private:
    Ui::ConfigAvancadasWidget* ui;
    QButtonGroup* _buttonGroup;
    bool _waitClose;
    ConfiguracaoCorModel& _configuracaoCorModel;
    PaletaSistemaController _paletaSistemaController;

private slots:
    void onCheckBoxChange();
    void onClickPadraoButton();
    void onClickSucessoButton();
    void onClickFalhaButton();
    void onClickAlertaButton();
    void onClickSalvarButton();
    void onButtonTestarSucessoClicked();
    void onButtonTestarErroClicked();
};

#endif // CONFIGAVANCADASWIDGET_H
