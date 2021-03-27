#pragma once
union DSCommandPacket
{
	struct
	{
		int16_t Speed;
		int16_t TurnRate;
		uint16_t STThetaXY;
		uint16_t STThetaZX;
	} fields;
	byte packet[28];	// TODO: Change this to use globally defined length of command packet
};