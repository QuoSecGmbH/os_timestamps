# Understanding MACB updates (Software Stack)

Timestamp updates are mandated by user actions on applications or utilities (`cp`), which rely on middleware, standard libraries (`libc`) and system calls in the kernel to ultimately have timestamps written down in inodes on the file system.

Therefore each of these layers (Application/POSIX Utility, Middleware, Standard Libraries, Kernel, File System) can influence the timestamps being eventually updated.
One should pay especially attention to **mount options** that can for instance completely disable A updates.

The following table illustrates timestamp updates across the software stack.

| Application or POSIX utility | -> Middleware (libraries) | -> Standard Libraries | -> Kernel | -> File System | -> (MACB)    |
|----------------------|---------|--------------|----------------|-----------------------------------|------|
| `cat file`             |         | glibc        | Linux (Ubuntu) | ext4 (mounted with `strictatime`) | .A.. |
| `cat file`             |         | glibc        | Linux (Ubuntu) | ext4 (mounted with `noatime`)     | .... |
| geany (save file)    | GTK/GIO | glibc        | Linux (Ubuntu) | ext4 (mounted with `relatime`)    | MACB |
| `ls dir/`              |         | OpenBSD libc | OpenBSD        | FFS2 | .A.0 |
| `ls dir/`              |         | FreeBSD libc | FreeBSD        | UFS2 | .... |


# OS results (Linux, OpenBSD, FreeBSD, macOS) and POSIX compliance

The following results and tables apply to the layers specified by POSIX: POSIX Utilities, standard libraries (`libc`), kernel (system calls and mount options) and file systems.

![Unix MACB](https://yaps8.github.io/os_timestamps/2022-03-03/unix_macb.png)

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
- [macOS](/os_results/macos.md)

# Middleware

Middleware were tested on Ubuntu (20.04.3 LTS).


# Applications

Applications were tested on Ubuntu (20.04.3 LTS).
File editors were tested for file Read and File Modify.

| Editor | Read | Write | 
| ------ | ---- | ----- | 
| Vim –clean         | .A.. | MACB | 
| Emacs              | .A.. | MACB |
| Code::Blocks       | .A.. | MACB |
| gedit              | .A.. | MACB |
| Bluefish           | .A.. | MACB |
| Geany              | .A.. | MACB |
| TeXstudio          | .A.. | MACB |
| JED                | .A.. | MACB |
| Kate               | .A.. | MAC. |
| Atom               | .A.. | MAC. |
| Vim nowritebackup  | .A.. | M.C. |
| nano               | .A.. | M.C. |
| Leafpad            | .A.. | M.C. |
| Visual Studio Code | .A.. | M.C. |
| Notepadqq          | .A.. | M.C. |
| Sublime Text       | .A.. | M.C. |


