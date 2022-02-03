#ifndef WORLD_H
#define WORLD_H

#include "math.h"
#include <QObject>
#include <QVector>
#include "worldobject.h"
#include "iostream"
#include <random>

#include "coreLib.h"
#include "orbitLib.h"

class world : public QObject
{
    Q_OBJECT
private:

    double _epoch_time;
    double _dt = 1.0;
    int _obj_num;

    QVector<worldObject*> _objects;


public:
    world();

    double _energy_norm;
    int _count_r;
    int _count_v;
    QVector<double> _rand_r;
    QVector<double> _rand_v;

    QVector<QPair<cSatellite, double>> _sats;
    void Update();
    QVector<worldObject*> Update(double new_epoch_time);
    //QVector<QPair<cSatellite, double>> SatUpdate(double new_epoch_time);

    void addObject(worldObject* obj);
    void addSat(cSatellite sat);
    void NumPluss() {this->_obj_num++;}
    int Num() {return this->_obj_num;}

    QVector3D GetPowers(worldObject* obj);
    QVector<worldObject*> GetObjects() {return _objects;}
    QVector<QPair<cSatellite, double>> GetSats() {return _sats;}
    double Time() {return _epoch_time;}
    void SetTimeInterval(double time) {_dt = time;}
    void Clear();
    bool IsContains(worldObject* obj);

    void SetUniformDistrib(double rA, double rB, double vA, double vB);
    void SetNormalDistrib(double rMu, double rSigma, double vMu, double vSigma);
    double GetRand_R(int i) {return _rand_r[i];}
    double GetRand_V(int i) {return _rand_v[i];}


    ~world();
};

#endif // WORLD_H
