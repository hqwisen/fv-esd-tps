LSRC = ./lustre_src
CSRC = ./c_src
OBJDIR = ./obj


CC = gcc
CFLAGS = -c -I$(CSRC) -I$(OBJDIR)
LFLAGS = -O2 -lcurses


# ec2c compilaton

OBJS = \
	$(OBJDIR)/New_Watch_ext.o \
	$(OBJDIR)/New_Watch.o \
	$(OBJDIR)/New_Watch_main.o


all: $(OBJDIR) watch

$(OBJDIR):
	mkdir $@

watch : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@


$(OBJDIR)/New_Watch.c : $(LSRC)/New_Watch.lus
	lus2ec $(LSRC)/New_Watch.lus New_Watch -o $(OBJDIR)/New_Watch.ec
	ec2c $(OBJDIR)/New_Watch.ec -o $(OBJDIR)/New_Watch.c

$(OBJDIR)/New_Watch.o : $(OBJDIR)/New_Watch.c
	$(CC) $(CFLAGS) $(OBJDIR)/New_Watch.c -o $(OBJDIR)/New_Watch.o

$(OBJDIR)/%.o : $(CSRC)/%.c $(OBJDIR)/New_Watch.o
	$(CC) $(CFLAGS) $(CSRC)/$*.c -o $(OBJDIR)/$*.o

clean :
	/bin/rm -rf $(OBJDIR) watch
