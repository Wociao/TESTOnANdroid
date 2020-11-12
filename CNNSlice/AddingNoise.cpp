/*adding noise*/


#include <math.h>
#include <cmath>
#include <iostream>
#include <cstdlib>// Header file needed to use rand
using namespace std;

#define MAXLEN 160000


double buff[MAXLEN];
int buffInd[MAXLEN];


double buffB[MAXLEN];
int buffIndB[MAXLEN];

double buffP[MAXLEN];
int buffIndP[MAXLEN];

int bufTMP[800];
int bufTMPF[800];

int bufTMPT[800];
int bufTMPTind[800];

int bufFirstHalf[100];
int buffSecondhalf[100];

int IsInTheArray(int Ind, int lenDef)
{
	int i = 0;
	int Flag = 0;	//0 ��ʾû�д���
	for (i = 0; i < lenDef; i++)
	{
		if (Ind == buffIndP[i])
			return  1;
	}
	return Flag;

}


int IsInTheArrayB(int Ind, int lenDef)
{
	int i = 0;
	int Flag = 0;	//0 ��ʾû�д���
	for (i = 0; i < lenDef; i++)
	{
		if (Ind == bufTMPTind[i])
			return  1;
	}
	return Flag;

}


/*Max 200 MAXLEN */
int AddingNoise(double * buf, int number, int type, int TotLen)
{
	

	int i = 0;
	int j = 0;
	int k = 0;
	int indexNU = 0;

	for (int i = 0; i < MAXLEN; i++)
	{
		buff[i]=0;
		buffInd[i]=0;
	}

	if (type == 0)
	{
		for (i = 0; i < number; i++)
		{
			indexNU=rand() % TotLen;
			//buf[indexNU] = 0;
			buf[indexNU] = buf[indexNU]*-2;
		}
	}
	else
	{
		if (number > MAXLEN)
		{
			number = MAXLEN;
		}
		
		for (i = 0; i < MAXLEN; i++)
		{
			buff[i] = 0;
		}
		double min=0;
		int minInd = 0;
		//int minInd = 0;
		for (i = 0; i < TotLen; i++)
		{
			//Ŀ��ֵ����
			if (fabs(buf[i]) > min)
			{
				//buff[minInd] = buf[i];
				buff[minInd] = fabs(buf[i]);
				buffInd[minInd] = i;
				//go through the buf and update with the target 
				min = 1000;
				for (k = 0; k < number; k++)
				{
							
					if (buff[k] < min)
					{
						min = buff[k];
						minInd = k;
					}
								
				}
				//break;
					
				
			}
		}
		for (k = 0; k < number; k++)
		{
			//buf[buffInd[k]] = 0;	
			buf[buffInd[k]] = buf[buffInd[k]] * 0.3;// buf[buffInd[k]]*-1;
			//printf("==%d==,", buffInd[k]);
		}
		printf("\n");
	}
	return 0;
}



/*Max 200 MAXLEN 
defence Flaten method
*/
bool IfInTheList(int target, int * NameList, int NamelistLen)
{
	//return true;
	int i = 0;
	for (i = 0; i < NamelistLen; i++)
	{
		if (target == NameList[i])
		{
			return true;
		}
	}
	return false;
}
//����flattenЧ��
int AddingNoise_def_flat_V1(double * buf, int number, int type, int TotLen, int * ProInd, int Len, int FlatFactor, int Dem, int NM, int NP)
{

	printf("using defence for dac-.......\n");
	int i = 0;
	int j = 0;
	int k = 0;
	int indexNU = 0;

	for (int i = 0; i < MAXLEN; i++)
	{
		buff[i] = 0;
		buffInd[i] = 0;
	}

	if (type == 0)
	{
		for (i = 0; i < number; i++)
		{
			indexNU = rand() % TotLen;
			//buf[indexNU] = 0;
			buf[indexNU] = buf[indexNU] * -2;
		}
	}
	else
	{
		if (number > MAXLEN)
		{
			number = MAXLEN;
		}

		for (i = 0; i < MAXLEN; i++)
		{
			buff[i] = 0;
		}
		double min = 0;
		int minInd = 0;
		//int minInd = 0;
		for (i = 0; i < TotLen; i++)
		{
			//Ŀ��ֵ����
			if (fabs(buf[i]) > min)
			{
				buff[minInd] = buf[i];
				buffInd[minInd] = i;
				//go through the buf and update with the target 
				min = 1000;
				for (k = 0; k < number; k++)
				{

					if (buff[k] < min)
					{
						min = buff[k];
						minInd = k;
					}

				}
				//break;


			}
		}
		for (k = 0; k < number; k++)
		{
			//buf[buffInd[k]] = 0;	
			if (IfInTheList(floor(buffInd[k]/ Dem), ProInd, Len))
			{
				buf[buffInd[k]] = buf[buffInd[k]] * (FlatFactor-2)/ FlatFactor;
				//printf("find one \n");
			}
			else 
			{
				buf[buffInd[k]] = buf[buffInd[k]] * -1;
			}
			
			//printf("==%d==,", buffInd[k]);
		}
		printf("\n");
	}
	return 0;
}

int DACbufIndF[800];
double DACbufIndFVal[800];

// ���ܹ����ͻ����
int AddingNoise_def_flat_V2(double * buf, int number, int type, int TotLen, int * ProInd, int Len, int FlatFactor, int Dem, int NM, int NP)
{

	printf("using defence for dacV2-.......\n");
	int i = 0;
	int j = 0;
	int k = 0;
	int indexNU = 0;

	for (int i = 0; i < MAXLEN; i++)
	{
		buff[i] = 0;
		buffInd[i] = 0;
	}
	for (int i = 0; i < 800; i++)
	{
		DACbufIndF[i] = 0;
	}
	int CountN = 0;
	int CountDAC1 = 0;
	int CountDAC2 = 0;
	if (type == 0)
	{
		for (i = 0; i < number; i++)
		{
			indexNU = rand() % TotLen;
			//buf[indexNU] = 0;
			buf[indexNU] = buf[indexNU] * -2;
		}
	}
	else
	{
		if (number > MAXLEN)
		{
			number = MAXLEN;
		}

		for (i = 0; i < MAXLEN; i++)
		{
			buff[i] = 0;
			buffB[i] = 0;
		}
		//ѡǰ NM
		double min = 0;
		int minInd = 0;
		/*
		//int minInd = 0;
		for (i = 0; i < TotLen; i++)
		{
			//Ŀ��ֵ����
			if (fabs(buf[i]) > min )
			{
				if (IfInTheList(floor(i / Dem), buffIndB, NM) == false)
				{
					buffB[minInd] = fabs(buf[i]);
					buffIndB[minInd] = i;
					//go through the buf and update with the target 
					min = 1000;
					for (k = 0; k < NM; k++)
					{

						if (buffB[k] < min)
						{
							min = buffB[k];
							minInd = k;
						}

					}
					DACbufIndF[CountN] = floor(i / Dem);
					CountN++;
					//break;
				}
				

			}
		}
		*/
		//ѡĿ��
		min = 0;
		minInd = 0;
		//int minInd = 0;
		for (i = 0; i < TotLen; i++)
		{
			//Ŀ��ֵ����
			if (fabs(buf[i]) > min)
			{
				if (IfInTheList(floor(i / Dem), ProInd, NM) == false)
				{
					buff[minInd] = fabs(buf[i]);
					buffInd[minInd] = i;
					//go through the buf and update with the target 
					min = 1000;
					for (k = 0; k < number ; k++)
					{

						if (buff[k] < min)
						{
							min = buff[k];
							minInd = k;
						}

					}
					//break;
				}
				else
				{
					CountDAC2++  ;
				}


			}
		}
		int count = 0;
		for (k = 0; k < number; k++)
		{
			//buf[buffInd[k]] = 0;	
			if (buffInd[k]>0)
			{
				//buf[buffInd[k]] = buf[buffInd[k]];
				count++;
				//printf("find one \n");
				buf[buffInd[k]] = buf[buffInd[k]] * -1;
			}
			/*
			else
			{
				count++;
				buf[buffInd[k]] = buf[buffInd[k]] * -1;
				//printf("==%d==%d--->%d,", k, number + NM, count);
			}
				*/
			//printf("==%d==,", buffInd[k]);
		}
		printf("=====total %d===Defence summary: total %d \n", count, CountDAC2);
	}
	return 0;
}

/*Max 200 MAXLEN */
int AddingNoiseDef(double * buf, int number, int type, int TotLen, int DefLen)
{


	int i = 0;
	int j = 0;
	int k = 0;
	int indexNU = 0;

	for (int i = 0; i < MAXLEN; i++)
	{
		buff[i] = 0;
		buffInd[i] = 0;
		buffP[i] = 0;
		buffP[i] = 0;
	}

	//�ҳ�Ҫ�����Ľڵ�
	double min = 0;
	int minInd = 0;
	for (i = 0; i < TotLen; i++)
	{
		//Ŀ��ֵ����
		if (fabs(buf[i]) > min)
		{
			buffP[minInd] = buf[i];
			buffIndP[minInd] = i;
			//go through the buf and update with the target 
			min = 1000;
			for (k = 0; k < DefLen; k++)
			{

				if (buffP[k] < min)
				{
					min = buffP[k];
					minInd = k;
				}

			}
			//break;


		}
	}

	//�����

	if (type == 0)	//�����
	{
		for (i = 0; i < number; i++)
		{
			indexNU = rand() % TotLen;
			while (IsInTheArray(indexNU, DefLen))
			{
				indexNU = rand() % TotLen;
			}
			//buf[indexNU] = 0;
			buf[indexNU] = buf[indexNU] * -1;
		}
	}
	else      //����Ҫ�ļ�
	{
		if (number > MAXLEN)
		{
			number = MAXLEN;
		}

		for (i = 0; i < MAXLEN; i++)
		{
			buff[i] = 0;
		}
		
		//int minInd = 0;
		min = 0;
		minInd = 0;
		for (i = 0; i < TotLen; i++)
		{
			//Ŀ��ֵ����
			if (fabs(buf[i]) > min)
			{
				buff[minInd] = buf[i];
				buffInd[minInd] = i;
				//go through the buf and update with the target 
				min = 1000;
				for (k = 0; k < number; k++)
				{

					if (buff[k] < min)
					{
						min = buff[k];
						minInd = k;
					}

				}
				//break;


			}
		}
		for (k = 0; k < number; k++)
		{
			//buf[buffInd[k]] = 0;	
			if (IsInTheArray(buffInd[k], DefLen))
				continue;
			buf[buffInd[k]] = buf[buffInd[k]] * -1;
			//printf("==%d==,", buffInd[k]);
		}
		printf("\n");
	}
	return 0;
}





/*Max 200 MAXLEN */
int AddingNoiseOurDef(double * buf, int number, int type, int demA, int demB, int ProLen, int DefLen)
{
	/*demA -> previous layer*/
	int TotLen = demA * demB;
	int i = 0;
	int j = 0;
	int k = 0;
	int indexNU = 0;
	int ind = 0;

	for (int i = 0; i < MAXLEN; i++)
	{
		buff[i] = 0;
		buffInd[i] = 0;
		buffP[i] = 0;
		buffP[i] = 0;
	}

	//�ҳ�Ҫ�����Ľڵ�
	// 1. �Ȱѷ���Ҫ�������Ȩֵ�ҳ�����index����buffIndP
	double min = 0;
	int minInd = 0;
	for (i = 0; i < TotLen; i++)
	{
		//Ŀ��ֵ����
		if (fabs(buf[i]) > min)
		{
			buffP[minInd] = buf[i];
			buffIndP[minInd] = i;
			//go through the buf and update with the target 
			min = 1000;
			for (k = 0; k < number; k++)
			{

				if (buffP[k] < min)
				{
					min = buffP[k];
					minInd = k;
				}

			}
			//break;


		}
	}
	// 2. ��������Ҫ���Ȩֵ�ֲ���Ƶ������bufTMP
	for (i = 0; i < demB; i++)
	{
		bufTMP[i] = 0;
		bufTMPT[i] = 0;
		bufTMPTind[i] = 0;
	}
	
	for (i = 0; i < number; i++)
	{
		ind= int(buffIndP[i] % demB);
		bufTMP[ind] = bufTMP[ind] + 1;
	}
	// 3. ����Ƶ���ߵ�ǰK�������б���������K���ֲ�ȷ��index �� bufTMPF bufTMPTind
	min = 0;
	minInd = 0;
	for (i = 0; i < demB; i++)
	{
		//Ŀ��ֵ����
		if (bufTMP[i] > min)
		{
			bufTMPT[minInd] = bufTMP[i];
			bufTMPTind[minInd] = i;
			//go through the buf and update with the target 
			min = 65530;
			for (k = 0; k < ProLen; k++)
			{

				if (bufTMPT[k] < min)
				{
					min = bufTMPT[k];
					minInd = k;
				}

			}
			//break;


		}
	}
	printf("-------------Protected ind-------------\n");
	for (k = 0; k < ProLen; k++)
	{
		printf(" %d ,", bufTMPTind[k]);

	}
	printf("\n");
	printf("--------------------end---total %d----------------\n", ProLen);


	//�����

	if (type == 0)	//�����
	{
		for (i = 0; i < number; i++)
		{
			indexNU = rand() % TotLen;
			ind = indexNU % demB;
			//while (IsInTheArrayB(ind, ProLen))
			//{
			//	indexNU = rand() % TotLen;
			//}
			if (IsInTheArrayB(ind, ProLen))
				continue;
			//buf[indexNU] = 0;
			buf[indexNU] = buf[indexNU] * -1;
		}
	}
	else      //����Ҫ�ļ�
	{
		if (number > MAXLEN)
		{
			number = MAXLEN;
		}

		for (i = 0; i < MAXLEN; i++)
		{
			buff[i] = 0;
		}

		//int minInd = 0;
		min = 0;
		minInd = 0;
		for (i = 0; i < TotLen; i++)
		{
			//Ŀ��ֵ����
			if (fabs(buf[i]) > min)
			{
				buff[minInd] = buf[i];
				buffInd[minInd] = i;
				//go through the buf and update with the target 
				min = 1000;
				for (k = 0; k < number; k++)
				{

					if (buff[k] < min)
					{
						min = buff[k];
						minInd = k;
					}

				}
				//break;


			}
		}
		for (k = 0; k < number; k++)
		{
			//buf[buffInd[k]] = 0;	
			ind = buffInd[k] % demB;
			//while (IsInTheArrayB(ind, ProLen))
			if (IsInTheArrayB(ind, ProLen))
				continue;
			buf[buffInd[k]] = buf[buffInd[k]] * -1;
			//printf("==%d==,", buffInd[k]);
		}
		printf("\n");
	}
	return 0;
}