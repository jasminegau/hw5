#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

bool scheduleHelper(size_t day, DailySchedule& sched, std::vector<int>& wshift, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts);
bool combination(size_t day, vector<Worker_T>& current, size_t workerIndex, DailySchedule& sched, vector<int>& wshift, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts);
bool placew(Worker_T worker, size_t day, const std::vector<int>& wshift, const AvailabilityMatrix& avail, size_t maxShifts);

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    vector<int> wshift;
    for(size_t i=0; i<avail[0].size(); ++i){
      wshift.push_back(0);
    }

    sched.clear();
    return scheduleHelper(0, sched, wshift, avail, dailyNeed, maxShifts);

}

bool combination(size_t day, vector<Worker_T>& current, size_t workerIndex, DailySchedule& sched, vector<int>& wshift, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts) {
    if (current.size() == dailyNeed) {
        sched.push_back(current);
        bool c = scheduleHelper(day + 1, sched, wshift, avail, dailyNeed, maxShifts);
        if (c) {
            return true;
        }
        sched.pop_back();  
    }

    for (size_t i = workerIndex; i < avail[day].size(); ++i) {
        if (placew(i, day, wshift, avail, maxShifts)) {
            wshift[i]++;
            current.push_back(i);
            bool check = combination(day, current, i + 1, sched, wshift, avail, dailyNeed, maxShifts);
            if (check) {
                return true;
            }
            current.pop_back(); 
            wshift[i]--;
        }
    }
    return false;
}

bool scheduleHelper(size_t day, DailySchedule& sched, std::vector<int>& wshift, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts) {
    if (day >= avail.size()) return true; 
    vector<Worker_T> current; 
    return combination(day, current, 0, sched, wshift, avail, dailyNeed, maxShifts);
}

bool placew(Worker_T worker, size_t day, const std::vector<int>& wshift, const AvailabilityMatrix& avail, size_t maxShifts) {
    return avail[day][worker] && wshift[worker] < maxShifts;
}