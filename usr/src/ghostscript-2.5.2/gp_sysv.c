/* Copyright (C) 1992 Aladdin Enterprises.  All rights reserved.
   Distributed by Free Software Foundation, Inc.

This file is part of Ghostscript.

Ghostscript is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility
to anyone for the consequences of using it or for whether it serves any
particular purpose or works at all, unless he says so in writing.  Refer
to the Ghostscript General Public License for full details.

Everyone is granted permission to copy, modify and redistribute
Ghostscript, but only under the conditions described in the Ghostscript
General Public License.  A copy of this license is supposed to have been
given to you along with Ghostscript so you can know your rights and
responsibilities.  It should be in a file named COPYING.  Among other
things, the copyright notice and this notice must be preserved on all
copies.  */

/* gp_sysv.c */
/* System V Unix-specific routines for Ghostscript */

/* This file contains a couple of standard Unix library procedures */
/* that a few System V platforms don't provide. */
#include <errno.h>
#include "time_.h"
#include <sys/types.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <sys/param.h>

extern long timezone;		/* doesn't seem to be declared anywhere */

/* rename */
int
rename(char *a, char *b)
{	if  (access(a, 0) == -1 )
		return(-1);
	unlink(b);
	if ( link(a, b) == -1 )
		return(-1);
	if ( unlink(a) == -1 )
	{	unlink(b);		/* ??? */
		return(-1);
	}
	return(0);
}

/* gettimeofday */
#ifndef HZ
#  define	HZ	100		/* see sys/param.h */
#endif
int
gettimeofday(struct timeval *tvp, struct timezone *tzp)
{	struct tms tms;
	static long offset = 0;
	long ticks;

	if (!offset)
	{	time(&offset);
		/* call localtime to set the timezone variable */
		localtime(&offset);
		offset -= (times(&tms) / HZ);
	}
	ticks = times(&tms);
	tvp->tv_sec = ticks/HZ + offset;
	tvp->tv_usec = (ticks % HZ) * (1000*1000/HZ);
	tzp->tz_minuteswest = timezone/60;
}
