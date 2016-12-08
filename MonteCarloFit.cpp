#include "MonteCarloFit.h"
#include <fstream>
#include <string>
#include "StringParser.h"
#include <iostream>

MonteCarloFit::MonteCarloFit(): d_size(0)
{
    d_myRand.SetSeed(3435);
    d_a = 1;
    d_da = 0.1;
    d_Bss = 1;
    d_dBss = 0.1;
    d_t = 1;
    d_dt = 0.1;
    d_dsOver2 = 1;
    d_ddsOver2 = 0.1;

    d_sum_diff_squares = 1E1000;
}

MonteCarloFit::~MonteCarloFit()
{
    //dtor
}

bool MonteCarloFit::readDataFile(){
    std::string fileName;
    std::cout<<"Read data from file: ";
    while(fileName.size()==0){std::getline(std::cin, fileName);}
    std::fstream myFile;
    myFile.open(fileName.c_str(), std::ios::in|std::ios::out);
    StringParser spobj;

    while(!myFile.eof()){
        std::string line;
        std::getline(myFile,line);
        if(line.size() == 0){
            continue;
        }
        spobj.setString(line);
        std::vector<std::string> result;
        result = spobj.getResult();
        d_field[d_size]=std::stod(result[0]);
        d_sheetConductance[d_size]=std::stod(result[1]);
        ++d_size;
    }

    calcSumDiffSquares(d_a, d_Bss, d_t, d_dsOver2);
}

double MonteCarloFit::calcSumDiffSquares(double a, double B_phi, double B_SO, double B_e) {
    double sum = 0;
    for(size_t i=0; i!=d_size; ++i){
        double diff = sigma(d_field[i], a, B_phi, B_SO, B_e) - d_sheetConductance[i];
        sum += diff * diff;
    }
    return sum;
}

void MonteCarloFit::updateSumDiffSquares(){
    d_sum_diff_squares = calcSumDiffSquares(d_a, d_Bss, d_t, d_dsOver2);
}

void MonteCarloFit::printAfterReadingFile() const{
    std::cout<<"d_size="<<d_size<<"\n";
    for(size_t i=0; i!=d_size; ++i){
        std::cout<<d_field[i]<<"\t"<<d_sheetConductance[i]<<"\n";
    }
}

void MonteCarloFit::fastMonteCarloOnce(){
    double newa = d_a + (d_myRand.Rand() * 2 -1) * d_da;
    double newSumDiffSquares = calcSumDiffSquares(newa, d_Bss, d_t, d_dsOver2);
    if(newSumDiffSquares < d_sum_diff_squares){
        //accept newa
        d_a = newa;
        d_sum_diff_squares = newSumDiffSquares;
    }

    double newB_phi = d_Bss + (d_myRand.Rand() * 2 - 1) * d_dBss;
    newSumDiffSquares = calcSumDiffSquares(d_a, newB_phi, d_t, d_dsOver2);
    if(newSumDiffSquares < d_sum_diff_squares){
        //accept newB_phi
        d_Bss = newB_phi;
        d_sum_diff_squares = newSumDiffSquares;
    }

    double newB_SO = d_t + (d_myRand.Rand() * 2 - 1) * d_dt;
    newSumDiffSquares = calcSumDiffSquares(d_a, d_Bss, newB_SO, d_dsOver2);
    if(newSumDiffSquares < d_sum_diff_squares){
        //accept newB_SO
        d_t = newB_SO;
        d_sum_diff_squares = newSumDiffSquares;
    }

    double newB_e = d_dsOver2 + (d_myRand.Rand() * 2 - 1) * d_ddsOver2;
    newSumDiffSquares = calcSumDiffSquares(d_a, d_Bss, d_t, newB_e);
    if(newSumDiffSquares < d_sum_diff_squares){
        //accept newB_e
        d_dsOver2 = newB_e;
        d_sum_diff_squares = newSumDiffSquares;
    }
}

void MonteCarloFit::fastMonteCarloNTimes(int n){
    for(size_t i = 0; i < n; ++i){
        fastMonteCarloOnce();
    }
}

bool MonteCarloFit::plotResult(){
    double B_max;
    std::cout<<"B_max = ";
    std::cin>>B_max;
    int n;
    std::cout<<"How many points to plot: ";
    std::cin>>n;

    std::string filename;
    std::cout<<"Save data to file: ";
    while(filename.size()==0){
        std::getline(std::cin, filename);
    }

    std::fstream myfile;
    myfile.open(filename.c_str(), std::ios::out);

    double dB = B_max/n;
    double B_min = dB/1000;
    for(double B=B_min; B<B_max; B+=dB){
        double s = sigma(B, d_a, d_Bss, d_t, d_dsOver2);
        myfile<<B<<"\t"<<s<<"\n";
    }
    myfile.close();

    //---
    std::fstream myfile2;
    filename = "para_" + filename;
    myfile2.open(filename.c_str(), std::ios::out);
    double alpha = d_a/(e*e/2/pi/pi/h_bar);
    myfile2<<"a = "<<d_a<<"\n";
    //myfile2<<"alpha = "<<alpha<<"\n";
    myfile2<<"Bss = "<<d_Bss<<"\n";
    myfile2<<"t = tau/tau_s = "<<d_t<<"\n";
    myfile2<<"dsOver2 = ds/2 = "<<d_dsOver2<<"\n";


    return true;
}

void MonteCarloFit::seta(double a){
    d_a = a;
}

void MonteCarloFit::setda(double da){
    d_da = da;
}

void MonteCarloFit::setB_phi(double B_phi){
    d_Bss = B_phi;
}

void MonteCarloFit::setdB_phi(double dB_phi){
    d_dBss = dB_phi;
}

void MonteCarloFit::setB_SO(double B_SO){
    d_t = B_SO;
}

void MonteCarloFit::setdB_SO(double dB_SO){
    d_dt = dB_SO;
}

void MonteCarloFit::setB_e(double B_e){
    d_dsOver2 = B_e;
}

void MonteCarloFit::setdB_e(double dB_e){
    d_ddsOver2 = dB_e;
}
