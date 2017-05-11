/*
htop - dragonflybsd/DragonFlyBSDCRT.c
(C) 2014 Hisham H. Muhammad
(C) 2017 Diederik de Groot
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "config.h"
#include "CRT.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_EXECINFO_H
#include <execinfo.h>
#endif

void CRT_handleSIGSEGV(int sgn) {
   (void) sgn;
   CRT_done();
   fprintf(stderr, "\n\nhtop " VERSION " aborting. Please visit http://hisham.hm/htop\n");
   fprintf(stderr, "\n\nor report a bug at https://github.com/hishamhm/htop/issues\n");
   #ifdef HAVE_EXECINFO_H
   size_t size = backtrace(backtraceArray, sizeof(backtraceArray) / sizeof(void *));
   fprintf(stderr, "\n Please include in your report the following backtrace: \n");
   backtrace_symbols_fd(backtraceArray, size, 2);
   fprintf(stderr, "\nAdditionally, in order to make the above backtrace useful,");
   fprintf(stderr, "\nplease also run the following command to generate a disassembly of your binary:");
   fprintf(stderr, "\n\n   objdump -d `which htop` > ~/htop.objdump");
   fprintf(stderr, "\n\nand then attach the file ~/htop.objdump to your bug report.");
   fprintf(stderr, "\n\nThank you for helping to improve htop!\n\n");
   #else
   fprintf(stderr, "\nPlease contact your DragonFlyBSD package maintainer!\n\n");
   #endif
   abort();
}

