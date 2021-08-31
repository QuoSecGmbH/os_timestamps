#!/bin/bash

convert -flatten -verbose -density 150 -trim -quality 100 -sharpen 0x1.0 linux_mac_reverse_table.pdf linux_mac_reverse_table.png
convert -flatten -verbose -density 150 -trim -quality 100 -sharpen 0x1.0 openbsd_mac_reverse_table.pdf openbsd_mac_reverse_table.png
convert -flatten -verbose -density 150 -trim -quality 100 -sharpen 0x1.0 freebsd_mac_reverse_table.pdf freebsd_mac_reverse_table.png
