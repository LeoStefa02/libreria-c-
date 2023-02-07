#ifndef __INTEGRAL_H__
#define __INTEGRAL_H__

#include "./../FunzioniUtili/FunzioneBase.h"
#include "./../FunzioniUtili/RandomGen.h"
#include <functional>
#include <iostream>

using namespace std;

class Integral {
public:
  Integral(double a, double b) {
    check_interval(a, b);
    m_nstep = 0;
    m_h = 0;
    m_sum = 0;
    m_integral = 0;
    m_prec = 0;
  }
  double get_precision() { return m_prec; }
  unsigned int get_step() { return m_nstep; }
  virtual double integra_step(unsigned int nstep, FunzioneBase &f) = 0;

protected:
  void check_interval(double a, double b) {
    m_a = min(a, b);
    m_b = max(a, b);
    if (a < b) {
      m_sign = 1;
    } else {
      m_sign = -1;
    }
  }

  unsigned int m_nstep;
  double m_a, m_b, m_prec;
  double m_sum, m_integral, m_h;
  int m_sign;
};

// Metodo MidPoint
class Midpoint : public Integral {

public:
  Midpoint(double a, double b) : Integral(a, b) { ; }

  double integra_step(unsigned int nstep, FunzioneBase &f) override {
    if (nstep == 0) {
      cout << "Il numero di passi non puo' essere minore o uguale a 0!" << endl;
      exit(-1);
    }
    m_sum = 0;
    m_nstep = nstep;
    m_h = (m_b - m_a) / m_nstep;
    for (int i = 0; i < m_nstep; i++) {
      m_sum += f.eval(m_a + (i + 0.5) * m_h);
    }
    m_integral = m_sign * m_sum * m_h;
    return m_integral;
  }

  double integra_prec(double prec, FunzioneBase &f) {
    double val_1 = integra_step(2,f);
    double val_2 = integra_step(4, f);
    while(((4./3.)*fabs(val_2 - val_1)) > prec) {
      val_1 = val_2;
      val_2 = integra_step(m_nstep * 2, f);
    }
    return val_2;
  }

  double h_stimato(double prec, FunzioneBase &f, unsigned int n_step) {
    double h = (m_b - m_a) / (double)n_step;
    double val_1 = integra_step(n_step, f);
    double val_2 = integra_step(n_step * 2, f);
    return sqrt((prec * 3 * pow(h, 2)) / (4 * fabs(val_2 - val_1)));
  }
  
};

// Metodo Simpson
class Simpson : public Integral {
public:
  Simpson(double a, double b) : Integral(a, b) { ; }

  double integra_step(unsigned int nstep, FunzioneBase &f) override {
    if (nstep == 0 || nstep % 2 == 1) {
      cout
          << "Il numero di passi non puo' essere dispari o minore o uguale a 0!"
          << endl;
      exit(-1);
    }
    m_sum = 0;
    m_nstep = nstep;
    m_h = (m_b - m_a) / m_nstep;
    for (int i = 0; i < m_nstep; i = i + 2) {
      double x0 = m_a + i * m_h;
      double x1 = m_a + (i + 1) * m_h;
      double x2 = m_a + (i + 2) * m_h;
      m_sum += f.eval(x0) + 4 * f.eval(x1) + f.eval(x2);
    }
    m_integral = m_sign * m_sum * m_h / 3.;
    return m_integral;
  }

  double integra_prec(double prec, FunzioneBase &f) {
    double val_1 = integra_step(2,f);
    double val_2 = integra_step(4, f);
    while(((16./15.)*fabs(val_2 - val_1)) > prec) {
      val_1 = val_2;
      val_2 = integra_step(m_nstep * 2, f);
    }
    return val_2;
  }

  double h_stimato(double prec, FunzioneBase &f, unsigned int n_step) {
    double h = (m_b - m_a) / (double)n_step;
    double val_1 = integra_step(n_step, f);
    double val_2 = integra_step(n_step * 2, f);
    return pow((prec * 15 * pow(h, 4)) / (16 * fabs(val_2 - val_1)), 1./4.);
  }

};

// Metodo Trapezi
class Trapezi : public Integral {
public:
  Trapezi(double a, double b) : Integral(a, b) { ; }

  double integra_step(unsigned int nstep, FunzioneBase &f) override {
    if (nstep == 0) {
      cout << "Il numero di passi non puo' essere minore o uguale a 0!" << endl;
      exit(-1);
    }
    m_sum = (f.eval(m_a) + f.eval(m_b)) * 0.5;
    m_nstep = nstep;
    m_h = (m_b - m_a) / m_nstep;
    for (int i = 1; i < m_nstep; i++) {
      m_sum += f.eval(m_a + i * m_h);
    }
    m_integral = m_sum * m_sign * m_h;
    return m_integral;
  }

  double integra_prec(double prec, FunzioneBase &f) {
    double val_1 = integra_step(2,f);
    double val_2 = integra_step(4, f);
    while(((4./3.)*fabs(val_2 - val_1)) > prec) {
      val_1 = val_2;
      val_2 = integra_step(m_nstep * 2, f);
    }
    return val_2;
  }

  double h_stimato(double prec, FunzioneBase &f, unsigned int n_step) {
    double h = (m_b - m_a) / (double)n_step;
    double val_1 = integra_step(n_step, f);
    double val_2 = integra_step(n_step * 2, f);
    return sqrt((prec * 3 * pow(h, 2)) / (4 * fabs(val_2 - val_1)));
  }

};

class HitOrMiss : public Integral {
public:
  HitOrMiss(double a, double b) : Integral(a, b){};
  double integra_step(unsigned int nstep, FunzioneBase &f) override {

    int Nhit = 0;
    double x, y;
    for (int i = 0; i < nstep; i++) {
      x = rand.unif(m_a, m_b);
      y = rand.unif(f.get_ymin(), f.get_ymax());
      if (f.eval(x) > 0 && y > 0 && y < f.eval(x) ||
          f.eval(x) < 0 && y < 0 && y > f.eval(x))
        Nhit++;
    }
    m_integral = ((m_b - m_a) * (f.get_ymax() - f.get_ymin())) *
                 (static_cast<double>(Nhit) / static_cast<double>(nstep));
    return m_integral;
  }

private:
  RandomGen rand = RandomGen(1);
};

class Media : public Integral {

public:
  Media(double a, double b) : Integral(a, b) { ; };

  double integra_step(unsigned int nstep, FunzioneBase &f) override {
    if (nstep == 0) {
      cout << "Steps number cannot be zero" << endl;
      exit(-1);
    }

    m_nstep = nstep;
    m_sum = 0;
    for (int i = 0; i < m_nstep; i++) {
      m_sum += f.eval(rand.unif(m_a, m_b));
    }
    m_integral = m_sum * (m_b - m_a) / nstep;
    return m_integral;
  };

private:
  RandomGen rand = RandomGen(1);
};

#endif // __INTEGRAL_H__