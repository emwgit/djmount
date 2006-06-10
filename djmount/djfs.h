/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* $Id$
 *
 * djfs : file system implementation for djmount.
 * This file is part of djmount.
 *
 * (C) Copyright 2005 R�mi Turboult <r3mi@users.sourceforge.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */



#ifndef DJFS_H_INCLUDED
#define DJFS_H_INCLUDED 1

#include <fuse.h>
#include "vfs.h"



/******************************************************************************
 * @var DJFS
 *      This opaque type encapsulates access to a djfs file system.
 *      This type is derived from the "VFS" type : all VFS_* methods
 *      can be used on DJFS.
 *
 *      NOTE THAT THE FUNCTION API IS NOT THREAD SAFE. Callers should
 *      take care of the necessary locks if an object is shared between
 *      multiple threads.
 *
 *****************************************************************************/

OBJECT_DECLARE_CLASS(DJFS,VFS);



/*****************************************************************************
 * Flags for DJFS_Create
 *****************************************************************************/
typedef enum _DJFS_Flags {
	
	DJFS_SHOW_DEBUG    = 01, // show debug directory
	DJFS_USE_PLAYLISTS = 02, // use playlists for AV files (default: files)
	DJFS_SHOW_METADATA = 04, // show XML files containing DIDL metadata
	
} DJFS_Flags;


/*****************************************************************************
 * @fn 		DJFS_Create
 * @brief	create a djfs file system object.
 *
 *****************************************************************************/
DJFS*
DJFS_Create (void* talloc_context, DJFS_Flags flags);



/*****************************************************************************
 * @fn		_DJFS_BrowseCDS
 * @brief	browse the ContentDirectory service associated to a UPnP device
 *
 *	path must be an absolute, canonical, path.
 *	DIDL-Lite containers titles are interpreted as directories names.
 *	It is left to the caller to interpret DIDL-Lite items / file names
 *	so this function returns when the current path part matches an item,
 *	or does not match anything.
 *
 * 	Result should be freed using "talloc_free" when finished.
 *
 *	Note: this function is used internaly by "djfs" ; it is exported 
 *	for testing purposes only.
 *
 *****************************************************************************/
const struct _ContentDir_BrowseResult*
_DJFS_BrowseCDS (void* result_context,
		 const char* deviceName, const char* path,
		 size_t* nb_char_matched);



#endif // DJFS_H_INCLUDED

