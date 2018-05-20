//
// Created by joela on 2/10/18.
//
#include "BinChromosome.h"

int main(int argc, char *argv[]) {
    int varLength;
    double min, max;
    int chromLength;
    varLength = 10;
    min = -100;
    max = 100;
    chromLength = 16;
    BinChromosome chrom[10];
    for (int i = 0; i < 1; i++) {
        chrom[i] = BinChromosome(varLength, min, max, chromLength);
        for (int j = 0; j < 10; j++) {
            printf("\nBinChromosome[%d] var[%d] = %f ", i, j, chrom->getvar(j));
        }
    }
}
