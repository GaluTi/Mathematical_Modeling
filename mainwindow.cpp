#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->_world = new world();

    this->_mainTimer = new QTimer();
    connect(this->_mainTimer, SIGNAL(timeout()), this, SLOT(onTimeChangedSlot()));

    this->initPlotter();
    connect(this->_swarmPlotter, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(MousePressEvent(QMouseEvent*)));

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
    this->_world = w;

    this->_mainTimer = new QTimer();
    connect(this->_mainTimer, SIGNAL(timeout()), this, SLOT(onTimeChangedSlot()));

    this->initPlotter();
    connect(this->_swarmPlotter, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(MousePressEvent(QMouseEvent*)));

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
    ui->gridLayout->addWidget(this->_swarmPlotter);

    this->_swarmPlotter->addGraph();

    //this->_swarmPlotter->graph(0)->setPen(QColor(50, 50, 50, 255));
    this->_swarmPlotter->graph(0)->setPen(QColor(255,0,0,255));
    this->_swarmPlotter->graph(0)->setBrush(QColor(50, 50, 50, 255));

    this->_swarmPlotter->graph(0)->setLineStyle(QCPGraph::lsNone);
    this->_swarmPlotter->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    this->_swarmPlotter->graph(0)->setName("Swarm Data");

    this->_swarmPlotter->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
}

void MainWindow::onTimeChangedSlot()
{
    std::cout << "Timer changed! " << std::endl;

    for(auto i : this->_world->GetObjects())
        i->SetUpdate(false);

    this->_swarmPlotter->graph(0)->data()->clear();
    this->_world->Update(QDateTime::currentSecsSinceEpoch()); //Ms
    for (auto i : this->_world->GetObjects())
        this->_swarmPlotter->graph(0)->addData(i->GetCoord().x(), i->GetCoord().y());
    this->_swarmPlotter->replot();
    ui->MeanVel->clear();
    ui->SwarmDiam->clear();
    QString str = "%1";
    ui->MeanVel->insert(str.arg(this->_world->GetMeanVel()));
    ui->SwarmDiam->insert(str.arg(this->_world->GetSetDiam()));
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
        this->_mainTimer->setInterval(25);
        this->_mainTimer->start();

        this->_world->Update(this->_world->Time());
        this->t = QDateTime::currentSecsSinceEpoch(); //Ms
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
    if(this->_world != nullptr)
    {
        if(ui->Distrib->currentText() == "-")
            QMessageBox::warning(this, "Warning!", "Select Distribution or use <Add by Click> ");
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
                    if(N == 0)
                        N = 1;
                    if(N <= 500)
                    {
                        if(this->_world->_rand_r.size() > this->_world->_count_r+2*N && this->_world->_rand_v.size() > this->_world->_count_v+2*N)
                        {
                            for(int i = 0; i < N; ++i)
                            {
                                QVector2D r(this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++));
                                QVector2D v(this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++));

                                this->_world->addObject(new worldObject(this->_world->Num(), r, v));
                                this->_swarmPlotter->graph(0)->addData(r.x(), r.y());
                            }
                            this->_swarmPlotter->replot();
                        }
                        else
                            QMessageBox::warning(this, "Warning!", "Need another generate of numbers");
                    }
                    else
                        QMessageBox::warning(this, "Warning!", "Select N <= 500");
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
                    if(N == 0)
                        N = 1;
                    if(N <= 500)
                    {
                        if(this->_world->_rand_r.size() > this->_world->_count_r+2*N && this->_world->_rand_v.size() > this->_world->_count_v+2*N)
                        {
                            for(int i = 0; i < N; ++i)
                            {
                                QVector2D r(this->_world->GetRand_R(this->_world->_count_r++), this->_world->GetRand_R(this->_world->_count_r++));
                                QVector2D v(this->_world->GetRand_V(this->_world->_count_v++), this->_world->GetRand_V(this->_world->_count_v++));

                                this->_world->addObject(new worldObject(this->_world->Num(), r, v));
                                this->_swarmPlotter->graph(0)->addData(r.x(), r.y());
                            }
                            this->_swarmPlotter->replot();
                        }
                        else
                            QMessageBox::warning(this, "Warning!", "Need another generate of numbers");
                    }
                    else
                        QMessageBox::warning(this, "Warning!", "Select N <= 500");
                }
            }
            else
                QMessageBox::warning(this, "Warning!", "Distribution parameters does not exist!/n Don`t close the <Normal Distribution> window but push <OK> button>");
        }
        else
        {
            //static int _obj_num = 0;
            double x = 1.5*(rand()/(double)RAND_MAX-0.5);
            double y = 1.5*(rand()/(double)RAND_MAX-0.5);
            double vx = 1.5*(rand()/(double)RAND_MAX-0.5);
            double vy = 1.5*(rand()/(double)RAND_MAX-0.5);
            QVector2D r(x, y);
            QVector2D v(vx, vy);

            this->_world->addObject(new worldObject(this->_world->Num(), r, v));
            this->_swarmPlotter->graph(0)->addData(x, y);
            this->_swarmPlotter->replot();
       }
    }
}



void MainWindow::MousePressEvent(QMouseEvent* event)
{
    if(ui->AddByClick->isChecked())
    {
        double x, y;
        x = this->_swarmPlotter->xAxis->pixelToCoord(event->pos().x());
        y = this->_swarmPlotter->yAxis->pixelToCoord(event->pos().y());
        if(this->_world != nullptr)
        {
            QVector2D r(x, y);
            QVector2D v(0, 0);
            this->_world->addObject(new worldObject(this->_world->Num(), r, v));
            this->_swarmPlotter->graph(0)->addData(x, y);
            this->_swarmPlotter->replot();
        }
    }
}


void MainWindow::on_clearButton_clicked()
{
    _world->Clear();
    ui->MeanVel->clear();
    ui->SwarmDiam->clear();
    this->_swarmPlotter->graph(0)->data()->clear();
    this->_swarmPlotter->replot();
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
