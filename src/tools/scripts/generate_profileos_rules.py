#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import argparse

latex_preamble = r"""
% \documentclass[a4paper,10pt]{article}
\documentclass{article}
\usepackage[pdftex,active,tightpage]{preview}
\setlength\PreviewBorder{2mm} % use to add a border around the image
% \usepackage{standalone}
\usepackage[T1]{fontenc}
\usepackage{lmodern}

\usepackage[english]{babel}
% \usepackage{fullpage}

% \usepackage{scrextend}

% \usepackage[algoruled,french,onelanguage]{algorithm2e}
% \usepackage{amsfonts}
% \usepackage{amsmath}
% \usepackage{placeins}
% \usepackage{verbatim}
% \usepackage{graphicx}
% \usepackage{listings}
% \usepackage{textcomp}
\usepackage{tikz}
\usetikzlibrary{shapes,arrows,positioning,fit}
\usetikzlibrary{shapes.multipart,calc}
\usetikzlibrary{arrows}


%\usepackage{fontspec}
%\setmonofont{Libertinus Mono}[
%  Scale=MatchLowercase
%] % or whatever font you prefer

%\setmonofont{Everson Mono}

\usepackage{inconsolata}

% tikz
\tikzset{
  state/.style={
    rectangle,
    rounded corners=1pt,
    draw=black, very thick,
    minimum height=2em
    text centered,
    align=center,
  },
}

% tikz
\tikzset{
  snb/.style={
    rectangle,
    align=left,
%    draw=black
  },
}

\begin{document}
% \documentclass{standalone}
\begin{preview}
\begin{tikzpicture}[->,scale=1,>=stealth',thick,every text node part/.style={align=left}, node distance=0cm]
"""

latex_end = r"""
\end{tikzpicture}%}
\end{preview}
% \end{document}
\end{document}
"""

def group_corres(group, args, group_desc):
    if group in group_desc:
        return group_desc[group]

    if args.group:
        return group

    print(group)
    print(group_desc)

    dl = dict()
    dl["PROFILE.OS.FILE.RENAME"] = "File Rename"
    dl["PROFILE.OS.DIR.RENAME"] = "Dir Rename"
    dl["PROFILE.OS.FILE.MV_LOCAL"] = "Local File Move"
    dl["PROFILE.OS.DIR.MV_LOCAL"] = "Local Dir Move"
    dl["PROFILE.OS.FILE.MV_VOLUME"] = "Volume File Move"
    dl["PROFILE.OS.DIR.MV_VOLUME"] = "Volume Dir Move"
    dl["PROFILE.OS.FILE.COPY.NEW"] = "File Copy (new)"
    dl["PROFILE.OS.FILE.COPY.EXISTING"] = "File Copy (existing)"
    dl["PROFILE.OS.DIR.COPY.NEW.NOTEMPTY"] = "Dir Copy (notempty)"
    dl["PROFILE.OS.DIR.COPY.NEW.EMPTY"] = "Dir Copy (empty)"
    dl["PROFILE.OS.FILE.NEW"] = "New File"
    dl["PROFILE.OS.DIR.NEW"] = "New Dir"
    dl["PROFILE.OS.FILE.READ"] = "File Read"
    dl["PROFILE.OS.FILE.WRITE"] = "File Write"
    dl["PROFILE.OS.FILE.RM.last"] = "File Delete (last)"
    dl["PROFILE.OS.FILE.RM.notlast"] = "File Delete (notlast)"
    dl["PROFILE.OS.DIR.RM.last"] = "Dir Delete (last)"
    dl["PROFILE.OS.DIR.LISTING.notempty"] = "Dir Listing (notempty)"
    dl["PROFILE.OS.DIR.LISTING.empty"] = "Dir Listing (empty)"
    dl["PROFILE.OS.DIR.TRAVERSAL"] = "Dir Traversal"
    dl["PROFILE.OS.EXEC"] = "Binary Execution"

    dl["PROFILE.OS.HARDLINK.FILE.NEW"] = "New Hardlink\\\\(to file)"
    dl["PROFILE.OS.FILE.NEW.INTOSYMLINKDIR"] =  "File Creation\\\\ into Symlink Dir"
    dl["PROFILE.OS.SYMLINK.FILE.READ"] = "Symlink (to file)\\\\ Access"
    dl["PROFILE.OS.SYMLINK.READLINK"] = "Symlink readlink"
    dl["PROFILE.OS.SYMLINK.FILE.WRITE"] = "Symlink (to file)\\\\ Modify"
    dl["PROFILE.OS.FILE.CHANGE"] = "File Change"
    dl["PROFILE.OS.SYMLINK.FILE.CHANGE"] = "Symlink (to file)\\\\ Change"
    dl["PROFILE.OS.DIR.CHANGE"] = "Dir Change"
    dl["PROFILE.OS.SYMLINK.FILE.RM.last"] = "Symlink (to file)\\\\ Delete"
    dl["PROFILE.OS.SYMLINK.DIR.RM.last"] = "Symlink (to dir)\\\\ Delete"
    dl["PROFILE.OS.SYMLINK.DIR.LISTING.notempty"] = "Symlink (to dir)\\\\ Listing"
    dl["PROFILE.OS.SYMLINK.DIR.TRAVERSAL"] = "Symlink (to dir)\\\\ Traversal"
    dl["PROFILE.OS.SYMLINK.EXEC"] = "Symlink (to binary)\\\\ Execution"
    dl["PROFILE.OS.EXEC.INTOSYMLINKDIR"] = "Binary Execution\\\\ into Symlink Dir"
    dl["PROFILE.OS.VIRTUAL.SYMLINK.FILE.OP"] = "Action on symlink\\\\target (read, listing...)"
    dl["PROFILE.OS.SYMLINK.FILE.CHANGE.NOFOLLOW"] = "Symlink Link Change"

    d = dict()
    d["PROFILE.OS.FILE.RENAME"] = "File Rename"
    d["PROFILE.OS.DIR.RENAME"] = "Dir Rename"
    d["PROFILE.OS.FILE.MV_LOCAL"] = "Local File Move"
    d["PROFILE.OS.DIR.MV_LOCAL"] = "Local Dir Move"
    d["PROFILE.OS.FILE.MV_VOLUME"] = "Volume File Move"
    d["PROFILE.OS.DIR.MV_VOLUME"] = "Volume Dir Move"
    d["PROFILE.OS.FILE.COPY.NEW"] = "File Copy (new)"
    d["PROFILE.OS.FILE.COPY.EXISTING"] = "File Copy (existing)"
    d["PROFILE.OS.DIR.COPY.NEW.NOTEMPTY"] = "Dir Copy (notempty)"
    d["PROFILE.OS.DIR.COPY.NEW.EMPTY"] = "Dir Copy (empty)"
    d["PROFILE.OS.FILE.NEW"] = "New File"
    d["PROFILE.OS.DIR.NEW"] = "New Dir"
    d["PROFILE.OS.FILE.READ"] = "File Access"
    d["PROFILE.OS.FILE.WRITE"] = "File Modification"
    d["PROFILE.OS.FILE.RM.last"] = "File Delete (last)"
    d["PROFILE.OS.FILE.RM.notlast"] = "File Delete (notlast)"
    d["PROFILE.OS.DIR.RM.last"] = "Dir Delete (last)"
    d["PROFILE.OS.DIR.LISTING.notempty"] = "Dir Listing (notempty)"
    d["PROFILE.OS.DIR.LISTING.empty"] = "Dir Listing (empty)"
    d["PROFILE.OS.DIR.TRAVERSAL"] = "Dir Traversal"
    d["PROFILE.OS.EXEC"] = "Binary Execution"

    d["PROFILE.OS.HARDLINK.FILE.NEW"] = "New Hardlink\\\\(to file)"
    d["PROFILE.OS.FILE.NEW.INTOSYMLINKDIR"] =  "File Creation\\\\ into Symlink Dir"
    d["PROFILE.OS.SYMLINK.FILE.READ"] = "Symlink (to file)\\\\ Access"
    d["PROFILE.OS.SYMLINK.READLINK"] = "Symlink readlink"
    d["PROFILE.OS.SYMLINK.FILE.WRITE"] = "Symlink (to file)\\\\ Modify"
    d["PROFILE.OS.FILE.CHANGE"] = "File Change"
    d["PROFILE.OS.SYMLINK.FILE.CHANGE"] = "Symlink (to file)\\\\ Change"
    d["PROFILE.OS.DIR.CHANGE"] = "Dir Change"
    d["PROFILE.OS.SYMLINK.FILE.RM.last"] = "Symlink (to file)\\\\ Delete"
    d["PROFILE.OS.SYMLINK.DIR.RM.last"] = "Symlink (to dir)\\\\ Delete"
    d["PROFILE.OS.SYMLINK.DIR.LISTING.notempty"] = "Symlink (to dir)\\\\ Listing"
    d["PROFILE.OS.SYMLINK.DIR.TRAVERSAL"] = "Symlink (to dir)\\\\ Traversal"
    d["PROFILE.OS.SYMLINK.EXEC"] = "Symlink (to binary)\\\\ Execution"
    d["PROFILE.OS.EXEC.INTOSYMLINKDIR"] = "Binary Execution\\\\ into Symlink Dir"
    d["PROFILE.OS.VIRTUAL.SYMLINK.FILE.OP"] = "Action on symlink\\\\target (read, listing...)"

    if group in dl:
        return dl[group]
    return group

def tex_end_group(group, group_list):
    if len(group_list) == 0:
        return ""

    if group == "":
        v_style="snb"
    else:
        v_style="state"

    group_ = group.replace(".", "_")

    tex = "\\node[snb, below = 0.8cm of {}_TITLE.north west, anchor= north west, minimum height=2.3cm]({}_TEXTBOUNDS){{}};\n".format(group_, group_)

    #tex = "\\node[snb, below = 0.8cm of {}_TITLE.north west, anchor= north west, minimum height=2cm]".format(group_)
    
    i = 0
    for element, mac in group_list:
        el = element.replace("/", "")
        cm = 0.3+0.5*i
        tex += "\\node[snb, below right="+str(cm)+"cm and 0.48cm of {}_TEXTBOUNDS.north west, anchor= north west, minimum height=0.5cm]".format(group_)
        #tex += "\\node[snb, below ="+str(cm)+"cm of {}_TEXTBOUNDS.north west, anchor= north west, minimum height=0.5cm]".format(group_)
        tex += "({}_FILES_{}){{".format(group_, el)
        if element != "":
            tex += element.replace("_", "\\_") + ":"
        tex += "\\vphantom{{{}}}".format(mac)
        tex += "};\n"
        i += 1


    #tex += "\\node[snb, right = of {}_FILES.north east, anchor=north west, minimum height=2cm]".format(group_)
    #tex += "\\node[snb, below = 0.1 of {}_TITLE.south west, anchor=north west, minimum height=2cm]".format(group_)

    i = 0
    for element, mac in group_list:
        el = element.replace("/", "")
        tex += "\\node[snb, right = 1.9cm of {}_FILES_{}.north west, anchor=north west, minimum height=0.5cm]".format(group_, el)
        tex += "({}_MAC_{}){{".format(group_, el)
        tex += "\\texttt{" + mac + "}"
        #tex += element
        tex += "\\vphantom{{{}:}}".format(element.replace("_", "\\_"))
        tex += "};\n"
#        if "/" in element:
        i += 1

    tex += "\\node[{}, fit={{({}_TITLE) ({}_TEXTBOUNDS)}}] ({}_FIT) {{}};\n".format(v_style, group_, group_, group_)

    return tex


def tex_new_group(c1, c2, group, last_real_group, below, below_group, args, group_desc):
    group_ = group.replace(".", "_")
    group_name = group_corres(group, args, group_desc).replace("_", "\\_")

    if group == "":
        v_style = "snb"
    else:
        v_style = "state"
    
    if last_real_group is None:
        return "\\node[{}, minimum width=3.6cm, align=center] ({}_TITLE) {{{}}};\n".format(v_style, group_, group_name)
    else:
        last_real_group_ = last_real_group.replace(".", "_")
        if below:
            below_group_ = below_group.replace(".", "_")
            return "\\node[{}, minimum width=3.6cm, align=center, below = 3cm of {}_TITLE.south west, anchor=north west] ({}_TITLE) {{{}}};\n".format(v_style, below_group_, group_, group_name)
        else:
            return "\\node[{}, minimum width=3.6cm, align=center, right = 4.5cm of {}_TITLE.north east, anchor=north east] ({}_TITLE) {{{}}};\n".format(v_style, last_real_group_, group_, group_name)

def get_group_element(c1):
    splitted = c1.split(".")
    group = ".".join(splitted[0:-1])
    element = splitted[-1]
    return group, element

def main():
    parser = argparse.ArgumentParser(description='generate .tex (compile with pdflatex', formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument(dest="csv_path", help="csv_path")
    parser.add_argument("-md", "--make-dots", dest="make_dots", action="store_true", default=False, help="Converts all occurrences of inherit flag (>) into no change flag (.). Make sure you know what you're doing!!!")
    parser.add_argument("-g", "--group", dest="group", action="store_true", default=False, help="Show group names instead of description")
    parser.add_argument("-p", "--partial-tex", dest="partial_tex", action="store_true", default=False, help="Outputs only body of tikz file")
    parser.add_argument("-o", "--output", dest="output_tex", action="store", default="out.tex", help="Path to save TEX file to")
    parser.add_argument("-s", "--skip", dest="skip_list", nargs="+", default=[], help="Skip group")
    parser.add_argument("-gd", "--group-description", dest="group_description", nargs="+", default=[], help="Rename group with custom description")
    parser.add_argument("-rs", "--row_size", dest="row_size", action="store", default=3, help="Number of items per row")
    args = parser.parse_args()

    print(args.group_description)
    group_desc = dict()
    for s in args.group_description:
        splitted = s.split("=")
        if len(splitted) != 2:
            continue
        group_desc[splitted[0]] = splitted[1]

    path = args.csv_path
    text = open(path, "r").read()
    lines = text.split("\n")

    tex = ""
    if not args.partial_tex:
        tex += latex_preamble
    last_group = None
    last_real_group = None
    below_group = None
    group_list = []

    ncol = 0
    for l in lines[1:]:
        splitted = l.replace("\"", "").split(", ")
        if len(splitted) <= 1:
            break
        c1 = splitted[0]
        if c1 in args.skip_list:
            continue

        if c1 in group_desc:
            c1 = group_desc[c1]

        mac = splitted[1]
        if args.make_dots:
            mac = mac.replace(">", ".")

        group, element = get_group_element(c1)
        if group in args.skip_list:
            continue

        if last_group == None or group != last_group:
            print("new:", group)
            print("element:", element)
            print("mac:", mac)
            print("group:", group)
            if last_group != None:
                tex += tex_end_group(last_group, group_list)
                last_real_group = last_group
                tex += "\n\n"
            print("ncol:", ncol)
            if ncol < int(args.row_size):
                below = False
            else:
                below = True
                ncol = 0
            print("bg:", below_group)
            tex += tex_new_group(c1, mac, group, last_real_group, below, below_group, args, group_desc)
            if ncol == 0:
                below_group = group
            group_list = []
            group_list.append((element, mac))
            ncol += 1
        else:
            print("existing:", group)
            group_list.append((element, mac))

        last_group = group


    if last_group != None:
        tex += tex_end_group(last_group, group_list)

    if not args.partial_tex:
        tex += latex_end
    open(args.output_tex, "w").write(tex)

main()
