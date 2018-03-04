proc SB_SaveConfiguration {} {
    global StrlBox 
    set dump_file [SB_SingleAskBrowser \
		       .configuration \
		       $StrlBox(top) \
		       {{{Xesterel saves} *.xsv} {All {*}}} \
		       xsv]

    if {$dump_file == ""} {
	return
    }
    if {[catch {open $dump_file w} fd]} {
	tk_dialog .alert "Error" $fd error 0 OK
	return
    }

    set searchId [array startsearch StrlBox]
    while {[array anymore StrlBox $searchId]} {
	set key [array nextelement StrlBox $searchId]
	puts $fd "set Dump($key) {$StrlBox($key)}"
    }
    array donesearch  StrlBox $searchId
    close $fd
}

proc SB_LoadConfiguration {} {
    global StrlBox
    set file [SB_SingleBrowser \
		  .configuration \
		  $StrlBox(top) \
		  {{{Xesterel saves} *.xsv} {All {*}}}]
    if {$file == ""} {
	return
    }
    if {[catch {source $file} error]} {
	tk_dialog .error Error "Cannot load dump: $error" error 0 OK
	return
    }
    set searchId [array startsearch Dump]
    while {[array anymore Dump $searchId]} {
	set key [array nextelement Dump $searchId]
	set StrlBox($key) $Dump($key)
    }
    array donesearch  Dump $searchId
    unset Dump
    
    # Fix settings
    eval $StrlBox(autoCheckCommand)
    eval $StrlBox(autoBackupCommand)
    SB_CheckProcessorOptions
    SB_CheckBackups
    SB_EsterelOptions 1
    cd $StrlBox(dirs:cwd)
    SB_Browse $StrlBox(browser:main) $StrlBox(dirs:cwd)
}    

proc SB_SaveLastCommand {} {
    global StrlBox
    if { ![info exist StrlBox(file:last_save) ] } {
	set file ""
	switch [tk_dialog \
		    .what "Save" "Choose how to save command" info \
		    0 "Command Script" Makefile Cancel] \
	{
	    0 {
		set what command
	    }
	    1 {
		set what makefile
	    }
	    2 {
		return
	    }
		       
	}
    } else {
	set what [lindex $StrlBox(file:last_save) 0]
	set file [lindex $StrlBox(file:last_save) 1]
    }
    switch $what {
	makefile {
	    SB_WriteMakefile $file
	}
	command {
	    SB_SaveCommand $file
	}
    }
}


proc SB_WriteMakefile {{makefile ""}} {
    global StrlBox

    catch {unset StrlBox(file:last_save)}
    
    if { $makefile == "" } {
	set makefile [SB_SingleAskBrowser .makefile $StrlBox(top) \
			  {{Makefiles {*.mke}} \
			       {All {*}}} mke]
	
	if {$makefile == ""} {
	    return
	}
    }
    
    if {[catch "open $makefile w" fd]} {
	error $fd
    }

    puts $fd "STRL_CMD = $StrlBox(esterel)"
    puts $fd ""
    puts -nonewline $fd "STRL_OPTIONS = "
    foreach option [split $StrlBox(esterel:options)] {
	if {$option == ""} {
	    continue
	}
	puts -nonewline $fd "\\\n   $option"
    }
    puts $fd "\n"
    puts -nonewline $fd "STRL_PROC_OPTIONS ="
    foreach option [split $StrlBox(processor:options)] {
	if {$option == ""} {
	    continue
	}
	puts -nonewline $fd " \\\n   $option"
    }
    puts $fd "\n"
    puts -nonewline $fd "STRL_BACKUP_OPTIONS ="
    foreach option [split $StrlBox(processor:backups)] {
	if {$option == ""} {
	    continue
	}
	puts -nonewline $fd " \\\n   $option"
    }
    puts $fd "\n"

    puts -nonewline $fd "STRL_FLAGS ="
    foreach macro {STRL_OPTIONS STRL_PROC_OPTIONS STRL_BACKUP_OPTIONS} {
	puts -nonewline $fd " \\\n   \$($macro)"
    }
    puts $fd "\n"

    # files.
    puts -nonewline $fd "STRL_FILES ="
    foreach file $StrlBox(files:selected) {
	set dir [file dirname $file]
	set base [file tail $file]
	if {! [regsub "^$StrlBox(dirs:cwd)" $dir {.} path]} {
	    set path $dir
	}
	puts -nonewline $fd " \\\n   "
	puts -nonewline $fd [file join $path $base]
    }
    puts $fd "\n"

    puts $fd "all:"
    puts $fd "\t\$(STRL_CMD) $(STRL_FLAGS) $(STRL_FILES)"

    close $fd

    set StrlBox(file:last_save) [list makefile $makefile]
    return
}

proc SB_SaveCommand {{file ""}} {
    global StrlBox tcl_platform

    catch {unset StrlBox(file:last_save)}

    if { $tcl_platform(platform) == "unix" } {
	set defaultextension sh
	set filetypes {
	    {{Command Files} *.sh} 
	    {All {*}}}
	set script "\#!/bin/sh\n$StrlBox(command:line)"
	
    } else {
	# NT
	set defaultextension cmd
	set filetypes {
	    {{Command Files} {*.cmd *.bat}} 
	    {All {*}}}
	set script "$StrlBox(command:line)"
    }

    if {$file == ""} {
	set file [SB_SingleAskBrowser .script $StrlBox(top) \
		  $filetypes $defaultextension]
	
	if {$file == ""} {
	    return
	}
    }

    if {[catch {open $file w} fd]} {
	tk_dialog .alert "Error" $fd error 0 OK
	return
    }
    puts $fd $script
    close $fd
    set StrlBox(file:last_save) [list command $file]
    return
}


