/*
文件读写。主要是读取训练数据
*/


void testWork();
#pragma once
double ReadImage(char * filename);
double * ReadImageMNist(char * filename);
double * ReadImageMNistB(char * filename);
int ReadImageMNistC(char * filename, double * imageB);
int TReadImageMNistC(char * filename, double * imageB);
int TReadImageMNistLabel(char * filename, int * label);
int ReadWeightAndBiasFromFiles(char * filename, double * buf, int demA, int demB);
double CalculateNumber(char * Number);