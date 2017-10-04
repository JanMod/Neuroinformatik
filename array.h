#ifndef ARRAY_H
#define ARRAY_H
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <array>
#include <qDebug>
#include <vector>
#include <crtdbg.h>

class Array
{
public:
     enum Type{ weight  , neuron , input, output, act_func_neruon};
     enum Layer{hidden, final, none};
     Type type;
     Layer layer;
     ~Array();
    Array();
    Array(int height, int width);
    void setValue0();
    void setValue1();
    void setRandom();
    void setValue(int i, int j, double value);
    void transpose();
    void copy(Array *A);

    void shuffle(unsigned int seed);

     void setValue(int i, double value);
     double getValue(int i, int j);
     double getValue(int i);
     int getHeight() const;
     int getWidth() const;
    void setAllValues_Negative();
    void swap();
    void addBias(double b);
    void setHeight(int height);

    void setWidth(int width);

    void setSample(int value);

    int getSample() const;

    void copybetween(Array *A);
    void copy(Array *A, int at, int to);
    void copy(Array *A, int at);
    void copy(Array *A, int at, int to, int aat);
    bool getMomentum() const;
    void setMomentum(bool value);

private:
    int Sample=0;
    bool momentum= false;
    int m_height;
    bool bool_transpose;
    int m_width;
    int init_height;
    int inti_width;
    double *m_array;
    bool m_swap;
    std::vector<double> m_Vector;
      void setVector0();
};

#endif // ARRAY_H
