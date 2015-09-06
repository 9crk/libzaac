
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "faac.h"


faacEncHandle aac_init(int nSampleRate, int nChannels, int nBit, char** pbPCMBuffer, char** pbAACBuffer, unsigned long* maxOut, unsigned long* maxIn)// it will malloc mem for you
{

	faacEncHandle hEncoder;
	unsigned long nInputSamples = 0; //输入样本数
	faacEncConfigurationPtr pConfiguration;//aac设置指针 
	int nRet;
	//1.0
	hEncoder = faacEncOpen(nSampleRate, nChannels, &nInputSamples, &(*maxOut));
	*maxIn=nInputSamples*nBit/8;
	printf("nInputSamples:%ld nMaxInputBytes:%ld nMaxOutputBytes:%ld\n", nInputSamples, *maxIn,*maxOut);
    if(hEncoder == NULL)
    {
        printf("[ERROR] Failed to call faacEncOpen()\n");
        return NULL;
    }
	*pbPCMBuffer = (char*)malloc(*maxIn);
    *pbAACBuffer = (char*)malloc(*maxOut);
	//2.0
	pConfiguration = faacEncGetCurrentConfiguration(hEncoder);//获取配置结构指针
    pConfiguration->inputFormat = FAAC_INPUT_16BIT;
	pConfiguration->outputFormat=1;
	pConfiguration->useTns=1;//TRUE
	pConfiguration->useLfe=0;//FALSE
	pConfiguration->aacObjectType=LOW;
	pConfiguration->shortctl=SHORTCTL_NORMAL;
	pConfiguration->quantqual=100;
	pConfiguration->bandWidth=0;
	pConfiguration->bitRate=0;
	nRet = faacEncSetConfiguration(hEncoder, pConfiguration);
	return hEncoder;
}
int aac_encode(faacEncHandle hEncoder,int nBytes, int nBit, char* pbPCMBuffer, char* pbAACBuffer, int maxOut)//return bytes of aac data
{
	int nInputSamples, nRet;
	nInputSamples = nBytes/ (nBit / 8);
    nRet = faacEncEncode(hEncoder, (int*) pbPCMBuffer, nInputSamples, (unsigned char*)pbAACBuffer, maxOut);
	if (nRet<1){
		return 0;
	}
	return nRet;
}
int aac_close(char* pbPCMBuffer, char* pbAACBuffer)
{
	free(pbPCMBuffer);
	free(pbAACBuffer);
}
