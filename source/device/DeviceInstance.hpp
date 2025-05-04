#ifndef __SPARK_DEVICE_DEVICEINSTANCE_HPP_INCLUDED__
#define __SPARK_DEVICE_DEVICEINSTANCE_HPP_INCLUDED__

namespace spark {
	namespace device {
		class AbstractSparkDevice;
	}
}

namespace spark {
	namespace device {
		
		class DeviceInstance
		{
		public:
			static  spark::device::AbstractSparkDevice*  Instance;
		};
		
	} // end namespace device
} // end namespace spark
#endif