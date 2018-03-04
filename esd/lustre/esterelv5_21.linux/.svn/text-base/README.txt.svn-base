                           ESTEREL Version V5_21
                           ---------------------

                            INSTALLATION NOTES


This is release V5_21 of the Esterel V5 compiler by INRIA / CMA.

This tape includes the following:

        1) This "README.txt" file and a release "RELEASENOTES.txt" file.

        2) Some executable files, libraries and header files in
           subdirectories "bin", "lib" and "include".

        3) The man pages in "man" nroff format for the different
           programs and libraries, in directory "man". (Unix only)

        4) The documentation in PDF and PostScript formats in
	   directory "doc". The files "primer.pdf" and "primer.ps"
	   contain the Esterel language description,  with hyperlinks
	   for the PDF version. The file "manual.pdf" is the Esterel
	   v5_21 system  manual. It explains how to use the compiler,
	   how to interface with the C generated code, and how to use
	   the simulators. The PostScript "manual.ps" is unfortunately 
	   to big to get included in the distribution, but you can get 
	   it at: ftp://ftp-sop.inria.fr/meije/esterel/....

        5) An installation "Makefile" that you will have to modify,
           and a copy Makefile.orig of this Makefile if you want
           to cancel or change your modifications. (Unix only)

        6) The wristwatch example in directory wristwatch.

        7) Constructive causality analysis examples in directory
	   sccheck.

        8) a tcltk directory that contains Tcl/Tk libraries. 
 

Installing Esterel v5_21 (Unix only)
====================================

        1) Put this directory tree where you want it to stay.
           Be careful: this directory MUST remain permanently
           at the same place in your machine, since the installation
	   only builds symbolic links to the files it contains. To
	   change the installation, first do "make uninstall", then
	   redo "make install".

        2) Edit the "Makefile" and set the definitions of the 9
           variables ESTEREL_DISTRIB_DIR, ESTEREL_COMMAND, XES_COMMAND,
           XESTEREL_COMMAND, BIN_DIR, LIB_DIR, INCLUDE_DIR, MAN1_DIR, and
           MAN3_DIR which control the location from which the Esterel
           components will be accessible.  (see comments in Makefile for
           explanations)

        3) Type

               make install        (or simply make)

The Esterel automatic installation procedure sets the access rights
of the esterel files. If needed, check that they suit your own system 
management policy.

The Esterel compiler, the xesterel GUI and xes simulator should be
ready to run. To identify the software's version, type the commands:

   esterel -version
   xes -version

to check that the Esterel sofware is installed and operational.

Uninstalling the Esterel v5_21 system (Unix only)
=================================================

In order to remove the Esterel compiler installed by the Makefile,
that is all the symbolic links created by the installation procedure above,
type

   make uninstall

Running the wristwatch example
==============================

Go to directory wristwatch. 
 - Unix

   Type:
      make -f makefile.Unix

 - Windows NT

   Type in a command interpreter window:
      nmake -f makefile.VC

These commands will produces a tty simulation (Unix: sww, NT: sww.exe),
an xes-based simulator (xww.exe), and Tcl/Tk executable
(tkww.exe). See the README file in directory wristwatch for more details.


PLEASE READ CAREFULLY THE COPYRIGHT NOTICE.
