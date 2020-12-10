//StochProcess.cpp
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Sampler.h"
#include "StochProcess.h"
#include "CoND.h"
#include "Normals.h"
//the following functions get_terminalvalue,
//get_samplepath and step have their structures all coming from the MA323 worksheet 5
double StochProcess::get_terminalvalue(double T, int numberofsteps, double X0)
{
       //std::cout << "X0="<< S0 << "\n";
       double h=T/numberofsteps;
       double currentX=X0;
       for(int i=0; i<numberofsteps;i++){
            currentX=step(currentX, h);
       }
       return currentX;
}


void StochProcess::get_samplepath(double T, int numberofsteps, double X0, double *p)
{
      //std::cout << "X0="<< X0 << "\n";
      double h=T/numberofsteps;
      double tmpresult;
      *p=X0;
      for(int i=0; i<numberofsteps;i++){
            tmpresult=step(*p, h);
            p=p+1;
            *p=tmpresult;
      }
      return;
}


double CEVModel::step(double currentX, double h)
{
     double nextvalue;
     NormalSampler ns(0.0, 1.0);
     double normalrand=ns.getnumber();
     nextvalue=currentX*exp(h*(r-0.5*sigma*sigma*pow(currentX,2*gamma-2)))*exp(sigma*pow(currentX,gamma-1)*sqrt(h)*normalrand);
     return nextvalue;
}



