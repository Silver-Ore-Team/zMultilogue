// Disable macro redefinition warning 
#pragma warning(disable: 4005)

#include <Union/Hook.h>
#include <Union/RawMemory.h>
#include <ZenGin/zGothicAPI.h>

#include "NH/Logger.h"


#ifdef __G1
#define GOTHIC_NAMESPACE Gothic_I_Classic
#define ENGINE Engine_G1
HOOKSPACE(Gothic_I_Classic, GetGameVersion() == ENGINE);

#include "Plugin.hpp"

#endif

#ifdef __G2A
#define GOTHIC_NAMESPACE Gothic_II_Addon
#define ENGINE Engine_G2A
HOOKSPACE(Gothic_II_Addon, GetGameVersion() == ENGINE);

#include "Plugin.hpp"

#endif

#undef GOTHIC_NAMESPACE
#undef ENGNE
HOOKSPACE(Global, true);