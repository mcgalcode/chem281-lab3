FROM ubuntu:22.04

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install essential packages

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    cmake \
    lcov \
    mpich \
    libmpich-dev \
    nlohmann-json3-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up a working directory
WORKDIR /workspace

# Set the default command to bash
CMD ["/bin/bash"]