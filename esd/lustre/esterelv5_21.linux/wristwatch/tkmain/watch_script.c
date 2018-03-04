
#ifndef _ANSI_ARGS_
#define _ANSI_ARGS_(x) ()
#endif

typedef struct {
    char *name;
    char **tcl_code;
    long lines;
    long chars;
} Tcl2array;


/* 
 * loads a tcl code put in code_array
 */
extern int 
Tcl_LoadCodeArray _ANSI_ARGS_((Tcl_Interp *interp, Tcl2array code_array));

static char *__watch_script[] = {
"global Watch",
"wm withdraw .",
"if { $argv != \"\" } {",
"    WatchSetSpeed [lindex $argv 0]",
"}",
"proc cget {widget option} {",
"    return [lindex [$widget configure $option] 4]",
"}",
"proc WatchSwitchForeBackGround {what} {",
"    global Watch",
"    set foreground [cget $Watch($what) -foreground]",
"    set background [cget $Watch($what) -background]",
"    $Watch($what) configure -bg $foreground",
"    $Watch($what) configure -fg $background",
"}",
"proc WRISTWATCH_O_BEEP { beep } {",
"    global Watch",
"    set delay 0",
"    for {set i 0} {$i<$beep} {incr i} {",
"	bell",
"	after [incr delay 100] $Watch(watch_frame) configure -bg red",
"	after [incr delay 100] $Watch(watch_frame) configure -bg black",
"    }",
"}",
"proc WRISTWATCH_O_START_ENHANCING {w} {",
"    WatchSwitchForeBackGround $w",
"}",
"proc WRISTWATCH_O_STOP_ENHANCING {w} {",
"    WatchSwitchForeBackGround $w",
"}",
"proc WRISTWATCH_O_MAIN_DISPLAY { \\",
"	hour_or_mn \\",
"	mn_or_sec \\",
"	sec_or_cent \\",
"	time_mode} {",
"    global Watch",
"    $Watch(main,hour_or_mn) configure -text \"$hour_or_mn\"",
"    $Watch(main,10mn_or_sec) configure -text [string index \"$mn_or_sec\" 0]",
"    $Watch(main,mn_or_sec) configure -text [string index \"$mn_or_sec\" 1]",
"    $Watch(main,sec_or_cent) configure -text \"$sec_or_cent\"    ",
"    $Watch(main,time_mode) configure -text \"$time_mode\"",
"}",
"proc WRISTWATCH_O_MINI_DISPLAY {hour_or_day sep mn_or_month} {",
"    global Watch",
"    $Watch(mini,hour_or_day) configure -text \"$hour_or_day\"",
"    $Watch(mini,sep) configure -text \"$sep\"",
"    $Watch(mini,mn_or_month) configure -text \"$mn_or_month\"",
"}",
"proc WRISTWATCH_O_ALPHABETIC_DISPLAY {s} {",
"    global Watch",
"    $Watch(alphabetic) configure -text \"$s\"",
"}",
"proc WRISTWATCH_O_CHIME_STATUS {set} {",
"    global Watch",
"    set text [cget $Watch(main,chime_alarm) -text]",
"    if {$set} {",
"	regsub {(.. )....( ..)} $text {\\1(())\\2} text",
"    } else {",
"	regsub {\\(\\(\\)\\)} $text {    } text",
"    }",
"    $Watch(main,chime_alarm) configure -text \"$text\"",
"}",
"proc WRISTWATCH_O_ALARM_STATUS {set} {",
"    global Watch",
"    set text [cget $Watch(main,chime_alarm) -text]",
"    if {$set} {",
"	regsub {..( .... )..} $text {((\\1))} text",
"    } else {",
"	regsub {..( .... )..} $text {  \\1  } text",
"    }",
"    $Watch(main,chime_alarm) configure -text \"$text\"",
"}",
"proc WRISTWATCH_O_STOPWATCH_RUN_STATUS {set} {",
"    global Watch",
"    if {$set} {",
"	$Watch(run) configure -text \"run\"",
"    } else {",
"	$Watch(run) configure -text \"   \"",
"    }",
"}",
"proc WRISTWATCH_O_STOPWATCH_LAP_STATUS {set} {",
"    global Watch",
"    if {$set} {",
"	$Watch(lap) configure -text \"lap\"",
"    } else {",
"	$Watch(lap) configure -text \"   \"",
"    }",
"}",
"set Watch(inputs) {}",
"set Watch(running) 0",
"proc WatchAppendEvent {args} {",
"    global Watch",
"    foreach event $args {",
"	if {[lsearch $Watch(inputs) $event]==-1} {",
"	    lappend Watch(inputs) $event",
"	}",
"    }",
"    if { $Watch(running) == 0} {",
"	if {[catch WatchHandleEvents error]} {",
"	    puts stderr \"error $error\"",
"	}",
"    }",
"}",
"proc WatchHandleEvents {} {",
"    global Watch",
"    set Watch(running) 1",
"    while {[llength $Watch(inputs)] != 0} {",
"	foreach event $Watch(inputs) {",
"	    WRISTWATCH_I_$event",
"	}",
"	set Watch(inputs) {}",
"	WRISTWATCH",
"    }",
"    set Watch(running) 0",
"}",
"set Watch(large_font)  {-adobe-helvetica-bold-r-*-*-*-180-*}",
"set Watch(medium_font) {-adobe-helvetica-bold-r-*-*-*-140-*}",
"set Watch(small_font)  {-adobe-helvetica-bold-r-*-*-*-120-*}",
"set Watch(watch) .watch",
"set Watch(input) {}",
"catch {destroy $Watch(watch)}",
"toplevel $Watch(watch)",
"set Watch(left_frame)   [frame $Watch(watch).left_frame] ",
"set Watch(right_frame)	[frame $Watch(watch).rigth_frame]",
"set Watch(watch_frame)	[frame $Watch(watch).watch_frame -bg black] ",
"set Watch(screen_frame) [frame $Watch(watch).watch_frame.screen]",
"pack $Watch(left_frame) -side left -fill y",
"pack $Watch(right_frame) -side right -fill y",
"pack $Watch(watch_frame) -side top -fill both -expand 1",
"pack $Watch(screen_frame) -padx 5 -pady 5 -expand 1 -fill both",
"set Watch(UL) [button $Watch(left_frame).ul -text UL]",
"set Watch(LL) [button $Watch(left_frame).ll -text LL]",
"set Watch(UR) [button $Watch(right_frame).ur -text UR]",
"set Watch(LR) [button $Watch(right_frame).lr -text LR]",
"pack $Watch(UL) -expand 1",
"pack $Watch(LL) -expand 1",
"pack $Watch(UR) -expand 1",
"pack $Watch(LR) -expand 1",
"$Watch(UL) configure -command {WatchAppendEvent UL}",
"$Watch(LL) configure -command {WatchAppendEvent LL}",
"$Watch(LR) configure -command {WatchAppendEvent LR}",
"$Watch(UR) configure -command {WatchAppendEvent UR}",
"set Watch(top_display) [frame $Watch(screen_frame).top_display]",
"pack $Watch(top_display) -fill x",
"set Watch(alphabetic)  \\",
"	[label $Watch(top_display).alphabetic \\",
"	-font $Watch(large_font) -width 3 -text MO]",
"set Watch(mini_display) \\",
"	[frame $Watch(top_display).mini_display -bd 2 -relief ridge]",
"set Watch(mini,hour_or_day)  \\",
"	[label $Watch(mini_display).hour_or_day \\",
"	-font $Watch(large_font) -width 2 -anchor e \\",
"	-text 9]",
"set Watch(mini,mn_or_month)  \\",
"	[label $Watch(mini_display).mn_or_month \\",
"	-font $Watch(large_font) -width 2 -anchor w \\",
"	-text 11]",
"set Watch(mini,sep) \\",
"	[label $Watch(mini_display).sep -font $Watch(large_font) -text \"-\"]",
"set Watch(lap) \\",
"	[label $Watch(top_display).lap -font $Watch(small_font) -text lap]",
"set Watch(run) \\",
"	[label $Watch(top_display).run -font $Watch(small_font) -text run]",
"pack $Watch(alphabetic) -side left -padx 4 ",
"pack $Watch(mini_display) -side right -padx 4",
"pack $Watch(mini,mn_or_month) -side right",
"pack $Watch(mini,sep) -side right",
"pack $Watch(mini,hour_or_day) -side right",
"pack $Watch(lap)",
"pack $Watch(run)",
"pack [frame $Watch(screen_frame).sep -bd 1 -height 2 -relief sunken ] -fill x",
"set Watch(main_display) [frame $Watch(screen_frame).main_display]",
"pack $Watch(main_display) -fill x",
"set Watch(top_main) [frame $Watch(main_display).top]",
"set Watch(bot_main) [frame $Watch(main_display).bot]",
"pack $Watch(top_main) -fill x",
"pack $Watch(bot_main) -fill x",
"set Watch(main,time_mode) \\",
"	[label $Watch(top_main).time_mode \\",
"	-font $Watch(small_font) -width 3 \\",
"	-text PM]",
"set Watch(main,chime_alarm)     \\",
"	[label $Watch(top_main).chime_alarm -font $Watch(small_font) \\",
"	-text {(( (()) ))}]",
"$Watch(top_main).chime_alarm configure -width 11",
"pack $Watch(main,time_mode) -side left -expand 1 -anchor e -fill x",
"pack $Watch(main,chime_alarm) -side right -padx 4",
"set Watch(main,hour_or_mn)  \\",
"	[label $Watch(bot_main).hour_or_mn \\",
"	-font $Watch(large_font) -width 2 -anchor e \\",
"	-text 11]",
"set Watch(main,sep)         \\",
"	[label $Watch(bot_main).sep -font $Watch(large_font) \\",
"	-text {:}]",
"set Watch(main,10mn_or_sec)   \\",
"	[label $Watch(bot_main).10mn_or_sec \\",
"	-font $Watch(large_font) -anchor e -width 1 -padx 0\\",
"	-text 1]",
"set Watch(main,mn_or_sec)   \\",
"	[label $Watch(bot_main).mn_or_sec \\",
"	-font $Watch(large_font) -anchor w -width 1 -padx 0\\",
"	-text 2]",
"set Watch(main,sec_or_cent) \\",
"	[label $Watch(bot_main).sec_or_cent \\",
"	-font $Watch(medium_font) -width 2 \\",
"	-text 43]",
"pack $Watch(main,hour_or_mn) -side left -expand 1 -anchor e",
"pack $Watch(main,sep) -side left",
"pack $Watch(main,10mn_or_sec) -side left ",
"pack $Watch(main,mn_or_sec) -side left  -anchor w",
"pack $Watch(main,sec_or_cent) -side left -expand 1 -anchor w -padx 4",
"focus $Watch(watch)",
"bind $Watch(watch) <q> {destroy %W}",
"bind $Watch(watch) <Q> {destroy %W}",
"tkwait visibility $Watch(watch)",
"pack propagate $Watch(mini_display) 0",
"pack propagate $Watch(top_display) 0",
"pack propagate $Watch(main_display) 0",
"pack propagate $Watch(top_main) 0",
"pack propagate $Watch(bot_main) 0",
"update idletasks",
"WatchStartTimer",
"tkwait window $Watch(watch)",
"exit 0",
""
};
Tcl2array watch_script = {
	"watch_script",
	__watch_script,
	224,
	7146
};