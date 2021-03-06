//
// Created by joela on 1/2/18.
//

#ifndef BINGA_H
#define BINGA_H

#include "BinChromosome.h"
#include "string"


class BinGA
{
public:
    BinGA();
    BinGA(int r_ncross, int r_nmute, int chrom_length, int r_nchroms, int r_nelites, int r_nvars, float min, float max);

    //data structures
    std::vector< std::vector<BinChromosome> > pop;
    //global crossover kga
    struct memoryAssistedCrossover {

       std::vector<BinChromosome> lower;
       std::vector<BinChromosome> upper;

    } memAssist;

    void initMemAssist();
    //BinChromosome pop[2][50];

//    ~BinGA();
    int rouletteWheel();
    void calcfitness(double *x, double *f, int nx, int mx,int func_num);

    void preserveElites();

    void global_crossover();
    void local_crossover();
    void memAssist_global_crossover();


    void sort(int p, int q);
    int partition(int p, int q);
    void mutate(int mutations);
    void createNew();
    void iteration();
    void calcVars(int chrom_length, double max);

    double gettopFit();
    void settopFit(double rtopFit);
    int getpopNum();
    void setpopNum(int rpopNum);
    void returnInput(double *x);
    void returnInput(double *x, int chroms);
    void setMemFit(std::vector<BinChromosome>& temp, int chroms);

    void calcfitness(double* f);
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


    int ncross, nmute, nchroms, nelites, nvars, ngenes, chrom_length, func_num;
    float min, max;
    int popNum;
    int generation;

};

inline int BinGA::getGen()
{
    return generation;
}
inline void BinGA::setGen(int rgeneration)
{
    generation = rgeneration;
}

inline void BinGA::setpopNum(int rpopNum)
{
    popNum = rpopNum;
    generation++;
}
inline int BinGA::getpopNum()
{
    return popNum;
}

inline int BinGA::get_ncross()
{
    return ncross;
}
inline void BinGA::set_ncross(int rncross)
{
    ncross = rncross;
}

inline int BinGA::get_nmute()
{
    return nmute;
}
inline void BinGA::set_nmute(int rnmute)
{
    nmute = rnmute;
}

inline int BinGA::get_nchroms()
{
    return nchroms;
}
inline void BinGA::set_nchroms(int rnchroms)
{
    nchroms = rnchroms;
}

inline int BinGA::get_nelites()
{
    return nelites;
}
inline void BinGA::set_nelites(int rnelites)
{
    ncross = rnelites;
}

inline int BinGA::get_nvars()
{
    return nvars;
}
inline void BinGA::set_nvars(int rnvars)
{
    ncross = rnvars;
}


#endif //BINGA_H
