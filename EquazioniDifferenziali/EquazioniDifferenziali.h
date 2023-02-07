#ifndef __EquazioniDifferenziali_h__
#define __EquazioniDifferenziali_h__

#include "./../FunzioniUtili/FunzioneVettorialeBase.h"
#include "./../FunzioniUtili/VectorOperations.h"

using namespace std;

// classe generica astratta
class EquazioneDifferenzialeBase {
public:
  virtual vector<double> passo(double t, const vector<double> &x, double h,
                               const FunzioneVettorialeBase &f) const = 0;
};

// Metodo di Eulero
class Eulero : public EquazioneDifferenzialeBase {
public:
  vector<double> passo(double t, const vector<double> &x, double h,
                       const FunzioneVettorialeBase &f) const override {
    vector<double> x1 = x + h * f.eval(t, x);
    return x1;
  }
};

// Metodo di Runge-Kutta
class RungeKutta : public EquazioneDifferenzialeBase {
public:
  vector<double> passo(double t, const vector<double> &x, double h,
                       const FunzioneVettorialeBase &f) const override {
    vector<double> k1 = f.eval(t, x);
    vector<double> k2 = f.eval(t + h / 2., x + k1 * h / 2.);
    vector<double> k3 = f.eval(t + h / 2., x + k2 * h / 2.);
    vector<double> k4 = f.eval(t + h, x + k3 * h);
    vector<double> x1 = x + (k1 + 2. * k2 + 2. * k3 + k4) * (h / 6.);
    return x1;
  }

  double h_stimato(double prec, const vector<double> &x, const FunzioneVettorialeBase &f, unsigned int n_step, double h) {
    vector<double> x_n{x};
    vector<double> x_2n{x};
    double t = 0;

    for (unsigned int i = 0; i < n_step; i++) {
      x_n = passo(t, x_n, h, f);
      t += h;
    }

    t = 0;

    for (unsigned int i = 0; i < 2 * n_step; i++) {
      x_2n = passo(t, x_2n, h / 2., f);
      t += h / 2.;
    }

    return pow((15. * prec) / fabs(16. * (x_n[0] - x_2n[0])), 1. / 4.) * h;

  }

  vector<vector<double>>* integra_prec(double prec, double t_0, double t_f, const vector<double> &x, const FunzioneVettorialeBase &f, double h = 0.001) {
    double h_s = h_stimato(prec, x, f, 1000, h);

    vector<double> x_n{x};
    vector<double> x_2n{x};
    double t = 0;

    unsigned int n_step = (t_f - t_0) / (h_s * 2);
    vector<vector<double>> * p = new vector<vector<double>>(n_step * 2);

    while(prec < (16. / 15.) * fabs(x_n[0] - x_2n[0])) {
      for (unsigned int i = 0; i < n_step; i++) {
        x_n = passo(t, x_n, h_s * 2, f);
        t += h_s * 2;
      }

      for (unsigned int i = 0; i < n_step * 2; i++) {
        x_2n = passo(t, x_n, h_s, f);
        (*p)[i] = x_2n;
        t += h_s;
      }
    }

    return p;


  }
  
};

#endif // __EquazioniDifferenziali_h__