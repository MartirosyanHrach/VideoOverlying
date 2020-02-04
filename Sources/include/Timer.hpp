#ifndef TIIMER
#define TIMER

#include <iostream>
#include <chrono>

/**
 * @brief   This class intends to measure performance
 **/
class Timer {
public:
	/**
	 * @brief Class constructor, which returns a time point representing the current point in time. 		
	 **/
    Timer() : m_start_time_point (std::chrono::high_resolution_clock::now()) {}

	/**
	 * @brief   Destructor of class, which calculates the life time of Timer object.
	 **/
    ~Timer() {
        Stop();
    }

private:
	/**
	 * @brief Meauseres the difference beetwen creation and the destructon of the object.		
	 **/
    void Stop() {
        const auto end_time_point = std::chrono::high_resolution_clock::now();
        const auto start = std::chrono::time_point_cast<std::chrono::seconds>(m_start_time_point).time_since_epoch().count();
        const auto end = std::chrono::time_point_cast<std::chrono::seconds>(end_time_point).time_since_epoch().count();
        const auto duration = end - start;
        constexpr double sec_to_min_coeff = 0.0166667;
        const double minutes = duration * sec_to_min_coeff;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time_point;
};
#endif