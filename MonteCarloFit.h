#ifndef MONTECARLOFIT_H
#define MONTECARLOFIT_H


#include "RandomGenerator.h"
#include "Digamma.cpp"
#include <complex>

namespace{
    const int ARRAY_MAX = 10000;
    const double e = 1.602176565e-19;
    const double pi = 3.14159265359;
    const double h_bar = 1.05457172534e-34;
    const double A = -e*e/2/pi/h_bar;
    const double B = h_bar/4/e;
    const double FourOverThree = 4.0/3.0;
}

class MonteCarloFit
{
    private:
        double d_field[ARRAY_MAX];
        double d_sheetConductance[ARRAY_MAX];
        size_t d_size;

        RandGenerator d_myRand;
        int errorflag;

        double d_a;
        double d_da;

        double d_Bss;
        double d_dBss;

        double d_t;
        double d_dt;

        double d_dsOver2;
        double d_ddsOver2;

        double d_sum_diff_squares;

    public:
        MonteCarloFit();
        virtual ~MonteCarloFit();

        bool readDataFile();

        double sigma(double B, double a, double Bss, double t, double dsOver2) {
            std::complex<double> x(t, B/Bss);
            std::complex<double> y(t, -B/Bss);
            return (a*(pow(x,dsOver2) + pow(y,dsOver2))).real();
        }

        double calcSumDiffSquares(double a, double B_phi, double B_SO, double B_e);
        // will call sigma(H,a,B_phi,B_phi_i) which is not a const member function

        void updateSumDiffSquares();

        void fastMonteCarloOnce();

        void fastMonteCarloNTimes(int n);

        bool plotResult();


        // setters
        void seta(double a);
        void setda(double da);
        void setB_phi(double B_phi);
        void setdB_phi(double dB_phi);
        void setB_SO(double B_SO);
        void setdB_SO(double dB_SO);
        void setB_e(double B_e);
        void setdB_e(double dB_e);


        // getters
        double a() const {return d_a;}
        double da() const {return d_da;}
        double B_phi() const {return d_Bss;}
        double dB_phi() const {return d_dBss;}
        double B_SO() const {return d_t;}
        double dB_SO() const {return d_dt;}
        double B_e() const {return d_dsOver2;}
        double dB_e() const {return d_ddsOver2;}

        double sum_diff_squares() const {return d_sum_diff_squares;}



        // for testing -----
        void printAfterReadingFile() const;


};

#endif // MONTECARLOFIT_H
