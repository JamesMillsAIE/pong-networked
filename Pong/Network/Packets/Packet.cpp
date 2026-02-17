#include "pch.h"
#include "Packet.h"

Packet::Packet(const function<void(Packet*)>& cb)
	: m_callback{ cb }, m_caret{ 0 }
{
}

ENetPacket* Packet::Encode(const ENetPacketFlag flag) const
{
	// Converts the internal buffer into an enet packet.
	ENetPacket* packet = enet_packet_create(
		m_buffer.data(),
		m_buffer.size(),
		flag
	);

	return packet;
}

void Packet::Decode(const ENetPacket* packet)
{
	m_buffer.assign(packet->data, packet->data + packet->dataLength);
	m_caret = 0;
}

void Packet::Execute()
{
	// Execute the handler callback provided it was passed
	if (m_callback != nullptr)
	{
		m_callback(this);
	}
}

void Packet::SerializeBytes(uint8* bytes, const int32 length)
{
	// Insert the memory into the buffer
	m_buffer.insert(m_buffer.end(), bytes, bytes + length);
}

// String specialisations
template<>
void Packet::Write(string data)
{
	int32 length = static_cast<int32>(data.length());

	// Write the length of the string and the string into the memory buffer
	SerializeBytes(reinterpret_cast<uint8*>(&length), sizeof(int32));
	SerializeBytes(reinterpret_cast<uint8*>(data.data()), length);
}

template<>
string Packet::Read()
{
	// Read the length of the string array
	int32 valueLength;
	std::memcpy(&valueLength, &m_buffer[m_caret], sizeof(int32));
	m_caret += sizeof(int32);

	// Read the string memory from the buffer
	string str;
	str.assign(reinterpret_cast<const char*>(&m_buffer[m_caret]), valueLength);
	m_caret += valueLength;

	// Return the read string
	return str;
}