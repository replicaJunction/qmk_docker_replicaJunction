#pragma once

// WinCompose has a bug right now where 4-length Unicode sequences aren't working
// on new versions of Windows 10.
// https://github.com/samhocevar/wincompose/issues/235

enum unicode_name
{
    // THINK, // thinking face 🤔
    // GRIN,  // grinning face 😊
    // HEART, // heart ❤
    EYERT // smiling face with heart shaped eyes 😍

    // SNEK,    // snke 🐍
    // PENGUIN, // 🐧
    // DRAGON,  // 🐉
    // MONKEY,  // 🐒
    // CHICK,   // 🐥
    // BOAR,    // 🐗

    // OKOK, // 👌
    // EFFU, // 🖕
    // INUP, // 👆
    // THUP, // 👍
    // THDN, // 👎

    // BBB,     // dat B 🅱
    // POO,     // poop 💩
    // HUNDR,   // 100 💯
    // EGGPL,   // EGGPLANT 🍆
    // WATER,   // wet 💦
    // TUMBLER, // 🥃

    // LIT,   // fire 🔥
    // BANG,  // ‽
    // IRONY, // ⸮
    // DEGREE // °
};

#ifdef UNICODEMAP_ENABLE
const uint32_t PROGMEM unicode_map[] = {
    // [THINK] = 0x1F914,
    // [GRIN] = 0x1F600,
    // [BBB] = 0x1F171,
    // [POO] = 0x1F4A9,
    // [HUNDR] = 0x1F4AF,
    // [EGGPL] = 0x1F346,
    // [WATER] = 0x1F4A6,
    // [LIT] = 0x1F525,
    // [SNEK] = 0x1F40D,
    // [PENGUIN] = 0x1F427,
    // [BOAR] = 0x1F417,
    // [MONKEY] = 0x1F412,
    // [CHICK] = 0x1F425,
    // [DRAGON] = 0x1F409,
    // [OKOK] = 0x1F44C,
    // [EFFU] = 0x1F595,
    // [INUP] = 0x1F446,
    // [THDN] = 0x1F44E,
    // [THUP] = 0x1F44D,
    // [TUMBLER] = 0x1F943,
    // [BANG] = 0x0203D,
    // [IRONY] = 0x02E2E,
    // [DEGREE] = 0x000B0,
    // [HEART] = 0x2764,
    [EYERT] = 0x1f60d
};
#endif
