# A simple file viewer
#---------------------
global StrlBox Viewer

# default builtin viewer
set StrlBox(viewer) "builtin %s"
set Viewer(viewer:ctr) 0
set Viewer(views) ""

proc SB_FileViewer {files} {
    foreach file $files {
	SB_ViewFile $file
    }
}

proc SB_ViewFile {file} {
    global StrlBox Viewer

    set command [string trim $StrlBox(viewer)]
    if { ! ( $command == "" || [regexp "builtin +%s" $command] ) } {
	# extern command.
	append command " &"
	eval "exec [format $command $file]"
	return
    } 

    foreach {index viewed} $Viewer(views) {
	if {$viewed == $file} {
	    if {[catch "raise .view$index"]} {
		# view destroyed
		SB_RemoveView $index
		break
	    }
	    return
	}
    }

    # build new view
    set top .view[incr Viewer(viewer:ctr)]
    
    toplevel $top
    wm withdraw $top

    set menubar [frame $top.menubar -relief raise -bd 2]
    pack $menubar -fill x 
    set text [text $top.fileview]
    if {[catch {SB_LoadFile $text $file}]} {
	destroy $top
	return
    }
    set vscroll [scrollbar $top.scroll \
	    -orient vertical -command "$text yview"]
    $text configure -yscrollcommand "$vscroll set"
    pack $text -side left -expand 1 -fill both

    pack $vscroll -side left -fill y
    
    set menu $menubar.file.menu
    pack [menubutton $menubar.file -menu $menu -text File] -side left
    menu $menu
    $menu add command \
	    -label Reload \
	    -command "SB_LoadFile $text $file"

    $menu add command \
	    -label Close \
	    -command "catch {SB_RemoveView $Viewer(viewer:ctr)}"

    # line column
    pack [label $menubar.lc] -side right
    bind $text <Motion> "
    set coord \[split \[$text index @%x,%y\] .\]
    $menubar.lc configure -text \[format {line:%%3d col:%%3d} \
	  \[lindex \$coord 0\] \
	  \[expr \[lindex \$coord 1\] + 1\] \]
    "

    wm deiconify $top
    wm title $top "View: $file"
    wm group $top $StrlBox(top)

    lappend Viewer(views) $Viewer(viewer:ctr) $file
}

proc SB_LoadFile {viewer file} {
    if {[catch {open $file r} fd]} {
	return -code error
    }
    $viewer configure -state normal
    $viewer delete 1.0 end
    # filling
    while {[gets $fd line] != -1} {
	$viewer insert end "$line\n"
    }
    close $fd
    $viewer configure -state disabled
}

proc SB_RemoveView {view} {
    global Viewer

    if {[winfo exist .view$view]} {
	destroy .view$view
    }
    set list ""
    foreach {index viewed} $Viewer(views) {
	if {$index == $view} {
	    continue
	}
	lappend list $index $viewed
    }
    set Viewer(views) $list
}
