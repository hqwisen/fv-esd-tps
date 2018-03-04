global StrlBox

bind Listbox <ButtonRelease-1> {
    tkCancelRepeat
}

bind Listbox <KeyPress> {
    for {set index 0} "\$index<[%W size]" {incr index} {
	if {[regexp {^ ?%A} [%W get $index]]} {
	    %W selection clear 0 end
	    %W selection set $index
	    %W see $index
	    %W activate $index
	    break
	}
    }
}

#===========================================================================
#SB_DirFileBrowser
#
#Builds a directory and file browser.
#
#Arguments:
#    w : name of the browser. It will be a frame.
#    useFileProc: a procedure called on selection (<Double-Button-1>
#                 or <Return> 
#                 First argument is current browser.
#    isFileSelected: this function takes a directory and a file name
#                 without its directory part. If this file is to be 
#                 selected by the application, then isFileSelected returns
#                 true and the file in the listbox will be prefixed by '+'
#    extensions: optional
#                list of patterns to use for filtering.
#                Elements are: {<text> {extension list}}
#                as {{"C code" {*.c *.h}} {Objects {*.o}}}
#                May also be a global variable. It will be evaluated before
#                menu posting for updates.
# Set:
#   StrlBox($w:dirs:current) as current directory
proc SB_DirFileBrowser {w useFileProc isFileSelected {extensions ""} {initialDir ""}} {
    global StrlBox tcl_platform
    
    set StrlBox($w:isSelectedProc) $isFileSelected
    set frame [frame $w]
    set dirbar [frame $frame.bar]
    
    # drive
    #------
    if { $tcl_platform(platform) == "windows" } {
	set menubutton [menubutton $dirbar.drive \
			    -relief raised ]
	set StrlBox($w:drive:button) $menubutton
	set StrlBox($w:drive:menu) \
	    [menu $menubutton.menu -postcommand "SB_FillDriveMenu $w"]
	$menubutton configure -menu $menubutton.menu
	pack $menubutton -side left
	$StrlBox($w:drive:button) configure -text \
	    [lindex [split [pwd] /] 0]
					 
    }
    # path 
    #-----
    set dirframe [frame $dirbar.dir -bd 2 -relief sunken]
    set menubutton [menubutton $dirframe.button \
	    -image $StrlBox(image:down) -relief raised]
    set entry [label $dirframe.value \
	    -textvariable StrlBox($w:dirs:basename) \
	    -width 15]
    pack $menubutton -side right -fill y
    pack $entry -side left
    set StrlBox($w:dirs:basename) ""
    set StrlBox($w:dirs:menu) $menubutton.optionList
    $menubutton configure \
	    -menu $StrlBox($w:dirs:menu)
    menu $StrlBox($w:dirs:menu)

    cb_balloonHelp $menubutton "Path to current directory"


    # up button
    #----------
    button $dirbar.up -image $StrlBox(image:updir) \
	    -bd 2 \
	    -highlightthickness 0 \
	    -command "SB_Browse $w \[file dirname \$StrlBox($w:dirs:current)\]"

    cb_balloonHelp $dirbar.up "Move up dir."

    # scan button
    #-------------
    button $dirbar.scan -image $StrlBox(image:rescan) \
	    -bd 2 \
	    -highlightthickness 0 \
	    -command "SB_Rescan $w"

    cb_balloonHelp $dirbar.scan "Rescan dir."

    # history
    set menubutton [menubutton $dirbar.hist -relief raised]
    cb_balloonHelp $dirbar.hist "Path history."

    set StrlBox($w:dirs:history) $menubutton.optionList
    $menubutton configure \
	    -image $StrlBox(image:history) \
	    -menu $StrlBox($w:dirs:history) 
    menu $StrlBox($w:dirs:history) -tearoff 0 \
	    -background white \
	    -activeforeground white \
	    -activebackground RoyalBlue \
	    -activeborderwidth 0

    pack $dirbar.dir $dirbar.up $dirbar.scan $dirbar.hist \
	    -side left -fill y
    pack $dirbar.dir -expand 1 -padx 2
    pack $dirbar.hist -fill y
    # Lists
    #------
    foreach list {dir file} {
	frame $frame.$list
	grid rowconfigure $frame.$list 0 -weight 1
	grid columnconfigure $frame.$list 0 -weight 1
	listbox $frame.$list.list -width 15 -highlightthickness 0
	scrollbar $frame.$list.vscroll \
		-orient vertical \
		-command "$frame.$list.list yview"
	scrollbar $frame.$list.hscroll \
		-orient horizontal \
		-command "$frame.$list.list xview"
	$frame.$list.list configure \
	    -yscrollcommand "$frame.$list.vscroll set" \
	    -xscrollcommand "$frame.$list.hscroll set" 
	grid $frame.$list.list -row 0 -column 0 -sticky nswe
	grid $frame.$list.vscroll -row 0 -column 1 -sticky ns
	grid $frame.$list.hscroll -row 1 -column 0 -sticky we
	
	bind $frame.$list.list <Any-Enter> {
	    set StrlBox(focus) [focus]
	    focus %W
	    break
	}
	bind $frame.$list.list <Any-Leave> {
	    focus $StrlBox(focus)
	    break
	}
    }
    set StrlBox($w:dirs:dir:list) $frame.dir.list
    set StrlBox($w:dirs:file:list) $frame.file.list

    $StrlBox($w:dirs:dir:list) configure \
	    -selectmode browse \
	    -exportselection 0
    $StrlBox($w:dirs:file:list) configure \
	    -selectmode extended \
	    -exportselection 0
    set prog  {
	if {[catch  {$StrlBox(%1$s:dirs:dir:list) get \
		[$StrlBox(%1$s:dirs:dir:list) curselection]} dir]} {
	    break
	}
	SB_Browse %1$s [file join $StrlBox(%1$s:dirs:current) $dir] 
    }
    bind $StrlBox($w:dirs:dir:list) <Double-Button-1> \
	    [format $prog $w]

    bind $StrlBox($w:dirs:dir:list) <Return> \
	    [bind $StrlBox($w:dirs:dir:list) <Double-Button-1>]

    set prog {
	set listbox $StrlBox(%2$s:dirs:file:list)
	%1$s %2$s
	foreach index [$listbox curselection] {
	    set file [string range [$listbox get $index] 1 end] 
	    $listbox delete $index
	    if {[$StrlBox(%2$s:isSelectedProc) \
		    $StrlBox(%2$s:dirs:current) $file]} {
		$listbox insert $index "+$file"
	    } else {
		$listbox insert $index " $file"
	    }
	}
	$listbox selection clear 0 end
	# add to history if something done
	SB_AddDirToHistory %2$s $StrlBox(%2$s:dirs:current)

    }
    bind $StrlBox($w:dirs:file:list) <Double-Button-1> \
	    [format $prog $useFileProc $w]

    bind $StrlBox($w:dirs:file:list) <Return> \
	    [bind $StrlBox($w:dirs:file:list) <Double-Button-1>]

    # Extensions
    #-----------
    if {[info exist $extensions] || [llength $extensions] > 1 } {
	set ext [frame $frame.userselect]
	label $ext.ftype -text "File Types:"
	set StrlBox($w:ext:menu) $ext.regexp.button.optionList
	frame $ext.regexp -relief sunken -bd 2
	label $ext.regexp.value \
	    -highlightthickness 0 \
	    -justify center \
	    -textvariable StrlBox($w:ext:label) 

	menubutton $ext.regexp.button \
	    -relief raised \
	    -image $StrlBox(image:down) \
	    -menu $StrlBox($w:ext:menu)
	cb_balloonHelp $ext.regexp.button "File extension menu."
	pack $ext.regexp.button -side right -fill y
	pack $ext.regexp.value -side left -fill y
	
	grid $ext.ftype -row 0 -column 0
	grid $ext.regexp -row 0 -column 1 -sticky ew

	# build regular expressions
	menu $StrlBox($w:ext:menu)
	if {[info exist $extensions]} {
	    eval "global $extensions; SB_FillBrowserMenu $w \$$extensions"
	    $StrlBox($w:ext:menu) configure \
		-postcommand "SB_FillBrowserMenu $w \$$extensions"
	} else {
	    SB_FillBrowserMenu $w $extensions
	}
	pack $ext -side bottom -fill x -pady 2 -anchor w 

    } elseif { [llength $extensions] == 0} {
	set StrlBox($w:ext:regexp) "*"

    } else {
	    set StrlBox($w:ext:regexp) $extensions
    }
	
    pack $dirbar -anchor center -pady 2 -padx 2 

    pack $frame.dir -fill both -expand 1 -side left 
    pack $frame.file -fill both -expand 1 -side left
    
    if {$initialDir == ""} {
	set initialDir $StrlBox(dirs:cwd)
    }
    SB_Browse $w $initialDir
    SB_AddDirToHistory $w $initialDir
}

proc SB_FillBrowserMenu {w extensions} {
    global StrlBox
    $StrlBox($w:ext:menu) delete 0 end
    foreach format $extensions {
	set text   [lindex $format 0]
	set label  [join [lindex $format 1] ","]
	set regexp [lindex $format 1]
	
	$StrlBox($w:ext:menu) add command \
	    -label [format {%s (%s)} $text $label] \
	    -command [format {\
				  set StrlBox(%4$s:ext:label) {%1$s (%2$s)}; \
				  set StrlBox(%4$s:ext:regexp) {%3$s}; \
				  SB_Browse %4$s $StrlBox(%4$s:dirs:current)\
			      } $text $label $regexp $w]
    }
    set format [lindex $extensions 0]
    set text   [lindex $format 0]
    set label  [join [lindex $format 1] ","]
    set regexp [lindex $format 1]

    set StrlBox($w:ext:label) [format {%s (%s)} $text $label]
    set StrlBox($w:ext:regexp) $regexp
}

proc SB_FillDriveMenu {w} {
    global StrlBox

    set menu $StrlBox($w:drive:menu)
    $menu delete 0 end

    set drives [file volume] 

    # removing unused drive
    foreach entry [array names StrlBox "$w:drive:\[a-z\]:/"] {
	regsub -- "$w:drive:" $entry {} drive
	if { [lsearch $drives $drive] == -1} {
	    # no such drive anymore
	    unset StrlBox($entry)
	}
	
    }
    # setting new drives
    foreach drive $drives {
	if { [catch {set dir $StrlBox($w:drive:$drive)} ] } {
	    set dir $drive
	    set StrlBox($w:drive:$drive) $dir
	}
	regsub {/$} $drive {} drive
	$menu add command \
	    -label $drive \
	    -command [format {
		# testing for path.
		if {[file exist %3$s/]} {
		    # drive is ok, looking for file
		    if {[file exist %2$s]} {
			# no such file, taking root.
			set StrlBox(%1$s:drive:%3$s) %2$s
		    }
		    SB_Browse %1$s $StrlBox(%1$s:drive:%3$s/)
		    $StrlBox(%1$s:drive:button) configure -text "%3$s"
		}
	    } $w $dir $drive]

    }
}

# useful macros
# return currently selected dir
proc SB_SelectedDir {w} {
    global StrlBox
    set selected [$StrlBox($w:dirs:dir:list) curselection]
    if {$selected != ""} {
	set selected [$StrlBox($w:dirs:dir:list) get $selected]
    }
    return $selected
}

# return current directory of browser
proc SB_CurrentDirectory {w} {
    global StrlBox
    return $StrlBox($w:dirs:current)
}

# return currently selected files
proc SB_SelectedFiles {w} {
    global StrlBox
    set selected ""
    foreach index [$StrlBox($w:dirs:file:list) curselection] {
	lappend selected [file join \
		$StrlBox($w:dirs:current) \
		[string range \
		[$StrlBox($w:dirs:file:list) get $index] \
		1 end]]
    }
    return $selected
}

# rescan current directory
proc SB_Rescan {w} {
    global StrlBox
    SB_Browse $w $StrlBox($w:dirs:current)
}


# === Private part ===
proc SB_Browse {w dir} {
    global StrlBox tcl_platform

    set top [winfo toplevel $w]
    if { [winfo viewable $top]} {
	$top configure -cursor watch
	update idletasks
    }

    if {$dir == ""} {
	set dir $StrlBox($w:dirs:current)
    }

    set StrlBox($w:dirs:current) $dir

    set path_list [file split $dir]

    if {[file tail $dir]==""} {
	set StrlBox($w:dirs:basename) {/}
    } else {
	set StrlBox($w:dirs:basename) [file tail $dir]
    }


    # Builds the new path menu
    $StrlBox($w:dirs:menu) delete 0 end
    set local_path {}
    foreach path $path_list {
	set local_path [file join $local_path $path]
	$StrlBox($w:dirs:menu) add command \
		-label $path \
	        -command "SB_Browse $w \"$local_path\" "
    }

    # resetting lists
    $StrlBox($w:dirs:dir:list) delete 0 end
    $StrlBox($w:dirs:file:list) delete 0 end

    set cwd [pwd]
    cd $dir
    set entries [lsort  [glob -nocomplain .* *]]
    cd $cwd

    foreach entry $entries {
	if {   ! [string compare $entry "."] \
	    || ! [string compare $entry ".."]} {
	    continue
	}
	
	set file [file join $dir $entry]

	if { [file isfile $file] } {
	    foreach regexp $StrlBox($w:ext:regexp) {
		if {[string match $regexp $entry]} {
		    if {[$StrlBox($w:isSelectedProc) \
			    $StrlBox($w:dirs:current) $entry]} {
			$StrlBox($w:dirs:file:list) insert end "+$entry"
		    } else {
			$StrlBox($w:dirs:file:list) insert end " $entry"
		    }
		    continue
		}
	    }
	    continue
	}

	if {[file isdirectory $file]} {
	    $StrlBox($w:dirs:dir:list) insert end $entry
	    continue
	}
    }

    if { [winfo viewable $top] } {
	$top configure -cursor {}
	update idletasks
    }
}


proc SB_AddDirToHistory {w dir} {
    global StrlBox
    set last [$StrlBox($w:dirs:history) index end]
    if {$last != "none"} {
	for {set entry 0} {$entry<=$last} {incr entry} {
	    if {[$StrlBox($w:dirs:history) entrycget $entry -label]=="$dir"} {
		# entry exist
		return
	    }
	}
    }
    $StrlBox($w:dirs:history) add command \
	    -label $dir \
	    -command "SB_Browse $w \"$dir\" "
    if {[$StrlBox($w:dirs:history) index end] == $StrlBox(dirs:history:size)} {
	$StrlBox($w:dirs:history) delete 0
    }
}

proc SB_SingleBrowserIsSelected {args} {
    return 0
}


proc SB_SingleBrowserUseFile {browser} {
    global StrlBox
    set files [SB_SelectedFiles $browser]
    if {$files == ""} {
	return
    }
    set dir [SB_CurrentDirectory $browser]
    set StrlBox(singleBrowser:dir) $dir
    set StrlBox(singleBrowser:file)  [file tail [lindex $files 0]]
}

set StrlBox(singleBrowser:ask) false
proc SB_SingleBrowser {w parent {extensions ""} {defaultextension ""}} {
    global StrlBox
    toplevel $w
    wm group $w $parent
    wm transient $w $parent

    set oldFocus [focus]
    set oldGrab [grab current $w]
    if {$oldGrab != ""} {
	set grabStatus [grab status $oldGrab]
    }
    grab $w

    set browser $w.browser
    SB_DirFileBrowser \
	$browser \
	SB_SingleBrowserUseFile \
	SB_SingleBrowserIsSelected \
	$extensions \
	$StrlBox(dirs:cwd)

    set StrlBox(singleBrowser:dir) [SB_CurrentDirectory $w.browser]

    $StrlBox($browser:dirs:file:list) configure \
	    -selectmode single
    pack $browser

    label $browser.userselect.label -text "File Name:"
    set entry [entry $browser.userselect.entry \
		   -textvariable StrlBox(singleBrowser:file)]
    grid configure $browser.userselect.ftype -row 1
    grid configure $browser.userselect.regexp -row 1
    grid $browser.userselect.label -row 0 -column 0
    grid $entry -row 0 -column 1 -sticky ew

    set StrlBox(singleBrowser:file) ""

    button $w.ok -text "OK" \
	-command "if {\[SB_SingleBrowserCheck $browser {$defaultextension}\]} {destroy $w}"
    button $w.dismiss -text "Dismiss" \
	-command "set StrlBox(singleBrowser:dir) {}; destroy $w"

    bind $entry <Return> "$w.ok invoke; break"

    pack $w.ok $w.dismiss -side left -expand 1

    SB_Center $w $parent 

    tkwait window $w

    catch {focus $oldFocus}
    catch {
	bind $w <Destroy> {}
	destroy $w
    }
    if {$oldGrab != ""} {
	if {$grabStatus == "global"} {
	    grab -global $oldGrab
	} else {
	    grab $oldGrab
	}
    }
    set file ""

    if {$StrlBox(singleBrowser:dir) != "" && $StrlBox(singleBrowser:file) != ""} {
	set file [file join $StrlBox(singleBrowser:dir) \
		      $StrlBox(singleBrowser:file)]
	if { $defaultextension != "" \
		 && [file extension $file] == ""} {
	    append file ".$defaultextension"
	}
    }
    return $file
}

proc SB_SingleAskBrowser {w parent {extensions ""} {defaultextension ""}} {
    global StrlBox
    set StrlBox(singleBrowser:ask) true
    set file [SB_SingleBrowser $w $parent $extensions $defaultextension]
    set StrlBox(singleBrowser:ask) false
    return $file
}

proc SB_SingleBrowserCheck {browser defaultextension} {
    global StrlBox
    SB_SingleBrowserUseFile $browser
    set status 1
    if { $StrlBox(singleBrowser:ask) } {
	set file ""
	if {$StrlBox(singleBrowser:dir) != "" \
		&& $StrlBox(singleBrowser:file) != ""} {
	    set file [file join $StrlBox(singleBrowser:dir) \
			  $StrlBox(singleBrowser:file)]
	    if { $defaultextension != "" \
		     && [file extension $file] == ""} {
		append file ".$defaultextension"
	    }
	}
	if {[file exist $file]} {
	    set answer [tk_dialog .message Message \
			    "[file tail $file] exists, really want to overwrite?" \
			    info 0 Yes No]
	    if {$answer == 1} {
		set status 0
	    }
	}
    } 
    return $status
}

# Dir browser
#============
proc SB_SingleDirBrowserIsSelected {args} {
    return 0
}


proc SB_SingleDirBrowserUseDir {browser} {
    global StrlBox
    set dir [SB_SelectedDir $browser]
    if {$dir == ""} {
	return
    }
    set StrlBox(singleBrowser:dir) $dir
    set StrlBox(singleBrowser:file) $dir
}

proc SB_SingleDirBrowser {w parent} {
    global StrlBox
    toplevel $w
    wm group $w $parent
    wm transient $w $parent

    set oldFocus [focus]
    set oldGrab [grab current $w]
    if {$oldGrab != ""} {
	set grabStatus [grab status $oldGrab]
    }
    grab $w

    set browser $w.browser
    SB_DirFileBrowser \
        $browser \
	SB_SingleDirBrowserUseDir \
	SB_SingleDirBrowserIsSelected \
         {}\
	$StrlBox(dirs:cwd)
    set StrlBox(singleBrowser:dir) [SB_CurrentDirectory $w.browser]

    pack forget [winfo parent $StrlBox($browser:dirs:file:list)]

    pack $browser

    button $w.ok -text "OK" \
	-command [format {
	    set dir  [SB_SelectedDir %1$s]
	    if { $dir != "" } {
		set StrlBox(singleBrowser:dir) \
		    [file join [SB_CurrentDirectory %1$s]  $dir]
	    } else {
		set StrlBox(singleBrowser:dir) \
		    [SB_CurrentDirectory %1$s]
	    }
	    destroy %2$s
	} $browser $w]

    button $w.dismiss -text "Dismiss" \
	-command "set StrlBox(singleBrowser:dir) {}; destroy $w"

    pack $w.ok $w.dismiss -side left -expand 1

    SB_Center $w $parent 

    tkwait window $w

    catch {focus $oldFocus}
    catch {
	bind $w <Destroy> {}
	destroy $w
    }
    if {$oldGrab != ""} {
	if {$grabStatus == "global"} {
	    grab -global $oldGrab
	} else {
	    grab $oldGrab
	}
    }

    return $StrlBox(singleBrowser:dir)
}
