#ifndef KMC_UTILITIES_H
#define KMC_UTILITIES_H

#include <vector>
#include "reaction.H"
#include <string>

int nChooseK(int n, int k);
float calculateReactionPropensity(std::vector<int>& specieCounts, Reaction reaction);
double randomDouble(double min, double max);

float computeTimeInterval(float totalPropensity, float tau);
std::vector<int> computeNewSpecieCounts(const std::vector<int>& oldSpecieCounts, Reaction reaction);
void writeResult(ReactionResult v, std::string);

#endif