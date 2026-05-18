#include "Copter.h"

#if MODE_TETHER_ENABLED

// init - initialise TETHER mode
bool ModeTether::init(bool ignore_checks)
{
    (void)ignore_checks;

    if (motors == nullptr) {
        return false;
    }

    motors->clear_tether_override();
    motors->set_tether_override(true);
    return true;
}

void ModeTether::exit()
{
    if (motors != nullptr) {
        motors->clear_tether_override();
        motors->set_tether_override(false);
    }
}

// run - main loop for TETHER mode
void ModeTether::run()
{
    if (motors == nullptr) {
        return;
    }

    if (!motors->armed()) {
        motors->clear_tether_override();
        motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
        return;
    }

    motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::THROTTLE_UNLIMITED);

    // Temporary SITL-only path check. This is not a tether controller and does
    // not implement payload dynamics, force allocation, or MAVLink input.
    motors->set_tether_override(true);
    for (uint8_t i = 0; i < 4; i++) {
        motors->set_motor_thrust_override(i, 0.10f);
    }
}

#endif  // MODE_TETHER_ENABLED
