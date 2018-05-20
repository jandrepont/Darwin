#include <iostream>
#include <random>
#include <algorithm>
#include "BinGA.h"
#include "BinChromosome.h"
#include <sstream>

void cec17_test_func(double *x, double *f, int nx, int mx,int func_num);


BinGA::BinGA()
{
    popNum = 0;
    ncross = 40;
    nmute = 3;
    nchroms = 50;
    nelites = 5;
    generation = 0;
    nvars = 10;
    min = -100;
    max = 100;
    ngenes = 160;

    for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<BinChromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(BinChromosome());
        }
    }
}
BinGA::BinGA(int r_ncross, int r_nmute, int r_chrom_length, int r_nchroms, int r_nelites, int r_nvars, float r_min, float r_max)
{
    popNum = 0;
    generation=0;
    ncross = r_ncross;
    nmute = r_nmute;
    nchroms = r_nchroms;
    nelites = r_nelites;
    nvars = r_nvars;
    generation = 0;
    min = r_min;
    max = r_max;
    chrom_length = r_chrom_length;
    ngenes = r_chrom_length * r_nvars;
        for(int i = 0; i < 2; i++){
        pop.push_back(std::vector<BinChromosome>());
        for(int j = 0; j < nchroms; j++){
            pop[i].push_back(BinChromosome(r_nvars, min, max, r_chrom_length));
        }
    }
}


//BinGA::~BinGA()
//{
//    for(int i = 0; i < 2; i++){
//        delete [] pop[i];
//    }
//    delete [] pop;
//
//}

void BinGA::initMemAssist()
{
    //defined for each gene
    int lowRange, upRange, lvar, uvar;
    BinChromosome fittest = pop[popNum][0];

    double max = 100.0;
    int gene_length;
    for(int gene = 0; gene < ngenes; gene++){
        //init container
        uvar = (gene / chrom_length)+1;
        lvar = nvars - uvar;

        memAssist.upper.push_back(BinChromosome (nvars, min, max, chrom_length));
        memAssist.lower.push_back(BinChromosome (nvars, min, max, chrom_length));
        //range for transfer
        //assume 480 genes uprange starts @ 0 goes to 478
        upRange = gene+1;
        lowRange = ngenes - gene;

        for(int index = 0; index < upRange; index++){
            //fill in upper triangle
            memAssist.upper[gene].set_gene(index,fittest.get_gene(index));
        }
        for(int index = upRange; index < lowRange; index++) {
            //fill in rest
            memAssist.lower[gene].set_gene(index,fittest.get_gene(index));
        }
        memAssist.upper[gene].calcVar(chrom_length, max, uvar);
        memAssist.lower[gene].calcVar(chrom_length, max, lvar);

    }

}

//select canidates for crossover where P(x) = x.fitness/totalFitness
int BinGA::rouletteWheel()
{
    double totalFit = 0;
//    topFit++;
    int prevPop = ((popNum+1)%2);
    for(int i = 0; i < nchroms; i++){
        totalFit += fabs(pop[prevPop][i].getFitness());
    }
    std::uniform_real_distribution<double> r_dist(0, totalFit);
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    double roulette;
    roulette = r_dist(rng);
//    printf("totalFit = %f, roulette = %f\n",totalFit, roulette);
    int wheel = 0;
    double x=0;
    while(roulette > 0){
        x = pop[prevPop][wheel].getFitness();
        roulette = roulette - fabs(x);
        wheel++;
    }
    if(wheel == nchroms){
        wheel--;
    }
    return wheel;
}

void BinGA::calcfitness(double *x, double *f, int nx, int mx,int rfunc_num){
    /*
     * I know this seems ridiculous but it helps with calc of memAssist during crossover
     * if the cec17 funct is inside of this class
     */
    func_num = rfunc_num;
    cec17_test_func(x, f, nx, mx, func_num);

    for(int i = 0; i < nchroms; i++){
        pop[popNum][i].setFitness(f[i]);
    }

}


void BinGA::dummyFitness()
{
    for(int i = 0; i < nchroms; i++){
        pop[popNum][i].setFitness(1.0);
    }
}

void BinGA::preserveElites()
{
    int prevPop = (popNum + 1)%2;
//    std::string add_origin;
//    add_origin = "elite of Generation: " + std::to_string(generation);
    for(int i = 0; i < nelites; i++){
        pop[popNum][i] = pop[prevPop][i];
//        pop[popNum][i].push_to_origin(add_origin);
    }
}
void BinGA::local_crossover(){
    int prevPop = ((popNum+1)%2);
    int ran1, ran2, crosspoint,gene;
    std::uniform_int_distribution<int> i_dist(1, chrom_length-2);
    std::mt19937 rng;
    rng.seed(std::random_device{}());

    std::vector<std::string> child_origin;
    child_origin.push_back(" ");
    std::ostringstream os;
    for(int child = nelites; child < ncross+nelites; child+=2){
        ran1 = rouletteWheel();
        ran2 = rouletteWheel();
//        printf("ran1 = %d, ran2 = %d\n",ran1, ran2);

        while(ran1 == ran2){
            ran2 = rouletteWheel();
        }
        for(int var = 0; var < nvars; var++) {
            //different crossPoint for each var
            crosspoint = i_dist(rng);
//            printf("Crosspoint = %d\n",crosspoint);
            for (int cross = 0; cross < chrom_length; cross++) {
//        printf("NGENES = %d\n",ngenes);
                //calculate gene number
                gene = (var*16)+cross;
                if (cross <= crosspoint) {
                    pop[popNum][child].set_gene(gene, pop[prevPop][ran1].get_gene(gene));
                    pop[popNum][child + 1].set_gene(gene, pop[prevPop][ran2].get_gene(gene));
                } else {
                    pop[popNum][child].set_gene(gene, pop[prevPop][ran2].get_gene(gene));
                    pop[popNum][child + 1].set_gene(gene, pop[prevPop][ran1].get_gene(gene));
                }
            }
        }

        //add to or create genealogy
        child_origin[0] = "child of parents " + std::to_string(ran1) + " & " + std::to_string(ran2) + " Generation: " + std::to_string(generation);
//        std::cout<<child_origin[0]<<std::endl;
        pop[popNum][child].rewrite_resize_origin(child_origin);
        pop[popNum][child+1].rewrite_resize_origin(child_origin);
    }
}
void BinGA::global_crossover()
{
    int prevPop = ((popNum+1)%2);
    int ran1, ran2, crosspoint;
    std::uniform_int_distribution<int> i_dist(1, ngenes-2);
    std::mt19937 rng;
    rng.seed(std::random_device{}());

    std::vector<std::string> child_origin;
    child_origin.push_back(" ");
    std::ostringstream os;
    for(int child = nelites; child < ncross+nelites; child+=2){
        crosspoint = i_dist(rng);
        ran1 = rouletteWheel();
        ran2 = rouletteWheel();

        while(ran1 == ran2){
            ran2 = rouletteWheel();
        }
        for(int cross = 0; cross < ngenes; cross++){

            if(cross <= crosspoint){
                pop[popNum][child].set_gene(cross, pop[prevPop][ran1].get_gene(cross));
                pop[popNum][child+1].set_gene(cross, pop[prevPop][ran2].get_gene(cross));
            }
            else{
                pop[popNum][child].set_gene(cross, pop[prevPop][ran2].get_gene(cross));
                pop[popNum][child+1].set_gene(cross, pop[prevPop][ran1].get_gene(cross));
            }
        }

        //add to or create genealogy
        child_origin[0] = "child of parents " + std::to_string(ran1) + " & " + std::to_string(ran2) + " Generation: " + std::to_string(generation);
        pop[popNum][child].rewrite_resize_origin(child_origin);
        pop[popNum][child+1].rewrite_resize_origin(child_origin);
    }
}

void BinGA::memAssist_global_crossover()
{
    int prevPop = ((popNum+1)%2);
    double max = 100.0;
    //parent1 parent2
    int p1, p2, crosspoint;
    std::uniform_int_distribution<int> i_dist(1, ngenes-2);
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    //normal children
    BinChromosome p1p2, p2p1;
    //memAssist freaks
    BinChromosome k1p1, k1p2, p1k2, p2k2;
    //collection
    std::vector<BinChromosome> temp(6, BinChromosome (nvars, min, max, chrom_length) );


//    std::vector<std::string> child_origin;
//    child_origin.push_back(" ");
//    std::ostringstream os;
    for(int child = nelites; child < ncross+nelites; child+=2){

        crosspoint = i_dist(rng);
        //normal parents
        p1 = rouletteWheel();
        p2 = rouletteWheel();
        //mem assist

        /*
         * Set up all possible children
         */
        p1p2 = BinChromosome (nvars, min, max, chrom_length);
        p2p1 = BinChromosome (nvars, min, max, chrom_length);
        k1p1 = BinChromosome (nvars, min, max, chrom_length);
        k1p2 = BinChromosome (nvars, min, max, chrom_length);
        p1k2 = BinChromosome (nvars, min, max, chrom_length);
        p2k2 = BinChromosome (nvars, min, max, chrom_length);

        while(p1 == p2){
            p2 = rouletteWheel();
        }

        for(int cross = 0; cross < ngenes; cross++){

            /*
             * Fill in upper
             */
            if(cross <= crosspoint){

                p1p2.set_gene(cross, pop[prevPop][p1].get_gene(cross));
                p2p1.set_gene(cross, pop[prevPop][p2].get_gene(cross));

                k1p1.set_gene(cross, memAssist.lower[crosspoint].get_gene(cross));
                k1p2.set_gene(cross, memAssist.lower[crosspoint].get_gene(cross));

                p1k2.set_gene(cross, pop[prevPop][p1].get_gene(cross));
                p2k2.set_gene(cross, pop[prevPop][p2].get_gene(cross));
            } else{
               /*
                * Fill in lower
                */
                p1p2.set_gene(cross, pop[prevPop][p2].get_gene(cross));
                p2p1.set_gene(cross, pop[prevPop][p1].get_gene(cross));

                k1p1.set_gene(cross, pop[prevPop][p1].get_gene(cross));
                k1p2.set_gene(cross, pop[prevPop][p2].get_gene(cross));

                p1k2.set_gene(cross, memAssist.upper[crosspoint].get_gene(cross));
                p2k2.set_gene(cross, memAssist.upper[crosspoint].get_gene(cross));
            }
        }

        temp[0] = p1p2;
        temp[1] = p2p1;
        temp[2] = k1p1;
        temp[3] = k1p2;
        temp[4] = p1k2;
        temp[5] = p2k2;

        /*
         * calc vars
         */
        temp[0].calcVar(chrom_length, max);
        temp[1].calcVar(chrom_length, max);
        temp[2].calcVar(chrom_length, max);
        temp[3].calcVar(chrom_length, max);
        temp[4].calcVar(chrom_length, max);
        temp[5].calcVar(chrom_length, max);


        /*
         * get xarray input
         */
        setMemFit(temp, 6);

        std::vector<BinChromosome> memEntries(6, BinChromosome (nvars, min, max, chrom_length) );
        memEntries = temp;
        //Sort for mins
        //using default comparison operator (<)
        std::sort (temp.begin(), temp.begin()+6);

        int rank[2];
        for(int i = 0; i < 2; i++){
            /*
             * Identify the original entry rank before sorting
             */
            for(int j = 0; j < 6; j++){
                if((std::abs(temp[i].getFitness() - memEntries[j].getFitness())) < .00001){
                    rank[i] = j;
                }
            }
        }

        /*
         * Insert best candidates into Population
         */

        pop[popNum][child] = temp[0];
        pop[popNum][child+1] = temp[1];

        /*
         * Find out what genes the upper and lower should be
         */
        int lower, upper;
        lower = 0;
        upper = 0;
        //naive, make rank[0] be upper and rank[1] be lower unless upper = lower
        if(rank[0] == 0){
            if((rank[1] == 1) || (rank[1] == 2)){
                //then memEntries[0] is upper and lower
                upper = 0;
                lower = 0;
            }
            else{
                upper = 0;
                lower = rank[1];
            }
        }
        else if(rank[0] == 1){
            if((rank[1] == 3) || (rank[1] == 5)){
                //then memEntries[0] is upper and lower
                upper = 1;
                lower = 1;
            }
            else{
                upper = 1;
                lower = rank[1];
            }
        }
        else if(rank[0] == 2){
            if(rank[1] == 3){
                //then memEntries[0] is upper and lower
                upper = 2;
                lower = 2;
            }
            else{
                upper = 2;
                lower = rank[1];
            }
        }
        else if(rank[0] == 3){
            if(rank[1] == 2){
                //then memEntries[0] is upper and lower
                upper = 3;
                lower = 3;
            }
            else{
                upper = 3;
                lower = rank[1];
            }
        }
        else if(rank[0] == 4){
            if(rank[1] == 0){
                //then memEntries[0] is upper and lower
                lower = 4;
                upper = 4;
            }
            else{
                upper = 4;
                lower = rank[1];
            }
        }
        else if(rank[0] == 5){
            if(rank[1] == 1){
                //then memEntries[0] is upper and lower
                lower = 5;
                upper = 5;
            }
            else{
                upper = 5;
                lower = rank[1];
            }
        }

        for(int cross = 0; cross < ngenes; cross++){
            if(cross <= crosspoint){
                memAssist.upper[crosspoint].set_gene(cross, memEntries[lower].get_gene(cross));
            } else{
                memAssist.lower[crosspoint].set_gene(cross, memEntries[upper].get_gene(cross));
            }
        }

//        pop[popNum][child] = temp[i]
//        pop[popNum][child+1] = temp[i]
        /*
         *                       A       B      ifA      | ifB
         * 1st: Compare values [k1p1 V k1p2 V [A V p2p1  | B V p1p2]
         *                       C      D      if(A&C)      if(B&C)   if(-A&C)
         * 2nd: Compare values [p1k2 V p2k2 V [ C V p2p1 | C V p1p2 | ...
         */



//        if(temp[1] < temp[0]){
//            std::swap(temp[1], temp[0]);
//        }
//        if(temp[3] < temp[2]){
//            std::swap(temp[3], temp[2]);
//        }
//        if(temp[5] < temp[4]){
//            std::swap(temp[5], temp[4]);
//        }
//
//        if(temp[0] < temp[2]){
//
//        }

//     0   p1p2.calcVar(chrom_length, max);
//     1   p2p1.calcVar(chrom_length, max);
//     2   k1p1.calcVar(chrom_length, max);
//     3   k1p2.calcVar(chrom_length, max);
//     4   p1k2.calcVar(chrom_length, max);
//     5   p2k2.calcVar(chrom_length, max);

//        if((temp[2] < temp[3]) && (temp[2] < temp[1])){
//            pop[popNum][child] = temp[2];
//            /*
//             * Need to update mem struct
//             */
//            if(temp[0] < temp[1]) {
//                if ((temp[4] < temp[5]) && (temp[4] < temp[0])) {
//                    pop[popNum][child + 1] = temp[4];
//                } else if ((temp[4] < temp[5]) && (temp[0] < temp[4])) {
//                    pop[popNum][child + 1] = temp[0];
//                } else if ((temp[5] < temp[4]) && (temp[5] < temp[0])) {
//                    /*
//                     * this comparison doesnt seem to follow the pattern
//                     */
//                    pop[popNum][child + 1] = temp[5];
//                } else if ((temp[5] < temp[4]) && (temp[0] < temp[5])) {
//                    /*
//                     * Ditto above
//                     */
//                    pop[popNum][child + 1] = temp[0];
//                } else {
//                    printf("Error in comparison of temps for memAssist crossover\n");
//                    exit(0);
//                }
//            }
//            else{
//                if ((temp[4] < temp[5]) && (temp[4] < temp[0])) {
//                    pop[popNum][child + 1] = temp[4];
//                } else if ((temp[4] < temp[5]) && (temp[0] < temp[4])) {
//                    pop[popNum][child + 1] = temp[0];
//                } else if ((temp[5] < temp[4]) && (temp[5] < temp[1])) {
//                    /*
//                     * this comparison doesnt seem to follow the pattern
//                     */
//                    pop[popNum][child + 1] = temp[5];
//                } else if ((temp[5] < temp[4]) && (temp[1] < temp[5])) {
//                    /*
//                     * Ditto above
//                     */
//                    pop[popNum][child + 1] = temp[1];
//                } else {
//                    printf("Error in comparison of temps for memAssist crossover\n");
//                    exit(0);
//                }
//            }
//        }
//        else if((temp[2] < temp[3]) && (temp[1] < temp[2])){
//            pop[popNum][child] = temp[1];
//            if(( temp[4] < temp[5] ) && (temp[4] < temp[0])){
//                pop[popNum][child+1] = temp[4];
//            }
//            else if(( temp[4] < temp[5] ) && (temp[0] < temp[4])){
//                pop[popNum][child+1] = temp[0];
//            }
//            else if(( temp[5] < temp[4] ) && (temp[5] < temp[0])){
//                /*
//                 * this comparison doesnt seem to follow the pattern
//                 */
//                pop[popNum][child+1] = temp[5];
//            }
//            else if(( temp[5] < temp[4] ) && (temp[0] < temp[5])){
//                /*
//                 * Ditto above
//                 */
//                pop[popNum][child+1] = temp[0];
//            } else{
//                printf("Error in comparison of temps for memAssist crossover\n");
//                exit(0);
//            }
//        }
//        else if((temp[3] < temp[2]) && (temp[3] < temp[0])){
//            pop[popNum][child] = temp[3];
//            if(( temp[4] < temp[5] ) && (temp[4] < temp[0])){
//                pop[popNum][child+1] = temp[4];
//            }
//            else if(( temp[4] < temp[5] ) && (temp[0] < temp[4])){
//                pop[popNum][child+1] = temp[0];
//            }
//            else if(( temp[5] < temp[4] ) && (temp[5] < temp[0])){
//                /*
//                 * this comparison doesnt seem to follow the pattern
//                 */
//                pop[popNum][child+1] = temp[5];
//            }
//            else if(( temp[5] < temp[4] ) && (temp[0] < temp[5])){
//                /*
//                 * Ditto above
//                 */
//                pop[popNum][child+1] = temp[0];
//            } else{
//                printf("Error in comparison of temps for memAssist crossover\n");
//                exit(0);
//            }
//        }
//        else if((temp[3] < temp[2]) && (temp[0] < temp[2])){
//            pop[popNum][child] = temp[0];
//            if(( temp[4] < temp[5] ) && (temp[4] < temp[0])){
//                pop[popNum][child+1] = temp[4];
//            }
//            else if(( temp[4] < temp[5] ) && (temp[0] < temp[4])){
//                pop[popNum][child+1] = temp[0];
//            }
//            else if(( temp[5] < temp[4] ) && (temp[5] < temp[0])){
//                /*
//                 * this comparison doesnt seem to follow the pattern
//                 */
//                pop[popNum][child+1] = temp[5];
//            }
//            else if(( temp[5] < temp[4] ) && (temp[0] < temp[5])){
//                /*
//                 * Ditto above
//                 */
//                pop[popNum][child+1] = temp[0];
//            } else{
//                printf("Error in comparison of temps for memAssist crossover\n");
//                exit(0);
//            }
//        } else{
//            printf("Error in comparison of temps for memAssist crossover\n");
//            exit(0);
//        }




//        //add to or create genealogy
//        child_origin[0] = "child of parents " + std::to_string(ran1) + " & " + std::to_string(ran2) + " Generation: " + std::to_string(generation);
//        std::cout<<child_origin[0]<<std::endl;
//        pop[popNum][child].rewrite_resize_origin(child_origin);
//        pop[popNum][child+1].rewrite_resize_origin(child_origin);
    }
}


/*
 * Quicksort
 */
void BinGA::sort(int p, int q)
{
    int r;
    if(p<q)
    {
        r = partition(p,q);
        sort(p,r);
        sort(r+1, q);
    }
}

int BinGA::partition(int p, int q)
{
    double x = pop[popNum][p].getFitness();
    int i = p;
    int j;

    for(j = p+1; j<q; j++)
    {
        if(pop[popNum][j].getFitness() <= x)
        {
            i = i + 1;
            std::swap(pop[popNum][i], pop[popNum][j]);
        }
    }

    std::swap(pop[popNum][i], pop[popNum][p]);
    return i;
}

void BinGA::mutate(int mutations)
{
    int ran_gene, ran_chrom, gene_val;
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::string add_origin;
    for(int i = 0; i < nmute; i++) {
        std::uniform_int_distribution<int> i_dist(nelites, nchroms-1);
        ran_chrom = i_dist(rng);
        i_dist = std::uniform_int_distribution<int> (0,ngenes-1);
        for(int j = 0; j < mutations; j++){
            ran_gene = i_dist(rng);
            gene_val = pop[popNum][ran_chrom].get_gene(ran_gene);
            gene_val = (gene_val+1)%2;
            pop[popNum][ran_chrom].set_gene(ran_gene, gene_val);

//            add_origin = "Gene [";
//            add_origin += std::to_string(ran_gene);
        }
        add_origin += "Mutated Generation: " + std::to_string(generation);
        pop[popNum][ran_chrom].push_to_origin(add_origin);
    }
}

void BinGA::createNew()
{
    int newChrom = nchroms - (nelites + ncross);
    std::vector<std::string> new_origin;
    new_origin.push_back("New Chrom created in Generation: " + std::to_string(generation));
//    printf("New Chroms = %d\n",newChrom);
    int index = 0;
    for(int i = 0; i < newChrom; i++){
        index = nchroms - 1 - i;
        pop[popNum][index] = BinChromosome(nvars, min, max,chrom_length);
        pop[popNum][index].rewrite_resize_origin(new_origin);
//        printf("Index = %d\n",index);
    }

}

void BinGA::returnInput(double *x)
{
    double temp;
    int count;
    count = 0;
    for(int i = 0; i < nchroms; i++){
        for(int j = 0; j < nvars; j++){
            temp = pop[popNum][i].getvar(j);
            x[count] = temp;
            count++;
        }
    }
}

void BinGA::setMemFit(std::vector<BinChromosome>& temp, int chroms)
{
    double val;
    double *x, *f;
    x=(double *)malloc(chroms*nvars*sizeof(double));
    f=(double *)malloc(sizeof(double)  *  chroms);

    int count;
    count = 0;
    for(int i = 0; i < chroms; i++){
        for(int j = 0; j < nvars; j++){
            val = temp[i].getvar(j);
            x[count] = val;
            count++;
        }
    }

    cec17_test_func(x, f, nvars, chroms, func_num);
    temp[0].setFitness(f[0]);
    temp[1].setFitness(f[1]);
    temp[2].setFitness(f[2]);
    temp[3].setFitness(f[3]);
    temp[4].setFitness(f[4]);
    temp[5].setFitness(f[5]);

    free(x);
    free(f);

}



void BinGA::calcVars(int chrom_length, double max){
    for(int i = 0; i < nchroms; i++){
        pop[popNum][i].calcVar(chrom_length, max);
    }
}


void BinGA::iteration()
{

}
