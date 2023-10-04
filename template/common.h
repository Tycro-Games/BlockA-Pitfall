// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

// common.h is to be included in host and device code and stores
// global settings and defines.

// default screen resolution
constexpr int SCRWIDTH = 1152;
constexpr int SCRHEIGHT = 648;
constexpr double MS_PER_UPDATE = 1.0 / 65;
constexpr double fixedDeltaTime = 0.01f;
constexpr uint RED = 0xff0000;
constexpr uint YELLOW = 0xffff00;
constexpr uint PINK = 0xff00ff;
constexpr uint ORANGE = 0xff8000;

constexpr uint GREEN = 0x00ff00;
constexpr uint BLUE = 0x0000ff;

// #define FULLSCREEN

// constants
constexpr float  PI = 3.14159265358979323846264f;
constexpr float  INVPI = 0.31830988618379067153777f;
constexpr float  INV2PI = 0.15915494309189533576888f;
constexpr float  TWOPI = 6.28318530717958647692528f;
constexpr float  SQRT_PI_INV = 0.56418958355f;
constexpr float  LARGE_FLOAT = 1e34f;