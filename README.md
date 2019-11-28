# os_timestamps
### [https://github.com/quoscient/os_timestamps](https://github.com/quoscient/os_timestamps)

Profile how your Unix-like OS(Linux, BSD...)  modifies MAC(B) timestamps.

# Build

- `mkdir build; cd build/`
- `cmake ../src/`
- `make`

# profile_os

To have complete results you will need:
- For "Volume Copy" (copy a file to a different file system): the other file system to test, mounts into mnt/
    - On Linux you can create an Ext4 fs with:
        - dd if=/dev/zero of=profileos.ext4 bs=4M count=10
        - mkfs.ext4 -O extra_isize -I 256 profileos.ext4
    - On OpenBSD you may use /tmp/ as it is typically on a separate partition
- For reliable chown tests ("File Change"...): the GID of a group you can attribute to a file (you shall be able to do `chown :GID file`)
    - On OpenBSD & FreeBSD, GID 0 (wheel) can be used

`./profile_os -m mnt/ -g 1002`

```
INFO: Directory for tests is: tmp_os_profile_10/
INFO: Volume path is: mnt/tmp_os_profile_10/
File Creation (PROFILE.OS.FILE.NEW):
dir/
  M.C.
newfile
  MACB
File Copy (new) (PROFILE.OS.FILE.COPY.NEW):
src
  .A..
srcdir/
  ....
dst
  MACB
dstdir/
  M.C.
```

Two CSV files are also created:
- os_profile_results.csv - Contains a condensed view of the results, can be used for comparison
- os_profile_flags.csv   - Contains a more detailed view of the results, explaining precisely what happens to each timestamp
