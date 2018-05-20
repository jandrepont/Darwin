#include "RealChromosome.h"
#include <random>
#include <ctime>
#include <iostream>

RealChromosome::RealChromosome()
{
    fitness = 0;
    nvars = 10;
    std::uniform_real_distribution<double> r_dist(-1024, 1023);
    std::mt19937 rng;
    rng.seed(std::random_device{}());

    for (int i = 0; i < nvars; i++){
        var.push_back(r_dist(rng));
    }


    origin.push_back("initial generation: 0");

}

RealChromosome::RealChromosome(int &r_nvars, float &min, float &max ) {

    std::uniform_real_distribution<double> r_dist(min, max);
    std::mt19937 rng;
    rng.seed(std::random_device{}());

    nvars = r_nvars;
    fitness = 0;
    origin.push_back("initial generation: 0");

    for (int i = 0; i < nvars; i++) {
        var.push_back(r_dist(rng));
    }
}

RealChromosome::~RealChromosome()
{
//    delete [] var;
}

void RealChromosome::setAllvar(std::vector<double> rvar)
{
//    var = std::move(rvar);
    var.swap(rvar);
}

RealChromosome RealChromosome::operator=(const RealChromosome& r)
{
    if (this == &r)
        return *this;

    var = std::move(r.var);
    fitness = r.fitness;
    origin = std::move(r.origin);
    return *this;
}
void RealChromosome::add_full_origin(std::vector<std::string> rorigin)
{
    origin = std::move(rorigin);
}
/*
 * from std::vector::clear
 * A reallocation is not guaranteed to happen, and the vector capacity is not guaranteed to change due to calling this function.
 * A typical alternative that forces a reallocation is to use swap:
 */
void RealChromosome::rewrite_resize_origin(std::vector<std::string> rorigin)
{
    origin.swap(rorigin);
}
