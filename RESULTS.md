# Understanding MACB updates (Software Stack)

Timestamp updates are mandated by user actions on applications or utilities (`cp`), which rely on middleware, standard libraries (`libc`) and system calls in the kernel to ultimately have timestamps written down in inodes on the file system.

Therefore each of these layers (Application/POSIX Utility, Middleware, Standard Libraries, Kernel, File System) can influence the timestamps being eventually updated.
One should pay especially attention to **mount options** that can for instance completely disable A updates.

The following table illustrates timestamp updates across the software stack.

| Application or POSIX utility | -> Middleware (libraries) | -> Standard Libraries | -> Kernel | -> File System | -> (MACB)    |
|----------------------|---------|--------------|----------------|-----------------------------------|------|
| `cat file`             |         | GLibc        | Linux (Ubuntu) | ext4 (mounted with `strictatime`) | .A.. |
| `cat file`             |         | GLibc        | Linux (Ubuntu) | ext4 (mounted with `relatime`)    | .... |
| geany (save file)    | GTK/GIO | GLibc        | Linux (Ubuntu) | ext4 (mounted with `strictatime`)    | MACB |
| `ls dir/`              |         | GLibc        | Linux (Ubuntu) | ext4 (mounted with `strictatime`) | ..A. |
| `ls dir/`              |         | OpenBSD libc | OpenBSD        | FFS2                              | ..A  |
| `ls dir/`              |         | FreeBSD libc | FreeBSD        | UFS2                              | .... |


# OS results (Linux, OpenBSD, FreeBSD, macOS) and POSIX compliance

The following results and tables apply to the layers specified by POSIX: POSIX Utilities, standard libraries (`libc`), kernel (system calls and mount options) and file systems.

![Unix MACB](https://raw.githubusercontent.com/yaps8/yaps8.github.io/master/os_timestamps/2022-03-03/unix_macb.png)

- PDF: [unix_macb.pdf](https://github.com/QuoSecGmbH/os_timestamps/releases/download/2022-03-03/unix_macb.pdf)

## POSIX
POSIX specifies MAC updates, the manually generated os_profile_results.csv is here:
- [results/2019_11_29/profileos/posix/os_profile.csv](results/2019_11_29/profileos/posix/os_profile.csv)

`*` is an additional symbol for when POSIX leaves choice to the implementation:
> Some implementations mark for update the last file status change timestamp of renamed files and some do not.

## Linux, OpenBSD, FreeBSD, macOS (POSIX Utilities, libc, kernel, file systems)

- [Linux](/os_results/linux.md)
- [OpenBSD](/os_results/openbsd.md)
- [FreeBSD](/os_results/freebsd.md)
- [macOS](/os_results/openbsd.md)

# Middleware

# Applications

