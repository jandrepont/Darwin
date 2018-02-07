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
#include <malloc.h>

void cec14_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

int main(int argc, char *argv[]){


    /*
     * set up dyn GA
     */
    int ncross, nmute, nchroms, nelites, nvars;
    float min, max;
    printf("chroms = ");
    scanf("%d", &nchroms);
    printf("cross = ");
    scanf("%d", &ncross);
    printf("mutation = ");
    scanf("%d", &nmute);
    printf("elites = ");
    scanf("%d", &nelites);
    printf("min = ");
    scanf("%f", &min);
    printf("max = ");
    scanf("%f", &max);
    printf("vars = ");
    scanf("%d", &nvars);

    int i,j,k,n,m,func_num;
    double *f,*x,*y;

    x=(double *)malloc(nchroms*nvars*sizeof(double));
    f=(double *)malloc(sizeof(double)  *  nchroms);




    GA *gen;
    gen = new GA(ncross, nmute, nchroms, nelites, nvars, min, max);
    int popNum = 0;

    gen->returnInput(x);
//    for(int i = 0; i < nchroms*nvars; i++){
//        printf("\n%f\n", x[i]);
//    }

    cec14_test_func(x, f,nvars,nchroms,1);
    gen->calcfitness(f);
    gen->sort(0, nchroms);
//    for(int i = 0; i < nchroms; i++){
//        printf("chrom[%d] fitness = %f\n",i, gen->pop[popNum][i].getFitness());
//    }

    for(int epoch = 0; epoch < 2000; epoch++){
        popNum = ((popNum+1)%2);
        gen->setpopNum(popNum);
        gen->preserveElites();
        gen->crossover();
        gen->createNew();
        gen->mutate();
        gen->returnInput(x);
        cec14_test_func(x, f,nvars,nchroms,1);
        gen->calcfitness(f);
        gen->sort(0, gen->get_nchroms());
        printf("epoch[%d] chrom[%d] fit = %f\n",epoch,0, gen->pop[popNum][0].getFitness());

    }

    free(x);
    free(f);
    free(y);
    free(z);
    free(M);
    free(OShift);
    free(x_bound);
    delete gen;
    return 0;
}