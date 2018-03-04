# $Id: help.tcl,v 1.5 1999/02/03 18:30:14 fornari Exp $

#
# from Jay Sekora js@priceton.edu

# -------------------------------------
global HelpPriv

option add *help.roman "-adobe-helvetica-medium-r-normal--*-120-*"
option add *help.italic "-adobe-helvetica-medium-o-normal--*-120-*"
option add *help.bold "-adobe-helvetica-bold-r-normal--*-120-*"
option add *help.bolditalic "-adobe-helvetica-bold-o-normal--*-120-*"
option add *help.typewriter "-adobe-courier-medium-r-normal--*-120-*"
option add *help.headline1 "-adobe-helvetica-bold-r-normal--*-140-*"
option add *help.headline2 "-adobe-helvetica-bold-r-normal--*-120-*"
option add *help.linkfg "red"
option add *help.itemlabel "*"
option add *help*Text.background LemonChiffon
option add *help.helpfile "help.tkhelp"

proc H_SetDefaults {} {
    global HelpPriv
    foreach option {\
	    roman \
	    italic \
	    bold \
	    bolditalic \
	    typewriter \
	    headline1 \
	    headline2 \
	    linkfg \
	    itemlabel \
	    helpfile
	} {
	set HelpPriv(res:$option) \
		[option get $HelpPriv(W:help) $option $option]
    }
}

proc H_SetTags {text} {
    global HelpPriv
    foreach tag {\
	    roman \
	    italic \
	    bold \
	    bolditalic \
	    typewriter \
	    headline1 \
	    headline2 } {
	$text tag configure $tag -font $HelpPriv(res:$tag)
    }
    $text tag configure headline1 -underline 1
    $text tag configure headline2 -underline 1
}




#--------------------------------------------------------------------
# not modify from here (a priori :-)
set HelpPriv(bitmap_help) questhead

#--------------------------------------
#
# Widget hierarchy
#
#
global HelpPriv
# help hierarchy
set {HelpPriv(W:help)}                {.help}
set {HelpPriv(W:bar)}                 {.help.menu}
set {HelpPriv(W:button:next)}         {.help.menu.next}
set {HelpPriv(W:button:prev)}         {.help.menu.prev}
set {HelpPriv(W:section:button)}      {.help.menu.sections}
set {HelpPriv(W:sections)}            {.help.menu.sections.menu}
set {HelpPriv(W:subsection:button)}   {.help.menu.subsections}
set {HelpPriv(W:subsections)}         {.help.menu.subsections.menu}
set {HelpPriv(W:helpbutton)}          {.help.menu.help}
set {HelpPriv(W:helpmenu)}            {.help.menu.help.menu}
set {HelpPriv(W:done)}                {.help.done}
set {HelpPriv(W:text)}                {.help.text}
set {HelpPriv(W:scroll)}              {.help.scrollbar}
set {HelpPriv(W:bottom)}              {.help.bottomline}
set {HelpPriv(W:top)}                 {.help.topline}
set {HelpPriv(W:vline)}               {.help.vline}

# alert hierarchy
set {HelpPriv(alert)}          {.alert}


######################################################################
# various procs used to display text
######################################################################

# insertWithTags - append to a text widget in a particular style
# (lifted from mkStyles.tcl demo)
#
# The procedure below inserts text into a given text widget and
# applies one or more tags to that text.  The arguments are:
#
# w		Window in which to insert
# text		Text to insert (it's inserted at the "insert" mark)
# args		One or more tags to apply to text.  If this is empty
#		then all tags are removed from the text.




proc H_insertWithTags {w text args} {
    set start [$w index insert]
    $w insert insert $text
    foreach tag [$w tag names $start] {
	$w tag remove $tag $start insert
    }
    foreach i $args {
	$w tag add $i $start insert
    }
}

# rm - insert at end of HelpPriv(W:text) in a plain font


proc rm {text} {
  global HelpPriv
  H_insertWithTags $HelpPriv(W:text) $text roman
}

# it - insert at end of HelpPriv(W:text) in an italic font


proc it {text} {
  global HelpPriv
  H_insertWithTags $HelpPriv(W:text) $text italic
}

# bf - insert at end of HelpPriv(W:text) in a bold font


proc bf {text} {
  global HelpPriv
  H_insertWithTags $HelpPriv(W:text) $text bold
}

# bi - insert at end of HelpPriv(W:text) in a bold italic font

proc bi {text} {
  global HelpPriv
  H_insertWithTags $HelpPriv(W:text) $text bolditalic
}

# tt - insert at end of HelpPriv(W:text) in a typewriter-text font


proc tt {text} {
  global HelpPriv
  H_insertWithTags $HelpPriv(W:text) $text typewriter
}

# hl - insert at end of HelpPriv(W:text) in a big headline font


proc hl {text {level 1}} {
  global HelpPriv
  H_insertWithTags $HelpPriv(W:text) $text headline$level
}

# section - section title (stick in menu)


proc section {title body} {
    global HelpPriv
    global HelpPriv

    $HelpPriv(W:sections) add command \
        -label $title \
        -command "H_SectionCmd $HelpPriv(section:ctr) {$title} {$body}"
    incr HelpPriv(section:ctr) 
}

proc H_SectionCmd {ctr title body} {
    global HelpPriv

    set HelpPriv(subsection:ctr) 0
    $HelpPriv(W:text) configure -state normal
    $HelpPriv(W:subsection:button) configure -state disabled
    $HelpPriv(W:subsections) delete 0 last
    $HelpPriv(W:text) delete 1.0 end
    H_RemoveTags
    hl $title
    cr
    par
    eval $body
    $HelpPriv(W:text) configure -state disabled
    if {$HelpPriv(subsection:ctr)} {
	$HelpPriv(W:subsection:button) configure -state normal
    }

    # section stack management
    if {$HelpPriv(stack:selection) == 0} {
	H_SectionStackPush $ctr
    }
    H_StackUpdateButtons
}

proc subsection {title body} {
    global HelpPriv
    set index [$HelpPriv(W:text) index insert]
    $HelpPriv(W:subsections) add command \
        -label $title \
        -command "$HelpPriv(W:text) yview $index"
    cr
    cr
    incr HelpPriv(subsection:ctr)
    hl $title 2
    cr
    par 
    eval $body
}

######################################################################

# par - start a new paragraph
# par : insert a white space
# par text
# insert text in roman
# par style text
# insert text with style style

proc par {args} {
    global HelpPriv
    rm "\n"
    set start [$HelpPriv(W:text) index insert]
    switch [llength $args] {
	0 {
	    set cmd rm
	    set text " "
	}
	1 {
	    set cmd rm
	    set text [lindex $args 0]
	}
	2 {
	    set cmd [lindex $args 0]
	    set text [lindex $args 1]
	}
    }
    $cmd "$text"
    $HelpPriv(W:text) tag add par $start \
	    [$HelpPriv(W:text) index insert]
    $HelpPriv(W:text) tag configure par -lmargin1 10
}

# cr - insert a line break at end of HelpPriv(W:text)


proc cr {} {
  global HelpPriv
  rm "\n"
}

# tab - insert a tab at end of HelpPriv(W:text)

proc tab {} {
  global HelpPriv
  rm "\t"
}
set HelpPriv(tab:level) 0
set HelpPriv(tab:tag) 0
proc itemBody {text} {
    global HelpPriv
    incr HelpPriv(tab:level) 20
    cr
    set start [$HelpPriv(W:text) index insert]
    eval $text
    incr  HelpPriv(tab:tag)
    $HelpPriv(W:text) tag add tab$HelpPriv(tab:tag) \
	    $start [$HelpPriv(W:text) index insert]
    $HelpPriv(W:text) tag configure tab$HelpPriv(tab:tag) \
	    -lmargin1 $HelpPriv(tab:level) \
	    -lmargin2 [expr $HelpPriv(tab:level) + 20]
    
    incr HelpPriv(tab:level) -20

    $HelpPriv(W:text) tag add itemskip3 \
	    "insert -1 char linestart" "insert -1 char"
    $HelpPriv(W:text) tag configure itemskip3 -spacing3 4
}

# description - description LaTeX-like environment
set HelpPriv(item:type:stack) ""
set HelpPriv(item:ctr:stack) ""
proc description {text} {
    global HelpPriv
    set HelpPriv(item:type) description
    set HelpPriv(item:type:stack) "$HelpPriv(item:type) $HelpPriv(item:type:stack)"
    itemBody $text
    set HelpPriv(item:type:stack) [lrange $HelpPriv(item:type:stack) 1 end]
    set HelpPriv(item:type) [lindex $HelpPriv(item:type:stack) 0]
}

# enumerate - enumerate LaTeX-like environment
proc enumerate {text} {
    global HelpPriv
    set HelpPriv(item:type) enumerate
    set HelpPriv(item:type:stack) "$HelpPriv(item:type) $HelpPriv(item:type:stack)"
    set HelpPriv(item:ctr) 1
    set HelpPriv(item:ctr:stack) "$HelpPriv(item:ctr) $HelpPriv(item:ctr:stack)"
    itemBody $text
    set HelpPriv(item:type:stack) [lrange $HelpPriv(item:type:stack) 1 end]
    set HelpPriv(item:type) [lindex $HelpPriv(item:type:stack) 0]
    set HelpPriv(item:ctr:stack) [lrange $HelpPriv(item:ctr:stack) 1 end]
    set HelpPriv(item:ctr) [lindex $HelpPriv(item:ctr:stack) 0]
}

# itemize - itemize LaTeX-like environment
proc itemize {text} {
    global HelpPriv
    set HelpPriv(item:type) itemize
    set HelpPriv(item:type:stack) "$HelpPriv(item:type) $HelpPriv(item:type:stack)"
    itemBody $text
    set HelpPriv(item:type:stack) [lrange $HelpPriv(item:type:stack) 1 end]
    set HelpPriv(item:type) [lindex $HelpPriv(item:type:stack) 0]
}

# item for previous enviroment
proc item {args} {
    global HelpPriv
    switch [llength $args] {
        1 {
            set item ""
            set text [lindex $args 0]
        }
        2 {
            set item [lindex $args 0]
            set text [lindex $args 1]
        }
        default {
            error "wrong #args"
        }
    } 
    set face roman
    switch $HelpPriv(item:type) {
        description {
            if {$item!=""} {
                set face bold
            }
        }
        enumerate {
            if {$item==""} {
                set item "$HelpPriv(item:ctr)-"
                incr HelpPriv(item:ctr)
            } 
        }
        itemize {
            if {$item==""} {
                set item $HelpPriv(res:itemlabel)
            }
        }
    }
    set start [$HelpPriv(W:text) index insert]
    H_insertWithTags $HelpPriv(W:text) "$item " $face
    $HelpPriv(W:text) tag add itemskip1 $start [$HelpPriv(W:text) index insert]
    $HelpPriv(W:text) tag configure itemskip1 -spacing1 4
    eval $text
    cr
}
######################################################################
#
# mark - save the current line for later x-ref

proc mark {label} {
    global HelpPriv
    set HelpPriv(link:$label) [$HelpPriv(W:text) index insert]
}

######################################################################
#
# ref - set a tag for xref. 
# section is the place where to found the label label
# text is the activable text
proc ref {text section label} {
    global HelpPriv

    append tag XREF [incr HelpPriv(tag:ctr)]
    $HelpPriv(W:text) tag configure $tag \
	    -foreground $HelpPriv(res:linkfg) 
    
    $HelpPriv(W:text) tag bind $tag <Enter> {
	$HelpPriv(W:text) configure -cursor hand2
    }
    $HelpPriv(W:text) tag bind $tag <Leave> {
	$HelpPriv(W:text) configure -cursor top_left_arrow
    }
    
    $HelpPriv(W:text) tag bind $tag <1> \
    [format {
        set section {%s}
        if {[catch "%s invoke \"$section\"" err]} {
	    tk_dialog .err Error  \
		    "no section $section ($err)" \
		    info 0 Ok
        } else {
            set label {%s}
            if {[info exist HelpPriv(link:$label)]} {
                $HelpPriv(W:text) yview -pickplace $HelpPriv(link:$label)
            } else {
		tk_dialog .err Error  \
			"no label $label in section $section" \
			info 0 Ok
	    }
        }
    } $section $HelpPriv(W:sections) $label]

    # set the tag.
    H_insertWithTags $HelpPriv(W:text) $text $tag
}

######################################################################
#
# H_RemoveTags - removes all the tag from the text

proc H_RemoveTags {} {
    global HelpPriv
    # remove any tags
    set tags [$HelpPriv(W:text) tag names]
    set ind [lsearch $tags sel]
    foreach tag [lreplace $tags $ind $ind] {
        $HelpPriv(W:text) tag remove $tag 0.0 end
    }
    set HelpPriv(tag:ctr) 0

}

######################################################################
# cmd_quit - quit
#

proc H_Quit {} {
    global HelpPriv
    destroy $HelpPriv(W:help)
}




proc HelpWindow { {section ""} } {
    global HelpPriv HelpPriv

    if { [winfo exist $HelpPriv(W:help) ] } {
        if {$section!=""} {
            $HelpPriv(W:sections) invoke $section
        } 
	raise $HelpPriv(W:help)
        return
    }

    global HelpPriv

    ######################################################################
    # interface elements
    #
    set HelpPriv(section:ctr) 0
    toplevel $HelpPriv(W:help) -class Help

    H_SetDefaults

    frame $HelpPriv(W:bar)
    menubutton $HelpPriv(W:section:button)\
        -text {Sections} \
        -menu $HelpPriv(W:sections)
    menu $HelpPriv(W:sections) -tearoff 0

    menubutton $HelpPriv(W:subsection:button)\
        -text {Subsections} \
        -menu $HelpPriv(W:subsections) \
        -state disabled
    menu $HelpPriv(W:subsections) -tearoff 0

    menubutton $HelpPriv(W:helpbutton) \
        -text {Help} \
        -menu $HelpPriv(W:helpmenu)
    
    menu $HelpPriv(W:helpmenu) -tearoff 0

    $HelpPriv(W:helpmenu) \
         add command \
         -label {Help on Help} \
         -command H_HelpOnHelp
    $HelpPriv(W:helpmenu) \
         add command \
         -label {Quit} \
         -command "H_Quit"

    button $HelpPriv(W:button:prev) \
	    -highlightthickness 0 \
	    -padx 0 \
	    -text Previous \
	    -relief flat

    button $HelpPriv(W:button:next) \
	    -highlightthickness 0 \
	    -padx 0 \
	    -text Next \
	    -relief flat

    pack $HelpPriv(W:helpbutton) \
        $HelpPriv(W:section:button) \
        $HelpPriv(W:subsection:button) \
	$HelpPriv(W:button:prev) \
	$HelpPriv(W:button:next) \
        -in $HelpPriv(W:bar) \
        -side left

    button $HelpPriv(W:done) \
      -text Done \
      -command "H_Quit"
    
    text $HelpPriv(W:text) \
        -yscrollcommand "$HelpPriv(W:scroll) set" \
        -width 70 -height 18 \
        -setgrid true -wrap word \
	-cursor top_left_arrow

    H_SetTags  $HelpPriv(W:text)

    scrollbar $HelpPriv(W:scroll) \
       -relief flat \
       -command "$HelpPriv(W:text) yview"
    
    # horizontal separators between menu and text, and text and button
    frame $HelpPriv(W:top) \
        -height 2 -width 20 -borderwidth 1 -relief sunken
    frame $HelpPriv(W:bottom) \
        -height 2 -width 20 -borderwidth 1 -relief sunken

    
    # vertical separator between text and scrollbar
    frame $HelpPriv(W:vline) \
    -width 2 -height 20 -borderwidth 1 -relief sunken

    
    pack $HelpPriv(W:bar)   \
        $HelpPriv(W:top)    \
        -in $HelpPriv(W:help) \
        -side top -fill x 

    pack $HelpPriv(W:done)   \
        $HelpPriv(W:bottom) \
        -in $HelpPriv(W:help) \
        -side bottom -fill x
    pack $HelpPriv(W:scroll) \
        $HelpPriv(W:vline)   \
        -in $HelpPriv(W:help)  \
        -side right -fill y
    pack $HelpPriv(W:text)  \
        -in $HelpPriv(W:help) \
        -side right -expand 1 -fill y -padx 4
    
    
    ######################################################################
    # keyboard bindings
    #

    FocusBinding $HelpPriv(W:help)
    bind $HelpPriv(W:help) <Control-q> {H_Quit; break}
    bind $HelpPriv(W:help) <Control-h> {HelpWindow Help; break}
    # apply any changes to the text-appearance variables
    
    $HelpPriv(W:button:prev) configure \
	    -command H_PrevSection \
	    -state disabled
    $HelpPriv(W:button:next) configure \
	    -command H_NextSection \
	    -state disabled

    regsub -all -- {%W} [bind Text <Next>] "$HelpPriv(W:text)" bind
    bind $HelpPriv(W:help) <space> $bind

    regsub -all -- {%W} [bind Text <Prior>] "$HelpPriv(W:text)" bind
    bind $HelpPriv(W:help) <BackSpace> $bind

    H_FillText

    if {$section != ""} {
        $HelpPriv(W:sections) invoke $section
    } 
}
set HelpPriv(stack:index) -1
set HelpPriv(stack:items) {}
# section issue from stack order
set HelpPriv(stack:selection) 0

proc H_NextSection {} {
    global HelpPriv
    set HelpPriv(stack:selection) 1
    incr HelpPriv(stack:index)
    $HelpPriv(W:sections) invoke \
	    [lindex $HelpPriv(stack:items) $HelpPriv(stack:index)]
    set HelpPriv(stack:selection) 0
}

proc H_PrevSection {} {
    global HelpPriv
    set HelpPriv(stack:selection) 1
    incr HelpPriv(stack:index) -1
    $HelpPriv(W:sections) invoke \
	    [lindex $HelpPriv(stack:items) $HelpPriv(stack:index)]
    set HelpPriv(stack:selection) 0
}

proc H_SectionStackPush {section} {
    # called when a section is directly selected
    global HelpPriv

    incr HelpPriv(stack:index)
    if { [llength $HelpPriv(stack:items)] == $HelpPriv(stack:index) } {
	# adding new section at end of stack
	lappend HelpPriv(stack:items) $section
    } elseif {[lindex $HelpPriv(stack:items) $HelpPriv(stack:index)]\
	    != $section } {
	# next in stack is not the same as the want we are viewing.
	# replace from stack:index to end
	set HelpPriv(stack:items) \
		[lreplace $HelpPriv(stack:items) \
		$HelpPriv(stack:index) end $section]	
    }
    # else nothing.
}

proc H_StackUpdateButtons {} {
    global HelpPriv

    if {$HelpPriv(stack:index)>0} {
	$HelpPriv(W:button:prev) configure -state normal
    } else {
	$HelpPriv(W:button:prev) configure -state disabled
    }
    set nb_items [llength $HelpPriv(stack:items)]
    if { [incr nb_items -1] == $HelpPriv(stack:index) } {
	$HelpPriv(W:button:next) configure -state disabled
    } else {
	$HelpPriv(W:button:next) configure -state normal
    }
}

proc DestroyHelpWindow { } {
     global HelpPriv
     catch "destroy $HelpPriv(about)"
     destroy $HelpPriv(W:help)
}    



proc H_FillText { } {
    global HelpPriv
    global HelpPriv

    ######################################################################
    # search for help file
    # the contents of the help file will set up the Sections menu
    #
    set HelpPriv(section:ctr) 0
    $HelpPriv(W:sections) delete 0 last
    set filename $HelpPriv(res:helpfile)
    
    if {! [file exists $filename ] } then {
      $HelpPriv(W:section:button) configure \
          -state disabled
      hl "Unable to find file `$filename'."
      par
      rm "The requested help file was not found.  "
      rm "It may not have been installed at your site."
      tkwait window $HelpPriv(W:help)
      return
    } else {
        source $filename
    }
    set HelpPriv(section:ctr) 0
    wm title $HelpPriv(W:help)  "Help"
    wm iconbitmap $HelpPriv(W:help) $HelpPriv(bitmap_help)
    # display the first section of help:
    $HelpPriv(W:sections) invoke $HelpPriv(section:ctr)
    
}

proc H_HelpOnHelp {} {
    global HelpPriv
    $HelpPriv(W:text) configure -state normal
    $HelpPriv(W:text) delete 1.0 end
hl "Help On Help"
cr
par "The help is divided into sections and subsections. To go directly"
rm " to a topic use the "
bf "Sections"
rm " and "
bf "Subsections"
rm " menus. Note: if a section has no subsection, the subsection menu "
rm "is disabled. In a section there are several bindings:"
description {
item "<space>" {
rm "move one page down"
}
item "<Control-b>" {
rm "move one page up"
}
}
rm "There are hypertext-like links too. Some words (generally found as in "
rm "\"see "
bf "word"
rm "\" are pointers to other sections. When the mouse cursor moves over "
rm "them, they change of color. Click on them to directly jump to the "
rm "topic."
par
rm "When finished, click on the "
bf "Done"
rm " button, or select the "
bf "Quit"
rm " entry in the help menu."
$HelpPriv(W:text) configure -state disabled
}

if {[info proc CenterWindowOnScreen]==""} {
    proc CenterWindowOnScreen w {
	wm withdraw $w
	update idletasks
	set x [expr [winfo screenwidth $w]/2 - [winfo reqwidth $w]/2 \
		- [winfo vrootx [winfo parent $w]]]
	set y [expr [winfo screenheight $w]/2 - [winfo reqheight $w]/2 \
		- [winfo vrooty [winfo parent $w]]]
	wm geom $w +$x+$y
	wm deiconify $w
    }
}

#----------------------------------------------------------------
# FocusBinding
#
#    set focus for the window W whenever it contains the mouse pointer
# Return:
#    none
#
# Side effects:
#    set focus
#----------------------------------------------------------------
if {[info proc FocusBinding]==""} {
    proc FocusBinding w {
	bind $w  <FocusIn> {            
	    if {[string match "%d" "NotifyVirtual"]} {
		focus  %W
	    }
	}
    }
}

