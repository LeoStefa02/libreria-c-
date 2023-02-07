#ifndef __FunzioneVettorialeBase_h__
#define __FunzioneVettorialeBase_h__

#include "VectorOperations.h"
#include <cmath>

using namespace std;

// classe generica astratta
class FunzioneVettorialeBase {
public:
  virtual vector<double> eval(double t, const vector<double> &x) const = 0;
};

// oscillatore armonico
class OscillatoreArmonico : public FunzioneVettorialeBase {

public:
  OscillatoreArmonico(double omega0) { m_w0 = omega0; };
  vector<double> eval(double t, const vector<double> &x) const override {
    return vector<double>{x[1], -(m_w0 * m_w0) * x[0]};
  }

private:
  double m_w0;
};

// pendolo
class Pendolo : public FunzioneVettorialeBase {

public:
  Pendolo(double l) { m_l = l; };
  vector<double> eval(double t, const vector<double> &x) const override {
    return vector<double>{x[1], -(m_g / m_l) * sin(x[0])};
  }

private:
  double m_l;
  double m_g = 9.80665;
};

// oscillatore armonico forzato
class OscillatoreArmonicoForzato : public FunzioneVettorialeBase {

public:
  OscillatoreArmonicoForzato(double omega0, double a, double omega) {
    m_w0 = omega0;
    m_a = a;
    m_omega = omega;
  }
  void SetOmega(double omega) { m_omega = omega; }
  vector<double> eval(double t, const vector<double> &x) const override {
    return vector<double>{x[1], -(m_w0 * m_w0) * x[0] - m_a * x[1] +
                                    sin(m_omega * t)};
  }

private:
  double m_w0, m_a, m_omega;
};

#endif // __FunzioneVettorialeBase_h__