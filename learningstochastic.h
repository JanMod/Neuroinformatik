#ifndef LEARNING_H
#define LEARNING_H
#include "array.h"
#include "vector_list.h"
#include "tools.h"
#include "qdebug.h"
#include <QtCore>
#include <thread>
#include <QObject>


class learningStochastic : public QThread
{
    Q_OBJECT
public:

    void run(); // Thread

    //Konstruktor
    // In : Input Datensatz
    //Out : Output Datensatz
    //Batchsize Unterteilung der Datensätze in selbst definierte Gruppen
    explicit learningStochastic(Array *In, Array *Out, int Number_of_Hiddenneuron, double learning_rate, double alpha, double Bias, int Batchsize);



    int getIteration() const;
    double getError() const;

    Array *getOutput() const;

    void setLearning_rate(double learning_rate);
    void setAlpha(double alpha);

    void testResult(double input);
    void testResult(double input1, double input2);


    void testSinus();


signals:
    void plot(int iterator, double error);
    void SinusTested(Array* input, Array* output);
    void ResultTested(double Result);
private:


    bool bias=false;
    double m_alpha=0;
    int  m_iteration =0;
    int miniBatch_size=1;

    int m_final_layer=0;
    int m_number_of_Hiddenneuron=0;
    double m_learning_rate=1;
    double m_Bias=0;
    double m_error=0;

    //Aufteilen der Datensätze in Training und Test
    void splitt_data(int percentage);//Cross-Validation: Nicht genutzt
    void splitt_step(int step);//Cross-Validation: Nicht genutzt








    Array *m_Input;//Input Datensatz
    Array *m_Output;//Output Datensatz

    std::list<Array * >m_List;
    Tools tool;
    Vector_list list;

    Vector_list momentum_list_w1;
    Vector_list momentum_list_w2;

    Array *trainingSet_Input;
    Array *testingSet_Input;

    Array *trainingSet_Output;
    Array *testingSet_Output;

    Array *testingSet_Output_forwardoutput;

    //Backpropgation Variablen
    Array *Delta;
    Array *deltaW2;
    Array *deltaW1;
    Array *neth_d;

    Array *y_y_is;
    Array *TanhAbleitung;

    Array *delta_w2       ;
    Array *delta_w2_neth_d;

    //NN Test Outputs
    Array*   AinputSinusTest;
    Array*   AoutputSinusTest;




    void build();//Errechnet aus den Parametern im Konstruktor die entsprechenden Eigenschaften (z.B. Gewichte, Momentum)
    void forward_pass(Array *input, Array *output); //Input zum Testen. Output das Ergebnis
    void toTanH(Array *A, Array *B);// Alle Werte in Array A -> tanh(A.value)
    void toSigmoid(Array *A, Array *B); // Alle Werte in Array A -> sigmoid(A.value)

    //In der Backpropagation werden die neuen Gewichte ausgrechnet
    void backpropagation(Array *input, Array *output_forward, Array *output_soll, Array *previous_weight1, Array *previous_weigh2);
    void weightUpdate(Array *weight, Array *delta, Array *previous_d); // Gewichtsupdate inkl. Momentum
};

#endif // LEARNING_H
