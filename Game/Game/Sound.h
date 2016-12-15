#pragma once
#include "stdafx.h"
#include "tkEngine/Sound/tkSoundSource.h"

//サウンドデモのクラス。
class SoundCTL : public IGameObject
{
public:
	SoundCTL();
	~SoundCTL();
	void Start();
	void Update();
private:
	CSoundSource* bgmSource;		//BGMのサウンドソース。
};
