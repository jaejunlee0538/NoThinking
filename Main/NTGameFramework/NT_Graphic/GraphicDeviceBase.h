#pragma once
namespace qwer
{
	struct DeviceConfiguration {
		bool isWindowed;
	};

	class GraphicDeviceBase
	{
	public:
		GraphicDeviceBase();
		virtual ~GraphicDeviceBase();

		virtual bool Initialize(const DeviceConfiguration& config, HWND hwnd) = 0;
		virtual bool IsSupported() = 0;
		virtual void GetCurrentConfig(DeviceConfiguration& config) const = 0;
		virtual bool IsWindowed() const = 0;
	};
}
