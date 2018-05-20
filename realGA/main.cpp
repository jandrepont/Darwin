//
// Created by joela on 1/4/18.
//
#include <iostream>
#include "RealGA.h"
#include "RealChromosome.h"
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
     * set up dyn RealGA
     */
    int standard, nchroms, ncross, nmute, nelites, nvars, nepochs;
    float min, max;
    printf("0 for standard, 1 for custom: ");
    scanf("%d", &standard);
    if(standard == 1) {
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
    }

    int i,j,k,n,m,func_num;
    double *f,*x,*y;
    printf("func num = ");
    scanf("%d", &func_num);

    x=(double *)malloc(nchroms*nvars*sizeof(double));
    f=(double *)malloc(sizeof(double)  *  nchroms);

    for(int run = 0; run < 30; run++) {

        RealGA *gen;
        std::vector<std::string> origin;
        gen = new RealGA(ncross, nmute, nchroms, nelites, nvars, min, max);
        int popNum = 0;

        gen->returnInput(x);
        cec17_test_func(x, f, nvars, nchroms, func_num);
        gen->calcfitness(f);
//    gen->dummyFitness();
        gen->sort(0, nchroms);

        for (int epoch = 0; epoch < nepochs; epoch++) {
            popNum = ((popNum + 1) % 2);
            gen->setpopNum(popNum);
            gen->preserveElites();
            gen->crossover();
            gen->createNew();
            gen->mutate();
            gen->returnInput(x);
            cec17_test_func(x, f, nvars, nchroms, func_num);
            gen->calcfitness(f);
//        gen->dummyFitness();
            gen->sort(0, nchroms);
//            printf("%d, %f\n", run, gen->pop[popNum][0].getvar(0));
            printf("%d, %f\n", run, gen->pop[popNum][0].getFitness());
//
//            origin = (gen->pop[popNum][0].getOrigin());
//
//            for(int i = 0; i < origin.size(); i++){
//                printf("%s | ", origin[i].c_str());
//            }
//            printf("\n");

        }

        delete gen;
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