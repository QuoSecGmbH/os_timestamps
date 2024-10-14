# This file holds all unique testcases

import os
import subprocess
from dataclasses import dataclass
import pyautogui
import time
import argparse
# from shortcuts import *
import shortcuts
# from utility import *
import utility
import sys


def test_template_editor_singlesize(env, sleeptime, filesize, target_code, test_code, test_description, fun_actions, target_prompt):
    # See https://yaps8.github.io/blog/02_Testing_POSIX.html
    if env.args.verbose: print("  BEGIN:", target_code + "." + test_code, "- filesize:", filesize)
    if env.args.verbose:
        if test_description:
            print("  Description:", test_description)

    # Create the file, it actually closes it, so no need for stat
    p1 = "testfile.c"
    utility.create_file_random(p1, filesize)

    profile = utility.ProfileInfo(target_code, test_code, filesize, test_description)
    profile.watch_array.append(("file", p1))

    profile.profile_init(env)
    fun_actions(env, sleeptime, target_prompt)
    profile.profile_analyze(env)

    # utility.compareTimestamps(env, str(target_code).upper() + "." + test_code, t_before, t_after, ts_file)

    if (env.args.verbose):
        utility.print_timestamps(env, profile.multi_stat_before[0], profile.multi_stat_after[0])
        print("", file=env.file_output)

    if env.args.verbose: print("  END:", target_code + "." + test_code, "- filesize:", filesize)

    return profile

    # utility.remove_file()

def test_template_editor(env, sleeptime, target_code, target_type, test_code, test_description, fun_actions, target_prompt):
    if target_type + "." + test_code not in env.operations:
        return
    
    utility.dir_navigate(test_code, new=True)

    profiles = []
    for s in env.sizes:
        dir_name = "size_" + str(s)
        utility.dir_navigate(dir_name, new=True)

        profile = test_template_editor_singlesize(env, sleeptime, s, target_code, test_code, test_description, fun_actions, target_prompt)
        profiles.append(profile)
        if env.args.verbose:
            profile.profile_verbose_print(file = sys.stdout, print_path=True)

        utility.dir_navigate("..")
    utility.dir_navigate("..")

    if len(profiles) != 0:
        p1 = profiles[0]
        report_all = False
        for profile in profiles[1:]:
            if not p1.profile_mostly_same(profile):
                report_all = True

        if report_all:
            profiles_report = profiles
            print("WARNING: Conflictual Results!")
        else:
            profiles_report = [p1]

        for p in profiles_report:
            p.profile_report(env, print_path = report_all, print_filesize = report_all)


def access(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write(prompt + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.close()
    timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, str(prompt).upper() + " ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
        # utility.print_timestamps(env, timestamp1, timestamp2)
        # print("", file=env.file_output)

    # utility.remove_file()


def modify(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write(prompt + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.save()
    time.sleep(sleeptime)
    shortcuts.close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, str(prompt).upper() + " MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def save_no_modify(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write(prompt + " testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.save()
    time.sleep(sleeptime)
    shortcuts.close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, str(prompt).upper() + " SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Access(env, sleeptime, prompt):
    # utility.create_file(mode)

    # t_before = utility.get_current_time(env)
    # print("Current time:", t_before)
    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("vim --clean testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    # timestamp2 = utility.statextract(env, "testfile.c")

    # utility.compareTimestamps(env, "VIM ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Modify(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_safe_no_mod(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("vim --clean testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_mod_no_save(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Access_conf(env, sleeptime, prompt):
    # utility.create_file(mode)
    open("config_vim", 'w').write("set nowritebackup")

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("vim -u config_vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Modify_conf(env, sleeptime, prompt):
    # utility.create_file(mode)
    open("config_vim", 'w').write("set nowritebackup")

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_safe_no_mod_conf(env, sleeptime, prompt):
    # utility.create_file(mode)
    open("config_vim", 'w').write("set nowritebackup")

    timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("vim -u config_vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_mod_no_save_conf(env, sleeptime, prompt):
    # utility.create_file(mode)
    open("config_vim", 'w').write("set nowritebackup")

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def nano_Access(env, sleeptime, prompt):
    # utility.create_file(mode)

    # print("nano1")
    # timestamp1 = utility.statextract(env,"testfile.c")
    # print("nano2")
    pyautogui.write("nano testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.keyDown('ctrl')
    pyautogui.press("x")
    pyautogui.keyUp('ctrl')

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "NANO ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def nano_Modify(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "NANO MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def nano_save_no_mod(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "NANO SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def nano_mod_no_save(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "NANO MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def emacs_Access(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.emacs_close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "EMACS ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def emacs_Modify(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.emacs_save()
    time.sleep(sleeptime)
    shortcuts.emacs_close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "EMACS MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def emacs_save_no_mod(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.emacs_save()
    time.sleep(sleeptime)
    shortcuts.emacs_close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "EMACS SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def emacs_mod_no_save(env, sleeptime, prompt):
    # utility.create_file(mode)

    timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("emacs testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.emacs_close()
    pyautogui.press("n")
    pyautogui.write("yes")
    pyautogui.press('enter')
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "EMACS MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_gedit(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("gedit testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.close()
    time.sleep(sleeptime)
    shortcuts.dont_save()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_atom(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("atom testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.close()
    time.sleep(sleeptime)
    shortcuts.right_enter()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_geany(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("geany testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.close()
    time.sleep(sleeptime)
    shortcuts.left_enter()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_sublime(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("sublime testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.subl_close_file()
    time.sleep(sleeptime)
    shortcuts.left_left_enter()
    time.sleep(sleeptime)
    shortcuts.close()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_kate(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("kate testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.close()
    time.sleep(sleeptime)
    shortcuts.kate_close_file()
    time.sleep(sleeptime)
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_codeblocks(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("codeblocks testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.close()
    time.sleep(sleeptime)
    shortcuts.left_left_enter()
    time.sleep(sleeptime)
    shortcuts.close()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_texstudio(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("texstudio testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.close()
    time.sleep(sleeptime)
    shortcuts.one_right_enter()
    time.sleep(sleeptime)
    shortcuts.close()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_code(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("code testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.code_close_file()
    shortcuts.close()
    time.sleep(sleeptime)
    shortcuts.left_left_enter()
    time.sleep(sleeptime)
    shortcuts.close()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def access_notepadqq(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("notepadqq testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.notepadqq_close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_notepadqq(env, sleeptim, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("notepadqq testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.save()
    time.sleep(sleeptime)
    shortcuts.notepadqq_close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def save_no_modify_notepadqq(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("notepadqq testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.save()
    time.sleep(sleeptime)
    shortcuts.notepadqq_close()
    # timestamp2 = utility.statextract("testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def modify_dont_save_notepadqq(env, sleeptime, prompt):
    # utility.create_file(mode)

    timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("notepadqq testfile.c &> errors")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.write("Hello World")
    # time.sleep(sleeptime)
    shortcuts.subl_close_file()
    time.sleep(sleeptime)
    shortcuts.left_left_enter()
    time.sleep(sleeptime)
    shortcuts.notepadqq_close()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env,str(name).upper() + " MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def jed_Access(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.jed_close()
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "JED ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def jed_Modify(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write("Test")
    shortcuts.jed_save_and_close()
    time.sleep(sleeptime)

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "JED MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def jed_safe_no_mod(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    shortcuts.jed_pseudosave_and_close()

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "JED SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def jed_mod_no_save(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("jed testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write("Test")
    shortcuts.jed_close()
    pyautogui.press('n')

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "JED MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Access_own_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Modify_own_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_safe_no_mod_own_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("vim testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_mod_no_save_own_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    timestamp1 = utility.statextract(env,"testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Access_choose_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")

    pyautogui.write("vim -u " + env.args.vim_conf + " testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.press(':')
    pyautogui.press('q')
    pyautogui.press('enter')
    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM ACCESS TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_Modify_choose_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("vim -u " + env.args.vim_conf + " testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_safe_no_mod_choose_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("vim -u " + env.args.vim_conf + " testfile.c")
    pyautogui.press('enter')
    time.sleep(sleeptime)
    pyautogui.write(":")
    pyautogui.write("wq")
    pyautogui.press('enter')

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM SAVE WITHOUT MODIFICATION TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()


def vim_mod_no_save_choose_conf(env, sleeptime, prompt):
    # utility.create_file(mode)

    # timestamp1 = utility.statextract(env,"testfile.c")
    pyautogui.write("vim -u " + env.args.vim_conf + " testfile.c")
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

    # timestamp2 = utility.statextract(env,"testfile.c")

    # utility.compareTimestamps(env, "VIM MODIFY BUT DONT SAVE TEST: ", timestamp1, timestamp2)

    # if (env.args.verbose):
    #     utility.print_timestamps(env, timestamp1, timestamp2)
    #     print("", file=env.file_output)

    # utility.remove_file()
