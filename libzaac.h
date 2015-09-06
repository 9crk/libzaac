#ifndef LIBZAAC_H
#define LIBZAAC_H

#include "faac.h"
extern int gMaxRead;
faacEncHandle aac_init(int nSampleRate, int nChannels, int nBit, char** pbPCMBuffer, char** pbAACBuffer, long* maxOut, long* maxIn);

int aac_encode(faacEncHandle hEncoder,int nBytes, int nBit, char* pbPCMBuffer, char* pbAACBuffer, int maxOut);

int aac_close(char* pbPCMBuffer, char* pbAACBuffer);

#endif  
/*  example:
int main(int argc, char* argv[])
{
	FILE* fin = fopen(argv[1],"rb");
	FILE* fout = fopen(argv[2],"wb");
	char* bufferIn;
	char* bufferOut;
	int ret;
	int cnt;
	aac_init(44100,2,16,&bufferIn, &bufferOut);
	while(1){
		ret = fread(bufferIn,1,gMaxRead, fin);
		if(ret <=0)break;
		cnt = aac_encode(ret, bufferIn, bufferOut);
		fwrite(bufferOut,1,cnt,fout);
	}
	aac_close( bufferIn, bufferOut);
	fclose(fin);
	fclose(fout);
}
*/
