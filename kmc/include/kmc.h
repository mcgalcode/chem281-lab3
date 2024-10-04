#ifndef KMC_H
#define KMC_H

#include <vector>
#include <string>
#include "reaction.h"

class KMC {
public:
    // Public member variables
    std::vector<int> particleCounts;
    std::vector<std::string> speciesNames;
    std::vector<Reaction> reactions;

    // Public member functions
    KMC(const std::vector<std::string>& speciesNames,
        const std::vector<int>& particleCounts);
    
    void print();

    void addReaction(const Reaction& reaction);

    ReactionResult run(float duration);
};

#endif // KMC_H