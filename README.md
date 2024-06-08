# FUSE in Docker

We want to mount filesystems in Docker. We don't want to run as root.

## Plan

### Kernel shim

* Use `LD_PRELOAD` to override glibc filesystem calls.

### fduse daemon

* Creates `/dev/fuse`
* This functions as the FUSE kernel module
