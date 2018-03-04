# -*- tcl -*-

if {[regsub {.*(v[0-9_]+).*} {$Name:  $} {\1} version]} {
    set StrlBox(VERSION) $version
} else {
    set StrlBox(VERSION) "<bad version>"
}

# == main program ===

wm withdraw .

if {![info exist env(XSTRL_LIB)]} {
    set env(XSTRL_LIB) [pwd]
}

source $env(XSTRL_LIB)/globals.tcl
source $env(XSTRL_LIB)/images.tcl
source $env(XSTRL_LIB)/builders.tcl
source $env(XSTRL_LIB)/balloons.tcl
source $env(XSTRL_LIB)/browser.tcl
source $env(XSTRL_LIB)/options.tcl
source $env(XSTRL_LIB)/simulate.tcl
source $env(XSTRL_LIB)/processor.tcl
source $env(XSTRL_LIB)/command.tcl
source $env(XSTRL_LIB)/exec.tcl
source $env(XSTRL_LIB)/help.tcl
source $env(XSTRL_LIB)/viewer.tcl
source $env(XSTRL_LIB)/save.tcl

option add *help.helpfile [file join $env(XSTRL_LIB) xstrl.hlp]

# global rc file and user rc file
foreach  rcfile [list [file join $env(XSTRL_LIB) xstrlrc] $StrlBox(rc_file)] {
    if {[file exist $rcfile] && [catch {source $rcfile} error]} {
	tk_dialog .err Error \
		"$rcfile load failed:\n$errorInfo" info 0 Ok
    }
}



proc SB_PreselectFiles {list} {
    # list is a list of file (from the command line)
    # try to find absolute file name for each element of list
    # and if file ok (exist, extension), add as pre-selected.
    global StrlBox
    foreach file $list {
	if { $file == "" } {
	    continue
	}
	if {[lsearch $StrlBox(formats) \
		[string range [file extension $file] 1 end]] == -1} {
	    # bad extension
	    tk_dialog .err Error  \
		    "*** bad file extension: \"$file\"" \
		    info 0 Ok
	    continue
	}
	if {![file exists $file] || ![file exists [file dirname $file]]} {
	    # no such file
	    tk_dialog .err Error  \
		    "*** no such file or directory: \"$file\"" \
		    info 0 Ok
	    continue
	}
	if {[file pathtype $file] == "relative"} {
	    # try to canonicalize file name.
	    set path [file split $StrlBox(dirs:cwd)]
	    set split [file split $file]
	    set base [lindex $split end]
	    foreach dir [lreplace $split end end] {
		switch $dir {
		    . {
			continue
		    }
		    .. {
			set path [lreplace $path end end]
		    }
		    default {
			lappend path $dir
		    }
		}
	    }
	    set new_file [eval file join $path $base]
	    if {![file exists $new_file]} {
	    tk_dialog .err Error  \
		    "*** file name canonicalization failed:\n$file -> $new_file" \
		    info 0 Ok
		continue
	    } 
	    set file $new_file
	}
	# add as selected.
	lappend StrlBox(files:selected) $file
    }
}


proc SB_Center {w root} {
    wm withdraw $w
    update idletasks
    set x [expr [winfo rootx $root] + \
	    ([winfo width $root] - [winfo reqwidth $w])/2]
    set y [expr [winfo rooty $root] + \
	    ([winfo height $root] - [winfo reqheight $w])/2]
    wm geometry $w +${x}+${y}
    wm deiconify $w
}

proc SB_SetAppCurrentDirectory {} {
    global StrlBox
    set StrlBox(dirs:cwd) \
	[SB_CurrentDirectory $StrlBox(browser:main)]
    cd $StrlBox(dirs:cwd)
    SB_BuildCommand
}

proc SB_FileToAppDir {file} {
    global StrlBox
    if {$file == ""} {
	return ""
    }
    set dir [file dirname $file]

    set base [file tail $file]
    if {! [regsub "^$StrlBox(dirs:cwd)" $dir {.} path]} {
	set path $dir
    }
    return [file join $path $base]
}

#----------------------------------
# Building the application toplevel
#----------------------------------
catch {destroy $StrlBox(top)}
toplevel $StrlBox(top)
wm title $StrlBox(top) "Esterel Commando Box"
wm iconname $StrlBox(top) XEsterel
wm protocol $StrlBox(top) WM_DELETE_WINDOW {
    wm protocol $StrlBox(top) WM_DELETE_WINDOW {}
    exit 0
}
#----------------------
# building the menu bar
#----------------------
set menubar $StrlBox(top).menubar
pack [frame $menubar -bd 2 -relief raise] -fill x

pack [menubutton $menubar.file \
	-text File -menu $menubar.file.menu] -side left
menu $menubar.file.menu
$menubar.file.menu add command \
	-label {Run...} \
	-command SB_RunCommand
cb_balloonHelp "$menubar.file.menu [$menubar.file.menu index end]" \
	"Execute command according to execution mode (see Options menu)." \
	100

$menubar.file.menu add command \
	-label {Simulate & Tools} \
	-command SB_Simulate
cb_balloonHelp "$menubar.file.menu [$menubar.file.menu index end]" \
	"Access to simulation and tools panel." \
	100

$menubar.file.menu add command \
	-label "View" \
	-command "SB_FileViewer \[SB_SelectedFiles $StrlBox(top).file.lists\]"
cb_balloonHelp "$menubar.file.menu [$menubar.file.menu index end]" \
	"View selected files." \
	100


cb_balloonHelp "$menubar.file.menu [$menubar.file.menu index end]" \
	"Change the application current directory to the currently browsed \
directory. Usefull to get a command with relative path files." \
	100

# Command Saving
$menubar.file.menu add command \
	-label "Save" \
	-command SB_SaveLastCommand
cb_balloonHelp "$menubar.file.menu [$menubar.file.menu index end]" \
	"Save current command." \
	100
menu $menubar.file.menu.save
$menubar.file.menu.save add command \
	-label "Command Script" \
	-command SB_SaveCommand
cb_balloonHelp "$menubar.file.menu.save [$menubar.file.menu.save index end]" \
	"Write current command into a command file." \
	100
$menubar.file.menu.save add command \
	-label "Makefile" \
	-command SB_WriteMakefile
cb_balloonHelp "$menubar.file.menu.save [$menubar.file.menu.save index end]" \
	"Save current command into a Makefile" \
	100
$menubar.file.menu add cascade \
    -label "Save as..." \
    -menu $menubar.file.menu.save 

# Configuration saving
menu $menubar.file.menu.configuration
$menubar.file.menu.configuration add command \
	-label "Save..." \
	-command SB_SaveConfiguration
cb_balloonHelp "$menubar.file.menu.configuration 0" \
	"Write current xesterel configuration into a file." \
	100

$menubar.file.menu.configuration add command \
	-label "Load..." \
	-command SB_LoadConfiguration
cb_balloonHelp "$menubar.file.menu.configuration 1" \
	"Load a configuration from a file." \
	100
$menubar.file.menu add cascade \
	-label "Configuration..." \
	-menu $menubar.file.menu.configuration


$menubar.file.menu add command \
	-label Quit \
	-command {exit 0}

pack [menubutton $menubar.edit \
	-text Edit -menu $menubar.edit.menu] -side left
menu $menubar.edit.menu 
$menubar.edit.menu add command \
	-label "Copy" \
	-accelerator "C-c" \
	-command {$StrlBox(command:entry) selection range 0 end}
cb_balloonHelp "$menubar.edit.menu 0" \
	"Copy command into current selection." \
	100

pack [menubutton $menubar.options \
	-text Options -menu $menubar.options.menu] -side left
menu $menubar.options.menu
$menubar.options.menu add command \
	-label "General Preferences..." \
	-command SB_Preferences
cb_balloonHelp "$menubar.options.menu 0" \
	"Set general preferences, such as compiler." \
	100

$menubar.options.menu add command \
	-label "Save Options" \
	-command SB_SaveOptions
cb_balloonHelp "$menubar.options.menu 1" \
	"Save options and current main option \
settings into \$HOME/.xstrlrc." \
	100


# On line help
global cb_tools

pack [menubutton $StrlBox(top).menubar.help \
	-text Help -menu $StrlBox(top).menubar.help.menu] -side right
menu $StrlBox(top).menubar.help.menu
$StrlBox(top).menubar.help.menu add command \
	-label "On Xesterel" \
	-command HelpWindow
$StrlBox(top).menubar.help.menu add command \
	-label About \
	-command [format {
    if {[winfo exist .about]} {
	return
    }
    toplevel .about
    wm transient .about $StrlBox(top)
    wm group .about $StrlBox(top)
    pack [message .about.msg -text {
Esterel commando box, version:%s.
	
A graphical front end to the esterel command.
	
Esterel Team (esterel-request@sophia.inria.fr)
} ]
    bind .about <1> {destroy .about}
    SB_Center .about $StrlBox(top)
} $StrlBox(VERSION)]

$StrlBox(top).menubar.help.menu add checkbutton \
	-label "Balloons" \
	-variable cb_tools(balloon_help)

set cb_tools(balloon_help) $StrlBox(help:balloon)

bind $StrlBox(top) <Control-KeyPress-c> {
    $StrlBox(command:entry) selection range 0 end
}



#------------------
# the final command
#------------------
set StrlBox(command:entry) $StrlBox(top).command_line
entry $StrlBox(command:entry) \
	-textvariable StrlBox(command:line) \
 	-relief sunken \
	-state $StrlBox(command:edition)
scrollbar $StrlBox(top).command_scroll \
	-orient horizontal \
	-command "$StrlBox(command:entry) xview"
$StrlBox(command:entry) configure \
	-xscrollcommand "$StrlBox(top).command_scroll set"
pack $StrlBox(top).command_scroll -side bottom -fill x
pack $StrlBox(command:entry) -side bottom -fill x -padx 4 -pady 4
cb_balloonHelp $StrlBox(command:entry) \
"Final command. \
 \
This entry contains the final command to execute. \
Once the command is complete, one can use it by selection \
(Edit menu, or triple-click)."  
bind $StrlBox(command:entry) <Key-Return> {SB_RunCommand; break}

#--------------------
# file related inputs
#-------------------- 
set file [frame $StrlBox(top).file] 
pack $file -side left -padx 4

# application current directory.
set app_path [frame $StrlBox(top).file.app_path] 
pack [label $app_path.l -text "Working Dir:"] -side left
pack [entry $app_path.e -width 30 \
	  -textvariable StrlBox(dirs:cwd)] \
    -side left
pack [button $app_path.b \
	  -text "Browse..." \
	  -highlightthickness 0 \
	  -padx 0 -pady 0] -side left
$app_path.b configure -command [format {
    set dir [SB_SingleDirBrowser %1$s %2$s]
    if {$dir != ""} {
	set StrlBox(dirs:cwd) $dir
	cd $dir
    } 
    SB_EsterelOptions
    SB_BuildCommand } .browse $StrlBox(top)]

$app_path.e configure -state disabled -cursor {}
bind $app_path.e <1> {focus %W; break}
bind $app_path.e <B1-Motion> {break}
bind $app_path.e <Control-A> {%W xview 0}
bind $app_path.e <Control-E> {%W xview end}
$app_path.e xview end

cb_balloonHelp $app_path.e "All built pathes will \
be relative to this value."

# Browser
set StrlBox(browser:main) $file.lists

# Possible files on command line
set initialDir $StrlBox(dirs:cwd)
if {[llength $argv]} {
    SB_PreselectFiles $argv
    set input [lindex $StrlBox(files:selected) 0]
    if {  $input != "" } {
	set dirname [file dirname $input]
	if {$dirname != "."} {
	    set initialDir $dirname
	}
    }
}

SB_DirFileBrowser \
	$file.lists \
	SB_UseFiles \
	SB_IsFileSelected \
	$StrlBox(files:extensions) \
        $initialDir


#-----------------
# -B and -D option
#-----------------
frame $file.output

SB_BuildEntryOption 0 $file.output \
	esterel \
	main "Main module" \
	"Defines the main module of the program." \
	-main \
	"SB_EsterelOptions; SB_BuildCommand"

SB_BuildEntryOption 1 $file.output \
	esterel \
	basename Basename \
	"Result basename." \
	-B \
	"SB_EsterelOptions; SB_BuildCommand"

SB_BuildBrowseEntryOption 2 $file.output \
	esterel \
	dirname "Target Dir." \
	"Directory where to put results." \
	-D \
    {SB_EsterelOptions; SB_BuildCommand} \
        dir



# Final file packing
pack $file.app_path -anchor w -fill x
pack [frame $file.sep1 -bd 2 -relief sunken -height 2] -fill x -pady 3
pack [label $file.lb1 -text "Source Files:"] -anchor w
pack $file.lists -expand 1 -fill both

pack [frame $file.sep2 -bd 2 -relief sunken -height 2] -fill x -pady 3
pack $file.output -side bottom -anchor w
pack $file -fill both -padx 2 -expand 1



#--------------
# other options
#--------------

set opt [frame $StrlBox(top).options]
pack $opt -side right -anchor  n -fill y -padx 4
frame $StrlBox(top).separator -bd 2 -width 2 -relief sunken
pack $StrlBox(top).separator -side right -pady 4 -fill y

#-----------------
# compilation type
#-----------------
set grid_row -1
SB_BuildOptionMenu [incr grid_row] $opt \
	esterel \
	"compilation" "Compilation Type" \
	"Select the kind of compilation. \
\"Check Only\" tests if interpreted code will respect the \
constuctive semantics, but do not generate code." \
        $StrlBox(compilation:list) \
	"SB_EsterelOptions; SB_BuildCommand"


#-----------------
# language type
#-----------------
SB_BuildOptionMenu [incr grid_row] $opt \
	esterel \
	"language" "Language" \
	"Select the target language." \
	$StrlBox(language:list) \
	"SB_EsterelOptions; SB_BuildCommand"

SB_BuildCheckOption [incr grid_row] $opt \
	esterel simul \
	"Code for Simulation" "Generate instrumented code for simulation." \
	-simul \
	"SB_EsterelOptions; SB_BuildCommand" \
	1

#--------------
# Check options
#-------------

SB_BuildCheckOption [incr grid_row] $opt \
	esterel \
	causal "Causality Analysis" \
	"Performs constructive causality analysis \
when set. This may be expensive. Use this option \
when sorted equations cannot be generated \
because of a causality cycle error." \
	-causal \
	"SB_EsterelOptions; SB_BuildCommand"

SB_BuildCheckOption [incr grid_row] $opt esterel single \
	"Single Signals Check" \
	"When set, check if valued signals without \
a combination function are emitted one once \
per instant. Implies constructive causality analysis." \
	-single \
	"SB_EsterelOptions; SB_BuildCommand"

SB_BuildCheckOption [incr grid_row] $opt esterel cycles \
	"Static Cycles Check" \
        "When set, check if there are no static cycles. \
Do not generate code." \
	-cycles \
	"SB_EsterelOptions; SB_BuildCommand"

grid [frame $opt.hsep1 -bd 2 -relief sunken -height 2]\
	-row [incr grid_row] -sticky we -columnspan 2

SB_BuildCheckOption [incr grid_row] $opt \
	esterel silent \
	"Don't Generate Code" "Work silently, no final code generated." \
	-s \
	"SB_EsterelOptions; SB_BuildCommand"

SB_BuildCheckOption [incr grid_row] $opt \
	esterel verbose \
	"Verbose Mode" "Verbose mode" \
	-v \
	"SB_EsterelOptions; SB_BuildCommand"

SB_BuildOptionMenu [incr grid_row] $opt \
	esterel "warnings" \
	"Warnings" "Set level of warnings." \
	$StrlBox(warnings:list) \
	"SB_EsterelOptions; SB_BuildCommand"


button $opt.more -text "Advanced Options..." -command SB_ProcessorOptions
cb_balloonHelp $opt.more "Access to processors' options."

grid $opt.more -row [incr grid_row] -column 1 -pady 10
grid [frame $opt.hsep2 -bd 2 -relief sunken -height 2]\
	-row [incr grid_row] -sticky we -columnspan 2
button $opt.run -text "Run..." -command {
    SB_RunCommand
}

cb_balloonHelp $opt.run  \
	"Execute command according to execution mode (see Options menu)." 
grid $opt.run -row [incr grid_row] -column 0 -pady 10
button $opt.sim -text "Simulate & Tools" -command SB_Simulate
cb_balloonHelp $opt.sim "Access to simulation and tools panel."
grid $opt.sim -row $grid_row -column 1 -pady 10

SB_EsterelOptions
SB_BuildCommand


# Debug
set menubar $StrlBox(top).menubar
bind $menubar <Triple-ButtonPress-1> {
    if {[namespace children :: ::MiniDebug] != "" } {
	MiniDebug::View
    } else {
	if {[file exist minidbg.tcl]} {
	    catch {
		source minidbg.tcl
		MiniDebug::View
	    }
	}
    }
}

## Guru's corner
## Local Variables: ##
## eval:(local-set-key [f12] 'tcl-restart-with-whole-file)
## eval:(local-set-key [find] 'tcl-get-error-info) 
## End: ##
