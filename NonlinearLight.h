#ifndef NonlinearLight_h
#define NonlinearLight_h

#include "Arduino.h"


class NonlinearLight
{
public:
 NonlinearLight();   
 
 static int toPWM(const uint8_t level, const int min_pwm, const int max_pwm);
 static uint8_t toLevel(int pwm, const int min_pwm, const int max_pwm);

private:
 static const uint8_t _steps_ldb[];
 static const uint16_t _max_stepsum;
};

#endif 


 
