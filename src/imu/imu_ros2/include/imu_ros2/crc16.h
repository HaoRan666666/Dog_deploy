#pragma once

#include <cstdint>

// Standard CRC-16/XMODEM (crc << 8)
uint16_t crc16_compute(const uint8_t *ptr, uint16_t len);

// As-written in the manual (crc << 1)
uint16_t crc16_v1(const uint8_t *ptr, uint16_t len);
