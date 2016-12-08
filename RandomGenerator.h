#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H


#define A_SCHRAGE 16807
#define M_SCHRAGE 2147483647
#define Q_SCHRAGE 127773
#define R_SCHRAGE 2836

class RandGenerator{
private:
	double x;
	long z;
	long z_next;

public:
	void SetSeed(long);
	double Rand();
	RandGenerator(){}
	~RandGenerator(){}
};



#endif
