FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    libc6-dev \
    libglib2.0-dev \
    cmake \
    cppcheck \
    doxygen \
    valgrind \
    python3 \
    python3-pip \
    netcat-openbsd \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*