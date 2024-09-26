#include "converters.h"
#include <cstring>

uint32_t convert4(char *buffer) {
  return (static_cast<uint32_t>(buffer[0]) << 24) |
         (static_cast<uint32_t>(buffer[1]) << 16) |
         (static_cast<uint32_t>(buffer[2]) << 8) |
         static_cast<uint32_t>(buffer[3]);
}

void createPaddedString(char *buffer, const std::string &msg, size_t lenj) {
  std::memset(buffer, 0, lenj);
  std::memcpy(buffer, msg.c_str(), std::min(msg.size(), lenj - 1));
}

std::string parseNullTerminatedString(char *buffer) {
  return std::string(buffer).c_str();
}
