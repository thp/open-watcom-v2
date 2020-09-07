/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  Message resource handling.
*
****************************************************************************/


#include "as.h"
#include "wreslang.h"

#ifdef _STANDALONE_

#ifdef __WATCOMC__
    #include <process.h>
#endif
#include "wressetr.h"
#include "wresset2.h"

#include "clibext.h"

#else

#define TXT_MSG_LANG_SPACING    (ABS_REF_NOT_ALLOWED - MSG_AS_BASE + 1)

// No res file to use. Just compile in the messages...
static char *asMessages[] = {
    #define pick( id, e_msg, j_msg )    e_msg,
    #include "as.msg"
    #undef pick
#if 0
//#if defined( JAPANESE )
    #define pick( id, e_msg, j_msg )    j_msg,
    #include "as.msg"
    #undef pick
#endif
};

#define TXT_MSG_SIZE    ArraySize( asMessages )

#endif

static unsigned         msgShift;

#ifdef _STANDALONE_

static HANDLE_INFO      hInstance = {0};

#endif

bool AsMsgInit( void )
//********************
{
#ifdef _STANDALONE_
    char        name[_MAX_PATH];

    hInstance.status = 0;
    if( _cmdname( name ) != NULL && OpenResFile( &hInstance, name ) ) {
        msgShift = _WResLanguage() * MSG_LANG_SPACING;
        if( AsMsgGet( MSG_AS_BASE, AsResBuffer ) ) {
            return( true );
        }
    }
    CloseResFile( &hInstance );
    printf( NO_RES_MESSAGE );
    return( false );
#else
    msgShift = _WResLanguage() * TXT_MSG_LANG_SPACING;
    if( msgShift >= TXT_MSG_SIZE )
        msgShift = 0;
    msgShift -= MSG_AS_BASE;
    return( true );
#endif
}

bool AsMsgGet( int resourceid, char *buffer )
//*******************************************
{
#ifdef _STANDALONE_
    if( hInstance.status == 0 || WResLoadString( &hInstance, resourceid + msgShift, (lpstr)buffer, MAX_RESOURCE_SIZE ) <= 0 ) {
        buffer[0] = '\0';
        return( false );
    }
#else
    strcpy( buffer, asMessages[resourceid + msgShift] );
#endif
    return( true );
}

void AsMsgFini( void ) {
//**********************

#ifdef _STANDALONE_
    CloseResFile( &hInstance );
#endif
}
