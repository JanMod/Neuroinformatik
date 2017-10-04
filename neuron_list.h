#ifndef NEURON_LIST_H
#define NEURON_LIST_H
#include <list>
#include "array.h"
#include "neuron.h"
class Neuron_list
{
public:
    Neuron_list();
    void add_to_List(Array *A);
    int size();
    Array *getArray(int layer);
private:
   static std::list<Array * >m_List;
};

#endif // NEURON_LIST_H
