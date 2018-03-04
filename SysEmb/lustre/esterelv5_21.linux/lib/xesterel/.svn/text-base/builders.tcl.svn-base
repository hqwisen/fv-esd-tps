#SB_BuildOptionMenu
#
#Builds a menu with a left-side label. The selected option
#is displayed in a sunken label, and a button with a down
#arrow is displayed in the sunken label on the right edge.
#This button gives access to the menu. Use gridding.
#
#Arguments
#   row: row number for gridding
#   grid: container
#   proc: processor
#   option: option name
#   label: menu label
#   help: text for balloons
#   spec: a list of {label value}
#         if value is "-" then it is the default option.
#         may be a global variable. Menu will be update.
#   doIt: optional command to call
#   editable: main field is editable (optional)

#Sets:
#   Option selected is in StrlBox($proc:menu:$option:label)
#   menu in StrlBox($proc:menu:$option)
#
#   set StrlBox(autoCheckCommand)
# Return:
#    the menu
proc SB_BuildOptionMenu {\
    row grid proc option label help spec {doIt ""} {editable false}} {
    global StrlBox
    set max_len  0
    grid rowconfigure $grid $row -pad 2
    grid [label $grid.label$row -text "$label:"] \
	    -row $row -column 0 \
	    -sticky w

    set frame [frame $grid.frame$row -bd 2 -relief sunken] 
    set button [menubutton $frame.button \
	    -image $StrlBox(image:down) -relief raised]

    if {$editable} {
    set entry [entry $frame.value \
		   -justify left \
		   -textvariable StrlBox($proc:menu:$option:label) ]
    } else {
	set entry [label $frame.value \
		       -textvariable StrlBox($proc:menu:$option:label) ]
    }

    set menu $button.optionList
    $button configure -menu $menu
    pack $entry -side left -fill x -expand 1
    pack $button -side right -fill y
    grid $frame -row $row -column 1 -sticky we
    # filling menu
    menu $menu
    set StrlBox($proc:menu:$option:cmd) $doIt

    if {[info exist $spec]} {
	$menu configure -postcommand \
	    "SB_FillOptionMenu $proc $option $menu \$$spec"
	# "dereferencing" spec
	set spec [eval "global $spec; set $spec"]
    } 

    SB_FillOptionMenu $proc $option $menu $spec

    # default
    for {set i 0} "\$i<[llength $spec]" {incr i} {
	set label [lindex $spec $i]
	set value [lindex $spec [incr i]]

	set len [string length $label]
	if {$len>$max_len} {
	    set max_len $len
	}
	set Option($label) $value
    }

    $entry configure -width $max_len

    # automatically set menu
    if { $StrlBox($proc:menu:$option:label) == ""} {
	set StrlBox($proc:menu:$option:label) [lindex $spec 0]
    } 
    
    set StrlBox($proc:menu:$option:value) \
	    $Option([$menu entrycget \
	       [$menu index $StrlBox($proc:menu:$option:label)] -label])
    cb_balloonHelp $button $help
    
    # auto build check command
    set prog {
	# Check menu
	if {$StrlBox(%1$s:menu:%2$s:value) != "-"} {
	    lappend command $StrlBox(%1$s:menu:%2$s:value)
	}
    }
    append StrlBox(autoCheckCommand) \
	    [format $prog $proc $option]
    set StrlBox($proc:menu:$option) $menu
    return $menu
}

proc SB_FillOptionMenu {proc option menu spec} {
    global StrlBox
    $menu delete 0 end
    for {set i 0} "\$i<[llength $spec]" {incr i} {
	set label [lindex $spec $i]
	set value [lindex $spec [incr i]]
	$menu add command \
		-label $label \
		-command "
	set StrlBox($proc:menu:$option:label) {$label}
	set StrlBox($proc:menu:$option:value) {$value}
        $StrlBox($proc:menu:$option:cmd)
	"
    }
}

#================================================================
# SB_BuildCheckOptionMenu
#
# Builds a menu with checkbuttons use gridding. Used for option
# with suboptions as -Rft
#
# Arguments:
#  row : row number. 
#  frame: container
#  proc: processor concerned
#  name: option name
#  label: menu label
#  help: text for balloons
#  option: option string 
#  spec: a list of {label value} where label is a comprehensive
#        text for the option and value its actual value
#        If value is '-', that means use option.
#  doIt: optional, command to call after selection
#
# Sets
#    a selected entry set  StrlBox($proc:cmenu:$name:<index>) 
#    the corresponding value, else to ""
# Menu in StrlBox($proc:cmenu:$name)
# Return
#    return the menu
proc SB_BuildCheckOptionMenu {\
	row frame proc name label help option spec {doIt ""}} {
    global StrlBox
    set StrlBox($proc:cmenu:$name:option) $option
    grid rowconfigure $frame $row -pad 2
    grid [label $frame.label$row \-text "$label:" ] \
	    -row $row -column 0 \
	    -sticky w
    set font [$frame.label$row cget -font]
    set frame [frame $frame.frame$row -bd 2 -relief sunken] 
    set button [menubutton $frame.button \
	    -image $StrlBox(image:down) -relief raised]

    set entry [entry $frame.value \
	    -highlightthickness 0 \
	    -relief flat \
	    -state disabled \
	    -font $font \
	    -cursor top_left_arrow \
	    -textvariable StrlBox($proc:cmenu:$name:label)]

    bind $frame.value  <1> {
	%W scan mark %x
	set tkPriv(x) %x
	set tkPriv(y) %y
	break
    }
    bind $frame.value  <B1-Motion> {
	if {abs(%x-$tkPriv(x)) > 2} {
	    set tkPriv(mouseMoved) 1
	}
	%W scan dragto %x
	break
    }

    set menu $button.optionList
    set StrlBox($proc:cmenu:$name) $menu
    $button configure -menu $menu
    pack $entry -side left -fill x -expand 1
    pack $button -side right -fill y
    grid $frame -row $row -column 1 -sticky we

    # filling menu
    menu $menu
    set index 0
    for {set i 0} "\$i<[llength $spec]" {incr i} {
	set label [lindex $spec $i]
	set value [lindex $spec [incr i]]
	$menu add checkbutton \
		-selectcolor red \
		-label $label \
		-offvalue "" \
		-onvalue $value \
		-variable StrlBox($proc:cmenu:$name:$index) 
	set StrlBox($proc:cmenu:$name:$index) ""
	if {$doIt != ""} {
	    $menu entryconfigure end \
		-command "$doIt $index; SB_CheckOptionMenuSet $proc $name"
	} else {
	    $menu entryconfigure end \
		-command "SB_CheckOptionMenuSet $proc $name"
	}
	# auto build check command
	set prog {
	    # Check check menu entry
	    if {$StrlBox(%1$s:cmenu:%2$s:%3$s) != ""} {
		set option StrlBox(%1$s:cmenu:%2$s:option)
		set sub $StrlBox(%1$s:cmenu:%2$s:%3$s)
		lappend command "$option$sub"
	    }
	}
	append StrlBox(autoCheckCommand) \
		[format $prog $proc $name $index]
	incr index
    }
    cb_balloonHelp $button $help
    SB_CheckOptionMenuSet $proc $name
    return $menu
}

proc SB_CheckOptionMenuSet {name option} {
    global StrlBox
    set label ""
    set last [expr [$StrlBox($name:cmenu:$option) index end] +1]
    for {set i 0} {$i<$last} {incr i} {
	if {$StrlBox($name:cmenu:$option:$i) != ""} {
	    lappend label \
		    [$StrlBox($name:cmenu:$option) entrycget $i -label]
	}
    }
    if {$label != ""} {
	set StrlBox($name:cmenu:$option:label) [join $label ","]
    } else {
	set StrlBox($name:cmenu:$option:label) nothing
    }
}

#=================================================================
# SB_BuildCheckOption
# 
# Build a check button. Use gridding
# Arguments:
#  row : row number. 
#  frame: container
#  proc: processor concerned
#  option: a name for the option
#  label: checkbutton label
#  help: text for balloons
#  value: option value ie -<string>
#  doIt: optional, command to call.
#  yesno:optional, builds a yes no radio button instead
#
# Sets:
#  StrlBox($proc:check:$option): "" if option unset, $value else
#
#  set check command StrlBox(autoCheckCommand)
proc SB_BuildCheckOption {\
	row frame proc option label help value {doIt ""} {yesno 0}} {
    global StrlBox

    grid rowconfigure $frame $row -pad 2
    set label [label $frame.label$row -text "$label:"]

    if {! $yesno } {
	# checkbutton
	set button [checkbutton $frame.check$row]
	if {[info exist StrlBox($proc:check:$option)] \
		&& $StrlBox($proc:check:$option) != ""} {
		set text on
	} else {
	    set text off
	}
	$button configure \
		-variable StrlBox($proc:check:$option) \
		-highlightthickness 0 \
		-text $text \
		-offvalue {} \
		-onvalue $value \
		-width 3 \
		-command "
	if {\$StrlBox($proc:check:$option) == \"\"} {
	    $button configure -text off
	} else {
	    $button configure -text on
	}
	$doIt
	"
	cb_balloonHelp $button $help
    } else {
	# yes no button
	set button [frame $frame.check$row]
	pack [radiobutton $button.yes -text Yes \
		-variable StrlBox($proc:check:$option) \
		-value $value] \
		-side left
	pack [radiobutton $button.no -text No \
		-variable StrlBox($proc:check:$option) \
		-value ""] \
		-side left
	if {$doIt != ""} {
	    $button.yes configure -command $doIt
	    $button.no configure -command $doIt
	}
	cb_balloonHelp $button.yes $help
    }

    # auto build check command
    set prog {
	# check Check Option
	if {$StrlBox(%1$s:check:%2$s) != ""} {
	    lappend command $StrlBox(%1$s:check:%2$s)
	}
    }
    append StrlBox(autoCheckCommand) \
	    [format $prog $proc $option]

    grid $label -row $row -sticky w -column 0
    grid $button -row $row -sticky e -column 1    
}


#===================================================================
#SB_BuildEntryOption
#
#Build an entry with a checkbutton. Use gridding
#Arguments :
#  row : row number. 
#  frame: container
#  proc: processor concerned
#  option: a name for the option
#  label: checkbutton label
#  help: text for balloons
#  value: option value ie -<string>
#  doIt: optional, command to call.

#Set:
#  StrlBox($proc:centry:option:$option): checkbutton value.
#                                        "" option not set
#                                        else has the value $value
#  StrlBox($proc:centry:value:$option): entry value
#  StrlBox($proc:centry:entry:$option): entry 
#
#  set check command StrlBox(autoCheckCommand)

proc SB_BuildEntryOption {\
	row frame proc option label help value {doIt ""}} {
    global StrlBox
    grid rowconfigure $frame $row -pad 2

    set button [checkbutton $frame.check$row]
    $button configure \
	    -variable StrlBox($proc:centry:option:$option) \
	    -text $label \
	    -offvalue {} \
	    -onvalue $value

    set cmd {
	if { $StrlBox(%1$s:centry:option:%2$s) != ""} {
	    focus $StrlBox(%1$s:centry:entry:%2$s)
	}
	%3$s
    }
    
    if {$doIt != ""} {
	$button configure -command [format $cmd $proc $option $doIt]
    } else {
	$button configure -command [format $cmd $proc $option ""]
    }

    set entry [entry $frame.entry$row \
	    -textvariable StrlBox($proc:centry:value:$option)]

    set StrlBox($proc:centry:value:$option) ""
    bind $entry <1> "set StrlBox($proc:centry:option:$option) $value"
#    bind $entry <Leave> \
	    {catch {focus [winfo toplevel [winfo containing %X %Y]]}; break}
    bind $entry <Return> "
    if { \$StrlBox($proc:centry:value:$option) != \"\" } {
	set StrlBox($proc:centry:option:$option) $value
    }
    catch {focus \[winfo toplevel \[focus\]\]}
    $doIt
    break
    "
    set StrlBox($proc:centry:entry:$option) $entry
    set StrlBox($proc:centry:value:$option) ""

    cb_balloonHelp $button \
	    "$help This option may be select or unselect manually."
    grid $button -row $row -column 0 -sticky w
    grid $entry -row $row -column 1 -sticky we

   # auto build check command
    set prog {
	# check Entry Option
	if {$StrlBox(%1$s:centry:option:%2$s) != ""}  {
	    if {$StrlBox(%1$s:centry:value:%2$s) != ""}  {
		lappend command \
			$StrlBox(%1$s:centry:option:%2$s) \
			$StrlBox(%1$s:centry:value:%2$s) 
	    } else {
		set StrlBox(%1$s:centry:option:%2$s) ""
	    }
	}
    }
    append StrlBox(autoCheckCommand) \
	    [format $prog $proc $option]
}

#=====================================================================
#Build an entry with a checkbutton. Use gridding
#Arguments :
#  row : row number. 
#  frame: container
#  proc: processor concerned
#  option: a name for the option
#  label: checkbutton label
#  help: text for balloons
#  value: option value ie -<string>
#  doIt: optional, command to call.
#  browser: file|dir : dir or file browser
#Set:
#  StrlBox($proc:centry:option:$option): checkbutton value.
#                                        "" option not set
#                                        else has the value $value
#  StrlBox($proc:centry:value:$option): entry value
#
#  set check command StrlBox(autoCheckCommand)
proc SB_BuildBrowseEntryOption {\
    row frame proc option label help value {doIt ""} {browser file}} {
    global StrlBox
    grid rowconfigure $frame $row -pad 2

    SB_BuildEntryOption $row $frame $proc \
		$option $label $help $value $doIt
    set cmd {
	set StrlBox(%1$s:centry:value:%2$s) [SB_SingleBrowser .browse %4$s]
	$StrlBox(%1$s:centry:entry:%2$s) xview end
	set StrlBox(%1$s:centry:option:%2$s) "%3$s"
    }
    set e $StrlBox($proc:centry:entry:$option)
    if {$browser == "dir" } {
	$e configure -state disabled -cursor {}
	bind $e <1> {focus %W; break}
	bind $e <B1-Motion> {break}
	bind $e <Control-A> {%W xview 0}
	bind $e <Control-E> {%W xview end}

    }
    button $frame.browse$row \
	    -text "Browse..." \
	    -padx 0 -pady 0 \
	    -highlightthickness 0 \
	-command "SB_BuildBrowseEntryOptionCommand $frame $proc $option $value {$doIt} $browser"

    bind $StrlBox($proc:centry:entry:$option) <Key-Tab> \
	    "SB_BrowseCompleteFilename %W StrlBox($proc:centry:value:$option)"

    grid $frame.browse$row -row $row -column 2 -padx 4
}

proc SB_BuildBrowseEntryOptionCommand {frame proc option value doIt browser} {
    global StrlBox
    if { $browser == "dir" } {
	set file [SB_SingleDirBrowser .browse [winfo toplevel $frame] ]
    } else {
	set file [SB_SingleBrowser .browse [winfo toplevel $frame] ]
    }

    if {$file != ""} {
	set StrlBox($proc:centry:value:$option) $file
	if {$browser == "dir" } {
	    set StrlBox($proc:centry:fullvalue:$option) $file
	}
	$StrlBox($proc:centry:entry:$option) xview end
	set StrlBox($proc:centry:option:$option) $value
	$StrlBox($proc:centry:entry:$option) xview end
    }
    eval $doIt
}

proc SB_BrowseCompleteFilename {widget var} {
    upvar #0 $var value

    set files [glob -nocomplain -- "${value}*"]

    switch [llength $files] {
	0 {
	    return -code break
	}
	1 {
	    if {[file isdirectory $files]} {
		# portable (?) hack to append /
		set files [file join $files "x"]
		regsub {x$} $files {} value
	    }
	}
	default  {
	    set first [lindex $files 0]
	    set max [string length $first]
	    for {set i [string length $value]} {$i<$max} {incr i} {
		set stop 0
		set char [string index $first $i]
		foreach file $files {
		    if {$char != [string index $file $i]} {
			set stop 1
			break
		    }
		}
		if {$stop} {
		    break
		}
	    }
	    set value [string range $first 0 [expr $i - 1]]
	}
    }
    $widget xview end
    $widget icursor end

    return -code break
}

# SB_FileAsker parent var
# widget: name of the asker. will be a frame, 
# label : text to print.
# var the name of a global variable to set
# Build a simple file asker
# return the build widget
proc SB_FileAsker {widget label var {extensions ""}} {
    # Compiler
    pack [frame $widget]
    pack [label $widget.l -text $label] -side left
    pack [entry $widget.e -width 30 \
	    -textvariable $var] \
	    -side left
    pack [button $widget.b \
	    -text "Browse..." \
	    -highlightthickness 0 \
	    -padx 0 -pady 0] -side left
    $widget.b configure -command [format {
	set file [SB_SingleBrowser .browse [winfo toplevel %1$s] "%2$s"]
	if {$file != ""} {
	    if {[regsub "^$StrlBox(dirs:cwd)" $file {.} new]} {
		set file $new
	    }
	    set %3$s $file
	    %1$s.e index end
	    %1$s.e icursor end
	}
    } $widget $extensions $var]
    bind $widget.e <Key-Tab> \
	    "SB_BrowseCompleteFilename %W $var"
    cb_balloonHelp $widget.e "Enter file name. <Tab> for completion."
    return $widget
}


proc SB_FileDialog {toplevel title label var {extensions ""} {defaultextension ""}} {
    global StrlBox
    set top $toplevel
    if {[winfo exist $top]} {
	raise $top
	return
    }
    toplevel $top
    wm title $top "$title"
    wm group $top $StrlBox(top)
    wm transient $top $StrlBox(top)

    SB_FileAsker $top.asker "$label:" $var $extensions

    label $top.title -text "Asker"
    label $top.bitmap -bitmap questhead
    frame $top.cmd
    button $top.cmd.ok -text OK \
	    -command "destroy $toplevel"
    button $top.cmd.ko -text Dismiss \
	-command "set $var {}; destroy $toplevel"
    pack $top.cmd.ok $top.cmd.ko -side left -expand 1
    pack $top.cmd -side bottom -fill x
    pack $top.asker -side bottom -after $top.cmd
    pack $top.bitmap -side left -after $top.asker -expand 1 -anchor e
    pack $top.title -side left -after $top.bitmap -expand 1 -anchor w
    SB_Center $top $StrlBox(top)
    tkwait window $top
    set file [string trim [set $var]]
    if { $file != "" && [file extension $file] == "" && $defaultextension != ""} {
	append $var ".$defaultextension"
	
    }
}
