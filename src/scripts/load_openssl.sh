# Builds openssl and libraries in nacl.
echo "Compiling Openssl"
cd /home/lind/lind_project/tests/applications/openssl
./bootstrap_nacl

echo "Copying Openssl"
lindfs cp /home/lind/lind_project/tests/applications/openssl/libcrypto.so.1.0.0 /lib/glibc/libcrypto.so.1.0.0
lindfs cp /home/lind/lind_project/tests/applications/openssl/libssl.so.1.0.0 /lib/glibc/libssl.so.1.0.0
