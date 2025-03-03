#include "engine/input/include/input_listener.h"

#include "app/include/debug.h"

namespace ho_renderer {
bool InputListener::is_active() const { return is_active_; }
void InputListener::Active() { is_active_ = true; }
void InputListener::Inactive() { is_active_ = false; }
}  // namespace ho_renderer