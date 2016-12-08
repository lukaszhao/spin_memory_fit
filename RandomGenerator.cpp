#include "RandomGenerator.h"

void RandGenerator::SetSeed(long seed){
	z_next=seed;
}

double RandGenerator::Rand(){
	z=z_next;
	z_next=A_SCHRAGE*(z%Q_SCHRAGE)-R_SCHRAGE*long(z/Q_SCHRAGE);
	if(z_next<0)z_next+=M_SCHRAGE;
	return double(z)/double(M_SCHRAGE);
}
