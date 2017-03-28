
#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_SONGS 3
typedef unsigned char Uint8;

class ModuleAudio : public Module
{
public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	Mix_Music* const Load(const char* path);
	bool CleanUp();

public:
	Mix_Music* audio[MAX_SONGS];
	uint last = 0;
};

#endif // __ModuleAudio_H__