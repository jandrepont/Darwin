#include "Chromosome.h"
#include <random>
#include <ctime>
#include <iostream>

Chromosome::Chromosome()
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

Chromosome::Chromosome(int &r_nvars, float &min, float &max ) {

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

Chromosome::~Chromosome()
{
//    delete [] var;
}

void Chromosome::setAllvar(std::vector<double> rvar)
{
    var = std::move(rvar);
}

Chromosome Chromosome::operator=(const Chromosome& r)
{
    if (this == &r)
        return *this;

    var = std::move(r.var);
    fitness = r.fitness;
    origin = std::move(r.origin);
    return *this;
}
void Chromosome::add_full_origin(std::vector<std::string> rorigin)
{
    origin = std::move(rorigin);
}
/*
 * from std::vector::clear
 * A reallocation is not guaranteed to happen, and the vector capacity is not guaranteed to change due to calling this function.
 * A typical alternative that forces a reallocation is to use swap:
 */
void Chromosome::rewrite_resize_origin(std::vector<std::string> rorigin)
{
    origin.swap(rorigin);
}
