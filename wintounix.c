/****************************************************************************
 *
 *    Copyright (C) 2015  Peter W. Draper (p.w.draper@durham.ac.uk)
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ****************************************************************************/
/*+
=pod

=head1 NAME

wintounix

=head1 SYNOPSIS

wintounix filetime

=head1 DESCRIPTION

Convert a Windows FILETIME counter to the UNIX epoch (seconds since 1970).

Under Win32 platforms, file times are maintained primarily in the form of a
64-bit FILETIME structure, which represents the number of 100-nanosecond
intervals since January 1, 1601 UTC (coordinate universal time).

=head1 AUTHOR

Peter W. Draper: 23-FEB-2015

Durham University

=cut

-*/

/*  Include files */
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/*  Maximum length of time string. */
#define BUFLEN 64

/*  Windows ticks are nano seconds. */
#define WINDOWS_TICK 10000000LL

/*  Windows seconds from UNIX epoch. */
#define SEC_TO_UNIX_EPOCH 11644473600LL

/**
 *  Main routine.
 */
int main( int argc, char *argv[] )
{
    time_t unixticks;              /*  Seconds since the UNIX epoch */
    unsigned long long winticks;   /*  Nano secs in windows */

    /*  Get the command-line value. */
    if ( argc != 2 ) {
        printf( "Usage: %s filetime\n", argv[0] );
        return 1;
    }
    if ( sscanf( argv[1], "%llu", &winticks ) == 0 ) {
        printf( "Usage: %s filetime\n", argv[0] );
        return 1;
    }

    /*  Ignore domain issue (post 2038 dates). */
    unixticks = (time_t) winticks / WINDOWS_TICK - SEC_TO_UNIX_EPOCH;

    printf( "Unix epoch = %ld\n", unixticks );

    return 0;
}
