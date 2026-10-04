#pragma once
#ifndef SHADER_SLOTS_HLSLI
#define SHADER_SLOTS_HLSLI

#define MATERIAL_TEXTURE_SLOT_0 register(t0)
#define MATERIAL_TEXTURE_SLOT_1 register(t1)
#define MATERIAL_TEXTURE_SLOT_2 register(t2)
#define MATERIAL_TEXTURE_SLOT_3 register(t3)
#define MATERIAL_TEXTURE_SLOT_4 register(t4)
#define MATERIAL_TEXTURE_SLOT_5 register(t5)
#define MATERIAL_TEXTURE_SLOT_6 register(t6)
#define MATERIAL_TEXTURE_SLOT_7 register(t7)

#define SAMPLER_SLOT_POINT_WRAP register(s0)
#define SAMPLER_SLOT_BILINEAR_WRAP register(s1)
#define SAMPLER_SLOT_TRILINEAR_WRAP register(s2)
#define SAMPLER_SLOT_POINT_CLAMP register(s3)
#define SAMPLER_SLOT_BILINEAR_CLAMP register(s4)
#define SAMPLER_SLOT_TRILINEAR_CLAMP register(s5)

#define BUFFER_SLOT_MATERIAL_PROPERTIES register(b0)

#define BUFFER_SLOT_FRAME register(b10)
#define BUFFER_SLOT_OBJECT register(b11)
#define BUFFER_SLOT_LIGHT register(b12)
#define BUFFER_SLOT_ANIMATION register(b13)

#endif