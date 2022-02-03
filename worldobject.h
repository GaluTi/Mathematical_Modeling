#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QVector2D>

class worldObject
{

private:

    int _id;
    QVector2D _coord;
    QVector2D _vel;
    bool _updated;

public:
    worldObject();
    worldObject(int id, QVector2D r, QVector2D v);

    QVector2D Power(worldObject* obj, double dt);
    void Update(double dt, QVector2D F);

    int getId() {return  this->_id;}
    QVector2D GetCoord() {return this->_coord;}
    QVector2D GetVel() {return this->_vel;}
    double ScalarMul(QVector2D v1, QVector2D v2) {return (v1.x()*v2.x()+v1.y()*v2.y())/(v1.length()*v2.length());}

    void SetUpdate(bool flag) {this->_updated = flag;}
    bool IsUpdated() {return _updated;}

    bool operator==(const worldObject& other) {return _coord == other._coord && _id == other._id;}
    bool operator!=(const worldObject& other) {return !(*this == other);}

    ~worldObject();
};

#endif // WORLDOBJECT_H
