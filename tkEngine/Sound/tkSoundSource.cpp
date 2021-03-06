/*!
 * @brief	音源クラス。
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/Sound/tkSoundSource.h"


namespace tkEngine{
	CSoundSource::CSoundSource()
	{
	}
	CSoundSource::~CSoundSource()
	{
		Release();
	}
	void CSoundSource::Init( char* filePath )
	{
		m_waveFile.Open(filePath);
		m_buffer.reset(new char[m_waveFile.GetSize()]);
		unsigned int dummy;
		m_waveFile.Read(m_buffer.get(), m_waveFile.GetSize(), &dummy);
		//サウンドボイスソースを作成。
		m_sourceVoice = SoundEngine().CreateXAudio2SourceVoice(&m_waveFile);
	}
	void CSoundSource::InitStreaming(char* filePath, unsigned int ringBufferSize, unsigned int bufferSize)
	{
		m_waveFile.Open(filePath);
		m_isStreaming = true;
		m_streamingBufferSize = bufferSize;
		m_buffer.reset( new char[ringBufferSize]);
		m_ringBufferSize = ringBufferSize;
		m_readStartPos = 0;
		m_currentBufferingSize = 0;
		//サウンドボイスソースを作成。
		m_sourceVoice = SoundEngine().CreateXAudio2SourceVoice(&m_waveFile);
		m_sourceVoice->Start(0,0);
	}
	void CSoundSource::Release()
	{
		m_waveFile.Release();
		if (m_sourceVoice != nullptr) {
			m_sourceVoice->DestroyVoice();
			m_sourceVoice = nullptr;
		}
		DeleteGO(this);
	}
	void CSoundSource::Play(char* buff, unsigned int bufferSize)
	{
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.pAudioData = (BYTE*)buff;
		buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
		buffer.AudioBytes = bufferSize;
		if (m_sourceVoice != nullptr && bufferSize > 0) {
			//再生開始。
			if (FAILED(m_sourceVoice->SubmitSourceBuffer(&buffer))) {
				Release();
				TK_LOG("Failed m_sourceVoice->SubmitSourceBuffer");
				return;
			}

		}
	}
	
	void CSoundSource::StartStreamingBuffring()
	{
		char* readStartBuff = m_buffer.get();
		m_readStartPos += m_currentBufferingSize;
		if (m_readStartPos + m_streamingBufferSize >= m_ringBufferSize) {
			//リングバッファのサイズを超える。
			//循環する。
			m_readStartPos = 0;
		}
		m_waveFile.ReadAsync(&readStartBuff[m_readStartPos], m_streamingBufferSize, &m_currentBufferingSize);
		m_streamingState = enStreamingBuffering;
	}
	void CSoundSource::Play(bool isLoop)
	{
		if (m_isPlaying) {
			//再生中のものを再開する。
			m_sourceVoice->Start(0);
		}
		else {
			if (m_isStreaming) {
				//バッファリング開始
				StartStreamingBuffring();
			}
			else {
				m_sourceVoice->FlushSourceBuffers();
				m_sourceVoice->Start(0);
				Play(m_buffer.get(), m_waveFile.GetSize());
			}
			m_isPlaying = true;
		}
		m_isLoop = isLoop;
	}
	void CSoundSource::UpdateStreaming()
	{
		if (!m_isPlaying) {
			return;
		}
		if (m_streamingState == enStreamingBuffering) {
			//バッファリング中。
			if (m_waveFile.IsReadEnd()) {
				//バッファリングが終わった。
				m_streamingState = enStreamingQueueing;
			}
		}
		if (m_streamingState == enStreamingQueueing) {
			//キューイング中。
			XAUDIO2_VOICE_STATE state;
			m_sourceVoice->GetState(&state);
			if (state.BuffersQueued <= 2) {	//キューイングされているバッファが２以下になったらキューイングできる。
				Play(&m_buffer[m_readStartPos], m_currentBufferingSize);
				if (m_currentBufferingSize == 0) {
					//読み込んだサイズが０ということは末端まで読み込みが終わったということ。
					if (m_isLoop) {
						//ループする？
						//waveファイルの読み込み位置をリセットしてバッファリング再開。
						m_waveFile.ResetFile();
						StartStreamingBuffring();
					}
					else {
						//ループしない場合はキューが空になったら再生終了。
						if (state.BuffersQueued == 0) {
							//再生終了。
							m_isPlaying = false;
							DeleteGO(this);
						}
					}
				}
				else {
					//次をバッファリングする。
					StartStreamingBuffring();
				}
			}
		}
	}
	void CSoundSource::UpdateOnMemory()
	{
		if (!m_isPlaying) {
			return;
		}
		XAUDIO2_VOICE_STATE state;
		m_sourceVoice->GetState(&state);
		if (state.BuffersQueued <= 0) {
			m_isPlaying = false;
			if (m_isLoop) {
				//ループ。
				Play(m_isLoop);
			}
			else {
				DeleteGO(this);
			}
		}
	}
	void CSoundSource::Update()
	{
		if (m_isStreaming) {
			//ストリーミング再生中の更新。
			UpdateStreaming();
		}
		else {
			//オンメモリ再生中の更新処理。
			UpdateOnMemory();
		}
	}
}
