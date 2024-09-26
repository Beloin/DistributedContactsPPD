////////////////////////////////////////////////////////////////////////////////
// File:        converters.h
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////

#ifndef UTILS_CONVERTERS_H
#define UTILS_CONVERTERS_H

#include <cstdint>
#include <string>

uint32_t convert4(char *buffer);

void createPaddedString(char *buffer, const std::string& msg, size_t lenj = 256);

std::string parseNullTerminatedString(char *buffer);

#endif /* UTILS_CONVERTERS_H */
