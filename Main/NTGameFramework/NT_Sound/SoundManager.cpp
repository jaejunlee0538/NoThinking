#include "stdafx.h"
#include "SoundManager.h"
#include <NT_Common\MacroUtils.h>
#include <NT_Logging\Logger.h>
namespace qwer {
	SoundManager::SoundManager(void)
	{
		
	}

	SoundManager::~SoundManager(void)
	{
	}

	bool SoundManager::isActiveChannel(int channelIdx) const
	{
		return _channel[channelIdx] != nullptr && _sound[channelIdx] != nullptr;
	}

	int SoundManager::findFreeChannel() const
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (_sound[i] == nullptr) {
				return i;
			}
		}
		return -1;
	}

	int SoundManager::findChannelOf(HashedString keyName) const
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (isActiveChannel(i)) {
				if (keyName == _playSoundName[i]) {
					//��ġ
					return i;
				}
			}
		}
		return -1;
	}

	void SoundManager::stopChannel(int channelIdx)
	{
		bool isPlaying;
		_channel[channelIdx]->isPlaying(&isPlaying);
		if (isPlaying) {
			_channel[channelIdx]->stop();
			LOG_DEBUG(Logging::CHANNEL_SOUND, "Stop %d channel", channelIdx);
		}
		LOG_DEBUG(Logging::CHANNEL_SOUND, "Clear %d channel", channelIdx);
		_channel[channelIdx] = nullptr;
		_sound[channelIdx] = nullptr;
		_playSoundName[channelIdx] = nullptr;
	}

	void SoundManager::stopChannel(FMOD::Channel * channel)
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (_channel[i] == channel) {
				stopChannel(i);
				break;
			}
		}
	}

	int SoundManager::getChannelIdx(FMOD::Channel * channel)
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (_channel[i] == channel) {
				return i;
			}
		}
		return -1;
	}

	FMOD::Sound * SoundManager::findSound(HashedString keyName)
	{
		arrSounds::iterator it = _mTotalSounds.find(keyName);
		if (it != _mTotalSounds.end()) {
			return it->second;
		}
		return nullptr;
	}

	const FMOD::Sound * SoundManager::findSound(HashedString keyName) const{
		return const_cast<SoundManager*>(this)->findSound(keyName);
	}

	bool SoundManager::StartUp(void)
	{
		//���� �ý��� �����Ѵ�
		System_Create(&_system);

		//ä�μ� ����
		_system->init(TOTAL_SOUND_BUFFER, FMOD_INIT_NORMAL, 0);

		//ä�μ��� ���� ������ �����ش�!!
		_sound = new FMOD::Sound*[TOTAL_SOUND_BUFFER];
		_channel = new FMOD::Channel*[TOTAL_SOUND_BUFFER];

		//�ʱ�ȭ
		ZeroMemory(_sound, sizeof(FMOD::Sound*) * (TOTAL_SOUND_BUFFER));
		ZeroMemory(_channel, sizeof(FMOD::Channel*) * (TOTAL_SOUND_BUFFER));

		return true;
	}

	void SoundManager::Shutdown(void)
	{
		if (_channel != nullptr || _sound != nullptr)
		{
			for (int i = 0; i < TOTAL_SOUND_BUFFER; i++)
			{
				if (_channel != nullptr)
				{
					if (_channel[i]) _channel[i]->stop();
				}

				if (_sound != nullptr)
				{
					if (_sound[i]) _sound[i]->release();
				}
			}
		}

		//�޸� �����
		SAFE_DELETE_ARR(_channel);
		SAFE_DELETE_ARR(_sound);

		if (_system != nullptr)
		{
			_system->release();
			_system->close();
		}

		_mTotalSounds.clear();
	}

	//flac, mp3, wave, midi, ogg, m4a, aac, aif, aiff, wma
	bool SoundManager::addSound(HashedString fileName, HashedString keyName, bool background, bool loop)
	{
		FMOD::Sound* sound = nullptr;
		//���R�� �����?
		if (background) {
			FMOD_MODE mode = loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;
			//��������϶�...
			_system->createStream(fileName.c_str(), mode, 0, &sound);
			LOG_DEBUG(Logging::CHANNEL_SOUND, "BGM added : %s", keyName.c_str());
		}
		else {
			FMOD_MODE mode = loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;
			//�Ϲ� �����....
			_system->createSound(fileName.c_str(), mode, 0, &sound);
			LOG_DEBUG(Logging::CHANNEL_SOUND, "SFX added : %s", keyName.c_str());
		}
		if (sound != nullptr) {
			//�ʿ� ���带 Ű���� �Բ� �־��ش�
			_mTotalSounds.insert(std::make_pair(keyName, sound));
			return true;
		}
		else {
			return false;
		}
	}

	void SoundManager::deleteSound(HashedString keyName)
	{
		auto it = _mTotalSounds.find(keyName);
		if (it != _mTotalSounds.end()) {
			LOG_DEBUG(Logging::CHANNEL_SOUND, "Sound���� : %s", keyName.c_str());
			it->second->release();
			_mTotalSounds.erase(it);
		}
	}

	int SoundManager::play(HashedString keyName)
	{
		int freeChannel = findFreeChannel();
		if (freeChannel < 0) {
			//��� ä�� �����
			LOG_ERROR(Logging::CHANNEL_SOUND, "Sound Channel�� �����մϴ�.");
			return -1;
		}
		arrSounds::iterator it = _mTotalSounds.find(keyName);
		if (it != _mTotalSounds.end()) {
			_system->playSound(FMOD_CHANNEL_FREE, it->second, false, &_channel[freeChannel]);
			_sound[freeChannel] = it->second;
			_playSoundName[freeChannel] = keyName;
			_channel[freeChannel]->setCallback(&SoundManager::callbackChannelEvent);
			LOG_DEBUG(Logging::CHANNEL_SOUND, "%s ���(%d ä��)", keyName.c_str(), freeChannel);
		}
		else {
			assert(false && "Cannot find sound");
		}
		return freeChannel;
	}

	int SoundManager::play(HashedString keyName, float volume)
	{
		int freeChannel = findFreeChannel();
		if (freeChannel < 0) {
			//��� ä�� �����
			LOG_ERROR(Logging::CHANNEL_SOUND, "����� ���� ä���� �����մϴ�.");
			return -1;
		}
		arrSounds::iterator it = _mTotalSounds.find(keyName);
		if (it != _mTotalSounds.end()) {
			_system->playSound(FMOD_CHANNEL_FREE, it->second, false, &_channel[freeChannel]);
			_channel[freeChannel]->setVolume(volume);
			_sound[freeChannel] = it->second;
			_playSoundName[freeChannel] = keyName;
			_channel[freeChannel]->setCallback(&SoundManager::callbackChannelEvent);
			LOG_DEBUG(Logging::CHANNEL_SOUND, "%s ���(%d ä��)", keyName.c_str(), freeChannel);
		}
		else {
			LOG_ERROR(Logging::CHANNEL_SOUND, "%s ��� ����", keyName.c_str());
			//assert(false && "Cannot find sound");
			return -1;
		}
		return freeChannel;
	}

	void SoundManager::setPaused(HashedString keyName)
	{
		int channelIdx = findChannelOf(keyName);
		if (channelIdx < 0) {
			return;
		}
		_channel[channelIdx]->setPaused(true);
	}

	void SoundManager::setPausedAll()
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (isActiveChannel(i)) {
				_channel[i]->setPaused(true);
			}
		}
	}

	void SoundManager::resume(HashedString keyName)
	{
		int channelIdx = findChannelOf(keyName);
		if (channelIdx < 0) {
			return;
		}
		_channel[channelIdx]->setPaused(false);
	}

	void SoundManager::resumeAll()
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (isActiveChannel(i)) {
				bool paused;
				_channel[i]->getPaused(&paused);
				if (paused) {
					_channel[i]->setPaused(false);
				}
			}
		}
	}

	void SoundManager::stop(HashedString keyName)
	{
		int channelIdx = findChannelOf(keyName);
		if (channelIdx < 0) {
			return;
		}
		stopChannel(channelIdx);
	}

	void SoundManager::stopAll()
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (_sound[i] != nullptr) {

				_channel[i]->stop();
			}
		}
	}

	bool SoundManager::isChannelPlaying(int channelIdx)
	{
		if (channelIdx < 0 || channelIdx >= TOTAL_SOUND_BUFFER) {
			return false;
		}
		if (_channel[channelIdx] != false) {
			bool playing;
			_channel[channelIdx]->isPlaying(&playing);
			return playing;
		}
		return false;
	}

	float SoundManager::getSoundData(int channelIdx)
	{
		if (!isChannelPlaying(channelIdx))
			return 0;
		float data;
		_channel[channelIdx]->getWaveData(&data, 1, 0);
		return data;
	}

	//�Ͻ� ���� �Ǿ��°�?
	bool SoundManager::isSoundPaused(HashedString keyName)
	{
		int channelIdx = findChannelOf(keyName);
		if (channelIdx < 0) {
			return false;
		}
		bool paused;
		_channel[channelIdx]->getPaused(&paused);
		return paused;
	}

	//���� ������̳�?
	bool SoundManager::isSoundPlaying(HashedString keyName)
	{
		int channelIdx = findChannelOf(keyName);
		if (channelIdx < 0) {
			return false;
		}
		bool playing;
		_channel[channelIdx]->isPlaying(&playing);
		return playing;
	}

	//fmod �ý��� ����...
	void SoundManager::update(void)
	{
		_system->update();
	}

	std::vector<HashedString> SoundManager::getSoundList() const
	{
		std::vector<HashedString> soundList;
		soundList.reserve(_mTotalSounds.size());
		for (auto it = _mTotalSounds.begin(); it != _mTotalSounds.end(); ++it) {
			soundList.push_back(it->first);
		}
		return soundList;
	}

	void SoundManager::setVolume(HashedString keyName, float volume)
	{
		int idx = findChannelOf(keyName);
		if (idx < 0)
			return;
		_channel[idx]->setVolume(volume);
	}

	void SoundManager::setVolume(int channelIdx, float volume)
	{
		if (!isChannelPlaying(channelIdx))
			return;
		_channel[channelIdx]->setVolume(volume);
	}

	void SoundManager::scalePlayingSoundVolume(float scale)
	{
		for (int i = 0; i < TOTAL_SOUND_BUFFER; ++i) {
			if (isActiveChannel(i)) {
				float currentVolume;
				_channel[i]->getVolume(&currentVolume);
				currentVolume *= scale;
				_channel[i]->setVolume(currentVolume);
			}
		}
	}

	int SoundManager::getSoundLengthMS(HashedString keyName)
	{
		FMOD::Sound* sound = findSound(keyName);
		if (sound == nullptr)
			return -1;
		unsigned int len;
		sound->getLength(&len, FMOD_TIMEUNIT_MS);
		return len;
	}

	int SoundManager::getPlayPositionMS(HashedString keyName) const
	{
		int idx = findChannelOf(keyName);
		if (idx < 0)
			return -1;

		unsigned int pos;
		_channel[idx]->getPosition(&pos, FMOD_TIMEUNIT_MS);
		return pos;
	}

	int SoundManager::getPlayPositionMS(int channelIdx)
	{
		if (!isActiveChannel(channelIdx))
			return -1;
		unsigned int pos;
		_channel[channelIdx]->getPosition(&pos, FMOD_TIMEUNIT_MS);
		return pos;
	}

	void SoundManager::setPlayPositionMS(HashedString keyName, unsigned int pos)
	{
		int idx = findChannelOf(keyName);
		if (idx < 0)
			return;
		_channel[idx]->setPosition(pos, FMOD_TIMEUNIT_MS);
	}

	void SoundManager::addSoundFinishedCallback(SOUND_FINISHED_CALLBACK cb, void * data)
	{
		_soundFinishedCallback.push_back(SoundFinishedCallback());
		_soundFinishedCallback.back().set(cb, data);
	}

	FMOD_RESULT F_CALLBACK SoundManager::callbackChannelEvent(FMOD_CHANNEL * channel, FMOD_CHANNEL_CALLBACKTYPE type, void * commanddata1, void * commanddata2)
	{
		///*
		//FMOD_CHANNEL_CALLBACKTYPE_END,                  /* Called when a sound ends. */
		//FMOD_CHANNEL_CALLBACKTYPE_VIRTUALVOICE,         /* Called when a voice is swapped out or swapped in. */
		//	FMOD_CHANNEL_CALLBACKTYPE_SYNCPOINT,            /* Called when a syncpoint is encountered.  Can be from wav file markers. */
		//	FMOD_CHANNEL_CALLBACKTYPE_OCCLUSION,            /* Called when the channel has its geometry occlusion value calculated.  Can be used to clamp or change the value. */

		//	FMOD_CHANNEL_CALLBACKTYPE_MAX,                  /* Maximum number of callback types supported. */
		//	FMOD_CHANNEL_CALLBACKTYPE_FORCEINT = 65536      /* Makes sure this enum is signed 32bit. */
		//*/
		switch (type) {
		case FMOD_CHANNEL_CALLBACKTYPE_END:
		{
			auto& soundManager = GET_SOUNDMANAGER();
			int idx = soundManager.getChannelIdx((FMOD::Channel*)channel);
			if (idx >= 0) {
				unsigned int pos;
				((FMOD::Channel*)channel)->getPosition(&pos, FMOD_TIMEUNIT_MS);
				unsigned int len;
				soundManager._sound[idx]->getLength(&len, FMOD_TIMEUNIT_MS);
				if (pos == len) {
					//���尡 ������ ����� �� ����� ��
					for (int i = 0; i < soundManager._soundFinishedCallback.size(); ++i) {
						soundManager._soundFinishedCallback[i].call(soundManager._playSoundName[idx]);
					}
				}
			}
			soundManager.stopChannel(idx);
		}
			break;
		}
		return FMOD_OK;
	}
}