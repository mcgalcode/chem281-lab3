#include <cmath>
#include <vector>
#include "reaction.h"
#include <random>
#include <nlohmann/json.hpp>
#include <fstream>


int nChooseK(int n, int k) {
    if (k > n) return 0;
    if (k == 0) return 1;

    long result = n;
    for (int i = 2; i <= k; i++) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
};

float calculateReactionPropensity(std::vector<int>& specieCounts, Reaction reaction) {
    /*
    * This function should calculate the "propensity", or likelihood of
    * the reaction occuring. It combines the number of each species, and the rate of the reaction
    * This value is computed by finding the number of possible combinations of each reactant particle
    * that could be picked out of the current mixture.
    * 
    * For example:
    * 
    * If our beaker has 10 A particles and 15 B particles,
    * and we are calculating the propensity for this reaction:
    * 
    * 2 A + 1 B -> C, k = 0.03
    *
    * The propensity will be 
    * 
    * (10 choose 2) * (15 choose 1) * 0.03
    * 
    * In general, for a mixture of N A particles and M B particles
    * a reaction with the following form:
    * 
    * x A + y B -> C, k = 0.03
    * 
    * Will have a propensity of:
    * 
    * (N choose x) * (M choose y) * k
    * 
    * Use the nChooseK helper function!
    */
    float propensity = reaction.rate;
    std::vector<int> reactants = reaction.reactants;
    for (int i = 0; i < reactants.size(); i++) {
        int particlesInReaction = reactants[i];
        if (particlesInReaction != 0) {
            int count = specieCounts[i];
            propensity *= nChooseK(count, particlesInReaction);
        }
    }
    return propensity;
};

double randomDouble(double min, double max) {
    static std::random_device rd;  // Obtain a random number from hardware
    static std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(min, max); // Define the range

    return distr(gen); // Generate numbers
};

std::vector<int> computeNewSpecieCounts(const std::vector<int>& oldSpecieCounts, Reaction reaction) {
    // Given a reaction and the current species counts, this function should return
    // the new specie counts after the reaction happens once
    
    int numSpecies = oldSpecieCounts.size();
    std::vector<int> newSpecieCounts{};

    for (int i = 0; i < numSpecies; i++) {
        int specieCount = oldSpecieCounts[i] - reaction.reactants[i] + reaction.products[i];
        newSpecieCounts.push_back(specieCount);
    }

    return newSpecieCounts;
};

float computeTimeInterval(float alpha0, float tau) {
    // This function should compute the time interval per
    // Eqn. 21a in the Gillespie paper
    return 1 / totalPropensity * log(1 / tau);
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReactionResult, amounts, times, specieNames)

void writeResult(ReactionResult r, std::string filename) {
    // Convert vector to JSON
    nlohmann::json j = r;

    // Write JSON to file
    std::ofstream file(filename);
    file << j.dump(4);
    file.close();    
}