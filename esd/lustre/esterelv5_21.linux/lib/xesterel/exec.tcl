proc SB_Console {} {
    global StrlBox
    if {[winfo exist .exec]} {
	wm deiconify .exec
	raise .exec
	update
	return
    }
    toplevel .exec
    pack [button .exec.close -text Close \
	    -command {wm withdraw .exec}] \
	    -side bottom -fill x

    set StrlBox(exec:console) [text .exec.console \
	    -state disabled \
	    -highlightthickness 0 \
	    -wrap char]
    scrollbar .exec.vscroll \
	    -command ".exec.console yview" \
	    -orient vertical
    .exec.console configure -yscrollcommand ".exec.vscroll set"
    pack .exec.vscroll -side left -fill y
    pack .exec.console -side left  -expand 1 -fill both
    update idletasks
    set StrlBox(console:lines) 0
}

proc SB_ToConsole {text} {
    global StrlBox
    SB_Console
    $StrlBox(exec:console) configure -state normal
    $StrlBox(exec:console) insert end $text
    $StrlBox(exec:console) configure -state disabled
    $StrlBox(exec:console)  see end
    incr StrlBox(console:lines)
    if {$StrlBox(console:lines) > $StrlBox(console:history:size)} {
	$StrlBox(exec:console) delete 1.0 "1.0 lineend + 1 chars"
	set StrlBox(console:lines) $StrlBox(console:history:size)
    }
    update idletasks
}

proc SB_Exec {cmd} {
    global StrlBox tcl_platform
    set cmd [string trim $cmd]
    if {$cmd == "" } {
	return
    }
    if { $tcl_platform(platform) == "unix" } {
	# background commands
        if {[regsub "&$" $cmd "" cmd]} {
	    catch {eval "exec $cmd >&@ stdout &"} error
	    return
	}

	switch $StrlBox(exec:mode) {
	    console {
		SB_ToConsole "\$ $cmd\n"
		set fd [open "|$cmd |& cat"]
		while {[gets $fd line] != -1} {
		    SB_ToConsole "$line\n"
		}
		catch {close $fd}
		SB_ToConsole "--- Done\n"
	    }
	    run {
		puts "--- Running $cmd"
		catch {eval "exec $cmd >&@ stdout"} error
	    }
	    print {
		puts $cmd
	    }
	}
    } else {
	# see strl.bat
	global env
	set batch exe[pid].cmd
	if {[info exist env(TMP)]} {
	    set batch [file join $env(TMP) $batch]
	} elseif {[info exist env(TEMP)]} {
	    set batch [file join $env(TEMP) $batch]
	} 
	if {[catch {open $batch w} fd]} {
	    SB_ToConsole "Cannot open \"$batch\"\n$fd\n"
	    return
	}
	puts $fd {@echo off}
	puts $fd {REM TMP FILE AUTOMATICALLY GENERATED BY XESTEREL}
	puts $fd "echo --- Running $cmd"
	puts $fd $cmd
	puts $fd "if ERRORLEVEL 0 goto end"
	puts $fd "echo --- Done"
	puts $fd :end
	puts $fd pause
	puts $fd exit
	close $fd
	if {[catch {exec cmd /x /c "start /i $batch"} error]} {
	    SB_ToConsole "\n$error\nwhile running \"$batch\""
	}
	file delete $batch
    }
}