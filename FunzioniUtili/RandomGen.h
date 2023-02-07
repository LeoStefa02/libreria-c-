#ifndef __RandomGen_h__
#define __RandomGen_h__
#include <cmath>

// generatori di numeri casuali
class RandomGen {

public:
  RandomGen() { m_seed = 1; }
  RandomGen(unsigned int seme) { m_seed = seme; }

  void set_a(unsigned int a) { m_a = a; }
  void set_c(unsigned int c) { m_c = c; }
  void set_m(unsigned int m) { m_m = m; }
  void set_seed(unsigned int seme) { m_seed = seme; }

  double rand() {
    m_seed = (m_a * m_seed + m_c) % m_m;
    return double(m_seed) / m_m;
  }
  double unif(double xmin, double xmax) {
    return xmin + (xmax - xmin) * rand();
  }
  double exponential(double mean) { return -log(1 - rand()) / mean; }

  double gauss(double mean, double sigma) {
    double s = rand();
    double t = rand();
    double x = sqrt(-2. * log(1. - s)) * cos(2. * M_PI * t);
    return mean + x * sigma;
  }
  double gauss_ar(double mean, double sigma) {
    double altezza = 1. / (sigma * pow(2 * M_PI, 0.5));
    while (true) {
      double x = unif(mean - 3 * sigma, mean + 3 * sigma);
      double y = (1 / (sigma * (pow(2 * M_PI, 1 / 2)))) *
                 pow(M_E, -(pow((x - mean) / sigma, 2)) / 2);
      if (unif(0, altezza) < y) {
        return x;
      }
    }
  }

private:
  unsigned int m_a = 1664525, m_c = 1013904223, m_m = pow(2, 31);
  unsigned int m_seed;
};

#endif //__RandomGen_h__