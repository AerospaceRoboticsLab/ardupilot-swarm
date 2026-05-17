#include "Copter.h"

// Temporary stub for TETHER mode.
// This keeps the build working while we test the 3-UAV GUIDED/MAVROS workflow.
// Do not use TETHER mode with this stub implementation.

bool ModeTether::init(bool ignore_checks)
{
    (void)ignore_checks;
    return true;
}

void ModeTether::exit()
{
}

void ModeTether::run()
{
    // Stubbed intentionally.
    // Normal 3-UAV testing uses GUIDED via MAVROS, not TETHER mode.
}
