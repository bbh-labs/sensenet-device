#ifndef OPTICAL_DUST_HPP
#define OPTICAL_DUST_HPP

class OpticalDust {
public:
	static const float minValue;
	static const float maxValue;
	float value;

	OpticalDust();
	void init();
	void update();

private:
	unsigned long mStartTime;
	unsigned long mLowPulseOccupancy;
	float mCalcVoltage;
};

#endif
