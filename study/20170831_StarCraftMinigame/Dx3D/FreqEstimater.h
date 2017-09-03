#pragma once
namespace qwer {
	class FreqEstimater {
	public:
		FreqEstimater(float samplingTime)
			:_samplePeriod(samplingTime) {
			reset();
		}

		void reset() {
			_lastSampleTime = -1;
			_sampleCount = 0;
			_fps = 0.0f;
			_frameTime = 999999;
		}

		/*
		�����ӷ��� ��ȯ�Ѵ�.
		*/
		float getFPS() const {
			return _fps;
		}

		/*
		��� ������ �ð��� ��ȯ�Ѵ�.
		*/
		int getFramTime() const {
			return _frameTime;
		}

		bool update(float currentTime) {
			_sampleCount++;
			if (_lastSampleTime < 0) {
				_lastSampleTime = currentTime;
				return false;
			}
			float dt = currentTime - _lastSampleTime;
			if (dt >= _samplePeriod) {
				_fps = _sampleCount / dt;
				_frameTime = dt / _sampleCount;
				_lastSampleTime = currentTime;
				_sampleCount = 0;
				return true;
			}
			return false;
		}
	private:
		float _lastSampleTime;
		float _samplePeriod;
		float _fps;
		int _frameTime;
		int _sampleCount;
	};
}