#ifndef __solutore__
#define __solutore__

#include "./../FunzioniUtili/FunzioneBase.h"
#include <float.h>
#include <iostream>
using namespace std;

class Solutore {

public:
  // Costruttori
  Solutore() {
    m_a = 0;
    m_b = 0;
    m_prec = 0;
  }
  Solutore(double prec) {
    m_a = 0;
    m_b = 0;
    m_prec = prec;
  }
  Solutore(double a, double b, double prec) {
    m_a = a;
    m_b = b;
    m_prec = prec;
  }
  Solutore(double a, double b, double prec, double iter, double max) {
    m_a = a;
    m_b = b;
    m_prec = prec;
    m_nmax = max;
    m_niterations = iter;
  }

  virtual double cerca_zeri(double a, double b, const FunzioneBase &f,
                            double prec = 0.001, unsigned int nmax = 100) = 0;

  void set_precisione(double epsilon) { m_prec = epsilon; }
  void set_max_iterazioni(unsigned int n) { m_nmax = n; }

  unsigned int get_max_iterazioni() { return m_nmax; }
  unsigned int get_iterazioni() { return m_niterations; }
  double get_precisione() { return m_prec; }

protected:
  double m_a, m_b;
  double m_prec, m_incertezza;
  bool m_trovato = true;
  unsigned int m_nmax, m_niterations;
};

class Bisezione : public Solutore {

public:
  Bisezione() : Solutore() { ; };

  double cerca_zeri(double a, double b, const FunzioneBase &f,
                    double prec = 0.001, unsigned int nmax = 100) override {

    if (b < a) {
      double temp = a;
      a = b;
      b = temp;
    }

    Segno sign;
    int count = 0;

    double c;
    for (int i = 0; i < nmax; i++) {
      count++;
      c = (b + a) / 2;
      double s_fa = sign.eval(f.eval(a));
      double s_fc = sign.eval(f.eval(c));
      if ((s_fa * s_fc) < 0)
        b = c;
      else
        a = c;
      if ((b - a) < prec)
        break;
    }
    m_niterations = count;
    return c;
  }
};

#endif // __solutore__