#include <stdio.h>
#include <stdlib.h>

void testWork()
{
	printf("FileIO is working");

}


double ReadImage(char * filename)
{
	int a[10] = { 0 };
	FILE *fpRead = fopen("test.txt", "r");
	if (fpRead == NULL)
	{
		return 0;
	}
	for (int i = 0; i < 10; i++)
	{
		fscanf(fpRead, "%d ", &a[i]);
		printf("%d ", a[i]);
	}
	return 0.0;
}

double * ReadImageMNistB(char * filename)
{
	int a[10] = { 0 };
	double Image[784] = { 0.0 };
	FILE *fpRead = fopen("test.txt", "r");
	if (fpRead == NULL)
	{
		return 0;
	}
	char ch;
	int count_I = 0;
	int flagA = 0;	//小数点前那一位，‘a’之后。
	int flagB = 0;		//小数点后， 等待‘a’出现
	int countbit = 1;
	while ((ch = fgetc(fpRead)) != EOF)
	{
		//========第一次尝试==================================
		/*
		if (flagA == 0)
		{
			//一开始就保存小数点前一位。已知最大值不会大于1.0，所以保存1或0
			Image[count_I] = ch - '0';
			flagA = 1;
			countbit = countbit * 10;
		}
		if (ch == ',')
		{
			continue;
		}
		if (flagA == 1 && flagB == 0 && ch != 'a')
		{
			//进入小数点后一位到a之前。标志就是flagA == 1 && flagB == 0，用ch != 'a'检测是否结束
			//得到结果除以countbit取得对应小数位的值，加入原值
			Image[count_I] = Image[count_I] + (ch - '0')/ countbit;
			countbit = countbit * 10;
		}
		if (ch == 'a')
		{
			flagA = 0;
			count_I++;
			flagB = 0;
			countbit = 1;
		}
		//fscanf(fpRead, "%d ", &a[i]);
		printf("%c ", ch);
		*/
		//========第二次尝试==================================
		switch (flagA)
		{
		case 0: 
		{
			Image[count_I] = ch - '0';
			flagA = 1;
			countbit = countbit * 10;
			break;
		}
		case 1:
		{
			if (ch == '.')
			{
				flagA = 2;
				//printf("=----------------------------=%d\n", count_I);
			}
			break;
		}
		case 2:
		{
			if (ch == 'a')
			{
				printf("=----------------------------=%d +++++++ %f\n", count_I, Image[count_I]);
				flagA = 0;
				count_I++;
				//printf("=----------------------------=%d +++++++ %f\n", count_I, Image[count_I]);
				flagB = 0;
				countbit = 1;
				//printf("\n");
			}
			else
			{
				Image[count_I] = Image[count_I] +( (ch - '0') / countbit);
				//printf("%d", ch - '0');
				countbit = countbit * 10;
			}
			break;
		}
		default:
			break;
		}
		
	}

	printf("====================%d \n", count_I);
	return Image;
}

double * ReadImageMNist(char * filename)
{
	int a[10] = { 0 };
	double Image[784] = { 0.0 };
	FILE *fpRead = fopen("test.txt", "r");
	if (fpRead == NULL)
	{
		return 0;
	}
	char ch;
	int count_I = 0;
	int flagA = 0;	//小数点前那一位，‘a’之后。
	int flagB = 0;		//小数点后， 等待‘a’出现
	int countbit = 1;
	while ((ch = fgetc(fpRead)) != EOF)
	{
		//printf("%c", ch);
		;
	}
	for (int i = 0; i < 784; i++)
	{
		Image[i] = i / 784;
		//printf("   %f  ", Image[i]);
	}
	for (int i = 0; i < 784; i++)
	{
		//Image[i] = i / 784;
		printf("   %f  ", Image[i]);
	}

	printf("====================%d \n", count_I);
	return Image;
}


int ReadImageMNistC(char * filename, double * imageB)
{

	int a[10] = { 0 };
	char NUmber[50] = {'0'};
	double Image[784] = { 0.0 };
	FILE *fpRead = fopen("test.txt", "r");
	if (fpRead == NULL)
	{
		return 0;
	}
	char ch;
	int count_I = 0;
	int count_N = 0;
	int flagA = 0;	//小数点前那一位，‘a’之后。
	int flagB = 0;		//小数点后， 等待‘a’出现
	int countbit = 1;
	while ((ch = fgetc(fpRead)) != EOF)
	{
		NUmber[count_I] = ch;
		count_I++;
		if (ch == 'a')
		{
			NUmber[count_I-1] = '\0'; 
			imageB[count_N] = atof(NUmber);
			count_N++;
			count_I = 0;
			printf("%s \n", NUmber);
		}
		
	}
	/*
	for (int i = 0; i < 784; i++)
	{
		imageB[i] = (double) i/2 ;
		//printf("   %f  ", Image[i]);
	}
	for (int i = 0; i < 784; i++)
	{
		//Image[i] = i / 784;
		printf("   %f  ", imageB[i]);
	}*/
	return 0;
	
}


int TReadImageMNistC(char * filename, double * imageB)
{

	int a[10] = { 0 };
	char NUmber[50] = { '0' };
	double Image[784] = { 0.0 };
	FILE *fpRead = fopen(filename, "r");
	if (fpRead == NULL)
	{
		printf(" file not found-----> %s\n", filename);
		printf("NO file found\n");
		return 0;
	}
	char ch;
	int count_I = 0;
	int count_N = 0;
	int flagA = 0;	//小数点前那一位，‘a’之后。
	int flagB = 0;		//小数点后， 等待‘a’出现
	int countbit =0;
	while ((ch = fgetc(fpRead)) != EOF)
	{
		NUmber[count_I] = ch;
		count_I++;
		if (ch == 'a')
		{
			countbit++;
			NUmber[count_I - 1] = '\0';
			imageB[count_N] = atof(NUmber);
			count_N++;
			count_I = 0;
			//printf("%s \n", NUmber);
		}

	}
	fclose(fpRead);
	/*
	for (int i = 0; i < 784; i++)
	{
		imageB[i] = (double) i/2 ;
		//printf("   %f  ", Image[i]);
	}
	for (int i = 0; i < 784; i++)
	{
		//Image[i] = i / 784;
		printf("   %f  ", imageB[i]);
	}*/
	return countbit;

}


int TReadImageMNistLabel(char * filename, int * label)
{

	int a[10] = { 0 };
	char NUmber[50] = { '0' };
	double Image[784] = { 0.0 };
	FILE *fpRead = fopen(filename, "r");
	if (fpRead == NULL)
	{
		printf("NO file found\n");
		return 0;
	}
	char ch;
	int count_I = 0;
	int count_N = 0;
	int flagA = 0;	//小数点前那一位，‘a’之后。
	int flagB = 0;		//小数点后， 等待‘a’出现
	int countbit = 1;
	int Result = 0;
	while ((ch = fgetc(fpRead)) != EOF)
	{
		if (ch == 'a')
		{
			continue;
		}
		else 
		{
			Result = ch - '0';
			//printf("----------%d  \n", Result);
			label[count_I] = Result;
			count_I++;
		}
		
		/*
		NUmber[count_I] = ch;
		count_I++;
		if (ch == 'a')
		{
			NUmber[count_I - 1] = '\0';
			label[count_N] = atof(NUmber);
			count_N++;
			count_I = 0;
			//printf("%s \n", NUmber);
		}
		*/

	}
	/*
	for (int i = 0; i < 784; i++)
	{
		imageB[i] = (double) i/2 ;
		//printf("   %f  ", Image[i]);
	}
	for (int i = 0; i < 784; i++)
	{
		//Image[i] = i / 784;
		printf("   %f  ", imageB[i]);
	}*/
	return count_I;

}

double CalculateNumber(char * Number)
{
	double Rees = 0.0;
	double Flag = 1;
	int Power = 0;
	int count = 0;
	double DecCount = 1.0;
	if (Number[0] == '1'&& Number[1] == '\0')
	{
		return 1;
	}
	if (Number[0] == '0' && Number[1]=='\0')
	{
		return 0.0;
	}
	if (Number[0] == '-')
	{
		Flag = -1;
		count++;
	}
	
	while (Number[count] != '.')
	{
		Rees = Rees * 10 + Number[count] - '0';
		count++;
	}
	if (Number[count] == '.')
	{
		count++;
	}
	while (Number[count] != '\0')
	{
		//if (Number[count] != 'E' || Number[count] != 'e')
		
		if (Number[count] == 'e')
		{
			Power = (Number[count+3] - '0');
			//printf("Power is %d\n", Power);
			break;
		}
		else
		{
			
			DecCount = DecCount / 10.0;
			Rees = Rees + (Number[count] - '0')* DecCount;
			count++;
			
		}
		
		
	}
	int j = 0;
	for (j = 0; j < Power; j++)
	{
		Rees = Rees / 10;
	}
	return Rees* Flag;
}


int ReadWeightAndBiasFromFiles(char * filename, double * buf, int demA, int demB)
{

	int a[10] = { 0 };
	char NUmber[50] = { '\0' };
	double Image[784] = { 0.0 };
	FILE *fpRead = fopen(filename, "r");
	if (fpRead == NULL)
	{
		printf("NO file found\n");
		return 0;
	}
	char ch;
	int count_I = 0;
	int count_N = 0;
	int flagA = 0;	//小数点前那一位，‘a’之后。
	int flagB = 0;		//小数点后， 等待‘a’出现
	int countbit = 1;
	int Result = 0;
	while ((ch = fgetc(fpRead)) != EOF)
	{
		NUmber[count_N] = ch;
		count_N++;
		if (ch == ',' || ch =='\n')
		{
			NUmber[count_N-1] = '\0';
			buf[count_I] = CalculateNumber(NUmber);
			
			//printf("======%s=====\n", NUmber);
			/*
			if (count_I < 10)
			{
				printf("======%s=====\n", NUmber);
				printf("======%.50lf=====\n", buf[count_I]);
			}
			*/
			count_I++;
			count_N = 0;
			
		}
		//printf("%c", ch);
		/*
		if (ch == 'a')
		{
			continue;
		}
		else
		{
			Result = ch - '0';
			//printf("----------%d  \n", Result);
			buf[count_I] = Result;
			count_I++;
		}
		*/
		/*
		NUmber[count_I] = ch;
		count_I++;
		if (ch == 'a')
		{
			NUmber[count_I - 1] = '\0';
			label[count_N] = atof(NUmber);
			count_N++;
			count_I = 0;
			//printf("%s \n", NUmber);
		}
		*/

	}
	/*
	for (int i = 0; i < 784; i++)
	{
		imageB[i] = (double) i/2 ;
		//printf("   %f  ", Image[i]);
	}
	for (int i = 0; i < 784; i++)
	{
		//Image[i] = i / 784;
		printf("   %f  ", imageB[i]);
	}*/
	return count_I;

}

