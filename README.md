# FUSE in Docker

We want to mount filesystems in Docker. We don't want to run as root.

## Plan

Intercept stdio calls and implement a VFS 

### fduse daemon

* Creates `/dev/fuse` and `/var/dfused`
* This functions as the FUSE kernel module

### glibc shim

* Use `LD_PRELOAD` to override glibc filesystem calls.

