#pragma once

#ifdef _cplusplus
extern "C" {
#endif

#include "SDL_rwops.h"
#include <android/asset_manager.h>

SDL_RWops * AAsset_RWFromAsset(AAssetManager *mgr, const char *filename);

#ifdef _cplusplus
}
#endif
