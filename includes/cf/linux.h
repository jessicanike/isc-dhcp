/* linux.h

   System dependencies for Linux.

   Based on a configuration originally supplied by Jonathan Stone. */

/*
 * Copyright (c) 1996-1999 Internet Software Consortium.
 * Use is subject to license terms which appear in the file named
 * ISC-LICENSE that should have accompanied this file when you
 * received it.   If a file named ISC-LICENSE did not accompany this
 * file, or you are not sure the one you have is correct, you may
 * obtain an applicable copy of the license at:
 *
 *             http://www.isc.org/isc-license-1.0.html. 
 *
 * This file is part of the ISC DHCP distribution.   The documentation
 * associated with this file is listed in the file DOCUMENTATION,
 * included in the top-level directory of this release.
 *
 * Support and other services are available for ISC products - see
 * http://www.isc.org for more information.
 */

#include <features.h>
#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__
#undef __USE_BSD
typedef char int8_t;
typedef short int16_t;
typedef long int32_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned long u_int32_t;
#endif /* __BIT_TYPES_DEFINED__ */

typedef u_int8_t u8;
typedef u_int16_t u16;
typedef u_int32_t u32;

#include <syslog.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <limits.h>

extern int h_errno;

#include <net/if.h>
#include <net/route.h>

#if LINUX_MAJOR == 1
# include <linux/if_arp.h>
# include <linux/time.h>		/* also necessary */
#else
# include <net/if_arp.h>
#endif

#include <sys/time.h>		/* gettimeofday()*/

/* Databases go in /var/state/dhcp.   It would also be valid to put them
   in /var/state/misc - indeed, given that there's only one lease file, it
   would probably be better.   However, I have some ideas for optimizing
   the lease database that may result in a _lot_ of smaller files being
   created, so in that context it makes more sense to have a seperate
   directory. */

#ifndef _PATH_DHCPD_DB
#define _PATH_DHCPD_DB		"/var/state/dhcp/dhcpd.leases"
#endif

#ifndef _PATH_DHCLIENT_DB
#define _PATH_DHCLIENT_DB	"/var/state/dhcp/dhclient.leases"
#endif

/* Varargs stuff... */
#include <stdarg.h>
#define VA_DOTDOTDOT ...
#define VA_start(list, last) va_start (list, last)
#define va_dcl

#define vsnprintf(buf, size, fmt, list) vsprintf (buf, fmt, list)
#define NO_SNPRINTF

#define VOIDPTR	void *

#define EOL	'\n'

/* Time stuff... */

#include <time.h>

#define TIME time_t
#define GET_TIME(x)	time ((x))

#if (LINUX_MAJOR >= 2)
# if (LINUX_MINOR >= 1)
#  if defined (USE_DEFAULT_NETWORK)
#   define USE_LPF
#  endif
#  define LINUX_SLASHPROC_DISCOVERY
#  define PROCDEV_DEVICE "/proc/net/dev"
#  define HAVE_ARPHRD_TUNNEL
#  define HAVE_TR_SUPPORT
# endif
# define HAVE_ARPHRD_METRICOM
# define HAVE_ARPHRD_IEEE802
# define HAVE_ARPHRD_LOOPBACK
# define HAVE_SO_BINDTODEVICE
# define HAVE_SIOCGIFHWADDR
# define HAVE_SETFD
#endif

#if !defined (USE_LPF)
# if defined (USE_DEFAULT_NETWORK)
#  define USE_SOCKETS
# endif
# define IGNORE_HOSTUNREACH
#endif

#define ALIAS_NAMES_PERMUTED
#define SKIP_DUMMY_INTERFACES

#ifdef NEED_PRAND_CONF
#ifndef HAVE_DEV_RANDOM
 # define HAVE_DEV_RANDOM 1
 #endif /* HAVE_DEV_RANDOM */

const char *cmds[] = {
	"/bin/ps -axlw 2>&1",
	"/sbin/arp -an 2>&1",
	"/bin/netstat -an 2>&1",
	"/bin/df  2>&1",
	"/usr/bin/dig com. soa +ti=1 +retry=0 2>&1",
	"/usr/bin/uptime  2>&1",
	"/bin/netstat -s 2>&1",
	"/usr/bin/dig . soa +ti=1 +retry=0 2>&1",
	"/usr/bin/vmstat  2>&1",
	"/usr/bin/w  2>&1",
	NULL
};

const char *dirs[] = {
	"/tmp",
	"/usr/tmp",
	".",
	"/",
	"/var/spool",
	"/dev",
	"/var/spool/mail",
	"/home",
	"/usr/home",
	NULL
};

const char *files[] = {
	"/proc/stat",
	"/proc/rtc",
	"/proc/meminfo",
	"/proc/interrupts",
	"/proc/self/status",
	"/var/log/messages",
	"/var/log/wtmp",
	"/var/log/lastlog",
	NULL
};
#endif /* NEED_PRAND_CONF */
