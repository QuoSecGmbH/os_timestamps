# This file holds all unique testcases

import os
import subprocess
from dataclasses import dataclass
import pyautogui
import time
import argparse
from shortcuts import *
from utility import *


def access(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    save()
    time.sleep(sleeptime)
    close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def save_no_modify(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    save()
    time.sleep(sleeptime)
    close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Access(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("vim --clean testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Modify(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim --clean testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_safe_no_mod(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim --clean testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_mod_no_save(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim --clean testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("q!")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Access_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("vim -u config_vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Modify_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim -u config_vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_safe_no_mod_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim -u config_vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_mod_no_save_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim -u config_vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("q!")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def nano_Access(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("nano testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.keyDown('ctrl')
    pyautogui.press("x")
    pyautogui.keyUp('ctrl')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("NANO ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def nano_Modify(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("nano testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("x")
    # time.sleep(sleeptime)
    pyautogui.keyDown('ctrl')
    pyautogui.press("x")
    pyautogui.keyUp('ctrl')
    pyautogui.press("y")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("NANO MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def nano_save_no_mod(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("nano testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.keyDown('ctrl')
    pyautogui.press("s")
    pyautogui.keyUp('ctrl')
    pyautogui.keyDown('ctrl')
    pyautogui.press("x")
    pyautogui.keyUp('ctrl')
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("NANO SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def nano_mod_no_save(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("nano testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("x")
    # time.sleep(sleeptime)
    pyautogui.keyDown('ctrl')
    pyautogui.press("x")
    pyautogui.keyUp('ctrl')
    pyautogui.press("n")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("NANO MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def emacs_Access(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    emacs_close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps("EMACS ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def emacs_Modify(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    emacs_save()
    time.sleep(sleeptime)
    emacs_close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps("EMACS MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def emacs_save_no_mod(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    emacs_save()
    time.sleep(sleeptime)
    emacs_close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps("EMACS SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def emacs_mod_no_save(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    emacs_close()
    pyautogui.press("n")
    pyautogui.write("yes")
    pyautogui.press('enter')
    timestamp2 = statextract("testfile.c")

    compareTimestamps("EMACS MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_gedit(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    close()
    time.sleep(sleeptime)
    dont_save()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_atom(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    close()
    time.sleep(sleeptime)
    right_enter()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_geany(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    close()
    time.sleep(sleeptime)
    left_enter()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_sublime(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    subl_close_file()
    time.sleep(sleeptime)
    left_left_enter()
    time.sleep(sleeptime)
    close()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_kate(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    close()
    time.sleep(sleeptime)
    kate_close_file()
    time.sleep(sleeptime)
    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_codeblocks(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    close()
    time.sleep(sleeptime)
    left_left_enter()
    time.sleep(sleeptime)
    close()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_texstudio(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    close()
    time.sleep(sleeptime)
    one_right_enter()
    time.sleep(sleeptime)
    close()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_code(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    code_close_file()
    close()
    time.sleep(sleeptime)
    left_left_enter()
    time.sleep(sleeptime)
    close()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def access_notepadqq(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    notepadqq_close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_notepadqq(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    save()
    time.sleep(sleeptime)
    notepadqq_close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def save_no_modify_notepadqq(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    save()
    time.sleep(sleeptime)
    notepadqq_close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def modify_dont_save_notepadqq(name, sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write(name + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    write("Hello World")
    # time.sleep(sleeptime)
    subl_close_file()
    time.sleep(sleeptime)
    left_left_enter()
    time.sleep(sleeptime)
    notepadqq_close()

    timestamp2 = statextract("testfile.c")

    compareTimestamps(str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def jed_Access(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    jed_close()
    timestamp2 = statextract("testfile.c")

    compareTimestamps("JED ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def jed_Modify(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write("Test")
    jed_save_and_close()
    time.sleep(sleeptime)

    timestamp2 = statextract("testfile.c")

    compareTimestamps("JED MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def jed_safe_no_mod(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    jed_pseudosave_and_close()

    timestamp2 = statextract("testfile.c")

    compareTimestamps("JED SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def jed_mod_no_save(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write("Test")
    jed_close()
    pyautogui.press('n')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("JED MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Access_own_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Modify_own_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_safe_no_mod_own_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_mod_no_save_own_conf(sleeptime, verbose, mode):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("q!")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Access_choose_conf(sleeptime, verbose, mode, file):
    create_file(mode)

    timestamp1 = statextract("testfile.c")

    pyautogui.write("vim -u " + file + " testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM ACCESS TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_Modify_choose_conf(sleeptime, verbose, mode, file):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim -u " + file + " testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_safe_no_mod_choose_conf(sleeptime, verbose, mode, file):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim -u " + file + " testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()


def vim_mod_no_save_choose_conf(sleeptime, verbose, mode, file):
    create_file(mode)

    timestamp1 = statextract("testfile.c")
    pyautogui.write("vim -u " + file + " testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press("i")
    # time.sleep(sleeptime)
    pyautogui.write("Test")
    # time.sleep(sleeptime)
    pyautogui.press('esc')
    pyautogui.write(":")
    pyautogui.write("q!")
    pyautogui.press('enter')

    timestamp2 = statextract("testfile.c")

    compareTimestamps("VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    if (verbose):
        print_timestamps(timestamp1, timestamp2)
        print()

    remove_file()
