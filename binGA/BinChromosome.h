//
// Created by joela on 12/20/17.
//

#ifndef REALGA_BINCHROMOSOME_H
#define REALGA_BINCHROMOSOME_H

#include <vector>
#include <stdio.h>
#include <string>


class BinChromosome {
public:

    BinChromosome();
    BinChromosome(int r_nvars, float min, float max, int chrom_length);

    ~BinChromosome();

    bool operator<(BinChromosome& r);
    BinChromosome operator=(const BinChromosome& r);

    double getvar(int index);
    void setvar(int index, double rvar);
    void calcVar(int& chrom_length, double& max);

    std::vector<double> const &getAllvar() const;
    void setAllvar(std::vector<double>& rvar);

    double getFitness();
    void setFitness(double fitness);

    double get_nvars();
    void set_nvars(int r_nvars);

    int get_gene(int index);
    void set_gene(int index, int val);

    /*
     * Genealogy functions
     */
    std::vector<std::string> const &getOrigin() const;
    void push_to_origin(std::string addition);
    void add_full_origin(std::vector<std::string> history);
    void rewrite_resize_origin(std::vector<std::string> rorigin);
    void clear_origin();

private:

    double fitness;
    std::vector<int> gene;
    std::vector<double> var;
    std::vector<std::string> origin;
    int nvars;
};

inline int BinChromosome::get_gene(int index)
{
    return gene[index];
}
inline void BinChromosome::set_gene(int index, int val)
{
    gene[index] = val;
}

inline double BinChromosome::get_nvars()
{
    return nvars;
}
inline void BinChromosome::set_nvars(int r_nvars)
{
    nvars = r_nvars;
}

inline void BinChromosome::clear_origin()
{
    std::vector<std::string>().swap(origin);
}
inline std::vector<std::string> const &BinChromosome::getOrigin() const
{
    return origin;
}
inline void BinChromosome::push_to_origin(std::string addition)
{
    origin.push_back(addition);
}
inline bool BinChromosome::operator<(BinChromosome& r)
{
    return fitness < r.fitness;
}

inline double BinChromosome::getvar(int index)
{
    return var[index];
}
inline void BinChromosome::setvar(int index, double rvar)
{
    var[index] = rvar;
}

inline std::vector<double> const &BinChromosome::getAllvar() const
{
    return var;
}

inline double BinChromosome::getFitness()
{
    return fitness;
}

inline void BinChromosome::setFitness(double rfitness)
{
    fitness = rfitness;
}

#endif //REALGA_BINCHROMOSOME_H
