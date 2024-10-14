# This file stores functions which automate often used processes in this project

import os
import subprocess
from dataclasses import dataclass
import pyautogui
import time
import argparse
import decimal
import typing
import sys
import random

@dataclass
class env:
    args: None
    operations: None
    sizes: typing.List[int]
    tmpdir_path: None
    filets_path: None
    currenttime_path: None
    file_output: None
    file_csv_output: None
    file_flags_csv_output: None


# Dataclass to store the timestamps
@dataclass
class TimeStamp:
    Modify: decimal
    Access: decimal
    Change: decimal
    Birth: decimal
    Inode: int

# Dataclass to store the timestamps
# @dataclass
# class TimeStamp:
#     Access: str
#     Modify: str
#     Change: str
#     Birth: str
#     Inode: str

class Compared_TS:
    def __init__(self):
        self.PROFILE_ERROR = None
        self.PROFILE_SAMEAS_W0_BEFORE = None
        self.PROFILE_SAMEAS_W0_M_BEFORE = None
        self.PROFILE_SAMEAS_W0_A_BEFORE = None
        self.PROFILE_SAMEAS_W0_C_BEFORE = None
        self.PROFILE_SAMEAS_W0_B_BEFORE = None
        self.PROFILE_EARLIER = None
        self.PROFILE_LATER = None
        self.PROFILE_ZERO = None
        self.PROFILE_UPDATE = None
        self.PROFILE_EQ = None

    def __eq__(self, other):
        if self.PROFILE_ERROR != other.PROFILE_ERROR:
            return False
        if self.PROFILE_SAMEAS_W0_BEFORE != other.PROFILE_SAMEAS_W0_BEFORE:
            return False
        if self.PROFILE_SAMEAS_W0_M_BEFORE != other.PROFILE_SAMEAS_W0_M_BEFORE:
            return False
        if self.PROFILE_SAMEAS_W0_A_BEFORE != other.PROFILE_SAMEAS_W0_A_BEFORE:
            return False
        if self.PROFILE_SAMEAS_W0_C_BEFORE != other.PROFILE_SAMEAS_W0_C_BEFORE:
            return False
        if self.PROFILE_SAMEAS_W0_B_BEFORE != other.PROFILE_SAMEAS_W0_B_BEFORE:
            return False
        if self.PROFILE_EARLIER != other.PROFILE_EARLIER:
            return False
        if self.PROFILE_LATER != other.PROFILE_LATER:
            return False
        if self.PROFILE_ZERO != other.PROFILE_ZERO:
            return False
        if self.PROFILE_UPDATE != other.PROFILE_UPDATE:
            return False
        if self.PROFILE_EQ != other.PROFILE_EQ:
            return False
        return True
        

@dataclass
class Compared_MACBI:
    PROFILE_I_EQ: bool
    PROFILE_I_ERROR: bool
    c_ts: typing.List[Compared_TS]

    def __init__(self):
        self.c_ts = []
        self.PROFILE_I_ERROR = None
        self.PROFILE_I_EQ = None

@dataclass
class ProfileInfo:
    t_before: TimeStamp
    t_after: TimeStamp
    watch_array: typing.List
    multi_stat_before: typing.List[TimeStamp]
    multi_stat_after: typing.List[TimeStamp]
    profile: typing.List[Compared_TS]
    profile_str: typing.List[str]
    target_code: str
    filesize: int
    test_code: str
    test_description: str


    def __init__(self, target_code, test_code, filesize, test_description):
        self.t_before = None
        self.t_after = None
        self.watch_array = []
        self.multi_stat_before = None
        self.multi_stat_after = None
        self.profile = None
        self.profile_str = None
        self.target_code = target_code
        self.filesize = filesize
        self.test_code = test_code
        self.test_description = test_description


    def profile_mostly_same(self, pi):
        if len(self.watch_array) != len(pi.watch_array):
            return False
        
        for i in range(len(self.watch_array)):
            if self.watch_array[i][0] != pi.watch_array[i][0]:
                return False
            
            c_macbi1 = self.profile[i]
            c_macbi2 = pi.profile[i]

            if c_macbi1.PROFILE_I_EQ != c_macbi2.PROFILE_I_EQ:
                return False
            if c_macbi1.PROFILE_I_ERROR != c_macbi2.PROFILE_I_ERROR:
                return False

            for j in range(4):
                c_ts_1 = c_macbi1.c_ts[j]
                c_ts_2 = c_macbi2.c_ts[j]

                if c_ts_1.PROFILE_ERROR == c_ts_2.PROFILE_ERROR == True:
                    continue

                if c_ts_1.PROFILE_ZERO == c_ts_2.PROFILE_ZERO == True:
                    continue

                m1_1 = [c_ts_1.PROFILE_UPDATE, c_ts_1.PROFILE_SAMEAS_W0_BEFORE, c_ts_1.PROFILE_EQ, c_ts_1.PROFILE_ZERO]
                m1_2 = [c_ts_2.PROFILE_UPDATE, c_ts_2.PROFILE_SAMEAS_W0_BEFORE, c_ts_2.PROFILE_EQ, c_ts_2.PROFILE_ZERO]
                if m1_1.count(True) == m1_2.count(True) != 0 and m1_1 == m1_2:
                    continue

                m2_1 = [c_ts_1.PROFILE_SAMEAS_W0_M_BEFORE, c_ts_1.PROFILE_SAMEAS_W0_A_BEFORE, c_ts_1.PROFILE_SAMEAS_W0_C_BEFORE, c_ts_1.PROFILE_SAMEAS_W0_B_BEFORE]
                m2_2 = [c_ts_2.PROFILE_SAMEAS_W0_M_BEFORE, c_ts_2.PROFILE_SAMEAS_W0_A_BEFORE, c_ts_2.PROFILE_SAMEAS_W0_C_BEFORE, c_ts_2.PROFILE_SAMEAS_W0_B_BEFORE]
                if m2_1.count(True) == m2_2.count(True) != 0 and m2_1 == m2_2:
                    continue

                if not (c_ts_1 == c_ts_2):
                    return False
        return True


    def profile_init(self, env):
        delay()
        self.populate_stat_before(env)
        self.t_before = get_current_time(env)


    def profile_analyze(self, env):
        self.populate_stat_after(env)
        self.t_after = get_current_time(env)
        delay()
        self.compute_profile()
        self.compute_profile_str()

    def profile_report(self, env, print_path=False, print_filesize=False):
        self.profile_report_csv(file=env.file_csv_output, print_path=print_path, print_filesize=print_filesize)
        self.profile_report_csv(file=sys.stdout, print_path=print_path, print_filesize=print_filesize)
        self.profile_report_flags_csv(file=env.file_flags_csv_output, print_path=print_path, print_filesize=print_filesize)


    def multi_stat(self, env):
        multi_stat = []

        for i in range(len(self.watch_array)):
            ts = statextract(env, self.watch_array[i][1])
            multi_stat.append(ts)
        return multi_stat
            

    def populate_stat_before(self, env):
        self.multi_stat_before = self.multi_stat(env)


    def populate_stat_after(self, env):
        self.multi_stat_after = self.multi_stat(env)


    def profile_report_csv(self, file, print_path, print_filesize):
        for i in range(len(self.watch_array)):
            print_list = [self.target_code, self.test_code]
            if print_filesize:
                print_list.append(str(self.filesize))
            print_list. append(self.watch_array[i][0])
            if print_path:
                print_list. append(self.watch_array[i][1])
            id = ".".join(print_list)
            result = self.profile_str[i]
            print(id + ", " + result, file=file)


    def profile_report_flags_csv(self, file, print_path, print_filesize):
        for i in range(len(self.watch_array)):
            print_list = [self.target_code, self.test_code]
            if print_filesize:
                print_list.append(str(print_filesize))
            print_list. append(self.watch_array[i][0])
            if print_path:
                print_list. append(self.watch_array[i][1])
            id = ", ".join(print_list)
            c_macbi = self.profile[i]

            macb_str = "MACB"
            for j in range(len(macb_str)):
                c_ts = c_macbi.c_ts[j]
                for key in (vars(c_ts)):
                    if c_ts.__dict__[key]:
                        print(id + ", " + macb_str[j] + ", " + key, file=file)


    def profile_verbose_print(self, file, print_path):
        print("---\nBEGIN TS Profile", file=file)
        print("  t_before:", self.t_before)
        print("  t_after: ", self.t_after)
        for i in range(len(self.watch_array)):
            print(self.watch_array[i][0] + " - " + self.watch_array[i][1] + ":", file=file)

            print("  Before:", file=file)
            print_timestamp(file, "    ", self.multi_stat_before[i])
            print("  After:", file=file)
            print_timestamp(file, "    ", self.multi_stat_after[i])

            c_macbi = self.profile[i]
            print("  PROFILE_I_EQ:", c_macbi.PROFILE_I_EQ)
            macb_str = "MACB"
            for j in range(len(macb_str)):
                print("  " + macb_str[j] + ":", file=file)
                c_ts = c_macbi.c_ts[j]
                # print(dir(c_ts))
                # print(c_ts.__dict__)
                for k in (vars(c_ts)):
                    print("    {0:27}: {1}".format(k, vars(c_ts)[k]))
        print("END   TS Profile\n---", file=file)


    def compute_profile(self):
        if self.watch_array is None or len(self.watch_array) == 0:
            return
        
        ts_w0_before = self.multi_stat_before[0]
        ts_w0_before_MACB = (ts_w0_before.Modify, ts_w0_before.Access, ts_w0_before.Change, ts_w0_before.Birth)
        self.profile = []

        for i in range(len(self.watch_array)):
            ts_before = self.multi_stat_before[i]
            ts_before_MACB = (ts_before.Modify, ts_before.Access, ts_before.Change, ts_before.Birth)
            ts_after = self.multi_stat_after[i]
            ts_after_MACB = (ts_after.Modify, ts_after.Access, ts_after.Change, ts_after.Birth)

            c_macbi = Compared_MACBI()

            if ts_after.Inode is None:
                c_macbi.PROFILE_I_ERROR = True
            elif ts_after.Inode == ts_before.Inode:
                c_macbi.PROFILE_I_EQ = True

            for j in range(4):
                c_ts = Compared_TS()

                ts_w0_before_j = ts_w0_before_MACB[j]
                ts_before_j = ts_before_MACB[j]
                ts_after_j = ts_after_MACB[j]

                if ts_after_j == None:
                    c_ts.PROFILE_ERROR = True
                    c_macbi.c_ts.append(c_ts)
                    continue

                if ts_after_j == ts_w0_before_j:
                    c_ts.PROFILE_SAMEAS_W0_BEFORE = True
                if ts_after_j == ts_w0_before.Modify:
                    c_ts.PROFILE_SAMEAS_W0_M_BEFORE = True
                if ts_after_j == ts_w0_before.Access:
                    c_ts.PROFILE_SAMEAS_W0_A_BEFORE = True
                if ts_after_j == ts_w0_before.Change:
                    c_ts.PROFILE_SAMEAS_W0_C_BEFORE = True
                if ts_after_j == ts_w0_before.Birth:
                    c_ts.PROFILE_SAMEAS_W0_B_BEFORE = True

                if self.t_before <= ts_after_j <= self.t_after:
                    c_ts.PROFILE_UPDATE = True

                if ts_after_j != ts_before_j:
                    if ts_after_j < self.t_before:
                        c_ts.PROFILE_EARLIER = True
                    if self.t_after < ts_after_j:
                        c_ts.PROFILE_LATER = True
                
                if ts_after_j == 0:
                    c_ts.PROFILE_ZERO = True

                if ts_after_j == ts_before_j:
                    c_ts.PROFILE_EQ = True

                c_macbi.c_ts.append(c_ts)
            
            self.profile.append(c_macbi)


    def compute_profile_str(self):
        macb_upper = "MACB"
        self.profile_str = []

        for i in range(len(self.watch_array)):
            c_macbi = self.profile[i]
            macbi_i = ""

            for j in range(len(macb_upper)):
                c_ts = c_macbi.c_ts[j]

                if c_ts.PROFILE_ERROR:
                    macbi_i += "!"
                    continue

                if c_ts.PROFILE_ZERO:
                    macbi_i += "0"
                    continue

                if c_ts.PROFILE_UPDATE:
                    macbi_i += macb_upper[j]
                    continue

                if c_ts.PROFILE_EQ and c_macbi.PROFILE_I_EQ:
                    macbi_i += "."
                    continue

                flags_SAMEAS_W0_BEFORE_MACB = [c_ts.PROFILE_SAMEAS_W0_M_BEFORE, c_ts.PROFILE_SAMEAS_W0_A_BEFORE, c_ts.PROFILE_SAMEAS_W0_C_BEFORE, c_ts.PROFILE_SAMEAS_W0_B_BEFORE]
                n_SAMEAS_W0_BEFORE_MACB = flags_SAMEAS_W0_BEFORE_MACB.count(True)

                if n_SAMEAS_W0_BEFORE_MACB > 1:
                    macbi_i += "s"
                    continue
                elif n_SAMEAS_W0_BEFORE_MACB == 1:
                    if c_ts.PROFILE_SAMEAS_W0_M_BEFORE:
                        macbi_i += "m"
                        continue
                    if c_ts.PROFILE_SAMEAS_W0_A_BEFORE:
                        macbi_i += "a"
                        continue
                    if c_ts.PROFILE_SAMEAS_W0_C_BEFORE:
                        macbi_i += "c"
                        continue
                    if c_ts.PROFILE_SAMEAS_W0_B_BEFORE:
                        macbi_i += "b"
                        continue
                
                if c_ts.PROFILE_EARLIER:
                    macbi_i += "-"
                    continue

                if c_ts.PROFILE_LATER:
                    macbi_i += "+"
                    continue   

                macbi_i += "?"
            
            if c_macbi.PROFILE_I_ERROR:
                macbi_i += "!"
            elif c_macbi.PROFILE_I_EQ:
                macbi_i += "."
            else:
                macbi_i += "I"

            self.profile_str.append(macbi_i)

        

def get_current_time(env):
    output = subprocess.check_output([env.currenttime_path]).decode('ascii')
    dec = decimal.Decimal(output)
    return dec

def compare_ts_flag(env, testname, ts1, ts2):
    pass

def compareTimeStamps2(env, testname, ts_before, ts_after, ts_file):
    flags = compare_ts_flag(env, testname, ts1, ts2)


# function to compare two different timestamps and return the difference
def compareTimestamps(env, testname, ts1, ts2):
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

    print(testname, file=env.file_output)


# Function to extract the timestamps of a file with ./prototype_file_fs
# and the Inode number with stat
def statextract(env, testfile):
    try:
        output = subprocess.check_output([env.filets_path, testfile,  '11', '-i']).decode('ascii')
        splitted = output.strip().split(",")
        M = decimal.Decimal(splitted[0])
        A = decimal.Decimal(splitted[1])
        C = decimal.Decimal(splitted[2])
        B = decimal.Decimal(splitted[3])
        I = int(splitted[4])
    except:
        M = None
        A = None
        C = None
        B = None
        I = None
    ts = TimeStamp(M, A, C, B, I)

    return ts

# Function to extract the timestamps of a file with ./prototype_file_fs
# and the Inode number with stat
# def statextract(testfile):
#     Access = ""
#     Modify = ""
#     Change = ""
#     Birth = ""
#     Inode = ""

#     output = str(subprocess.check_output(['./prototype_file_ts', testfile]))
#     beginOutput = output.find("M:")
#     output = output[beginOutput + 3::]

#     findAccess = output.find("A:")
#     Modify = output[:findAccess - 2]
#     output = output[findAccess + 3:]

#     findChange = output.find("C:")
#     Access = output[:findChange - 2]
#     output = output[findChange + 3:]

#     findBirth = output.find("B:")
#     Change = output[:findBirth - 2]
#     Birth = output[findBirth + 3:len(output) - 3]

#     output = str(subprocess.check_output(['stat', testfile]))
#     findInode = output.find("Inode")
#     output = output[findInode + 7::]
#     i = 0
#     while output[i] != " ":
#         Inode += output[i]
#         i += 1

#     ts = TimeStamp(Access, Modify, Change, Birth, Inode)
#     return ts



# prints the before and after timestamps
def print_timestamps(env, ts1, ts2):
    print("Before:", file=env.file_output)
    print("Modify: " + str(ts1.Modify), file=env.file_output)
    print("Access: " + str(ts1.Access), file=env.file_output)
    print("Change: " + str(ts1.Change), file=env.file_output)
    print("Birth:  " + str(ts1.Birth), file=env.file_output)
    print("Inode:  " + str(ts1.Inode), file=env.file_output)
    print("After:", file=env.file_output)
    print("Modify: " + str(ts2.Modify), file=env.file_output)
    print("Access: " + str(ts2.Access), file=env.file_output)
    print("Change: " + str(ts2.Change), file=env.file_output)
    print("Birth:  " + str(ts2.Birth), file=env.file_output)
    print("Inode:  " + str(ts2.Inode), file=env.file_output)


def print_timestamp(file, prefix, ts):
    print(prefix + "Modify: " + str(ts.Modify), file=file)
    print(prefix + "Access: " + str(ts.Access), file=file)
    print(prefix + "Change: " + str(ts.Change), file=file)
    print(prefix + "Birth:  " + str(ts.Birth), file=file)
    print(prefix + "Inode:  " + str(ts.Inode), file=file)


# Function to check if a given program is installed on a system
def doesProgramExist(program):
    try:
        output = str(subprocess.check_output([str(program), '--version']))
    except FileNotFoundError:
        return False
    return True


# Function to open a terminal
def open_terminal():
    if doesProgramExist("terminator"):
        os.spawnlp(os.P_NOWAIT, 'terminator', 'terminator')
    elif doesProgramExist("gnome-terminal"):
        os.spawnlp(os.P_NOWAIT, 'gnome-terminal', 'gnome-terminal')
    elif doesProgramExist("konsole"):
        os.spawnlp(os.P_NOWAIT, 'konsole', 'konsole')
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

    return "testfile.c"

def create_file_random(filename, size=10):
    str_chr = "abcdefghijklmnopqrstuvwxyz0123456789 -/"

    f = open(filename, "w")
    random.seed(a=42)
    for i in range(size):
        r =  random.randrange(0, len(str_chr))
        c = str_chr[r]
        f.write(c)

    f.close()

# Function for removing a file
def remove_file():
    os.system("rm testfile.c")

def dir_navigate(dir_name, new=False):
    if new:
        os.mkdir(dir_name)
    os.chdir(dir_name)
    pyautogui.write("cd " + dir_name)
    pyautogui.press('enter')

def delay():
    time.sleep(1.1)
