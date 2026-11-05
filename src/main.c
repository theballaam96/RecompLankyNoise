#include "modding.h"
#include "ultra64.h"
#include "recompconfig.h"
#include "recompdata.h"
#include "recompui.h"
#include "recompui_event_structs.h"
#include "rt64_extended_gbi.h"
#include "libaudio.h"
#include "enums.h"
#include "common_structs.h"

typedef struct NewAudioSample NewAudioSample;
struct NewAudioSample {
    u8 *sample;
    f32 sample_length; // In seconds
    u32 sample_size; // in bytes
    u8 bank; // 0 = OST, 1 = SFX
    u8 inst;
    u16 snd;
    u32 base_start; // DO NOT PRE-POPULATE
    u32 base_end; // DO NOT PRE-POPULATE
    NewAudioSample *prev; // DO NOT PRE-POPULATE
    NewAudioSample *next; // DO NOT PRE-POPULATE
};
RECOMP_IMPORT("audio_tools", void ReplaceSample(NewAudioSample *smp));

extern u8 hajaga[];
extern u32 hajaga_size;
extern s32 *D_global_asm_807FBB50;

NewAudioSample lanky_beta_sound = {
    .sample = &hajaga[0],
    .sample_length = 0.474f,
    .sample_size = 0,
    .bank = 1,
    .inst = 0,
    .snd = 939,
};

RECOMP_CALLBACK("*", recomp_on_init)
void lankyNoiseInit(void) {
    // Initialize the lanky noise
    lanky_beta_sound.sample_size = hajaga_size;
    ReplaceSample(&lanky_beta_sound);
}

u8 anim_bytes[] = {57, 3, 172, 25};  // 3, 172 = 940

RECOMP_CALLBACK("*", dk64recomp_every_frame)
void lankyNoiseAnimWipe(void) {
    // Get rid of interfering sound calls
    u8 *offset;
    s32 i;

    if (D_global_asm_807FBB50) {
        offset = (u8 *)((s32)D_global_asm_807FBB50 + D_global_asm_807FBB50[354]);
        for (i = 0xC; i < 0x10; i++) {
            offset[i] = anim_bytes[i - 0xC];
        }
        for (i = 0x2d; i < 0x31; i++) {
            offset[i] = 0;
        }
    }
}