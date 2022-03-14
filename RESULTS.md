# Understanding MACB updates

Timestamp updates are mandated by user actions on applications or utilities (`cp`), which rely on middleware, standard libraries (`libc`) and system calls in the kernel to ultimately have timestamps written down in inodes on the file system.

Therefore each of these layers (Application/POSIX Utility, Middleware, Standard Libraries, Kernel, File System) can influence the timestamps being eventually updated.
One should pay escpecially attention to **mount options** that can for instance completely disable A updates.

The following figure illustrates timestamp updates across the software stack.

![Unix MACB](https://raw.githubusercontent.com/yaps8/yaps8.github.io/master/os_timestamps/2022-03-03/software_stack.png)


# OS results (Linux, OpenBSD, FreeBSD, macOS) and POSIX compliance
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

