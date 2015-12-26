#! /bin/sh

#
# Work in the progress
#
# Configuring gcc for cross-native build og DJGPP port under Linux
# 
# - one must install GMP, MPFR, MPC and ZLIB development files
#   for DJGPP
#

export PATH=$(pwd)/../tmpinst/bin:$PATH
export LD_LIBRARY_PATH=$(pwd)/../tmpinst/lib64

gcc -v 
i586-pc-msdosdjgpp-gcc -v


target=i586-pc-msdosdjgpp

../gnu/gcc-6.00-20151211/configure \
    --prefix=/dev/env/DJDIR \
    --build=i586-pc-linux-gnu \
    --host=i586-pc-msdosdjgpp \
    --target=$target \
    --enable-languages="c,c++,fortran,objc,obj-c++," \
    --with-native-system-header-dir=/usr/$target/sys-include \
    --disable-libstdcxx-pch \
    --enable-lto \
    --enable-nls || exit 1

make -j12 | exit 1
