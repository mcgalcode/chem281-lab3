#include <iostream>
#include "kmc.h"
#include "kmc_utilities.h"
#include <vector>
#include <string>

int main(int argc, char* argv[]) {

    // Name the species and establish their order for this reaction simulation
    std::vector<std::string> specieNames {"A", "B", "C"};
    
    // Define the reactions that can occur in our simulation
    std::vector<Reaction> reactions = {
        {
            {1, 1, 0},
            {0, 0, 2},
            0.05
        }
    };

    // Choose starting counts for each specie
    std::vector<int> startingCounts {1000, 1000, 0};

    // Instaniate the simulation class
    KMC kmc(specieNames, startingCounts);

    // Add all of our reactions to the simulation
    for (int i = 0; i < reactions.size(); i++) {
        kmc.addReaction(reactions[i]);
    }

    // Run the simulation for a time interval of 0.1s
    ReactionResult result = kmc.run(0.1);

    // Select a filename
    std::string outputFname {"out.json"};

    // Write the simulation results to that file
    writeResult(result, outputFname);

}