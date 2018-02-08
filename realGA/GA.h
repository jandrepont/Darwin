//
// Created by joela on 1/2/18.
//

#ifndef REALGA_GA_H
#define REALGA_GA_H

#include "Chromosome.h"
#include "string"


class GA
{
public:
    GA();
    GA(int r_ncross, int r_nmute, int r_nchroms, int r_nelites, int r_nvars, float min, float max);

    std::vector< std::vector<Chromosome> > pop;
    //Chromosome pop[2][50];

//    ~GA();
    int rouletteWheel();
    void calcfitness(double* f);

    void preserveElites();
    void crossover();
    void sort(int p, int q);
    int partition(int p, int q);
    void mutate();
    void createNew();
    void iteration();

    double gettopFit();
    void settopFit(double rtopFit);
    int getpopNum();
    void setpopNum(int rpopNum);

    void returnInput(double* x);

    //for pthreads
    int thread_id;


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

inline int GA::getGen()
{
    return generation;
}
inline void GA::setGen(int rgeneration)
{
    generation = rgeneration;
}

inline void GA::setpopNum(int rpopNum)
{
    popNum = rpopNum;
}
inline int GA::getpopNum()
{
    return popNum;
}

inline int GA::get_ncross()
{
    return ncross;
}
inline void GA::set_ncross(int rncross)
{
    ncross = rncross;
}

inline int GA::get_nmute()
{
    return nmute;
}
inline void GA::set_nmute(int rnmute)
{
    nmute = rnmute;
}

inline int GA::get_nchroms()
{
    return nchroms;
}
inline void GA::set_nchroms(int rnchroms)
{
    nchroms = rnchroms;
}

inline int GA::get_nelites()
{
    return nelites;
}
inline void GA::set_nelites(int rnelites)
{
    ncross = rnelites;
}

inline int GA::get_nvars()
{
    return nvars;
}
inline void GA::set_nvars(int rnvars)
{
    ncross = rnvars;
}


#endif //REALGA_GA_H