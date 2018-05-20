 #include <iostream>
#include <random>
#include <algorithm>
#include "RealGA.h"
#include "RealChromosome.h"
#include <sstream>
#include <malloc.h>
//#include "../cec14-c-code/cec14_test_func.cpp"

RealGA::RealGA()
{
    popNum = 0;
    ncross = 40;
    nmute = 3;
    nchroms = 50;
    nelites = 5;
    generation = 0;
    nvars = 10;
    min = -1024;
    max = 1023;


    for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<RealChromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(RealChromosome());
        }
    }
}
RealGA::RealGA(int r_ncross, int r_nmute, int r_nchroms, int r_nelites, int r_nvars, float r_min, float r_max)
{
    popNum = 0;
    ncross = r_ncross;
    nmute = r_nmute;
    nchroms = r_nchroms;
    nelites = r_nelites;
    nvars = r_nvars;
    generation = 0;
    min = r_min;
    max = r_max;
    for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<RealChromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(RealChromosome(r_nvars, min, max));
        }
    }
}


//RealGA::~RealGA()
//{
//    for(int i = 0; i < 2; i++){
//        delete [] pop[i];
//    }
//    delete [] pop;
//
//}


//select canidates for crossover where P(x) = x.fitness/totalFitness
int RealGA::rouletteWheel()
{
    double totalFit = 0;
//    topFit++;
    int prevPop = ((popNum+1)%2);
    for(int i = 0; i < nchroms; i++){
        totalFit += fabs(pop[prevPop][i].getFitness());
    }
    std::uniform_real_distribution<double> r_dist(0, totalFit);
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    double roulette;
    roulette = r_dist(rng);
//    printf("totalFit = %f, roulette = %f\n",totalFit, roulette);
    int wheel = 0;
    double x=0;
    while(roulette > 0){
        x = pop[prevPop][wheel].getFitness();
        roulette = roulette - fabs(x);
        wheel++;
    }
    if(wheel == nchroms){
        wheel--;
    }
    return wheel;
}

void RealGA::returnInput(double *x)
{
    double temp;
    int count;
    count = 0;
    for(int i = 0; i < nchroms; i++){
        for(int j = 0; j < nvars; j++){
            temp = pop[popNum][i].getvar(j);
            x[count] = temp;
            count++;
        }
    }
}

void RealGA::calcfitness(double* f)
{
    for(int i = 0; i < nchroms; i++){
        pop[popNum][i].setFitness(f[i]);
    }
}
void RealGA::dummyFitness()
{
    for(int i = 0; i < nchroms; i++){
        pop[popNum][i].setFitness(1.0);
    }
}
void RealGA::preserveElites()
{
    int prevPop = (popNum + 1)%2;
    std::string add_origin;
    add_origin = "elite of Generation: " + std::to_string(generation);
    for(int i = 0; i < nelites; i++){
        pop[popNum][i] = pop[prevPop][i];
        pop[popNum][i].push_to_origin(add_origin);
    }
}

void RealGA::crossover()
{
    int prevPop = ((popNum+1)%2);
    int ran1, ran2, crosspoint;
    double weight;
    std::uniform_int_distribution<int> i_dist(0, nvars-1);
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::uniform_real_distribution<double> real_distribution(0.0, 1.0);
    double val1, val2, p1, p2;
    std::vector<std::string> child_origin;
    child_origin.push_back(" ");
    std::ostringstream os;

    for(int child = nelites; child < ncross+nelites; child+=2){
        crosspoint = i_dist(rng);
        ran1 = rouletteWheel();
        ran2 = rouletteWheel();
        weight = real_distribution(rng);
        while(ran1 == ran2){
            ran2 = rouletteWheel();
//            printf("random parent 1 = %d\nrandom parent 2 = %d \n", ran1, ran2);
        }
        for(int cross = 0; cross < nvars; cross++){
            if(cross == crosspoint){
                p1 = pop[prevPop][ran1].getvar(cross);
                p2 = pop[prevPop][ran2].getvar(cross);
                val1 = (p1*weight) + ((1 - weight)*p2);
                val2 = (p1*(1-weight)) + (weight*p2);
                pop[popNum][child].setvar(cross, val1);
                pop[popNum][child+1].setvar(cross, val2);
            }
            else if(cross < crosspoint){
                pop[popNum][child].setvar(cross, pop[prevPop][ran1].getvar(cross));
                pop[popNum][child+1].setvar(cross, pop[prevPop][ran2].getvar(cross));
            }
            else{
                pop[popNum][child].setvar(cross, pop[prevPop][ran2].getvar(cross));
                pop[popNum][child+1].setvar(cross, pop[prevPop][ran1].getvar(cross));
            }
        }

        //add to or create genealogy
        child_origin[0] = "child of parents " + std::to_string(ran1) + " & " + std::to_string(ran2) + " Generation: " + std::to_string(generation);
        pop[popNum][child].rewrite_resize_origin(child_origin);
        pop[popNum][child+1].rewrite_resize_origin(child_origin);
    }
}


/*
 * Quicksort
 */
void RealGA::sort(int p, int q)
{
    int r;
    if(p<q)
    {
        r = partition(p,q);
        sort(p,r);
        sort(r+1, q);
    }
}

int RealGA::partition(int p, int q)
{
    double x = pop[popNum][p].getFitness();
    int i = p;
    int j;

    for(j = p+1; j<q; j++)
    {
        if(pop[popNum][j].getFitness() <= x)
        {
            i = i + 1;
            std::swap(pop[popNum][i], pop[popNum][j]);
        }
    }

    std::swap(pop[popNum][i], pop[popNum][p]);
    return i;
}

void RealGA::mutate()
{
    int ran_gene, ran_chrom;
    double var;
    int prevPop = (popNum+1)%2;
    int index;
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::string add_origin;
    std::uniform_int_distribution<int> i_dist(0,nvars-1);
    std::uniform_real_distribution<double> r_dist(min, max);
    for(int i = 0; i < nmute; i++) {
        index = nelites + ncross + i;
        var = r_dist(rng);
        i_dist = std::uniform_int_distribution<int> (0, nvars-1);
        ran_gene = i_dist(rng);
        i_dist = std::uniform_int_distribution<int> (nelites, nchroms-1);
        ran_chrom = i_dist(rng);
        pop[popNum][ran_chrom].setvar(ran_gene, var);
        pop[popNum][index] = pop[prevPop][ran_chrom];
        add_origin = "Gene [";
        add_origin += std::to_string(ran_gene);
        add_origin += "] mutated Generation: " + std::to_string(generation);
        pop[popNum][ran_chrom].push_to_origin(add_origin);

    }
}

void RealGA::createNew()
{
    int newChrom = nchroms - (nelites + ncross);
    std::vector<std::string> new_origin;
    new_origin.push_back("New Chrom created in Generation: " + std::to_string(generation));
//    printf("New Chroms = %d\n",newChrom);
    int index = 0;
    for(int i = 0; i < newChrom; i++){
        index = nchroms - 1 - i;
        pop[popNum][index] = RealChromosome(nvars, min, max);
        pop[popNum][index].rewrite_resize_origin(new_origin);
//        printf("Index = %d\n",index);
    }

}



void RealGA::iteration()
{

}






