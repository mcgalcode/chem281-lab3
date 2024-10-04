# CHEM 281 Lab 3

## Orientation

Welcome to another week of CHEM 281 lab! This week we will be exploring Monte Carlo simulations, a topic we briefly visited in the homework. While this is a truly massive class of programs spanning fields as diverse as finance, applied math, sociology and physics, we will be focusing in this programming exercise on **kinetic Monte Carlo** (also called, _dynamic_ Monte Carlo), or **kMC** methods.

The premise behind any Monte Carlo method is to produce a set of samples whose distribution matches a probability distribution that may be hard to determine analytically. As far as chemistry is concerned, this often corresponds to producing samples snapshots of some system (perhaps a bond whose energy varies harmonically as a function of length) and using statistics about those samples to calculate physical features of the system (average energy, average length in our stretching bond example).

Kinetic Monte Carlo introduces the notion of _time_ to this framework. Originally introduced by Gillespie in the 1970s, kinetic Monte Carlo algorithms use rate constants to produce trajectories that explore the state space for some system. To be concrete, imagine a beaker containing a solution of molecules of types A and B which react according to the following process:

```
A + 2B -> C
```

Associated with this process is rate constant _k<sub>1</sub>_.

Similarly, the backward process,

```
C -> A + 2B
```

is associated with a different rate constant, _k<sub>2</sub>_.

As the beaker sits, both of these reactions occur with their respective rates (though these rates are attenuated by the concentrations of the particles - even if a reaction is fast, it can't occur if there are no reactants!), and eventually reaches some equilibrium state.

The kinetic Monte Carlo algorithm provides a method for us to investigate the time-dependent concentrations of these molecules - in other words, we can simulate a chemical reaction proceeding.

### Goals

The goal of this lab is to allow you to experiment with a kMC simulation. In this repository, a simple kMC code is implemented. Or... it almost is. You'll find it's a bit broken and incomplete. Fortunately you for you, there is a test suite that can help you fix the codebase and start your experiments.

## 0. Set up your development environment

A Dockerfile containing all of the tools and dependencies you need for this project is included here. Use `build_image.sh` to build the image. From there, you should be able to use `interactive.sh` to run a container with an interactive terminal.

## 1. Investigate test failures

The code here runs, but it looks like there are some failing tests. To see them, you'll need to compile the code and run the test executable. To do this, open an interactive session in your development container, then follow the usual method:

```
mkdir build
cd build
cmake ..
make
```

This command built two executable targets: `Main` and `KMCTest`. You should see them in the build directory.

Run `KMCTest` and check out the failures.

## 2. Fix the tests by implementing the kMC algorithm as described in the Gillespie paper

In order to fix the tests for this piece of code, you'll need to understand the data structures used in this simulation.

We think of the species involved as belonging to a list (you define this using the `speciesNames` parameter to the `KMC` constructor). For example, our species might be:

```
["A", "B", "C"]
```

At any given point in the simulation, we keep track of how many particles of each species exist. This takes the form of a `std::vector<int>`. The position of each value in the list tells you which species it refers to. For example:

```
[100, 100, 10]
```

Would refer to 100 A particles, 100 B particles, and 10 C particles.

Finally, reactions are represented by `Reaction` structs, which have fields `reactants`, `products`, `rate`.

For example:

```
Reaction r {
    {1, 1, 0}, // the reactant stoichiometry
    {0, 0, 2}, // the product stoichiometry
    0.05 // the rate
}
```

corresponds to the reaction:

```
A + B -> 2C, k = 0.05
```

The first parameter, `{1, 1, 0}` refers to the reactants. This means that this reaction consumes 1 A and 1 B particle and 0 C particles. Similarly, it produces 2 C particles, and its rate is 0.05.


## 3. 

