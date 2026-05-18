#include "Copter.h"

// init - initialise TETHER mode
bool ModeTether::init(bool ignore_checks)
{
    
    //// Temporary

    /*

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

    */

    return true;
}

void ModeTether::exit()
{
    /*
    
    if (copter.motors != nullptr) {
        copter.motors->set_tether_override(false);
    }

    */
}

// run - main loop for TETHER mode
void ModeTether::run()
{

    /*

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

    // --- 1. Experimental Constants ---
    // User: define your motor constants here
    // e.g. Thrust = cT * RPM^2, Torque = cQ * RPM^2, RPM = k * Throttle + b
    // const float param_cT = 0.0001f; 
    // const float param_cQ = 0.00002f;

    // --- 2. Desired Wrench (Forces and Torques) ---
    // You have the incoming force vector (fx, fy, fz) and target attitude quaternion (q1...q4).
    // Convert the target attitude error into desired torques (tau_x, tau_y, tau_z)
    // Combine this with the tether force request to get the total desired body frame Thrust and Torques.
    
    float desired_thrust = 0.0f; // Compute from your tracking controller
    float desired_tau_x = 0.0f;  // Roll torque
    float desired_tau_y = 0.0f;  // Pitch torque
    float desired_tau_z = 0.0f;  // Yaw torque

    // --- 3. Mixing Matrix ---
    // Map Thrust (T) and Torques (tau) to individual motor thrusts (T1, T2, T3, T4)
    // Example for a standard 'X' quadcopter structure:
    // T1 = (desired_thrust / 4.0f) - (desired_tau_x / L) + (desired_tau_y / L) + (desired_tau_z / cQ)
    float T_motors[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    
    // --- 4. Thrust to Throttle Inversion ---
    // Invert the Thrust model to find target RPM, then map RPM to PWM/Throttle percentage (0.0 to 1.0)
    float throttle_m[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    for (uint8_t i = 0; i < 4; i++) {
        // Example inversion: 
        // float desired_rpm = sqrtf(T_motors[i] / param_cT);
        // throttle_m[i] = (desired_rpm - param_RPM_min) / (param_RPM_max - param_RPM_min);
        
        // Ensure constraints are respected
        throttle_m[i] = constrain_float(throttle_m[i], 0.0f, 1.0f);
    }

    // Apply exact overrides (0.0 to 1.0) for each quadcopter motor
    if (copter.motors != nullptr) {
        copter.motors->set_motor_thrust_override(0, throttle_m[0]);
        copter.motors->set_motor_thrust_override(1, throttle_m[1]);
        copter.motors->set_motor_thrust_override(2, throttle_m[2]);
        copter.motors->set_motor_thrust_override(3, throttle_m[3]);
    }

    // Keep ground handling safe and clear windup in regular attitude controller
    zero_throttle_and_relax_ac(true);

    */
}
