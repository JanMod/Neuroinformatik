#include "learningStochastic.h"
#include <QtCore>
#include <stdlib.h>


learningStochastic::learningStochastic(Array *In, Array *Out, int Number_of_Hiddenneuron, double learning_rate, double alpha, double Bias, int Batchsize)
{
    miniBatch_size= Batchsize;
    m_Bias=Bias;
    m_alpha = alpha;
    m_learning_rate= learning_rate;
    m_number_of_Hiddenneuron = Number_of_Hiddenneuron;

    if(m_Bias != 0) // Fügt den Bias hinzu falls er ausgewählt worden ist
    {
        In->addBias(m_Bias);
        bias=true;
    }
    m_Input=In;
    tool.output(m_Input);
    m_Output=Out;

}

void learningStochastic::run()
{
    build();
    m_error =1;
    int SampleSize= m_Input->getHeight();
    Array *input_sample= new Array (miniBatch_size,m_Input->getWidth());
    Array * output_sample = new Array (miniBatch_size,m_Output->getWidth());
    Array * output_soll = new Array (miniBatch_size,m_Output->getWidth());
    Array * out=list.m_Vector[7];


    while(true) // Bis der User stoppt
    {
        for(int sample=0; sample<SampleSize;sample+=miniBatch_size) //
        {
            for(int i=sample;i<sample+miniBatch_size;i++)
            {
                for(int j=0;j<m_Input->getWidth();j++)
                {
                    input_sample->setValue(i-sample,j,m_Input->getValue(i,j)); // m_Input[N] in einen Testsample umwandeln
                }

                output_soll->setValue(i-sample,m_Output->getValue(i));// m_Output[N] in einen Testsample umwandeln
            }


            forward_pass(input_sample, output_sample); //  Forwardpass des Inputsamples
            for(int i=sample;i<sample+miniBatch_size;i++)
            {
                out->setValue(i,output_sample->getValue(i-sample)); // Fügt das Ergebnis aus dem Forwardpass dem Output hinzu
            }
            //Ruft den Backpropagation-Algorithmus
            backpropagation(input_sample,output_sample, output_soll,momentum_list_w1.m_Vector[sample/miniBatch_size], momentum_list_w2.m_Vector[sample/miniBatch_size]);
        }
        m_error=tool.square_error_overall(out,m_Output);//Rechnet den Fehler aus
        qDebug()<<"Iterationen "<<m_iteration++ <<" | Error overall "<<m_error;

        if(m_iteration%100==0) // Alle 100 Iterationen Error und Iterationen zur GUI übergeben
        {
            emit plot(m_iteration, m_error);
        }
    }
}

void learningStochastic::build()
{

    Array *weight_to_H = new Array (m_Input->getWidth(),m_number_of_Hiddenneuron);
    Array *Neth= new Array(miniBatch_size,weight_to_H->getWidth());
    Array *Outh= new Array(miniBatch_size,weight_to_H->getWidth());
    Array *Neto= new Array(miniBatch_size, m_Output->getWidth());
    Array *Outo= new Array(miniBatch_size, m_Output->getWidth());
    Array *Output_sample = new Array(m_Output->getHeight(), m_Output->getWidth());
    if (bias) //Fügt den Bias in der Hiddenschicht hinzu, falls er ausgewählt wurde
    {
        Neth->addBias(m_Bias);
        Outh->addBias(m_Bias);
    }

    Array *weight_to_O = new Array (Outh->getWidth(), m_Output->getWidth());

    weight_to_H->setRandom(); // Random [-0.5,0.5]
    weight_to_O->setRandom();

    //Für jeden Batchsize eine Datenstruktur für den Iterator-1 Gewichtsveränderung
    for(int i=0;i<m_Input->getHeight()/miniBatch_size;i++)
    {
        Array *momentum_w1= new Array(weight_to_H->getHeight(), weight_to_H->getWidth());
        momentum_list_w1.add(momentum_w1);

        Array *momentum_w2= new Array(weight_to_O->getHeight(), weight_to_O->getWidth());
        momentum_list_w2.add(momentum_w2);
    }
    //Fügt das Erstellte in eine liste ein
    list.add(m_Input);
    list.add(weight_to_H);
    list.add(Neth);
    list.add(Outh);
    list.add(weight_to_O);
    list.add(Neto);
    list.add(Outo);
    list.add(Output_sample);

    //Backpropgation temporäre lokale Variablen zur schrittweisen Berrechnung von dem Backpropagation-Algorithmus
    y_y_is = new Array(miniBatch_size,m_Output->getWidth());
    TanhAbleitung = new Array(Neto->getHeight(),Neto->getWidth());
    Delta = new Array(Neto->getHeight(), Neto->getWidth());
    deltaW2 = new Array(weight_to_O->getHeight(),weight_to_O->getWidth());
    neth_d = new Array(Neth->getHeight(), Neth->getWidth());
    delta_w2 = new Array( Delta->getHeight(),weight_to_O->getHeight());
    delta_w2_neth_d = new Array (Neth->getHeight(),Neth->getWidth());
    deltaW1 = new Array(weight_to_H->getHeight(), weight_to_H->getWidth());
}

void learningStochastic::forward_pass(Array *input, Array * output)
{
    tool.Matrixmultiplikation(input, list.m_Vector[1],list.m_Vector[2]); // Net_h =Input[sample] * Weight1
    toTanH(list.m_Vector[2], list.m_Vector[3]); //a(Net_h) = tanh(Net_h)

    tool.Matrixmultiplikation(list.m_Vector[3],list.m_Vector[4], list.m_Vector[5]); // Net_o = Out_h*Weight2
    toTanH(list.m_Vector[5], output); // out[sample] = a(Net_o) = tanh(Net_o)
}

void learningStochastic::toTanH(Array *A, Array *B)
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

void learningStochastic::backpropagation(Array *input, Array * Outo, Array* output_soll, Array *previous_weight1, Array *previous_weight2)
{
    tool.vektorSubtraktion(Outo ,output_soll, y_y_is); // dError/dOuto = (ist-soll)
    tool.TanhAbleitung(Outo,TanhAbleitung); // neth_h ableitung

    tool.skalarMultiplikation( TanhAbleitung , y_y_is,Delta); // skalarmultiplikation

    Array *weight1 = list.m_Vector[1];
    Array *weight2 = list.m_Vector[4];


    //W2 : Weights2
    Array *outh = list.m_Vector[3];

    outh->transpose();
    tool.Matrixmultiplikation( outh , Delta , deltaW2); //
    outh->transpose();

    //W1 : Weights1

    if(bias)
    {outh->setWidth(outh->getWidth()-1);
        weight2->setHeight(weight2->getHeight()-1);}

    tool.TanhAbleitung(outh,neth_d);

    weight2->transpose();

    tool.Matrixmultiplikation(Delta , weight2 , delta_w2);

    tool.skalarMultiplikation( delta_w2 , neth_d , delta_w2_neth_d );

    input->transpose();

    tool.Matrixmultiplikation(input,delta_w2_neth_d,deltaW1 );

    weight2->transpose();
    input->transpose();

    if(bias)
    {outh->setWidth(outh->getWidth()+1);
        weight2->setHeight(weight2->getHeight()+1);
    }



    //weight update
    weightUpdate(weight1,deltaW1,previous_weight1);
    weightUpdate(weight2,deltaW2,previous_weight2);


}

void learningStochastic::weightUpdate(Array *weight, Array *delta, Array *previous_d )
{
    double value=0;
    for(int i=0;i<weight->getHeight();i++)
    {
        for(int j=0;j<weight->getWidth(); j++)
        {
            value=weight->getValue(i,j)-(m_learning_rate*delta->getValue(i,j)-m_alpha*previous_d->getValue(i,j));

            previous_d->setValue(i,j, delta->getValue(i,j));
            weight->setValue(i,j,value);
        }

    }

}

void learningStochastic::toSigmoid(Array *A, Array *B)
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
                Sum= 1/(1+pow(exp(1),-Sum));
                B->setValue(i,k,Sum);
            }
        }
    }

}

void learningStochastic::setLearning_rate(double learning_rate)
{
    m_learning_rate = learning_rate;
}

void learningStochastic::setAlpha(double alpha)
{
    m_alpha = alpha;
}

void learningStochastic::testResult(double input)
{
    Array *Ainput;
    Array *Output;
    if(!bias)
    {


        Ainput= new Array(1,1);
        Output= new Array(1,1);
        Ainput->setValue(0,input);
    }
    else{
        Ainput= new Array(1,2);
        Output= new Array(1,1);
        Ainput->setValue(0,0,input);
        Ainput->setValue(0,1,m_Bias);
    }
    forward_pass(Ainput,Output);
    tool.output(Output);
    qDebug()<<"Sinus: "<<sin(input*2*M_PI) <<"Trained Sinus: "<<Output->getValue(0)<<" Error: "<< 100-(100/sin(input*2*M_PI)*Output->getValue(0))<<" %";
    emit ResultTested(Output->getValue(0));
}

void learningStochastic::testResult(double input1, double input2)
{
    Array *Ainput;
    Array *Output;
    if(!bias)
    {
        Ainput= new Array(1,2);
        Output= new Array(1,1);
        Ainput->setValue(0,0,input1);
        Ainput->setValue(0,1,input2);
    }
    else{
        Ainput= new Array(1,3);
        Output= new Array(1,1);
        Ainput->setValue(0,0,input1);
        Ainput->setValue(0,1,input2);
        Ainput->setValue(0,2,m_Bias);
    }

    forward_pass(Ainput,Output);

    tool.output(Output);

    emit ResultTested(Output->getValue(0));
}

void learningStochastic::testSinus()
{
    int sinusResolution=1000;
    double AverageError=0;
    Array *SinusOutput = new Array(sinusResolution,1);
    Array *SinusInput = new Array(sinusResolution,1);
    AinputSinusTest = new Array(1,2);
    AoutputSinusTest = new Array(1,1);
    AinputSinusTest->setValue(0,1,1);//Setze Bias


    for(int i=0;i<sinusResolution;i++)
    {
        double   pi = double(i+1)/double(sinusResolution) ;
        AinputSinusTest->setValue(i,0,pi);
        forward_pass(AinputSinusTest,AoutputSinusTest);
        SinusOutput->setValue(i,0,AoutputSinusTest->getValue(i));
        SinusInput->setValue(i,0,AinputSinusTest->getValue(i,0));
        AverageError+= 100-(100/sin(pi*2*M_PI)*AoutputSinusTest->getValue(0));
    }
    qDebug()<<"Average Error: "<<AverageError /1000 << " %";


}

Array *learningStochastic::getOutput() const
{
    if(!list.m_Vector.empty()){
        return list.getLastArray();
    }
    return NULL;
}

void learningStochastic::splitt_data(int percentage)
{
    int size = m_Input->getHeight();
    double test = (size/100.0)*percentage;
    double training = size-test;
    training= round(training);
    test= round(test);
    qDebug()<<training;

    trainingSet_Input = new Array(training,m_Input->getWidth());
    testingSet_Input = new Array(test,m_Input->getWidth());

    trainingSet_Output = new Array(training,m_Output->getWidth());
    testingSet_Output = new Array(test,m_Output->getWidth());
    testingSet_Output_forwardoutput= new Array(test,m_Output->getWidth());

}

void learningStochastic::splitt_step(int step)
{
    switch(step)
    {
    case 0:
        trainingSet_Input->copy(m_Input,0,47);
        testingSet_Input->copy(m_Input,47,70,47); // Erst ab 2/3

        trainingSet_Output->copy(m_Output,0,47);
        testingSet_Output->copy(m_Output,47,70,47);

        break;
    case 1:
        trainingSet_Input->copy(m_Input,0,23);
        testingSet_Input->copy(m_Input,23,47); // Erst ab 2/3
        trainingSet_Input->copy(m_Input,47,70);

        trainingSet_Output->copy(m_Output,0,23 );
        testingSet_Output->copy(m_Output,23,47);
        trainingSet_Output->copy(m_Output,47,70 );
        break;
    case 2:
        trainingSet_Input->copy(m_Input,23,70);
        testingSet_Input->copy(m_Input,0,23); // Erst ab 2/3

        trainingSet_Output->copy(m_Output,23 ,70);
        testingSet_Output->copy(m_Output,0,23);
        break;
    }



}

int learningStochastic::getIteration() const
{
    return m_iteration;
}



