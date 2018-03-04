# main routine for processor options
proc SB_ProcessorOptions {} {
    global StrlBox
    if {[winfo exist .processors]} {
        SB_Center .processors $StrlBox(top)
	wm deiconify .processors
	raise .processors
	return
    }

    toplevel .processors
    wm withdraw .processors
    wm title .processors "Options"
    wm group .processors $StrlBox(top)
    wm transient .processors $StrlBox(top)

    set width 0
    set height 0
    pack [frame .processors.cmd] -fill x -side bottom
    pack [frame .processors.options \
	    -relief raised -bd 2] \
	    -side right \
	    -fill both -expand 1 -ipadx 4 -ipady 4
    pack [frame .processors.list -relief raised -bd 2] -fill x
    set StrlBox(esterel:message) \
"Select a processor and choose specific options for it."

    set StrlBox(processor:message) $StrlBox(esterel:message)
    pack [frame .processors.finfo -width 150] -expand 1 -fill y
    pack [message .processors.finfo.info \
	    -width 150 \
	    -textvariable StrlBox(processor:message)] \
	    -expand 1
    pack [button .processors.cmd.ok \
	      -text OK \
	      -padx 10m \
	      -command {\
	SB_CheckProcessorOptions; \
	SB_CheckBackups; \
	SB_EsterelOptions 1; \
	SB_BuildCommand; \
	wm withdraw .processors} ] \
	    -expand 1 
    

    # special esterel case
    SB_BuildEsterelOption .processors.options

    # Handle processors
    set StrlBox(processor:list) ""
    set StrlBox(autoCheckCommand) "proc SB_CheckProcessorOptions {} \{\n"
    append StrlBox(autoCheckCommand) "   global StrlBox\n"
    append StrlBox(autoCheckCommand) "   set StrlBox(processor:options) \"\"\n"

    set StrlBox(autoBackupCommand) "proc SB_CheckBackups {} \{\n"
    append StrlBox(autoBackupCommand) "   global StrlBox\n"
    append StrlBox(autoBackupCommand) \
	    "   set StrlBox(processor:backups) \"\"\n"

    
    # other processors
    foreach spec $StrlBox(processor:description) {
	SB_BuildProcessorOptions $spec
    }

    # resize main frame
    .processors.options configure -width $width -height $height 

    # build processor menu
    SB_BuildOptionMenu 0 .processors.list \
	    processor selected \
	    "Processor" "Select processor for specific options." \
	    $processor_menu \
	    SB_ProcessorShow

    SB_Center .processors $StrlBox(top)
    
    # auto build processor options check command
    append StrlBox(autoCheckCommand) "\n\}\n"
    eval $StrlBox(autoCheckCommand)
    append StrlBox(autoBackupCommand) "\n\}\n"
    eval $StrlBox(autoBackupCommand)

    unset StrlBox(autoBackupCommand)
    unset StrlBox(autoCheckCommand)

    pack propagate .processors.finfo false
}


proc SB_BuildProcessorOption {\
	frame row processor optionType option label help specs} {
    switch -exact -- $optionType {
	check {
	    SB_BuildCheckOption $row \
		    $frame $processor $option $label $help \
		    $specs
	}
	entry {
	    SB_BuildEntryOption $row \
		    $frame $processor $option $label $help \
		    $specs
	}
	menu {
	    SB_BuildOptionMenu $row \
		    $frame $processor $option $label $help \
		    [lindex $specs 0]
	}
	cmenu {
	    SB_BuildCheckOptionMenu $row \
		    $frame $processor $option $label $help \
		    [lindex $specs 0] [lindex $specs 1]
	}
	default {
	    puts "unknown type $optionType"
	}
    }
}

proc SB_BuildProcessorOptions {processorSpec} {
    upvar width width
    upvar height height
    upvar processor_menu processor_menu

    global StrlBox

    append StrlBox(autoBackupCommand) "   set command \"\"\n"
    append StrlBox(autoCheckCommand) "   set command \"\"\n"

    lappend StrlBox(processor:list) \
	    [set processor [lindex $processorSpec 0]]
    set class [lindex $processorSpec 1]
    switch [lindex $class 0] {
	internal {
	    set backup $processor
	    set class internal
	    set language ""
	}
	generator {
	    set backup [lindex $class 1]
	    set language [lindex $class 2]
	    # specific options for target language, from specific class
	    set class generator
	}
    }

    set StrlBox($processor:message) [lindex $processorSpec 2]
    # processor menu label and value.
    lappend processor_menu $processor
    lappend processor_menu $processor

    set frame [frame .processors.options.$processor]
    set StrlBox($processor:frame) $frame
    # option building
    set row -1
    foreach spec [lrange $processorSpec 3 end] {
	SB_BuildProcessorOption $frame [incr row] \
		$processor [lindex $spec 0] [lindex $spec 1] \
		[lindex $spec 2] [lindex $spec 3] \
		[lrange $spec 4 end]
    }

    SB_BuildBackupOption [incr row] $frame $processor \
	    $backup $class $language

    SB_BuildWizardOption [incr row] $frame $processor

    # build final auto check command
    if {$class == "internal"} {
	set prog {
	    if {$command != ""} {
		append StrlBox(processor:options) " -%s:\"$command\""
	    }
	}
	append StrlBox(autoCheckCommand) [format $prog $processor]
    } else {
	# generator.
	append StrlBox(autoCheckCommand) \
		[format \
		"set StrlBox(language:%s:%s:options) \"\$command\"\n" \
		$language $backup]
    }
    SB_PlaceOptionFrame $frame
}

proc SB_BuildEsterelOption {parent} {
    global StrlBox
    upvar width width height height
    upvar processor_menu processor_menu
    set frame [frame $parent.esterel]
    set row -1
    SB_BuildCheckOptionMenu [incr row] $frame esterel \
	    keep "Keep Intermediate Code"  \
	    "Keep intermediate code. Several code may be kept." \
	    -K \
	    {ic ic lc lc sc sc ssc ssc \
	    oc oc All all} \
	    SB_EsterelKeepOptions 

    SB_BuildOptionMenu [incr row] $frame esterel \
	    stop "Stop At"  \
	    "Stop code production at intermediate format." \
	    {"target code" "-" "ic code" -ic "lc code" \
	     -lc "sc code" -sc "ssc code" -ssc \
	    "oc code" -oc}

    SB_BuildWizardOption [incr row] $frame esterel 

    SB_PlaceOptionFrame $frame
    set StrlBox(esterel:frame) $frame
    lappend processor_menu esterel esterel
}

proc SB_PlaceOptionFrame {frame} {
    upvar width width height height
    # so the display order of the frames will be correct.
    lower $frame

    update
    if {[winfo reqwidth $frame]>$width} {
	set width [winfo reqwidth $frame]
    }
    if {[winfo reqheight $frame]>$height} {
	set height [winfo reqheight $frame]
    }
    place $frame -x 0 -y 0 -relwidth 1.0 -relheight 1.0
    
}

proc SB_ProcessorShow {} {
    global StrlBox
    set processor $StrlBox(processor:menu:selected:value)
    raise $StrlBox($processor:frame)
    set StrlBox(processor:message) $StrlBox($processor:message)
}

proc SB_BuildBackupOption {row frame processor backup class language} {
    global StrlBox
    set autoCheckCommand $StrlBox(autoCheckCommand)
    set StrlBox(autoCheckCommand) ""
    SB_BuildBrowseEntryOption $row $frame $processor \
	    backup "Backup Executable" "alternative processor" -backup
    append StrlBox(autoBackupCommand) $StrlBox(autoCheckCommand)
    set prog {
	if {$command != ""} {
	    set backup $StrlBox(%1$s:centry:value:backup)
	    switch %3$s {
		internal {
		    append StrlBox(processor:backups) \
			    " -backup %1$s:$backup"	    
		}
		generator {
		    if {! [file isdirectory $backup]} {
			# remove language part for code generator
			# works for true files and links.
			# but not for link to directories (sop).
			regsub {%4$s$} $backup {} backup
		    }
		    append StrlBox(processor:backups) \
			    " -backup %2$s:$backup"
		}
	    }
	}
    }
    append StrlBox(autoBackupCommand) \
	    [format $prog $processor $backup $class $language]
    set StrlBox(autoCheckCommand) $autoCheckCommand
}

proc SB_BuildWizardOption {row frame processor} {
    global StrlBox
    # wizard corner.
    set autoCheckCommand $StrlBox(autoCheckCommand)
    SB_BuildEntryOption $row $frame $processor \
	    wizard "Wizard Options" "Use to pass magic incantations." \
	    -wizard
    # auto check command
    set prog {
	# check Entry Option
	if {$StrlBox(%1$s:centry:option:%2$s) != ""}  {
	    if {$StrlBox(%1$s:centry:value:%2$s) != ""}  {
		if {$command != ""} {
		    append command " "
		}
		append command $StrlBox(%1$s:centry:value:%2$s) 
	    } else {
		set StrlBox(%1$s:centry:option:%2$s) ""
	    }
	}
    }
    append autoCheckCommand [format $prog $processor wizard]
    set  StrlBox(autoCheckCommand) $autoCheckCommand

}
