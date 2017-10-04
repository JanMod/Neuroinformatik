#include "learning.h"
#include <QtCore>
#include <stdlib.h>
void Learning::run()
{
    build();
    Array *F=list.m_Vector.at(list.getLast_element());
    m_error=tool.square_error_overall(m_Output,F);
    forward_pass();

    while(m_error>0.0001)
    {
        back_propagation();
        /*  m_Input->swap();
        m_Output->swap();
        F->swap();*/
        forward_pass();
        m_error=tool.square_error_overall(m_Output,F);
        error[1]=error[0];
        error[0]=m_error;
        qDebug()<<"Iterationen "<<m_iteration++ <<" | Error overall "<<m_error;

        if(m_iteration%100==0)
        {
            emit plot(m_iteration, m_error);
        }
    }
}

Learning::Learning(QObject *parent)
{

}

Learning::Learning(Array *In, Array *Out)
{

}

Learning::Learning(Array *In, Array *Out, int Number_of_Hiddenneuron, double learning_rate, double alpha, double Bias)
{
    qDebug()<<"Test";
    m_Bias=Bias;
    m_alpha = alpha;
    m_learning_rate= learning_rate;
    m_number_of_Hiddenneuron = Number_of_Hiddenneuron;
    if(m_Bias != 0)
    {
        In->addBias(m_Bias);
        bias=true;
    }
    m_Input=In;
    tool.output(m_Input);
    m_Output=Out;
    previous_delta.add(NULL);
    previous_delta.add(NULL);
    previous_weight.add(NULL);
    previous_weight.add(NULL);

}


void Learning::forward_pass()
{

    for(int layer=0;layer<=list.getSize()-2;layer+=3)
    {

        tool.Matrixmultiplikation(list.m_Vector.at(layer),list.m_Vector.at(layer+1),list.m_Vector.at(layer+2));
        toTanH(list.m_Vector.at(layer+2),list.m_Vector.at(layer+3));
        // toSigmoid(list.m_Vector.at(layer+2),list.m_Vector.at(layer+3)); Sigmoid
    }
    //  tool.output(list.m_Vector.at(list.getLast_element()));
}

void Learning::weightUpdate(Array *weight, Array* previous_w, Array *delta, Array *previous_d, int position )
{
    Array *old_weight= tool.Copy(weight);
    if (previous_d == NULL)
    {
        tool.WeightUpdateMomentum(weight,NULL, delta,NULL,m_learning_rate, m_alpha, bias,error[0],error[1]);
    }
    else {
        tool.WeightUpdateMomentum(weight,previous_w, delta,previous_d,m_learning_rate, m_alpha ,bias,error[0],error[1] );

        delete previous_d;
        delete previous_w;
        previous_d= NULL;
        previous_w = NULL;
    }

    previous_delta.m_Vector[position]= delta;
    previous_weight.m_Vector[position]= old_weight;
}

void Learning::square_error()
{


}

void Learning::back_propagation()
{


    Array *y_y_is = tool.vektorSubtraktion(m_Output,list.m_Vector.at(list.getLast_element()));
    Array *TanhAbleitung = tool.TanhAbleitung(list.m_Vector.at(list.getLast_element()-1));
    Array *Delta = tool.skalarMultiplikation( TanhAbleitung , y_y_is);
    for(int layer=list.getSize()-3;layer>0;layer-=3)
    {
        Array *deltaW2;
        Array *weight = list.m_Vector.at(layer);
        if(layer==list.getSize()-3)//final Layer
        {
            Array *outh = list.m_Vector.at(layer-1);
            outh->transpose();
            deltaW2= tool.Matrixmultiplikation(outh,Delta);
            outh->transpose();
        }
        else{
            Array *weight2 = list.m_Vector.at(layer+3);

            Array *neth = list.m_Vector.at(layer+1);
            if(bias)
            {neth->setWidth(neth->getWidth()-1);
                weight2->setHeight(weight2->getHeight()-1);}
            Array *neth_d= tool.TanhAbleitung(neth);
            //    Array *neth_d= tool.SigmoidAbleitung(list.m_Vector.at(layer+1));
            weight2->transpose();
            Array *delta_w2= tool.Matrixmultiplikation(Delta,weight2);
            Array *delta_w2_neth_d = tool.skalarMultiplikation(delta_w2,neth_d);

            m_Input->transpose();

            Array *deltaW1 = tool.Matrixmultiplikation(m_Input,delta_w2_neth_d );
            
            weight2->transpose();
            m_Input->transpose();
            if(bias)
            {neth->setWidth(neth->getWidth()+1);
                weight2->setHeight(weight2->getHeight()+1);
            }



            //weight update
            weightUpdate(weight,previous_weight.m_Vector[0],deltaW1,previous_delta.m_Vector[0],0);
            weightUpdate(weight2,previous_weight.m_Vector[1],deltaW2,previous_delta.m_Vector[1],1);

            delete  neth_d;
            delete  delta_w2;
            delete  delta_w2_neth_d;
            neth_d           =NULL;
            delta_w2         =NULL;
            delta_w2_neth_d  =NULL;

        }
    }
    delete TanhAbleitung;
    delete y_y_is;
    delete Delta ;
    y_y_is= NULL;
    Delta = NULL;
    TanhAbleitung = NULL;
}

int Learning::getIteration() const
{
    return m_iteration;
}

void Learning::build()
{
    Array *weight_to_H = new Array (m_Input->getWidth(),m_number_of_Hiddenneuron);
    Array *Neth= new Array(m_Input->getHeight(),weight_to_H->getWidth());
    Array *Outh= new Array(m_Input->getHeight(),weight_to_H->getWidth());
    Array *Neto= new Array(m_Output->getHeight(), m_Output->getWidth());
    Array *Outo= new Array(m_Output->getHeight(), m_Output->getWidth());
    if (bias)
    {
        
     //   Neth->addBias(m_Bias);
     //   Outh->addBias(m_Bias);
    }
    Array *weight_to_O = new Array (Outh->getWidth(), m_Output->getWidth());

    weight_to_H->setRandom();
    weight_to_O->setRandom();
    list.add(m_Input);
    list.add(weight_to_H);
    list.add(Neth);
    list.add(Outh);
    list.add(weight_to_O);
    list.add(Neto);
    list.add(Outo);
}

void Learning::toSigmoid(Array *A, Array *B)
{
    double Sum=0;
    for(int i=0;i<A->getHeight();i++){
        for(int k=0;k<A->getWidth();k++)
        {
            Sum=A->getValue(i,k);
            Sum= 1/(1+pow(exp(1),-Sum));
            B->setValue(i,k,Sum);


        }
    }
    qDebug()<<"Sigmoid";
    tool.output(B);
}

void Learning::setLearning_rate(double learning_rate)
{
    m_learning_rate = learning_rate;
}

void Learning::setAlpha(double alpha)
{
    m_alpha = alpha;
}

void Learning::toTanH(Array *A, Array *B)
{
    double Sum=0;
    for(int i=0;i<A->getHeight();i++){
        for(int k=0;k<A->getWidth();k++)
        {
            if(A->getValue(i,k) == 1 )
            {
                B->setValue(i,k,1);
            }
            else
            {
                Sum=A->getValue(i,k);
                Sum= tanh(Sum);
                B->setValue(i,k,Sum);
            }
        }
    }
}

double Learning::getError() const
{
    return m_error;
}

Array *Learning::getOutput() const
{
    if(!list.m_Vector.empty()){
        return list.getLastArray();
    }
    return NULL;
}

void Learning::GradientChecking(Array *Weight1, Array *Weigth2)
{
    /*
    double x=1.5;
    Array* GradWeigth1= new Array(Weight1->getHeight(),Weight1->getWidth());
    Array* GradWeigth2= new Array(Weight2->getHeight(),Weight2->getWidth());
    double epsilon = 0.001;
    for (int i = 0;i<Weight1->getHeight();i++)
    {
        for (int j= 0 ; j<Weight1->getWidth(); j++)
        {


            double num_grad = 0 ;
            GradientChecking->setValue(i,j,num_grad);
        }
    }
    */
}

Vector_list Learning::getList() const
{
    return list;
}

void Learning::delete_from_list()
{

}

void Learning::draw_to_mainwindow()
{

}
