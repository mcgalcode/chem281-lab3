#ifndef REACTION_H
#define REACTION_H

#include <vector>
#include <string>

struct Reaction {
    std::vector<int> reactants;
    std::vector<int> products;
    double rate;
};

struct ReactionResult {
    std::vector<std::vector<int>> amounts;
    std::vector<float> times;
    std::vector<std::string> specieNames;
};

#endif