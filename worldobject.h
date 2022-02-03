#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QVector3D>

class worldObject
{

private:

    int _id;
    QVector3D _coord;
    QVector3D _vel;
    bool _updated;
    long double _mass;

public:
    worldObject();
    worldObject(int id, QVector3D r, QVector3D v, long double mass);

    QVector3D Power(worldObject* obj, double dt);
    void Update(double dt, QVector3D F);

    int getId() {return  this->_id;}
    QVector3D GetCoord() {return this->_coord;}
    QVector3D GetVel() {return this->_vel;}
    double ScalarMul(QVector3D v1, QVector3D v2) {return (v1.x()*v2.x()+v1.y()*v2.y()+v1.z()*v2.z())/(v1.length()*v2.length());}

    void SetUpdate(bool flag) {this->_updated = flag;}
    bool IsUpdated() {return _updated;}

    bool operator==(const worldObject& other) {return _coord == other._coord && _id == other._id;}
    bool operator!=(const worldObject& other) {return !(*this == other);}

    ~worldObject();
};

#endif // WORLDOBJECT_H
