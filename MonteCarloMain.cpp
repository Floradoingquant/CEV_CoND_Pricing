//MonteCarloMain.cpp
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "Normals.h"
#include "Sampler.h"
#include "StochProcess.h"
#include "CoND.h"
using namespace std;

int main()
{
//srand(time(0));
 srand(1.0);  //Could also use such a seed. This is useful if you would like to reproduce your results;

 double T=1.0;
 double H=10.0;
 double C=15.0;
 double S0=10.0;
 double sigma=0.2;
 double r=0.01;
 double gamma=0.75;
 int numberofsteps=20;
 int n=100000;
 double mystdev=0.00;

 //to calculate the MC price
 CoNDCall CDC(H,C);
 double price1;
 price1=CDC.computepriceMC(S0, sigma, r, T, n, gamma, numberofsteps);
 cout << "The Monte Carlo Cash-or-nothing Digital Option price approximation under CEV is " << price1 << "\n";

 //to calculate the MC price in another sample for its standard deviation
 double price2;
 price2=CDC.computepriceMC2(mystdev, S0, sigma, r, T, n, gamma, numberofsteps);
 cout <<"MC price for another approximation is " <<price2 <<"and the standard deviation for my MCestimator is"<<mystdev/sqrt(n)<<"\n";

 //the following interval estimation is from week 4 worksheet
 //to calculate the confidence interval of 95% for MC estimator
 double myepsilon=0.05;
 double leftside, rightside;
 double quantile=InverseCumulativeNormal(1.0-myepsilon*0.5);
 leftside= price2-quantile*mystdev/sqrt(n);
 rightside=price2+quantile*mystdev/sqrt(n);
 cout << "Recall that Phi^{-1}(" <<1.0-myepsilon*0.5 <<") = " << quantile << "\n";
 cout << "MC confidence interval for confidence level ="<<1.0-myepsilon <<"  and n=" << n << " is (" << leftside << " , " << rightside << ") \n";

 //to calculate the confidence interval of 99% for MCestimator
 double myepsilon1=0.01;
 double leftside1, rightside1;
 double quantile1=InverseCumulativeNormal(1.0-myepsilon1*0.5);
 leftside1= price2-quantile1*mystdev/sqrt(n);
 rightside1=price2+quantile1*mystdev/sqrt(n);
 cout << "Recall that Phi^{-1}(" <<1.0-myepsilon1*0.5 <<") = " << quantile1 << "\n";
 cout << "MC confidence interval for confidence level ="<<1.0-myepsilon1 <<"  and n=" << n << " is (" << leftside1 << " , " << rightside1 << ") \n";

 //to calculate a control variate estimator
 double price3;
 price3=CDC.computepriceCV(S0, sigma, r, T, n, gamma, numberofsteps);
 cout <<"Control Variate estimate based on X as discounted stock price is " <<price3 <<"\n";

 double price4;
 price4=CDC.computepriceCV2(S0, sigma, r, T, n, gamma, numberofsteps);
 cout <<"Control Variate estimate based on X as standard normal is " <<price4 <<"\n";

 return 0;
}


 //cout <<"Checking analytical put-call-parity: put-call=" <<price3-price1 <<" and Ke^{-rT}-S0= "<<K*exp(-r*T)-S0 <<"\n";
 //cout <<"Checking MC put-call-parity: put-call=" <<price4-price2 <<" and Ke^{-rT}-S0= "<<K*exp(-r*T)-S0 <<"\n";


