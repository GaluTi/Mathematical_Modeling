#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QDateTime>

#include "world.h"
#include "qcustomplot.h"
#include "uniformdistribwin.h"
#include "normaldistribwin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(world* w, QWidget *parent = nullptr);
    double t;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer* _mainTimer;
    world* _world;

    QCustomPlot* _swarmPlotter;

    UniformDistribWin* _u_window;
    NormalDistribWin* _n_window;

    void initPlotter();

private slots:
    void MousePressEvent(QMouseEvent* event);
    void onTimeChangedSlot();
    void on_startTimerButton_clicked();
    void on_addObjButton_clicked();
    void on_clearButton_clicked();
    void on_Distrib_currentTextChanged(const QString &arg1);
    void CloseUniformDistWin();
    void CloseNormalDistWin();
};
#endif // MAINWINDOW_H
