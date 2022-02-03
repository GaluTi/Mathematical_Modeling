#include "normaldistribwin.h"
#include "ui_normaldistribwin.h"
#include <QString>
#include <QMessageBox>

NormalDistribWin::NormalDistribWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NormalDistribWin)
{
    ui->setupUi(this);
    _rMu = 0.0;
    _rSigma = 0.0;
    _vMu = 0.0;
    _vSigma = 0.0;
    QString str = "%1";
    ui->coordMu->setText(str.arg(_rMu));
    ui->coordSigma->setText(str.arg(_rSigma));
    ui->velMu->setText(str.arg(_vMu));
    ui->velSigma->setText(str.arg(_vSigma));
}

NormalDistribWin::~NormalDistribWin()
{
    delete ui;
}

void NormalDistribWin::on_pushButton_clicked()
{
    QString rMu = ui->coordMu->text();
    QString rSigma = ui->coordSigma->text();
    QString vMu = ui->velMu->text();
    QString vSigma = ui->velSigma->text();
    if(rMu.isEmpty()|| rSigma.isEmpty() || vMu.isEmpty() || vSigma.isEmpty())
        QMessageBox::warning(this, "Warning!", "Select all parameters!");
    else
    {
        SetR_Mu(rMu.toDouble());
        SetR_Sigma(rSigma.toDouble());
        SetV_Mu(vMu.toDouble());
        SetV_Sigma(vSigma.toDouble());
        emit OK();
    }
}

