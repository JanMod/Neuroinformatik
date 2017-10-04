#ifndef VECTOR_LIST_H
#define VECTOR_LIST_H
#include <vector>
#include "array.h"
class Vector_list
{
public:
    Vector_list();
    void add(Array* A);
    void add(Array* A, int position);
     std::vector<Array *> m_Vector;
    int getSize();
    void clearList();
    int getLast_element() const;
    Array *getLastArray() const;

private:
    int m_last_element=-1;
     std::vector<Array *> m_Empty;

};

#endif // VECTOR_LIST_H
