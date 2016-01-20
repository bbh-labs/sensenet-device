#ifndef OPTICAL_DUST_HPP
#define OPTICAL_DUST_HPP

class OpticalDust {
public:
	float value;

	OpticalDust();
	void init();
	void update();

private:
	float mVoMeasured;
	float mCalcVoltage;
};

#endif
