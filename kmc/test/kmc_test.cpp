#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "kmc_utilities.h"
#include "reaction.h"
#include "kmc.h"

TEST(KMCUtilities, nChooseKAssertions) {
  int val = nChooseK(2, 1);
  EXPECT_EQ(val, 2);
  
  int val2 = nChooseK(3, 2);
  EXPECT_EQ(val2, 3);

  int val3 = nChooseK(10, 5);
  EXPECT_EQ(val3, 252);

  int val4 = nChooseK(1000, 3);
  EXPECT_EQ(val4, 166167000);

  int val5 = nChooseK(10, 2);
  EXPECT_EQ(val5, 45);

  int val6 = nChooseK(15, 1);
  EXPECT_EQ(val6, 15);
}

TEST(KMCUtilities, calculateReactionPropensityAssertions) {
  std::vector<int> reactants {1, 1, 0};
  std::vector<int> products {0, 0, 2};

  Reaction r;
  r.reactants = reactants;
  r.products = products;
  r.rate = 2.0;

  std::vector<int> specieCounts1 {100, 100, 0};
  float p = calculateReactionPropensity(specieCounts1, r);
  EXPECT_EQ(p, 20000);

  std::vector<int> reactants2 {2, 1, 0};
  std::vector<int> products2 {0, 0, 3};
  Reaction r2;
  r2.reactants = reactants2;
  r2.products = products2;
  r2.rate = 2.0;

  std::vector<int> specieCounts2 {10, 15, 0};
  float p2 = calculateReactionPropensity(specieCounts2, r2);
  EXPECT_EQ(p2, 45 * 15 * 2.0);
}

TEST(KMCUtilities, computeNewSpecieCounts) {
  std::vector<int> startingCounts = {100, 100, 10};

  std::vector<int> reactants {1, 1, 0};
  std::vector<int> products {0, 0, 2};

  Reaction r;
  r.reactants = reactants;
  r.products = products;
  r.rate = 2.0;

  std::vector<int> reactants2 {2, 1, 0};
  std::vector<int> products2 {0, 0, 3};
  Reaction r2;
  r2.reactants = reactants2;
  r2.products = products2;
  r2.rate = 2.0;

  std::vector<int> c1 = computeNewSpecieCounts(startingCounts, r);
  EXPECT_EQ(c1[0], 99);
  EXPECT_EQ(c1[1], 99);
  EXPECT_EQ(c1[2], 12);
  EXPECT_EQ(c1.size(), startingCounts.size());

  std::vector<int> c2 = computeNewSpecieCounts(c1, r2);
  EXPECT_EQ(c2[0], 97);
  EXPECT_EQ(c2[1], 98);
  EXPECT_EQ(c2[2], 15);
  EXPECT_EQ(c1.size(), c2.size());
}

TEST(KMCUtilities, computeTimeInterval) {
  float propTotal = 5;
  float tau = 0.2;
  EXPECT_NEAR(computeTimeInterval(propTotal, tau), 0.3218875825, 0.000001);
}

TEST(KMCUtilities, jsonWriting) {
  std::vector<int> frame1 {100, 100, 10};
  std::vector<int> frame2 {90, 95, 20};
  std::vector<float> times {0.2, 0.5, 0.8};

  std::vector<std::string> { "A", "B", "C" };

  ReactionResult r { {frame1, frame2}, times };

  std::string fname {"output.json"};
  writeResult(r, fname);
}

TEST(KMCMain, RunSimulation) {
  std::vector<int> reactants {1, 1, 0};
  std::vector<int> products {0, 0, 2};

  Reaction r;
  r.reactants = reactants;
  r.products = products;
  r.rate = 1.0;

  std::vector<std::string> specieNames {"A", "B", "C"};
  std::vector<int> startingCounts {100, 100, 10};

  KMC kmc(specieNames, startingCounts);

  kmc.addReaction(r);

  ReactionResult result = kmc.run(1);
}