#include "tools.h"
#include <array>
#include "qdebug.h"
#include <string>
Tools::Tools()
{

}

Array *Tools::SumWeightMatrix(Array *A)
{
    double value=0;
    Array *C = new Array (A->getHeight(),A->getWidth());
    for(int j=0;j<A->getWidth();j++)
    {

        value=0;
        for(int i=0;i<A->getHeight();i++)
        {
            value+= A->getValue(i,j);
        }
        for(int k=0;k<A->getHeight();k++)
        {
            C->setValue(k,j,value);
        }
    }
    return C;
}

Array *Tools::Copy(Array *A)
{
    Array *B= new Array(A->getHeight(),A->getWidth());
    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0;j<A->getWidth();j++)
        {
            B->setValue(i,j,A->getValue(i,j));
        }
    }
    return B;
}

Array *Tools::Copy(Array *A, Array *B)
{

    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0;j<A->getWidth();j++)
        {
            B->setValue(i,j,A->getValue(i,j));
        }
    }

}

Array *Tools::Matrixmultiplikation_Bias(Array *A, Array *B, double Bias)
{

    int A_height=A->getHeight();
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    int B_width=B->getWidth();
    if(A_width!=B_height)
    {
        qDebug()<<"Matrixmuliplication: Matrix A Breite ungleich Matrix B Hoehe!";
        return 0;
    }
    Array *C = new Array (A_height,B_width);
    double value;

    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0;j<B->getWidth();j++)
        {
            value=0;
            for(int k = 0;k<A_width;k++)
            {

                value += A->getValue(i,k)*B->getValue(k,j);

            }
            value+=Bias*(-1);

            C->setValue(i,j, (value));

        }
    }

    return C;
}

Array* Tools::Matrixmultiplikation(Array *A, Array *B)
{

    int A_height=A->getHeight();
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    int B_width=B->getWidth();
    if(A_width!=B_height)
    {
        qDebug()<<"Matrixmuliplication: Matrix A Breite ungleich Matrix B Hoehe!";
        return 0;
    }
    Array *C = new Array (A_height,B_width);
    double value=0;
    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0;j<B->getWidth();j++)
        {
            value=0;
            for(int k = 0;k<A_width;k++)
            {
                value += A->getValue(i,k)*B->getValue(k,j);

            }
            C->setValue(i,j, value);

        }
    }
    return C;
}

void Tools::Matrixmultiplikation(Array *A, Array *B, Array *C)
{


    double value=0;
    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0;j<B->getWidth();j++)
        {
            value=0;
            for(int k = 0;k<A->getWidth();k++)
            {
                value += A->getValue(i,k)*B->getValue(k,j);

            }

            C->setValue(i,j, value);
        }
    }
}

void Tools::output(Array *A)
{



    QString row="";

    for(int i=0;i<A->getHeight();i++)
    {
        row="";
        for(int j=0;j<A->getWidth();j++)
        {
            row+= row.number(A->getValue(i,j));
            row+="  ";

        }
        qDebug()<<row;
    }
    qDebug()<<" ";
}

Array *Tools::SigmoidAbleitung(Array *A)
{
    int A_height=A->getHeight();
    int A_width=A->getWidth();

    double value=0;
    Array *C= new Array (A_height,A_width);
    for(int i=0;i<A_height;i++)
    {
        for(int j=0 ; j<A_width; j++)
        {
            value=A->getValue(i,j)*(1-A->getValue(i));
            C->setValue(i,value);
            value=0;
        }
    }
    return C;
}

Array *Tools::SigmoidAbleitung(Array *A, Array *C)
{
    int A_height=A->getHeight();
    int A_width=A->getWidth();

    double value=0;
    for(int i=0;i<A_height;i++)
    {
        for(int j=0 ; j<A_width; j++)
        {
            value=A->getValue(i,j)*(1.0-A->getValue(i));
            C->setValue(i,value);
            value=0;
        }
    }

}

Array *Tools::TanhAbleitung(Array *A)
{
    int A_height=A->getHeight();
    int A_width=A->getWidth();

    double value=0;
    Array *C= new Array (A_height,A_width);
    for(int i=0;i<A_height;i++)
    {
        for(int j=0 ; j<A_width; j++)
        {
            value=(1.0+A->getValue(i,j))*A->getValue(i,j);
            C->setValue(i,value);
            value=0;
        }
    }
    return C;
}

Array *Tools::TanhAbleitung(Array *A, Array *C)
{

    double value=0;
    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0 ; j<A->getWidth(); j++)
        {
           // value=(1+tanh(A->getValue(i,j)))*1-tanh(A->getValue(i,j));
            value=1.0-(A->getValue(i,j)*A->getValue(i,j));
            C->setValue(i,j,value);

            value=0;
        }
    }

}

Array *Tools::vektorAddition(Array *A, Array *B)
{
    int A_height=A->getHeight();
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    if(A_height!=B_height)
    {
        qDebug()<<"Vectoraddition: A height not equal with B height";
        return 0;
    }
    double value=0;
    Array *C= new Array (A_height,A_width);
    for(int i=0;i<A_height;i++)
    {
        value=A->getValue(i)+B->getValue(i);
        C->setValue(i,value);
        value=0;
    }
    return C;
}

Array *Tools::vektorAddition(Array *A, Array *B, Array *C)
{


    if(A->getHeight()!=B->getHeight())
    {
        qDebug()<<"Vectoraddition: A height not equal with B height";
        return 0;
    }
    double value=0;

    for(int i=0;i<A->getHeight();i++)
    {
        value=A->getValue(i)+B->getValue(i);
        C->setValue(i,value);
        value=0;
    }

}

Array *Tools::vektorSubtraktion(Array *A, Array *B)
{
    int A_height=A->getHeight();
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    if(A_height!=B_height)
    {
        qDebug()<<"Vectorsubtraction: A height not equal with B height";
        return 0;
    }
    double value=0;
    Array *C= new Array (A_height,A_width);
    for(int i=0;i<A_height;i++)
    {
        value=A->getValue(i)-B->getValue(i);
        C->setValue(i,value);
        value=0;
    }
    return C;
}

Array *Tools::vektorSubtraktion(Array *A, Array *B, Array *C)
{
    int A_height=A->getHeight();
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    if(A_height!=B_height)
    {
        qDebug()<<"Vectorsubtraction: A height not equal with B height";
        return 0;
    }
    double value=0;

    for(int i=0;i<A_height;i++)
    {
        value=A->getValue(i)-B->getValue(i);
        C->setValue(i,value);
        value=0;
    }

}

Array *Tools::skalarMultiplikation(Array *A, Array *B)
{
    int A_height=A->getHeight();
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    if((A_height!=B_height) || (A->getWidth()!= B->getWidth()))
    {
        qDebug()<<"Scalarmultiplication: A height not equal with B height";

    }
    double value=0;
    Array *C= new Array (A_height,A_width);
    for(int i=0;i<A_height;i++)
    {
        for(int j=0;j<A_width;j++)
        {

            value=A->getValue(i,j)*B->getValue(i,j);
            C->setValue(i,j,value);
            value=0;
        }
    }
    return C;
}

Array *Tools::skalarMultiplikation(Array *A, Array *B, Array *C)
{
    int A_height=A->getHeight();
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    if((A_height!=B_height) || (A->getWidth()!= B->getWidth()))
    {
        qDebug()<<"Scalarmultiplication: A height not equal with B height";

    }
    double value=0;
//    Array *C= new Array (A_height,A_width);
    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0;j<A->getWidth();j++)
        {

            value=A->getValue(i,j)*B->getValue(i,j);
            C->setValue(i,j,value);
            value=0;
        }
    }

}

Array *Tools::skalarMultiplikation_lernrate(Array *A, Array *B, double r, int iterationen)
{
    int A_height=A->getHeight();
    int A_width=A->getWidth();
    int B_height=B->getHeight();

    if(A_height!=B_height)
    {
        qDebug()<<"Scalarmultiplication learnrate: A height not equal with B height";

    }

    if(A->getWidth()!=B->getWidth())
    {
        qDebug()<<"Scalarmultiplication learnrate: A width not equal with B width";

    }
    double value=0;

    for(int i=0;i<A_height;i++)
    {
        for(int j=0;j<A_width; j++)
        {
            value=A->getValue(i,j)+(r*B->getValue(i,j));
            A->setValue(i,j,value);
            value=0;
        }
    }

}

void Tools::Matrixmultiplikation_Bias(Array *A, Array *B, Array *C, double Bias)
{
    int B_height=B->getHeight();
    int A_width=A->getWidth();
    if(A_width!=B_height)
    {
        qDebug()<<"Matrixmultiplication Bias: Matrix A Breite ungleich Matrix B Hoehe!";
        return ;
    }
    double value;

    for(int i=0;i<A->getHeight();i++)
    {
        for(int j=0;j<B->getWidth();j++)
        {
            value=0;
            for(int k = 0;k<A_width;k++)
            {

                value += A->getValue(i,k)*B->getValue(k,j);

            }
            value+=Bias*(-1);

            C->setValue(i,j, (value));

        }
    }


}


Array *Tools::square_error(Array *is, Array *soll)
{
    Array *C= new Array(is->getHeight(),is->getWidth());
    for(int i=0;i<is->getHeight();i++)
    {

        for(int j=0;j<is->getWidth();j++)
        {
            double out= is->getValue(i,j);
            double temp_soll= soll->getValue(i,j);
            double error=0;
            error= 0.5*((-temp_soll)*(out-temp_soll)) ;
            C->setValue(i,j, error );

        }
    }
    return C;
}

double Tools::square_error_overall(Array *is, Array *soll)
{
    double error=0;
    double error_temp=0;
    for(int i=0;i<is->getHeight();i++)
    {
        for(int j=0;j<is->getWidth();j++)
        {
            double out= is->getValue(i,j);
            double temp_soll= soll->getValue(i,j);
            error_temp= ((out-temp_soll)*(out-temp_soll)) ;
            //   qDebug()<<"Error: "<<error_temp;
            error+=0.5*error_temp;
        }
    }
    return error;
}

void Tools::shuffle(Array *A, Array *B)
{
    auto seed = unsigned (std::time(0));
    output(A);
    A->shuffle(seed);
    qDebug()<<"Shuffle";
   output(A);
    B->shuffle(seed);
   output(B);

}

double Tools::Random()
{
    double rnd_Number1;
    double rnd_Number2;
    double result;
    srand(time(NULL));
    rnd_Number1 = rand()%50;
    rnd_Number2 = rand()%50;
    result= rnd_Number1/rnd_Number2;
    return result;
}

void Tools::Matrixmultiplication_Stocastic(Array *A, Array *B, Array *C, int sample)
{

    double value=0;
  for(int j=0;j<B->getWidth();j++)
        {
            value=0;
            for(int k = 0;k<A->getWidth();k++)
            {
                value += A->getValue(sample,k)*B->getValue(k,j);

            }
            C->setValue(0,j,value);
    }
}

void Tools::WeightUpdateMomentum(Array *weight, Array* previous_weight, Array *delta, Array *previous_Delta, double learnrate, double alpha, bool bias, double error, double previous_error)
{


    double value=0;

    double etamax=0.1;
    for(int i=0;i<weight->getHeight();i++)
    {
        for(int j=0;j<weight->getWidth(); j++)
        {
        //Bold Driver
            if(previous_Delta!= NULL){
/*                double d1=weight->getValue(i,j) - previous_weight->getValue(i,j);
                double d2= delta->getValue(i,j) - previous_Delta->getValue(i,j);
                eta= (d1*d1)/(d1*d2);

                if(eta<0)
                {
                    eta= eta*(-1);
                }
                //http://www.math.upatras.gr/~dgs/papers/reports/tr98-02.pdf
                if(eta >etamax)
                {
                    eta=etamax;
                }*/
                //Bold Driver

                if(error<previous_error)
                {
                 //   learnrate = learnrate*1.2;
                }
                else{
                 //   weight->setValue(i,j,previous_weight->getValue(i,j));
                 //   learnrate = learnrate*0.5;
                }
            }
            if(previous_Delta!= NULL)
            {
                if(bias && i== weight->getHeight()-1)
                {
                    value=weight->getValue(i,j)+(learnrate*delta->getValue(i,j));
                }
                else{
                //    value=weight->getValue(i,j)-(learnrate*delta->getValue(i,j))+ alpha* previous_Delta->getValue(i,j); Momentum
                     value=weight->getValue(i,j)-(learnrate*delta->getValue(i,j));
                }
            }
            else
            {
                if(bias && i== weight->getHeight()-1){
                    value=weight->getValue(i,j)+(learnrate*delta->getValue(i,j));
                }
                else
                {
                    //value=weight->getValue(i,j)-(learnrate*delta->getValue(i,j))+ alpha* previous_Delta->getValue(i,j);
                    value=weight->getValue(i,j)+(learnrate*delta->getValue(i,j));
                }
            }
            weight->setValue(i,j,value);
            value=0;
        }
    }

}

void Tools::WeightUpdateMomentum(Array *weight, Array* previous_weight, Array *delta, Array *previous_Delta, Array *learnrate, double alpha, bool bias, double error, double previous_error)
{

    if(weight->getHeight()!=delta->getHeight())
    {
        qDebug()<<"Scalarmultiplication learnrate: A height not equal with B height";

    }

    if(weight->getWidth()!=delta->getWidth())
    {
        qDebug()<<"Scalarmultiplication learnrate: A width not equal with B width";

    }
    double value=0;

    double etamax=0.1;
    for(int i=0;i<weight->getHeight();i++)
    {
        for(int j=0;j<weight->getHeight(); j++)
        {
        //Bold Driver
            if(previous_Delta!= NULL){
/*                double d1=weight->getValue(i,j) - previous_weight->getValue(i,j);
                double d2= delta->getValue(i,j) - previous_Delta->getValue(i,j);
                eta= (d1*d1)/(d1*d2);

                if(eta<0)
                {
                    eta= eta*(-1);
                }
                //http://www.math.upatras.gr/~dgs/papers/reports/tr98-02.pdf
                if(eta >etamax)
                {
                    eta=etamax;
                }*/
                //Bold Driver
/*
                if(error<previous_error)
                {
                    learnrate = learnrate*1.05;
                }
                else{
                    weight->setValue(i,j,previous_weight->getValue(i,j));
                    learnrate = learnrate*0.5;
                }
            }
            if(previous_Delta!= NULL)
            {
                if(bias && i== weight->getHeight()-1)
                {
                    value=weight->getValue(i,j)+(learnrate*delta->getValue(i,j));
                }
                else{
                    value=weight->getValue(i,j)+(learnrate*delta->getValue(i,j))+ alpha* previous_Delta->getValue(i,j);
                }
            }
            else
            {
                if(bias && i== weight->getHeight()-1){
                    value=weight->getValue(i,j)+(learnrate*delta->getValue(i,j));
                }
                else
                {
                    value=weight->getValue(i,j)+(learnrate*delta->getValue(i,j));
                }
            }
            weight->setValue(i,j,value);
            value=0;*/
        }
        }
    }

}

