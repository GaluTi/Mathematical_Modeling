#include "timelinewidget.h"

TimeLineWidget::TimeLineWidget(QWidget *parent) :
    QWidget(parent)
{
    hgt = 15;
    margin = 20;
    markerpressed = false;
    this->hours = 7;
    QDateTime currentTime = VirtualDateTime::GetTime();
    qint64 msecs = currentTime.toMSecsSinceEpoch();
    msecs -= hours * 3600000.0 * 0.2;
    startTime = QDateTime::fromMSecsSinceEpoch(msecs).toUTC();
    endTime = startTime.addSecs(3600 * hours);
    currentPos = timeToPos(currentTime);

    setFixedHeight(60);

    connect (&timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer.setInterval(100);
    timer.start();
}

QDateTime TimeLineWidget::getStartTime()
{
    return this->startTime;
}

QDateTime TimeLineWidget::getEndTime()
{
    return this->endTime;
}

void TimeLineWidget::startTimeChanged(QDateTime dTime)
{

    startTime = QDateTime::fromMSecsSinceEpoch(dTime.toMSecsSinceEpoch()).toUTC();

    endTime = startTime.addSecs(3600 * hours);


    QDateTime currentTime = startTime.addSecs(60 * 10);
    currentPos = timeToPos(currentTime);

    VirtualDateTime::SetTime(currentTime);

    onTimer();


//    startTime = QDateTime::fromMSecsSinceEpoch(dTime.toMSecsSinceEpoch()).toUTC();

//    endTime = startTime.secsTo(this->endTime) > 0 ? this->endTime : this->startTime.addSecs(3600 * 24);
//    QDateTime currentTime = VirtualDateTime::GetTime();
//    update();

//    if(endTime.secsTo(currentTime) >= 0)
//    {
//        currentTime = startTime;
//    }

//    currentPos = timeToPos(currentTime);

//    emit timeChanged();
//     update();

    //    QDateTime startTimeOld = startTime;

//    startTime = QDateTime::fromMSecsSinceEpoch(dTime.toMSecsSinceEpoch()).toUTC();

//    QDateTime currentTime = VirtualDateTime::GetTime();

//    if(currentTime.secsTo(startTime) > 0)
//    {
//        currentTime = startTime;
//    }

//    currentPos = timeToPos(currentTime);

//    this->hours = startTime.secsTo(this->endTime) > 0 ? startTime.secsTo(this->endTime) / 60 / 60 + 1 : 24;

//    endTime = startTime.secsTo(this->endTime) > 0 ? this->endTime : this->startTime.addSecs(3600 * hours);

//    emit timeChanged();
//    update();

}

void TimeLineWidget::endTimeChanged(QDateTime dTime)
{

    endTime = QDateTime::fromMSecsSinceEpoch(dTime.toMSecsSinceEpoch()).toUTC();

    //startTime = endTime.addSecs(- 3600 * hours);
    QDateTime currentTime = startTime;//.addSecs(10 * 60);
    currentPos = timeToPos(currentTime);
    VirtualDateTime::SetTime(currentTime);

//    startTime = startTime.secsTo(this->endTime) > 0 ? this->startTime : this->endTime.addSecs(- 3600 * 24);
//    QDateTime currentTime = VirtualDateTime::GetTime();
//    update();

//    if(endTime.secsTo(currentTime) >= 0)
//    {
//        currentTime = startTime;
//    }

//    currentPos = timeToPos(currentTime);

//    emit timeChanged();

//    update();

    onTimer();
}

void TimeLineWidget::onTimer()
{
    timer.start();
    setEnabled(true);
    QDateTime currentTime = VirtualDateTime::GetTime();
    if (currentTime.msecsTo(endTime) < 1000)//hours * 360000)
    {
        qint64 msecs = currentTime.toMSecsSinceEpoch();
        msecs -= hours * 3600000.0 * 0.2;
        startTime = QDateTime::fromMSecsSinceEpoch(msecs).toUTC();
        endTime = startTime.addSecs(3600 * hours);
    }
    if (startTime.msecsTo(currentTime) < 1000)//hours * 720000)
    {
        qint64 msecs = currentTime.toMSecsSinceEpoch();
        msecs -= hours * 3600000.0 * 0.8;
        startTime = QDateTime::fromMSecsSinceEpoch(msecs).toUTC();
        endTime = startTime.addSecs(3600 * hours);
    }
    currentPos = timeToPos(currentTime);
    emit timeChanged();

    this->update();
}

void TimeLineWidget::offTimer()
{
    timer.stop();
    setEnabled(false);
}

void TimeLineWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    drawLines(&painter);
    drawTimeTicks(&painter);
    drawCurrentMarker(&painter);

    painter.end();
}

void TimeLineWidget::drawLines(QPainter *painter)
{
    painter->setPen(QPen(QColor(0,0,0)));
    int h0 = hgt / 6;
    int h = height();
    int w = width();
    painter->drawLine(margin, h/2-h0, w-margin, h/2-h0);
    painter->drawLine(margin, h/2-h0, margin, h/2+h0);
    painter->drawLine(margin, h/2+h0, w-margin, h/2+h0);
    painter->drawLine(w-margin, h/2-h0, w-margin, h/2+h0);
    QBrush br = QBrush (QColor (180, 180, 180));
    painter->setBrush(br);
    painter->setPen(Qt::NoPen);
    painter->drawRect(margin + 1, h/2-h0+1, w-2*margin-1, 2*h0 - 1);
}

void TimeLineWidget::drawTimeTicks(QPainter *painter)
{
    int h0 = hgt / 3;
    QPen ln(QColor(0,0,0));
    QPen tx(QColor(50,50,50));
    QDate sd=startTime.date();
    QTime st=startTime.time();
    int x;
    painter->setPen(ln);
    QString str;

    st = QTime(st.hour(), 0, 0, 0);
    QDateTime t0(sd, st, Qt::UTC);
    int counter = 0;
    for (; t0 < endTime; t0 = t0.addSecs(10*60))
    {
        if (t0 >= startTime)
        {
            x = timeToPos(t0);

            if (t0.time().hour() % 4 == 0 && t0.time().minute() == 0 && t0.time().second() == 0)
            {
                painter->drawLine(x, height() / 2 + h0, x, height() / 2 + 12);
                str = t0.date().toString("dd.MM.yyyy");
                painter->setPen(tx);
                painter->drawText(x-15, height() / 2 + 30, str);

                if (counter%6 == 0)
                {
                    painter->drawLine(x, height()/2-h0, x, height()/2-12);
                    str = t0.time().toString("hh:mm");
                    painter->setPen(tx);
                    painter->drawText(x-15, height()/2-15, str);
                }
                else
                    painter->drawLine(x, height()/2-h0, x, height()/2-8);
            }
            else
            {
                if (counter%6 == 0)
                {
                    painter->drawLine(x, height()/2-h0, x, height()/2-12);
                    str = t0.time().toString("hh:mm");
                    painter->setPen(tx);
                    painter->drawText(x-15, height()/2-15, str);
                }
                else
                    painter->drawLine(x, height()/2-h0, x, height()/2-8);
            }
            painter->setPen(ln);
        }
        counter++;
    }
}

void TimeLineWidget::drawCurrentMarker(QPainter *painter)
{
    int h0 = hgt / 3;
    int w0 = h0 * 2;

    QBrush b1(QColor(192, 192, 192));
    QPen pen(QColor(0, 0, 0));

    painter->setPen(pen);
    painter->setBrush(b1);
    QPoint marker[5];
    marker[0] = QPoint (currentPos, height()/2-2*h0);
    marker[1] = QPoint (currentPos+w0, height()/2-h0);
    marker[2] = QPoint (currentPos+w0, height()/2+h0);
    marker[3] = QPoint (currentPos-w0, height()/2+h0);
    marker[4] = QPoint (currentPos-w0, height()/2-h0);

    w0 *= 2;
    painter->drawEllipse(currentPos - w0/2, height() /2 - w0 / 2, w0, w0);
}

void TimeLineWidget::resizeEvent(QResizeEvent* )
{
    currentPos = timeToPos(VirtualDateTime::GetTime());
}

void TimeLineWidget::mousePressEvent(QMouseEvent *event)
{
    int y=event->pos().y();
    int x=event->pos().x();

    checkMarkers(x, y);
}

void TimeLineWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (markerpressed)
    {
        currentPos = event->pos().x();
        if (currentPos < margin)
            currentPos = margin;
        if (currentPos >= width() - margin)
            currentPos = width() - margin;
        QDateTime dt = posToTime(currentPos);
        VirtualDateTime::SetTime(dt);
        emit timeChanged();
        update();
    }
}

void TimeLineWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (markerpressed)
    {
        if(getTimerEnabled())
        {
            timer.start();
            markerpressed = false;
        }
        else
            markerpressed = false;
    }
}

int TimeLineWidget::timeToPos(QDateTime dt)
{
    if (dt < startTime) return margin/2;
    if (dt > endTime) return width() - margin/2;
    float dif1 = startTime.secsTo(endTime);
    float dif2 = startTime.secsTo(dt);
    return margin+(width()-2*margin)*dif2/dif1;
}

QDateTime TimeLineWidget::posToTime(int pos)
{
    if (pos < margin) return startTime;
    if (pos > width()-margin) return endTime;
    float dif1 = startTime.secsTo(endTime);
    float l = width()-2*margin;
    float pos0 = pos - margin;
    float dif2 = dif1*pos0/l;
    QDateTime d0 = startTime.addSecs(dif2);
    return d0;
}

void TimeLineWidget::checkMarkers(int x, int y)
{
    markerpressed=false;
    if (currentPos - hgt / 3 <= x && x <= currentPos + hgt / 3 && y >=height()/2 - 2 * hgt / 3 && y <= height()/2 + hgt / 3 )
    {
        markerpressed=true;
        timer.stop();
    }
}
