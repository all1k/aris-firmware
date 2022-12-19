#ifndef _ARIS_TEST_UTILITIES_HPP_
#define _ARIS_TEST_UTILITIES_HPP_

#ifdef TEMPERATURE_SENSOR_TEST
#define QUANTITY "Temperature"
#define UNIT     "Degree Celcius"
#elif defined TURBIDITY_SENSOR_TEST
#define QUANTITY "Turbidity"
#define UNIT     "NTU"
#elif defined PH_SENSOR_TEST
#define QUANTITY "pH"
#define UNIT     ""
#elif defined EC_SENSOR_TEST
#define QUANTITY "Conductivity"
#define UNIT     "ms/cm"
#elif defined DO_SENSOR_TEST
#define QUANTITY "Dissolved Oxygen"
#define UNIT     "mg/L"
#endif

#include <unity.h>

#include <numeric>
#include <string>
#include <vector>

namespace aristest {

void logValue(float value) {
	std::string msg;
	msg.append(QUANTITY);
	msg.append(" = ");
	msg.append(std::to_string(value));
	msg.append(" ");
	msg.append(UNIT);
	TEST_MESSAGE(msg.c_str());
}

void logValue(
	float value, const std::string& quantity, const std::string& unit
) {
	std::string msg;
	msg.append(quantity);
	msg.append(" = ");
	msg.append(std::to_string(value));
	msg.append(" ");
	msg.append(unit);
	TEST_MESSAGE(msg.c_str());
}

template <typename Type>
float getAverage(std::vector<Type> const& v) {
	if (v.empty()) {
		return 0;
	} else {
		return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
	}
}

template <typename Type>
void checkDataValidity(Type data, Type upper_tresh, Type low_tresh) {
	if (data < low_tresh) {
		logValue(data);
		TEST_FAIL();
	} else if (data > upper_tresh) {
		logValue(data);
		TEST_FAIL();
	} else {
		logValue(data);
		TEST_PASS();
	}
}

}  // namespace aristest

#endif
