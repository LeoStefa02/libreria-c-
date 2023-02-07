#include "./../FunzioniUtili/FunzioneBase.h"
#include "./../FunzioniUtili/RandomGen.h"

class IntegralMC {
public:
  IntegralMC(unsigned int seed) { m_myrand.set_seed(seed); }
  void set_seed(unsigned int seed) { m_myrand.set_seed(seed); }
  double get_error() { return m_errore; }
  int get_N() { return m_N; }

  double integra_avg(int n_punti, double xmin, double xmax,
                     const FunzioneBase &f) {
    m_sum = 0;
    for (int i = 0; i < n_punti; i++)
      m_sum += f.eval(m_myrand.unif(xmin, xmax));
    m_integral = ((xmax - xmin) * m_sum) / n_punti;
    return m_integral;
  }

  // integrale montecarlo con precisione
  double integra_avg_precision(double prec, double xmin, double xmax,
                               const FunzioneBase &f) {
    m_sum = 0;
    double k = 0, media = 0, media2 = 0, integrale;
    int volte = 10000;

    // calcolo di n stimato
    for (int i = 0; i < volte; i++) {
      k = static_cast<double>(i) / static_cast<double>(i + 1);
      integrale = f.eval(m_myrand.unif(xmin, xmax));
      media = k * media + integrale / static_cast<double>(i + 1);
      media2 =
          k * media2 + (integrale * integrale) / static_cast<double>(i + 1);
    }
    m_N = volte *
          (pow(xmax - xmin, 2.) * ((media2 - media * media) / (volte - 1))) /
          (prec * prec);

    return integra_avg(m_N, xmin, xmax, f);
  }

  double integra_hm(int punti, double xmin, double xmax, double ymin,
                    double ymax, const FunzioneBase &f) {
    int Nhit = 0;
    double x, y;
    for (int i = 0; i < punti; i++) {
      x = m_myrand.unif(xmin, xmax);
      y = m_myrand.unif(ymin, ymax);
      if (y < f.eval(x)) {
        Nhit++;
      }
    }
    m_integral = ((xmax - xmin) * (ymax - ymin)) *
                 (static_cast<double>(Nhit) / static_cast<double>(punti));
    return m_integral;
  }

private:
  RandomGen m_myrand;
  double m_errore;
  double m_sum;
  double m_integral;
  int m_N;
};