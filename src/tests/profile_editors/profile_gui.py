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

# runs all of vim tests
def vim_test(args, sleeptime, mode):
    # Checks if the program is installed
    if (doesProgramExist("vim") == -1):
        print("WARNING: vim not found", file=sys.stderr)
        return
    x = vimVersion()
    print("Vim Version: " + x)
    # prints the testname
    print("vim --clean")
    # runs the tests
    vim_Access(sleeptime, args.verbose, mode)
    vim_Modify(sleeptime, args.verbose, mode)
    vim_safe_no_mod(sleeptime, args.verbose, mode)
    vim_mod_no_save(sleeptime, args.verbose, mode)
    print()
    print("vim set nowritebackup")
    vim_Access_conf(sleeptime, args.verbose, mode)
    vim_Modify_conf(sleeptime, args.verbose, mode)
    vim_safe_no_mod_conf(sleeptime, args.verbose, mode)
    vim_mod_no_save_conf(sleeptime, args.verbose, mode)
    print()


def vim_own_test(args, sleeptime, mode):
    # Checks if the program is installed
    if (doesProgramExist("vim") == -1):
        print("WARNING: vim not found", file=sys.stderr)
        return
    x = vimVersion()
    print("Vim Version: " + x)
    print("vim with system used vimrc")
    # Runs the different vim tests
    vim_Access_own_conf(sleeptime, args.verbose, mode)
    vim_Modify_own_conf(sleeptime, args.verbose, mode)
    vim_safe_no_mod_own_conf(sleeptime, args.verbose, mode)
    vim_mod_no_save_own_conf(sleeptime, args.verbose, mode)
    print()


def vim_choose_test(args, sleeptime, mode):
    if (doesProgramExist("vim") == -1):
        print("WARNING: vim not found", file=sys.stderr)
        return
    x = vimVersion()
    print("Vim Version: " + x)
    print("vim with choosen config file: " + conf_file)
    vim_Access_choose_conf(sleeptime, args.verbose, mode, conf_file)
    vim_Modify_choose_conf(sleeptime, args.verbose, mode, conf_file)
    vim_safe_no_mod_choose_conf(sleeptime, args.verbose, mode, conf_file)
    vim_mod_no_save_choose_conf(sleeptime, args.verbose, mode, conf_file)
    print()


# runs all of nano tests
def nano_test(args, sleeptime, mode):
    if (doesProgramExist("nano") == -1):
        print("WARNING: nano not found", file=sys.stderr)
        return
    x = nanoVersion()
    print("Nano Version: " + x)
    nano_Access(sleeptime, args.verbose, mode)
    nano_Modify(sleeptime, args.verbose, mode)
    nano_save_no_mod(sleeptime, args.verbose, mode)
    nano_mod_no_save(sleeptime, args.verbose, mode)
    print()


# runs all of gedit tests
def gedit_test(args, sleeptime, mode):
    if (doesProgramExist("gedit") == -1):
        print("WARNING: gedit not found", file=sys.stderr)
        return
    x = geditVersion()
    print("Gedit Version: " + x)
    test("gedit", mode)
    modify_dont_save_gedit("gedit", sleeptime, args.verbose, mode)
    print()


# runs all of kate tests
def kate_test(args, sleeptime, mode):
    if (doesProgramExist("kate") == -1):
        print("WARNING: kate not found", file=sys.stderr)
        return
    x = kateVersion()
    print("Kate Version: " + x)
    # test("kate")
    access("kate", sleeptime, args.verbose, mode)
    modify("kate", sleeptime, args.verbose, mode)
    save_no_modify("kate", sleeptime, args.verbose, mode)
    modify_dont_save_kate("kate", sleeptime, args.verbose, mode)
    print()


# runs all of atom tests
def atom_test(args, sleeptime, mode):
    if (doesProgramExist("atom") == -1):
        print("WARNING: atom not found", file=sys.stderr)
        return
    x = atomVersion()
    print("Atom Version: " + x)
    test("atom", mode)
    modify_dont_save_atom("atom", sleeptime, args.verbose, mode)
    print()


# runs all of emacs tests
def emacs_test(args, sleeptime, mode):
    if (doesProgramExist("emacs") == -1):
        print("WARNING: emacs not found", file=sys.stderr)
        return
    x = emacsVersion()
    print("Emacs Version: " + x)
    emacs_Access(sleeptime, args.verbose, mode)
    emacs_Modify(sleeptime, args.verbose, mode)
    emacs_save_no_mod(sleeptime, args.verbose, mode)
    emacs_mod_no_save(sleeptime, args.verbose, mode)
    print()


# runs all of geany tests
def geany_test(args, sleeptime, mode):
    if (doesProgramExist("geany") == -1):
        print("WARNING: geany not found", file=sys.stderr)
        return
    x = geanyVersion()
    print("Geany Version: " + x)
    test("geany", mode)
    modify_dont_save_geany("geany", sleeptime, args.verbose, mode)
    print()


def sublime_text_test(args, sleeptime, mode):
    if (doesProgramExist("subl") == -1):
        print("WARNING: subl/sublime not found", file=sys.stderr)
        return
    x = sublimeVersion()
    print("Sublime Text Version: " + x)
    test("subl", mode)
    modify_dont_save_sublime("subl", sleeptime, args.verbose, mode)
    print()


def codeblocks_test(args, sleeptime, mode):
    x = codeblocksVersion()
    if (x.find("not found") != -1):
        print("WARNING: codeblocks not found", file=sys.stderr)
        return
    print("Codeblocks Version: " + x)
    access("codeblocks", sleeptime * 2, args.verbose, mode)
    modify("codeblocks", sleeptime * 2, args.verbose, mode)
    save_no_modify("codeblocks", sleeptime * 2, args.verbose, mode)
    modify_dont_save_codeblocks("codeblocks", sleeptime * 2, args.verbose, mode)
    print()


def bluefish_test(args, sleeptime, mode):
    if (doesProgramExist("bluefish") == -1):
        print("WARNING: bluefish not found", file=sys.stderr)
        return
    x = bluefishVersion()
    print("Bluefish Text Version: " + x)
    if (mode != 2):
        access("bluefish", sleeptime, args.verbose, mode)
        modify("bluefish", sleeptime, args.verbose, mode)
        save_no_modify("bluefish", sleeptime, args.verbose, mode)
        modify_dont_save_codeblocks("bluefish", sleeptime, args.verbose, mode)
    else:
        print("Not really working with this filesize")
    print()


def texstudio_test(args, sleeptime, mode):
    if (doesProgramExist("texstudio") == -1):
        print("WARNING: texstudio not found", file=sys.stderr)
        return
    x = texstudioVersion()
    print("Texstudio Version: " + x)
    if (mode != 2):
        access("texstudio", sleeptime, args.verbose, mode)
        modify("texstudio", sleeptime, args.verbose, mode)
        save_no_modify("texstudio", sleeptime, args.verbose, mode)
        modify_dont_save_texstudio("texstudio", sleeptime, args.verbose, mode)
    else:
        print("Not really working with this filesize")
    print()


def visualstudiocode_test(args, sleeptime, mode):
    if (doesProgramExist("code") == -1):
        print("WARNING: visualstudiocode not found", file=sys.stderr)
        return
    x = visualstudiocodeVersion()
    print("Visual Studio Code Version: " + x)
    access("code", sleeptime, args.verbose, mode)
    modify("code", sleeptime, args.verbose, mode)
    save_no_modify("code", sleeptime, args.verbose, mode)
    modify_dont_save_code("code", sleeptime, args.verbose, mode)
    print()


def leafpad_test(args, sleeptime, mode):
    if (doesProgramExist("leafpad") == -1):
        print("WARNING: leafpad not found", file=sys.stderr)
        return
    x = leafpadversion()
    print("Leafpad Version: " + x)
    access("leafpad", sleeptime, args.verbose, mode)
    modify("leafpad", sleeptime, args.verbose, mode)
    save_no_modify("leafpad", sleeptime, args.verbose, mode)
    modify_dont_save_codeblocks("leafpad", sleeptime, args.verbose, mode)
    print()


def notepadqq_test(args, sleeptime, mode):
    if (doesProgramExist("notepadqq") == -1):
        print("WARNING: notepadqq not found", file=sys.stderr)
        return
    x = notepadqqVersion()
    print("Notepadqq Version: " + x)
    if (not mode == 2):
        access_notepadqq("notepadqq", sleeptime, args.verbose, mode)
        modify_notepadqq("notepadqq", sleeptime, args.verbose, mode)
        save_no_modify_notepadqq("notepadqq", sleeptime, args.verbose, mode)
        modify_dont_save_notepadqq("notepadqq", sleeptime, args.verbose, mode)
    else:
        print("Not perfomant for big files")
    print()


def jed_test(args, sleeptime, mode):
    if (doesProgramExist("jed") == -1):
        print("WARNING: jed not found", file=sys.stderr)
        return
    x = jedVersion()
    print("Jed Version: " + x)
    jed_Access(sleeptime, args.verbose, mode)
    jed_Modify(sleeptime, args.verbose, mode)
    jed_safe_no_mod(sleeptime, args.verbose, mode)
    jed_mod_no_save(sleeptime, args.verbose, mode)
    print()


# runs all tests
def profile_gui(args, targets):
    # global sleeptime
    sys.stdout = open('editors_profile.txt', 'w')

    start_time = datetime.now()
    open_terminal()
    time.sleep(args.sleeptime)
    if (args.empty):
        print("Empty File Test")
        run_test(args, targets, args.sleeptime, 0)

    if (args.small):
        print("Small File Test")
        run_test(args, targets, args.sleeptime, 1)

    if (args.large):
        sleeptime = args.sleeptime * 1.5
        print("Big File Test")
        run_test(args, targets, sleeptime, 2)

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
def run_test(args, targets, sleeptime, mode):
    if (targets["EDITOR.vim"]):
        vim_test(args, sleeptime, mode)
    if (targets["EDITOR.vim_own_conf"]):
        vim_own_test(args, sleeptime, mode)
    if (targets["EDITOR.vim_choose_conf"]):
        vim_choose_test(args, sleeptime, mode)
    if (targets["EDITOR.nano"]):
        nano_test(args, sleeptime, mode)
    if (targets["EDITOR.gedit"]):
        gedit_test(args, sleeptime, mode)
    if (targets["EDITOR.kate"]):
        kate_test(args, sleeptime, mode)  # Problems with fonts I think
    if (targets["EDITOR.atom"]):
        atom_test(args, sleeptime, mode)
    if (targets["EDITOR.emacs"]):
        emacs_test(args, sleeptime, mode)
    if (targets["EDITOR.geany"]):
        geany_test(args, sleeptime, mode)
    if (targets["EDITOR.sublime"]):
        sublime_text_test(args, sleeptime, mode)
    if (targets["EDITOR.codeblocks"]):
        codeblocks_test(args, sleeptime, mode)
    if (targets["EDITOR.bluefish"]):
        bluefish_test(args, sleeptime, mode)
    if (targets["EDITOR.texstudio"]):
        texstudio_test(args, sleeptime, mode)
    if (targets["EDITOR.code"]):
        visualstudiocode_test(args, sleeptime, mode)
    if (targets["EDITOR.leafpad"]):
        leafpad_test(args, sleeptime, mode)
    if (targets["EDITOR.notepadqq"]):
        notepadqq_test(args, sleeptime, mode)
    if (targets["EDITOR.jed"]):
        jed_test(args, sleeptime, mode)


# parses the run arguments of the program
# "-h" will give an overview of the available options
def parse():
    # What targets should be run?
    targets = dict()
    targets["EDITOR.vim"] = False
    targets["EDITOR.vim_own_conf"] = False
    targets["EDITOR.vim_choose_conf"] = False
    targets["EDITOR.nano"] = False
    targets["EDITOR.gedit"] = False
    targets["EDITOR.kate"] = False
    targets["EDITOR.emacs"] = False
    targets["EDITOR.atom"] = False
    targets["EDITOR.geany"] = False
    targets["EDITOR.sublime"] = False
    targets["EDITOR.codeblocks"] = False
    targets["EDITOR.bluefish"] = False
    targets["EDITOR.texstudio"] = False
    targets["EDITOR.code"] = False
    targets["EDITOR.leafpad"] = False
    targets["EDITOR.notepadqq"] = False
    targets["EDITOR.jed"] = False

    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action='store_true', default=False, help="prints timestamp before and after test as well as inode number")
    parser.add_argument("-st", "--SLEEPTIME", dest="sleeptime", default=6, help="sleep timer")
   
    parser.add_argument("--test", "-t", dest='test', action='append', help="Include the target (can be used multiple times)")
    parser.add_argument("--vim-conf", "-vc", dest='vim_conf', default=None, help="Specific conf file to use for vim (.vimrc)")


    parser.add_argument("--empty", action='store_true', help="runs the tests with empty files")
    parser.add_argument("--small", action='store_true', help="runs the tests with small files")
    parser.add_argument("--large", action='store_true', help="runs the tests with large files")
    args = parser.parse_args()

    if args.test is not None:
        for t in args.test:
            if t in targets:
                targets[t] = True
            elif "EDITOR."+t in targets:
                targets["EDITOR."+t] = True
            elif "FILEMANAGER."+t in targets:
                targets["FILEMANAGER"+t] = True
            else:
                print("WARNING: test target " + t + " not found.")
    else:
        for t in targets:
            targets[t] = True

    if ((not args.empty) and (not args.small) and (not args.large)):
        args.empty = True
        args.small = True
        args.large = True

    return args, targets

def main():
    # executes the parsing function
    args, targets = parse()
    # executes the editor tests
    profile_gui(args, targets)

main()