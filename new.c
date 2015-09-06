#include"libzaac.h"
#include<stdio.h>
#include"pthread.h"

pthread_t pid[4];
typedef struct argStruct{
char fin[20];
char fout[20];
}argStruct;
argStruct arg1={
"audio_chn0.pcm",
"audio_chn0.aac"
};
argStruct arg2={
"audio_chn1.pcm",
"audio_chn1.aac"
};
argStruct arg3={
"audio_chn2.pcm",
"audio_chn2.aac"
};
argStruct arg4={
"audio_chn3.pcm",
"audio_chn3.aac"
};

void* record(void *arg){
	struct argStruct *pArg = (struct argStruct*)arg;
	FILE* fin = fopen(pArg->fin,"rb");
	FILE* fout = fopen(pArg->fout,"wb");
	int ret;
	int cnt;
	char* bufferIn;
	char* bufferOut;
	faacEncHandle handle;
	unsigned long maxOut=1, maxIn=1;
	handle = aac_init(44100,2,16,&bufferIn, &bufferOut, &maxOut, &maxIn);
	printf("record---%ld %ld-----\n", maxOut, maxIn);
	while(1){
		ret = fread(bufferIn,1,maxIn, fin);
		printf("read %d |||||||||\n",ret);
		if(ret <=0)break;
		cnt = aac_encode(handle,ret,16,bufferIn, bufferOut,maxOut);
		fwrite(bufferOut,1,cnt,fout);
	}
	aac_close( bufferIn, bufferOut);
	fclose(fin);
	fclose(fout);
}

int main(int argc, char* argv[])
{
printf("go!\n");
pthread_create(&pid[0],0,record,&arg1);
pthread_create(&pid[1],0,record,&arg2);
pthread_create(&pid[2],0,record,&arg3);
pthread_create(&pid[3],0,record,&arg4);
sleep(10);
printf("main done!\n");
}

