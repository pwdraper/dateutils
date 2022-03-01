/****************************************************************************
 *
 *    Copyright (C) 2011  Peter W. Draper (p.w.draper@durham.ac.uk)
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

datetounix

=head1 SYNOPSIS

datetounix now

datetounix <date_and_time>

=head1 DESCRIPTION

Converts a UT date and time or the current second ("now") into the number of
seconds in the UNIX epoch.

If given the date and time should be in "YYYY-MM-DD HH:MM:SS.SS" format.

=head1 AUTHOR

Peter W. Draper: 10-JUN-2011

Durham University

=cut

-*/

/*  Include files */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/**
 *  Main routine.
 */
int main( int argc, char *argv[] )
{
    time_t unixsecs;               /*  Seconds since the UNIX epoch */
    struct tm utc;                 /*  UTC time struct */

    /*  Get the command-line value. */
    if ( argc != 2 ) {
        printf( "Usage: %s now\n" 
                "       %s 'YYYY-MM-DD HH:MM:SS.SS'\n", argv[0], argv[0] );
        return 1;
    }

    /*  Do we want "now"? */
    if ( strncmp( argv[1], "now", 3 ) == 0 ) {

        /*  Seconds of the UNIX epoch. */
        unixsecs = time( NULL );
    }
    else {
        /*  Convert formatted time into a struct. */
        if ( strptime( argv[1], "%Y-%m-%d %H:%M:%S", &utc ) == NULL ) {
            printf( "Failed to convert date (%s)\n", argv[1] );
            return 1;
        }

        /*  Seconds since the UNIX epoch. */
        unixsecs = timegm( &utc );
    }

    /*  Get UNIX ticks. */
    printf( "Unix ticks = %ld\n", unixsecs );
    return 0;
}
