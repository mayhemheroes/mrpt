FROM --platform=linux/amd64 ubuntu:18.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential pkg-config cmake libwxgtk3.0-dev libwxgtk3.0-gtk3-dev libopencv-dev libeigen3-dev zlib1g-dev libsuitesparse-dev libjpeg-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev freeglut3-dev libassimp-dev libglfw3-dev \
    libglu1-mesa-dev libqt5opengl5-dev qtbase5-dev \
    libxrandr-dev libxxf86vm-dev clang-10

COPY . /repo
WORKDIR /repo/build
RUN cmake .. -DCMAKE_INSTALL_PREFIX=/install
RUN make -j8
RUN make install
RUN clang++-10 /repo/mayhem/fuzz_trim.cpp -fsanitize=fuzzer,address -I /install/include/mrpt/system/include/mrpt/system/ /install/lib/libmrpt*.so -std=c++17 -o /fuzz

FROM ubuntu:18.04 as package
COPY --from=builder /install /install
COPY --from=builder /fuzz /fuzz_trim
ENV LD_LIBRARY_PATH=/install/lib
