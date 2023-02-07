#ifndef __VectorOperations_h__
#define __VectorOperations_h__

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric> // per inner_product
#include <vector>

using namespace std;

// somma di due vettori : somma componente per componente
template <typename T>
vector<T> operator+(const vector<T> &a, const vector<T> &b) {
  if (a.size() != b.size())
    throw "Stai provando a sommare vettori di dimensioni diverse!";
  vector<T> somma(a.size());
  transform(a.begin(), a.end(), b.begin(), somma.begin(), plus<T>());
  return somma;
}

// differenza di due vettori componente per componente
template <typename T>
vector<T> operator-(const vector<T> &a, const vector<T> &b) {
  if (a.size() != b.size())
    throw "Stai provando a sottrarre vettori di dimensioni diverse!";
  vector<T> differenza(a.size());
  transform(a.begin(), a.end(), b.begin(), differenza.begin(), minus<T>());
  return differenza;
}

// prodotto scalare tra due vettori
template <typename T> T operator*(const vector<T> &a, const vector<T> &b) {
  if (a.size() != b.size())
    throw "Stai provando a fare il prodotto scalare tra vettori di dimensioni "
          "diverse!";
  T sum = inner_product(a.begin(), a.end(), b.begin(), 0.);
  return sum;
}

// prodotto tra uno scalare e un vettore
template <typename T> vector<T> operator*(T c, const vector<T> &a) {
  vector<T> risultato(a.size());
  transform(a.begin(), a.end(), risultato.begin(), [&c](T x) { return x * c; });
  return risultato;
}

// prodotto tra un vettore e uno scalare
template <typename T> vector<T> operator*(const vector<T> &a, T c) {
  vector<T> risultato(a.size());
  transform(a.begin(), a.end(), risultato.begin(), [&c](T x) { return x * c; });
  return risultato;
}

// divisione tra un vettore e uno scalare
template <typename T> vector<T> operator/(const vector<T> &a, T c) {
  vector<T> risultato(a.size());
  transform(a.begin(), a.end(), risultato.begin(), [&c](T x) { return x / c; });
  return risultato;
}

// somma ad a un vettore b e il risultato viene messo in a
template <typename T> vector<T> &operator+=(vector<T> &a, const vector<T> &b) {
  if (a.size() != b.size())
    throw "Stai provando a sommare vettori di dimensioni diverse!";
  transform(a.begin(), a.end(), b.begin(), a.begin(), plus<T>());
  return a;
}

// sottrai ad a un vettore b e il risultato viene messo in a
template <typename T> vector<T> &operator-=(vector<T> &a, const vector<T> &b) {
  if (a.size() != b.size())
    throw "Stai provando a sottrarre vettori di dimensioni diverse!";
  transform(a.begin(), a.end(), b.begin(), a.begin(), minus<T>());
  return a;
}

// Metodi con vettori

// metodo comodo per stampare il vettore
template <typename T> void Print(const vector<T> &v) {
  cout << "Stampo il vettore" << endl;
  for (auto it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";
  }
  cout << endl << "Il vettore è stato stampato" << endl;
}

#endif // __VectorOperations_h__