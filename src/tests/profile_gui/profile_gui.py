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
# import shortcuts
from tests_editors import *
import utility
import versions


# runs all of vim tests
def vim_test(env, sleeptime, target_code):
    # Checks if the program is installed
    if (utility.doesProgramExist("vim") == -1):
        print("WARNING: vim not found", file=sys.stderr)
        return
    x = versions.vimVersion()
    print("Vim Version: " + x, file=env.file_output)
    # prints the testname
    print("vim --clean", file=env.file_output)
    # runs the tests
    # if "EDITOR.access" in env.operations: vim_Access(env, sleeptime, mode)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "access", None, vim_Access)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify", None, vim_Modify)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "save_no_modify", None, vim_safe_no_mod)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify_no_save", None, vim_mod_no_save)
    print("", file=env.file_output)


def vim_conf_test(env, sleeptime, target_code):
    # Checks if the program is installed
    if (utility.doesProgramExist("vim") == -1):
        print("WARNING: vim not found", file=sys.stderr)
        return
    x = versions.vimVersion()
    print("Vim Version: " + x, file=env.file_output)
    print("vim set nowritebackup", file=env.file_output)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "access", None, vim_Access_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify", None, vim_Modify_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "save_no_modify", None, vim_safe_no_mod_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify_no_save", None, vim_mod_no_save_conf)
    print("", file=env.file_output)


def vim_own_test(env, sleeptime, target_code):
    # Checks if the program is installed
    if (utility.doesProgramExist("vim") == -1):
        print("WARNING: vim not found", file=sys.stderr)
        return
    x = versions.vimVersion()
    print("Vim Version: " + x, file=env.file_output)
    print("vim with system used vimrc", file=env.file_output)
    # Runs the different vim tests
    test_template_editor(env, sleeptime, target_code, "EDITOR", "access", None, vim_Access_own_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify", None, vim_Modify_own_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "save_no_modify", None, vim_safe_no_mod_own_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify_no_save", None, vim_mod_no_save_own_conf)
    print("", file=env.file_output)


def vim_choose_test(env, sleeptime, target_code):
    if (utility.doesProgramExist("vim") == -1):
        print("WARNING: vim not found", file=sys.stderr)
        return
    x = versions.vimVersion()
    print("Vim Version: " + x, file=env.file_output)
    print("vim with choosen config file: " + str(env.args.vim_conf), file=env.file_output)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "access", None, vim_Access_choose_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify", None, vim_Modify_choose_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "save_no_modify", None, vim_safe_no_mod_choose_conf)
    test_template_editor(env, sleeptime, target_code, "EDITOR", "modify_no_save", None, vim_mod_no_save_choose_conf)
    print("", file=env.file_output)


# runs all of nano tests
def nano_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("nano") == -1):
        print("WARNING: nano not found", file=sys.stderr)
        return
    x = versions.nanoVersion()
    print("Nano Version: " + x, file=env.file_output)
    nano_Access(env, sleeptime, mode)
    nano_Modify(env, sleeptime, mode)
    nano_save_no_mod(env, sleeptime, mode)
    nano_mod_no_save(env, sleeptime, mode)
    print("", file=env.file_output)


# runs all of gedit tests
def gedit_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("gedit") == -1):
        print("WARNING: gedit not found", file=sys.stderr)
        return
    x = versions.geditVersion()
    print("Gedit Version: " + x, file=env.file_output)
    test("gedit", mode, env)
    modify_dont_save_gedit("gedit", sleeptime, env.args.verbose, mode)
    print("", file=env.file_output)


# runs all of kate tests
def kate_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("kate") == -1):
        print("WARNING: kate not found", file=sys.stderr)
        return
    x = versions.kateVersion()
    print("Kate Version: " + x, file=env.file_output)
    # test("kate")
    access("kate", sleeptime, env.args.verbose, mode)
    modify("kate", sleeptime, env.args.verbose, mode)
    save_no_modify("kate", sleeptime, env.args.verbose, mode)
    modify_dont_save_kate("kate", sleeptime, env.args.verbose, mode)
    print("", file=env.file_output)


# runs all of atom tests
def atom_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("atom") == -1):
        print("WARNING: atom not found", file=sys.stderr)
        return
    x = versions.atomVersion()
    print("Atom Version: " + x, file=env.file_output)
    test("atom", mode, env)
    modify_dont_save_atom("atom", sleeptime, env.args.verbose, mode)
    print("", file=env.file_output)


# runs all of emacs tests
def emacs_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("emacs") == -1):
        print("WARNING: emacs not found", file=sys.stderr)
        return
    x = versions.emacsVersion()
    print("Emacs Version: " + x, file=env.file_output)
    emacs_Access(env, sleeptime, mode)
    emacs_Modify(env, sleeptime, mode)
    emacs_save_no_mod(env, sleeptime, mode)
    emacs_mod_no_save(env, sleeptime, mode)
    print("", file=env.file_output)


# runs all of geany tests
def geany_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("geany") == -1):
        print("WARNING: geany not found", file=sys.stderr)
        return
    x = versions.geanyVersion()
    print("Geany Version: " + x, file=env.file_output)
    test("geany", mode, env)
    modify_dont_save_geany("geany", sleeptime, env.args.verbose, mode)
    print("", file=env.file_output)

def sublime_text_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("subl") == -1):
        print("WARNING: subl/sublime not found", file=sys.stderr)
        return
    x = versions.sublimeVersion()
    print("Sublime Text Version: " + x, file=env.file_output)
    test("subl", mode, env.args)
    modify_dont_save_sublime("subl", sleeptime, env.args.verbose, mode)
    print("", file=env.file_output)


def codeblocks_test(env, sleeptime, mode, target_code):
    x = versions.codeblocksVersion()
    if (x.find("not found") != -1):
        print("WARNING: codeblocks not found", file=sys.stderr)
        return
    print("Codeblocks Version: " + x, file=env.file_output)
    access("codeblocks", sleeptime * 2, env.args.verbose, mode)
    modify("codeblocks", sleeptime * 2, env.args.verbose, mode)
    save_no_modify("codeblocks", sleeptime * 2, env.args.verbose, mode)
    modify_dont_save_codeblocks("codeblocks", sleeptime * 2, env.args.verbose, mode)
    print("", file=env.file_output)

def bluefish_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("bluefish") == -1):
        print("WARNING: bluefish not found", file=sys.stderr)
        return
    x = versions.bluefishVersion()
    print("Bluefish Text Version: " + x, file=env.file_output)
    if (mode != 2):
        access("bluefish", sleeptime, env.args.verbose, mode)
        modify("bluefish", sleeptime, env.args.verbose, mode)
        save_no_modify("bluefish", sleeptime, env.args.verbose, mode)
        modify_dont_save_codeblocks("bluefish", sleeptime, env.args.verbose, mode)
    else:
        print("Not really working with this filesize", file=env.file_output)
    print("", file=env.file_output)


def texstudio_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("texstudio") == -1):
        print("WARNING: texstudio not found", file=sys.stderr)
        return
    x = versions.texstudioVersion()
    print("Texstudio Version: " + x, file=env.file_output)
    if (mode != 2):
        access("texstudio", sleeptime, env.args.verbose, mode)
        modify("texstudio", sleeptime, env.args.verbose, mode)
        save_no_modify("texstudio", sleeptime, env.args.verbose, mode)
        modify_dont_save_texstudio("texstudio", sleeptime, env.args.verbose, mode)
    else:
        print("Not really working with this filesize", file=env.file_output)
    print("", file=env.file_output)


def visualstudiocode_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("code") == -1):
        print("WARNING: visualstudiocode not found", file=sys.stderr)
        return
    x = versions.visualstudiocodeVersion()
    print("Visual Studio Code Version: " + x, file=env.file_output)
    access("code", sleeptime, env.args.verbose, mode)
    modify("code", sleeptime, env.args.verbose, mode)
    save_no_modify("code", sleeptime, env.args.verbose, mode)
    modify_dont_save_code("code", sleeptime, env.args.verbose, mode)
    print("", file=env.file_output)


def leafpad_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("leafpad") == -1):
        print("WARNING: leafpad not found", file=sys.stderr)
        return
    x = versions.leafpadversion()
    print("Leafpad Version: " + x, file=env.file_output)
    access("leafpad", sleeptime, env.args.verbose, mode)
    modify("leafpad", sleeptime, env.args.verbose, mode)
    save_no_modify("leafpad", sleeptime, env.args.verbose, mode)
    modify_dont_save_codeblocks("leafpad", sleeptime, env.args.verbose, mode)
    print("", file=env.file_output)


def notepadqq_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("notepadqq") == -1):
        print("WARNING: notepadqq not found", file=sys.stderr)
        return
    x = versions.notepadqqVersion()
    print("Notepadqq Version: " + x, file=env.file_output)
    if (not mode == 2):
        access_notepadqq("notepadqq", sleeptime, env.args.verbose, mode)
        modify_notepadqq("notepadqq", sleeptime, env.args.verbose, mode)
        save_no_modify_notepadqq("notepadqq", sleeptime, env.args.verbose, mode)
        modify_dont_save_notepadqq("notepadqq", sleeptime, env.args.verbose, mode)
    else:
        print("Not perfomant for big files", file=env.file_output)
    print("", file=env.file_output)


def jed_test(env, sleeptime, mode, target_code):
    if (utility.doesProgramExist("jed") == -1):
        print("WARNING: jed not found", file=sys.stderr)
        return
    x = versions.jedVersion()
    print("Jed Version: " + x, file=env.file_output)
    jed_Access(env, sleeptime, mode)
    jed_Modify(env, sleeptime, mode)
    jed_safe_no_mod(env, sleeptime, mode)
    jed_mod_no_save(env, sleeptime, mode)
    print("", file=env.file_output)


# runs all tests
def profile_gui(env, targets):
    # global sleeptime
    # sys.stdout = open('editors_profile.txt', 'w')

    start_time = datetime.now()
    utility.open_terminal()
    time.sleep(max(1, env.args.sleeptime))

    run_test(env, targets, env.args.sleeptime)

    utility.close_terminal()

    os.system("touch errors")
    os.system("rm errors")

    end_time = datetime.now()
    print('EXECUTION TIME: {}'.format(end_time - start_time), file=env.file_output)

    # sys.stdout.close()


def test(name, mode, env):
    access(name, env.args.sleeptime, env.args.verbose, mode)
    modify(name, env.args.sleeptime, env.args.verbose, mode)
    save_no_modify(name, env.args.sleeptime, env.args.verbose, mode)


# Executes all testcases of a given mode for all editors if the are set to be run
def run_test(env, targets, sleeptime):
    utility.dir_navigate(env.tmpdir_path)

    EDITOR_tests = dict()
    # EDITOR_tests["EDITOR.vim_clean"] = (vim_test, "vim_clean")
    # EDITOR_tests["EDITOR.vim_conf"] = (vim_conf_test, "vim_conf")
    # EDITOR_tests["EDITOR.vim_own_conf"] = (vim_own_test, "vim_own_conf")
    # EDITOR_tests["EDITOR.vim_choose_conf"] = (vim_choose_test, "vim_choose_conf")
    # EDITOR_tests["EDITOR.nano"] = (nano_test, "nano")
    # EDITOR_tests["EDITOR.gedit"] = (gedit_test, "gedit")
    # EDITOR_tests["EDITOR.kate"] = (kate_test, "kate")
    # EDITOR_tests["EDITOR.atom"] = (atom_test, "atom")
    # EDITOR_tests["EDITOR.emacs"] = (emacs_test, "emacs")
    # EDITOR_tests["EDITOR.geany"] = (geany_test, "geany")
    # EDITOR_tests["EDITOR.sublime"] = (sublime_text_test, "sublime_text")
    # EDITOR_tests["EDITOR.codeblocks"] = (codeblocks_test, "codeblocks")
    # EDITOR_tests["EDITOR.bluefish"] = (bluefish_test, "bluefish")
    # EDITOR_tests["EDITOR.texstudio"] = (texstudio_test, "texstudio")
    # EDITOR_tests["EDITOR.code"] = (visualstudiocode_test, "visualstudiocode")
    # EDITOR_tests["EDITOR.leafpad"] = (leafpad_test, "leafpad")
    # EDITOR_tests["EDITOR.notepadqq"] = (notepadqq_test, "notepadqq")
    # EDITOR_tests["EDITOR.jed"] = (jed_test, "jed")

    for t_name, t_code, t_func, t_desc in targets_info:
        EDITOR_tests[t_name] = (t_func, t_code)

    for test in EDITOR_tests:
        if targets[test]:
            tmp_dir = test
            if env.args.verbose: print("BEGIN test: ", test)
            utility.dir_navigate(tmp_dir, new=True)

            (target_fun, target_code) = EDITOR_tests[test]
            target_fun(env, sleeptime, target_code)

            utility.dir_navigate("..")
            if env.args.verbose: print("DONE test:  ", test)
    
    utility.dir_navigate("..")

# parses the run arguments of the program
# "-h" will give an overview of the available options
def parse():
    # What targets should be run?
    targets = dict()
    for t_name, t_code, t_func, t_desc in targets_info:
        targets[t_name] = False

    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action='store_true', default=False, help="prints timestamp before and after test as well as inode number")
    parser.add_argument("-d", "--debug", action='store_true', default=False, help="debug mode")
    parser.add_argument("-st", "--sleeptime", type=float, default=6., help="sleep timer (seconds)")
    parser.add_argument("-o", "--output", dest="path_output", default="profile_gui.txt", help="Path to output")
    parser.add_argument("-ro", "--output-results-csv-file", dest="path_csv_output", default="profile_gui_results.csv", help="Path to csv output results")
    parser.add_argument("-fo", "--output-flags-csv-file", dest="path_flags_csv_output", default="profile_gui_flags.csv", help="Path to csv output detailed results (flags)")
   
    parser.add_argument("--test", "-t", dest='test', action='append', help="Include the target (can be used multiple times), list to get a list")
    parser.add_argument("--operations", "-op", dest='operation', action='append', help="(Only for file managers) Include the operation (can be used multiple times), list to list possible operations")
    parser.add_argument("--vim-conf", "-vc", dest='vim_conf', default=None, help="Specific conf file to use for vim (.vimrc)")

    parser.add_argument("--empty", dest="empty", action='store_true', default=False, help="runs the tests with empty files (0 byte)")
    parser.add_argument("--small", dest="small", action='store_true', default=False, help="runs the tests with small files (1 KB)")
    parser.add_argument("--large", dest="large", action='store_true', default=False, help="runs the tests with large files (1 MB)")
    parser.add_argument("--big", dest="big", action='store_true', default=False, help="runs the tests with big files (1 GB)")
    parser.add_argument("--custom-size", dest="custom_size", type=int, default=None, help="runs the tests with custom-size files (size in bytes)")
    args = parser.parse_args()

    if args.test is not None:
        for t in args.test:
            if t == "list":
                print("Possible targets:")
                for t_name, t_code, t_func, t_desc in targets_info:
                    print("  " + t_name, "-", t_desc)
                sys.exit(1)

            if t in targets:
                targets[t] = True
            elif "EDITOR."+t in targets:
                targets["EDITOR."+t] = True
            elif "FILEMANAGER."+t in targets:
                targets["FILEMANAGER"+t] = True
            else:
                print("WARNING: test target " + t + " not found.", file=sys.stderr)
    else:
        for t in targets:
            targets[t] = True

    if (not args.empty) and (not args.small) and (not args.large) and (not args.big) and (args.custom_size is None) :
        args.empty = True
        args.small = True
        args.large = True

    sizes = []
    if args.empty:
        sizes.append(0)
    if args.small:
        sizes.append(1024)
    if args.large:
        sizes.append(1024**2)
    if args.big:
        sizes.append(1024**3)
    if args.custom_size is not None:
        sizes.append(args.custom_size)

    possible_operations = ["EDITOR.access", "EDITOR.modify", "EDITOR.save_no_modify", "EDITOR.modify_no_save"]
    #possible_operations = []

    operations = []
    if args.operation is not None:
        for op in args.operation:
            if op.strip() == "list":
                print("Possible operations:")
                for o in possible_operations:
                    print("  " + o)
                sys.exit(1)
            elif op.strip() in possible_operations:
                operations.append(op.strip())
            else:
                print("WARNING: unknown operation: " + op, file=sys.stderr)
    else:
        operations = possible_operations

    if len([t for t in targets if targets[t]]) == 0:
        print("ERROR: No target selected.")
        sys.exit(1)    

    if len(operations) == 0:
        print("ERROR: No operation selected.")
        sys.exit(1)



    return args, targets, operations, sizes

def find_tmp_dir():
    basename = "tmp_gui_profile_"
    for i in range(1, 100):
        path = basename + str(i).zfill(2)
        if os.path.exists(path):
            continue
        
        os.mkdir(path)
        return path
    return None



targets_info = []
targets_info.append(("EDITOR.vim_clean", "vim_clean", vim_test, "vim with empty config (--clean option)"))
targets_info.append(("EDITOR.vim_conf", "vim_conf", vim_conf_test, "vim with a config limited to: set nowritebackup"))
targets_info.append(("EDITOR.vim_own_conf", "vim_own_conf", vim_own_test, "vim with existing config"))
targets_info.append(("EDITOR.vim_choose_conf", "vim_choose_conf", vim_choose_test, "vim with a user-chosen conf (--vim-conf PATH)"))
targets_info.append(("EDITOR.nano", "nano", nano_test, ""))
targets_info.append(("EDITOR.gedit", "gedit", gedit_test, ""))
targets_info.append(("EDITOR.kate", "kate", kate_test, ""))
targets_info.append(("EDITOR.emacs", "emacs", emacs_test, ""))
targets_info.append(("EDITOR.atom", "atom", atom_test, ""))
targets_info.append(("EDITOR.geany", "geany", geany_test, ""))
targets_info.append(("EDITOR.sublime", "sublime_text", sublime_text_test, ""))
targets_info.append(("EDITOR.codeblocks", "codeblocks", codeblocks_test, ""))
targets_info.append(("EDITOR.bluefish", "bluefish", bluefish_test, ""))
targets_info.append(("EDITOR.texstudio", "texstudio", texstudio_test, ""))
targets_info.append(("EDITOR.code", "visualstudiocode", visualstudiocode_test, ""))
targets_info.append(("EDITOR.leafpad", "leafpad", leafpad_test, ""))
targets_info.append(("EDITOR.notepadqq", "notepadqq", notepadqq_test, ""))
targets_info.append(("EDITOR.jed", "jed", jed_test, ""))

def main():
    # Create test directory
    tmpdir_path = find_tmp_dir()
    if tmpdir_path is None:
        print("ERROR: could not create temporary directory - delete some of them?", file=sys.stderr)
        sys.exit(1)
    
    print("Output dir:", tmpdir_path)

    # find path to ./prototype_file_ts
    filets_path = os.getcwd() + os.sep + "prototype_file_ts"
    currenttime_path = os.getcwd() + os.sep + "prototype_current_time"

    # executes the parsing function
    args, targets, operations, sizes = parse()
    env = utility.env(args, operations, sizes, tmpdir_path, filets_path, currenttime_path, 
                      open(tmpdir_path + os.sep + args.path_output, "w"),
                      open(tmpdir_path + os.sep + args.path_csv_output, "w"), 
                      open(tmpdir_path + os.sep + args.path_flags_csv_output, "w"))

    print("Run Info:", file=env.file_output)
    print("  Output dir:", tmpdir_path, file=env.file_output)
    print("  Targets:", [t for t in targets if targets[t]], file=env.file_output)
    print("  Operations:", operations, file=env.file_output)
    print("  Sizes:", sizes, file=env.file_output)
    print("  args:", args, file=env.file_output)

    if args.verbose:
        print("Targets:", targets)
        print("Operations:", operations)
        print("Sizes:", sizes)

    # executes the editor tests
    profile_gui(env, targets)
    env.file_output.close()

main()