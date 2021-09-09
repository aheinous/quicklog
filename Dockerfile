FROM debian

RUN apt-get update
RUN apt-get -y install make
RUN apt-get -y install wget
RUN DEBIAN_FRONTEND=noninteractive apt-get  install apt-utils
# RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get -y install gcc-10
RUN apt-get -y install g++-10
RUN mkdir /opt/cmake
RUN cd /opt/cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.21.2/cmake-3.21.2-linux-x86_64.sh
RUN chmod +x cmake-3.21.2-linux-x86_64.sh
RUN ./cmake-3.21.2-linux-x86_64.sh --skip-license
RUN apt-get -y install ninja-build
RUN apt-get -y install clang-11

ENV CC=/usr/bin/gcc-10
ENV CXX=/usr/bin/g++-10

# RUN cd /
# RUN mkdir /quicklog

COPY . /quicklog/

# ENTRYPOINT touch entrypointwashere