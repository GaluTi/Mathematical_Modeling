#include "worldobject.h"
const double e = 2.7;

worldObject::worldObject()
{

}

worldObject::worldObject(int id, QVector2D r, QVector2D v)
{
    this->_id = id;
    this->_coord = r;
    this->_vel = v;
    this->_updated = false;
}

QVector2D worldObject::Power(worldObject* obj, double dt)
{
    QVector2D r = obj->_coord - this->_coord;
    QVector2D F = r/pow(r.length(),3);
    if(r.length() < 10)
    {
        this->_vel = this->_vel - (ScalarMul(this->_vel - obj->_vel, this->_coord - obj->_coord))*(this->_coord - obj->_coord)/((this->_coord - obj->_coord).lengthSquared());
        this->Update(dt, F);
        //obj->_vel = obj->_vel - (ScalarMul(obj->_vel - this->_vel, obj->_coord - this->_coord))*(obj->_coord - this->_coord)/((obj->_coord - this->_coord).lengthSquared());
        //obj->Update(0.1, -0.01*F);
        return F;
    }
    else if(r.length() > 100)
    {
        return r.lengthSquared()*F;
    }
    else
    {
        return F;
    }
}

void worldObject::Update(double dt, QVector2D F)
{
    this->_coord += _vel*dt + F*dt*dt/2;
    this->_vel += F*dt;
    this->_updated = true;
}



worldObject::~worldObject()
{

}
