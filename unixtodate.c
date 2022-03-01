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

unixtodate

=head1 SYNOPSIS

unixtodate now

unixtodate <date_and_time>

=head1 DESCRIPTION

Convert a UNIX epoch (seconds since 1970) into a UT date and time.

=head1 AUTHOR

Peter W. Draper: 10-JUN-2011

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

/**
 *  Main routine.
 */
int main( int argc, char *argv[] )
{
    char buffer[BUFLEN];           /*  Formatted time buffer */
    double tmp;                    /*  Seconds value from command-line */
    struct tm *utc;                /*  UTC time struct */
    time_t unixsecs;               /*  Seconds since the UNIX epoch */

    /*  Get the command-line value. */
    if ( argc != 2 ) {
        printf( "Usage: %s unixsecs\n", argv[0] );
        return 1;
    }
    if ( sscanf( argv[1], "%lf", &tmp ) == 0 ) {
        printf( "Usage: %s unixsecs\n", argv[0] );
        return 1;
    }

    /*  Put this cast off since we don't know the type of time_t for the above
     *  format. */
    unixsecs = (time_t) tmp;

    /*  Get the UTC. */
    utc = gmtime( &unixsecs );

    /*  Convert into ISO 8601 date and time and print. */
    strftime( buffer, BUFLEN, "%Y-%m-%dT%H:%M:%S", utc );
    printf( "%s\n", buffer );

    return 0;
}
