# -----------------------------------------------------------------------------
# cb_balloonHelp: A simple balloon help for arbitrary widgets.
# Options: w: widget name, text: help text
#
global cb_balloonHelp
option add *balloon.Background LemonChiffon
#option add *balloon.Font fixed

set cb_balloonHelp(stay_on_screen) 1

set cb_balloonHelp(screen_width) [winfo screenwidth .]
set cb_balloonHelp(screen_height) [winfo screenheight .]

proc cb_balloonHelp {w text {delay 1000}} {
    global cb_balloonHelp

    set me ""
    if {[llength $w] > 1} {
	# 2nd element is the number of a menu entry
	set me [lindex $w 1]
	# 1st element the menu itself
	set w [lindex $w 0]
    }
    
    set cb_balloonHelp($w,cursor) [$w cget -cursor]
    set cb_balloonHelp($w,shown) 0

    if {$me == ""} {
	bind $w <Enter> "
	set cb_balloonHelp(id) \
		\[after $delay _cb_balloonDisplay $w \\\{$text\\\}\]
	"
	if {! $cb_balloonHelp(stay_on_screen) } {
	    bind $w <Motion> "
	    catch {
	    set tmp_w \[winfo containing %X %Y\]
	    destroy .cb_balloon
	    after cancel \$cb_balloonHelp(id)
	    after cancel \$cb_balloonHelp(id,timeout)
	    if {\$tmp_w == \"%W\"} {
		set cb_balloonHelp(id) \
		\[after $delay _cb_balloonDisplay $w \\\{$text\\\}\]
	    }
	    unset tmp_w
	    }
	    "
        }
	bind $w <Leave> {
	    catch {destroy .cb_balloon}
	    catch {after cancel $cb_balloonHelp(id)}
	    catch {after cancel $cb_balloonHelp(id,timeout)}
	    set cb_balloonHelp(%W,shown) 0
	}
	bind $w <Any-ButtonPress> {
	    catch {destroy .cb_balloon}
	    catch {after cancel $cb_balloonHelp(id)}
	    catch {after cancel $cb_balloonHelp(id),timeout}
	    set cb_balloonHelp(%W,shown) 1
	}
	bind $w <Any-Key> [bind $w <Any-ButtonPress>]
    } else {
	set cb_balloonHelp($w,$me,text) $text
	bind $w <Enter> "
	set tmp_me \[%W index @%y\]
	if {\[info exists cb_balloonHelp(%W,\$tmp_me,text)\]} {
	    set cb_balloonHelp(id) \
		    \[after $delay _cb_balloonDisplay \
		    $w \\\{\$cb_balloonHelp(%W,\$tmp_me,text)\\\} 1\]
	}
	unset tmp_me
	"
	bind $w <Motion> "
        catch \{destroy .cb_balloon\}
	catch \{after cancel \$cb_balloonHelp(id)\}
	catch \{after cancel \$cb_balloonHelp(id,timeout)\}
	set tmp_me \[%W index @%y\]
	set cb_balloonHelp($w,shown) 0
	if {\[info exists cb_balloonHelp(%W,\$tmp_me,text)\]} {
	    set cb_balloonHelp(id) \
		    \[after $delay _cb_balloonDisplay \
		    $w \\\{\$cb_balloonHelp(%W,\$tmp_me,text)\\\} 1\]
	}
	unset tmp_me
	"
	bind $w <Leave> {
	    catch {destroy .cb_balloon}
	    catch {after cancel $cb_balloonHelp(id)}
	    catch {after cancel $cb_balloonHelp(id,timeout)}
	    #catch {%W config -cursor $cb_balloonHelp(%W,cursor)}
	    set cb_balloonHelp(%W,shown) 0
	}
	bind $w <Any-ButtonPress> [bind $w <Leave>]
	bind $w <Any-Key> [bind $w <Any-ButtonPress>]
    }
}

set cb_tools(balloon_help) 1

proc _cb_balloonDisplay {win text {menu 0}} {
    global cb_balloonHelp cb_tools
    
    if {!$cb_tools(balloon_help) || $cb_balloonHelp($win,shown)} {
	return
    }
    if {[winfo containing [winfo pointerx .] [winfo pointery .]] != $win} {
	return
    }
    set cb_balloonHelp($win,shown) 1

    
    catch {destroy [set t .cb_balloon]}
    toplevel $t 
    wm withdraw $t
    label $t.balloon -text $text -wraplength 200 -justify left \
	    -bd 1 -relief raised
    pack $t.balloon ;# -padx 1 -pady 1
    wm overrideredirect $t 1
    set w [winfo reqwidth $t.balloon]
    set h [winfo height $win]

    if { ! $menu} {
	# basic widget
	set x [expr [winfo rootx $win] + 2]
	set y [expr [winfo rooty $win] + $h + 2]
    } else {
	# menu entry
	set x [expr [winfo rootx $win] + [winfo reqwidth $win] + 2]
	set my [expr [winfo pointery .] - [winfo rooty $win] ]
	set y [expr [winfo rooty $win] + \
		[$win yposition [$win index @$my]] + 2]
    }

    # make help window be completely visible
    if {$x + $w > $cb_balloonHelp(screen_width)} {
	set x [expr $cb_balloonHelp(screen_width) - $w]
    }
    if {$y + $h > $cb_balloonHelp(screen_height)} {
	set y [expr $cb_balloonHelp(screen_height) - $h]
    }

    wm geometry $t +$x+$y
    wm deiconify $t
    # the original cursor is saved in cb_balloonHelp
    #$w config -cursor arrow

    # remove the balloon window after 5 seconds:
    if {! $cb_balloonHelp(stay_on_screen)} {
	set cb_balloonHelp(id,timeout) \
		[after [expr 3000 + [string length $text] * 50] \
		"catch \{destroy $t\}"]
    }
}
