#include "KeyCodes.h"

std::bitset<COUNT_KEYCODES> GetKeyCodeBits(KeyCode code)
{
std::bitset<COUNT_KEYCODES> bits;

bits.set(code);

return bits;
}