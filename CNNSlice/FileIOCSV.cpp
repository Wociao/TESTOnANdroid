#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  

using namespace std;


void WriteTOCSV()
{
	ofstream outFile;
	outFile.open("001data.csv", ios::out); // 打开模式可省略  
	outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
	outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
	outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
	outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
	outFile.close();
}

/*
001V1ResultDefnceV1 第一次进行defence 比例是被干扰的2%
001V1ResultDefnceV1A2.............................3%

001V1ResultDefnceV2 第二次进行defence，每一次的干扰量下测试从10% 到90% 的比例。同时针对random版，测试1%到9% 的结果

001V1ResultDefnceAfterAttackV1 先attack，第一次进行defence, 比例是被干扰的3%

002V1ResultDefnceAfterAttackUsingOurMethodV2_Dynamic 测试我们的方法

002V1ResultDefnceAfterAttackUsingOurMethodV2_DynamicV6: dynamic 20% 20% 60%

002V2AttackOnAllLayersDefV1 attack on all layers with defence  20% 20% 60%
002V2AttackOnAllLayersDefV2 attack on all layers with defence  dixed size

*/
void WriteToCSV(double *Result, int NO)
{
	ofstream outFile;
	outFile.open("Newresult.csv", ios::out); // 打开模式可省略  
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
	outFile.open(FileName, ios::out); // 打开模式可省略  
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