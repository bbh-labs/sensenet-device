#ifndef UV_HPP
#define UV_HPP

class UV {
public:
	static const float minValue;
	static const float maxValue;
	float value;

	UV();
	void init();
	void update();
};

#endif
