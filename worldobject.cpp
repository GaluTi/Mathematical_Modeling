#include "worldobject.h"
const double e = 2.7;
const double G = 6.67*1e-11;
const double GM = 40*1e+4;

worldObject::worldObject()
{

}

worldObject::worldObject(int id, QVector3D r, QVector3D v, long double mass)
{
    this->_id = id;
    this->_coord = r;
    this->_vel = v;
    this->_mass = mass;
    this->_updated = false;
}

QVector3D worldObject::Power(worldObject* obj, double dt)
{
    QVector3D r = obj->_coord - this->_coord;
    QVector3D F = r/pow(r.length(),3);
    return GM*this->_mass*F;
}

void worldObject::Update(double dt, QVector3D F)
{
    QVector3D acc = F/this->_mass;
    this->_coord += _vel*dt + acc*dt*dt/2;
    this->_vel += acc*dt;
    this->_updated = true;
}



worldObject::~worldObject()
{

}
