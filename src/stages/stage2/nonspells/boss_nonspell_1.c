/*
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 * ---
 * Copyright (c) 2011-2019, Lukas Weber <laochailan@web.de>.
 * Copyright (c) 2012-2019, Andrei Alexeyev <akari@taisei-project.org>.
*/

#include "taisei.h"

#include "nonspells.h"

#include "global.h"
#include "common_tasks.h"

void hina_cards1(Boss *h, int time) {
	int t = time % 500;
	TIMER(&t);

	if(time < 0)
		return;

	AT(0) {
		aniplayer_queue(&h->ani, "guruguru", 0);
	}
	FROM_TO(0, 500, 2-(global.diff > D_Normal)) {
		play_sound_ex("shot1", 4, false);
		PROJECTILE(.proto = pp_card, .pos = h->pos+50*cexp(I*t/10), .color = RGB(0.8,0.0,0.0), .rule = asymptotic, .args = { (1.6+0.4*global.diff)*cexp(I*t/5.0), 3 });
		PROJECTILE(.proto = pp_card, .pos = h->pos-50*cexp(I*t/10), .color = RGB(0.0,0.0,0.8), .rule = asymptotic, .args = {-(1.6+0.4*global.diff)*cexp(I*t/5.0), 3 });
	}
}

TASK(wander, { BoxedBoss boss; }) {
	Rect wander_bounds = viewport_bounds(80);
	wander_bounds.bottom = 130;

	Boss *boss = TASK_BIND(ARGS.boss);
	boss->move = move_towards(boss->pos, 0.03);

	for(;;WAIT(300)) {
		boss->move.attraction_point = common_wander(boss->pos, 60, wander_bounds);
	}
}

DEFINE_EXTERN_TASK(stage2_boss_nonspell_1) {
	STAGE_BOOKMARK(boss-non1);

	Boss *boss = INIT_BOSS_ATTACK();
	BEGIN_BOSS_ATTACK();

	INVOKE_SUBTASK_DELAYED(420, wander, ENT_BOX(boss));

	aniplayer_queue(&boss->ani, "guruguru", 0);

	int step = difficulty_value(2, 2, 1, 1);
	real speed0 = difficulty_value(2.0, 2.4, 2.8, 3.2);
	real speed1 = difficulty_value(0.1, 0.1, 0.1, 0.2);

	for(int t = 0;; t += WAIT(step)) {
		// play_sound_ex("shot1", 4, false);
		play_loop("shot1_loop");

		cmplx dir = cdir(t / 5.0);
		cmplx ofs = 50 * cdir(t / 10.0);

		real hl = 30 + 50 * psin(t/60.0);

		PROJECTILE(
			.proto = pp_card,
			.pos = boss->pos + ofs,
			.color = RGB(0.8, 0.0, 0.0),
			// .move = move_asymptotic_simple(speed0 * dir, 3),
			.move = move_asymptotic_halflife(speed1 * dir, speed0 * dir * 2, hl),
		);

		PROJECTILE(
			.proto = pp_card,
			.pos = boss->pos - ofs,
			.color = RGB(0.0, 0.0, 0.8),
			// .move = move_asymptotic_simple(speed * -dir, 3),
			.move = move_asymptotic_halflife(speed0 * -dir, speed1 * -dir, hl),
		);
	}
}
