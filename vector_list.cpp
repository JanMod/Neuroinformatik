#include "vector_list.h"

Vector_list::Vector_list()
{

}

void Vector_list::add(Array *A)
{   m_last_element++;
    m_Vector.push_back(A);
}

void Vector_list::add(Array *A, int position)
{
    m_last_element++;
    m_Vector.insert(m_Vector.begin()+position, A);
}

int Vector_list::getSize()
{
    return m_Vector.size();
}

void Vector_list::clearList()
{
    m_Vector.swap(m_Empty);
}

int Vector_list::getLast_element() const
{
    return m_last_element;
}

Array *Vector_list::getLastArray() const
{


    return m_Vector.at(m_last_element);

}

