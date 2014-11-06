#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Tools.c";

int MAX_TIME = 1000;

typedef struct{
	int t;
	int numOfNeighbors;
	int hostID;
	double deltat;
    double rv[];
    double tv[];
    double range[];
    double orientation[];
    double bearing[];
    int id[];
    double p[][][];
    double pHost[][];
}inputData;

typedef struct{
	double partX[];
	double partY[];
	double partHeading[];
	double weight[];
	double nextWeight[];
	int counter;
}particleCloud;

typedef struct{
	particleCloud particleClouds[];
}particleClouds;

typedef struct{
	double cdata[];
	double colorMap[];
}mov;

typedef struct{
	particleCloud X;
	mov Mov;
}simulationInitOutput;

inputData input;

int numOfRobots = input.numOfNeighbors + 1;
int hostRobot = input.hostID;

double dead = 0.1;
double resample_thresh = 0.1;
int M = 100;
double lowWeightConstant = pow(M_E, -10);
int idcnt[numOfRobots] = {};

particleCloud particleFilter(particleCloud original, double bearing, double orientation, double range, double tv, double rv){
	particleCloud XBar = robotmotionSampleStruct(original, tv, rv);
	double* tempWeight = newFilterpdfRelative(XBar, bearing, orientation, range);
	double currentLowestSum = 0;
	for (int i = 0; i < M; i++){
		original.weight[i] = original.nextWeight[i] * tempWeight[i];
		if (original.weight[i] <= lowWeightConstant){
			currentLowestSum += original.weight[i];
		}
	}

	double reinjectRange = 0.3;
	double reinjectBearing = M_PI / 8;

	polarCoordinates polars = cart2pol(XBar.partX, XBar.partY);
	double numBearingError = 0;
	double numRangeError = 0;

}

particleClouds simulationInit(){
	particleCloud E[numOfRobots] = {};
	particleClouds result;
	for (int i = 0; i < numOfRobots; i++){
		particleCloud current;
		double x[M] = {};
		double y[M] = {};
		double heading[M] = {};
		double weight[M] = {};
		double nextWeight[M] = {};
		for (int j = 0; j < M; j++){
			weight[j] = 0;
			nextWeight[j] = 0;
		}
		current.partX = x;
		current.partY = y;
		current.partHeading = heading;
		current.weight = weight;
		current.nextWeight = nextWeight;
		current.counter = 0;
		E[i] = current;
	}
	return E;
}
