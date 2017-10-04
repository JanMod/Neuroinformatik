#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QtCore>
#include "array.h"
#include "learningStochastic.h"
//#include "learning.h"
#include "csv_file.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread PlotThread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void drawLayer(int size, int layer);
    void PlotError(int iteration, double Error);



private slots:
    void ResultTest(double Y);
    void drawOutputSinus(Array *Input, Array *Output);
    void plot_slot(int iteration, double error);
    void realtimeDataSlot();
    void on_pushButton_clicked();

    void on_pushButton_NOT_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_AND_clicked();

    void on_spinBox_HiddenLayer_valueChanged(int arg1);

    void on_pushButton_DrawOutput_clicked();

    void on_pushButton_OR_clicked();

    void on_pushButton_XOR_clicked();

    void on_pushButton_Sinus_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_checkBox_clicked(bool checked);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_pushButton_Test_clicked();

    void on_pushButton_TestSinus_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

private:
    double m_Bias=0;
    double m_learnrate = 0.01;
    bool m_plot =true;
    void ini_Output_plot();
    void drawOutput();
    void drawOutput(Array* Input, Array* Output);
    int m_HiddenLayer = 1;
    bool Training =false;
    void sinusPlot();
    void drawNeuralNet();
//    Learning Learn;
//    Learning *learn;
    learningStochastic *learn_stoch;
 //   Learning *learn;
    Ui::MainWindow *ui;
    void setupPlot();
    double m_alpha=0;
    int m_iteration=20;
    double m_error=3000;
    int m_Batchsize= 1;
    int previous_iteration;
    QTimer dataTimer;
    bool m_PlotVisible=true;
    CSV_File csv;
    Array *m_Input;
   Array *m_OutputSoll;

};

#endif // MAINWINDOW_H
