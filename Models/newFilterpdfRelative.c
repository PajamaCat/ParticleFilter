/*
 * newFilterpdfRelative.c
 *
 *  Created on: Oct 31, 2014
 *      Author: chenxiaoyu
 */
#include "RelativeMultiFlock.c";
#include "Tools.c";
#include <math.h>;

#define DBL_EPSILON 2.2204460492503131e-16;

double* newFilterpdfRelative(particleCloud XBar, double bearing, double orientation, double range){
	double tempWeight[M] = {};
	for (int i = 0; i < M; i++){
		tempWeight[i] = 1;
	}
	polarCoordinates pc = cart2pol(XBar.partX, XBar.partY);
	double rawOrientation[M] = {};
	for (int i = 0; i < M; i++){
		rawOrientation[i] = M_PI + pc.theta[i] - XBar.partHeading[i];
	}
	double partOrientation[M] = normalizeAngle(rawOrientation);

	double bearingMu = -0.18;
	double bearingSig = 0.23;
	double orientationMu = -0.189;
	double orientationSig = 0.23;
	double rangeMu = 0.07;
	double rangeSig = 0.27;

	double binSize = 0.02;

	for (int i = 0; i < M; i++){
		if (pc.rho[i] > 1){
			tempWeight[i] *= -10/7*(pc.rho[i]-1) + 1;
		}

		if (pc.rho[i] < dead * 0.6){
			tempWeight[i] = 0;
		}

		double rangeError = pc.rho[i] - range;
		double temp = abs(rangeError) % binSize;
		if (temp > binSize / 2){
			rangeError = rangeError + binSize - temp;
		}
		else{
			rangeError = rangeError - temp;
		}
		tempWeight[i] *= TempWeightofbin(rangeError, binSize, rangeMu, rangeSig);

		double bearingError = pc.theta[i] - bearing;
		temp = abs(bearingError) % binSize;
		if (temp > binSize / 2){
				bearingError = bearingError + binSize - temp;
			}
			else{
				bearingError = bearingError - temp;
			}
		tempWeight[i] *= TempWeightofbin(bearingError, binSize, bearingMu, bearingSig);

		double orientationError = partOrientation[i] - orientation;
		temp = abs(orientationError) % binSize;
		if (temp > binSize / 2){
					orientationError = orientationError + binSize - temp;
				}
				else{
					orientationError = orientationError - temp;
				}
		tempWeight[i] *= TempWeightofbin(orientationError, binSize, orientationMu, orientationSig);

		if (tempWeight[i] == 0){
			tempWeight[i] = DBL_EPSILON;
		}
	}
	return tempWeight;
}

double TempWeightofbin(double error, double bin_size, double mu, double sig){
	//TODO implement normCDF
	return (normCDF(error + bin_size / 2, mu, sig) - normCDF(error - bin_size / 2, mu, sig)) * 10;
}

