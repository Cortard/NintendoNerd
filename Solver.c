#include "Solver.h"

void ReadableForward(u8 input[32], u8 output[32], const u8 confusion[512], const u32 diffusion[32])
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

