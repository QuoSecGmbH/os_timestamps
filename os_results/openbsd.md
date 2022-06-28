# OpenBSD

![OpenBSD MACB](https://yaps8.github.io/os_timestamps/2022-03-09/openbsd_mac.png)

- PDF: [openbsd_mac.pdf](https://github.com/QuoSecGmbH/os_timestamps/releases/download/2022-03-03/openbsd_mac.pdf)


# File Systems: FFS1 and FFS2

|                      | FFS1 | FFS2 (default) |
|----------------------|------|------|
| Timestamp Resolution | 1 ns | 1 ns |
| Timestamp Size       | 32 bits (seconds) + 32 bits (nanosecond) | 64 bits (seconds) + 32 bits (nanosecond)     |
| Fields for B Timestamp (file creation)            |  No  | Yes  |

Although FFS2 has fields (64 bits + 32 bits) for the B timestamp, OpenBSD does not fill them, B is always 0.

# Test Setup

- Machine: Virtualbox
- Versions tested: 6.5, 6.8, 7.0
- Filesystems tested: FFS1, FFS2

# Result Output

July 2022:
- profile_os_results.csv: [../results/2022_06_28/profileos/openbsd/profile_os_results.csv](../results/2022_06_28/profileos/openbsd/profile_os_results.csv)
- profile_os_flags.csv: [../results/2022_06_28/profileos/openbsd/profile_os_flags.csv](../results/2022_06_28/profileos/openbsd/profile_os_flags.csv)
- run_tests_results.csv: [../results/2022_06_28/posix_compliance/openbsd/run_tests_results.csv](../results/2022_06_28/posix_compliance/openbsd/run_tests_results.csv)


March 2022:
- POSIX Compliance - results.csv: [/results/2022_03_09/posix_compliance/openbsd/results.csv](/results/2022_03_09/posix_compliance/openbsd/results.csv)
- os_profile_results.csv: [/results/2022_03_09/profileos/openbsd/os_profile_results.csv](/results/2022_03_09/profileos/openbsd/os_profile_results.csv)
- os_profile_flags.csv: [/results/2022_03_09/profileos/openbsd/os_profile_flags.csv](/results/2022_03_09/profileos/openbsd/os_profile_flags.csv)

2019:

- os_profile_results.csv: [/results/2019_11_29/profileos/openbsd/os_profile_results.csv](/results/2019_11_29/profileos/openbsd/os_profile_results.csv)
- os_profile_results_mac.csv: [/results/2019_11_29/profileos/openbsd/os_profile_results_mac.csv](/results/2019_11_29/profileos/openbsd/os_profile_results_mac.csv)
- os_profile_flags.csv: [/results/2019_11_29/profileos/openbsd/os_profile_flags.csv](/results/2019_11_29/profileos/openbsd/os_profile_flags.csv)
