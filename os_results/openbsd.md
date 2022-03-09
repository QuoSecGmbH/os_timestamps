# OpenBSD

![OpenBSD MACB](https://raw.githubusercontent.com/yaps8/yaps8.github.io/master/os_timestamps/2022-03-09/openbsd_mac.png)

- PDF: [openbsd_mac.pdf](https://github.com/QuoSecGmbH/os_timestamps/releases/download/2022-03-03/openbsd_mac.pdf)


## Files Systems: FFS1 and FFS2

|                      | FFS1 | FFS2 (default) |
|----------------------|------|------|
| Timestamp Resolution | 1 ns | 1 ns |
| Timestamp size       | 32 bits (seconds) + 32 bits (nanosecond) | 64 bits (seconds) + 32 bits (nanosecond)     |
| Field for B Timestamp (file creation)            |  No  | Yes  |

## Test Setup

- Machine: Virtualbox
- Versions tested: 6.5, 6.8, 7.0
- Filesystems tested: FFS1, FFS2
