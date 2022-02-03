#include "world.h"
#include <iostream>
#include <random>

const double m = 1e+2;

world::world()
{
    this->_epoch_time = 0.0;
    this->_obj_num = 0;
    this->_dt = -1.0;
    this->_count_r = 0.0;
    this->_count_v = 0.0;
    this->_energy_norm = 0.0;
}

QVector3D world::GetPowers(worldObject* obj)
{
    QVector3D F(0.0, 0.0, 0.0);
    F = obj->Power(_objects[0], _dt);
    /*for(auto i: this->_objects)
        if(i != obj)
            F += obj->Power(i, _dt);*/
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
        SetTimeInterval(10*(new_epoch_time - this->_epoch_time)*1e-3);

    this->_epoch_time = new_epoch_time;
    std::cout << "World update! Current epoch = " << this->_epoch_time << std::endl;

    QVector<QVector3D> F;
    for(auto i: this->_objects)
        F.push_back(GetPowers(i));

    for(int i = 1; i < this->_objects.size(); ++i)
    {
        if(!this->_objects[i]->IsUpdated())
        {
            this->_objects[i]->Update(_dt, F[this->_objects[i]->getId()]);
            /*if(this->_objects[i]->GetCoord().length() <= 6400)
                _objects.remove(i);*/
        }
    }

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
        if(i->GetCoord() == obj->GetCoord())
            return true;
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

void world::addSat(cSatellite sat)
{
    this->_sats.push_back(qMakePair(sat, _epoch_time));
}

void world::Clear()
{
    _obj_num = 0;
    _epoch_time = 0.0;
    _count_r = 0.0;
    _count_v = 0.0;
    int N = _objects.size();
    for(auto i : _objects)
        delete i;
    _objects.clear();
    _rand_r.clear();
    _rand_v.clear();
}

world::~world()
{

}
