set StrlBox(processor:options) ""
set StrlBox(processor:backups) ""
set StrlBox(esterel:options) ""
set StrlBox(esterel:option:keep) ""
# from processor.tcl : auto build
set StrlBox(esterel:menu:stop:value) -
set StrlBox(esterel:centry:value:wizard) ""
set StrlBox(esterel:centry:option:wizard) ""
set StrlBox(esterel:centry:option:main) ""

proc SB_EsterelKeepOptions {option} {
    # see processor.tcl
    global StrlBox
    set StrlBox(esterel:option:keep) ""
    set all [$StrlBox(esterel:cmenu:keep) index end]
    if {$option == $all} {
	# all changed, reset other entries
	if {$StrlBox(esterel:cmenu:keep:$all) != ""} {
	    for {set i 0} {$i<$all} {incr i} {
		set StrlBox(esterel:cmenu:keep:$i) ""
	    }
	    set StrlBox(esterel:option:keep) -K
	}
    } else {
	# unset all
	set StrlBox(esterel:cmenu:keep:$all) ""
    }
    for {set i 0} {$i<$all} {incr i} {
	if {$StrlBox(esterel:cmenu:keep:$i) != ""} {
	    lappend  StrlBox(esterel:option:keep) \
		    -K$StrlBox(esterel:cmenu:keep:$i)
	}
    }
}

proc SB_EsterelOptions {{expert 0}} {
    global StrlBox

    set StrlBox(esterel:output_option) ""
    # -B, -main option
    foreach option {basename main} {
	if {$StrlBox(esterel:centry:option:$option) != ""}  {
	    if {$StrlBox(esterel:centry:value:$option) != ""}  {
		lappend StrlBox(esterel:output_option) \
			$StrlBox(esterel:centry:option:$option) \
			$StrlBox(esterel:centry:value:$option) 
	    } else {
		if { [focus] != $StrlBox(esterel:centry:entry:$option) } {
		    set StrlBox(esterel:centry:option:$option) ""
		}
	    }
	}
    }

    if {$StrlBox(esterel:centry:option:dirname) != ""}  {
	if {$StrlBox(esterel:centry:value:dirname) != ""}  {
	    set dir $StrlBox(esterel:centry:fullvalue:dirname)
	    if { ! [ file isdirectory $dir ] } {
		tk_dialog .err "Xesterel Message" \
		    "$file is not a directory" \
		    info \
		    0 \
		    OK
	    }
	    set StrlBox(esterel:centry:value:dirname) \
		[SB_FileToAppDir $dir]
	    lappend StrlBox(esterel:output_option) \
		$StrlBox(esterel:centry:option:dirname) \
		$StrlBox(esterel:centry:value:dirname) 
	} else {
	    if { [focus] != $StrlBox(esterel:centry:entry:dirname) } {
		set StrlBox(esterel:centry:option:dirname) ""
	    }
	}
    }

    if { $StrlBox(esterel:output_option) != "" } {
	append command " $StrlBox(esterel:output_option)"
    }
    # language options.
    if {$expert} {
	# called from options menu. Can modify global options
	if {$StrlBox(esterel:menu:stop:value) != "-"} {
	    # stop option, unset compilation mode and language
	    # note that compilation values are not defined in
	    # the menu
	    set StrlBox(esterel:menu:language:value)  "-"
	    set StrlBox(esterel:menu:language:label) None
	    set StrlBox(esterel:menu:compilation:value) ""
	    set StrlBox(esterel:menu:compilation:label) Intermediate
	} elseif {$StrlBox(esterel:menu:compilation:value) == ""} {
	    # no stop option, but no compilation too. Reset it.
	    $StrlBox(esterel:menu:compilation) invoke 0
	    $StrlBox(esterel:menu:language) invoke 0
	}
    } else {
	# select from main panel, override possible expert options
	if {$StrlBox(esterel:menu:compilation:value) != ""} {
	    catch {
		set StrlBox(esterel:menu:stop:value) "-"
		set StrlBox(esterel:menu:stop:label) \
			[$StrlBox(esterel:menu:stop) entrycget 0 -label]
	    }
	}
    }
    # Ok, now we can build language related options.
    if { $StrlBox(esterel:menu:stop:value) != "-" } {
	# stop at intermediate code
	lappend command $StrlBox(esterel:menu:stop:value)
    } elseif {   $StrlBox(esterel:menu:language:value) == "-" \
	      || $StrlBox(esterel:menu:compilation:value) == "-Icheck"} {
	  # language is none, or check
	lappend command "$StrlBox(esterel:menu:compilation:value)"
        set StrlBox(esterel:menu:language:value) "-"
        set StrlBox(esterel:menu:language:label) None
    } else {
	set kind $StrlBox(esterel:menu:compilation:value)
	set lang $StrlBox(esterel:menu:language:value)

	set inline 0
	switch -- $kind {
	    -L {
		set class sscl
		if {[SB_CheckLanguage $lang {c ansic blif softBlif}]} {
		    return
		}
	    }
	    -I {
		set class scl
		if {[SB_CheckLanguage $lang {c ansic}]} {
		    return
		}
	    }
	    inlineAutomaton {
		set kind -A
		set class ocl
		if {[SB_CheckLanguage $lang {c ansic fc2}]} {
		    return
		}
		set inline 1
	    }
	    -A {
		set class ocl
		if {[SB_CheckLanguage $lang {c ansic fc2}]} {
		    return
		}
	    }
	    -S {
		set class ocl
		if {[SB_CheckLanguage $lang {c ansic fc2}]} {
		    return
		}
	    }
	}

	switch $lang {
	    softBlif {
		set lang blif
		set lang_opt $StrlBox(language:$lang:$class:options)
		if {$lang_opt != ""} {
		    set lang_opt "-soft $lang_opt"
		} else {
		    set lang_opt -soft
		}
	    }
	    ansic  {
		set lang c
		set lang_opt $StrlBox(language:$lang:$class:options)
		if {$lang_opt != ""} {
		    set lang_opt "-ansi $lang_opt"
		} else {
		    set lang_opt -ansi
		}
	    }
		
	    default {
		set lang_opt $StrlBox(language:$lang:$class:options)
	    }
	}
	if {$inline} {
	    regsub -- {-inline *} $lang_opt {} lang_opt
	    if {$lang_opt != ""} {
		set lang_opt "-inline $lang_opt"
	    } else {
		set lang_opt -inline
	    }
	}

	set comp_cmd $kind$lang
	if {$lang_opt != ""} {
	    append comp_cmd ":\"$lang_opt\""
	}
	append command " $comp_cmd"
    }

    # global options
    foreach option {silent simul causal single cycles verbose} {
	if {$StrlBox(esterel:check:$option) != ""} {
	    lappend command $StrlBox(esterel:check:$option)
	}
    }

    # Warnings
    if {$StrlBox(esterel:menu:warnings:value) != "-"} {
	lappend command $StrlBox(esterel:menu:warnings:value)
    }

    # keep
    if {$StrlBox(esterel:option:keep) != ""} {
	append command " $StrlBox(esterel:option:keep)"
    }
    
    # wizard 
    if {$StrlBox(esterel:centry:option:wizard) != ""}  {
	if {$StrlBox(esterel:centry:value:wizard) != ""}  {
	    append command " $StrlBox(esterel:centry:value:wizard)"
	} else {
	    set StrlBox(esterel:centry:option:wizard) ""
	}
    }
    # final command
    set StrlBox(esterel:options) $command
}

proc SB_CheckLanguage {lang validLanguages} {
    global StrlBox
    foreach valid $validLanguages {
	if {$lang == $valid} {
	    return 0
	}
    }
    set top [toplevel .info]
    wm title $top "Preferences"
    wm group $top $StrlBox(top)
    wm transient $top $StrlBox(top)
    pack [button $top.ok -text OK -command "destroy $top"] -side bottom
    pack [label $top.info -bitmap info -foreground red] \
	    -side left -ipadx 5m
    pack [message $top.message \
	    -aspect 300 \
	    -relief sunken -bd 2 \
	    -bg white] -padx 4 -pady 4 -side left
    $top.message configure -text "
Compilation type \"$StrlBox(esterel:menu:compilation:label)\" and \
language \"$StrlBox(esterel:menu:language:label)\" are incompatible
"


    SB_Center $top $StrlBox(top)

    set oldFocus [focus]
    set oldGrab [grab current $top]
    if {$oldGrab != ""} {
	set grabStatus [grab status $oldGrab]
    }
    grab $top

    tkwait window $top

    catch {focus $oldFocus}
    if {$oldGrab != ""} {
	if {$grabStatus == "global"} {
	    grab -global $oldGrab
	} else {
	    grab $oldGrab
	}
    }
    return 1
}

proc SB_BuildCommand {} {
    global StrlBox
    
    set command $StrlBox(esterel)
    if {$StrlBox(esterel:options) != ""} {
	append command " $StrlBox(esterel:options)"
    }

    if {$StrlBox(processor:options) != ""} {
	append command $StrlBox(processor:options)
    }
    if {$StrlBox(processor:backups) != ""} {
	append command $StrlBox(processor:backups)
    }
    

    # files.
    set files ""
    foreach file $StrlBox(files:selected) {
	set file [SB_FileToAppDir $file]
	if {[regexp "\[ \t\]" $file]} {
	    append files " \"$file\""
	} else {
	    append files " $file"
	}
    }
    set StrlBox(command:line) "$command$files"
    return
}


proc SB_RunCommand {} {
    global StrlBox
    $StrlBox(command:entry) selection from 0
    $StrlBox(command:entry) selection to end
    SB_Exec $StrlBox(command:line)
    $StrlBox(command:entry) selection clear
    SB_Rescan $StrlBox(browser:main)
}

proc SB_UseFiles {browser} {
    global StrlBox
    set dir [SB_CurrentDirectory $browser]
    set files [SB_SelectedFiles $browser]

    if {$files == ""} {
	return
    }

    foreach file $files {
	set ext [string range [file extension "$file"] 1 end]
	if {[lsearch $StrlBox(formats) $ext]<0} {
	    continue
	}
	set file [file join $dir $file]
	if {[set index \
		[lsearch $StrlBox(files:selected) \
		$file]] == -1} {
	    lappend StrlBox(files:selected) $file
	} else {
	    set StrlBox(files:selected) \
		    [lreplace $StrlBox(files:selected) $index $index]
	}
    }
    SB_BuildCommand
}

proc SB_IsFileSelected {dir file} {
    global StrlBox

    set ext [string range [file extension "$file"] 1 end]
    if {[lsearch $StrlBox(formats) $ext]<0} {
	return 0
    }
    set file [file join $dir $file]
    if {[lsearch $StrlBox(files:selected) $file] == -1} {
	return 0
    } else {
	return 1
    }
}


