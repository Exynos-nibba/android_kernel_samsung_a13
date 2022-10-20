#!/bin/bash

export CROSS_COMPILE=$(pwd)/../gas/bin/aarch64-linux-gnu-
export CC=$(pwd)/../clang/bin/clang
export CLANG_TRIPLE=aarch64-linux-gnu-
export PATH=$(pwd)/../clang/bin:$PATH
export PATH=$(pwd)/../gas/bin:$PATH
export ARCH=arm64
export ANDROID_MAJOR_VERSION=r
export VARIANT="A13"

export KCFLAGS=-w
export CONFIG_SECTION_MISMATCH_WARN_ONLY=y

make -C $(pwd) O=$(pwd)/out KCFLAGS=-w CONFIG_SECTION_MISMATCH_WARN_ONLY=y a13ve_defconfig
make -C $(pwd) O=$(pwd)/out KCFLAGS=-w CONFIG_SECTION_MISMATCH_WARN_ONLY=y -j16

git clone https://github.com/osm0sis/AnyKernel3 $(pwd)/AnyKernel3
cd AnyKernel3
git reset --hard
cp $(pwd)/../out/arch/arm64/boot/Image zImage
rm -rf anykernel.sh
cp ../ak3-script/anykernel.sh ./
zip -r9 $(pwd)/../${VARIANT}_chernobylkernel_`date '+%Y_%m_%d'`.zip * -x .git README.md *placeholder

#cp out/arch/arm64/boot/Image $(pwd)/arch/arm64/boot/Image
