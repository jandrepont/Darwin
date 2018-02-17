#include "Chromosome.h"
#include <random>
#include <ctime>
#include <iostream>

Chromosome::Chromosome()
{
    fitness = 0;
    nvars = 10;

    std::uniform_int_distribution<int> integer_distribution(0, 1);
    std::mt19937 rng;
    rng.seed(std::random_device{}());
//    std::vector<int> unbounded_val;
    double temp_val;
    temp_val = 0;
    for(int i = 0; i < 160; i++){
        gene.push_back(integer_distribution(rng));
        if(gene[i] == 1){
            temp_val += pow(2, i);
        }
        if(i % nvars == 0 && i != 0){
            temp_val = ((temp_val - 32768) / 32);
            var.push_back(temp_val);
            temp_val = 0;
        }
    }

    origin.push_back("initial generation: 0");
}
Chromosome::Chromosome(int r_nvars, float min, float max, int chrom_length ) {

    fitness = 0;
    nvars = r_nvars;

    std::uniform_int_distribution<int> integer_distribution(0, 1);
    std::mt19937 rng;
    rng.seed(std::random_device{}());
//    std::vector<int> unbounded_val;
    double temp_val;
    int constraint;
    int length;
    length = nvars * chrom_length;
    temp_val = 0;
    constraint = chrom_length;
    constraint = pow(2,constraint);
    constraint -= 1;
    for(int i = 0; i < length; i++){
        gene.push_back(integer_distribution(rng));
        if(gene[i] == 1){
            temp_val += pow(2, (i%chrom_length));
        }
        if(((i % chrom_length) == 0 && i != 0) || i == length-1){
            temp_val = temp_val-constraint;
            temp_val = temp_val/constraint;
            temp_val = temp_val*max;
            var.push_back(temp_val);
            temp_val = 0;
        }
    }
}

Chromosome::~Chromosome()
{
//    delete [] var;
}

void Chromosome::setAllvar(std::vector<double>& rvar)
{
    var = std::move(rvar);
}

Chromosome Chromosome::operator=(const Chromosome& r)
{
    if (this == &r)
        return *this;
    gene = std::move(r.gene);
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
