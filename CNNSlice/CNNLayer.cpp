#include <stdio.h>

void FClayerForward(double * PreLayer, double * NexLayer, double * Weight, int DemenA, int DemenB, double* NexLayerB)
{
	/*
	DemenB is the size of NexLayer and NexLayerB
	DemenA is the size of PreLayer
	Weight should be DemenA*DemenB
	*/
	int i = 0;
	int j = 0;
	for (i = 0; i < DemenB; i++)
	{
		for (j = 0; j < DemenA; j++)
		{
			NexLayer[i] = NexLayer[i] + PreLayer[j] * (Weight[j*DemenB+i]);
		}
		NexLayer[i] = NexLayer[i] + NexLayerB[i];
	}
}

/*
void AddNoise(double * CurrLayer, int * orderInd, double * WeightPre, double * WeightNex, int DemenPre, int DemenNex, int DemenCur, double* CurrBias)
{
	
	//DemenB is the size of NexLayer and NexLayerB
	//DemenA is the size of PreLayer
	//Weight should be DemenA*DemenB
	
	int i = 0;
	int j = 0;
	for (i = 0; i < DemenB; i++)
	{
		for (j = 0; j < DemenA; j++)
		{
			NexLayer[i] = NexLayer[i] + PreLayer[j] * (Weight[j*DemenB + i]);
		}
		NexLayer[i] = NexLayer[i] + NexLayerB[i];
	}
}
void Reorder(double * CurrLayer, int * orderInd, double * WeightPre, double * WeightNex, int DemenPre, int DemenNex, int DemenCur, double* CurrBias)
{
	
	//DemenB is the size of NexLayer and NexLayerB
	//DemenA is the size of PreLayer
	//Weight should be DemenA*DemenB
	
	int i = 0;
	int j = 0;
	for (i = 0; i < DemenB; i++)
	{
		for (j = 0; j < DemenA; j++)
		{
			NexLayer[i] = NexLayer[i] + PreLayer[j] * (Weight[j*DemenB + i]);
		}
		NexLayer[i] = NexLayer[i] + NexLayerB[i];
	}
}
*/

void FClayerForwardRelu(double * layer, int DemenB)
{
	/*
	DemenB is the size of the layer
	DemenA is the size of PreLayer
	Weight should be DemenA*DemenB
	*/
	int i = 0;
	int j = 0;
	for (i = 0; i < DemenB; i++)
	{
		if (layer[i] < 0)
		{
			layer[i] = 0;
		}
	}
}

void FClayerForward1(double PreLayer[784], double NexLayer[200], double Weight[200][784], int DemenA, int DemenB, double NexLayerB[200])
{
	/*
	DemenB is the size of NexLayer and NexLayerB
	DemenA is the size of PreLayer
	Weight should be DemenA*DemenB
	*/
	int i = 0;
	int j = 0;
	for (i = 0; i < DemenB; i++)
	{
		for (j = 0; j < DemenA; j++)
		{
			NexLayer[i] = NexLayer[i] + PreLayer[j] * (Weight[i][j]);
		}
		NexLayer[i] = NexLayer[i] + NexLayerB[i];
	}
}


double ExpEach(double * Layer, int Dem)
{
	int i = 0;
	double result = 0.0;
	for (i=0;i<Dem;i++)
	{
		result= result+Layer[i];
	}
	return result;
}


//============fully connected layer for backward==================================
//FClayerBackward(BNode.DFourth, ONode.Loss, 50, 10, NNode.Thired, BNode.Thired, NWeight.Fourth, BNode.Db4);
void FClayerBackward(double * DWeight, double * Dscore, int DemenA, int DemenB, double *Node, double * denode, double * Weight, double * DB)
{
	/*
	DemenB is the size of previous dscore
	DemenA is the size of next layer
	Weight should be DemenA*DemenB
	*/
	int i = 0;
	int j = 0;
	for (j = 0; j < DemenA; j++)
	{
		denode[j] = 0;
	}
	for (i = 0; i < DemenB; i++)
	{
		for (j = 0; j < DemenA; j++)
		{
			//NexLayer[i] = NexLayer[i] + PreLayer[j] * (Weight[i*DemenA + j]);
			DWeight[j*DemenB + i] = Dscore[i] * Node[j];
			denode[j] = denode[j] + Weight[j*DemenB + i] * Dscore[i];
		}
		DB[i] = Dscore[i];
	}
	/*
	for (i = 0; i < DemenA; i++)
	{
		for (j = 0; j < DemenB; j++)
		{
			//NexLayer[i] = NexLayer[i] + PreLayer[j] * (Weight[i*DemenA + j]);
			denode[i] = denode[i] + Weight[j*DemenA + i] * Dscore[j];
		}
		//DB[i] = Dscore[i];
	}
	*/
}


void FClayerBackwardUpdate(double * DWeight, double * deBias, int DemensA, int DemensB, double learningRate,double *Weight, double * Bais)
{
	int i = 0;
	for (i = 0; i < DemensA; i++)
	{
		Weight[i] = Weight[i] - DWeight[i] * learningRate;
	}
	for (i = 0; i < DemensB; i++)
	{
		Bais[i] = Bais[i] - deBias[i] * learningRate;
	}
}