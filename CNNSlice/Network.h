/*#pragma once
This file define the structure of the network.
Macro defines the parameters


*/

#define NUMOFLAYERS 6
#define Input 784

void HLS_FPGA_NET(
	const double * InputDataW,   //all weights
	const double * InputDataM,	//input image
	const double * InputBais,	//all bias
	int flag,
	double *OutputData
);