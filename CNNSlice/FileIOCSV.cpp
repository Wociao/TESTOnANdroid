#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  

using namespace std;


void WriteTOCSV()
{
	ofstream outFile;
	outFile.open("001data.csv", ios::out); // ��ģʽ��ʡ��  
	outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
	outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
	outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
	outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
	outFile.close();
}

/*
001V1ResultDefnceV1 ��һ�ν���defence �����Ǳ����ŵ�2%
001V1ResultDefnceV1A2.............................3%

001V1ResultDefnceV2 �ڶ��ν���defence��ÿһ�εĸ������²��Դ�10% ��90% �ı�����ͬʱ���random�棬����1%��9% �Ľ��

001V1ResultDefnceAfterAttackV1 ��attack����һ�ν���defence, �����Ǳ����ŵ�3%

002V1ResultDefnceAfterAttackUsingOurMethodV2_Dynamic �������ǵķ���

002V1ResultDefnceAfterAttackUsingOurMethodV2_DynamicV6: dynamic 20% 20% 60%

002V2AttackOnAllLayersDefV1 attack on all layers with defence  20% 20% 60%
002V2AttackOnAllLayersDefV2 attack on all layers with defence  dixed size

*/
void WriteToCSV(double *Result, int NO)
{
	ofstream outFile;
	outFile.open("Newresult.csv", ios::out); // ��ģʽ��ʡ��  
	for (int i = 0; i < NO;i++)
	{
		outFile << NO << ',' << Result[i]  << endl;
	}
	//outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
	//outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
	//outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
	//outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
	outFile.close();

}


void WriteToCSVB(double *Result, int NO, char * FileName)
{
	ofstream outFile;
	outFile.open(FileName, ios::out); // ��ģʽ��ʡ��  
	for (int i = 0; i < NO; i++)
	{
		outFile << Result[i] << endl;
	}
	//outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
	//outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
	//outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
	//outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
	outFile.close();

}