#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>


int main(){


    int nvars = 5;
    int chrom_length = 16;
    std::vector<double> vars;
    std::vector<int> gene;
     std::uniform_real_distribution<double> r_dist(-100, 100);
     std::mt19937 rng;
     rng.seed(std::random_device{}());
    for (int i = 0; i < 5; i++){
        vars.push_back(r_dist(rng));
        printf("vars[%d] = %f\n", i, vars[i]);
    }



    int temp;
    double conv;
    int index;
    double max = 100.0;
    double min = -100.0;
    for(int i = 0; i < nvars; i++){
        conv = vars[i];
        conv = conv / 100;
        conv = conv*(pow(2,15)-1);
        temp = (int)(conv+(pow(2,15)-1));
        printf("conv_vars[%d] = %d\n", i, temp);

        for(int j = 0; j < 16; j++){
            index = i*16;
            gene.push_back(0);
            gene[index+j] = temp % 2;
            temp = temp / 2;
        }
    }

    int constraint = 16;
    constraint = pow(2,constraint-1);
    constraint -= 1;
    double temp_val = 0;
    for(int i = 0; i < nvars*chrom_length; i++){
        if(gene[i] == 1){
            temp_val += pow(2, (i%chrom_length));
        }
        if(((i % chrom_length) == 0 && i != 0) || i == ((nvars*chrom_length)-1)){

            // printf("temp_var[%d] = %f\n", i, temp_val);
            temp_val = temp_val-constraint;
            temp_val = temp_val/constraint;
            temp_val = temp_val*max;
            printf("bin_vars[%d] = %f\n", i, temp_val);
            // var.push_back(temp_val);
            temp_val = 0;
        }
    }
}
