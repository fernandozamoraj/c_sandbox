#include<stdio.h>
#include "consts.h"
/*
I found this gem at the link below
http://www.trynull.com/2011/10/16/conditional-printf-debug-statements-in-c-based-programming-languages/

*/
#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DEBUGLOG(ARGS...) printf(ARGS)
#else
#define DEBUGLOG(ARGS...) do{}while(0)
#endif

#endif