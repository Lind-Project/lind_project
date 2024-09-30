#!/bin/bash
echo -e "------------ Starting 4-way Locking Comparison Tests ------------\n"

mkdir -p data

echo -e "\n====== Running Native ======\n"

# Compile binaries for native
/home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/compile-native.sh
/home/lind/lind_project/tests/ipc_performance/total_runtime/run_lock_comp.sh $1 "native" "regular"

echo -e "\n====== Running Lind ======\n"
# Compile binaries for lind
/home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/compile-lind.sh
/home/lind/lind_project/tests/ipc_performance/total_runtime/run_lock_comp.sh $1 "lind" "regular"

echo -e "\n====== Running Lind - Mutex ======\n"

# Clone the RustPOSIX repo
cd /home/lind/lind_project/src/
rm -r safeposix-rust
git clone https://github.com/Lind-Project/safeposix-rust.git
# Checkout to mutex locks branch and recompile RustPOSIX
cd /home/lind/lind_project/src/safeposix-rust
git checkout kernel-locks
cd /home/lind/lind_project/
src/mklind rustposix
src/mklind install

cd /home/lind/lind_project/tests/ipc_performance/total_runtime/

/home/lind/lind_project/tests/ipc_performance/total_runtime/run_lock_comp.sh $1 "lind" "mutex"

echo -e "\n====== Running Lind - Spin lock ======\n"

# Checkout to spin locks branch and recompile RustPOSIX
cd /home/lind/lind_project/src/safeposix-rust
git checkout kernel-locks-spin
cd /home/lind/lind_project/
src/mklind rustposix
src/mklind install

cd /home/lind/lind_project/tests/ipc_performance/total_runtime/

/home/lind/lind_project/tests/ipc_performance/total_runtime/run_lock_comp.sh $1 "lind" "spin"
