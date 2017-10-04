#include "csv_file.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
CSV_File::CSV_File()
{

}

CSV_File::loadCSV()
{
    list= new Vector_list();
    std::string row,column;
    QString test=" asd";
    int i=0;
    double d=0;
    bool ok=true;
    std::ifstream file("sinus.csv");
    Array *Input;
    Array *Output;

    if(file == NULL)
    {
        qDebug()<<"File not found";
    }

    while(std::getline(file,row))
    {
        std::stringstream  lineStream(row);
        std::string        cell;
        while(std::getline(lineStream,cell,','))
        {
            QString  temp= QString::fromStdString(cell);
            QStringList myStringList=  temp.split(';');


            double input,output =0;
            QString StringFirst= myStringList.first();
            QString StringLast= myStringList.last();
            input = QString(StringFirst).toDouble(&ok);
            output = QString(StringLast).toDouble(&ok);



            if(i>0)
            {

                Input->setValue(i-1,input);
                Output->setValue(i-1,output);
                qDebug()<<"I:"<< Input->getValue(i-1)<<" O:"<<  Output->getValue(i-1);


            }
            else
            {
                Input= new Array((int)input,1);
                Output = new Array ((int)output,1);
            }
            i++;
        }
    }

list->add(Input);
list->add(Output);
}


Vector_list CSV_File::getList() const
{
    return *list;
}


