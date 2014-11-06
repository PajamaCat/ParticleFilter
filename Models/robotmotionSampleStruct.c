/*
 * robotmotionSampleStruct.c

 *
 *  Created on: Oct 31, 2014
 *      Author: chenxiaoyu
 */
#include "RelativeMultiFlock.c";
#include <math.h>;

particleCloud robotmotionSampleStruct(particleCloud X, double tv, double rv){
	double tvnoise = 0.1;
	double rvnoise = 0.17;
	particleCloud result;
	if (tv !=0 || rv != 0){
		double ntv[M] = {};
		double nrv[M] = {};
		double r[M] = {};
		//TODO implement randNormal
		ntv = randNormal(M);
		nrv = randNormal(M);
		double deltaThe[M] = {};
		for (int i = 0; i < M; i++){
			ntv[i] = ntv[i] * tvnoise + tv;
			nrv[i] = nrv[i] * rvnoise + rv;
			r[i] = ntv[i] / nrv[i];
			deltaThe[i] = nrv[i] * input.deltat;
			X.partX[i] = X.partX[i] - r[i] * sin(X.partHeading[i]) + r[i] * sin(X.partHeading[i] + deltaThe[i]);
			X.partY[i] = X.partY[i] + r[i] * cos(X.partHeading[i]) - r[i] * cos(X.partHeading[i] + deltaThe[i]);
			X.partHeading[i] += deltaThe[i];
		}
		return X;
	}
	return NULL;
}

