//
// Created by joela on 1/2/18.
//

#ifndef BIN_REALGA_GA_H
#define BIN_REALGA_GA_H

#include "Chromosome.h"
#include "string"



class GA
{
public:
    GA();
    GA(int r_ncross, int r_nmute, int r_nchroms, int r_nelites, int r_ntraders );


    std::vector< std::vector<Chromosome> > pop;
    //Chromosome pop[2][50];

//    ~GA();
    int rouletteWheel();
    void calcfitness();

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

    int get_traders();
    void set_traders(int r_ntraders);

    int get_total_vars();
    void set_total_vars(int r_total_vars);


    //parsing functions for url
    void init_magic_url();
    std::string url_replace(std::string &s, size_t &found, const std::string &toReplace, const std::string &replaceWith);

    void replace_values();
private:

    //also need to keep track of which elements are actually found and placed in magic string so no wasted cycles
    //fields are the url fields to be replaced by vars
    Url_fields fields[8];

    int topFit;
    int ntraders, ncross, nmute, nchroms, nelites, nvars, total_vars;
    std::vector<std::string> url_list;
    std::string magic_url;
    int popNum;
    int n_of_reps; //max number of fields for an identifier to be replaced
    int generation;

};

inline int GA::get_total_vars(){
    return total_vars;
}
inline void GA::set_total_vars(int r_total_vars){
    total_vars = r_total_vars;
}
inline int GA::getGen()
{
    return generation;
}
inline void GA::setGen(int rgeneration)
{
    generation = rgeneration;
}
inline int GA::get_traders(){
    return ntraders;
}

inline void GA::set_traders(int r_ntraders){
    ntraders = r_ntraders;
}


inline double GA::gettopFit()
{
    return topFit;
}
inline void GA::settopFit(double rtopFit)
{
    topFit = rtopFit;
}

inline void GA::setpopNum(int rpopNum)
{
    popNum = rpopNum;
}
inline int GA::getpopNum()
{
    return popNum;
}
inline void GA::set_urlList(std::string &rurl_list, int index)
{
    url_list[index] = rurl_list;
}
inline std::string GA::get_urlList(int index)
{
    return url_list[index];
}
inline void GA::set_magicUrl(std::string &rmagic_url)
{
    magic_url = rmagic_url;
}
inline std::string GA::get_magicUrl()
{
    return magic_url;
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


#endif //GREGOR_GA_H