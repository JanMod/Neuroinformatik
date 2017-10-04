#ifndef NEURON_H
#define NEURON_H
#include "neuron_list.h"
#include <qstring.h>

class Neuron
{
public:
    Neuron();
    Neuron(int layer, int row);
     Neuron(int layer, int row, int X, int Y);
     ~Neuron();

private:
    int m_layer;
    int m_row;
    int m_PositionX=0;
    int m_PositionY=0;
    int m_width=10;
    int m_height=10;
    QString m_name;
};

#endif // NEURON_H
