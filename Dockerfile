# Check http://releases.llvm.org/download.html#10.0.0 for the latest available binaries
FROM ubuntu:20.04

# Make sure the image is updated, install some prerequisites,
# Download the latest version of Clang (official binary) for Ubuntu
# Extract the archive and add Clang to the PATH
# See https://github.com/llvm/llvm-project/releases/
RUN apt-get update && apt-get install -y \
    xz-utils \
    build-essential \
    curl \
    && rm -rf /var/lib/apt/lists/* \
    && curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.0/clang+llvm-13.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz \
    | tar -xJC . && \
    mv clang+llvm-13.0.0-x86_64-linux-gnu-ubuntu-20.04 clang_13.0.0 && \
    echo 'export PATH=/clang_13.0.0/bin:$PATH' >> ~/.bashrc && \
    echo 'export LD_LIBRARY_PATH=/clang_13.0.0/lib:$LD_LIBRARY_PATH' >> ~/.bashrc 

# install cmake, ninja, and clang-tidy
RUN apt-get update && apt-get install -y \
    cmake \
    ninja-build \
    clang-tidy \
    && rm -rf /var/lib/apt/lists/*
    
# Start from a Bash prompt
CMD [ "/bin/bash" ]