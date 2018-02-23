#include <iostream>
#include <random>
#include <algorithm>
#include "BinGA.h"
#include "BinChromosome.h"
#include <sstream>


BinGA::BinGA()
{
    popNum = 0;
    ncross = 40;
    nmute = 3;
    nchroms = 50;
    nelites = 5;
    generation = 0;
    nvars = 10;
    min = -100;
    max = 100;
    ngenes = 160;

    for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<BinChromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(BinChromosome());
        }
    }
}
BinGA::BinGA(int r_ncross, int r_nmute, int r_chrom_length, int r_nchroms, int r_nelites, int r_nvars, float r_min, float r_max)
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
    chrom_length = r_chrom_length;
    ngenes = r_chrom_length * r_nvars;
        for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<BinChromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(BinChromosome(r_nvars, min, max, r_chrom_length));
        }
    }
}


//BinGA::~BinGA()
//{
//    for(int i = 0; i < 2; i++){
//        delete [] pop[i];
//    }
//    delete [] pop;
//
//}


//select canidates for crossover where P(x) = x.fitness/totalFitness
int BinGA::rouletteWheel()
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

void BinGA::calcfitness(double* f)
{
    for(int i = 0; i < nchroms; i++){
        pop[popNum][i].setFitness(f[i]);
    }
}

void BinGA::dummyFitness()
{
    for(int i = 0; i < nchroms; i++){
        pop[popNum][i].setFitness(1.0);
    }
}

void BinGA::preserveElites()
{
    int prevPop = (popNum + 1)%2;
    std::string add_origin;
    add_origin = "elite of Generation: " + std::to_string(generation);
    for(int i = 0; i < nelites; i++){
        pop[popNum][i] = pop[prevPop][i];
        pop[popNum][i].push_to_origin(add_origin);
    }
}

void BinGA::crossover()
{
    int prevPop = ((popNum+1)%2);
    int ran1, ran2, crosspoint;
    std::uniform_int_distribution<int> i_dist(1, ngenes-2);
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    double val1, val2, p1, p2;
    std::vector<std::string> child_origin;
    child_origin.push_back(" ");
    std::ostringstream os;
    for(int child = nelites; child < ncross+nelites; child+=2){
        crosspoint = i_dist(rng);
        ran1 = rouletteWheel();
        ran2 = rouletteWheel();
        while(ran1 == ran2){
            ran2 = rouletteWheel();
        }
        for(int cross = 0; cross < ngenes; cross++){
            if(cross <= crosspoint){
                pop[popNum][child].set_gene(cross, pop[prevPop][ran1].get_gene(cross));
                pop[popNum][child+1].set_gene(cross, pop[prevPop][ran2].get_gene(cross));
            }
            else{
                pop[popNum][child].set_gene(cross, pop[prevPop][ran2].get_gene(cross));
                pop[popNum][child+1].set_gene(cross, pop[prevPop][ran1].get_gene(cross));
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
void BinGA::sort(int p, int q)
{
    int r;
    if(p<q)
    {
        r = partition(p,q);
        sort(p,r);
        sort(r+1, q);
    }
}

int BinGA::partition(int p, int q)
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

void BinGA::mutate()
{
    int ran_gene, ran_chrom, gene_val;
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::string add_origin;
    std::uniform_int_distribution<int> i_dist(0,ngenes-1);
    for(int i = 0; i < nmute; i++) {
        ran_gene = i_dist(rng);
        i_dist = std::uniform_int_distribution<int> (nelites, nchroms-1);
        ran_chrom = i_dist(rng);
        gene_val = pop[popNum][ran_chrom].get_gene(ran_gene);
        gene_val = (gene_val+1)%2;
        pop[popNum][ran_chrom].set_gene(ran_gene, gene_val);

        add_origin = "Gene [";
        add_origin += std::to_string(ran_gene);
        add_origin += "] mutated Generation: " + std::to_string(generation);
        pop[popNum][ran_chrom].push_to_origin(add_origin);

    }
}

void BinGA::createNew()
{
    int newChrom = nchroms - (nelites + ncross);
    std::vector<std::string> new_origin;
    new_origin.push_back("New Chrom created in Generation: " + std::to_string(generation));
//    printf("New Chroms = %d\n",newChrom);
    int index = 0;
    for(int i = 0; i < newChrom; i++){
        index = nchroms - 1 - i;
        pop[popNum][index] = BinChromosome(nvars, min, max,chrom_length);
        pop[popNum][index].rewrite_resize_origin(new_origin);
//        printf("Index = %d\n",index);
    }

}

void BinGA::returnInput(double *x)
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

void BinGA::calcVars(int chrom_length, double max){
    for(int i = 0; i < nchroms; i++){
        pop[popNum][0].calcVars(chrom_length, max);
    }
}


void BinGA::iteration()
{

}






