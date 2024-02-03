#include <memory.h>
#include <stdio.h>
#include "Solver.h"

void readableForward(u8 input[32], u8 output[32], const u8 confusion[512], const u32 diffusion[32])
{
    //just 32 time the process, no use of the iterator
    for(u32 i=0;i<256;i++)
    {
        //output equal confusion at input
        //only first half of confusion is used (u8<256)
        for(u8 j=0;j<32;j++)
        {
            output[j]=confusion[input[j]];
            input[j]=0;
        }

        //input equal xor of output according diffusion
        for(u8 j=0;j<32;j++)
            for(u8 k=0;k<32;k++)
                input[j]^= output[k] * ((diffusion[j] >> k) & 1);
    }
    //output i equal xor of confusion at input 2i and at (input 2i+1) + 256
    //left element in first confusion part and right in second part
    for(u8 i=0;i<16;i++)
        output[i]= confusion[input[i * 2]] ^ confusion[input[i * 2 + 1] + 256];
}

//XOR properties :
//a^a=0 and a^0=a => a^b^a=b
//a^b=b^a
//a^(b^c)=(a^b)^c

void confusionAnalyse(const u8 confusion[512]){
    u8 nbFoundLeft[256];
    memset(nbFoundLeft,0, sizeof(nbFoundLeft));
    u8 nbFoundRight[256];
    memset(nbFoundRight,0, sizeof(nbFoundRight));

    for(u32 i=0;i<512;++i){
        if(i<256)
            ++nbFoundLeft[confusion[i]];
        else
            ++nbFoundRight[confusion[i]];
    }

    u8 missingLeft=0;
    u8 missingRight=0;
    for(u32 i=0;i<256;++i){
        if(nbFoundLeft[i]==0)
            ++missingLeft;
        if(nbFoundRight[i]==0)
            ++missingRight;
    }
    printf("Missing %d left and %d right\n",missingLeft,missingRight);

    u8 maxLeft=nbFoundLeft[0];
    u8 maxRight=nbFoundRight[0];
    for(u32 i=1;i<256;++i){
        if(nbFoundLeft[i]>maxLeft)
            maxLeft=nbFoundLeft[i];
        if(nbFoundRight[i]>maxRight)
            maxRight=nbFoundRight[i];
    }
    printf("Max appearing %d left and %d right\n",maxLeft,maxRight);

    u8 totalMax=nbFoundLeft[0]+nbFoundRight[0];
    u8 totalMaxValue=0;
    for(u32 i=1;i<256;++i){
        if(nbFoundLeft[i]+nbFoundRight[i]>totalMax){
            totalMax=nbFoundLeft[i]+nbFoundRight[i];
            totalMaxValue=i;
        }
    }
    printf("Max appearing total %d with value %d(%x)\n",totalMax,totalMaxValue,totalMaxValue);
}

//pre computation
PosInConfusion confusionReversed[256];
void reverseConfusion(const u8 confusion[512]){
    memset(confusionReversed,0, sizeof(confusionReversed));
    for(u32 i=0;i<512;++i){
        if(i<256)
            ++confusionReversed[confusion[i]].posLeft[ confusionReversed[confusion[i]].nbLeft++ ];
        else
            ++confusionReversed[confusion[i]].posRight[ confusionReversed[confusion[i]].nbRight++ ];
    }
}
