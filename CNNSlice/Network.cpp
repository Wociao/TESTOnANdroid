#include <stdio.h>

/*
struct NetWorkNode
{

	double Seond1[200] ;
	double Thired[50];
	double Fourth[10];
	double Seond1B[200];
	double ThiredB[50];
	double FourthB[10];
};

struct NetWorkWeight
{
	double Seond1[200][784];
	double Thired[50][200];
	double Fourth[10][50];
};

int loadWeight()
{
	return 1;
}
*/

#define FIRST 784
#define SECOND 200
#define THIRD 50

void HLS_FPGA_NET(
	const double * InputDataW,   //all weights
	const double * InputDataM,	//input image
	const double * InputBais,	//all bias
	int flag,
	double *OutputData
)
{
	//========variables for node and weight============
	double Node1[FIRST];
	double Node2[SECOND];
	double Node3[THIRD];

	double BNode2[SECOND];
	double BNode3[THIRD];

	double Weight12[FIRST*SECOND];
	double Weight23[SECOND*THIRD];
	int Count;
	int i = 0;
	int j = 0;
	//============flag=1: load weight==================
	if (flag == 1)
	{
		//====all weights are stored in one array, should be orginized by CPU part.
		for (Count = 0; Count < FIRST*SECOND;Count++)
		{
			Weight12[Count]= InputDataW[Count];
		}
		for (Count = 0; Count < SECOND*THIRD; Count++)
		{
			Weight23[Count] = InputDataW[Count+ SECOND * THIRD];
		}
		//====all bias are stored in one array, should be orginized by CPU part.
		for (Count = 0; Count < SECOND; Count++)
		{
			BNode2[Count] = InputBais[Count];
		}
		for (Count = 0; Count < THIRD; Count++)
		{
			BNode3[Count] = InputBais[Count + SECOND ];
		}
	}
	else
	{
		//===========flag=2 load image================
		if (flag == 2)
		{
			for (Count = 0; Count < FIRST; Count++)
			{
				Node1[Count]= InputDataM[Count];
			}
		}
		//============other: inference================
		else
		{
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			//==========layer 1 to layer 2=============
			for (i = 0; i < SECOND; i++)
			{
				for (j = 0; j < FIRST; j++)
				{
					Node2[i] = Node2[i] + Node1[j] * (Weight12[j*SECOND + i]);
				}
				Node2[i] = Node2[i] + BNode2[i];

			}
			//===========relu==========================
			for (i = 0; i < SECOND; i++)
			{
				if (Node2[i] < 0)
				{
					Node2[i] = 0;
				}
			}
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			//==========layer 2 to layer 3=============
			for (i = 0; i < THIRD; i++)
			{
				for (j = 0; j < SECOND; j++)
				{
					Node3[i] = Node3[i] + Node2[j] * (Weight23[j*THIRD + i]);
				}
				Node3[i] = Node3[i] + BNode3[i];

			}
			//===========relu==========================
			for (i = 0; i < THIRD; i++)
			{
				if (Node3[i] < 0)
				{
					Node3[i] = 0;
				}
			}
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
	}
	OutputData = Node3;



}