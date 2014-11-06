/*
 * Tools.c
 *
 *  Created on: Oct 31, 2014
 *      Author: chenxiaoyu
 */
#include <stdlib.h>;
#include <math.h>;

typedef struct{
	double theta[];
	double rho[];
}polarCoordinates;

polarCoordinates cart2pol(double* partX, double* partY){
	double t[] = {};
	double r[] = {};
	for (int i = 0; i < sizeof(partX); i++){
		t[i] = atan2(partY[i], partX[i]);
		r[i] = sqrt(pow(partX[i], 2) + pow(partY[i], 2));
	}
	polarCoordinates result;
	result.theta = t;
	result.rho = r;
	return result;
}

double* normalizeAngle(double* x){
	for (int i = 0; i < sizeof(x); i++){
		if (x[i] > M_PI){
			x[i] -= 2*M_PI;
		}
		else if (x[i] < -M_PI){
			x[i] += 2*M_PI;
		}
	}
	for (int i = 0; i < sizeof(x); i++){
		if (x[i] > M_PI){
			x[i] -= 2*M_PI;
		}
		else if (x[i] < -M_PI){
			x[i] += 2*M_PI;
		}
	}
	return x;
}
