/*
 *  CRL reading application
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: GPL-2.0
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_printf          printf
#define mbedtls_exit            exit
#define MBEDTLS_EXIT_SUCCESS    EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE    EXIT_FAILURE
#endif /* MBEDTLS_PLATFORM_C */

#if !defined(MBEDTLS_BIGNUM_C) || !defined(MBEDTLS_RSA_C) ||  \
    !defined(MBEDTLS_X509_CRL_PARSE_C) || !defined(MBEDTLS_FS_IO)
int main( void )
{
    mbedtls_printf("MBEDTLS_BIGNUM_C and/or MBEDTLS_RSA_C and/or "
           "MBEDTLS_X509_CRL_PARSE_C and/or MBEDTLS_FS_IO not defined.\n");
    return( 0 );
}
#else

#include "mbedtls/x509_crl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DFL_FILENAME            "crl.pem"
#define DFL_DEBUG_LEVEL         0

#define USAGE \
    "\n usage: crl_app param=<>...\n"                   \
    "\n acceptable parameters:\n"                       \
    "    filename=%%s         default: crl.pem\n"      \
    "\n"

#if defined(MBEDTLS_CHECK_PARAMS)
#define mbedtls_exit            exit
void mbedtls_param_failed( const char *failure_condition,
                           const char *file,
                           int line )
{
    mbedtls_printf( "%s:%i: Input param failed - %s\n",
                    file, line, failure_condition );
    mbedtls_exit( MBEDTLS_EXIT_FAILURE );
}
#endif

/*
 * global options
 */
struct options
{
    const char *filename;       /* filename of the certificate file     */
} opt;

int main( int argc, char *argv[] )
{
    int ret = 1;
    int exit_code = MBEDTLS_EXIT_FAILURE;
    unsigned char buf[100000];
    mbedtls_x509_crl crl;
    int i;
    char *p, *q;

    /*
     * Set to sane values
     */
    mbedtls_x509_crl_init( &crl );

    if( argc == 0 )
    {
    usage:
        mbedtls_printf( USAGE );
        goto exit;
    }

    opt.filename            = DFL_FILENAME;

    for( i = 1; i < argc; i++ )
    {
        p = argv[i];
        if( ( q = strchr( p, '=' ) ) == NULL )
            goto usage;
        *q++ = '\0';

        if( strcmp( p, "filename" ) == 0 )
            opt.filename = q;
        else
            goto usage;
    }

    /*
     * 1.1. Load the CRL
     */
    mbedtls_printf( "\n  . Loading the CRL ..." );
    fflush( stdout );

    ret = mbedtls_x509_crl_parse_file( &crl, opt.filename );

    if( ret != 0 )
    {
        mbedtls_printf( " failed\n  !  mbedtls_x509_crl_parse_file returned %d\n\n", ret );
        mbedtls_x509_crl_free( &crl );
        goto exit;
    }

    mbedtls_printf( " ok\n" );

    /*
     * 1.2 Print the CRL
     */
    mbedtls_printf( "  . CRL information    ...\n" );
    ret = mbedtls_x509_crl_info( (char *) buf, sizeof( buf ) - 1, "      ", &crl );
    if( ret == -1 )
    {
        mbedtls_printf( " failed\n  !  mbedtls_x509_crl_info returned %d\n\n", ret );
        mbedtls_x509_crl_free( &crl );
        goto exit;
    }

    mbedtls_printf( "%s\n", buf );

    exit_code = MBEDTLS_EXIT_SUCCESS;

exit:
    mbedtls_x509_crl_free( &crl );

#if defined(_WIN32)
    mbedtls_printf( "  + Press Enter to exit this program.\n" );
    fflush( stdout ); getchar();
#endif

    return( exit_code );
}
#endif /* MBEDTLS_BIGNUM_C && MBEDTLS_RSA_C && MBEDTLS_X509_CRL_PARSE_C &&
          MBEDTLS_FS_IO */
