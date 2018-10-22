FROM debian:stable-slim

# Keyboard and layout can be defined at build time...
ARG buildKeyboard=ergodox_ez
ARG buildLayout=default
# ...or at runtime
ENV keyboard=$buildKeyboard
ENV layout=$buildLayout

# Install QMK prerequisites
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    gcc unzip \
    wget \
    zip \
    gcc-avr \
    binutils-avr \
    avr-libc \
    dfu-programmer \
    dfu-util \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi \
    make \
    git-core && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Clone the QMK repo & make submodules
RUN cd / && git clone https://github.com/qmk/qmk_firmware.git && cd /qmk_firmware && make git-submodule

# Create the output directory
RUN mkdir /output

# Add our run script
COPY run.sh /

# Command to use when running this container
WORKDIR /qmk_firmware
CMD /run.sh
