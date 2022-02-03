#ifndef UNIFORMDISTRIBWIN_H
#define UNIFORMDISTRIBWIN_H

#include <QDialog>
#include "world.h"

namespace Ui {
class UniformDistribWin;
}

class UniformDistribWin : public QDialog
{
    Q_OBJECT

public:
    explicit UniformDistribWin(QWidget *parent = nullptr);
    ~UniformDistribWin();

    void SetRA(double p) {_rA = p;}
    void SetRB(double p) {_rB = p;}
    void SetVA(double p) {_vA = p;}
    void SetVB(double p) {_vB = p;}
    double GetRA() {return _rA;}
    double GetRB() {return _rB;}
    double GetVA() {return _vA;}
    double GetVB() {return _vB;}

signals:
    void OK();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UniformDistribWin *ui;
    double _rA;
    double _rB;
    double _vA;
    double _vB;
};

#endif // UNIFORMDISTRIBWIN_H
