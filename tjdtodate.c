/****************************************************************************
 *
 *    Copyright (C) 2010  Peter W. Draper (p.w.draper@durham.ac.uk)
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

tjdtodate

=head1 SYNOPSIS

tjdtodate tjd

=head1 DESCRIPTION

Converts a Pan-STARRS truncated MJD into a UT date.

=head1 AUTHOR

Peter W. Draper: 10-JUN-2010 

Durham University

=cut

*/

/*  Include files */
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/*  Date of the Unix epoch as a Modified Julian Date. */
#define MJD_EPOCH 40587

/*  Number of seconds per day. */
#define SECS_PER_DAY (60 * 60 * 24)

/*  Maximum length of time string. */
#define BUFLEN 64

/**
 *  Main routine.
 */
int main( int argc, char *argv[] )
{
    char buffer[BUFLEN];           /*  Formatted time buffer */
    int mjd;                       /*  Modified Julian Date */
    int tjd;                       /*  Pan-STARRS Truncated Julian Date */
    struct tm *utc;                /*  UTC time struct */
    time_t unixsecs;               /*  Seconds since the UNIX epoch */

    /*  Get the command-line value. */
    if ( argc != 2 ) {
        printf( "Usage: %s tjd\n", argv[0] );
        return 1;
    }
    if ( sscanf( argv[1], "%d", &tjd ) == 0 ) {
        printf( "Usage: %s tjd\n", argv[0] );
        return 1;
    }

    /*  Convert to MJD, for Pan-STARRS epochs. */
    mjd = tjd + 50000;

    /*  Seconds since the UNIX epoch. */
    unixsecs = ( mjd - MJD_EPOCH ) * SECS_PER_DAY;

    /*  Get the UTC. */
    utc = gmtime( &unixsecs );

    /*  Convert into YYYYMMDD format and print. */
    strftime( buffer, BUFLEN, "%Y%m%d", utc );
    printf( "%s\n", buffer );

    return 0;
}
