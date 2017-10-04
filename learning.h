#ifndef LEARNING_H
#define LEARNING_H
#include "array.h"
#include "vector_list.h"
#include "tools.h"
#include "qdebug.h"
#include <QtCore>
#include <thread>
#include <QObject>

class Learning : public QThread
{
    Q_OBJECT
public:

    void run();
    explicit Learning(QObject *parent = 0);

    explicit Learning(Array *In, Array *Out);
    explicit Learning(Array *In, Array *Out, int Number_of_Hiddenneuron, double learning_rate, double alpha, double Bias);


    Vector_list getList() const;
    int getIteration() const;
    double getError() const;
    Array *getOutput() const;

    void GradientChecking(Array *Weight1, Array *Weigth2);
    void setLearning_rate(double learning_rate);

    void setAlpha(double alpha);

signals:
    void plot(int iterator, double error);
private:


    bool bias=false;
    double m_alpha=0.05;
    void delete_from_list();
    void forward_pass();
    void weightUpdate(Array* weight,Array* previous_weight, Array* delta, Array* previous, int position);
    void square_error();
    void back_propagation();
    int  m_iteration =0;
    void draw_to_mainwindow();
    void build();
    void toSigmoid(Array *A, Array *B);
    Array *m_Input;
    Array *m_Output;
    int m_hidden_layer=1;
    Vector_list previous_delta;
    Vector_list previous_weight;
    double error[2];
    int m_final_layer=0;
    int m_number_of_Hiddenneuron=0;
    double m_learning_rate=1;
    double m_Bias=0;
    double m_error=0;
    std::list<Array * >m_List;
    Tools tool;
    Vector_list list;



    //Backpropgation
    Array *Delta;
    Array *deltaW2;
    Array *deltaW1;
    Array *neth_d;









 //   MainWindow window;

    void toTanH(Array *A, Array *B);
};

#endif // LEARNING_H
