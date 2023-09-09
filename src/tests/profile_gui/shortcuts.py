# This file holds functions for often used keyboard shortcuts

import os
import subprocess
from dataclasses import dataclass
import pyautogui
import time
import argparse


def save():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('s')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('s')


def dont_save():
    pyautogui.press('left')
    pyautogui.press('left')
    pyautogui.press('enter')


def right_enter():
    pyautogui.press('right')
    pyautogui.press('right')
    pyautogui.press('enter')


def one_right_enter():
    pyautogui.press('right')
    pyautogui.press('enter')


def left_enter():
    pyautogui.press('left')
    pyautogui.press('enter')


def left_left_enter():
    pyautogui.press('left')
    pyautogui.press('left')
    pyautogui.press('enter')


# Shortcut for closing a program
def close():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('q')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('q')


def subl_close_file():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('w')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('w')


# Shortcut for closing vim
def vim_close():
    write(":")
    write("q")
    pyautogui.press('enter')


# Write a text with pyautogui.typewrite
def write(text):
    pyautogui.typewrite(text)


# Shortcut for closing emacs
def emacs_close():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('x')
    pyautogui.keyDown('c')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('x')
    pyautogui.keyUp('c')


# Shortcut for saving a file in emacs
def emacs_save():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('x')
    pyautogui.keyDown('s')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('x')
    pyautogui.keyUp('s')


def kate_close_file():
    pyautogui.press('tab')
    pyautogui.press('tab')
    pyautogui.press('tab')
    pyautogui.press('enter')


def code_close_file():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('w')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('w')


def notepadqq_close():
    pyautogui.keyDown('alt')
    pyautogui.keyDown('f4')
    pyautogui.keyUp('alt')
    pyautogui.keyUp('f4')


def jed_close():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('x')
    pyautogui.keyDown('c')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('x')
    pyautogui.keyUp('c')


def jed_save_and_close():
    jed_close()
    pyautogui.press('y')


def jed_pseudosave_and_close():
    pyautogui.keyDown('ctrl')
    pyautogui.keyDown('x')
    pyautogui.keyDown('s')
    pyautogui.keyUp('ctrl')
    pyautogui.keyUp('x')
    pyautogui.keyUp('s')
    jed_close()
