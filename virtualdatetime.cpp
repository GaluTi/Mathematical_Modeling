#include "virtualdatetime.h"
#include <QDebug>

namespace VirtualDateTime
{
    QDateTime changeSystemTime; //системное время последнего изменения скорости или сдвига
    QDateTime changeVirtualTime; //виртуальное время последнего изменения скорости или сдвига
    qint64 currentOffset = 0;
    double currentSpeed = 1;

    void ResetTime()
    {
        currentOffset = 0;
        currentSpeed = 1;
        changeSystemTime = QDateTime::currentDateTimeUtc();
        changeVirtualTime = QDateTime::currentDateTimeUtc();
    }

    void SetTime(QDateTime dt)
    {
        QDateTime currentTime = QDateTime::currentDateTimeUtc();
        QDateTime newTime = dt.toUTC();
        if (currentTime > newTime)
            SetOffset(-newTime.msecsTo(currentTime));
        else
            SetOffset(currentTime.msecsTo(newTime));
    }

    void SetOffset(qint64 msecs)
    {
        QDateTime newTime = QDateTime::currentDateTimeUtc();
        changeSystemTime = newTime;
        currentOffset = msecs;
        if (msecs > 0)
            changeVirtualTime = newTime.addMSecs(msecs);
        else
        {
            qint64 ms = newTime.toMSecsSinceEpoch();
            changeVirtualTime = QDateTime::fromMSecsSinceEpoch(ms + msecs);
            changeVirtualTime = changeVirtualTime.toUTC();
        }
        //qDebug()<<changeVirtualTime.utcOffset();
        //qDebug()<<changeSystemTime.toString()<<" "<<changeVirtualTime.toString();
    }

    qint64 GetOffset()
    {
        return currentOffset;
    }

    void SetSpeed(double speed)
    {
        QDateTime newTime = QDateTime::currentDateTimeUtc();
        qint64 dif = changeSystemTime.msecsTo(newTime);
        changeVirtualTime = changeVirtualTime.addMSecs(dif * currentSpeed);
        changeSystemTime = newTime;
        currentSpeed = speed;
        currentOffset = changeSystemTime.msecsTo(changeVirtualTime);
        if (currentOffset <= 0)
            currentOffset = -changeVirtualTime.msecsTo(changeSystemTime);
    }

    double GetSpeed()
    {
        return currentSpeed;
    }

    QDateTime GetTime()
    {
        QDateTime newTime = QDateTime::currentDateTimeUtc();
        qint64 dif = changeSystemTime.msecsTo(newTime);
        QDateTime newVirtTime = changeVirtualTime.addMSecs(dif * currentSpeed);
        //qDebug()<<"nt "<<newTime<<" chst "<<changeSystemTime<<" chvt "<<changeVirtualTime<<" nvt "<<newVirtTime;
        if (newVirtTime > newTime)
            currentOffset = newTime.msecsTo(newVirtTime);
        else
            currentOffset = -newVirtTime.msecsTo(newTime);
        //qDebug()<<"co"<<currentOffset;
        return newVirtTime;
    }
}
