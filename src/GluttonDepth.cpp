#include "GluttonDepth.h"
#include <vector>
#include <queue>
#include "Point.h"
#include "Time.h"
#include "TimeInterval.h"
#include "TreatmentType.h"
#include "Treatment.h"
#include "Nurse.h"
#include "Patient.h"
#include "Appointment.h"
#include "Inputs.h"
#include "Algorithm.h"

GluttonDepth::GluttonDepth(Inputs *inputs, short speed)
    :Algorithm(inputs, speed)
{}

void GluttonDepth::find_appointments()
{
    // Initialize nurses priority queue
    std::priority_queue<Nurse*, std::vector<Nurse*>, ComparePointers> nurses_pqueue;
    for (int i = 0, len = m_inputs->nurses_size(); i < len; ++i)
    {
        nurses_pqueue.push(m_inputs->get_nurse(i));
    }

    // Find appointments
    int appointments_left = m_inputs->treatments_size();
    while (!nurses_pqueue.empty() && appointments_left > 0)
    {
        // Get nurse
        Nurse *nurse = nurses_pqueue.top();
        nurses_pqueue.pop();

        // Get nearest appointment available
        Appointment *appointment = nearest_appointment(*nurse);
        while (appointment != nullptr)
        {
            // Set treatment to scheduled
            appointment->treatment()->is_scheduled(true);
            --appointments_left;

            // Add appointment in the list
            m_appointments.push_back(appointment);

            // Update nurse
            nurse->position(appointment->location());
            nurse->available(appointment->schedule().end_time());

            // Check if the nurse has ended her day
            if (!(nurse->available() < nurse->timetable().end_time()))
            {
                break;
            }

            // Get nearest appointment available
            appointment = nearest_appointment(*nurse);
        }
    }
}
