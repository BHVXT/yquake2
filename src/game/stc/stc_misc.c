/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 * Copyright (C) 2020 Brendan H.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Test entities
 *
 * =======================================================================
 */
 
#include "../header/local.h"
 
 

/* ===================================================== */

/*
 * kirkton
 */
void
stc_misc_kirkton_think(edict_t *self)
{
	if (!self)
	{
		return;
	}

	self->s.frame++;

	if (self->s.frame < 38)
	{
		self->nextthink = level.time + FRAMETIME;
	}
}

void
stc_misc_kirkton_use(edict_t *self, edict_t *other /* unused */, edict_t *activator /* unused */)
{
	if (!self)
	{
		return;
	}

	self->s.frame = 0;
	self->think = stc_misc_kirkton_think;
	self->nextthink = level.time + FRAMETIME;
}

void
SP_stc_misc_kirkton(edict_t *self)
{
	if (!self)
	{
		return;
	}

	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_BBOX;
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);
	self->s.modelindex = gi.modelindex("models/misc/kirkton/tris.md2");
	self->use = stc_misc_kirkton_use;
	gi.linkentity(self);
}