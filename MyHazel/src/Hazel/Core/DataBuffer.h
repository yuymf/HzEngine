#pragma once

namespace Hazel {
	class DataBuffer
	{
	public:
		DataBuffer(uint64_t dataBufferSize, uint8_t channel);
		DataBuffer() = default;
		DataBuffer(const DataBuffer&) = default;
		~DataBuffer();

		void Resize(uint64_t dataBufferSize);
		void SetDataBuffer(const void* dataBuffer);

		uint64_t GetDataBufferSize()const;
		const Ref<uint8_t>& GetDataBuffer()const;

		template<typename T>
		T* As()
		{
			return (T*)m_DataBuffer.get();
		}

		static Ref<DataBuffer> DepthCopy(Ref<DataBuffer> dataBuffer);

		operator bool() const;

	private:
		Ref<uint8_t> m_DataBuffer;
		uint64_t m_DataBufferSize;
		uint8_t m_Channel;
	};
}
