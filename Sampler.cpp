//Sampler.cpp
#include "Sampler.h"
#include<iostream>
#include<cstdlib>
#include<cmath>
//from worksheet 3
//Uniform
UniformSampler::UniformSampler(double lower, double upper)
{
                       mylower=lower;
                       myupper=upper;
}

double UniformSampler::getnumber()
{
       int myrand=rand();
       while((myrand==0)||(myrand==RAND_MAX)){myrand = rand(); } //We want a number in (0, RAND_MAX).

       double myuni = myrand/static_cast<double>(RAND_MAX); //Create a number in (0,1).
       return mylower+myuni*(myupper-mylower);
}

//Exponential
ExponentialSampler::ExponentialSampler(double lambda)
{
 mylambda=lambda;
}

double ExponentialSampler::getnumber()
{
       UniformSampler myu; //since U(0, 1) is default option
       double tmp=-log(myu.getnumber());
       return tmp/mylambda;
}

//Normal
NormalSampler::NormalSampler(double mu, double sigsqrd)
{
   mymu=mu;
   mysigmasquared=sigsqrd;
}

double NormalSampler::getnumber()
{
       ExponentialSampler mye(0.5);
       UniformSampler myu(0, 2*M_PI);
       double standardnorm=sqrt(mye.getnumber())*cos(myu.getnumber());
       return mymu + sqrt(mysigmasquared)*standardnorm;
}

double ExampleF::getnumber()
{
    UniformSampler myu;
    double result=0.0;
    double testu=myu.getnumber();
    if (testu < 0.5){
        result = log(2.0*testu);
    }
    //std::cout<<result<<"\n";
    return result;
}
