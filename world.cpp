#include "world.h"
#include <iostream>
#include <random>

const double G = 6.67*1e-11;
const double m = 1e+3;

world::world()
{
    this->_epoch_time = 0.0;
    this->_obj_num = 0;
    this->_dt = -1.0;
    this->_mean_v = 0.0;
    this->_max_r = 0.0;
    this->_count_r = 0.0;
    this->_count_v = 0.0;
}

QVector2D world::GetPowers(worldObject* obj)
{
    QVector2D F;
    F.setX(0);
    F.setY(0);
    for(auto i: this->_objects)
    {
        if(i != obj)
        {
            F += obj->Power(i, _dt);
            if(_max_r < (i->GetCoord() - obj->GetCoord()).length())
                _max_r = (i->GetCoord() - obj->GetCoord()).length();
        }
    }
    return F;
}

void world::Update()
{

}

QVector<worldObject*> world::Update(double new_epoch_time)
{
    if(_epoch_time == 0.0)
        _dt = 0.0;
    else if(_dt == 0.0)
        SetTimeInterval(new_epoch_time - this->_epoch_time);

    this->_epoch_time = new_epoch_time;
    std::cout << "World update! Current epoch = " << this->_epoch_time << std::endl;

    _mean_v = 0.0;
    _max_r = 0.0;
    QVector<QVector2D> F;
    for(auto i: this->_objects)
        F.push_back(GetPowers(i));
    for(auto i: this->_objects)
    {
        if(!i->IsUpdated())
            i->Update(_dt, F[i->getId()]);
        _mean_v += i->GetVel().length();
    }
    if(_obj_num != 0)
        _mean_v /= _obj_num;

    return _objects;
}

void world::SetUniformDistrib(double rA, double rB, double vA, double vB)
{
    _count_r = 0.0;
    _count_v = 0.0;
    _rand_r.clear();
    _rand_v.clear();
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> uniform_dist_r(rA, rB);
    std::uniform_real_distribution<> uniform_dist_v(vA, vB);
    for (int n = 0; n < 10000; ++n)
    {
        _rand_r.push_back(uniform_dist_r(gen));
        _rand_v.push_back(uniform_dist_v(gen));
    }
}

void world::SetNormalDistrib(double rMu, double rSigma, double vMu, double vSigma)
{
    _count_r = 0.0;
    _count_v = 0.0;
    _rand_r.clear();
    _rand_v.clear();
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> normal_dist_r{rMu, rSigma};
    std::normal_distribution<> normal_dist_v{vMu, vSigma};
    for (int n = 0; n < 10000; ++n)
    {
        _rand_r.push_back(normal_dist_r(gen));
        _rand_v.push_back(normal_dist_v(gen));
    }
}

bool world::IsContains(worldObject *obj)
{
    for(auto i : _objects)
    {
        if(i->GetCoord() == obj->GetCoord())
            return true;
    }
    return false;
}

void world::addObject(worldObject *obj)
{
    if(!IsContains(obj))
    {
        this->_obj_num++;
        this->_objects.push_back(obj);
    }
}

void world::Clear()
{
    _obj_num = 0;
    _epoch_time = 0.0;
    _count_r = 0.0;
    _count_v = 0.0;
    for(auto i : _objects)
        delete i;
    _objects.clear();
    _rand_r.clear();
    _rand_v.clear();
}

world::~world()
{

}
