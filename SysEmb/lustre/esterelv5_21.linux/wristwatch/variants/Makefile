#
# makefile for the wristwatch variants
#

# User-definable

ESTEREL = esterel
STRLFLAGS = -size

# Don't change from here

WS1A_STRL= watch.strl \
          stopwatch1.strl \
          alarm.strl \
          button-ws1a.strl \
          display-wsa.strl \
          wristwatch-ws1a.strl

WS2A_STRL= watch.strl \
           stopwatch2.strl \
           alarm.strl \
           button-ws2a.strl \
           display-wsa.strl \
           wristwatch-ws2a.strl

WS1_STRL= watch.strl \
          stopwatch1.strl \
          button-ws1.strl \
          display-ws.strl \
          wristwatch-ws1.strl

WS2_STRL= watch.strl \
          stopwatch2.strl \
          button-ws2.strl \
          display-ws.strl \
          wristwatch-ws2.strl

WA_STRL=  watch.strl \
          alarm.strl \
          button-wa.strl \
          display-wa.strl \
          wristwatch-wa.strl

all : wristwatch-ws1a.c \
      wristwatch-ws2a.c \
      wristwatch-ws1.c \
      wristwatch-ws2.c \
      wristwatch-wa.c

#
# watch, stopwatch1, alarm -> wristwatch-ws1a
#

wristwatch-ws1a.c : ${WS1A_STRL}
	@echo "*** making wristwatch-ws1a 
	$(ESTEREL) ${STRLFLAGS} ${WS1A_STRL} -B wristwatch-ws1a

#
# watch, stopwatch2, alarm -> wristwatch-ws2a
#

wristwatch-ws2a.c : ${WS2A_STRL}
	@echo "*** making wristwatch-ws2a
	$(ESTEREL) ${STRLFLAGS} ${WS2A_STRL} -B wristwatch-ws2a

#
# watch, stopwatch1 -> wristwatch-ws1
#

wristwatch-ws1.c : ${WS1_STRL}
	@echo "*** making wristwatch-ws1
	$(ESTEREL) ${STRLFLAGS} ${WS1_STRL} -B wristwatch-ws1

#
# watch, stopwatch2 -> wristwatch-ws2
#

wristwatch-ws2.c : ${WS2_STRL}
	@echo "*** making wristwatch-ws2
	$(ESTEREL) ${STRLFLAGS} ${WS2_STRL} -B wristwatch-ws2

#
# watch, alarm -> wristwatch-wa
#

wristwatch-wa.c : ${WA_STRL}
	@echo "*** making wristwatch-wa
	$(ESTEREL) ${STRLFLAGS} ${WA_STRL} -B wristwatch-wa

clean :
	 rm -f *.ic *.lc *.oc *.c *.o
