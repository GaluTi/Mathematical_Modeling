#include "mainwindow.h"

#include <QApplication>
#include "world.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("RedSpaceAnts");
    w.setWindowIcon(QIcon("AppIcon"));
    w.show();
    return a.exec();
}
