# This file has the main code and is also responsible for parsing the arguments
# and executing all the testcases

import os
import subprocess
from dataclasses import dataclass
import pyautogui
import time
import sys
import argparse
from datetime import datetime
from shortcuts import *
from tests_editors import *
from utility import *
from versions import *

# Wait time for gui programms to start and execute commands
sleeptime = 6

# Saves all not found editors to print out at the end
notFoundEditors = []

# What Editors should be run?
vim = False
vim_own_conf = False
vim_choose_conf = False
nano = False
gedit = False
kate = False
emacs = False
atom = False
geany = False
sublime = False
codeblocks = False
bluefish = False
texstudio = False
code = False
leafpad = False
notepadqq = False
jed = False

# Should be run verbose?
verbose = False

# Anything has been set?
anyset = False

# What filesize
empty = False
small = False
large = False

# Config File
conf_file = ""


# runs all of vim tests
def vim_test(mode):
    # Checks if the program is installed
    if (doesProgramExist("vim") == -1):
        notFoundEditors.append("VIM")
        return
    x = vimVersion()
    print("Vim Version: " + x)
    # prints the testname
    print("vim --clean")
    # runs the tests
    vim_Access(sleeptime, verbose, mode)
    vim_Modify(sleeptime, verbose, mode)
    vim_safe_no_mod(sleeptime, verbose, mode)
    vim_mod_no_save(sleeptime, verbose, mode)
    print()
    print("vim set nowritebackup")
    vim_Access_conf(sleeptime, verbose, mode)
    vim_Modify_conf(sleeptime, verbose, mode)
    vim_safe_no_mod_conf(sleeptime, verbose, mode)
    vim_mod_no_save_conf(sleeptime, verbose, mode)
    print()


def vim_own_test(mode):
    # Checks if the program is installed
    if (doesProgramExist("vim") == -1):
        notFoundEditors.append("VIM")
        return
    x = vimVersion()
    print("Vim Version: " + x)
    print("vim with system used vimrc")
    # Runs the different vim tests
    vim_Access_own_conf(sleeptime, verbose, mode)
    vim_Modify_own_conf(sleeptime, verbose, mode)
    vim_safe_no_mod_own_conf(sleeptime, verbose, mode)
    vim_mod_no_save_own_conf(sleeptime, verbose, mode)
    print()


def vim_choose_test(mode):
    if (doesProgramExist("vim") == -1):
        notFoundEditors.append("VIM")
        return
    x = vimVersion()
    print("Vim Version: " + x)
    print("vim with choosen config file: " + conf_file)
    vim_Access_choose_conf(sleeptime, verbose, mode, conf_file)
    vim_Modify_choose_conf(sleeptime, verbose, mode, conf_file)
    vim_safe_no_mod_choose_conf(sleeptime, verbose, mode, conf_file)
    vim_mod_no_save_choose_conf(sleeptime, verbose, mode, conf_file)
    print()


# runs all of nano tests
def nano_test(mode):
    if (doesProgramExist("nano") == -1):
        notFoundEditors.append("NANO")
        return
    x = nanoVersion()
    print("Nano Version: " + x)
    nano_Access(sleeptime, verbose, mode)
    nano_Modify(sleeptime, verbose, mode)
    nano_save_no_mod(sleeptime, verbose, mode)
    nano_mod_no_save(sleeptime, verbose, mode)
    print()


# runs all of gedit tests
def gedit_test(mode):
    if (doesProgramExist("gedit") == -1):
        notFoundEditors.append("GEDIT")
        return
    x = geditVersion()
    print("Gedit Version: " + x)
    test("gedit", mode)
    modify_dont_save_gedit("gedit", sleeptime, verbose, mode)
    print()


# runs all of kate tests
def kate_test(mode):
    if (doesProgramExist("kate") == -1):
        notFoundEditors.append("KATE")
        return
    x = kateVersion()
    print("Kate Version: " + x)
    # test("kate")
    access("kate", sleeptime, verbose, mode)
    modify("kate", sleeptime, verbose, mode)
    save_no_modify("kate", sleeptime, verbose, mode)
    modify_dont_save_kate("kate", sleeptime, verbose, mode)
    print()


# runs all of atom tests
def atom_test(mode):
    if (doesProgramExist("atom") == -1):
        notFoundEditors.append("ATOM")
        return
    x = atomVersion()
    print("Atom Version: " + x)
    test("atom", mode)
    modify_dont_save_atom("atom", sleeptime, verbose, mode)
    print()


# runs all of emacs tests
def emacs_test(mode):
    if (doesProgramExist("emacs") == -1):
        notFoundEditors.append("EMACS")
        return
    x = emacsVersion()
    print("Emacs Version: " + x)
    emacs_Access(sleeptime, verbose, mode)
    emacs_Modify(sleeptime, verbose, mode)
    emacs_save_no_mod(sleeptime, verbose, mode)
    emacs_mod_no_save(sleeptime, verbose, mode)
    print()


# runs all of geany tests
def geany_test(mode):
    if (doesProgramExist("geany") == -1):
        notFoundEditors.append("GEANY")
        return
    x = geanyVersion()
    print("Geany Version: " + x)
    test("geany", mode)
    modify_dont_save_geany("geany", sleeptime, verbose, mode)
    print()


def sublime_text_test(mode):
    if (doesProgramExist("subl") == -1):
        notFoundEditors.append("SUBLIME")
        return
    x = sublimeVersion()
    print("Sublime Text Version: " + x)
    test("subl", mode)
    modify_dont_save_sublime("subl", sleeptime, verbose, mode)
    print()


def codeblocks_test(mode):
    x = codeblocksVersion()
    if (x.find("not found") != -1):
        notFoundEditors.append("CODEBLOCKS")
        return
    print("Codeblocks Version: " + x)
    access("codeblocks", sleeptime * 2, verbose, mode)
    modify("codeblocks", sleeptime * 2, verbose, mode)
    save_no_modify("codeblocks", sleeptime * 2, verbose, mode)
    modify_dont_save_codeblocks("codeblocks", sleeptime * 2, verbose, mode)
    print()


def bluefish_test(mode):
    if (doesProgramExist("bluefish") == -1):
        notFoundEditors.append("BLUEFISH")
        return
    x = bluefishVersion()
    print("Bluefish Text Version: " + x)
    if (mode != 2):
        access("bluefish", sleeptime, verbose, mode)
        modify("bluefish", sleeptime, verbose, mode)
        save_no_modify("bluefish", sleeptime, verbose, mode)
        modify_dont_save_codeblocks("bluefish", sleeptime, verbose, mode)
    else:
        print("Not really working with this filesize")
    print()


def texstudio_test(mode):
    if (doesProgramExist("texstudio") == -1):
        notFoundEditors.append("texstudio")
        return
    x = texstudioVersion()
    print("Texstudio Version: " + x)
    if (mode != 2):
        access("texstudio", sleeptime, verbose, mode)
        modify("texstudio", sleeptime, verbose, mode)
        save_no_modify("texstudio", sleeptime, verbose, mode)
        modify_dont_save_texstudio("texstudio", sleeptime, verbose, mode)
    else:
        print("Not really working with this filesize")
    print()


def visualstudiocode_test(mode):
    if (doesProgramExist("code") == -1):
        notFoundEditors.append("visualstudiocode")
        return
    x = visualstudiocodeVersion()
    print("Visual Studio Code Version: " + x)
    access("code", sleeptime, verbose, mode)
    modify("code", sleeptime, verbose, mode)
    save_no_modify("code", sleeptime, verbose, mode)
    modify_dont_save_code("code", sleeptime, verbose, mode)
    print()


def leafpad_test(mode):
    if (doesProgramExist("leafpad") == -1):
        notFoundEditors.append("leafpad")
        return
    x = leafpadversion()
    print("Leafpad Version: " + x)
    access("leafpad", sleeptime, verbose, mode)
    modify("leafpad", sleeptime, verbose, mode)
    save_no_modify("leafpad", sleeptime, verbose, mode)
    modify_dont_save_codeblocks("leafpad", sleeptime, verbose, mode)
    print()


def notepadqq_test(mode):
    if (doesProgramExist("notepadqq") == -1):
        notFoundEditors.append("notepadqq")
        return
    x = notepadqqVersion()
    print("Notepadqq Version: " + x)
    if (not mode == 2):
        access_notepadqq("notepadqq", sleeptime, verbose, mode)
        modify_notepadqq("notepadqq", sleeptime, verbose, mode)
        save_no_modify_notepadqq("notepadqq", sleeptime, verbose, mode)
        modify_dont_save_notepadqq("notepadqq", sleeptime, verbose, mode)
    else:
        print("Not perfomant for big files")
    print()


def jed_test(mode):
    if (doesProgramExist("jed") == -1):
        notFoundEditors.append("jed")
        return
    x = jedVersion()
    print("Jed Version: " + x)
    jed_Access(sleeptime, verbose, mode)
    jed_Modify(sleeptime, verbose, mode)
    jed_safe_no_mod(sleeptime, verbose, mode)
    jed_mod_no_save(sleeptime, verbose, mode)
    print()


# runs all tests
def editorTest():
    global sleeptime
    sys.stdout = open('editors_profile.txt', 'w')

    start_time = datetime.now()
    open_terminal()
    time.sleep(sleeptime)
    if (empty):
        print("Empty File Test")
        run_test(0)

    if (small):
        print("Small File Test")
        run_test(1)

    if (large):
        sleeptime = sleeptime * 1.5
        print("Big File Test")
        run_test(2)

    if (len(notFoundEditors) != 0):
        print("Editors that couldnt be found")
        listofeditors = ""
        for i in range(len(notFoundEditors)):
            if (i != 0):
                listofeditors += ","
            listofeditors += notFoundEditors[i]
        print(listofeditors)

    close_terminal()

    os.system("touch errors")
    os.system("rm errors")

    end_time = datetime.now()
    print('EXECUTION TIME: {}'.format(end_time - start_time))

    sys.stdout.close()


def test(name, mode):
    access(name, sleeptime, verbose, mode)
    modify(name, sleeptime, verbose, mode)
    save_no_modify(name, sleeptime, verbose, mode)


# Executes all testcases of a given mode for all editors if the are set to be run
def run_test(mode):
    if (vim):
        vim_test(mode)
    if (vim_own_conf):
        vim_own_test(mode)
    if (vim_choose_conf):
        vim_choose_test(mode)
    if (nano):
        nano_test(mode)
    if (gedit):
        gedit_test(mode)
    if (kate):
        kate_test(mode)  # Problems with fonts I think
    if (atom):
        atom_test(mode)
    if (emacs):
        emacs_test(mode)
    if (geany):
        geany_test(mode)
    if (sublime):
        sublime_text_test(mode)
    if (codeblocks):
        codeblocks_test(mode)
    if (bluefish):
        bluefish_test(mode)
    if (texstudio):
        texstudio_test(mode)
    if (code):
        visualstudiocode_test(mode)
    if (leafpad):
        leafpad_test(mode)
    if (notepadqq):
        notepadqq_test(mode)
    if (jed):
        jed_test(mode)


# Sets all editors on true
def alltrue():
    global vim
    global nano
    global gedit
    global geany
    global kate
    global atom
    global sublime
    global emacs
    global codeblocks
    global bluefish
    global texstudio
    global code
    global leafpad
    global notepadqq
    global jed

    vim = True
    nano = True
    gedit = True
    emacs = True
    geany = True
    atom = True
    sublime = True
    kate = True
    codeblocks = True
    bluefish = True
    texstudio = True
    code = True
    leafpad = True
    notepadqq = True
    jed = True


# parses the run arguments of the program
# "-h" will give an overview of the available options
def parse():
    global vim
    global vim_own_conf
    global vim_choose_conf
    global nano
    global gedit
    global geany
    global kate
    global atom
    global sublime
    global emacs
    global codeblocks
    global bluefish
    global texstudio
    global code
    global leafpad
    global notepadqq
    global jed

    global sleeptime
    global verbose
    global anyset

    global empty
    global small
    global large

    global conf_file

    parser = argparse.ArgumentParser()
    parser.add_argument("-a", "--all", action='store_true', help="runs all tests")
    parser.add_argument("-v", "--verbose", action='store_true',
                        help="prints timestamp before and after test as well as inode number")
    parser.add_argument("-t", "--time", nargs=1, help="set sleep timer manually")

    parser.add_argument("--vim", action='store_true', help="runs the vim tests")
    parser.add_argument("--vimown", action='store_true', help="runs the vim tests with system used vimrc")
    parser.add_argument("--vimchoose", nargs=1, help="runs the vim tests with choosen config file")
    parser.add_argument("--nano", action='store_true', help="runs the nano tests")
    parser.add_argument("--gedit", action='store_true', help="runs the gedit tests")
    parser.add_argument("--kate", action='store_true', help="runs the kate tests")
    parser.add_argument("--sublime", action='store_true', help="runs the sublime tests")
    parser.add_argument("--geany", action='store_true', help="runs the geany tests")
    parser.add_argument("--atom", action='store_true', help="runs the atom tests")
    parser.add_argument("--emacs", action='store_true', help="runs the emacs tests")
    parser.add_argument("--codeblocks", action='store_true', help="runs the codeblocks tests")
    parser.add_argument("--bluefish", action='store_true', help="runs the bluefish tests")
    parser.add_argument("--texstudio", action='store_true', help="runs the texstudio tests")
    parser.add_argument("--code", action='store_true', help="runs the visualstudiocode tests")
    parser.add_argument("--leafpad", action='store_true', help="runs the leafpad tests")
    parser.add_argument("--notepadqq", action='store_true', help="runs the notepadqq tests")
    parser.add_argument("--jed", action='store_true', help="runs the jed tests")

    parser.add_argument("--empty", action='store_true', help="runs the tests with empty files")
    parser.add_argument("--small", action='store_true', help="runs the tests with small files")
    parser.add_argument("--large", action='store_true', help="runs the tests with large files")
    args = parser.parse_args()

    if (args.all):
        alltrue()
    if (args.verbose):
        verbose = True
    if (args.time):
        sleeptime = float(args.time[0])
    if (args.vim):
        vim = True
        anyset = True
    if (args.vimown):
        vim_own_conf = True
        anyset = True
    if (args.vimchoose):
        vim_choose_conf = True
        conf_file = str(args.vimchoose[0])
        anyset = True
    if (args.nano):
        nano = True
        anyset = True
    if (args.gedit):
        gedit = True
        anyset = True
    if (args.kate):
        kate = True
        anyset = True
    if (args.sublime):
        sublime = True
        anyset = True
    if (args.geany):
        geany = True
        anyset = True
    if (args.atom):
        atom = True
        anyset = True
    if (args.emacs):
        emacs = True
        anyset = True
    if (args.codeblocks):
        codeblocks = True
        anyset = True
    if (args.bluefish):
        bluefish = True
        anyset = True
    if (args.texstudio):
        texstudio = True
        anyset = True
    if (args.code):
        code = True
        anyset = True
    if (args.leafpad):
        leafpad = True
        anyset = True
    if (args.notepadqq):
        notepadqq = True
        anyset = True
    if (args.jed):
        jed = True
        anyset = True

    if (not anyset):
        alltrue()
    if (args.empty):
        empty = True
    if (args.small):
        small = True
    if (args.large):
        large = True
    if ((not empty) and (not small) and (not large)):
        empty = True
        small = True
        large = True


# executes the parsing function
parse()
# executes the editor tests
editorTest()
