/*
 * mad - MPEG audio decoder
 * Copyright (C) 2000-2001 Robert Leslie
 *
 *  This file is part of AlsaPlayer.
 *
 *  AlsaPlayer is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AlsaPlayer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

# ifndef XING_H
# define XING_H

# include <mad.h>

struct xing {
  long flags;			/* valid fields (see below) */
  unsigned long blocks;		/* total number of blocks */
  unsigned long bytes;		/* total number of bytes */
  unsigned char toc[100];	/* 100-point seek table */
  long scale;			/* ?? */
};

enum {
  XING_BLOCKS = 0x00000001L,
  XING_BYTES  = 0x00000002L,
  XING_TOC    = 0x00000004L,
  XING_SCALE  = 0x00000008L
};

void xing_init(struct xing *);

# define xing_finish(xing)	/* nothing */

int xing_parse(struct xing *, struct mad_bitptr, unsigned int);

# endif
