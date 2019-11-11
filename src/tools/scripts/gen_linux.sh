#!/bin/bash

python3 generate_profileos_rules.py -rs 4 linux_os_profile_results_v2_modified.csv -o linux_mac_results_partial.tex -p -gd \
       	"PROFILE.OS.FILE.RENAME=File/Dir Rename" \
       	"PROFILE.OS.FILE.MV_LOCAL=File/Dir Move\\\\(Local/Volume)" \
	"PROFILE.OS.FILE.COPY.NEW=File/Dir Copy (new)" \
	"PROFILE.OS.FILE.COPY.EXISTING=File Copy (existing)" \
	"PROFILE.OS.FILE.NEW=New File/Dir" \
	"PROFILE.OS.FILE.CHANGE=File/Dir Change" \
	"PROFILE.OS.FILE.CHANGE.file=PROFILE.OS.FILE.CHANGE.target" \
	"PROFILE.OS.FILE.RM.last=File/Dir Delete (last)" \
	"PROFILE.OS.DIR.LISTING.empty=Dir Listing" \
	"PROFILE.OS.FILE.READ=File Access/Execution" \
	"PROFILE.OS.FILE.RENAME.dir/=PROFILE.OS.FILE.RENAME.parentdir/" \
	"PROFILE.OS.FILE.RM.last.dir/=PROFILE.OS.FILE.RM.last.parentdir/" \
	"PROFILE.OS.FILE.RM.notlast.dir/=PROFILE.OS.FILE.RM.notlast.parentdir/" \
	"PROFILE.OS.FILE.NEW.dir/=PROFILE.OS.FILE.NEW.parentdir/" \
	"PROFILE.OS.FILE.NEW.newfile=PROFILE.OS.FILE.NEW.new" \
	"PROFILE.OS.FILE.READ.dir/=PROFILE.OS.FILE.READ.parentdir/" \
	"PROFILE.OS.FILE.WRITE.dir/=PROFILE.OS.FILE.WRITE.parentdir/" \
	"PROFILE.OS.DIR.LISTING.notempty.file=PROFILE.OS.DIR.LISTING.notempty.dir/file" \
	"PROFILE.OS.DIR.LISTING.notempty=Dir Listing" \
	"PROFILE.OS.SYMLINK.FILE.NEW=New Symlink" \
	"PROFILE.OS.SYMLINK.FILE.NEW.file=PROFILE.OS.SYMLINK.FILE.NEW.target" \
	"PROFILE.OS.SYMLINK.FILE.NEW.newsymlink=PROFILE.OS.SYMLINK.FILE.NEW.symlink" \
	"PROFILE.OS.SYMLINK.FILE.RM.last=Symlink Link Delete" \
	"PROFILE.OS.SYMLINK.FILE.RM.last.file=PROFILE.OS.SYMLINK.FILE.RM.last.target" \
	"PROFILE.OS.SYMLINK.READLINK=Symlink\\\\Follow/Dereference" \
       	-s \
	PROFILE.OS.DIR.RENAME \
	PROFILE.OS.DIR.MV_LOCAL \
	PROFILE.OS.FILE.MV_VOLUME \
	PROFILE.OS.DIR.MV_VOLUME \
	PROFILE.OS.DIR.COPY.NEW.NOTEMPTY \
	PROFILE.OS.DIR.COPY.NEW.EMPTY \
	PROFILE.OS.DIR.NEW \
	PROFILE.OS.DIR.RM.last \
	PROFILE.OS.DIR.LISTING.empty \
	PROFILE.OS.EXEC \
	PROFILE.OS.FILE.RENAME.src \
	PROFILE.OS.FILE.MV_LOCAL.src \
	PROFILE.OS.FILE.RM.last.file \
	PROFILE.OS.SYMLINK.DIR.NEW \
	PROFILE.OS.HARDLINK.FILE.NEW.hardlink \
	PROFILE.OS.DIR.CHANGE \
	PROFILE.OS.SYMLINK.FILE.CHANGE \
	PROFILE.OS.SYMLINK.FILE.WRITE \
	PROFILE.OS.SYMLINK.FILE.READ \
	PROFILE.OS.SYMLINK.DIR.RM.last \
	PROFILE.OS.EXEC.INTOSYMLINKDIR \
	PROFILE.OS.FILE.NEW.INTOSYMLINKDIR \
	PROFILE.OS.SYMLINK.EXEC \
	PROFILE.OS.SYMLINK.DIR.TRAVERSAL \
	PROFILE.OS.SYMLINK.DIR.LISTING.notempty \
