#ifndef __funzioniutili__
#define __funzioniutili__

#include "TGraph.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std;

class TGraphData {
public:
  vector<double> x;
  vector<double> y;
};

template <typename T> vector<T> read_all(const char *filename) {
  ifstream f(filename);
  vector<T> data;
  if (!f) {
    cout << "Errore apertura del file!" << endl;
    exit(0);
  } else{
      istream_iterator<double> start(f), end;
      vector<T> v(start, end);
      f.close();
      return v;
    }
}

template <typename T> double media(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end) {
  double sum = accumulate(begin, end, 0.0);
  return sum / double(end - begin);
}

template <typename T> double varianza(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end) {
  double m = media<T>(begin, end);

  vector<double> v;
  for(auto it = begin; it != end; it++)
    v.push_back(pow(*it, 2));

  return (media<T>(v.begin(), v.end()) - pow(m, 2));
}

template <typename T> double varianza(vector<T> v) {
  double m = media<T>(v.begin(), v.end());
  double sum = 0;

  for(int i = 0; i < v.size(); i++) {
    sum += pow(v[i] - m, 2);
  }

  return sum / double(v.size());
}

template <typename T> double mediana(const vector<T> v) {
  vector<T> temp = v;
  sort(temp.begin(), temp.end());
  double m;

  if (temp.size() % 2 == 0) {
    m = (temp[(temp.size() / 2) - 1] + temp[temp.size() / 2]) / 2;
  } else
    m = temp[temp.size() / 2];

  return m;
}

template <typename T> void print(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end) {
  for(begin; begin != end; begin++)
    cout << *begin << endl;
}

template <typename T> void print(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end, const char *filename) {
  ofstream f(filename);
  copy(begin, end, ostream_iterator<T>(f, "\n"));
  f.close();
}

unsigned int cifresignificative(double precisione) {
  return (unsigned int)-log10(precisione);
}

void fill_graph(TGraph& graph, TGraphData& data) {
  for (int i = 0; i < min(data.x.size(), data.y.size()); i++) {
    graph.AddPoint(data.x[i], data.y[i]);
  }
}

TGraph *tgraph_with_data(TGraphData& data) {
  TGraph *graph = new TGraph();
  for (int i = 0; i < min(data.x.size(), data.y.size()); i++) {
    graph->AddPoint(data.x[i], data.y[i]);
  }
  return graph;
}

#endif