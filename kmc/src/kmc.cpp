#include <random>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <numeric>


#include "kmc.h"
#include "kmc_utilities.h"
/**
 * First, we provide a list of our species names:
 * 
 * ["A", "B", "C"]
 * 
 * Next, define the reactions that can occur. A reaction is given by
 * two vectors of length num_species.
 * 
 * For example, to encode the reaction
 * 
 * A + 2B -> C
 * 
 * We can use the vector representation for the reactants:
 * 
 * std::vector<float> reactants {1, 2, 0}
 * std::vector<float> products {0, 0, 1}
 * 
 */

KMC::KMC(const std::vector<std::string>& speciesNames,
         const std::vector<int>& particleCounts)
    : speciesNames(speciesNames),
      particleCounts(particleCounts) {}

void KMC::print() {
    std::cout << "Species Counts:\n";
    std::cout << std::setw(15) << "Species" << std::setw(10) << "Count\n";
    std::cout << std::string(25, '-') << "\n";  // Separator line
    
    for (size_t i = 0; i < speciesNames.size(); ++i) {
        std::cout << std::setw(15) << speciesNames[i] 
                  << std::setw(10) << particleCounts[i] << "\n";
    }
}

void KMC::addReaction(const Reaction& reaction) {
    reactions.push_back(reaction);
};

ReactionResult KMC::run(float duration) {
    // We will accumulate the time points here
    std::vector<float> times {0};
    // And the counts as the species react here
    std::vector<std::vector<int>> specieCounts {};
    specieCounts.push_back(particleCounts);

    while (times.back() < duration) {
        std::vector<int> currentCounts = specieCounts.back();
        std::vector<float> propensities{};

        for (int i = 0; i < reactions.size(); i++) {
            Reaction r = reactions[i];
            float rPropensity = calculateReactionPropensity(currentCounts, r);
            propensities.push_back(rPropensity);
        }

        // Sum up the propensities
        float alpha0 = std::accumulate(propensities.begin(), propensities.end(), 0.0);
        
        // Generate random val for selecting time
        // Generate random val for selecting reaction
        float tau = randomDouble(0, 1.0);
        float mu = randomDouble(0, 1.0);
        
        // Using propensities, choose a reaction
        float runningPropensityTotal = 0;
        int selectedRxnIdx;
        for (int i = 0; i < propensities.size(); i++) {
            float p = propensities[i];
            float marker = mu * alpha0;
            if (marker >= runningPropensityTotal && marker < runningPropensityTotal + p) {
                selectedRxnIdx = i;
                break;
            }
            runningPropensityTotal += p;
        }

        Reaction selectedReaction = reactions[selectedRxnIdx];

        // Using time value, select a time interval
        float elapsedInterval = computeTimeInterval(alpha0, tau);

        // Using the reaction and the old specie counts, get the new species counts
        std::vector<int> newCounts = computeNewSpecieCounts(currentCounts, selectedReaction);
        
        // Update reaction state
        specieCounts.push_back(newCounts);
        times.push_back(times.back() + elapsedInterval);
    }
    ReactionResult result {
        specieCounts,
        times,
        speciesNames
    };
    return result;
}