//
// Created by joela on 12/20/17.
//

#ifndef REALGA_CHROMOSOME_H
#define REALGA_CHROMOSOME_H

#include <vector>
#include <stdio.h>
#include <string>


class Chromosome {
public:

    Chromosome();
    Chromosome(int &r_nvars, float &min, float &max );

    ~Chromosome();

    bool operator<(Chromosome& r);
    Chromosome operator=(const Chromosome& r);

    double getvar(int index);
    void setvar(int index, double rvar);

    std::vector<double> const &getAllvar() const;
    void setAllvar(std::vector<double>);

    double getFitness();
    void setFitness(double fitness);

    double get_nvars();
    void set_nvars(int r_nvars);

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
    std::vector<double> var;
    std::vector<std::string> origin;
    int nvars;
};
inline double Chromosome::get_nvars()
{
    return nvars;
}
inline void Chromosome::set_nvars(int r_nvars)
{
    nvars = r_nvars;
}

inline void Chromosome::clear_origin()
{
    std::vector<std::string>().swap(origin);
}
inline std::vector<std::string> const &Chromosome::getOrigin() const
{
    return origin;
}
inline void Chromosome::push_to_origin(std::string addition)
{
    origin.push_back(addition);
}
inline bool Chromosome::operator<(Chromosome& r)
{
    return fitness < r.fitness;
}

inline double Chromosome::getvar(int index)
{
    return var[index];
}
inline void Chromosome::setvar(int index, double rvar)
{
    var[index] = rvar;
}

inline std::vector<double> const &Chromosome::getAllvar() const
{
    return var;
}

inline double Chromosome::getFitness()
{
    return fitness;
}

inline void Chromosome::setFitness(double rfitness)
{
    fitness = rfitness;
}

#endif //REALGA_CHROMOSOME_H
