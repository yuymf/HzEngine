#include "hzpch.h"
#include "DataBuffer.h"

namespace Hazel {

	DataBuffer::DataBuffer(uint64_t dataBufferSize)
	{
		Resize(dataBufferSize);
	}

	DataBuffer::~DataBuffer()
	{
		m_DataBufferSize = 0;
	}

	void DataBuffer::Resize(uint64_t dataBufferSize)
	{
		m_DataBuffer = Ref<uint8_t>(new uint8_t[dataBufferSize], std::default_delete<uint8_t>());
		m_DataBufferSize = dataBufferSize;
	}

	void DataBuffer::SetDataBuffer(const void* dataBuffer)
	{
		memcpy(m_DataBuffer.get(), dataBuffer, m_DataBufferSize);
	}

	uint64_t DataBuffer::GetDataBufferSize() const
	{
		return m_DataBufferSize;
	}

	const Ref<uint8_t>& DataBuffer::GetDataBuffer() const
	{
		return m_DataBuffer;
	}

	Ref<DataBuffer> DataBuffer::DepthCopy(Ref<DataBuffer> dataBuffer)
	{
		auto CopyBuffer = CreateRef<DataBuffer>(dataBuffer->m_DataBufferSize);
		memcpy(CopyBuffer.get(), dataBuffer->m_DataBuffer.get(), dataBuffer->m_DataBufferSize);
		return CopyBuffer;
	}

	DataBuffer::operator bool() const
	{
		return m_DataBuffer != nullptr;
	}

}
