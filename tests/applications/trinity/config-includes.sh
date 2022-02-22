mkdir /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/mtd/
mkdir /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/linux/hdlc
cp /usr/include/asm-generic/* /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/asm-generic/
cp /usr/include/asm/* /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/asm/
cp /usr/include/linux/* /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/linux/
cp /usr/include/linux/hdlc/* /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/linux/hdlc/
cp /usr/include/netinet/* /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/netinet/
cp /usr/include/arpa/* /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/arpa/
cp /usr/include/bits/stdint-intn.h /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/bits/
cp /usr/include/bits/stdint-uintn.h /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/bits/
cp /usr/include/bits/uintn-identity.h /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/bits/
# redefine largefile
sed -i '64,70d' /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/bits/fcntl.h
sed -i '64i#define O_LARGEFILE     0' /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/include/bits/fcntl.h
