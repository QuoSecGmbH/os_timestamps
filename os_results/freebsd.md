# FreeBSD

![FreeBSD MACB](https://yaps8.github.io/os_timestamps/2022-03-03/freebsd_macb.png)

- PDF: [freebsd_macb.pdf](https://github.com/QuoSecGmbH/os_timestamps/releases/download/2022-03-03/freebsd_macb.pdf)


# File Systems: UFS1 and UFS2

|                      | UFS1 | UFS2 (default) |
|----------------------|------|------|
| Timestamp Resolution | 1 ns | 1 ns |
| Timestamp Size       | 32 bits (seconds) + 32 bits (nanosecond) | 64 bits (seconds) + 32 bits (nanosecond)     |
| Fields for B Timestamp (file creation)            |  No  | Yes  |

Beside support of nanoseconds from the file system, the timestamps resolution actually used by the kernel can be configured:
- 1 second
- **1 microsecond (default)**
- 1 nanosecond

The setting can be read with `sysctl vfs.timestamp_precision` and set for instance with `sysctl vfs.timestamp_precision = 3`.

Source and possible values:
- https://github.com/freebsd/freebsd-src/blob/de1aa3dab23c06fec962a14da3e7b4755c5880cf/sys/kern/vfs_subr.c#L984

# Test Setup

- Machine: Virtualbox
- Versions: 12.0 and 13.0
- Filesystem: UFS2

# Result Output

2022:
- profile_os_results.csv: [../results/2022_06_28/profileos/freebsd/profile_os_results.csv](../results/2022_06_28/profileos/freebsd/profile_os_results.csv)
- profile_os_flags.csv: [../results/2022_06_28/profileos/freebsd/profile_os_flags.csv](../results/2022_06_28/profileos/freebsd/profile_os_flags.csv)
- run_tests_results.csv: [../results/2022_06_28/posix_compliance/freebsd/run_tests_results.csv](../results/2022_06_28/posix_compliance/freebsd/run_tests_results.csv)

2019:
- os_profile_results.csv: [../results/2019_11_29/profileos/freebsd/os_profile_results.csv](../results/2019_11_29/profileos/freebsd/os_profile_results.csv)
- os_profile_results_mac.csv: [../results/2019_11_29/profileos/freebsd/os_profile_results_mac.csv](../results/2019_11_29/profileos/freebsd/os_profile_results_mac.csv)
- os_profile_flags.csv: [../results/2019_11_29/profileos/freebsd/os_profile_flags.csv](../results/2019_11_29/profileos/freebsd/os_profile_flags.csv)
