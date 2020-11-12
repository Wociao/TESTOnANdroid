#include <stdio.h>
#include "FileIO.h"
#include "CNNLayer.h"
#include "MathLayer.h"
//#include "Network.h"


#define BATSIZE 32

/*这一部分定义神经网络结构*/
/*=========================================
NetWorkNode:网络节点，B指的是bias

OutputNode: 输出层之后softmax出结果

LossNode：输出各种loss value

NetWorkWeight：各层之间节点权重
=========================================*/

struct NetWorkNode
{

	double Seond1[200];
	double Thired[50];
	double Fourth[10];
	double Seond1B[200];
	double ThiredB[50];
	double FourthB[10];
} NNode;

struct OutputNode
{

	double Exp[10];
	double SumofExp;
	double Prob[10];
	double Loss[10];
	
} ONode;

struct BackNode
{

	double Db4[10];
	double Db3[50];
	double Db2[200];
	double Seond1[200];
	double Thired[50];
	double Fourth[10];
	double DSeond1[200 * 784];
	double DThired[50 * 200];
	double DFourth[10 * 50];

} BNode;

struct NetWorkbatch
{
	double Seond1Bat[BATSIZE][200 * 784];
	double ThiredBat[BATSIZE][50 * 200];
	double FourthBat[BATSIZE][10 * 50];
	double Seond1BBat[BATSIZE][200];
	double ThiredBBat[BATSIZE][50];
	double FourthBBat[BATSIZE][10];
} NBat;

struct NetWorkWeight
{
	double Seond1[200*784];
	double Thired[50*200];
	double Fourth[10*50];
} NWeight;
//=====================================================================
/*这一部分定义神经网络结构*/
/*
=============+++++++++++++++
2.307179448830937 [0.10098569 0.11170167 0.09640025 0.10333706 0.09606873 0.09076936
 0.09954162 0.10587555 0.09583138 0.0994887 ] 6
=============+++++++++++++++
*/
int findMax(double prob[10], int dem)
{
	int i = 0;
	int k = 0;
	double TMP = 0;
	for (i = 0; i < dem; i++)
	{
		if (TMP < prob[i])
		{
			TMP = prob[i];
			k = i;
		}
	}
	return k;
}

int DigitNumber(int index)
{
	int Len = 1;
	double tmp = double(index);
	//while (double(double(tmp) / 10.0 )> 1)
	while (tmp / 10.0 >= 1)
	{
		tmp = tmp / 10;
		Len++  ;
	}
	return Len;
}
void CopyFilename(char *filenameB, char *filenameO)
{
	int i = 25;
	int j = 0;
	for (j = 0; j < i; j++)
	{
		filenameB[j] = filenameO[j];
	}
}
void nameMaker(char *filenameB, int Index)
{
	int i = 0;
	int len = 25;
	int startPoint = 18;
	int insertPoint = 13;
	int digitLen = DigitNumber(Index);
	int tmp;
	int Remain = Index;
	//平移 digitLen-1 个字符 减一是因为原来就有一个数字index
	//printf("=====%s====\n", filenameB);
	for (i = 0; i < startPoint - insertPoint; i++)
	{
		filenameB[startPoint-i+ digitLen-1]= filenameB[startPoint - i];
		//printf("=====%s====\n", filenameB);
	}
	//修改添加内容
	for (i = digitLen; i >0; i--)
	{
		tmp = Remain % 10;
		filenameB[insertPoint+i-1] = '0'+ tmp;
		Remain = int(Remain / 10);
		//filenameB[startPoint - i] = filenameB[startPoint - i - 1];
		//printf("+++%s++++\n", filenameB);
	}
	//filenameB[insertPoint] = 'C';
}


void nameMakerT(char *filenameB, int Index)
{
	int i = 0;
	int len = 25;
	int startPoint = 17;
	int insertPoint = 12;
	int digitLen = DigitNumber(Index);
	int tmp;
	int Remain = Index;
	//平移 digitLen-1 个字符 减一是因为原来就有一个数字index
	//printf("=====%s====\n", filenameB);
	for (i = 0; i < startPoint - insertPoint; i++)
	{
		filenameB[startPoint - i + digitLen - 1] = filenameB[startPoint - i];
		//printf("=====%s====\n", filenameB);
	}
	//修改添加内容
	for (i = digitLen; i > 0; i--)
	{
		tmp = Remain % 10;
		filenameB[insertPoint + i - 1] = '0' + tmp;
		Remain = int(Remain / 10);
		//filenameB[startPoint - i] = filenameB[startPoint - i - 1];
		//printf("+++%s++++\n", filenameB);
	}
	//filenameB[insertPoint] = 'C';
}

void initNode()
{
	int i;
	for (i = 0; i < 200; i++)
	{
		//NNode.Seond1[i] = 0.1;
		NNode.Seond1[i] = 0.0;
	}
	for (i = 0; i < 50; i++)
	{

		NNode.Thired[i] = 0.0;
	}
	for (i = 0; i < 10; i++)
	{
		NNode.Fourth[i] = 0.0;
	}

}



void initBNode()
{
	int i;
	for (i = 0; i < 200; i++)
	{
		//NNode.Seond1[i] = 0.1;
		BNode.Seond1[i] = 0.0;
	}
	for (i = 0; i < 50; i++)
	{

		BNode.Thired[i] = 0.0;
	}
	for (i = 0; i < 10; i++)
	{
		BNode.Fourth[i] = 0.0;
	}

}

void init()
{
	int i;
	for (i = 0; i < 200; i++)
	{
		//NNode.Seond1[i] = 0.1;
		NNode.Seond1B[i] = 0.1;
	}
	for (i = 0; i < 50; i++)
	{
		
		NNode.ThiredB[i] = 0.1;
	}
	for (i = 0; i < 10; i++)
	{
		NNode.FourthB[i] = 0.1;
	}
	
	for (i = 0; i < 200*784; i++)
	{
		//NNode.Seond1[i] = 0.1;
		NWeight.Seond1[i] = 0.00001;
	}
	for (i = 0; i < 200 * 50; i++)
	{
		//NNode.Seond1[i] = 0.1;
		NWeight.Thired[i] = 0.00001;
	}
	for (i = 0; i < 10 * 50; i++)
	{
		//NNode.Seond1[i] = 0.1;
		NWeight.Fourth[i] = 0.00001;
	}

}

void initB()
{
	int i;
	int j;
	for (j = 0; j < BATSIZE; j++)
	{
		for (i = 0; i < 200; i++)
		{
			//NNode.Seond1[i] = 0.1;
			NBat.Seond1BBat[j][i] = 0.0;
		}
		for (i = 0; i < 50; i++)
		{

			NBat.ThiredBBat[j][i] = 0.0;
		}
		for (i = 0; i < 10; i++)
		{
			NBat.FourthBBat[j][i] = 0.0;
		}

		for (i = 0; i < 200 * 784; i++)
		{
			//NNode.Seond1[i] = 0.1;
			NBat.Seond1Bat[j][i] = 0.0;
		}
		for (i = 0; i < 200 * 50; i++)
		{
			//NNode.Seond1[i] = 0.1;
			NBat.ThiredBat[j][i] = 0.0;
		}
		for (i = 0; i < 10 * 50; i++)
		{
			//NNode.Seond1[i] = 0.1;
			NBat.FourthBat[j][i] = 0.0;
		}
	}
	

}


void BatchSum()
{
	int i;
	int j;


	double tmp;
	double norm = 1;
	for (i = 0; i < 200; i++)
	{
		tmp = 0;
		for (j = 0; j < BATSIZE; j++)
		{
			tmp = NBat.Seond1BBat[j][i] + tmp;
		}
		//NNode.Seond1[i] = 0.1;
		NNode.Seond1B[i] = tmp/ norm;
	}
	for (i = 0; i < 50; i++)
	{
		tmp = 0;
		for (j = 0; j < BATSIZE; j++)
		{
			tmp = NBat.ThiredBBat[j][i] + tmp;
		}
		NNode.ThiredB[i] = tmp / norm;
	}
	for (i = 0; i < 10; i++)
	{
		tmp = 0;
		for (j = 0; j < BATSIZE; j++)
		{
			tmp = NBat.FourthBBat[j][i] + tmp;
		}
		NNode.FourthB[i] = tmp / norm;
	}

	for (i = 0; i < 200 * 784; i++)
	{
		tmp = 0;
		for (j = 0; j < BATSIZE; j++)
		{
			tmp = NBat.Seond1Bat[j][i] + tmp;
		}
		//NNode.Seond1[i] = 0.1;
		NWeight.Seond1[i] = tmp / norm;
	}
	for (i = 0; i < 200 * 50; i++)
	{
		tmp = 0;
		for (j = 0; j < BATSIZE; j++)
		{
			tmp = NBat.ThiredBat[j][i] + tmp;
		}
		//NNode.Seond1[i] = 0.1;
		NWeight.Thired[i] = tmp / norm;
	}
	for (i = 0; i < 10 * 50; i++)
	{
		tmp = 0;
		for (j = 0; j < BATSIZE; j++)
		{
			tmp = NBat.FourthBat[j][i] + tmp;
		}
		//NNode.Seond1[i] = 0.1;
		NWeight.Fourth[i] = tmp / norm;
	}



}



void TestByUsingExistingWeight()
{
	//读取模型权重文件
	printf("Test using existing weight!\n");
	char WeightWA[25] = "001_WA_F.csv";
	char WeightWB[25] = "001_WB_F.csv";
	char WeightWC[25] = "001_WC_F.csv";
	char WeightBAC[25] = "001_BA_F.csv";
	char WeightBBC[25] = "001_BB_F.csv";
	char WeightBCC[25] = "001_BC_F.csv";
	int count = 0;
	count=ReadWeightAndBiasFromFiles(WeightWA, NWeight.Seond1, 784, 200);
	count = ReadWeightAndBiasFromFiles(WeightWB, NWeight.Thired, 784, 200);
	count = ReadWeightAndBiasFromFiles(WeightWC, NWeight.Fourth, 784, 200);
	count = ReadWeightAndBiasFromFiles(WeightBAC, NNode.Seond1B, 784, 200);
	count = ReadWeightAndBiasFromFiles(WeightBBC, NNode.ThiredB, 784, 200);
	count = ReadWeightAndBiasFromFiles(WeightBCC, NNode.FourthB, 784, 200);
	
	//=========================准备训练图片和测试图片的label==================
	char filenameTrainLabel[25] = "TrainingLabel.txt";
	char filenameTeestLabeel[25] = "TestingLabel.txt";
	int TrainLabel[60000];
	int TestLabel[10000];
	TReadImageMNistLabel(filenameTrainLabel, TrainLabel);
	TReadImageMNistLabel(filenameTeestLabeel, TestLabel);

	//=================准备训练图片和测试图片=================
	double imageB[784] = { 0 };
	//ReadImage(filename);
	//image=ReadImageMNist(filename);
	char filenameO[25] = "TrainingImage0.txt";
	char filenameB[25] = "TrainingImage0.txt";
	char filenameOT[25] = "TestingImage0.txt";
	char filenameBT[25] = "TestingImage0.txt";
	int countImages = 60000;
	int testImages = 10000;
	int countImageIndex = 1;

	int Pre_Res;
	int T;
	int kID;
	int AccCount = 0;
	for (countImageIndex = 0; countImageIndex < testImages; countImageIndex++)
	{
		CopyFilename(filenameBT, filenameOT);
		nameMakerT(filenameBT, countImageIndex);
		//printf("obtain the file of: %s     \n", filenameB);
		TReadImageMNistC(filenameBT, imageB);
		/*
		for (kID = 0; kID < 784; kID++)
		{
			//printf("%d     %f\n", kID, imageB[kID]);
			printf("%d     %f\n", kID, NWeight.Seond1[kID]);
			
		}
		*/
		//==========forward propagation================
		initNode();
		FClayerForward(imageB, NNode.Seond1, NWeight.Seond1, 784, 200, NNode.Seond1B);
		FClayerForwardRelu(NNode.Seond1, 200);
		FClayerForward(NNode.Seond1, NNode.Thired, NWeight.Thired, 200, 50, NNode.ThiredB);
		FClayerForwardRelu(NNode.Thired, 50);
		FClayerForward(NNode.Thired, NNode.Fourth, NWeight.Fourth, 50, 10, NNode.FourthB);
		//==========calculate the loss deviation================
		//ONode.SumofExp = ExpSumToProb(NNode.Fourth, ONode.Exp , 10, ONode.Prob);
		Pre_Res = findMax(NNode.Fourth, 10);
		T = TestLabel[countImageIndex];//获取groundtruth
		
		if (Pre_Res == T)
		{
			AccCount++;
			//printf("=====%d   ---------%d\n", Pre_Res, T);
		}
		

	}
	double Acc = double(double(AccCount) / double(testImages));
	printf("The recognition accuracy is %f\n", Acc);


	printf("=====%d", count);
	while (1)
	{
		;
	}
}



//int main()
int mainBackup()
{

	//++++++++++++++++++++++++++++++++++++++++++++++++++++
	/*
	double K =  23.9876- 13.897 ;
	printf("%f",K*-1);
	while (1)
	{
		;
	}
	*/
	TestByUsingExistingWeight();
	return 0;
	//+++++++++++++++++++++++++++++++++++++++++++++++


	init();
	int ik;
	int jk;
	/*
	for (ik = 0; ik < 10; ik++)
	{
		printf("==%f    ", NNode.Seond1B[ik]);
	}
	printf("\n");
	*/
	/*============superparameters=======start=========*/
	double learningRate = 0.1;
	int T = 2;		//ground truth
	int epoch = 2;
	int batchSize = BATSIZE;		//batch size
	double DscoreBatch[32][10];		//batch score for gradient
	/*============superparameters=======end=========*/

	//NetWorkNode NNode;
	//NetWorkWeight NWeight;
	double imageC[784] = { 0 };
	double imageT[784] = { 0 };
	int Pre_Res = 0;
	
	//NNode.Seond1[0] = 5.2/7;
	//printf("========%f  ====\n", NNode.Seond1[0]);


	//=========================准备训练图片和测试图片的label==================
	char filenameTrainLabel[25] = "TrainingLabel.txt";
	char filenameTeestLabeel[25] = "TestingLabel.txt";
	int TrainLabel[60000];
	int TestLabel[10000];
	TReadImageMNistLabel(filenameTrainLabel, TrainLabel);
	TReadImageMNistLabel(filenameTeestLabeel, TestLabel);
	
	//=================准备训练图片和测试图片=================
	double imageB[784] = { 0 };
	//ReadImage(filename);
	//image=ReadImageMNist(filename);
	char filenameO[25] = "TrainingImage0.txt";
	char filenameB[25] = "TrainingImage0.txt";
	char filenameOT[25] = "TestingImage0.txt";
	char filenameBT[25] = "TestingImage0.txt";
	int countImages = 60000;
	int testImages = 10000;
	int countImageIndex = 1;
	//nameMaker(filenameB, countImageIndex);
	//printf("%s\n", filenameB);
	
	int digit;
	int flag = 9;
	int epiInd;


	/*文件读写测试，debug 没有关闭文件*/
	/*
	int Countline = 0;
	for (countImageIndex = 0; countImageIndex < countImages; countImageIndex++)
	{
		CopyFilename(filenameB, filenameO);
		nameMaker(filenameB, countImageIndex);
		//printf("obtain the file of: %s     \n", filenameB);
		Countline=TReadImageMNistC(filenameB, imageB);
		printf("compare filename is %s  target name is: %s \n", filenameO, filenameB);
		printf("countLine is %d\n", Countline);
		if (Countline == 0)
		{
			break;
		}
	}
	char tstfile [25]= "TrainingImage27.txt";
	Countline = TReadImageMNistC(tstfile, imageB);
	printf("compare filename is %s  target name is: %s \n", filenameO, filenameB);
	printf("countLine is %d\n", Countline);
	while (1)
	{
		;
	}
	*/
	/*=====================training====================================================*/
	int batIndex = 0;
	for (epiInd = 0; epiInd < epoch; epiInd++)
	{
		//for (countImageIndex = 0; countImageIndex < countImages; countImageIndex++)
		for (countImageIndex = 0; countImageIndex < countImages; )
		{
			initB();
			for (batIndex = 0; batIndex < batchSize; batIndex++)
			{

				if (countImageIndex % 1000 == 0)
				{
					printf("current training progress is: %d. \n, epoch is; %d", countImageIndex, epiInd);
				}
				/*============测试文件读取功能=========================*/
				/*
				if (countImageIndex >= flag && countImageIndex <= flag + 2)
				{
					if (countImageIndex == flag + 2)
					{
						flag = flag * 10 + 9;
					}
					digit = DigitNumber(countImageIndex);
					CopyFilename(filenameB, filenameO);
					nameMaker(filenameB, countImageIndex);
					printf("=====%d=====>>>>%s+++++++++++++++%d; \n", countImageIndex, filenameB, digit);
					//filenameB = "TrainingImage0.txt";
				}
				//digit = DigitNumber(countImageIndex);
				//printf("=====%d=====>>>>%s+++++++++++++++%d; \n", countImageIndex, filenameB, digit);
				*/
				/*================读取文件====================*/
				CopyFilename(filenameB, filenameO);
				nameMaker(filenameB, countImageIndex);
				//printf("obtain the file of: %s     \n", filenameB);
				TReadImageMNistC(filenameB, imageB);
				initNode();
				//==========forward propagation================
				FClayerForward(imageB, NNode.Seond1, NWeight.Seond1, 784, 200, NNode.Seond1B);
				FClayerForwardRelu(NNode.Seond1, 200);
				FClayerForward(NNode.Seond1, NNode.Thired, NWeight.Thired, 200, 50, NNode.ThiredB);
				FClayerForwardRelu(NNode.Thired, 50);
				FClayerForward(NNode.Thired, NNode.Fourth, NWeight.Fourth, 50, 10, NNode.FourthB);
				/*
				for (ik = 0; ik < 10; ik++)
				{
					printf("==%f    ", NNode.Seond1B[ik]);
				}
				printf("\n");
				*/
				//==========calculate the loss deviation================
				//ONode.SumofExp = ExpSumToProb(NNode.Fourth, ONode.Exp , 10, ONode.Prob);
				T = TrainLabel[countImageIndex];//获取groundtruth
				ONode.SumofExp = ExpSumToProbToLoss(NNode.Fourth, ONode.Exp, 10, ONode.Prob, ONode.Loss, T);
				Pre_Res = findMax(NNode.Fourth, 10);
				

				//================backward propagation=====================
			
				//DWC = np.transpose(np.dot(np.transpose(Dscores), HB))
				FClayerBackward(BNode.DFourth, ONode.Loss, 50, 10, NNode.Thired, BNode.Thired, NWeight.Fourth, BNode.Db4);
				FClayerBackwardUpdate(BNode.DFourth, BNode.Db4, 10 * 50, 10, learningRate, NBat.FourthBat[batIndex], NBat.FourthBBat[batIndex]);

				FClayerBackward(BNode.DThired, BNode.Thired, 200, 50, NNode.Seond1, BNode.Seond1, NWeight.Thired, BNode.Db3);
				//FClayerBackwardUpdate(BNode.DThired, BNode.Db3, 200 * 50, 50, learningRate, NWeight.Thired, NNode.ThiredB);
				FClayerBackwardUpdate(BNode.DThired, BNode.Db3, 200 * 50, 50, learningRate, NBat.ThiredBat[batIndex], NBat.ThiredBBat[batIndex]);

				FClayerBackward(BNode.DSeond1, BNode.Seond1, 784, 200, imageB, imageT, NWeight.Seond1, BNode.Db2);
				//FClayerBackwardUpdate(BNode.DSeond1, BNode.Db2, 784 * 200, 200, learningRate, NWeight.Seond1, NNode.Seond1B);
				FClayerBackwardUpdate(BNode.DSeond1, BNode.Db2, 784 * 200, 200, learningRate, NBat.Seond1Bat[batIndex], NBat.Seond1BBat[batIndex]);

				//==============Total index ====================================
				countImageIndex++;
			}
			
			//=======batch sum=====to weight========================
			BatchSum();

			//================backward propagation=====================
			/*
			//DWC = np.transpose(np.dot(np.transpose(Dscores), HB))
			FClayerBackward(BNode.DFourth, ONode.Loss, 50, 10, NNode.Thired, BNode.Thired, NWeight.Fourth, BNode.Db4);
			FClayerBackwardUpdate(BNode.DFourth, BNode.Db4, 10 * 50, 10, learningRate, NWeight.Fourth, NNode.FourthB);

			FClayerBackward(BNode.DThired, BNode.Thired, 200, 50, NNode.Seond1, BNode.Seond1, NWeight.Thired, BNode.Db3);
			FClayerBackwardUpdate(BNode.DThired, BNode.Db3, 200 * 50, 50, learningRate, NWeight.Thired, NNode.ThiredB);

			FClayerBackward(BNode.DSeond1, BNode.Seond1, 784, 200, imageC, imageT, NWeight.Seond1, BNode.Db2);
			FClayerBackwardUpdate(BNode.DSeond1, BNode.Db2, 784 * 200, 200, learningRate, NWeight.Seond1, NNode.Seond1B);
			*/
			/*
			for (ik = 0; ik < 10; ik++)
			{
				printf("==%f    ", NNode.Seond1B[ik]);
			}
			printf("\n");
			*/

		}
	}
	
	/*=====================testing====================================================*/

	int AccCount = 0;
	for (countImageIndex = 0; countImageIndex < testImages; countImageIndex++)
	{
		CopyFilename(filenameBT, filenameOT);
		nameMakerT(filenameBT, countImageIndex);
		//printf("obtain the file of: %s     \n", filenameB);
		TReadImageMNistC(filenameBT, imageB);

		//==========forward propagation================
		FClayerForward(imageB, NNode.Seond1, NWeight.Seond1, 784, 200, NNode.Seond1B);
		FClayerForwardRelu(NNode.Seond1, 200);
		FClayerForward(NNode.Seond1, NNode.Thired, NWeight.Thired, 200, 50, NNode.ThiredB);
		FClayerForwardRelu(NNode.Thired, 50);
		FClayerForward(NNode.Thired, NNode.Fourth, NWeight.Fourth, 50, 10, NNode.FourthB);
		//==========calculate the loss deviation================
		//ONode.SumofExp = ExpSumToProb(NNode.Fourth, ONode.Exp , 10, ONode.Prob);
		Pre_Res = findMax(NNode.Fourth, 10);
		T = TestLabel[countImageIndex];//获取groundtruth
		if (Pre_Res == T)
		{
			AccCount++  ;
			printf("=====%d   ---------%d", Pre_Res, T);
		}
		
		
	}
	double Acc = double (double(AccCount) / double(testImages));
	printf("The recognition accuracy is %f\n", Acc);

	/*===================================back up for 前向传播后向传播
	//printf("%s\n", filenameB);
	//TReadImageMNistC(filenameB, imageB);

	//=================read training files==(main loop for training)===========================

	//=====================if you want batch================================

	//==========forward propagation================
	FClayerForward(imageC, NNode.Seond1, NWeight.Seond1, 784, 200, NNode.Seond1B);
	FClayerForwardRelu(NNode.Seond1, 200);
	FClayerForward(NNode.Seond1, NNode.Thired, NWeight.Thired, 200, 50, NNode.ThiredB);
	FClayerForwardRelu(NNode.Thired, 50);
	FClayerForward(NNode.Thired, NNode.Fourth, NWeight.Fourth, 50, 10, NNode.FourthB);
	//==========calculate the loss deviation================
	//ONode.SumofExp = ExpSumToProb(NNode.Fourth, ONode.Exp , 10, ONode.Prob);
	ONode.SumofExp = ExpSumToProbToLoss(NNode.Fourth, ONode.Exp, 10, ONode.Prob, ONode.Loss,T);
	Pre_Res = findMax(ONode.Prob, 10);
	//================backward propagation=====================
	//DWC = np.transpose(np.dot(np.transpose(Dscores), HB))
	FClayerBackward(BNode.DFourth, ONode.Loss, 50, 10, NNode.Thired, BNode.Thired, NWeight.Fourth, BNode.Db4);
	FClayerBackwardUpdate(BNode.DFourth, BNode.Db4, 10 * 50, 10, learningRate, NWeight.Fourth, NNode.FourthB);

	FClayerBackward(BNode.DThired, BNode.Thired, 200, 50, NNode.Seond1, BNode.Seond1, NWeight.Thired, BNode.Db3);
	FClayerBackwardUpdate(BNode.DThired, BNode.Db3, 200 * 50, 50, learningRate, NWeight.Thired, NNode.ThiredB);

	FClayerBackward(BNode.DSeond1, BNode.Seond1, 784, 200, imageC, imageT, NWeight.Seond1, BNode.Db2);
	FClayerBackwardUpdate(BNode.DSeond1, BNode.Db2, 784 * 200, 200, learningRate, NWeight.Seond1, NNode.Seond1B);
		//DBC = np.sum(Dscores, axis = 0)         


	//=================read testing files==(main loop for testing)===========================

	printf("========%d  ====\n", Pre_Res);

	*/


	while (1)
	{
		;
	}
	return 1;

	/*==========================test load data============================*/
	char filename[]= "12345";
	//filename = "12345";
	printf("working\n");
	printf("input your number \n");
	int x=0;
	scanf("%d", &x);
	//double save[x] = { 0 };
	//array = (int*)calloc(n1, sizeof(int));
	testWork();
	double * image;
	//double imageB[784] = {0};
	//ReadImage(filename);
	//image=ReadImageMNist(filename);
	ReadImageMNistC(filename, imageB);
	int i = 0;
	printf("============================================================\n");
	
	for (i = 0; i < 784; i++)
	{
		printf("%f", imageB[i]);
		printf("                ");
		if ((i + 1) % 6 == 0)
		{
			printf("\n");
		}
	}
	
	while (1)
	{
		;
	}
}