FROM debian:11.0

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
RUN apt-get -y install gcovr
RUN apt-get -y install clang-tidy-11
RUN apt-get -y install cppcheck
RUN apt-get -y install clang-format-11
RUN apt-get -y install python3-pip
RUN pip3 install lizard
RUN apt-get -y install xsltproc
RUN apt-get -y install git
RUN apt-get -y install ssh



ENV CC=/usr/bin/gcc-10
ENV CXX=/usr/bin/g++-10
ENV CLANG_TIDY=/usr/bin/clang-tidy-11

# RUN cd /
# RUN mkdir /quicklog

COPY . /quicklog/

# ENTRYPOINT touch entrypointwashere