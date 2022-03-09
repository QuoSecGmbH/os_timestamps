# OpenBSD

![OpenBSD MACB](https://raw.githubusercontent.com/yaps8/yaps8.github.io/master/os_timestamps/2022-03-09/openbsd_mac.png)

- PDF: [openbsd_mac.pdf](https://github.com/QuoSecGmbH/os_timestamps/releases/download/2022-03-03/openbsd_mac.pdf)


## Files Systems: FFS1 and FFS2

|                      | FFS1 | FFS2 (default) |
|----------------------|------|------|
| Timestamp Resolution | 1 ns | 1 ns |
| Timestamp Size       | 32 bits (seconds) + 32 bits (nanosecond) | 64 bits (seconds) + 32 bits (nanosecond)     |
| Fields for B Timestamp (file creation)            |  No  | Yes  |

Though FFS2 has fields (64 bits + 32 bits) for the B timestamp, OpenBSD does not fill it, it is always 0.

## Test Setup

- Machine: Virtualbox
- Versions tested: 6.5, 6.8, 7.0
- Filesystems tested: FFS1, FFS2

## Result output

- os_profile_results.csv [2019]: [/results/2019_11_29/profileos/openbsd/os_profile_results.csv](/results/2019_11_29/profileos/openbsd/os_profile_results.csv)
- os_profile_results_mac.csv [2019]: [/results/2019_11_29/profileos/openbsd/os_profile_results_mac.csv](/results/2019_11_29/profileos/openbsd/os_profile_results_mac.csv)
- os_profile_flags.csv [2019]: [/results/2019_11_29/profileos/openbsd/os_profile_flags.csv](/results/2019_11_29/profileos/openbsd/os_profile_flags.csv)