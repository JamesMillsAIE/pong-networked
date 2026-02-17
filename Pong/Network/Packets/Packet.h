#pragma once

#include <Core/Common.h>

#include <enet/enet.h>

#include <functional>
#include <vector>

using std::function;
using std::vector;

/**
 * A wrapper for the enet packet which can be executed.
 */
class Packet
{
public:
	/**
	 * @param cb The handler callback to be run when 
	 */
	explicit Packet(const function<void(Packet*)>& cb);

public:
	/**
	 * Converts the internal buffer into an enet packet
	 * @param flag The flag for whether the packet is reliable or unreliable.
	 * @return The serialized packet used for enet.
	 */
	ENetPacket* Encode(ENetPacketFlag flag = ENET_PACKET_FLAG_RELIABLE) const;

	/**
	 * Reads the data from enet into the internal buffer of the packet.
	 * @param packet The enet packet that needs to be put into the internal buffer.
	 */
	void Decode(const ENetPacket* packet);

	/** Run the callback contained within the packet. */
	void Execute();

	/**
	 * Writes a single piece of data into the internal buffer.
	 * @param data The data to be written into the internal buffer.
	 */
	template<typename T>
	void Write(T data);

	/**
	 * Writes an array of data into the internal buffer.
	 * @param data The array of data to be serialized.
	 * @param length The length of the array to be serialized.
	 */
	template<typename T>
	void Write(T* data, uint32 length);

	/**
	 * Reads a portion of memory from the buffer and converts it to the template type.
	 * @return The data converted from binary.
	 */
	template<typename T>
	T Read();

private:
	vector<uint8> m_buffer; /**< The internal buffer of binary data. */
	function<void(Packet*)> m_callback; /**< The function / lambda to run when the packet executes. */
	int32 m_caret; /**< The location in the buffer we are reading from. */

private:
	/**
	 * Writes a series of bytes into the memory buffer to be converted into
	 * an enet packet in the future.
	 * @param bytes The memory to be written into the internal binary buffer.
	 * @param length The length of the array of memory to be written.
	 */
	void SerializeBytes(uint8* bytes, int32 length);

};

template <typename T>
void Packet::Write(T data)
{
	SerializeBytes(reinterpret_cast<uint8*>(&data), sizeof(T));
}

template <typename T>
void Packet::Write(T* data, uint32 length)
{
	SerializeBytes(reinterpret_cast<uint8*>(&length), sizeof(uint32));

	for (uint32 i = 0; i < length; ++i)
	{
		Write(data[i]);
	}
}

template <typename T>
T Packet::Read()
{
	// Copy the memory out of the buffer
	T value;
	std::memcpy(&value, &m_buffer[m_caret], sizeof(T));
	m_caret += sizeof(T);

	return value;
}