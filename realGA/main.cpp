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

#define NUM_THREADS 1

void cec14_test_func(double *, double *,int,int,int);
double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

void *run_GA(void *ga_thread)
{
    int taskid;
    GA *gen;
    int i,j,k,n,m,func_num;
    double *f,*x,*y;
    int ncross, nmute, nchroms, nelites, nvars, nepochs, standard;
    float min, max;


    ncross = 160;
    nmute = 10;
    nchroms = 200;
    nelites = 20;
    nvars = 10;
    nepochs = 2000;
    min = -100;
    max = 100;

    x=(double *)malloc(nchroms*nvars*sizeof(double));
    f=(double *)malloc(sizeof(double)  *  nchroms);

    gen = (GA *) ga_thread;
    int popNum = 0;
    gen->returnInput(x);
    printf("1\n");
    cec14_test_func(x, f,nvars,nchroms, 1);
    printf("2\n");
    gen->calcfitness(f);
    gen->sort(0, nchroms);
    taskid = gen->thread_id;
    int epoch = 0;
    for(int j = 0; j < 100; j++) {
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
    }
    printf("Thread #= %d epoch[%d] chrom[%d] fit = %f\n",gen->thread_id, nepochs,0, gen->pop[popNum][0].getFitness());
//
    free(x);
    free(f);
    pthread_exit(NULL);
}



int main(int argc, char *argv[]){

    /*
     * set up dyn GA
     */
    int ncross, nmute, nchroms, nelites, nvars, nepochs, standard;
    float min, max;
//    printf("0 for standard, 1 for custom: ");
//    scanf("%d", &standavalvrd);
//    if(standard == 1) {
//        printf("chroms = ");
//        scanf("%d", &nchroms);
//        printf("cross = ");
//        scanf("%d", &ncross);
//        printf("mutation = ");
//        scanf("%d", &nmute);
//        printf("elites = ");
//        scanf("%d", &nelites);
//        printf("min = ");
//        scanf("%f", &min);
//        printf("max = ");
//        scanf("%f", &max);
//        printf("vars = ");
//        scanf("%d", &nvars);
//        printf("epochs = ");
//        scanf("%d", &nepochs);
//    } else{
        ncross = 160;
        nmute = 10;
        nchroms = 200;
        nelites = 20;
        nvars = 10;
        nepochs = 2000;
        min = -100;
        max = 100;
//    }

    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc, sum, t;
    GA gen[NUM_THREADS];


    for(t = 0; t < NUM_THREADS; t++){
        gen[t].thread_id = t;
        printf("In main(), creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, run_GA, (void *)&gen[t]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

//    free(x);
//    free(f);
//    free(y);
    free(z);
    free(M);
    free(OShift);
    free(x_bound);
//    delete gen;
    return 0;
}