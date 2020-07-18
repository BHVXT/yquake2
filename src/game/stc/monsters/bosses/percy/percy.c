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
 * Percy
 *
 * =======================================================================
 */
 
#include "../../../../header/local.h"
#include "percy.h"

static int sound_tommy;

/* TODO: define functions 
 *
 * mframe_t percy_frames_stand[] = {
	 {ai_walk, 0, NULL},
	 {ai_walk, 0, NULL},
	 {ai_walk, 0, NULL},
	 {ai_walk, 0, NULL},
 * }
 * 
 * mmove_t percy_move_stand =
 * {
 *		beginning frame, 
 *		ending frame,
 *		mframe_t set,
 *		mmove_t set to move back to
 * }
 *
 * void
 * percy_stand(edict_t *self)
 */

mframe_t percy_frames_stand[] = {
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL}, /* 10 */
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL}, /* 20 */
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL}, /* 30 */
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL}, /* 40 */
	 {ai_stand, 0, NULL}
};

mmove_t percy_move_stand =
{
	FRAME_stand_01,
	FRAME_stand_41,
	percy_frames_stand,
	NULL /* nothing to go back to */
};

void
percy_stand(edict_t *self)
{
	if (!self)
	{
		return;
	}
	
	self->monsterinfo.currentmove = &percy_move_stand;
}

mframe_t percy_frames_run[] = {
	 {ai_run, 15, NULL},
	 {ai_run, 5, NULL},
	 {ai_run, 5, NULL},
	 {ai_run, 15, NULL},
	 {ai_run, 5, NULL},
	 {ai_run, 5, NULL}
};

mmove_t percy_move_run =
{
	FRAME_run01,
	FRAME_run06,
	percy_frames_run,
	NULL
};
 
void
percy_run(edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
	{
		self->monsterinfo.currentmove = &percy_move_stand;
	}
	else
	{
		self->monsterinfo.currentmove = &percy_move_run;
	}
}

void
percy_down(edict_t *self)
{
	if (!self)
	{
		return;
	}
	
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	gi.linkentity(self);
}

mframe_t percy_frames_downed[] = {
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL}, /* 10 */
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
};

mmove_t percy_move_downed =
{
	FRAME_downed01,
	FRAME_downed13,
	percy_frames_downed,
	percy_down
};

void
percy_downed(edict_t *self, edict_t *inflictor, edict_t *attacker,
	int damage, vec3_t point)
{
	if (!self)
	{
		return;
	}
	
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	/* s.skinnum command is placed here */
	
	self->monsterinfo.currentmove = &percy_move_downed;
	/* sound is placed here */
}

void
PercyTommyFire(edict_t *self)
{
	vec3_t dir;
	vec3_t vec;
	vec3_t start;
	vec3_t forward, right;
	
	int flash_number;
	
	if (!self)
	{
		return;
	}
	
	flash_number = MZ2_PERCY_BLASTER_6;
	
	AngleVectors(self->s.angles, forward, right, NULL);
	G_ProjectSource(self->s.origin, monster_flash_offset[flash_number],
		forward, right, start);
		
	VectorSubtract(self->pos1, start, dir);
	VectorNormalize(dir);
	
	monster_fire_blaster(self, start, forward, 15, 1000, 
		flash_number, EF_BLASTER);
}

mframe_t percy_frames_tommy[] = {
	 {ai_charge, 0, NULL},
	 {ai_charge, 0, NULL},
	 {ai_charge, 0, NULL},
	 {ai_charge, 0, NULL},
	 {ai_move, 0, PercyTommyFire},
	 {ai_move, 0, PercyTommyFire},
	 {ai_move, 0, PercyTommyFire},
	 {ai_move, 0, PercyTommyFire},
	 {ai_move, 0, NULL},
	 {ai_move, 0, NULL}, /* 10 */
	 {ai_move, 0, NULL},
	 {ai_move, 0, NULL},
	 {ai_move, 0, NULL},
};

mmove_t percy_move_tommy =
{
	FRAME_attack_leadup01,
	FRAME_attack_down06,
	percy_frames_tommy,
	percy_run
};

void
percy_tommy(edict_t *self)
{
	if (!self)
	{
		return;
	}
	
	self->monsterinfo.currentmove = &percy_move_tommy;
}

void
percy_sight(edict_t *self)
{
	if (!self)
	{
		return;
	}
	
	self->monsterinfo.currentmove = &percy_move_run;
}

mframe_t percy_frames_pain[] = {
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL}, /* 10 */
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
	 {ai_stand, 0, NULL},
};

mmove_t percy_move_pain =
{
	FRAME_pain01,
	FRAME_pain18,
	percy_frames_pain,
	percy_run
};

void
percy_pain(edict_t *self, edict_t *other, float kick, int damage)
{
	float n;
	
	if (!self)
	{
		return;
	}
	
	n = random();
	
	if (n < 0.7);
	{
		return;
	}
	self->monsterinfo.currentmove = &percy_move_pain;
}

/* void
percy_idle(edict_t *self) */

void
SP_stc_boss_percy(edict_t *self)
{
	if (!self) /* still not sure what this thing does */
	{
		return;
	}
	
	if(deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}
	
	/* TODO: add sound effects */
	
	sound_tommy = gi.soundindex("makron/blaster.wav"); /* placeholder until I can get a laser sound effect */
	
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/monsters/bosses/percy/tris.md2");
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);
	
	self->health = 1000;
	self->gib_health = -2000;
	self->mass = 200;
	
	self->pain = percy_pain;
	self->die = percy_downed;
	
	self->monsterinfo.stand = percy_stand;
	/* I'm still unsure of the difference between walking and running. 
	 * I believe "walk" is used in a fashion similar to that of the
	 * original Quake, but I can't be certain at the moment.
	 */
	self->monsterinfo.walk = NULL; /* At the moment this is disabled since it's directly a fight */
	self->monsterinfo.run = percy_run;
	self->monsterinfo.dodge = NULL; 
	/* I'm wondering if I can get some sort of strafing going on with Percy */
	self->monsterinfo.attack = percy_tommy;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = percy_sight;
	self->monsterinfo.idle = NULL;
	
	gi.linkentity(self);
	
	self->monsterinfo.currentmove = percy_run;
	self->monsterinfo.scale = MODEL_SCALE;
	
	walkmonster_start(self);
}