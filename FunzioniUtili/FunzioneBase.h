#ifndef __FunzioneBase__
#define __FunzioneBase__

#include <cmath>

class FunzioneBase {

public:
  virtual double eval(double x) const = 0;
  double get_ymax() { return m_ymax; };
  double get_ymin() { return m_ymin; };

protected:
  double m_ymax;
  double m_ymin;
};

class Seno : public FunzioneBase {
public:
  double eval(double x) const override { return sin(x); };
  Seno() {
    m_ymax = 1;
    m_ymin = -1;
  }
};
// Parabola
class Parabola : public FunzioneBase {

public:
  Parabola() {
    m_a = 0.;
    m_b = 0.;
    m_c = 0.;
  }
  Parabola(double a, double b, double c) {
    m_a = a;
    m_b = b;
    m_c = c;
  }
  ~Parabola() {}

  // metodo eval, guarda in esame se ha senso fare una madre class Funzioni
  double eval(double x) const override { return m_a * x * x + m_b * x + m_c; }

  void set_a(double a) { m_a = a; }
  void set_b(double b) { m_b = b; }
  void set_c(double c) { m_c = c; }

  double get_a() const { return m_a; }
  double get_b() const { return m_b; }
  double get_c() const { return m_c; }
  double get_ver() const { return (-m_b) / (2. * m_a); }

private:
  double m_a, m_b, m_c;
};

// Segno
class Segno : public FunzioneBase {

public:
  double eval(double x) const override {
    if (x > 0) {
      return 1;
    } else if (x < 0) {
      return -1;
    } else {
      return 0;
    }
  }
};

#endif // __FunzioneBase__