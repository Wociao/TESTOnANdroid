#pragma once
int AddingNoise(double * buf, int number, int type, int TotLen);
int AddingNoiseDef(double * buf, int number, int type, int TotLen, int DefLen);
int IsInTheArray(int Ind, int lenDef);
int AddingNoiseOurDef(double * buf, int number, int type, int demA, int demB, int ProLen, int DefLen);
int AddingNoise_def_flat_V1(double * buf, int number, int type, int TotLen, int * ProInd, int Len, int FlatFactor,int Dem, int NM, int NP);
int AddingNoise_def_flat_V2(double * buf, int number, int type, int TotLen, int * ProInd, int Len, int FlatFactor, int Dem, int NM, int NP);
bool IfInTheList(int target, int * NameList, int NamelistLen);