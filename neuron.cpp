#include "neuron.h"

Neuron::Neuron()
{

}

Neuron::Neuron(int layer, int row)
{
    m_layer=layer;
    m_row=row;
}

Neuron::Neuron(int layer, int row, int X, int Y)
{
    m_layer=layer;
    m_row=row;
    m_PositionX=X;
    m_PositionY=Y;
}

Neuron::~Neuron()
{
}
