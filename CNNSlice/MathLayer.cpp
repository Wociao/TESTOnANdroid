#include <math.h>

double ExpSumToProb(double * Orig, double *NewO, int dem ,double *Prob)
{
	double Sum=0;
	int i = 0;
	for (i = 0; i < dem; i++)
	{
		NewO[i] = exp(Orig[i]);
		Sum = Sum + NewO[i];
	}
	for (i = 0; i < dem; i++)
	{
		Prob[i] = NewO[i]/Sum;
	}
	return Sum;
}


double ExpSumToProbToLoss(double * Orig, double *NewO, int dem, double *Prob, double *Loss,int GroundT)
{
	double Sum = 0;
	int i = 0;
	for (i = 0; i < dem; i++)
	{
		NewO[i] = exp(Orig[i]);
		Sum = Sum + NewO[i];
	}
	for (i = 0; i < dem; i++)
	{
		Prob[i] = NewO[i] / Sum;
	}
	for (i = 0; i < dem; i++)
	{
		if (i == GroundT)
		{
			Loss[i] = Prob[i]-1;
		}
		else
		{
			Loss[i] = Prob[i];
		}
	}
	return Sum;
}



double LogLossSingle(double *Prob, int GroundT)
{
	double Loss = 0;
	Loss = -log(Prob[GroundT]);
	return Loss;
}