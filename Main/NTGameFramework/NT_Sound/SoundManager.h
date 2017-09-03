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

		//keyName 사운드를 재생하고 재생 채널 인덱스를 반환한다.
		int play(HashedString keyName);
		//keyName 사운드를 재생하고 재생 채널 인덱스를 반환한다.
		int play(HashedString keyName, float volume);

		void setPaused(HashedString keyName);
		void setPausedAll();
		void resume(HashedString keyName);
		void resumeAll();
		void stop(HashedString keyName);
		//channelIdx가 재생 중이면 재생을 멈추고 channelIdx의 채널 목록을 NULL로 초기화한다.
		void stopChannel(int channelIdx);
		void stopAll();

		//channelIdx의 채널이 재생 중이라면 true를 반환한다. 해당 인덱스에 채널이 할당되어 있지 않으면 false를 반환.
		bool isChannelPlaying(int channelIdx);

		float getSoundData(int channelIdx);

		//일시 정지 되었는가?
		bool isSoundPaused(HashedString keyName);

		//현재 재생중이냐?
		bool isSoundPlaying(HashedString keyName);

		//fmod 시스템 갱신...
		void update(void);

		std::vector<HashedString> getSoundList() const;

		void setVolume(HashedString keyName, float volume);
		void setVolume(int channelIdx, float volume);
		void scalePlayingSoundVolume(float scale);

		int getSoundLengthMS(HashedString keyName);
		int getPlayPositionMS(HashedString keyName) const;
		int getPlayPositionMS(int channelIdx);
		void setPlayPositionMS(HashedString keyName, unsigned int pos);

		//사운드가 끝까지 재생되었을 때 호출할 콜백함수를 추가한다.
		void addSoundFinishedCallback(SOUND_FINISHED_CALLBACK cb, void* data);
	private:
		//사용하고 있지 않은 채널 목록의 인덱스를 반환한다. 여유 공간이 없으면 -1을 반환한다.
		int findFreeChannel() const;
		//channelIdx에 사운드와 채널이 할당되어 있으면 true를 반환한다.
		bool isActiveChannel(int channelIdx) const;
		//현재 재생 중인 채널에서 keyName 사운드를 재생하고 있는 채널의 인덱스를 반환한다. 탐색에 실패하면 -1을 반환한다.
		int findChannelOf(HashedString keyName) const;

		//channel이 있는 채널 목록을 찾아 clear한다. stopChannel(int)와 동일하기 동작한다.
		void stopChannel(FMOD::Channel* channel);
		//채널 목록에서 channel에 해당하는 목록의 인덱스를 반환한다. 탐색에 실패하면 -1을 반환한다.
		int getChannelIdx(FMOD::Channel* channel);
		//keyName을 가진 FMOD::Sound 객체의 포인터를 반환한다.
		FMOD::Sound* findSound(HashedString keyName);
		//keyName을 가진 FMOD::Sound 객체의 포인터를 반환한다.
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