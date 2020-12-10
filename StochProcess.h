//StochProcess.h
#ifndef STOCHPROCESS_H
#define STOCHPROCESS_H
//code from worksheet 5
class StochProcess
{
      public:
             double get_terminalvalue(double T, int numberofsteps, double X0);
             void get_samplepath(double T, int numberofsteps, double X0, double *p);
      private:
              virtual double step(double currentX, double h)=0;
};


//to use the CEV model to generate sample paths of stock price
class CEVModel: public StochProcess
{
      public:
             CEVModel(double myr=0.01, double mysigma=0.2, double mygamma=0.75): r(myr), sigma(mysigma), gamma(mygamma){};

      private:
               virtual double step(double currentX, double h);
               double r, sigma, gamma;


};

#endif //STOCHPROCESS_H
