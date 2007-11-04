/*
 * ttalib.h
 *
 * Description:	 TTAv1 player library prototypes
 * Developed by: Alexander Djourik <sasha@iszf.irk.ru>
 *               Pavel Zhilin <pzh@iszf.irk.ru>
 *
 * Copyright (c) 1999-2004 Alexander Djourik. All rights reserved.
 *
 */

/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Please see the file COPYING in this directory for full copyright
 * information.
 */

#ifndef TTALIB_H_
#define TTALIB_H_

//#define _BIG_ENDIAN
#define MAX_BPS         24	// Max supported Bit resolution
#define MAX_NCH         8	// Max supported number of channels

// return codes
#define NO_ERROR        0
#define OPEN_ERROR      1	// Can't open file
#define FORMAT_ERROR    2	// Unknown TTA format version
#define PLAYER_ERROR    3	// Not supported file format
#define FILE_ERROR      4	// File is corrupted
#define READ_ERROR      5	// Can't read from file
#define MEMORY_ERROR    6	// Insufficient memory available

#define FRAME_TIME		1.04489795918367346939
#define SEEK_STEP		(int)(FRAME_TIME * 1000)

#define ISO_BUFFER_LENGTH	(1024*32)
#define ISO_NBUFFERS		(8)
#define ISO_BUFFERS_SIZE	(ISO_BUFFER_LENGTH*ISO_NBUFFERS)
#define PCM_BUFFER_LENGTH	(4608)

typedef struct {
	FILE            *HANDLE;	// file handle
	unsigned short  NCH;		// number of channels
	unsigned short  BPS;		// bits per sample
	unsigned short  BSIZE;		// byte size
	unsigned short  FORMAT;		// audio format
	unsigned long   SAMPLERATE;	// samplerate (sps)
	unsigned long   DATALENGTH;	// data length in samples
	unsigned long   FRAMELEN;	// frame length
	unsigned long   LENGTH;		// playback time (sec)
	unsigned long   STATE;		// return code
	unsigned long   DATAPOS;	// size of ID3v2 header
} tta_info;

/*********************** Library functions *************************/

#ifdef  LIBTEST
#ifndef DPRINTF
#define DPRINTF(x) fprintf(stderr, (x))
#endif /* DPRINTF */

static void tta_error (int error) {
	DPRINTF("TTA Decoder Error - ");
	switch (error) {
	case OPEN_ERROR:	DPRINTF("Can't open file\n"); break;
	case FORMAT_ERROR:	DPRINTF("Not supported file format\n"); break;
	case FILE_ERROR:	DPRINTF("File is corrupted\n"); break;
	case READ_ERROR:	DPRINTF("Can't read from file\n"); break;
	case MEMORY_ERROR:	DPRINTF("Insufficient memory available\n"); break;
	}
}
#endif /* LIBTEST */

long    open_tta_file (		// FUNCTION: opens TTA file
        const char *filename,	// file to open
        tta_info *info,		// file info structure
        unsigned long offset);	// ID3v2 header size
/*
 * RETURN VALUE
 * This function returns 0 if success. Otherwise, -1 is  returned
 * and the variable STATE of the currently using info structure
 * is set to indicate the error.
 *
 */

void    close_tta_file (	// FUNCTION: closes currently playing file
        tta_info *info);	// file info structure

long    set_position (		// FUNCTION: sets playback position
        unsigned long pos);	// seek position = seek_time_ms / SEEK_STEP
/*
 * RETURN VALUE
 * This function returns 0 if success. Otherwise, -1 is  returned
 * and the variable STATE of the currently using info structure
 * is set to indicate the error.
 *
 */

long    player_init (		// FUNCTION: initializes TTA player
        tta_info *info);	// file info structure
/*
 * RETURN VALUE
 * This function returns 0 if success. Otherwise, -1 is  returned
 * and the variable STATE of the currently using info structure
 * is set to indicate the error.
 *
 */

void    player_stop (void);	// FUNCTION: destroys memory pools

long    get_samples (		// FUNCTION: decode PCM_BUFFER_LENGTH samples
        unsigned char *buffer);	// into the current PCM buffer position
/*
 * RETURN VALUE
 * This function returns the number of samples successfully decoded.
 * Otherwise, -1 is  returned and the variable STATE of the currently
 * using info structure is set to indicate the error.
 *
 */

long	get_bitrate (void);	// RETURN VALUE: TTA dynamic bitrate

#endif /* TTALIB_H_ */

