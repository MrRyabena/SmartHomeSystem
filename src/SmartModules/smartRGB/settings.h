#pragma once

#define BOT_ACTIVE 1
#define BOT_TOCKEN "5993724594:AAHW-eBzSQs2QktURq0Waolu6zuO0VMGoe0" // https://api.telegram.org/bot5993724594:AAHW-eBzSQs2QktURq0Waolu6zuO0VMGoe0/getUpdates

#define BOT_NAME "@SHSrgb_bot"
#define CHAT_ID "438901860"       // commander's chat
#define GROUP_ID "-1001977013443" // smart home test

#define Rp 14 // D5
#define Gp 12 // D6
#define Bp 13 // D7

// для эффектов огня:
// настройки пламени
#define HUE_START 0    // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define HUE_GAP 10     // коэффициент цвета огня (чем больше - тем дальше заброс по цвету)
#define SMOOTH_K 0.10  // коэффициент плавности огня
#define MIN_BRIGHT 80  // мин. яркость огня
#define MAX_BRIGHT 255 // макс. яркость огня
#define MIN_SAT 255    // мин. насыщенность
#define MAX_SAT 255    // макс. насыщенность