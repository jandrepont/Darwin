#include <iostream>
#include <random>
#include <algorithm>
#include "GA.h"
#include "Chromosome.h"
#include <sstream>


GA::GA()
{
    popNum = 0;
    ncross = 44;
    nmute = 8;
    nchroms = 50;
    nelites = 2;
    topFit = 0;
    generation = 0;


    for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<Chromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(Chromosome());
            url_list.push_back(magic_url);
        }
    }
}
GA::GA(int r_ncross, int r_nmute, int r_nchroms, int r_nelites, int r_nvars, float min, float max)
{
    popNum = 0;
    ncross = r_ncross;
    nmute = r_nmute;
    nchroms = r_nchroms;
    nelites = r_nelites;
    nvars = 8;
    topFit = 0;
    generation = 0;
    ntraders = r_ntraders;
    total_vars = nvars * ntraders;
    for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<Chromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(Chromosome(r_nvars, min, max));
        }
    }
}


//GA::~GA()
//{
//    for(int i = 0; i < 2; i++){
//        delete [] pop[i];
//    }
//    delete [] pop;
//
//}


//select canidates for crossover where P(x) = x.fitness/totalFitness
int GA::rouletteWheel()
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

void GA::calcfitness()
{
    std::vector<double> vars;
    double fitness;
//    for(int i = 0; i < nchroms; i++){
//        vars = pop[popNum][i].getAllvar();
//        fitness = (vars[0]+vars[1]+vars[2]+vars[3]+vars[4]+vars[5]+vars[6]+vars[7])/10000000;
//        pop[popNum][i].setFitness(fitness);
//    }

}

void GA::preserveElites()
{
    int prevPop = (popNum + 1)%2;
    std::string add_origin;
    add_origin = "elite of Generation: " + std::to_string(generation);
    for(int i = 0; i < nelites; i++){
        pop[popNum][i] = pop[prevPop][i];
        pop[popNum][i].push_to_origin(add_origin);
    }
}

void GA::crossover()
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
        for(int cross = 0; cross < 8; cross++){
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
void GA::sort(int p, int q)
{
    int r;
    if(p<q)
    {
        r = partition(p,q);
        sort(p,r);
        sort(r+1, q);
    }
}

int GA::partition(int p, int q)
{
    double x = pop[popNum][p].getFitness();
    int i = p;
    int j;

    for(j = p+1; j<q; j++)
    {
        if(pop[popNum][j].getFitness() >= x)
        {
            i = i + 1;
            std::swap(pop[popNum][i], pop[popNum][j]);
        }
    }

    std::swap(pop[popNum][i], pop[popNum][p]);
    return i;
}

void GA::mutate()
{

    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::string add_origin;
    for(int i = 0; i < nmute; i++) {
        std::uniform_int_distribution<int> i_dist(0,nvars-1);
        int ran_gene = i_dist(rng);
        i_dist = std::uniform_int_distribution<int> (nelites, nchroms-1);
        int ran_chrom = i_dist(rng);
//        printf("Random chrom for mutate = %d\n", ran_chrom);
        switch (ran_gene % nvars) {
            case 0 :
            {
                std::uniform_real_distribution<double> r_dist(pop[popNum][ran_chrom].getvar(0), 10000000);
                pop[popNum][ran_chrom].setvar(0, r_dist(rng));
            }
                break;
            case 1 :
            {
                std::uniform_real_distribution<double> r_dist(2000000, pop[popNum][ran_chrom].getvar(ran_gene-1));
                pop[popNum][ran_chrom].setvar(1, r_dist(rng));
            }
                break;
            case 2 :
            {
                std::uniform_real_distribution<double> r_dist(-0.03, 0.08);
                pop[popNum][ran_chrom].setvar(2, r_dist(rng));
            }
                break;
            case 3 :
            {
                i_dist = std::uniform_int_distribution<int>(120, 480);
                pop[popNum][ran_chrom].setvar(3, i_dist(rng));
            }
                break;
            case 4 :
            {
                std::uniform_real_distribution<double> r_dist(0.3, 0.5);
                pop[popNum][ran_chrom].setvar(4, r_dist(rng));
            }
                break;
            case 5 :
            {
                i_dist = std::uniform_int_distribution<int>(2, 5);
                pop[popNum][ran_chrom].setvar(5, i_dist(rng));

            }
                break;
            case 6 :
            {
                std::uniform_real_distribution<double> r_dist(0.00, 0.050);
                pop[popNum][ran_chrom].setvar(6, r_dist(rng));
            }
                break;
            case 7 :
            {
                std::uniform_real_distribution<double> r_dist(0.00, 0.050);
                pop[popNum][ran_chrom].setvar(7, r_dist(rng));
            }
                break;
            default:
                printf("error in mutation, %d instead of (0-7)", ran_gene);
        }
        add_origin = "Gene [";
        add_origin += std::to_string(ran_gene);
        add_origin += "] mutated Generation: " + std::to_string(generation);
        pop[popNum][ran_chrom].push_to_origin(add_origin);

    }
}

void GA::createNew()
{
    int newChrom = nchroms - (nelites + ncross);
    std::vector<std::string> new_origin;
    new_origin.push_back("New Chrom created in Generation: " + std::to_string(generation));
//    printf("New Chroms = %d\n",newChrom);
    int index = 0;
    for(int i = 0; i < newChrom; i++){
        index = nchroms - 1 - i;
        pop[popNum][index] = Chromosome(ntraders);
        pop[popNum][index].rewrite_resize_origin(new_origin);
//        printf("Index = %d\n",index);
    }

}



void GA::iteration()
{

}

std::string GA::url_replace(std::string & s, size_t &found, const std::string &toReplace, const std::string &replaceWith)
{

    if (s.size() < toReplace.size())return s;

    std::size_t find = found;

    if (find == std::string::npos) return s;
    return(s.replace(find, toReplace.length(), replaceWith));
}





