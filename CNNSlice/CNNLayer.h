#pragma once
void FClayerForward(double * PreLayer, double * NexLayer, double * Weight, int DemenA, int DemenB, double* NexLayerB);
void FClayerForward1(double PreLayer[784], double NexLayer[200], double Weight[200][784], int DemenA, int DemenB, double NexLayerB[200]);
double ExpEach(double * Layer, int Dem);
void FClayerForwardRelu(double * layer, int DemenB);
void FClayerBackward(double * DWeight, double * Dscore, int DemenA, int DemenB, double *Node, double * denode, double * Weight, double * DB);
void FClayerBackwardUpdate(double * DWeight, double * deBias, int DemensA, int DemensB, double learningRate, double *Weight, double * Bais);