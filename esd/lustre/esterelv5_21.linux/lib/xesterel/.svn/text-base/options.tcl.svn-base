# === Option panel building and management ===
# === Save management ===

set StrlBox(prefs:balloon) 1

proc SB_Preferences {} {
    global StrlBox tcl_platform
    if {[winfo exist .pref]} {
	raise .pref
	return
    }
    toplevel .pref 
    wm title .pref "Preferences"
    wm group .pref $StrlBox(top)
    wm transient .pref $StrlBox(top)

    # Compiler
    #---------
    pack [frame .pref.comp]
    pack [label .pref.comp.l -text "Esterel Compiler:"] -side left
    pack [entry .pref.comp.e -width 30 \
	    -textvariable StrlBox(prefs:esterel)] \
	    -side left
    set StrlBox(prefs:esterel) $StrlBox(esterel)
    pack [button .pref.comp.b \
	    -text "Browse..." \
	    -highlightthickness 0 \
	    -padx 0 -pady 0] -side left
    .pref.comp.b configure -command {
	set file [SB_SingleBrowser .browse .pref]
	if {$file != ""} {
	    set StrlBox(prefs:esterel) $file
	}
    }
    bind .pref.comp.e <Key-Tab> \
	    "SB_BrowseCompleteFilename %W StrlBox(prefs:esterel)"
    cb_balloonHelp .pref.comp.e "Select Esterel Compiler"

    # simulator
    #----------
    pack [frame .pref.sim] -anchor w
    pack [label .pref.sim.l -text "Simulator:"] -side left
    pack [frame .pref.sim.f -bd 2 -relief sunken] -side left -padx 2
    pack [entry .pref.sim.f.e -relief flat -highlightthickness 0 \
	    -textvariable StrlBox(prefs:simulator:simulate) \
	    -width 30] -side left

    set button  .pref.sim.f.b
    pack [menubutton $button \
	    -image $StrlBox(image:down) \
	    -relief raised] -side left -fill y
    cb_balloonHelp .pref.sim.f.e "Choose a simulator command"
    set menu [menu $button.optionList]
    $button configure -menu $menu
    SB_FillSimMenu $menu
    pack [button .pref.sim.add \
	    -highlightthickness 0 -padx 0 -pady 0\
	    -text + \
	    -command {\
	    set StrlBox(simulator:list) [linsert \
	       $StrlBox(simulator:list) \
	       0 $StrlBox(prefs:simulator:simulate)] ; \
	    SB_FillSimMenu .pref.sim.f.b.optionList \
	}] -side left -fill y
    cb_balloonHelp .pref.sim.add "Add new simulator command to list"
    set cmd {
	set index [lsearch $StrlBox(simulator:list) \
		$StrlBox(prefs:simulator:simulate)]
	if {$index != -1} {
	    set StrlBox(simulator:list) \
                    [lreplace $StrlBox(simulator:list) $index $index]
	    SB_FillSimMenu .pref.sim.f.b.optionList
	}   
    }

    pack [button .pref.sim.del \
	    -highlightthickness 0 -padx 0 -pady 0\
	    -text "-" \
	    -command $cmd] -side left -fill y
    cb_balloonHelp .pref.sim.del "Remove simulator command to list"

    # C compiler
    #-----------
    pack [frame .pref.cc] -anchor w
    pack [label .pref.cc.l -text "C Compiler:"] -side left
    pack [entry .pref.cc.e -width 30 \
	    -textvariable StrlBox(prefs:simulator:compile)] \
	    -side left
    set StrlBox(prefs:simulator:compile) $StrlBox(simulator:compile)
    cb_balloonHelp .pref.cc.e "Command to produce .o files"

    # Viewer
    #-------
    pack [frame .pref.view] -anchor w
    pack [label .pref.view.l -text "Viewer Command:"] -side left
    pack [entry .pref.view.e -width 30 \
	    -textvariable StrlBox(prefs:viewer)] \
	    -side left
    set StrlBox(prefs:viewer) $StrlBox(viewer)
    cb_balloonHelp .pref.view.e "Command for viewing files"

    # Other tools
    #------------
    pack [frame .pref.tools] -anchor w
    listbox .pref.tools.list \
	-selectmode single \
	-height 1 \
	-highlightthickness 0
    scrollbar .pref.tools.v \
	-orient vertical \
	-command {.pref.tools.list yview}
    scrollbar .pref.tools.h \
	-orient horizontal \
	-command {.pref.tools.list xview}
    .pref.tools.list configure \
	-xscrollcommand {.pref.tools.h set} \
	-yscrollcommand {.pref.tools.v set} 
    label .pref.tools.l -text "Other tools:"
    frame .pref.tools.b

    pack [button .pref.tools.b.add  \
	      -text "Add" -command {SB_ToolAdd .pref.tools.list} \
	      -highlightthickness 0] \
	-expand 1 -fill x
    pack [button .pref.tools.b.edit \
	      -text "Edit" -command {SB_ToolEdit .pref.tools.list} \
	      -highlightthickness 0] \
	-expand 1 -fill x
    pack [button .pref.tools.b.del \
	      -text "Del" -command {SB_ToolDel .pref.tools.list} \
	      -highlightthickness 0] \
	-expand 1 -fill x
    grid .pref.tools.l -row 0 -column 0 -sticky w
    grid .pref.tools.b -row 1 -column 0 
    grid .pref.tools.list -row 1  -column 1 -sticky ns
    grid .pref.tools.v -row 1  -column 2 -sticky ns
    grid .pref.tools.h -row 4 -column 1 -sticky we

    
    foreach tool [set StrlBox(prefs:tools:list) $StrlBox(tools:list)] {
	.pref.tools.list insert end [lindex $tool 0]
    }
    # exec
    #-----
    if { $tcl_platform(platform) == "unix" } {
	pack [menubutton .pref.exec \
		-relief raised \
		-text "Execution mode" \
		-indicatoron 1 \
		-menu .pref.exec.optionList] \
		-anchor w -padx 4 -pady 4
	cb_balloonHelp .pref.exec "How to execute command. \
		Results may be printed on a console, on stdout or \
		command may be simply printed."
	menu .pref.exec.optionList -selectcolor red
	.pref.exec.optionList add radiobutton \
		-label "Use console" \
		-variable StrlBox(prefs:exec:mode) \
		-value console
	.pref.exec.optionList add radiobutton \
		-label "Use Stdout" \
		-variable StrlBox(prefs:exec:mode) \
		-value run
	.pref.exec.optionList add radiobutton \
		-label "Print command only" \
		-variable StrlBox(prefs:exec:mode) \
		-value print
	set StrlBox(prefs:exec:mode) $StrlBox(exec:mode)
    }

    # command edition
    #----------------
    pack [checkbutton .pref.edition \
	    -text "Allow Command Line Edition" \
	    -offvalue disabled \
	    -onvalue normal \
	    -variable StrlBox(prefs:command:edition)] \
	    -anchor w
    cb_balloonHelp .pref.edition \
	    "Final compiler or simulator command may be edited or not"
    set StrlBox(prefs:command:edition) $StrlBox(command:edition)

    # Balloons
    #---------
    checkbutton .pref.balloons \
	    -text "Balloons active at start up" \
	    -variable StrlBox(prefs:balloon)
    pack .pref.balloons -anchor w

    set StrlBox(prefs:balloon) 1

    pack [frame .pref.bot] -fill x
    pack [button .pref.bot.ok -text OK \
	    -command {
	set StrlBox(esterel) $StrlBox(prefs:esterel)
	set StrlBox(simulator:simulate) $StrlBox(prefs:simulator:simulate) 
	if { $tcl_platform(platform) == "unix" } {
	    set StrlBox(exec:mode) $StrlBox(prefs:exec:mode) 
	}
	set StrlBox(command:edition) $StrlBox(prefs:command:edition)
	foreach entry {command simulator} {
	    catch {$StrlBox($entry:entry) \
		    configure -state $StrlBox(command:edition)}
	}
	set StrlBox(simulator:compile) $StrlBox(prefs:simulator:compile)
	set StrlBox(viewer) $StrlBox(prefs:viewer) 
	set StrlBox(help:balloon) $StrlBox(prefs:balloon)
        set StrlBox(tools:list) $StrlBox(prefs:tools:list)
	SB_BuildCommand
	catch SB_BuildSimulationCommand
        SB_SimulateSetMenus
	destroy .pref
    }] -expand 1 -side left

    pack [button .pref.bot.cancel -text Cancel \
	    -command {destroy .pref} ] -expand 1 -side left

    pack [button .pref.bot.default -text Defaults \
	    -command {
	set StrlBox(prefs:esterel) esterel
	set StrlBox(simulator:list) $StrlBox(simulator:defaults)
	SB_FillSimMenu .pref.sim.f.b.optionList
	set StrlBox(simulator:compile) "gcc -c %s"
	set StrlBox(prefs:simulator:simulate) $StrlBox(simulator:simulate)
	set StrlBox(prefs:exec:mode)  console
	set StrlBox(prefs:command:edition) disabled
	set StrlBox(prefs:balloon) 1
	set StrlBox(prefs:viewer) "builtin %s"
	} ] -expand 1 -side left

    SB_Center .pref $StrlBox(top)
}

proc SB_FillSimMenu {menu} {
    global StrlBox
    $menu delete 0 end
    foreach sim $StrlBox(simulator:list) {
	$menu add command \
		-label $sim \
		-command "set StrlBox(prefs:simulator:simulate) \"$sim\""
    }
    catch "$menu invoke 0"
}

proc SB_SaveOptions {} {
    global StrlBox env tcl_platform
    if {[catch "open $StrlBox(rc_file) w" fd]} {
	tk_dialog .err Error $fd error 0 Ok
	return
    }

    puts $fd "# Esterel compiler"
    puts $fd "set StrlBox(esterel) \"$StrlBox(esterel)\""
    puts $fd "# Simulator"
    puts $fd "set StrlBox(simulator:list) {"
    foreach sim $StrlBox(simulator:list) {
	puts $fd "   \"$sim\""
    }
    puts $fd "}"
    puts $fd "set StrlBox(simulator:simulate) \"$StrlBox(simulator:simulate)\""
    puts $fd "# C Compiler command"
    puts $fd "set StrlBox(simulator:compile) \"$StrlBox(simulator:compile)\""
    puts $fd "# Tool List"
    if { $StrlBox(tools:list) == "" } {
	puts $fd "set StrlBox(tools:list) {}"
    } else {
	puts $fd "set StrlBox(tools:list) {"
	foreach tool $StrlBox(tools:list) {
	    puts $fd "{$tool}"
	}
	puts $fd "}"
    }
    puts $fd "# Viewer command"
    puts $fd "set StrlBox(viewer) \"$StrlBox(viewer)\""
    puts $fd "# Default compilation kind"
    puts $fd "set StrlBox(esterel:menu:compilation:value) \"$StrlBox(esterel:menu:compilation:value)\""
    puts $fd "# Default language" 
    puts $fd "set StrlBox(esterel:menu:language:value) \"$StrlBox(esterel:menu:language:value)\""
    puts $fd "# Causality analysis"
    puts $fd "set StrlBox(esterel:check:causal) \"$StrlBox(esterel:check:causal)\""
    puts $fd "# Single signals check"
    puts $fd "set StrlBox(esterel:check:single) \"$StrlBox(esterel:check:single)\""
    puts $fd "# Simulation mode"
    puts $fd "set StrlBox(esterel:check:simul) \"$StrlBox(esterel:check:simul)\""
    puts $fd "# Silent mode"
    puts $fd "set StrlBox(esterel:check:silent) \"$StrlBox(esterel:check:silent)\""
    puts $fd "# Warnings"
    puts $fd "set StrlBox(esterel:menu:warnings:value) \"$StrlBox(esterel:menu:warnings:value)\""
    puts $fd "# Ballons"
    puts $fd "set StrlBox(help:balloon) $StrlBox(help:balloon)"
    puts $fd "# Command edition"
    puts $fd "set StrlBox(command:edition) \"$StrlBox(command:edition)\""
    if { $tcl_platform(platform) == "unix" } {
	puts $fd "# Execution mode"
	puts $fd "set StrlBox(exec:mode) \"$StrlBox(exec:mode)\""
    }
    close $fd
}


# Tool list management
proc SB_ToolAdd {list} {
    global StrlBox
    set tool [SB_ToolForm]
    if {$tool != ""} {
	$list insert end [lindex $tool 0]
	lappend StrlBox(prefs:tools:list) $tool
    }
}

proc SB_ToolEdit {list} {
    global StrlBox
    if {[set tool [$list curselection]] == ""} {
	return
    }
    set newtool [SB_ToolForm [lindex $StrlBox(prefs:tools:list) $tool]]
    if {$newtool != ""} {
	$list delete $tool
	$list insert $tool [lindex $newtool 0]
	set StrlBox(prefs:tools:list) \
	    [lreplace  $StrlBox(prefs:tools:list) $tool $tool $newtool]
    }
}

proc SB_ToolDel {list} {
    global StrlBox
    if {[set tool [$list curselection]] == ""} {
	return
    }
    $list delete $tool
    set StrlBox(prefs:tools:list) \
	[lreplace  $StrlBox(prefs:tools:list) $tool $tool]
}


proc SB_ToolForm {{tool ""}} {
    global StrlBox

    if {[winfo exist .toolform]} {
	raise $tf
	return
    }
    set tf [toplevel .toolform]
    wm title $tf "Tool Form"

    set i 0
    foreach item { 
	{"Tool name:" "Name for menus"}
	{"Command:" "Command to run. %%s will be replaced by selected file"}} {

	grid [label $tf.l$i -text [lindex $item 0]] \
	    -row $i -column 0 -sticky w
	set e [entry $tf.e$i]
	$e insert 0 [lindex $tool $i]
	grid $e -row $i -column 1
	cb_balloonHelp $e [lindex $item 1]
	incr i
    }
    
    # Tool file type
    SB_BuildOptionMenu 2 $tf tools ftype \
	"File type" "Select a file type or add a new one" \
	[SB_GetFileTypes] \
	SB_ToolFileType \
	true
    set StrlBox(tools:menu:ftype:label) [lindex $tool 2]

    # Tool file type extension
    set item {"Ext. regexp:" \
		  {File extension regexp. Ex: \"*.c\", or \"*.ic *.lc\" }}
    set i 3
    grid [label $tf.l$i -text [lindex $item 0]] \
	-row $i -column 0 -sticky w
    set e [entry $tf.e$i]
    $e insert 0 [lindex $tool $i]
    grid $e -row $i -column 1
    cb_balloonHelp $e [lindex $item 1]
    $e configure -textvariable StrlBox(tools:menu:ftype:regexp)

    # final button
    grid [button $tf.name -text "OK" -command {set sb_tool_set 1}] \
	-row 4 -column 0 
    grid [button $tf.ko -text "Cancel" -command {set sb_tool_set 0}] \
	-row 4 -column 1 

    tkwait variable sb_tool_set

    global sb_tool_set
    set tool ""
    if { $sb_tool_set != 0} {
	set tool [list [$tf.e0 get] \
		       [$tf.e1 get] \
		      $StrlBox(tools:menu:ftype:label) \
		      $StrlBox(tools:menu:ftype:regexp) ]
    }
    destroy $tf
    return $tool
}

proc SB_ToolFileType {} {
    global StrlBox FileTypes
    set StrlBox(tools:menu:ftype:regexp) \
	$FileTypes($StrlBox(tools:menu:ftype:label))
}

proc SB_GetFileTypes {} {
    # returns a list of type regexp type regexp ....
    global StrlBox FileTypes
    foreach class {files simulator} {
	foreach item $StrlBox($class:extensions) {
	    set FileTypes([lindex $item 0]) [lindex $item 1]
	}
    }

    foreach tool  $StrlBox(prefs:tools:list) {
        set ext [lrange $tool 2 3]
        set FileTypes([lindex $ext 0]) [lindex $ext 1]
    }

    foreach type [lsort [array names FileTypes]] {
	lappend file_types $type $FileTypes($type)
    }

    return $file_types
}
