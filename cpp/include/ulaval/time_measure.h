/**
* \file time_measure.h
* \brief Compteur temporel permettant de mesurer le temps d'éxécution d'un algorithme.
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/4/2015
*/

#ifndef ULAVAL_TIME_MEASURE_H__
#define ULAVAL_TIME_MEASURE_H__

#if __cplusplus < 201103L
#include "time_measure_cxx03.h"
#else
#include "time_measure_cxx11.h"
#endif

#endif // ULAVAL_TIME_MEASURE_H__