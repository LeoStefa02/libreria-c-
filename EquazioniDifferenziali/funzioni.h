#include "./../FunzioniUtili/FunzioneVettorialeBase.h"
#include "EquazioniDifferenziali.h"

double calcola_ampiezza(EquazioneDifferenzialeBase *eq,
                        FunzioneVettorialeBase *moto, vector<double> x,
                        double h) {
  double t = 0;
  x = {0, 0.9E8};
  double v0 = x[1], v_a, v_b;
  for (int i = 0; i < 5; i++) {
    x = eq->passo(t, x, h, *moto);
    t = t + h;
  }
  double sum = 0;
  for (int i = 0; i < 10; i++) {
    if ((x[1] - 1E8 < 0)) {
      while ((v0 - x[1]) < 0) {
        v0 = x[1];
        x = eq->passo(t, x, h, *moto);
        t = t + h;
      }
      v_a = (v0 + x[1]) / 2.;
      while ((v0 - x[1]) > 0) {
        v0 = x[1];
        x = eq->passo(t, x, h, *moto);
        t = t + h;
      }
      v_b = (v0 + x[1]) / 2.;
    } else {
      while ((v0 - x[1]) > 0) {
        v0 = x[1];
        x = eq->passo(t, x, h, *moto);
        t = t + h;
      }
      v_a = (v0 + x[1]) / 2.;
      while ((v0 - x[1]) < 0) {
        v0 = x[1];
        x = eq->passo(t, x, h, *moto);
        t = t + h;
      }
      v_b = (v0 + x[1]) / 2.;
    }
    sum += fabs(v_a - v_b) / 2.;
  }

  return sum / 10;
}