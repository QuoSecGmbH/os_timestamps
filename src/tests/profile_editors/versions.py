# This file is responsible for extracting the version number of a given editor

import os
import subprocess
from dataclasses import dataclass
import pyautogui
import time
from utility import *
import argparse


# Extracts the Version of Vim
def vimVersion():
    output = str(subprocess.check_output(['vim', '--version']))
    beginOutput = output.find("IMproved ")
    output = output[beginOutput + 9::]
    endOutput = output.find(" ")
    output = output[:endOutput:]
    return output


# Extracts the Version of Nano, gives -1 if not installed
def nanoVersion():
    output = str(subprocess.check_output(['nano', '--version']))
    beginOutput = output.find("version")
    output = output[beginOutput + 8::]
    endOutput = output.find(" ")
    output = output[:endOutput - 2:]
    return output


# Extracts the Version of Gedit, gives -1 if not installed
def geditVersion():
    output = str(subprocess.check_output(['gedit', '--version']))
    beginOutput = output.find("Version")
    output = output[beginOutput + 8::]
    endOutput = output.find("\n")
    output = output[:endOutput - 2:]
    return output


# Extracts the Version of Kate, gives -1 if not installed
def kateVersion():
    output = str(subprocess.check_output(['kate', '--version']))
    beginOutput = output.find("kate")
    output = output[beginOutput + 5::]
    endOutput = output.find("\n")
    output = output[:endOutput - 2:]
    return output


# Extracts the Version of Atom, gives -1 if not installed
def atomVersion():
    output = str(subprocess.check_output(['atom', '--version']))
    beginOutput = output.find("Atom")
    output = output[beginOutput + 10::]
    endOutput = output.find("Electron")
    output = output[:endOutput - 2:]
    return output


# Extracts the Version of Emacs, gives -1 if not installed
def emacsVersion():
    output = str(subprocess.check_output(['emacs', '--version']))
    beginOutput = output.find("Emacs")
    output = output[beginOutput + 6::]
    endOutput = output.find("Copy")
    output = output[:endOutput - 2:]
    return output


# Extracts the Version of Geany, gives -1 if not installed
def geanyVersion():
    output = str(subprocess.check_output(['geany', '--version']))
    beginOutput = output.find("geany")
    output = output[beginOutput + 6::]
    endOutput = output.find(" ")
    output = output[:endOutput:]
    return output


def sublimeVersion():
    output = str(subprocess.check_output(['subl', '--version']))
    beginOutput = output.find("Text")
    output = output[beginOutput + 11::]
    endOutput = output.find("\n")
    output = output[:endOutput - 2:]
    return output


def codeblocksVersion():
    pyautogui.write("codeblocks -h > version")
    pyautogui.press('enter')
    time.sleep(0.5)
    pyautogui.press('enter')
    time.sleep(0.5)
    with open('version', 'r') as file:
        output = file.read()
    beginOutput = output.find("Release")
    output = output[beginOutput + 8::]
    endOutput = output.find("  ")
    output = output[:endOutput:]
    os.system("rm version")
    return output


def bluefishVersion():
    output = str(subprocess.check_output(['bluefish', '--version']))
    beginOutput = output.find("Editor")
    output = output[beginOutput + 7::]
    endOutput = output.find("Visit")
    output = output[:endOutput - 2:]
    return output


def texstudioVersion():
    output = str(subprocess.check_output(['texstudio', '--version']))
    beginOutput = output.find("studio")
    output = output[beginOutput + 7::]
    endOutput = output.find(" ")
    output = output[:endOutput:]
    return output


# def netbeansVersion():
#    output = str(subprocess.check_output(['netbeans', '-h']))
#    beginOutput = output.find("netbeans")
#    output = output[beginOutput + 9::]
#    endOutput = output.find("/")
#    output = output[:endOutput:]
#    return output

def visualstudiocodeVersion():
    output = str(subprocess.check_output(['code', '--version']))
    output = output[2::]
    output = output[:6:]
    return output


def leafpadversion():
    pyautogui.write("leafpad --version &> version")
    pyautogui.press('enter')
    time.sleep(0.5)
    pyautogui.press('enter')
    time.sleep(0.5)
    with open('version', 'r') as file:
        output = file.read()
    beginOutput = output.find("Leafpad")
    output = output[beginOutput + 8::]
    endOutput = output.find("\n")
    output = output[:endOutput:]
    os.system("rm version")
    return output


def notepadqqVersion():
    pyautogui.write("notepadqq --version &> version")
    pyautogui.press('enter')
    time.sleep(0.5)
    pyautogui.press('enter')
    time.sleep(0.5)
    with open('version', 'r') as file:
        output = file.read()
    beginOutput = output.find("Notepadqq")
    output = output[beginOutput + 10::]
    endOutput = output.find("\n")
    output = output[:endOutput:]
    os.system("rm version")
    return output


def jedVersion():
    output = str(subprocess.check_output(['jed', '--version']))
    beginOutput = output.find("version")
    output = output[beginOutput + 9::]
    endOutput = output.find("/")
    output = output[:endOutput:]
    return output
