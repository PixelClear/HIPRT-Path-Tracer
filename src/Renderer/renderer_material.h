#ifndef RENDERER_MATERIAL_H
#define RENDERER_MATERIAL_H

#include "Image/color.h"

enum BRDF
{
    Uninitialized,
    CookTorrance,
    SpecularFresnel
};

struct RendererMaterial
{
    bool is_emissive()
    {
        return emission.r != 0.0f || emission.g != 0.0f || emission.b != 0.0f;
    }

    BRDF brdf_type = BRDF::Uninitialized;

    HIPRTColor emission = HIPRTColor(0.0f, 0.0f, 0.0f);
    HIPRTColor diffuse = HIPRTColor(1.0f, 0.2f, 0.7f);

    float metalness = 0.0f;
    float roughness = 1.0f;
    float ior = 1.40f;
    float transmission_factor = 0.0f;
};

#endif
