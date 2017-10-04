#include "array.h"

Array::~Array()
{
    //  delete this;
    //m_Vector.swap(m_Empty);

 //       _CrtDumpMemoryLeaks();
 //   m_Vector.clear();
//    m_Vector.shrink_to_fit();
 //   delete m_Vector;
    //m_Vector.swap(m_Empty);



    // qDebug()<<"Deleted";
}

Array::Array()
{

}

Array::Array(int height, int width)
{
     srand(time(NULL));
    if(width>=1 && height>=1)
    {
        m_array=0;

        bool_transpose=false;
        inti_width= width;
        init_height= height;
        m_width= width;
        m_height= height;
        setVector0 ();
        m_swap=false;


    }
    else{
        qDebug()<<"Height or width can`t be 0";
    }
}

void Array::setValue0()
{
    for(int i=0;i<init_height;i++)
    {
        for(int j=0;j<inti_width;j++)
        {
            if(bool_transpose==false)
            {
                m_Vector[j+i*inti_width]=0;
            }
            else
            {
                m_Vector[i+j*inti_width]=0;
            }
        }
    }
}

void Array::setValue1()
{
    for(int i=0;i<init_height;i++)
    {
        for(int j=0;j<inti_width;j++)
        {
            if(bool_transpose==false)
            {
                m_Vector[j+i*inti_width]=0.5;
            }
            else
            {
                m_Vector[i+j*inti_width]=0.5;
            }
        }
    }

}

void Array::setRandom()
{
    time_t timer;


    double rnd_Number1;
    double rnd_Number2;
    for(int h=0;h<m_height;h++)
    {
        for(int w=0;w<inti_width;w++)
        {

            //
            double result;
            rnd_Number1 = -0.5 +(rand() / double(RAND_MAX));
            qDebug()<<rnd_Number1;
            //rnd_Number1 = rand()%20;
            //rnd_Number2 = rand()%20;
            if(rnd_Number1 == 0 || rnd_Number2 == 0)
            {
                setValue(h,w,0.1);
            }
            else{


                result= rnd_Number1;
                setValue(h,w,result);
            }
        }
    }
    qDebug()<<"";
}

void Array::setValue(int i, int j, double value)
{

    if(bool_transpose==false)
    {
        if(!m_swap)
        {
            m_Vector[j+i*inti_width]=value;
        }
        else
        {
            m_Vector[j+(m_height-i)*inti_width]=value;
        }
    }
    else
    {
        if(!m_swap)
        {
            m_Vector[i+j*inti_width]=value;
        }
        else
        {
            m_Vector[(m_height-i)+j*inti_width]=value;
        }
    }
}

void Array::transpose()
{
    int t_m_width=m_width;
    m_width=m_height;
    m_height=t_m_width;

    if(bool_transpose==false)
    {
        bool_transpose=true;
    }
    else{
        bool_transpose=false;
    }

}

void Array::copy(Array *A)
{
    for(int h=0;h<m_height;h++)
    {
        for(int w=0;w<inti_width;w++)
        {
        double Value= A->getValue(h,w);
        setValue(h,w,Value);
        Value=0;
        }
    }

}

void Array::copy(Array *A, int at)
{
    for(int h=0;h<m_height;h++)
    {
        for(int w=0;w<inti_width;w++)
        {
        double Value= A->getValue(h+at,w);
        setValue(h,w,Value);
        Value=0;
        }
    }

}


void Array::copy(Array *A, int at, int to)
{
    for(int h=at;h<to;h++)
    {
        for(int w=0;w<inti_width;w++)
        {
        double Value= A->getValue(h,w);
        if (at!=0)
        {
               setValue(h-23,w,Value);
        }
        else{
              setValue(h,w,Value);
        }

        Value=0;
        }
    }

}

void Array::copy(Array *A, int at, int to, int aat)
{
    for(int h=at;h<to;h++)
    {
        for(int w=0;w<inti_width;w++)
        {
        double Value= A->getValue(h,w);

               setValue(h-aat,w,Value);



        Value=0;
        }
    }

}

bool Array::getMomentum() const
{
    return momentum;
}

void Array::setMomentum(bool value)
{
    momentum = value;
}

void Array::copybetween(Array *A)
{
    for(int h=24;h<47;h++)
    {
        for(int w=0;w<inti_width;w++)
        {
        double Value= A->getValue(h,w);
        setValue(h-24,w,Value);
        Value=0;
        }
    }

}


void Array::shuffle(unsigned int seed)
{
 std::srand(seed);
 std::random_shuffle ( m_Vector.begin(), m_Vector.end());
}

void Array::setValue(int i, double value)
{
    if(!m_swap)
    {
        m_Vector[i]=value;
    }
    else
    {
        m_Vector[m_height-i]=value;
    }
}

double Array::getValue(int i, int j)
{
    if(bool_transpose==false)
    {
        if(!m_swap)
        {
            return m_Vector[j+i*inti_width];
        }
        else
        {
            return m_Vector[j+(m_height-i)*inti_width];
        }

    }
    else{
        if(!m_swap)
        {
            return m_Vector[i+j*inti_width];
        }
        else
        {
            return m_Vector[(m_height-i)+j*inti_width];
        }
    }
}

double Array::getValue(int i)
{

    if(bool_transpose==false)
    {
        return m_Vector[i*inti_width];
    }
    else{
        return m_Vector[i];
    }
}

int Array::getHeight() const
{
    return m_height;
}

int Array::getWidth() const
{
    return m_width;
}

void Array::setAllValues_Negative()
{
    for(int i=0;i<init_height;i++)
    {
        for(int j=0;j<inti_width;j++)
        {


            if(bool_transpose==false)
            {
                double value= m_Vector[j+i*inti_width];
                m_Vector[j+i*inti_width]=-value;
            }
            else
            {
                double value= m_Vector[j+i*inti_width];
                m_Vector[i+j*inti_width]=-value;
            }
        }
    }
}

void Array::swap()
{
    if(!m_swap)
    {
        m_swap=true;
    }
    else
    {
        m_swap=false;
    }
}

void Array::addBias(double b)
{
    inti_width+=1;
    m_width= inti_width;

    for(int i=0;i<init_height;i++)
    {
    int j=inti_width-1;
    m_Vector.insert(m_Vector.begin()+j+i*inti_width, b);
    }

}

void Array::setHeight(int height)
{
    m_height = height;

}

void Array::setWidth(int width)
{
    m_width = width;
}

void Array::setSample(int value)
{
    Sample = value;
}

int Array::getSample() const
{
    return Sample;
}

void Array::setVector0()
{
    for(int i=0;i<init_height;i++)
    {
        for(int j=0;j<inti_width;j++)
        {
            m_Vector.push_back(0);
        }
    }
}
