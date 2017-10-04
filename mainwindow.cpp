#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QPainter>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupPlot();
    realtimeDataSlot();
    ini_Output_plot();
    ui->label_datasplittoutput->setText(QString::number(0));
    /*
    connect(learn,SIGNAL(plot(int i, int b)),
            this,SLOT(plot_slot(int,int)));
            */
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen PenBlack(Qt::black);
    QPen PenRed(Qt::red);

    PenBlack.setWidth(1);
    PenRed.setWidth(1);
    painter.setPen(PenBlack);
    painter.drawLine(20,20,100,100);
    painter.drawEllipse(20,20,20,20);

}


void MainWindow::drawLayer(int size, int layer)
{

}

void MainWindow::setupPlot()
{
    ui->plot->addGraph(); // blue line

    ui->plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->plot->addGraph(); // red line
    ui->plot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
       ui->plot->addGraph(); // red line
     ui->plot->graph(2)->setPen(QPen(QColor(0, 0, 0)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->plot->xAxis->setTicker(timeTicker);
    ui->plot->axisRect()->setupFullAxesBox();
    ui->plot->yAxis->setRange(-1.2, 1.2);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

void MainWindow::PlotError(int iteration, double Error)
{



    m_iteration=iteration;
    m_error= Error;
    realtimeDataSlot();

}

void MainWindow::ResultTest(double Y)
{
  ui->label_test_output->setNum(Y);
}



void MainWindow::plot_slot(int iteration, double error)
{

    ui->iterator->setText(QString::number(iteration));
    static double min_error=error;
    static int previous_it=0;
    static int rescale_it=0;

        ui->Error_label->setText(QString::number(min_error));
        min_error = error;


    if((iteration%2==0) && (m_plot == true))
    {
        drawOutput();
    }
    if((previous_it+99)<iteration && (m_plot == true)){

        previous_it=iteration;
        ui->plot->graph(0)->addData(iteration-100,error );
        if((rescale_it+1000)<iteration)
        {
            ui->plot->graph(0)->rescaleValueAxis();
            ui->plot->graph(0)->rescaleKeyAxis();
            ui->plot->replot();
            rescale_it=iteration;
        }


    }
}

void MainWindow::realtimeDataSlot()
{
    if(learn_stoch==NULL){
        return;
    }
    //   m_iteration=learn->getIteration();
    //    m_error=learn->getError();
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.00000002) // at most add point every 2 ms
    {
        // add data to lines:

        ui->plot->graph(0)->addData(m_iteration, m_error);
        // rescale value (vertical) axis to fit the current data:
        ui->plot->graph(0)->rescaleValueAxis();
        ui->plot->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;

        // make key axis range scroll with the data (at a constant range size of 8):
        ui->plot->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->plot->replot();

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key-lastFpsKey > 2) // average fps over 2 seconds
        {
            ui->statusBar->showMessage(
                        QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(ui->plot->graph(0)->data()->size()+ui->plot->graph(1)->data()->size())
                        , 0);
            lastFpsKey = key;
            frameCount = 0;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{

    ui->plot->replot();
    if (m_PlotVisible==false)
    {
        ui->plot->setVisible(true);
        m_PlotVisible=true;
    }
    else{
        ui->plot->setVisible(false);
        m_PlotVisible=false;
    }
}

void MainWindow::on_pushButton_NOT_clicked()
{

    Array *Input     =new Array(2,1);
    Array *OutputSoll= new Array(2,1);
    Input->setValue(0,-1);
    Input->setValue(1,1);


    OutputSoll->setValue(0,1);
    OutputSoll->setValue(1,-1);
    m_Input= Input;
    m_OutputSoll=  OutputSoll;
    drawOutput();
    ui->pushButton_Start->setEnabled(true);

}

void MainWindow::on_pushButton_Start_clicked()
{

  //  learn_stoch = new learningStochastic(m_Input,m_OutputSoll,m_HiddenLayer,m_learnrate,m_alpha,m_Bias);

if (!Training)
{

    learn_stoch = new learningStochastic(m_Input,m_OutputSoll,m_HiddenLayer,m_learnrate,m_alpha,m_Bias, m_Batchsize);

    //learn = new Learning(m_Input,m_OutputSoll,m_HiddenLayer,m_learnrate,m_alpha,m_Bias);
    connect(learn_stoch, learningStochastic::plot,
    this,plot_slot);
    learn_stoch->start();
    Training = true;
    ui->pushButton_Start->setText("Stop");
}
else{
    learn_stoch->terminate();
    Training = false;
     ui->pushButton_Start->setText("Train");
}

}


void MainWindow::drawNeuralNet()
{

}

void MainWindow::on_spinBox_HiddenLayer_valueChanged(int arg1)
{
    m_HiddenLayer = arg1;
}

void MainWindow::ini_Output_plot()
{
    ui->ouputPlot->addGraph();
    ui->ouputPlot->addGraph();
    ui->ouputPlot->addGraph();
    ui->ouputPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->ouputPlot->graph(1)->setPen(QPen(QColor(20,200,20)));
    ui->ouputPlot->graph(2)->setPen(QPen(QColor(0,0,0)));
    ui->ouputPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->ouputPlot->yAxis->setRange(-1, 1);
    ui->ouputPlot->xAxis->setRange(0,6.25);
}

void MainWindow::drawOutput()
{
    Array *drawOutput;
    if(Training== true)
    {
        drawOutput = learn_stoch->getOutput();
        ui->ouputPlot->addGraph();
        ui->ouputPlot->graph(1)->setPen(QPen(QColor(20,200,20)));
    }
    else
    {
        drawOutput = NULL;
    }
    int ii=m_OutputSoll->getHeight();
    int jj=m_OutputSoll->getWidth();

    for(int i=0;i<ii;i++){

        for(int j=0;j<jj;j++)
        {

            if(drawOutput!=NULL ){
                ui->ouputPlot->graph(1)->addData(m_Input->getValue(i,j)*6.2,drawOutput->getValue(i,j));

            }
            else{
                   ui->ouputPlot->graph(0)->addData(m_Input->getValue(i,j)*6.2,m_OutputSoll->getValue(i,j));
            }
        }
    }
    ui->ouputPlot->replot();
    ui->ouputPlot->removeGraph(1);
}

void MainWindow::drawOutput(Array *Input, Array *Output)
{
    //  ui->ouputPlot->addGraph();
  //    ui->ouputPlot->graph(1)->setPen(QPen(QColor(0,0,0)));
ui->ouputPlot->replot();

  int ii=Output->getHeight();
  int jj=Output->getWidth();

  for(int i=0;i<ii;i++){

                 //ui->ouputPlot->graph(0)->setPen(QPen(QColor(20,200,20)));
          qDebug()<<ui->ouputPlot->graphCount();
                 ui->ouputPlot->graph(1)->addData(Input->getValue(i,1)*6.2,Output->getValue(i,1));


  }

  ui->ouputPlot->replot();
   // ui->ouputPlot->repaint();
//   ui->ouputPlot->removeGraph(1);
}

void MainWindow::drawOutputSinus(Array* Input, Array* Output)
{
//drawOutput(Input, Output);

}

void MainWindow::sinusPlot()
{
}

void MainWindow::on_pushButton_DrawOutput_clicked()
{
    drawOutput();
}

void MainWindow::on_pushButton_OR_clicked()
{
    delete m_Input,m_OutputSoll;

    Array *Input     =new Array(4,2);
    Array *OutputSoll= new Array(4,1);

    Input->setValue(0,0,0);
    Input->setValue(0,1,0);
    Input->setValue(1,0,0);
    Input->setValue(1,1,1);

    Input->setValue(2,0,1);
    Input->setValue(2,1,0);
    Input->setValue(3,0,1);
    Input->setValue(3,1,1);


    OutputSoll->setValue(0,0);
    OutputSoll->setValue(1,1);
    OutputSoll->setValue(2,1);
    OutputSoll->setValue(3,1);
/*
    //Internet Example
    Array *Input     =new Array(3,2);
    Array *OutputSoll= new Array(3,1);

    Input->setValue(0,0,0.3);
    Input->setValue(0,1,0.5);
    Input->setValue(1,0,0.5);
    Input->setValue(1,1,0.1);
    Input->setValue(2,0,1);
    Input->setValue(2,1,0.2);



    OutputSoll->setValue(0,0.75);
    OutputSoll->setValue(1,0.82);
    OutputSoll->setValue(2,0.93);
*/
    m_Input= Input;
    m_OutputSoll =  OutputSoll;
    drawOutput();

    ui->pushButton_Start->setEnabled(true);

}

void MainWindow::on_pushButton_XOR_clicked()
{

    delete m_Input,m_OutputSoll;
    Array *Input     =new Array(4,2);
    Array *OutputSoll= new Array(4,1);

    Input->setValue(0,0,0);
    Input->setValue(0,1,0);
    Input->setValue(1,0,0);
    Input->setValue(1,1,1);

    Input->setValue(2,0,1);
    Input->setValue(2,1,0);
    Input->setValue(3,0,1);
    Input->setValue(3,1,1);


    OutputSoll->setValue(0,0);
    OutputSoll->setValue(1,1);
    OutputSoll->setValue(2,1);
    OutputSoll->setValue(3,0);

    m_Input= Input;
    m_OutputSoll =  OutputSoll;
    drawOutput();
    ui->pushButton_Start->setEnabled(true);
}

void MainWindow::on_pushButton_Sinus_clicked()
{
    csv.loadCSV();


    delete m_Input, m_OutputSoll;

    Array *OutputSoll = csv.getList().m_Vector.at(1);
    Array *Input     = csv.getList().m_Vector.at(0);

    ui->pushButton_Start->setEnabled(true);
    m_Input= Input;

    m_OutputSoll =  OutputSoll;
  drawOutput();

}
void MainWindow::on_pushButton_AND_clicked()
{

    Array *Input     =new Array(4,2);
    Array *OutputSoll= new Array(4,1);

    Input->setValue(0,0,0);
    Input->setValue(0,1,0);
    Input->setValue(1,0,0);
    Input->setValue(1,1,1);

    Input->setValue(2,0,1);
    Input->setValue(2,1,0);
    Input->setValue(3,0,1);
    Input->setValue(3,1,1);


    OutputSoll->setValue(0,0);
    OutputSoll->setValue(1,0);
    OutputSoll->setValue(2,0);
    OutputSoll->setValue(3,1);

    m_Input= Input;
    m_OutputSoll =  OutputSoll;
    drawOutput();
    ui->pushButton_Start->setEnabled(true);

}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    if(!Training)
    {
            m_learnrate = arg1;
    }
    else
    {
        m_learnrate = arg1;
        learn_stoch->setLearning_rate(m_learnrate);
    }


}

void MainWindow::on_checkBox_clicked(bool checked)
{
    m_plot= checked;
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    m_Bias = arg1;
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{    if(!Training)
    {
            m_alpha = arg1;
    }
    else
    {
        m_alpha = arg1;
        learn_stoch->setAlpha(m_alpha);
    }

}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{


}

void MainWindow::on_pushButton_Test_clicked()
{

   QString input = ui->lineEdit_test->text();
   if(input!="")
   {
       connect(learn_stoch, learningStochastic::ResultTested,
               this,
               ResultTest);

         double x1 = input.toDouble();
       if(ui->lineEdit_test_1->text()!="")
       {
           double x2 = ui->lineEdit_test_1->text().toDouble();
              learn_stoch->testResult(x1,x2);
       }
       else
       {
           learn_stoch->testResult(x1);
       }


   }





}

void MainWindow::on_pushButton_TestSinus_clicked()
{
/*
    connect(learn_stoch, learningStochastic::SinusTested,
            this,
            drawOutputSinus);
*/


    learn_stoch->testSinus();
  //  drawOutput(Input, Output);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ui->label_datasplittoutput->setText(QString::number(value));
    m_Batchsize= value;
}
