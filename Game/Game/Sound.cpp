#include "stdafx.h"
#include "Sound.h"
#include "tkEngine/Sound/tkSoundSource.h"

SoundCTL::SoundCTL()
{
	bgmSource = NULL;
}


SoundCTL::~SoundCTL()
{
	if (bgmSource != NULL) {
		DeleteGO(bgmSource);
	}
}

void SoundCTL::Start() {
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/BGM.wav");
	bgmSource->Play(true);
}

void SoundCTL::Update() {
	bgmSource->Play(true);
}