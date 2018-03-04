/* scrun.c v2 */
#ifdef __SIMUL_SCRUN
#include <assert.h>
#ifndef TRACE_ACTION
#include <stdio.h>
#endif
#endif
 

#define __KIND 0
#define __AUX 1
#define __KNOWN 2
#define __DEFAULT_VALUE 3
#define __VALUE 4
#define __ARITY 5
#define __PREDECESSOR_COUNT 6
#define __ACCESS_ARITY  7
#define __ACCESS_COUNT 8
#define __LISTS 9

#define __SIMUL_VALUE 0
#define __SIMUL_KNOWN 1

static int __free_queue_position;
#ifdef __SIMUL_SCRUN
static int __TESTRES__[__NUMBER_OF_NETS__];
#endif
static int __REGVAL[__NUMBER_OF_NETS__];
static int __NUMBER_OF_REGS_KNOWN;


static void __SET_VALUE (netNum, value) 
int netNum; 
int value; {
   int* net = __NET_ARRAY__[netNum];
#ifdef __SIMUL_SCRUN
   if (net[__KNOWN] && net[__KIND] == __SINGLE && net[__VALUE] && value) {
       __SINGLE_SIGNAL_EMITTED_TWICE_ERROR__(net[__AUX]);
   }
#endif
   if (net[__KNOWN]) return;
   net[__KNOWN] =  1;
   switch (net[__KIND]) {
      case __REG:
      case __HALT:
         __REGVAL[netNum] = value;
         __NUMBER_OF_REGS_KNOWN++;
#ifdef TRACE_SCRUN
            fprintf(stderr, "Save register %d with value %d\n", netNum, value);
#endif
         break;
      default:
         net[__VALUE] =  value;
         if (! net[__ACCESS_COUNT]) {
            __QUEUE__[__free_queue_position++] = netNum;
#ifdef TRACE_SCRUN
            fprintf(stderr, "Enqueue net %d with value %d\n", netNum, value);
#endif
         }
   }
}

static void __DECR_ARITY (netNum)
int netNum; {
   int* net = __NET_ARRAY__[netNum];
   if (! (--(net[__PREDECESSOR_COUNT]))) {
      __SET_VALUE(netNum, !net[__DEFAULT_VALUE]);
   }
}

static void __DECR_ACCESS_ARITY (netNum) 
int netNum; {
   int* net = __NET_ARRAY__[netNum];
   if (   ! (--(net[__ACCESS_COUNT])) 
       && net[__KNOWN]) {
      __QUEUE__[__free_queue_position++] = netNum;
#ifdef TRACE_SCRUN
      fprintf(stderr, "Enqueue %d by freeing last access\n", netNum);
#endif
   }
}

static void __SCFOLLOW (netNum, value)
int netNum;
int value; {
   int* net = __NET_ARRAY__[netNum];
   int* lists = net + __LISTS;
   int count;
   int i;  /* list index */
   int followerNum;

#ifdef __SIMUL_SCRUN
   __SIMUL_NET_TABLE__[netNum].known = 1;
   __SIMUL_NET_TABLE__[netNum].value = value;
#endif
#ifdef __SIMUL_SCRUN
   if (net[__KIND] == __TEST) {
       /* set __KNOWN for inputs (one has already __KNOWN==1 for other tests
          when reaching this point. This is only useful to print correctly 
          the causality error message.
       */
       net[__KNOWN] = 1;
   }
#endif
   count = lists[0];
   lists++;
   if (value) {
      for (i=0; i<count; i++) {
         followerNum = lists[0];
         lists++;
         if (! __NET_ARRAY__[followerNum][__KNOWN]) {
            __DECR_ARITY(followerNum);
         }
      }
      count = lists[0];
      lists++;
      for (i=0; i<count; i++) {
         followerNum =lists[0];
         lists++;
         __SET_VALUE(followerNum, 
                     __NET_ARRAY__[followerNum][__DEFAULT_VALUE]);
      }
  } else {
      for (i=0; i<count; i++) {
         followerNum = lists[0];
         lists++;
         __SET_VALUE(followerNum,
                     __NET_ARRAY__[followerNum][__DEFAULT_VALUE]);
      }
      count = lists[0];
      lists++;
      for (i=0; i<count; i++) {
         followerNum = lists[0];
         lists++;
         if (! __NET_ARRAY__[followerNum][__KNOWN]) {
            __DECR_ARITY(followerNum);
         }
      }
   }
   count = lists[0];
   lists++;
   for (i=0; i<count; i++) {
      followerNum = lists[0];
      lists++;
      __DECR_ACCESS_ARITY(followerNum);
   }
}

static int __SCRUN__ () {
   int queuePosition;
   int netNum;
   int* net;
   int value;    /* current net value */
   int testres;  /* result of test action */
   __free_queue_position = __NUMBER_OF_INITIAL_NETS__;

#ifdef TRACE_SCRUN
            fprintf(stderr, "\n***************************\n");
#endif

   /* Reset predecessor counts, access counts, and known flags */
   for (netNum=0; netNum< __NUMBER_OF_NETS__; netNum++) {
      net = __NET_ARRAY__[netNum];
      net[__PREDECESSOR_COUNT] = net[__ARITY];
      net[__ACCESS_COUNT] = net[__ACCESS_ARITY];
      net[__KNOWN] = 0;
#ifdef __SIMUL_SCRUN
      __SIMUL_NET_TABLE__[netNum].known = 0;
      __TESTRES__[netNum] = 0;
#endif
   }
   __NUMBER_OF_REGS_KNOWN = 0;

   /* Run main algorithm */
   for (queuePosition=0; 
        queuePosition < __free_queue_position; 
        queuePosition++) {
      netNum = __QUEUE__[queuePosition];
      net = __NET_ARRAY__[netNum];
      value = net[__VALUE];
#ifdef TRACE_SCRUN
      fprintf(stderr,
              "Step %d : processing net %d value %d\n",
              queuePosition, netNum, value);
#endif

      /* Decode kind and perform action if necessary */
      switch (net[__KIND]) {
         case __STANDARD :
         case __SELECTINC :
         case __SINGLE :   /* TO BE CHANGED FOR SINGLE SIGNAL TEST! */
         case __REG :
         case __HALT :
#ifdef __SIMUL_SCRUN
   __SIMUL_NET_TABLE__[netNum].value = value;
#endif
            __SCFOLLOW(netNum, value);
            break;
         case __RETURN :
#ifdef __SIMUL_SCRUN
            if (value) {
               __AppendToList(__HALT_LIST__, net[__AUX]);
            }
#endif
            __SCFOLLOW(netNum, value);
            break;
         case __SIGTRACE :
#ifdef __SIMUL_SCRUN
            if (value) {
               __AppendToList(__EMITTED_LIST__, net[__AUX]);
           }
#endif
            __SCFOLLOW(netNum, value);
            break;
         case __ACTION :
            if (value) {
               __ACT(net[__AUX]);
            }
            __SCFOLLOW(netNum, value);
            break;
         case __TEST :
            if (value) {
               testres = __TEST_ACT(net[__AUX]);
#ifdef __SIMUL_SCRUN
               __TESTRES__[netNum] = testres;
#endif
            }
            __SCFOLLOW(netNum, value && testres);
            break;
      }
   }                     
         
   /* check that all nets have been explored */ 
   {
      int seen = queuePosition + __NUMBER_OF_REGS_KNOWN;
      int tosee = __NUMBER_OF_NETS__ + __NUMBER_OF_REGISTERS__;
      if (seen != tosee) {
#ifdef __SIMUL_SCRUN
      __CAUSALITY_ERROR__;
#endif
         return -1;
     }
   }
  
   /* Set registers. The computed values were temporarily stored in
                     the auxiliary __REGVAL  array.
                     All the register nums are initially in the queue */

   for (queuePosition=0; 
        queuePosition < __NUMBER_OF_INITIAL_NETS__;
        queuePosition++) {
      netNum = __QUEUE__[queuePosition];
      net = __NET_ARRAY__[netNum];
      switch (net[__KIND]) {
         case __REG :
         case __HALT :
            net[__VALUE] = __REGVAL[netNum];
#ifdef TRACE_SCRUN
            fprintf(stderr, "Register %d set to %d\n", 
                            netNum, 
                            __REGVAL[netNum]);
#endif
#ifdef __SIMUL_SCRUN
            if (net[__KIND] == __HALT &&net[__VALUE]) {
               __AppendToList(__HALT_LIST__, net[__AUX]);
           }
#endif
            break;
        default:
            break;
        }
   }
   return 0;
}


static void __SCRESET__ () {
#ifdef __SIMUL_SCRUN
   int netNum;
   for (netNum=0; netNum < __NUMBER_OF_NETS__; netNum++) {
      __SIMUL_NET_TABLE__[netNum].known = 1;
      __SIMUL_NET_TABLE__[netNum].value = 0;
   }
#endif
}


