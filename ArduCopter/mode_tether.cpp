#include "Copter.h"

// init - initialise TETHER mode
bool ModeTether::init(bool ignore_checks)
{
    // abort if no position available
    if (!ignore_checks && !copter.ap.initialised) {
        return false;
    }

    // require fresh tether data to enter
    if (AP_HAL::millis() - copter.tether_last_rcv_ms > TETHER_DATA_TIMEOUT_MS) {
        return false;
    }

    // set motors to active tether override
    if (copter.motors != nullptr) {
        copter.motors->set_tether_override(true);
    }

    return true;
}

void ModeTether::exit()
{
    if (copter.motors != nullptr) {
        copter.motors->set_tether_override(false);
    }
}

// run - main loop for TETHER mode
void ModeTether::run()
{
    // Check for tether data timeout
    if (AP_HAL::millis() - copter.tether_last_rcv_ms > TETHER_DATA_TIMEOUT_MS) {
        // Fallback to Land mode if tether data heartbeat is lost
        copter.set_mode(Mode::Number::LAND, ModeReason::CRASH_FAILSAFE);
        return;
    }

    // get vision pose data provided by AHRS (fusing the Vicon data)
    // currently just provided as example hook
    Vector3f current_pos;
    if (!ahrs.get_position(current_pos)) { 
        // position lost fallback if needed
    }

    // Pull the latest target struct from MAVROS
    float x = copter.tether_control_cmd.x;
    float y = copter.tether_control_cmd.y;
    float z = copter.tether_control_cmd.z;

    float fx = copter.tether_control_cmd.fx;
    float fy = copter.tether_control_cmd.fy;
    float fz = copter.tether_control_cmd.fz;

    float q1 = copter.tether_control_cmd.q[0];
    float q2 = copter.tether_control_cmd.q[1];
    float q3 = copter.tether_control_cmd.q[2];
    float q4 = copter.tether_control_cmd.q[3];

    // TODO: Define experimentally-determined mapping
    // Calculate mapping to 4 motors here based on quadcopter config
    // ... math ...
    
    // Default mapping sample mapping (replace with custom matrix math)
    float base_throttle = 0.3f; // hover roughly
    float thrust_m1 = base_throttle;
    float thrust_m2 = base_throttle;
    float thrust_m3 = base_throttle;
    float thrust_m4 = base_throttle;

    // Apply exact overrides (0.0 to 1.0) for each quadcopter motor
    if (copter.motors != nullptr) {
        copter.motors->set_motor_thrust_override(0, thrust_m1);
        copter.motors->set_motor_thrust_override(1, thrust_m2);
        copter.motors->set_motor_thrust_override(2, thrust_m3);
        copter.motors->set_motor_thrust_override(3, thrust_m4);
    }

    // Keep ground handling safe and clear windup in regular attitude controller
    zero_throttle_and_relax_ac(true);
}
