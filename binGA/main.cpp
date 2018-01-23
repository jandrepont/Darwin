//
// Created by joela on 1/4/18.
//
#include <iostream>
#include "GA.h"
#include "Chromosome.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <iostream>
#include <json-c/json.h>
#include <curl/curl.h>
#include <pthread.h>


int main(int argc, char *argv[]){

    /*
     * set up dyn GA
     */
    int cross, mute, chroms, elites, vars;
    float min, max;
    printf("chroms = ");
    scanf("%d", &chroms);
    printf("cross = ");
    scanf("%d", &cross);
    printf("mutation = ");
    scanf("%d", &mute);
    printf("elites = ");
    scanf("%d", &elites);
    printf("min = ");
    scanf("%f", &min);
    printf("max = ");
    scanf("%f", &max);
    printf("vars = ");
    scanf("%d", &vars);
    GA *gen;
    gen = new GA(cross, mute, chroms, elites, vars, min, max);
    int popNum = 0;
    gen->calcfitness();
    gen->sort(0, gen->get_nchroms());
    for(int epoch = 0; epoch < 100; epoch++){
        popNum = ((popNum+1)%2);
        gen->setpopNum(popNum);
        gen->preserveElites();
        gen->crossover();
        gen->createNew();
        gen->mutate();
        gen->calcfitness();
        gen->sort(0, gen->get_nchroms());
        printf("epoch[%d] chrom[%d] fit = %f\n",epoch, gen->pop[popNum][0].getFitness());

//        for(int j = 0; j < 5; j++){
//            for(int k = 0; k < vars; k++){
//                printf("epoch[%d] chrom[%d].var[%d] = %f\n",epoch, j, k, gen->pop[popNum][j].getvar(k));
//
//            }
//        }
    }

    delete gen;
    return 0;
}