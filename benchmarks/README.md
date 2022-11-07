# Running benchmarks with gem5

## SE mode

### Hetero-mark

Running kmeans on gem5 from Hetero-mark

```bash
git clone https://gem5.googlesource.com/public/gem5
cd gem5
docker run -u $UID:$GID --volume $(pwd):$(pwd) -w $(pwd) gcr.io/gem5-test/gcn-gpu:v22-0 scons build/GCN3_X86/gem5.opt -j$(nproc)
git clone https://github.com/NUCAR-DEV/Hetero-Mark
docker run -it --volume $(pwd):$(pwd) -w $(pwd) gcr.io/gem5-test/gcn-gpu:v22-0 /bin/bash
# Download dataset from here https://drive.google.com/file/d/1IItjFFUIfANgrUUI7jebNS9rfSEe32lZ/view?usp=sharing
mkdir build
cd build
cmake -DCOMPILE_HIP=On ../
make
docker run -u $UID:$GID --volume $(pwd):$(pwd) -w $(pwd) gcr.io/gem5-test/gcn-gpu:v22-0 build/GCN3_X86/gem5.opt configs/example/apu_se.py -n 3 --benchmark-root=Hetero-Mark/build/src/kmeans/hip -c ./kmeans_hip --options="-i 1000_34.txt"
```
