//
// Created by joela on 12/20/17.
//

#ifndef REALGA_CHROMOSOME_H
#define REALGA_CHROMOSOME_H

#include <vector>
#include <stdio.h>
#include <string>


class RealChromosome {
public:

    RealChromosome();
    RealChromosome(int &r_nvars, float &min, float &max );

    ~RealChromosome();

    bool operator<(RealChromosome& r);
    RealChromosome operator=(const RealChromosome& r);

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
inline double RealChromosome::get_nvars()
{
    return nvars;
}
inline void RealChromosome::set_nvars(int r_nvars)
{
    nvars = r_nvars;
}

inline void RealChromosome::clear_origin()
{
    std::vector<std::string>().swap(origin);
}
inline std::vector<std::string> const &RealChromosome::getOrigin() const
{
    return origin;
}
inline void RealChromosome::push_to_origin(std::string addition)
{
    origin.push_back(addition);
}
inline bool RealChromosome::operator<(RealChromosome& r)
{
    return fitness < r.fitness;
}

inline double RealChromosome::getvar(int index)
{
    return var[index];
}
inline void RealChromosome::setvar(int index, double rvar)
{
    var[index] = rvar;
}

inline std::vector<double> const &RealChromosome::getAllvar() const
{
    return var;
}

inline double RealChromosome::getFitness()
{
    return fitness;
}

inline void RealChromosome::setFitness(double rfitness)
{
    fitness = rfitness;
}

#endif //REALGA_CHROMOSOME_H
