FROM gcc:14

RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
    cmake \
    gdb \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["/bin/bash"]
