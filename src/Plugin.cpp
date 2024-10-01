#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>

#include "NH/Logger.h"

#ifdef __G2A
#define GOTHIC_NAMESPACE Gothic_II_Addon
#define ENGINE Engine_G2A
HOOKSPACE(Gothic_II_Addon, GetGameVersion() == ENGINE);

#include "Plugin.hpp"

#endif

#undef GOTHIC_NAMESPACE
#undef ENGNE
HOOKSPACE(Global, true);