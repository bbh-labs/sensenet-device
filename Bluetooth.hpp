#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include <stddef.h>

class Bluetooth {
public:
	Bluetooth();
	void init();
	void update();
	void write(const void *data, size_t size);
	void flush();
	bool connected() const;

private:
	int mState;
};

#endif
