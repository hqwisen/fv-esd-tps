#******************************************************************************
#
# Esterel v5_21: installation Makefile.
#
#******************************************************************************

# This Makefile is part of the Esterel v5_21 distribution you have
# downloaded. Please, enter here the full path name of the root directory
# of the distribution, that is, of the directory that contains this Makefile
# By default, we set this variable to /usr/local/esterelv5_20. Change it
# if you downloaded the tape in a different place.

ESTEREL_DISTRIB_DIR = /usr/local/esterelv5_21

# All distributed files will remain in this $ESTEREL_DISTRIB_DIR
# directory tree.
# This installation Makefile will just link commands and libraries 
# in the directories specified below
#
# If you use the default names and directories we have provided below,
# just type "make". Otherwise, change the directories below and type "make".

# Type "make uninstall" to remove all links made by this installation
# procedure. You will then be able to edit this Makefile again and to make
# another installation.

#==============================================================================
# Directory specification
#==============================================================================

#-------------------------------------------------------------
# Name of the installed esterel, xes and GUI xesterel commands
#-------------------------------------------------------------

ESTEREL_COMMAND	= esterel
XES_COMMAND	= xes
XESTEREL_COMMAND= xesterel


# if you don't want to override your current esterel, set:
#ESTEREL_COMMAND   = esterelv5_21
#XES_COMMAND	   = xesv5_21
#XESTEREL_COMMAND  = xesterelv5_21

#----------------------------------------------------------------------
# Directory where to link the "esterel", "xes", "xesterel" and "sametype" 
# commands
#
# REMARKS : This is useful if want to have a direct access, say 
# /usr/local/bin/esterel, instead of updating your PATH variable.
# Do no set BIN_DIR to $(ESTEREL_DISTRIB_DIR)/bin.
#----------------------------------------------------------------------

# If you do want to create symbolic links instead of adding
# $ESTEREL_DISTRIB_DIR/bin, to your PATH variable, comment the following line
# else use the next line
BIN_DIR	=
# BIN_DIR		= /usr/local/bin


#--------------------------------------------------------
# Directory where to link header include files ("XXX.h")
# Same remarks as for BIN_DIR
#--------------------------------------------------------
# If you do want to create symbolic links instead of adding
# -I$ESTEREL_DISTRIB_DIR/include option of your C compiler,
# comment the following line and use the next line.
INCLUDE_DIR	=
# INCLUDE_DIR	= /usr/local/include



#-----------------------------------------------------------------
# Directory where to link simulation and interpretation libraries
# Same remarks as for BIN_DIR
#-----------------------------------------------------------------
# If you do want to create symbolic links instead of adding
# -L$ESTEREL_DISTRIB_DIR/lib option of your C compiler,
# comment the following line and use the next line.
LIB_DIR	=
#LIB_DIR		= /usr/local/lib



#---------------------------------------------------
# Directory where to link man pages (man1 and man3)
# Same remarks as for BIN_DIR
#---------------------------------------------------
# If you do want to create symbolic links instead of adding
# $ESTEREL_DISTRIB_DIR/man to your MANPATH shell variable,
# comment the following line and use the next line.
MAN1_DIR	=
MAN3_DIR	=
# MAN1_DIR	= /usr/local/man/man1
# MAN3_DIR	= /usr/local/man/man3



#==============================================================================
# Installation procedure proper -- DO NOT CHANGE !
#==============================================================================

#------------------------------------------------------------------------------
# Variables
#------------------------------------------------------------------------------

SHELL = /bin/sh
MAIN_SCRIPT_FILES= esterel xes xesterel
SCRIPT_FILES	 = $(MAIN_SCRIPT_FILES) sscdebug
BIN_FILES	 = sametype
LIB_FILES	 = libcsimul.a libxes.a
INCLUDE_FILES	 = csimul.h exec_status.h
MAN1_FILES	 = esterel.1 strlic.1 iclc.1 lcoc.1 lcsc.1 scssc.1 \
		  sscoc.1 occ.1 sscc.1 scc.1 ocdebug.1 sscdebug.1 \
		  sametype.1 sscblif.1 blifssc.1 xes.1
MAN3_FILES	 = csimul.3 xes.3


#------------------------------------------------------------------------------
# Installation
#------------------------------------------------------------------------------

install:
	@chmod u+w bin
	@cd bin							;\
	 for FILE in $(SCRIPT_FILES)				;\
	 do							 \
	    echo "-- Updating $$FILE shell script"		;\
	    chmod u+w $$FILE					;\
	    sed  -e "/^[	 ]*ESTEREL=[^\`]/s|=[^;]*|=$(ESTEREL_DISTRIB_DIR)|"	 \
	         $$FILE.orig > $$FILE				;\
	 done
#
	@chmod u+w lib
	@cd lib							;\
	 for FILE in $(LIB_FILES)				;\
	 do							 \
	    echo "-- Updating table of contents of $$FILE"	;\
	    chmod u+w $$FILE					;\
	    ranlib $$FILE					;\
	 done
#
	@echo "-- Correcting access rights of distributed files"
	@find .    \( -name bin      -exec chmod -R 555 {} \; -prune \)	\
		-o \( -name Makefile -exec chmod    644 {} \; \)	\
		-o \( -type d        -exec chmod    755 {} \; \)	\
		-o \(                -exec chmod    444 {} \; \)
	@chmod u+w bin
	@chmod a-x bin/scrun.c
	@chmod u+w Makefile
#
	@if [ -n "$(BIN_DIR)" -a \
	     -d "$(BIN_DIR)" -a \
	     -f "$(BIN_DIR)/$(ESTEREL_COMMAND)" ] ; \
	then					\
	   echo "### Warning : an Esterel command is already installed as:"; \
	   echo "    $(BIN_DIR)/$(ESTEREL_COMMAND)"; \
	   echo "You should perform \"make uninstall\" in the previous Esterel distribution."; \
           exit 1;				\
	fi
	@$(MAKE) ESTEREL_DISTRIB_DIR=$(ESTEREL_DISTRIB_DIR) \
                 DIR=$(BIN_DIR)					\
		 FILE_LIST="esterel xes xesterel"	        \
		 LINK_LIST="$(ESTEREL_COMMAND) $(XES_COMMAND) $(XESTEREL_COMMAND)"\
		 SRC_DIR=bin					\
		 REMIND=""    \
		 one_install
	@$(MAKE) ESTEREL_DISTRIB_DIR=$(ESTEREL_DISTRIB_DIR) \
                 DIR=$(BIN_DIR)					\
		 FILE_LIST="$(BIN_FILES)"	\
		 SRC_DIR=bin					\
		 REMIND="\"$(ESTEREL_DISTRIB_DIR)/bin\" to your PATH"    \
		 one_install
	@$(MAKE) ESTEREL_DISTRIB_DIR=$(ESTEREL_DISTRIB_DIR) \
                 DIR=$(LIB_DIR)					\
		 FILE_LIST="$(LIB_FILES)"			\
		 SRC_DIR=lib					\
		 REMIND="option \"-L$(ESTEREL_DISTRIB_DIR)/lib\" to your C compilation command"	\
		 one_install
	@$(MAKE) ESTEREL_DISTRIB_DIR=$(ESTEREL_DISTRIB_DIR) \
                 DIR=$(INCLUDE_DIR)				\
		 FILE_LIST="$(INCLUDE_FILES)"			\
		 SRC_DIR=include				\
		 REMIND="option \"-I$(ESTEREL_DISTRIB_DIR)/include\" to your C compilation command"	\
		 one_install
	@$(MAKE) ESTEREL_DISTRIB_DIR=$(ESTEREL_DISTRIB_DIR) \
                 DIR=$(MAN1_DIR)				\
		 FILE_LIST="$(MAN1_FILES)"			\
		 SRC_DIR=man/man1				\
		 REMIND="\"$(ESTEREL_DISTRIB_DIR)/man\" to your MANPATH"\
		 one_install
	@$(MAKE) ESTEREL_DISTRIB_DIR=$(ESTEREL_DISTRIB_DIR) \
                 DIR=$(MAN3_DIR)				 \
		 FILE_LIST="$(MAN3_FILES)"			 \
		 SRC_DIR=man/man3				 \
		 REMIND="\"$(ESTEREL_DISTRIB_DIR)/man\" to your MANPATH"\
		 one_install
#
	@echo "*** Installation apparently successful. Version check:"
	@if test "$(BIN_DIR)"                                   ;\
	then                                                     \
	   esterel_cmd=$(BIN_DIR)/$(ESTEREL_COMMAND)            ;\
	   xes_cmd=$(BIN_DIR)/$(XES_COMMAND)                   ;\
	else                                                     \
	   esterel_cmd=bin/esterel                             ;\
	   xes_cmd=bin/xes                                     ;\
        fi                                                     ;\
	if $$esterel_cmd -version                              ;\
	then                                                    \
	   $$xes_cmd -version                                  ;\
	else                                                    \
	   echo "### Check failed. Check if the macro"         ;\
	   echo "    ESTEREL_DISTRIB_DIR=$(ESTEREL_DISTRIB_DIR)" ;\
	   echo "    defines correctly this distribution directory." ;\
           exit 1                                              ;\
	fi
#
	@echo "++ Remember that Esterel documentation is in directory \"$(ESTEREL_DISTRIB_DIR)/doc\"".


one_install:
	@if test -z "$(DIR)"					;\
	 then							 \
	    if test ! -z "$(REMIND)"				;\
	       then						 \
	          echo "++ Do not forget to add $(REMIND)"	;\
	       else						 \
	          :						;\
	       fi						;\
	 else							 \
	    if test "$(ESTEREL_DISTRIB_DIR)/$(SRC_DIR)" = "$(DIR)" ; \
	    then				 \
		echo "*** Installation error : " ;  \
		echo "    Directory $(DIR) cannot be used to set links" ; \
		echo "    since files cannot be linked to themselves." ; \
		exit 1			       ;\
	    else			       \
		:                              ;\
	    fi				       ;\
	    mkdir -p $(DIR) || :				;\
	    if  test ! -w $(DIR)				;\
	    then						 \
	       echo "*** Installation error : directory $(DIR) is not writable" ;\
	       exit 1						;\
	    else						 \
	       cd $(DIR)					;\
	       if [ -z "$(LINK_LIST)" ]                         ;\
	       then                                              \
	          set $(FILE_LIST)                              ;\
	       else                   		                 \
	          set $(LINK_LIST)                              ;\
	       fi                                               ;\
	       for FILE in $(FILE_LIST)				;\
	       do						 \
	          echo "-- Linking $$FILE in $(DIR)"		;\
	          ln -fs $(ESTEREL_DISTRIB_DIR)/$(SRC_DIR)/$$FILE $$1	;\
	          shift				                ;\
	       done						;\
	    fi							;\
	 fi


#------------------------------------------------------------------------------
# Uninstallation
#------------------------------------------------------------------------------

uninstall clean:
	@$(MAKE) DIR=$(BIN_DIR)				\
		 FILE_LIST="$(ESTEREL_COMMAND) $(XES_COMMAND) $(XESTEREL_COMMAND) $(BIN_FILES)" \
		 one_uninstall
	@$(MAKE) DIR=$(LIB_DIR)				\
		 FILE_LIST="$(LIB_FILES)"		\
		 one_uninstall
	@$(MAKE) DIR=$(INCLUDE_DIR)			\
		 FILE_LIST="$(INCLUDE_FILES)"		\
		 one_uninstall
	@$(MAKE) DIR=$(MAN1_DIR)			\
		 FILE_LIST="$(MAN1_FILES)"		\
		 one_uninstall
	@$(MAKE) DIR=$(MAN3_DIR)			\
		 FILE_LIST="$(MAN3_FILES)"		\
		 one_uninstall
one_uninstall:
	@if test ! -z "$(DIR)"				;\
	 then						 \
	    cd $(DIR)					;\
	    for FILE in $(FILE_LIST)			;\
	    do						 \
	       echo "-- Unlinking $$FILE from $(DIR)"	;\
	       rm -f $(DIR)/$$FILE			;\
	    done					;\
	 else						 \
	    :						;\
	 fi

#==============================================================================
