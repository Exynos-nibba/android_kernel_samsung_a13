#!/bin/bash

export CROSS_COMPILE=$(pwd)/../gas/bin/aarch64-linux-gnu-
export CC=$(pwd)/../clang/bin/clang
export CLANG_TRIPLE=aarch64-linux-gnu-
export PATH=$(pwd)/../clang/bin:$PATH
export PATH=$(pwd)/../gas/bin:$PATH
export ARCH=arm64
export ANDROID_MAJOR_VERSION=r

export KCFLAGS=-w
export CONFIG_SECTION_MISMATCH_WARN_ONLY=y

make -C $(pwd) O=$(pwd)/out KCFLAGS=-w CONFIG_SECTION_MISMATCH_WARN_ONLY=y a13ve_defconfig
make -C $(pwd) O=$(pwd)/out KCFLAGS=-w CONFIG_SECTION_MISMATCH_WARN_ONLY=y -j16

cp out/arch/arm64/boot/Image $(pwd)/arch/arm64/boot/Image
