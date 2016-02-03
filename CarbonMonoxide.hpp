#ifndef CARBON_MONOXIDE_HPP
#define CARBON_MONOXIDE_HPP

#include <stdint.h>

class CarbonMonoxide {
public:
	int16_t value;

	CarbonMonoxide();
	void init();
	void update();
};

#endif
