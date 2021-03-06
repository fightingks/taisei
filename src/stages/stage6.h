/*
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 * ---
 * Copyright (c) 2011-2019, Lukas Weber <laochailan@web.de>.
 * Copyright (c) 2012-2019, Andrei Alexeyev <akari@taisei-project.org>.
 */

#ifndef IGUARD_stages_stage6_h
#define IGUARD_stages_stage6_h

#include "taisei.h"

#include "stageinfo.h"
#include "enemy.h"
#include "stageutils.h"
#include "util/fbpair.h"

extern struct stage6_spells_s {
	// this struct must contain only fields of type AttackInfo
	// order of fields affects the visual spellstage number, but not its real internal ID

	union {
		AttackInfo scythe_first;
		struct {
			AttackInfo occams_razor;
			AttackInfo orbital_clockwork;
			AttackInfo wave_theory;
		} scythe;
	};

	union {
		AttackInfo baryon_first;
		struct {
			AttackInfo many_world_interpretation;
			AttackInfo wave_particle_duality;
			AttackInfo spacetime_curvature;
			AttackInfo higgs_boson_uncovered;
		} baryon;
	};

	struct {
		AttackInfo curvature_domination;
	} extra;

	struct {
		AttackInfo theory_of_everything;
	} final;

	// required for iteration
	AttackInfo null;
} stage6_spells;

// this hackery is needed for spell practice
#define STG6_SPELL_NEEDS_SCYTHE(s) ((s) >= &stage6_spells.scythe_first && ((s) - &stage6_spells.scythe_first) < sizeof(stage6_spells.scythe)/sizeof(AttackInfo))
#define STG6_SPELL_NEEDS_BARYON(s) ((s) >= &stage6_spells.baryon_first && ((s) - &stage6_spells.baryon_first) < sizeof(stage6_spells.baryon)/sizeof(AttackInfo)+1)

extern StageProcs stage6_procs;
extern StageProcs stage6_spell_procs;

extern FBPair baryon_fbpair;
extern Framebuffer *baryon_aux_fb;

void start_fall_over(void);

uint stage6_towerwall_pos(Stage3D *s3d, vec3 pos, float maxrange);
void stage6_towerwall_draw(vec3 pos);

#endif // IGUARD_stages_stage6_h
