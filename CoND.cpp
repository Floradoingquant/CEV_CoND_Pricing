//CoND.cpp
#include "CoND.h"
#include "Sampler.h"
#include "StochProcess.h"
#include "Normals.h"
#include<ctime>
#include<cmath>
#include<iostream>

//from week 3 worksheet
double CoND::computepriceMC(double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps)
{
    CEVModel price(r, sigma, gamma);
    double mysum=0.0;
    double MCprice=0.0;
    double spot, tmppayoff;

	for (int i=0; i < n; i++)
	{
		spot=price.get_terminalvalue(T,numberofsteps,S0);
		tmppayoff = computepayoff(spot);
		mysum+=tmppayoff;
     }
    MCprice=mysum*exp(-r*T)/n; //Don't forget discounting!
	return MCprice;
}
//from week 3 worksheet
double CoND::computepriceMC2(double &mystdev, double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps)
{
    CEVModel price(r,sigma,gamma);
    double *myvector;
    myvector =  new double[n];

    double mysum=0.0;
    double MCprice2=0.0;
    double spot, tmppayoff;

	for (int i=0; i < n; i++)
    {
		spot= price.get_terminalvalue(T,numberofsteps,S0);
		tmppayoff = computepayoff(spot);
        myvector[i] = tmppayoff*exp(-r*T);
		mysum+=tmppayoff;
     }

    MCprice2=mysum*exp(-r*T)/n;

    mystdev=0.0;
    double tmp=0.0;
    for (int i=0; i < n; i++)
	{
        tmp+=(myvector[i] - MCprice2)*(myvector[i] - MCprice2);
    }
    mystdev=sqrt(tmp/(n - 1.0));
    delete [] myvector;

	return MCprice2;
}

//from week 4 worksheet
double CoND::computepriceCV(double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps )
{
    CEVModel price(r, sigma, gamma);
    double mysumX, mysumY;
    double spot, discountedstockprice, tmppayoff;
    double MCprice=0.0;
    double cov, varX, varY, bhat;
    double *myYvector;
    myYvector =  new double[n];
    double *myXvector;
    myXvector =  new double[n];

    mysumX=0.0;
    mysumY=0.0;
	for (int i=0; i < n; i++)
	{
		spot=price.get_terminalvalue(T,numberofsteps,S0);
        discountedstockprice= spot*exp(-r*T);
		tmppayoff = computepayoff(spot);
		myXvector[i] = discountedstockprice;    //X is the discounted stock price and we know that under Q it has known expectation
		myYvector[i] = tmppayoff*exp(-r*T);
		mysumX+=myXvector[i];
		mysumY+=myYvector[i];
     }


    bhat=0.0;
    cov=0.0;
    varX=0.0;
    varY=0.0;
    double tmp=0.0;
    for (int i=0; i < n; i++)
	{
        cov+=(myXvector[i] - mysumX/n)*(myYvector[i] - mysumY/n);
        varX+=(myXvector[i] - mysumX/n)*(myXvector[i] - mysumX/n);
        varY+=(myYvector[i] - mysumY/n)*(myYvector[i] - mysumY/n);

    }

    //Note that cov & var ar not the sample covariance/variance since one still needs to divide by n (or n-1).
    //In the computation of bhat this cancels.
    //Note, that this computation does introduce bias in the estimator since the same X, Y are used for computing bhat.
    //This could be avoided by using a new sample for the estimation, see Glasserman.

    bhat=cov/varX;
    std::cout << "The Control Variate Estimator in the first case with Xi to be discounted stock price has bhat =  " << bhat << " and corr(X, Y)^2 = " << (cov*cov)/(varX*varY) << "\n";
    for (int i=0; i < n; i++)
	{
        MCprice+=myYvector[i]- bhat*(myXvector[i]-S0); //the discounted stock price has mean S0
     }

    delete [] myXvector;
    delete [] myYvector;

    MCprice=MCprice/n;
	return MCprice;


}
//from week 4 worksheet
double CoND::computepriceCV2(double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps )
{
    CEVModel price(r, sigma, gamma);
    NormalSampler mystdnormal(0.0, 1.0);
    double mysumX, mysumY;
    double spot, mynormal, tmppayoff;
    double MCprice2=0.0;
    double cov, varX, varY, bhat;
    double *myYvector;
    myYvector =  new double[n];
    double *myXvector;
    myXvector =  new double[n];

    mysumX=0.0;
    mysumY=0.0;
	for (int i=0; i < n; i++)
	{
		spot=price.get_terminalvalue(T,numberofsteps,S0);
        mynormal=mystdnormal.getnumber();
		tmppayoff = computepayoff(spot);
		myXvector[i] = mynormal;    //X is the standard normal as it is a random number in the MCprice function, and it has mean 0
		myYvector[i] = tmppayoff*exp(-r*T);
		mysumX+=myXvector[i];
		mysumY+=myYvector[i];
     }


    bhat=0.0;
    cov=0.0;
    varX=0.0;
    varY=0.0;
    double tmp=0.0;
    for (int i=0; i < n; i++)
	{
        cov+=(myXvector[i] - mysumX/n)*(myYvector[i] - mysumY/n);
        varX+=(myXvector[i] - mysumX/n)*(myXvector[i] - mysumX/n);
        varY+=(myYvector[i] - mysumY/n)*(myYvector[i] - mysumY/n);

    }

    //Note that cov & var ar not the sample covariance/variance since one still needs to divide by n (or n-1).
    //In the computation of bhat this cancels.
    //Note, that this computation does introduce bias in the estimator since the same X, Y are used for computing bhat.
    //This could be avoided by using a new sample for the estimation, see Glasserman.

    bhat=cov/varX;
    std::cout << "The Control Variate Estimator in the second case with Xi to be standard normal distribution has bhat =  " << bhat << " and corr(X, Y)^2 = " << (cov*cov)/(varX*varY) << "\n";
    for (int i=0; i < n; i++)
	{
        MCprice2+=myYvector[i]- bhat*(myXvector[i]-0); //the standard normal distribution has mean 0
     }

    delete [] myXvector;
    delete [] myYvector;

    MCprice2=MCprice2/n;
	return MCprice2;


}

CoNDCall::CoNDCall(double H, double C)
{
    strike=H;
    cash=C;
}

double CoNDCall::computepayoff(double spot)
{
    double res=0.0;
    if (spot >=strike){res=cash;}
    return res;
}

