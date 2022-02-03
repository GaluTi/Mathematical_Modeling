#ifndef TimeLineWidget_H
#define TimeLineWidget_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include "virtualdatetime.h"

class TimeLineWidget : public QWidget
{
    Q_OBJECT
    QDateTime startTime; //текущее начало таймлайна
    QDateTime endTime; //текущее окончание таймлайна
    int hours; //сколько часов помещается в таймлайне

    int margin; //отступ при отрисовке таймлайна

    int currentPos; //текущая позиция маркера

    int hgt;

    bool markerpressed;

    bool run;
    QTimer timer;



public:
    explicit TimeLineWidget(QWidget *parent = 0);

    void setEnabled(bool f) { run = f;    }
    bool getTimerEnabled()  { return run; }

    QDateTime getStartTime();
    QDateTime getEndTime();

signals:
    void timeChanged();
    void timeOut();

public slots:
    void onTimer();
    void offTimer();
    void startTimeChanged(QDateTime dTime);
    void endTimeChanged(QDateTime dTime);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

    void drawLines(QPainter* painter);
    void drawTimeTicks(QPainter* painter);
    void drawCurrentMarker(QPainter* painter);

    void checkMarkers(int x, int y);

    int timeToPos(QDateTime dt);
    QDateTime posToTime(int pos);
};

#endif // TimeLineWidget_H
