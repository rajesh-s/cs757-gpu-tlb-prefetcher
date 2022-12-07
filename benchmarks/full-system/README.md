# Steps to run FS simulation on gem5-gpu

- Dependencies:

```bash
sudo apt install build-essential git m4 scons zlib1g zlib1g-dev \
    libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev \
    python3-dev python-is-python3 libboost-all-dev pkg-config
sudo apt install qemu-kvm qemu virt-manager virt-viewer libvirt-clients libvirt-daemon-system bridge-utils virtinst libvirt-daemon
```

- Follow steps here to build disk image: `https://gem5.googlesource.com/public/gem5-resources/+/refs/heads/stable/src/gpu-fs/`

## Commands 

```bash
# Compile square
docker run --rm -v ${PWD}:${PWD} -w ${PWD}/src/gpu/square/ gcr.io/gem5-test/gpu-fs:latest bash -c 'make clean; HCC_AMDGPU_TARGET=gfx900 make'

# Run FS sim
build/VEGA_X86/gem5.opt configs/example/gpufs/vega10_kvm.py --disk-image ../disk-image/rocm42/rocm42-image/rocm42 --kernel ../vmlinux-5.4.0-105-generic --gpu-mmio-trace /path/to/gem5-resources/src/gpu-fs/vega_mmio.log --app ../../gpu/square/bin/square`
```
