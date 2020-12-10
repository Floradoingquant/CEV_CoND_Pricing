//CoND.h
#ifndef COND_H
#define COND_H
//from worksheet 3 code
class CoND
{
public:
    virtual double computepayoff(double spot) = 0;
    double computepriceMC(double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps);
    double computepriceMC2(double &mystdev,  double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps);
    double computepriceCV(double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps);
    double computepriceCV2(double S0, double sigma, double r, double T, int n, double gamma, int numberofsteps);
};

class CoNDCall: public CoND{
private:
    double strike;
    double cash;
public:
    CoNDCall(double H, double C);
    virtual double computepayoff(double spot);
};

#endif
