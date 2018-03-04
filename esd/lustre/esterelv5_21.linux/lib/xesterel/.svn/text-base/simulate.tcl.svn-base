# === Simulation panel ===

global StrlBox

proc SB_SimulateSetMenus {} {
    global StrlBox
    # uniquify extensions
    foreach ext $StrlBox(simulator:extensions) {
	set array([lindex $ext 0]) [lindex $ext 1]
    }
    foreach tool  $StrlBox(tools:list) {
	set ext [lrange $tool 2 3]
	set array([lindex $ext 0]) [lindex $ext 1]
    }
    set StrlBox(simulator:local:extensions) ""
    foreach name [lsort [array names array]] {
	lappend StrlBox(simulator:local:extensions) [list $name $array($name)]
    }

    set StrlBox(simulator:menu:actions) {Compile compile Simulate simulate}
    set i 0
    foreach tool $StrlBox(tools:list) {
	lappend StrlBox(simulator:menu:actions) [lindex $tool 0] tool$i
	# selected files for tool$i
	set StrlBox(simulator:tool$i) ""
	incr i
    }

}

proc SB_Simulate {} {
    global StrlBox 
    if {[winfo exist .simulate]} {
	if {[wm state .simulate] == "normal"} {
	    raise .simulate
	} else {
	    SB_Center .simulate $StrlBox(top)
	    wm deiconify .simulate
	}
	return
    }
    # selected source files to be compiled
    set StrlBox(simulator:files) "" 
    # selected object files to be simulated
    set StrlBox(simulator:objects) ""
    # ``pointer'' to selected files for browser
    set StrlBox(simulator:selection) files


    # previous command
    set StrlBox(simulator:prev_cmd)  ""
    # final command line
    set StrlBox(simulator:line) ""
    # final command line format
    set StrlBox(simulator:line:format) $StrlBox(simulator:compile)

    toplevel .simulate

    wm group .simulate $StrlBox(top)
    wm transient .simulate $StrlBox(top)
    wm withdraw .simulate
    set StrlBox(browser:simul) .simulate.lists
    SB_SimulateSetMenus

    SB_DirFileBrowser \
	    .simulate.lists \
	    SB_UseSimulationFiles \
	    SB_IsSimulationFileSelected \
	    StrlBox(simulator:local:extensions)

    pack .simulate.lists -expand 1 -fill both
    set StrlBox(simulator:entry) .simulate.cmd
    pack [entry .simulate.cmd \
	    -textvariable StrlBox(simulator:line) \
	    -highlightthickness 0 \
	    -selectbackground RoyalBlue \
	    -selectforeground white \
	    -state $StrlBox(command:edition)] \
	    -padx 4 -pady 4 -fill x
    scrollbar .simulate.cmd_scroll \
	    -orient horizontal \
	    -command ".simulate.cmd xview"
    pack .simulate.cmd_scroll -fill x
    .simulate.cmd configure \
	-xscrollcommand ".simulate.cmd_scroll set"

    pack [frame .simulate.action]


    SB_BuildOptionMenu 0 .simulate.action \
	    simulator action \
	    "Action" \
	    "Action to perform on files: simulation on objects, compilation for C code." \
	    StrlBox(simulator:menu:actions) \
	    SB_SelectSimulationCommand
	     
    pack [button .simulate.run \
	    -text "Do It" \
	    -command SB_SimulateCommand] -side left -expand 1

    pack [button .simulate.quit -text Dismiss \
	    -command {wm withdraw .simulate}] -side left -expand 1

    SB_Center .simulate $StrlBox(top)
    wm deiconify .simulate    
}


proc SB_IsSimulationFileSelected {dir file} {
    global StrlBox 
    upvar #0 StrlBox(simulator:$StrlBox(simulator:selection)) selection

    if {! [regsub "^$StrlBox(dirs:cwd)" $dir {.} path]} {
	set path $dir
    }

    set file [file join $path $file]
    if {[lsearch $selection $file] == -1} {
	return 0
    } else {
	return 1
    }
}

proc SB_UseSimulationFiles {browser} {
    global StrlBox 
    upvar #0 StrlBox(simulator:$StrlBox(simulator:selection)) selection

    set dir [SB_CurrentDirectory $browser]
    set files [SB_SelectedFiles $browser]

    if {$files == ""} {
	return
    }

    if {! [regsub "^$StrlBox(dirs:cwd)" $dir {.} path]} {
	set path $dir
    }

    foreach file $files {
	set file [file join $path $file]
	if {[set index [lsearch $selection $file]] == -1} {
	    lappend selection $file
	} else {
	    set selection [lreplace $selection $index $index]
	}
    }
    SB_BuildSimulationCommand 
}

proc SB_SelectSimulationCommand {} {
    global StrlBox

    switch $StrlBox(simulator:menu:action:value) {
	simulate {
	    # kind of file to select
	    set StrlBox(simulator:selection) objects
	    # set command line format
	    set StrlBox(simulator:line:format) \
		    $StrlBox(simulator:simulate)
	}

	compile {
	    # kind of file to select
	    set StrlBox(simulator:selection) files
	    # set command line format
	    set StrlBox(simulator:line:format) \
		    $StrlBox(simulator:compile)
	}

	default {
	    # kind of file to select, here tool0, tool1, etc...
	    set StrlBox(simulator:selection) $StrlBox(simulator:menu:action:value)
	    # get tool index from name
	    set index [string range $StrlBox(simulator:menu:action:value) 4 end]
	    # set command line format
	    set StrlBox(simulator:line:format) \
		[lindex [lindex $StrlBox(tools:list) $index] 1]
	}
    }
    # rescan with correct file selection 
    SB_Rescan $StrlBox(browser:simul)
    SB_BuildSimulationCommand
}

proc SB_BuildSimulationCommand {} {
    global StrlBox 
    upvar #0 StrlBox(simulator:$StrlBox(simulator:selection)) selection
    set files ""

    foreach file $selection {
	set file [SB_FileToAppDir $file]
	if {[regexp "\[ \t\]" $file]} {
	    append files " \"$file\""
	} else {
	    append files " $file"
	}
    }
    set StrlBox(simulator:line)  \
	    [format $StrlBox(simulator:line:format) $files]
}

proc SB_SimulateCommand {} {
    global StrlBox
    $StrlBox(simulator:entry) selection from 0
    $StrlBox(simulator:entry) selection to end
    SB_Exec $StrlBox(simulator:line)
    $StrlBox(simulator:entry) selection clear
    SB_Rescan $StrlBox(browser:simul)
}


