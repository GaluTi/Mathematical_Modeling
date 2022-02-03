#ifndef NORMALDISTRIBWIN_H
#define NORMALDISTRIBWIN_H

#include <QDialog>

namespace Ui {
class NormalDistribWin;
}

class NormalDistribWin : public QDialog
{
    Q_OBJECT

public:
    explicit NormalDistribWin(QWidget *parent = nullptr);
    ~NormalDistribWin();

    void SetR_Mu(double p) {_rMu = p;}
    void SetR_Sigma(double p) {_rSigma = p;}
    void SetV_Mu(double p) {_vMu = p;}
    void SetV_Sigma(double p) {_vSigma = p;}
    double GetR_Mu() {return _rMu;}
    double GetR_Sigma() {return _rSigma;}
    double GetV_Mu() {return _vMu;}
    double GetV_Sigma() {return _vSigma;}

signals:
    void OK();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NormalDistribWin *ui;

    double _rMu;
    double _rSigma;
    double _vMu;
    double _vSigma;
};

#endif // NORMALDISTRIBWIN_H
