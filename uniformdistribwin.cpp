#include "uniformdistribwin.h"
#include "ui_uniformdistribwin.h"
#include <QString>
#include <QMessageBox>

UniformDistribWin::UniformDistribWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UniformDistribWin)
{
    ui->setupUi(this);
    _rA = 0.0;
    _rB = 0.0;
    _vA = 0.0;
    _vB = 0.0;
    QString str = "%1";
    ui->coordA->setText(str.arg(_rA));
    ui->coordB->setText(str.arg(_rB));
    ui->velA->setText(str.arg(_vA));
    ui->velB->setText(str.arg(_vB));
}

UniformDistribWin::~UniformDistribWin()
{
    delete ui;
}

void UniformDistribWin::on_pushButton_clicked()
{
    QString rA = ui->coordA->text();
    QString rB = ui->coordB->text();
    QString vA = ui->velA->text();
    QString vB = ui->velB->text();
    if(rA.toDouble() == 0.0 || rB.toDouble() == 0.0 || vA.toDouble() == 0.0 || vB.toDouble() == 0.0)
        QMessageBox::warning(this, "Warning!", "Select all parameters!");
    else
    {
        SetRA(rA.toDouble());
        SetRB(rB.toDouble());
        SetVA(vA.toDouble());
        SetVB(vB.toDouble());
        emit OK();
    }
}
