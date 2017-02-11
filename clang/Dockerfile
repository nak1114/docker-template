FROM ubuntu

RUN set -x && \
    apt-get update && \
    apt-get install -y make cmake gcc g++ python libtool zlib1g zlib1g-dev subversion && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    cd / && \
    mkdir llvm && \
    cd /llvm && \
    svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm && \
    cd /llvm/llvm/tools && \
    svn co http://llvm.org/svn/llvm-project/cfe/trunk clang && \
    cd /llvm/llvm/tools/clang/tools && \
    svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra && \
    cd /llvm/llvm/projects && \
    svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt && \
    cd /llvm && \
    mkdir build && \
    cd build && \
    cmake -G "Unix Makefiles" ../llvm/ -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release && \
    make -j$(grep processor /proc/cpuinfo | wc -l) REQUIRES_RTTI=1 && \
    make install && \
    cd / && \
    rm -rf llvm

ENTRYPOINT ["/bin/bash"]
