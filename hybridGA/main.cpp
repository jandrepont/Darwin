//
// Created by joela on 1/4/18.
//
#include <iostream>
#include "RealGA.h"
#include "RealChromosome.h"
#include "BinChromosome.h"
#include "BinGA.h"
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

void cec17_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

int main(int argc, char *argv[]){


    /*
     * Set up hybrid
     */
    int standard, nchroms, ncross, nmute, nelites, nvars, nepochs, chrom_length;
    float min, max;
    printf("0 for standard, 1 for custom: ");
    scanf("%d", &standard);
    if(standard == 1) {
        printf("chroms = ");
        scanf("%d", &nchroms);
        printf("chrom length = ");
        scanf("%d", &chrom_length);
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
        printf("epochs = ");
        scanf("%d", &nepochs);
    } else{
        ncross = 160;
        nmute = 10;
        nchroms = 200;
        nelites = 20;
        nvars = 30;
        nepochs = 2000;
        min = -100;
        max = 100;
        chrom_length = 16;
    }


    int i,j,k,n,m,func_num;
    double *f,*x,*y;
    printf("func num = ");
    scanf("%d", &func_num);

    x=(double *)malloc(nchroms*nvars*sizeof(double));
    f=(double *)malloc(sizeof(double)  *  nchroms);

    RealGA *realGA;
    BinGA *binGA;

    for(int run = 0; run < 30; run++) {

        RealGA *realgen;
        BinGA *bingen;
        realgen = new RealGA(ncross, nmute, nchroms, nelites, nvars, min, max);
        bingen = new BinGA(ncross, nmute, chrom_length, nchroms, nelites, nvars, min, max);
        int popNum = 0;

        realgen->returnInput(x);
        cec17_test_func(x, f, nvars, nchroms, func_num);
        bingen->returnInput(x);
        realgen->calcfitness(f);
        cec17_test_func(x, f, nvars, nchroms, func_num);
        bingen->calcfitness(f);

//    realgen->dummyFitness();
        realgen->sort(0, nchroms);
        bingen->sort(0, nchroms);
        printf("%f\n", realgen->pop[popNum][0].getFitness());
        printf("%f\n", bingen->pop[popNum][0].getFitness());

        for (int epoch = 0; epoch < nepochs; epoch++) {
            popNum = ((popNum + 1) % 2);
            realgen->setpopNum(popNum);
            bingen->setpopNum(popNum);
            realgen->preserveElites();
            bingen->preserveElites();
            realgen->crossover();
            bingen->crossover();
            realgen->createNew();
            bingen->createNew();
            realgen->mutate();
            bingen->mutate();
            realgen->returnInput(x);
            cec17_test_func(x, f, nvars, nchroms, func_num);
            bingen->returnInput(x);
            realgen->calcfitness(f);
            cec17_test_func(x, f, nvars, nchroms, func_num);
            bingen->calcfitness(f);
//        realgen->dummyFitness();
            realgen->sort(0, nchroms);
            bingen->sort(0, nchroms);
            printf("%d, real =  %f\n", epoch, realgen->pop[popNum][0].getFitness());
            printf("%d, bin = %f\n", epoch, bingen->pop[popNum][0].getFitness());
            /*
             * need to compare top vals
             * replace
             * 
             */
        }

        printf("%d, %f\n", run, realgen->pop[popNum][0].getFitness());

        delete realgen;
        delete bingen;
    }
    free(x);
    free(f);
    free(z);
    free(M);
    free(OShift);
    free(x_bound);
//    delete gen;
    return 0;
}