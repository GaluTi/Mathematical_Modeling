#ifndef VIRTUALDATETIME_H
#define VIRTUALDATETIME_H

#include <QDateTime>

namespace VirtualDateTime {
    void  SetOffset(qint64 msecs);
    void  SetTime(QDateTime dt);
    qint64  GetOffset();
    void  SetSpeed(double speed);
    double  GetSpeed();
    QDateTime  GetTime();
    void  ResetTime();
}

#endif // VIRTUALDATETIME_H
