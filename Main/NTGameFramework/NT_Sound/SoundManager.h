#pragma once

#include <NT_Common\Singleton.h>
#include <string>
#include <map>
#include <Windows.h>
#include <vector>
#include <functional>
#include <NT_Common\HashedString.h>
#include <fmod\fmod.hpp>


namespace qwer {
	class SoundManager : public Singleton <SoundManager>
	{
		enum {
			EXTRA_CHANNEL_BUFFER = 5,
			SOUND_BUFFER = 10,
			MAX_SOUND_NAME_LENGTH = 50,
			TOTAL_SOUND_BUFFER = EXTRA_CHANNEL_BUFFER + SOUND_BUFFER
		};
	public:
		typedef std::function<void(HashedString keyName, void* data)> SOUND_FINISHED_CALLBACK;
	private:
		typedef std::map<HashedString, FMOD::Sound*> arrSounds;
		typedef std::map<HashedString, FMOD::Sound*>::iterator arrSoundsIter;
		typedef std::map<HashedString, FMOD::Channel*> arrChannels;
		typedef std::map<HashedString, FMOD::Channel*>::iterator arrChannelsIter;
		
		class SoundFinishedCallback {
			SOUND_FINISHED_CALLBACK cb;
			void* data;
		public:
			SoundFinishedCallback()
				:cb(NULL), data(NULL) {
			}
			void set(SOUND_FINISHED_CALLBACK cb, void* data) {
				this->cb = cb;
				this->data = data;
			}
			inline void call(HashedString soundName) {
				if (cb) {
					cb(soundName, data);
				}
			}
		};
	public:
		SoundManager(void);
		~SoundManager(void);

		bool StartUp(void);
		void Shutdown(void);

		//flac, mp3, wave, midi, ogg, m4a, aac, aif, aiff, wma
		bool addSound(HashedString fileName, HashedString keyName, bool background, bool loop);
		void deleteSound(HashedString keyName);

		//keyName ���带 ����ϰ� ��� ä�� �ε����� ��ȯ�Ѵ�.
		int play(HashedString keyName);
		//keyName ���带 ����ϰ� ��� ä�� �ε����� ��ȯ�Ѵ�.
		int play(HashedString keyName, float volume);

		void setPaused(HashedString keyName);
		void setPausedAll();
		void resume(HashedString keyName);
		void resumeAll();
		void stop(HashedString keyName);
		//channelIdx�� ��� ���̸� ����� ���߰� channelIdx�� ä�� ����� NULL�� �ʱ�ȭ�Ѵ�.
		void stopChannel(int channelIdx);
		void stopAll();

		//channelIdx�� ä���� ��� ���̶�� true�� ��ȯ�Ѵ�. �ش� �ε����� ä���� �Ҵ�Ǿ� ���� ������ false�� ��ȯ.
		bool isChannelPlaying(int channelIdx);

		float getSoundData(int channelIdx);

		//�Ͻ� ���� �Ǿ��°�?
		bool isSoundPaused(HashedString keyName);

		//���� ������̳�?
		bool isSoundPlaying(HashedString keyName);

		//fmod �ý��� ����...
		void update(void);

		std::vector<HashedString> getSoundList() const;

		void setVolume(HashedString keyName, float volume);
		void setVolume(int channelIdx, float volume);
		void scalePlayingSoundVolume(float scale);

		int getSoundLengthMS(HashedString keyName);
		int getPlayPositionMS(HashedString keyName) const;
		int getPlayPositionMS(int channelIdx);
		void setPlayPositionMS(HashedString keyName, unsigned int pos);

		//���尡 ������ ����Ǿ��� �� ȣ���� �ݹ��Լ��� �߰��Ѵ�.
		void addSoundFinishedCallback(SOUND_FINISHED_CALLBACK cb, void* data);
	private:
		//����ϰ� ���� ���� ä�� ����� �ε����� ��ȯ�Ѵ�. ���� ������ ������ -1�� ��ȯ�Ѵ�.
		int findFreeChannel() const;
		//channelIdx�� ����� ä���� �Ҵ�Ǿ� ������ true�� ��ȯ�Ѵ�.
		bool isActiveChannel(int channelIdx) const;
		//���� ��� ���� ä�ο��� keyName ���带 ����ϰ� �ִ� ä���� �ε����� ��ȯ�Ѵ�. Ž���� �����ϸ� -1�� ��ȯ�Ѵ�.
		int findChannelOf(HashedString keyName) const;

		//channel�� �ִ� ä�� ����� ã�� clear�Ѵ�. stopChannel(int)�� �����ϱ� �����Ѵ�.
		void stopChannel(FMOD::Channel* channel);
		//ä�� ��Ͽ��� channel�� �ش��ϴ� ����� �ε����� ��ȯ�Ѵ�. Ž���� �����ϸ� -1�� ��ȯ�Ѵ�.
		int getChannelIdx(FMOD::Channel* channel);
		//keyName�� ���� FMOD::Sound ��ü�� �����͸� ��ȯ�Ѵ�.
		FMOD::Sound* findSound(HashedString keyName);
		//keyName�� ���� FMOD::Sound ��ü�� �����͸� ��ȯ�Ѵ�.
		const FMOD::Sound* findSound(HashedString keyName) const;

		static FMOD_RESULT F_CALLBACK callbackChannelEvent(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2);
	private:
		FMOD::System* _system;

		FMOD::Sound** _sound;
		FMOD::Channel** _channel;
		HashedString _playSoundName[TOTAL_SOUND_BUFFER];

		arrSounds _mTotalSounds;
		std::vector<SoundFinishedCallback> _soundFinishedCallback;
	};
}
#define GET_SOUNDMANAGER()	qwer::SoundManager::GetSingleton()