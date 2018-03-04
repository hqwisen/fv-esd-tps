global StrlBox env tcl_platform

# === Global options ====
# Fix basic colors
option add *Foreground Black
option add *Background #d9d9d9
option add *activeForeground Black
option add *activeBackground #ececec
option add *DisabledForeground #a3a3a3
if { $tcl_platform(platform) == "unix" } {
    option add *selectColor #b03060
} else {
    option add *Radiobutton.selectColor white
    option add *Checkbutton.selectColor white
}
option add *Menu.tearOff false

# option menus
option add *optionList.Background white
option add *optionList.activeForeground white 
option add *optionList.activeBackground RoyalBlue 
option add *optionList.activeBorderWidth 0

# option menu labels
option add *value.Background white
option add *value.Justify center
option add *value.HighlightThickness 0

option add *Entry.Background white
option add *Entry.selectBackground RoyalBlue
option add *Entry.selectForeground white

option add *Listbox.Background white
option add *Listbox.selectForeground white
option add *Listbox.selectBackground RoyalBlue

option add *console.Background white
option add *fileview.Background white

# rc file
if { $tcl_platform(platform) == "unix" } {
    set StrlBox(rc_file) [file join $env(HOME) .xstrlrc]
} else {
    set StrlBox(rc_file) [file join $env(HOME) xstrlrc]
}

# the esterel command
set StrlBox(esterel)  esterel

if { [info exist env(ESTEREL)] } {
    if { $tcl_platform(platform) == "unix" } {
	set esterel [file join $env(ESTEREL) esterel]
    } else {
	set esterel [file join $env(ESTEREL) "esterel.exe"]
    }
    if { [file exist $esterel] } {
	set StrlBox(esterel)  $esterel
    }
} 

# list of simulator
if { $tcl_platform(platform) == "unix" } {
    set StrlBox(simulator:defaults)  {
	"xes %s"
	"gcc %s -L/usr/local/esterel/lib -lxes"
	"gcc %s -L/usr/local/esterel/lib -lcsimul"
	"a.out"
	"%s"
    }
} else {
    set StrlBox(simulator:defaults)  {
	"xes %s"
	"%s"
    }
}

set StrlBox(simulator:simulate) [lindex $StrlBox(simulator:defaults) 0]
set StrlBox(simulator:list) $StrlBox(simulator:defaults)

# compiler
if { $tcl_platform(platform) == "unix" } {
    set StrlBox(simulator:compile) "gcc -c %s"
} else {
    set StrlBox(simulator:compile) "cl.exe -c %s"
}

# possible other tools
set StrlBox(tools:list) ""

# extension for file browser
set StrlBox(files:extensions) {
    {"Esterel Code" {*.strl}}
    {"ic Code" {*.ic *.lc}}
    {"Circuit Code" {*.sc}}
    {"Sorted Circuit Code" {*.ssc}}
    {"Object Code" {*.oc}}
    {"All" {*.*}}
}

# extension for simulation browser
if { $tcl_platform(platform) == "unix" } {
    set StrlBox(simulator:extensions) {
	{"C Code"               {*.c}}  
	{"Object Code"          {*.o}}
	{"Object & C Code"      {*.[och]}}  
	{"All" {*.*}}
    }
} else {
    set StrlBox(simulator:extensions) {
	{"C Code"               {*.c}}  
	{"Object Code"          {*.obj *.o}}
	{"Object & C Code"      {*.obj *.[och]}}  
	{"All" {*.*}}
    }
}

# user extensions
set StrlBox(user:extensions) ""

# variables for language options.
# language:<lang>:<class>:options
# where class is the input format class.
set StrlBox(language:c:scl:options) ""
set StrlBox(language:c:sscl:options) ""
set StrlBox(language:c:ocl:options) ""
set StrlBox(language:blif:sscl:options) ""

# compilation option list
set StrlBox(compilation:list) [list \
	"Sorted Equations" "-L" \
	"Interpreted" "-I" \
	"Automaton" "-A"  \
	"Inline Automaton" "inlineAutomaton"  \
	"Single State" "-S" \
	"Check Only" "-Icheck" ]

# language option list
set StrlBox(language:list) [list \
	"C" "c" \
	"ANSI C" "ansic" \
	"Hardware Circuit" "blif" \
	"Software Circuit" "softBlif" \
	"FC Tools" "fc2" \
	"None" "-" ]

# warning list
set StrlBox(warnings:list) [list \
	"None" "-" \
	"Harmful" "-w" \
	"All" "-W" ]

# === Internal processors and their options ===
# elements are {processor class desc spec ...}
# processor: the processor name
# class: list {type language class}
#        where type is internal for internal processor. In this case
#        there is no language nor class spec.
#        type is generator: language is target language et class
#        if input format class, as scl, ocl.
#
#        
# spec : list of specification of option presentation
#        - options as checkbutton
#          {check mnemonic buttonLabel buttonHelp option}
#          ex {check v3 "V3 Mode" "Split Boolean signal expressions" -v3}
#        - simple menu
#        {menu mnemonic label menuHelp {label option ...}}
#        ex:
#        {menu "warnings" 
#              "Warnings" "Set level of warnings."
#               {"None" "-" "Harmful" "-w" "All" "-W"}}
#         option '-' means no option in command line
#
#        - check menu. List of suboptions coding -R, -Rf, -Rft
#        {cmenu mnemonic label menuHelp option {label option ...}}
#        ex:
#       {cmenu trace "Trace" "Trace captures and renamings" -R
#         {Types t Constants c Functions f Procedures p Signals s Tasks k}}
#        - option plus value (entry)
#        {entry mnemonic label entryHelp option}
#        ex:
#        {entry main "Main module" "Main module to bind" -main}
#
set StrlBox(processor:list) ""
set StrlBox(processor:description) {
   {strlic 
       {internal}
       "Esterel front-end. Converts Esterel code into ic code."
       {check v3 "V3 Mode" "Split Boolean signal expressions." -v3}
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
   {iclc 
       {internal}
       "Esterel linker. Assemble ic code \
and resolve module calls and renamings."
       {check v3 "V3 Mode" "Use v3 intermediate code." -V3}
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
       {entry main "Main Module" "Main module to bind." -main}
       {cmenu trace "Trace" "Trace captures and renamings." -R \
          {Types t Constants c Functions f Procedures p Signals s Tasks k}}
   }
   {lcsc 
       {internal}
       "Esterel core processor. Translate program control into \
boolean equations, ie an implicit automaton."
       {check acc "Control Cycles" "Allow safe control cycles." -acc}
       {check parano "Full duplication" \
	      "Systematically duplicate surfaces instead of trying \
 to do static analysis" -parano}
       {check verify "Verify" "Used for blif comparizon." -verify}
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
   {lcoc 
       {internal}
       "Old Esterel core. Translate program into explicit automaton."
       {check show "Show States" "Show analyzed states." -show}
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
   {sccausal
       {internal}
       "Constructive Causality Analyser. Performs reachable states analysis \
to make cyclic circuits acyclic. Also try to remove latches."
       {check verbose Verbose "Verbose." -v}
       {check sift Sifting "Do sifting on BDD" -sift}
       {check o1 "Optimize BDD" "Optimize BDD using sifting." -o1}
       {check o2 "Remove Latches" "Remove redundant latches." -o2}
       {check single "Single signals" "Check single signals." -single}
       {check cyclicBlif "Cyclic BLIF" "Write cyclic BLIF before analysis." 
              -cyclic_blif}
       {check blif "Write BLIF" "Write acyclic BLIF after analysis." 
              -blif}
       {check xes "No Debug" "Do not call graphical interface." -no_xes}
       {check tvf "TFV" "Used for sccausal test." -tvf}
       {menu control "Analysis Control" "Control the analysis algorithm."
          {"Default" - "Cofactor" -cofactor 
           "Restrict" -restrict  "Incremental" -inc}}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
       {entry basename Basename 
	      "Output basename for -blif and -cyclic_blif options." -B}
   }
   {scssc
       {internal}
       "Topological sorter. Transform boolean equations of Sc code into \
sorted boolean equations."
       {check cycles Cycles "Show all cycles." -allcycles}
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
   {scc 
       {generator scl c}
       "Interpreted C code generator."
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
   {sscc 
       {generator sscl c}
       "C sorted boolean equation generator."
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }  
   {sscblif 
       {generator sscl blif}
       "BLIF code generator. Used for control optimization."
       {check makefile Makefile "Generate a Mafile for optimization." 
        -makefile}
       {check 
          hierarchy Hierarchy "Decompose circuit into subcircuits." 
        -hierarchy}
       {check 
          soft Soft "Generate control circuit for any Esterel program." -soft}
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
   {sscoc 
       {internal} 
       "Build explicit automata from implicit ones described as circuits."
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
   {occ
      {generator ocl c}
       "C automaton code generator."
       {check verbose Verbose "Verbose." -v}
       {menu "warnings" 
              "Warnings" "Set level of warnings."
              {"None" "-" "Harmful" "-w" "All" "-W"}}
   }
}

# ==== current path ====
if {[info exist env(PWD)]} {
    set StrlBox(dirs:cwd) $env(PWD)
} else {
    set StrlBox(dirs:cwd) [pwd]
}
# size of directory history
set StrlBox(dirs:history:size) 10

# ==== main toplevel  ====
set StrlBox(top) .strlbox


# ==== Help ====
set StrlBox(help:balloon) 1

# ==== Esterel formats ====
set StrlBox(formats) {strl ic lc sc ssc oc}
set StrlBox(files:selected) {}
foreach fmt $StrlBox(formats) {
    set StrlBox(files:.$fmt) ""
}

# ==== Misc ====
# value of command line
set StrlBox(command:line) ""

# history size of console
set StrlBox(console:history:size) 100

# show execution in console. Other values are: run (on stdout)
# print (don't run but simply print command
set StrlBox(exec:mode) console

# edition of command entries (compiler, simulator) disabled or normal
set StrlBox(command:edition) disabled
