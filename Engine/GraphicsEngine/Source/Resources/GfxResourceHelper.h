// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

// ------------------------------------------------------------

#define DECLARE_GFX_RESOURCE_DEFAULTS(GfxResource)                                                                                                                       \
    GfxResource##();                                                                                                                                                     \
    GfxResource##(const GfxResource##&);                                                                                                                                 \
    GfxResource##(GfxResource##&&) noexcept;                                                                                                                             \
    ~##GfxResource##();                                                                                                                                                  \
    GfxResource##& operator=(const GfxResource##&);                                                                                                                      \
    GfxResource##& operator=(GfxResource##&&) noexcept;

#define DEFINE_GFX_RESOURCE_DEFAULTS(GfxResource)                                                                                                                        \
    GfxResource## ::GfxResource##() = default;                                                                                                                           \
    GfxResource## ::GfxResource##(const GfxResource##&) = default;                                                                                                       \
    GfxResource## ::GfxResource##(GfxResource##&&) noexcept = default;                                                                                                   \
    GfxResource## ::##~##GfxResource##() = default;                                                                                                                      \
    GfxResource##& GfxResource## ::operator=(const GfxResource##&) = default;                                                                                            \
    GfxResource##& GfxResource## ::operator=(GfxResource##&&) noexcept = default;

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------