#include "split.hpp"
#include <vector>

std::vector<std::string> split(const std::string &a, const std::string &match) {
  size_t pos = 0;
  size_t lastpos = pos;
  std::vector<std::string> tokens{};
  std::string currentToken;
  while ((pos = a.find(match, lastpos)) != std::string::npos) {
    currentToken = a.substr(lastpos, pos - lastpos);
    tokens.push_back(currentToken);
    lastpos = pos + match.length();
  }

  if (lastpos < a.length()) {
    currentToken = a.substr(lastpos);
    tokens.push_back(currentToken);
  }

  return tokens;
}
