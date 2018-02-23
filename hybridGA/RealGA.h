//
// Created by joela on 1/2/18.
//

#ifndef REALGA_GA_H
#define REALGA_GA_H

#include "RealChromosome.h"
#include "string"


class RealGA
{
public:
    RealGA();
    RealGA(int r_ncross, int r_nmute, int r_nchroms, int r_nelites, int r_nvars, float min, float max);

    std::vector< std::vector<RealChromosome> > pop;
    //RealChromosome pop[2][50];

//    ~RealGA();
    int rouletteWheel();
    void calcfitness(double* f);

    void preserveElites();
    void crossover();
    void sort(int p, int q);
    int partition(int p, int q);
    void mutate();
    void createNew();
    void iteration();

    std::vector<double> gettopFit();
    void settopFit(double rtopFit);
    int getpopNum();
    void setpopNum(int rpopNum);

    void returnInput(double* x);
    void dummyFitness();


    //getters and setters for member vars;



        int get_ncross();
    void set_ncross(int rncross);

    int get_nmute();
    void set_nmute(int rnmute);

    int get_nchroms();
    void set_nchroms(int rnchroms);

    int get_nelites();
    void set_nelites(int rnelites);

    int get_nvars();
    void set_nvars(int rnvars);

    int getGen();
    void setGen(int rgeneration);

private:


    int ncross, nmute, nchroms, nelites, nvars;
    float min, max;
    int popNum;
    int generation;

};


inline void RealGA::setGen(int rgeneration)
{
    generation = rgeneration;
}

inline void RealGA::setpopNum(int rpopNum)
{
    popNum = rpopNum;
}


inline int RealGA::get_nchroms()
{
    return nchroms;
}


#endif //REALGA_GA_H