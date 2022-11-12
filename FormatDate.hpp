#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>

namespace nk125 {
	class dateFormatter {
	public:
		static std::string getDate(std::string format = "%A %d-%m-%Y %H-%M-%S") {
			time_t t = std::time(nullptr);
			tm ltime = *std::localtime(&t);

			std::stringstream s;
			s << std::put_time(&ltime, format.c_str());
			return s.str();
		}
	};
}