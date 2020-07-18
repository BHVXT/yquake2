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
 * Gangsters
 *
 * =======================================================================
 */
 
#include "../../header/local.h"
#include "gangsters.h"

/* TODO: define functions 
 *
 * mframe_t stc_gangster_frames_stand[] = {
	 {ai_walk, 0, NULL},
	 {ai_walk, 0, NULL},
	 {ai_walk, 0, NULL},
	 {ai_walk, 0, NULL},
 * }
 * 
 * mmove_t stc_gangster_move_stand =
 * {
 *		beginning frame, 
 *		ending frame,
 *		mframe_t set,
 *		mmove_t set to move back to
 * }
 *
 * void
 * stc_gangster_stand(edict_t *self)
 */
 
/* still not sure on this name yet..... */
void
SP_stc_monster_gangster_template(edict_t *self) 
{
	if (!self) /* still not sure what this thing does */
	{
		return;
	}
	
	/* Perhaps swap out different models per strength? */
	self->s.modelindex = gi.modelindex("models/monsters/gangsters/tris.md2");
	
	/* TODO: add sound effects */
	
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);
	
	self->health = 40;
	self->gibhealth = -2000; /* disabling gibs due to more violent content being unfitting */
	self->mass = 200;
	
	self->pain = stc_gangster_pain;
	self->die = stc_gangster_downed;
	
	self->monsterinfo.stand = stc_gangster_stand;
	self->monsterinfo.walk = stc_gangster_walk; /* what is the difference between walk and run? */
	self->monsterinfo.run = stc_gangster_run;
	self->monsterinfo.dodge = NULL; /* how so? */
	self->monsterinfo.attack = stc_gangster_gun; /* laser beam? */
	self->monsterinfo.melee = stc_gangster_melee;
	self->monsterinfo.sight = stc_gangster_sight;
	self->monsterinfo.idle = stc_gangster_idle;
	
	gi.linkentity(self);
	
	self->monsterinfo.currentmove = /* what does this mean? */
	self->monsterinfo.scale = MODEL_SCALE;
	
	walkmonster_start(self);
}

/* 
 * The general plan is to add a few color-coded
 * enemies. Not anything particular per different
 * skins on the same model, just to make things more
 * varied. Any alterations would probably be achieved
 * with the gi.modelindex command.
 */