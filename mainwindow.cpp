#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cluster_counter = 0;
    this->_world = new world();

    this->_mainTimer = new QTimer();
    connect(this->_mainTimer, SIGNAL(timeout()), this, SLOT(onTimeChangedSlot()));

    //this->initPlotter();
    //connect(this->_swarmPlotter, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(MousePressEvent(QMouseEvent*)));
    this->_swarmPlotter = new QCustomPlot(this);
    ui->gridLayoutXY->addWidget(this->_swarmPlotter);

    this->_swarmPlotterXZ = new QCustomPlot(this);
    ui->gridLayoutXZ->addWidget(this->_swarmPlotterXZ);

    this->_swarmPlotterYZ = new QCustomPlot(this);
    ui->gridLayoutYZ->addWidget(this->_swarmPlotterYZ);

    add_graph(QColor(255, 0, 0), 40.0);
    ClusterDistribution.push_back(1);
    QPair<int, int> p = qMakePair(0, ClusterDistribution.size()-1);
    GraphDistribution.push_back(p);
    _world->addObject(new worldObject(0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 6*1e+24));
    this->_swarmPlotter->graph(0)->addData(0.0, 0.0);
    this->_swarmPlotter->replot();
    this->_swarmPlotterXZ->graph(0)->addData(0.0, 0.0);
    this->_swarmPlotterXZ->replot();
    this->_swarmPlotterYZ->graph(0)->addData(0.0, 0.0);
    this->_swarmPlotterYZ->replot();

    this->_swarmPlotter->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    this->_swarmPlotterXZ->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    this->_swarmPlotterYZ->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    //
    this->_u_window = new UniformDistribWin();
    this->_u_window->setWindowTitle("Uniform Distribution");
    this->_u_window->resize(350, 180);
    this->_u_window->setWindowIcon(QIcon("AppIcon"));
    connect(this->_u_window, SIGNAL(OK()), this, SLOT(CloseUniformDistWin()));

    this->_n_window = new NormalDistribWin();
    this->_n_window->setWindowTitle("Normal Distribution");
    this->_n_window->resize(350, 180);
    this->_n_window->setWindowIcon(QIcon("AppIcon"));
    connect(this->_n_window, SIGNAL(OK()), this, SLOT(CloseNormalDistWin()));
}

MainWindow::MainWindow(world* w, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cluster_counter = 0;
    this->_world = w;

    this->_mainTimer = new QTimer();
    connect(this->_mainTimer, SIGNAL(timeout()), this, SLOT(onTimeChangedSlot()));

    //this->initPlotter();
    //connect(this->_swarmPlotter, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(MousePressEvent(QMouseEvent*)));
    this->_swarmPlotter = new QCustomPlot(this);
    ui->gridLayoutXY->addWidget(this->_swarmPlotter);

    this->_swarmPlotterXZ = new QCustomPlot(this);
    ui->gridLayoutXZ->addWidget(this->_swarmPlotterXZ);

    this->_swarmPlotterYZ = new QCustomPlot(this);
    ui->gridLayoutYZ->addWidget(this->_swarmPlotterYZ);

    add_graph(QColor(255, 0, 0), 20.0);
    ClusterDistribution.push_back(1);
    QPair<int, int> p = qMakePair(0, ClusterDistribution.size()-1);
    GraphDistribution.push_back(p);
    _world->addObject(new worldObject(0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 6*1e+24));
    this->_swarmPlotter->graph(0)->addData(0.0, 0.0);
    this->_swarmPlotter->replot();
    this->_swarmPlotterXZ->graph(0)->addData(0.0, 0.0);
    this->_swarmPlotterXZ->replot();
    this->_swarmPlotterYZ->graph(0)->addData(0.0, 0.0);
    this->_swarmPlotterYZ->replot();

    this->_swarmPlotter->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    this->_swarmPlotterXZ->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    this->_swarmPlotterYZ->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    this->_u_window = new UniformDistribWin();
    this->_u_window->setWindowTitle("Uniform Distribution");
    this->_u_window->resize(350, 180);
    this->_u_window->setWindowIcon(QIcon("AppIcon"));
    connect(this->_u_window, SIGNAL(OK()), this, SLOT(CloseUniformDistWin()));

    this->_n_window = new NormalDistribWin();
    this->_n_window->setWindowTitle("Normal Distribution");
    this->_n_window->resize(350, 180);
    this->_n_window->setWindowIcon(QIcon("AppIcon"));
    connect(this->_n_window, SIGNAL(OK()), this, SLOT(CloseNormalDistWin()));
}

void MainWindow::initPlotter()
{
    this->_swarmPlotter = new QCustomPlot(this);
    //ui->gridLayout->addWidget(this->_swarmPlotter);

    this->_swarmPlotter->addGraph();

    //this->_swarmPlotter->graph(0)->setPen(QColor(50, 50, 50, 255));
    this->_swarmPlotter->graph(0)->setPen(QColor(255,0,0,255));
    this->_swarmPlotter->graph(0)->setBrush(QColor(50, 50, 50, 255));

    this->_swarmPlotter->graph(0)->setLineStyle(QCPGraph::lsNone);
    this->_swarmPlotter->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    this->_swarmPlotter->graph(0)->setName("Swarm Data");

    this->_swarmPlotter->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
}

void MainWindow::plot_initialisation()
{
    this->_swarmPlotter->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
}

void MainWindow::add_graph(QColor color, double radius)
{
    QString str = "Cluster %1";
    this->_swarmPlotter->addGraph();
    this->_swarmPlotter->graph(cluster_counter)->setPen(color);
    this->_swarmPlotter->graph(cluster_counter)->setBrush(color);
    this->_swarmPlotter->graph(cluster_counter)->setLineStyle(QCPGraph::lsNone);
    this->_swarmPlotter->graph(cluster_counter)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, radius));
    this->_swarmPlotter->graph(cluster_counter)->setName(str.arg(cluster_counter+1));

    this->_swarmPlotterXZ->addGraph();
    this->_swarmPlotterXZ->graph(cluster_counter)->setPen(color);
    this->_swarmPlotterXZ->graph(cluster_counter)->setBrush(color);
    this->_swarmPlotterXZ->graph(cluster_counter)->setLineStyle(QCPGraph::lsNone);
    this->_swarmPlotterXZ->graph(cluster_counter)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, radius));
    this->_swarmPlotterXZ->graph(cluster_counter)->setName(str.arg(cluster_counter+1));

    this->_swarmPlotterYZ->addGraph();
    this->_swarmPlotterYZ->graph(cluster_counter)->setPen(color);
    this->_swarmPlotterYZ->graph(cluster_counter)->setBrush(color);
    this->_swarmPlotterYZ->graph(cluster_counter)->setLineStyle(QCPGraph::lsNone);
    this->_swarmPlotterYZ->graph(cluster_counter)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, radius));
    this->_swarmPlotterYZ->graph(cluster_counter)->setName(str.arg(cluster_counter+1));
    ++cluster_counter;
}

void MainWindow::onTimeChangedSlot()
{
    std::cout << "Timer changed! " << std::endl;

    for(auto i : this->_world->GetObjects())
        i->SetUpdate(false);

    for(int i = 1; i < cluster_counter; ++i)
    {
        this->_swarmPlotter->graph(i)->data()->clear();
        this->_swarmPlotterXZ->graph(i)->data()->clear();
        this->_swarmPlotterYZ->graph(i)->data()->clear();
    }
    double t_now = QDateTime::currentMSecsSinceEpoch();
    this->_world->Update(t_now); //Ms

    int M = 1;
    int K = 0;
    for(int i = 1; i < cluster_counter; ++i)
    {
        QPair<int, int> current_graph = GraphDistribution[i];
        if(current_graph.first == 0)
        {
            int N = ClusterDistribution[current_graph.second];
            for(int j = 1; j <= N; ++j)
            {
                this->_swarmPlotter->graph(i)->addData(this->_world->GetObjects()[M]->GetCoord().x(), this->_world->GetObjects()[M]->GetCoord().y());
                this->_swarmPlotterXZ->graph(i)->addData(this->_world->GetObjects()[M]->GetCoord().x(), this->_world->GetObjects()[M]->GetCoord().z());
                this->_swarmPlotterYZ->graph(i)->addData(this->_world->GetObjects()[M]->GetCoord().y(), this->_world->GetObjects()[M]->GetCoord().z());
                M++;
            }
        }
        else if(current_graph.first == 1)
        {
            int N = SatClusterDistribution[current_graph.second];
            std::cout << N << std::endl;
            for(int j = 1; j <= N; ++j)
            {
                cSatellite sat_n = this->_world->GetSats()[K].first;
                std::cout << "sat take\n";
                double sat_time = this->_world->GetSats()[K].second;
                std::cout << "sat time " << sat_time << " t now " << t_now << " t_now - sat_time = " << (t_now-sat_time)/600.0 <<std::endl;
                cEciTime eci = sat_n.PositionEci(10*((t_now-sat_time)/60000.0));
                std::cout << "sat update " << sat_time << std::endl;
                QVector3D r(eci.Position().m_x, eci.Position().m_y, eci.Position().m_z);
                QVector3D r_model(this->_world->GetObjects()[K+1]->GetCoord().x(), this->_world->GetObjects()[K+1]->GetCoord().y(), this->_world->GetObjects()[K+1]->GetCoord().z());
                this->_world->_energy_norm += (r_model-r).length();

                this->_swarmPlotter->graph(i)->addData(r.x(), r.y());
                this->_swarmPlotterXZ->graph(i)->addData(r.x(), r.z());
                this->_swarmPlotterYZ->graph(i)->addData(r.y(), r.z());
                K++;
            }
        }
    }

    /*int M = 0;
    for(int i = 1; i < ClusterDistribution.size(); ++i)
    {
        int N = ClusterDistribution[i];
        for(int j = 1; j <= N; ++j)
        {
            this->_swarmPlotter->graph(i)->addData(this->_world->GetObjects()[M+1]->GetCoord().x(), this->_world->GetObjects()[M+1]->GetCoord().y());
            this->_swarmPlotterXZ->graph(i)->addData(this->_world->GetObjects()[M+1]->GetCoord().x(), this->_world->GetObjects()[M+1]->GetCoord().z());
            this->_swarmPlotterYZ->graph(i)->addData(this->_world->GetObjects()[M+1]->GetCoord().y(), this->_world->GetObjects()[M+1]->GetCoord().z());
            M++;
        }
    }*/
    this->_swarmPlotter->replot();
    this->_swarmPlotterXZ->replot();
    this->_swarmPlotterYZ->replot();
    ui->EnergyNorm->setText(QString::number(this->_world->_energy_norm));
}

MainWindow::~MainWindow()
{
    delete _world;
    delete ui;
}


void MainWindow::on_startTimerButton_clicked()
{
    if(!this->_mainTimer->isActive())
    {
        this->_mainTimer->setInterval(1);
        this->_mainTimer->start();


        //this->_world->Update(this->_world->Time());
        this->t = QDateTime::currentMSecsSinceEpoch(); //Ms
        this->_world->Update(t);
        for(int i = 0; i < this->_world->GetSats().size(); ++i)
        {
            this->_world->_sats[i].second = t;
        }
        std::cout << "Timer started! " << std::endl;

    }
    else
    {
        this->_mainTimer->stop();
        std::cout << "Timer stopped! " << std::endl;

    }

}


void MainWindow::on_addObjButton_clicked()
{
    if(cluster_counter == 1)
        QMessageBox::warning(this, "Warning!", "Firstly, create new cluster");
    else
    {
        if(this->_world != nullptr)
        {
            if(ui->Distrib->currentText() == "-")
            {
                if((ui->x->text() == "" || ui->y->text() == "" || ui->z->text() == "" || ui->vx->text() == "" || ui->vy->text() == "" || ui->vz->text() == "") && ui->TLE->toPlainText() == "")
                    QMessageBox::warning(this, "Warning!", "Select Distribution or Сoordinates with Velocity or TLE");
                else if(ui->TLE->toPlainText() != "")
                {
                    this->add_graph(inverse_color, 3);
                    SatClusterDistribution.push_back(0);
                    GraphDistribution.push_back(qMakePair(1, SatClusterDistribution.size()-1));
                    QString str_win = ui->TLE->toPlainText();
                    std::string str = str_win.toStdString();
                    std::string str1;
                    std::string str2;
                    std::string str3;
                    std::istringstream input(str);
                    while(std::getline(input, str1))
                    {
                            std::getline(input, str2);
                            std::getline(input, str3);

                            // Create a TLE object using the data above
                            cTle tle_n(str1, str2, str3);

                            // Create a satellite object from the TLE object
                            cSatellite sat_n(tle_n);
                            this->_world->addSat(sat_n);
                            std::cout << "New sat\n";
                            SatClusterDistribution.back()++;

                            // Get the position of the satellite at time "mpe"
                            cEciTime eci = sat_n.PositionEci(0);

                            QVector3D r(eci.Position().m_x, eci.Position().m_y, eci.Position().m_z);
                            QVector3D v(eci.Velocity().m_x, eci.Velocity().m_y, eci.Velocity().m_z);
                            this->_world->addObject(new worldObject(this->_world->Num(), r, v, 1e+2));
                            ClusterDistribution.back()++;


                            this->_swarmPlotter->graph(cluster_counter-2)->addData(r.x(), r.y());
                            this->_swarmPlotter->replot();
                            this->_swarmPlotterXZ->graph(cluster_counter-2)->addData(r.x(), r.z());
                            this->_swarmPlotterXZ->replot();
                            this->_swarmPlotterYZ->graph(cluster_counter-2)->addData(r.y(), r.z());
                            this->_swarmPlotterYZ->replot();
                            ui->Num->setText(QString::number(this->_world->GetSats().size()));
                    }
                    ui->TLE->clear();
                }
                else
                {
                    double x = (ui->x->text()).toDouble(); double y = (ui->y->text()).toDouble(); double z = (ui->z->text()).toDouble();
                    double vx = (ui->vx->text()).toDouble(); double vy = (ui->vy->text()).toDouble(); double vz = (ui->vz->text()).toDouble();
                    QVector3D r(x, y, z);
                    QVector3D v(vx, vy, vz);
                    this->_world->addObject(new worldObject(this->_world->Num(), r, v, 1e+2));
                    ClusterDistribution.back()++;
                    this->_swarmPlotter->graph(cluster_counter-1)->addData(r.x(), r.y());
                    this->_swarmPlotter->replot();
                    this->_swarmPlotterXZ->graph(cluster_counter-1)->addData(r.x(), r.z());
                    this->_swarmPlotterXZ->replot();
                    this->_swarmPlotterYZ->graph(cluster_counter-1)->addData(r.y(), r.z());
                    this->_swarmPlotterYZ->replot();
                    ui->Num->setText(QString::number(this->_world->GetObjects().size()-1));
                }
            }
            else if(ui->Distrib->currentText() == "Uniform Distribution")
            {
                if(this->_u_window != nullptr)
                {
                    if(this->_u_window->GetRA() == this->_u_window->GetRB() || this->_u_window->GetVA() == this->_u_window->GetVB())
                        QMessageBox::warning(this, "Warning!", "Don`t select parameter A equal to B");
                    else if(this->_u_window->GetRA() > this->_u_window->GetRB() || this->_u_window->GetVA() > this->_u_window->GetVB())
                        QMessageBox::warning(this, "Warning!", "Select parameter A greater then B");
                    else
                    {
                        int N = ui->NumPoints->text().toInt();
                        if(N == 0 || N == 1)
                        {
                            N = 1;
                            if(this->_world->_rand_r.size() > this->_world->_count_r+3*N && this->_world->_rand_v.size() > this->_world->_count_v+3*N)
                            {
                                QVector3D r(this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++));
                                QVector3D v(this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++));

                                this->_world->addObject(new worldObject(this->_world->Num(), r, v, 1e+2));
                                ClusterDistribution.back()++;
                                this->_swarmPlotter->graph(cluster_counter-1)->addData(r.x(), r.y());
                                this->_swarmPlotter->replot();
                                this->_swarmPlotterXZ->graph(cluster_counter-1)->addData(r.x(), r.z());
                                this->_swarmPlotterXZ->replot();
                                this->_swarmPlotterYZ->graph(cluster_counter-1)->addData(r.y(), r.z());
                                this->_swarmPlotterYZ->replot();
                                ui->Num->setText(QString::number(this->_world->GetObjects().size()-1));
                            }
                        }
                        if(N <= 200)
                        {
                            if(this->_world->_rand_r.size() > this->_world->_count_r+3*N && this->_world->_rand_v.size() > this->_world->_count_v+3*N)
                            {
                                for(int i = 0; i < N; ++i)
                                {
                                    QVector3D r(this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++));
                                    QVector3D v(this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++));

                                    this->_world->addObject(new worldObject(this->_world->Num(), r, v, 1e+2));
                                    ClusterDistribution.back()++;
                                    this->_swarmPlotter->graph(cluster_counter-1)->addData(r.x(), r.y());
                                    this->_swarmPlotterXZ->graph(cluster_counter-1)->addData(r.x(), r.z());
                                    this->_swarmPlotterYZ->graph(cluster_counter-1)->addData(r.y(), r.z());
                                }
                                this->_swarmPlotter->replot();
                                this->_swarmPlotterXZ->replot();
                                this->_swarmPlotterYZ->replot();
                                ui->Num->setText(QString::number(this->_world->GetObjects().size()-1));
                            }
                            else
                                QMessageBox::warning(this, "Warning!", "Need another generate of numbers");
                        }
                        else
                            QMessageBox::warning(this, "Warning!", "Select N <= 200");
                    }
                }
                else
                    QMessageBox::warning(this, "Warning!", "Distribution parameters does not exist!/n Don`t close the <Uniform Distribution> window but push <OK> button>");
            }
            else if(ui->Distrib->currentText() == "Normal Distribution")
            {
                if(this->_n_window != nullptr)
                {
                    if(this->_n_window->GetR_Sigma() < 0 || this->_n_window->GetV_Sigma() < 0)
                        QMessageBox::warning(this, "Warning!", "Select Sigma > 0");
                    else
                    {
                        int N = ui->NumPoints->text().toInt();
                        if(N == 0 || N == 1)
                        {
                            N = 1;
                            if(this->_world->_rand_r.size() > this->_world->_count_r+3*N && this->_world->_rand_v.size() > this->_world->_count_v+3*N)
                            {
                                QVector3D r(this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++));
                                QVector3D v(this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++));

                                this->_world->addObject(new worldObject(this->_world->Num(), r, v, 1e+2));
                                ClusterDistribution.back()++;
                                this->_swarmPlotter->graph(cluster_counter-1)->addData(r.x(), r.y());
                                this->_swarmPlotter->replot();
                                this->_swarmPlotterXZ->graph(cluster_counter-1)->addData(r.x(), r.z());
                                this->_swarmPlotterXZ->replot();
                                this->_swarmPlotterYZ->graph(cluster_counter-1)->addData(r.y(), r.z());
                                this->_swarmPlotterYZ->replot();
                                ui->Num->setText(QString::number(this->_world->GetObjects().size()-1));
                            }
                        }
                        if(N <= 200)
                        {
                            if(this->_world->_rand_r.size() > this->_world->_count_r+3*N && this->_world->_rand_v.size() > this->_world->_count_v+3*N)
                            {
                                for(int i = 0; i < N; ++i)
                                {
                                    add_graph(QColor(2*cluster_counter, 2*cluster_counter, 2*cluster_counter), 4);
                                    QVector3D r(this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++));
                                    QVector3D v(this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++));

                                    this->_world->addObject(new worldObject(this->_world->Num(), r, v, 1e+2));
                                    ClusterDistribution.back()++;
                                    this->_swarmPlotter->graph(cluster_counter-1)->addData(r.x(), r.y());
                                    this->_swarmPlotterXZ->graph(cluster_counter-1)->addData(r.x(), r.z());
                                    this->_swarmPlotterYZ->graph(cluster_counter-1)->addData(r.y(), r.z());
                                }
                                this->_swarmPlotter->replot();
                                this->_swarmPlotterXZ->replot();
                                this->_swarmPlotterYZ->replot();
                                ui->Num->setText(QString::number(this->_world->GetObjects().size()-1));
                            }
                            else
                                QMessageBox::warning(this, "Warning!", "Need another generate of numbers");
                        }
                        else
                            QMessageBox::warning(this, "Warning!", "Select N <= 200");
                    }
                }
                else
                    QMessageBox::warning(this, "Warning!", "Distribution parameters does not exist!/n Don`t close the <Normal Distribution> window but push <OK> button>");
            }
        }
    }
}

void MainWindow::on_CreateCluster_clicked()
{
    if(ui->ClusterColorR->text() == "" || ui->ClusterColorG->text() == "" || ui->ClusterColorB->text() == "")
        QMessageBox::warning(this, "Warning!", "Set Color!");
    else
    {
        int R = (ui->ClusterColorR->text()).toInt();
        int G = (ui->ClusterColorG->text()).toInt();
        int B = (ui->ClusterColorB->text()).toInt();
        add_graph(QColor(R, G, B), 3);
        inverse_color = {255 - R, 255 - G, 255 - B};
        ClusterDistribution.push_back(0);
        QPair<int, int> p = qMakePair(0, ClusterDistribution.size()-1);
        GraphDistribution.push_back(p);
        QMessageBox::information(this, "New Cluster", "Success!");
    }
}

void MainWindow::on_clearButton_clicked()
{
    ui->x->clear();
    ui->y->clear();
    ui->z->clear();
    ui->vx->clear();
    ui->vy->clear();
    ui->vz->clear();
    ui->Num->clear();
    ui->EnergyNorm->clear();
    _world->Clear();
    for(int i = 1; i < cluster_counter; ++i)
    {
        this->_swarmPlotter->graph(i)->data()->clear();
        this->_swarmPlotterXZ->graph(i)->data()->clear();
        this->_swarmPlotterYZ->graph(i)->data()->clear();
    }
    /*for(int i = 1; i < cluster_counter; ++i)
        delete this->_swarmPlotter->graph(i);*/
    //this->_swarmPlotter->graph(0)->addData(0.0, 0.0);
    _world->addObject(new worldObject(0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 6*1e+24));
    cluster_counter = 1;
    ClusterDistribution.clear();
    ClusterDistribution.push_back(1);
    this->_swarmPlotter->replot();
    this->_swarmPlotterXZ->replot();
    this->_swarmPlotterYZ->replot();
}


void MainWindow::on_Distrib_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Uniform Distribution")
    {
        this->_u_window = new UniformDistribWin();
        this->_u_window->setWindowTitle("Uniform Distribution");
        this->_u_window->resize(350, 180);
        this->_u_window->setWindowIcon(QIcon("AppIcon"));
        connect(this->_u_window, SIGNAL(OK()), this, SLOT(CloseUniformDistWin()));
        this->_u_window->show();
    }
    else if(arg1 == "Normal Distribution")
    {
        this->_n_window = new NormalDistribWin();
        this->_n_window->setWindowTitle("Normal Distribution");
        this->_n_window->resize(350, 180);
        this->_n_window->setWindowIcon(QIcon("AppIcon"));
        connect(this->_n_window, SIGNAL(OK()), this, SLOT(CloseNormalDistWin()));
        this->_n_window->show();
    }
}

void MainWindow::CloseUniformDistWin()
{
    this->_world->SetUniformDistrib(this->_u_window->GetRA(), this->_u_window->GetRB(), this->_u_window->GetVA(), this->_u_window->GetVB());
    this->_u_window->close();
}

void MainWindow::CloseNormalDistWin()
{
    this->_world->SetNormalDistrib(this->_n_window->GetR_Mu(), this->_n_window->GetR_Sigma(), this->_n_window->GetV_Mu(), this->_n_window->GetV_Sigma());
    this->_n_window->close();
}

