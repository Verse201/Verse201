#pragma once
#include "stdafx.h"
#include "tkEngine/Sound/tkSoundSource.h"

//�T�E���h�f���̃N���X�B
class SoundCTL : public IGameObject
{
public:
	SoundCTL();
	~SoundCTL();
	void Start();
	void Update();
private:
	CSoundSource* bgmSource;		//BGM�̃T�E���h�\�[�X�B
};
