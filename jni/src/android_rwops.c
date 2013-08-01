#include "android_rwops.h"

static SDLCALL long aa_rw_seek(struct SDL_RWops * ops, long offset, int whence)
{
	return AAsset_seek((AAsset*)ops->hidden.unknown.data1, offset, whence);
}


static SDLCALL size_t aa_rw_read(struct SDL_RWops * ops, void *ptr, size_t size, size_t maxnum)
{
	return AAsset_read((AAsset*)ops->hidden.unknown.data1, ptr, maxnum * size) / size;
}


static SDLCALL int aa_rw_close(struct SDL_RWops * ops)
{
	AAsset_close((AAsset*)ops->hidden.unknown.data1);
	SDL_FreeRW(ops);

	return 0;
}


SDL_RWops * AAsset_RWFromAsset(AAssetManager *mgr, const char *filename)
{
	AAsset *asset = AAssetManager_open(mgr, filename, AASSET_MODE_RANDOM);

	if (!asset)
		return NULL;
	
	SDL_RWops *ops = SDL_AllocRW();
	
	if (!ops)
	{
		AAsset_close(asset);
		return NULL;
	}
	
	ops->hidden.unknown.data1 = asset;
	ops->read = aa_rw_read;
	ops->write = NULL;
	ops->seek = aa_rw_seek;
	ops->close = aa_rw_close;
	
	return ops;
}
