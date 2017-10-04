#ifndef TOOLS_H
#define TOOLS_H
#include <array.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <ctime>

class Tools
{
public:
    Tools();
    Array*SumWeightMatrix(Array *A);
    Array *Copy(Array *A);
    Array* Matrixmultiplikation(Array* A, Array* B);
    void Matrixmultiplikation( Array *A, Array *B, Array *C);
    void output(Array* A);
    Array* SigmoidAbleitung(Array* A);
    Array* vektorAddition(Array* A, Array* B);
     Array* vektorSubtraktion(Array* A, Array* B);
    Array* skalarMultiplikation(Array* A,Array* B);
    Array* skalarMultiplikation_lernrate(Array* A, Array* B, double r, int iterationen);
    void Matrixmultiplikation_Bias(Array* A, Array* B, Array* C, double Bias);
    Array* Matrixmultiplikation_Bias(Array* A, Array* B, double Bias);
    Array* square_error(Array* is, Array* soll);
    double square_error_overall(Array* is, Array* soll);
    void shuffle(Array *A, Array *B);
    double Random();
    void Matrixmultiplication_Stocastic(Array* A, Array*B, Array *C, int sample);
    void WeightUpdateMomentum(Array* weight, Array *previous_weight, Array* delta, Array* previous_Delta, double learnrate, double alpha , bool bias, double error, double previous_error);
    void WeightUpdateMomentum(Array* weight, Array *previous_weight, Array* delta, Array* previous_Delta, Array *learnrate, double alpha , bool bias, double error, double previous_error);
    Array *TanhAbleitung(Array *A);
    Array *TanhAbleitung(Array *A, Array *C);
    Array *vektorSubtraktion(Array *A, Array *B, Array *C);
    Array *vektorAddition(Array *A, Array *B, Array *C);
    Array *skalarMultiplikation(Array *A, Array *B, Array *C);
    Array *SigmoidAbleitung(Array *A, Array *C);
    Array *Copy(Array *A, Array *B);
};

#endif // TOOLS_H
