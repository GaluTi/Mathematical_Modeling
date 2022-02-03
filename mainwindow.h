#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QDateTime>
#include <QColor>
#include <QChar>

#include "world.h"
#include "qcustomplot.h"
#include "uniformdistribwin.h"
#include "normaldistribwin.h"

#include "coreLib.h"
#include "orbitLib.h"

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
    int cluster_counter;
    QColor inverse_color;
    QVector<QPair<int, int>> GraphDistribution;
    QVector<int> ClusterDistribution;
    QVector<int> SatClusterDistribution;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer* _mainTimer;
    world* _world;

    QCustomPlot* _swarmPlotter;
    QCustomPlot* _swarmPlotterXZ;
    QCustomPlot* _swarmPlotterYZ;

    UniformDistribWin* _u_window;
    NormalDistribWin* _n_window;

    void initPlotter();
    void add_graph(QColor color, double radius);
    void plot_initialisation();

private slots:
    void onTimeChangedSlot();
    void on_startTimerButton_clicked();
    void on_addObjButton_clicked();
    void on_CreateCluster_clicked();
    void on_clearButton_clicked();
    void on_Distrib_currentTextChanged(const QString &arg1);
    void CloseUniformDistWin();
    void CloseNormalDistWin();
};
#endif // MAINWINDOW_H
