#pragma once

static const uint8_t COM_BUFFER_SIZE = 32;
static const uint8_t ENCODED_PACKET_SIZE = COM_BUFFER_SIZE - 1;
static const uint8_t PACKET_SIZE = ENCODED_PACKET_SIZE - 1;
static const uint8_t PACKET_PAYLOAD_SIZE = PACKET_SIZE - 2;

