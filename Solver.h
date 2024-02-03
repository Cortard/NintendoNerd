#ifndef NINTENDONERD_SOLVER_H
#define NINTENDONERD_SOLVER_H

typedef unsigned char u8;
typedef unsigned int u32;

void readableForward(u8 input[32], u8 output[32], const u8 confusion[512], const u32 diffusion[32]);

void confusionAnalyse(const u8 confusion[512]);

#endif //NINTENDONERD_SOLVER_H
