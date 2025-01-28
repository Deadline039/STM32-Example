#include "eez-flow.h"

#ifdef DEBUG

namespace eez {
namespace debug {

void pushDebugTraceHook(const char *message, size_t messageLength) {
    LV_UNUSED(messageLength);
    puts("DEBUG: ");
    puts(message);
}

void pushInfoTraceHook(const char *message, size_t messageLength) {
    LV_UNUSED(messageLength);
    puts("Info: ");
    puts(message);
}

void pushErrorTraceHook(const char *message, size_t messageLength) {
    LV_UNUSED(messageLength);
    puts("Error: ");
    puts(message);
}

} // namespace debug
} // namespace eez

#endif /* DEBUG */