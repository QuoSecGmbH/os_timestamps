# This file stores functions which automate often used processes in this project

import os
import subprocess
from dataclasses import dataclass
import pyautogui
import time
import argparse


# Dataclass to store the timestamps
@dataclass
class TimeStamp:
    Access: str
    Modify: str
    Change: str
    Birth: str
    Inode: str


# function to compare two different timestamps and return the difference
def compareTimestamps(testname, ts1, ts2):
    if (ts1.Modify != ts2.Modify):
        testname = testname + "M"
    else:
        testname = testname + " "
    testname = testname + "|"
    if (ts1.Access != ts2.Access):
        testname = testname + "A"
    else:
        testname = testname + " "
    testname = testname + "|"
    if (ts1.Change != ts2.Change):
        testname = testname + "C"
    else:
        testname = testname + " "
    testname = testname + "|"
    if (ts1.Birth != ts2.Birth):
        testname = testname + "B"
    else:
        testname = testname + " "
    testname = testname + "|"
    if (ts1.Inode != ts2.Inode):
        testname = testname + "I"
    else:
        testname = testname + " "

    print(testname)


# Function to extract the timestamps of a file with ./prototype_file_fs
# and the Inode number with stat
def statextract(testfile):
    Access = ""
    Modify = ""
    Change = ""
    Birth = ""
    Inode = ""

    output = str(subprocess.check_output(['./prototype_file_ts', testfile]))
    beginOutput = output.find("M:")
    output = output[beginOutput + 3::]

    findAccess = output.find("A:")
    Modify = output[:findAccess - 2]
    output = output[findAccess + 3:]

    findChange = output.find("C:")
    Access = output[:findChange - 2]
    output = output[findChange + 3:]

    findBirth = output.find("B:")
    Change = output[:findBirth - 2]
    Birth = output[findBirth + 3:len(output) - 3]

    output = str(subprocess.check_output(['stat', testfile]))
    findInode = output.find("Inode")
    output = output[findInode + 7::]
    i = 0
    while output[i] != " ":
        Inode += output[i]
        i += 1

    ts = TimeStamp(Access, Modify, Change, Birth, Inode)
    return ts


# prints the before and after timestamps
def print_timestamps(ts1, ts2):
    print("Before:")
    print("Modify: " + str(ts1.Modify))
    print("Access: " + str(ts1.Access))
    print("Change: " + str(ts1.Change))
    print("Birth:  " + str(ts1.Birth))
    print("Inode:  " + str(ts1.Inode))
    print("After:")
    print("Modify: " + str(ts2.Modify))
    print("Access: " + str(ts2.Access))
    print("Change: " + str(ts2.Change))
    print("Birth:  " + str(ts2.Birth))
    print("Inode:  " + str(ts2.Inode))


# Function to check if a given program is installed on a system
def doesProgramExist(program):
    try:
        output = str(subprocess.check_output([str(program), '--version']))
    except FileNotFoundError:
        return -1


# Function to open a terminal
def open_terminal():
    if (doesProgramExist("gnome-terminal") != -1):
        os.spawnlp(os.P_NOWAIT, 'gnome-terminal', 'gnome-terminal')
    elif (doesProgramExist("konsole") != -1):
        os.spawnlp(os.P_NOWAIT, 'konsole', 'konsole')
    elif (doesProgramExist("terminator") != -1):
        os.spawnlp(os.P_NOWAIT, 'terminator', 'terminator')
    else:
        print("ERROR: No usable terminal found")
        quit()


# Function to close a terminal
def close_terminal():
    pyautogui.write("exit")
    pyautogui.press('enter')


# Function to create files of different sizes depending on a given mode
def create_file(mode):
    if (mode == 0):
        os.system("touch testfile.c")
    if (mode == 1):
        os.system("seq 1 > testfile.c")
    if (mode == 2):
        os.system("seq 1000000 > testfile.c")


# Function for removing a file
def remove_file():
    os.system("rm testfile.c")
