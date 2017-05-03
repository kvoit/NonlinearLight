#include "NonlinearLight.h"

// ----- Initialization and Default Values -----

NonlinearLight::NonlinearLight()
{
} 

const uint8_t NonlinearLight::_steps_ldb[] = { 1, 2, 3, 5, 7, 9, 13, 17, 21, 25 }; //max 
const uint16_t NonlinearLight::_max_stepsum = 1023;

int NonlinearLight::toPWM(const uint8_t level, const int min_pwm, const int max_pwm)
{
    if(level>=100)
        return max_pwm;
    else if(level==1)
        return min_pwm;
    else if(level<=0)
        return 0;
        
    uint16_t stepsum = 0;
    int j;
    for (j = 0; j < level / 10; j++) {
        stepsum += _steps_ldb[j] * 10;
    }
    stepsum += (level % 10) * _steps_ldb[j];

    return min(max_pwm,min_pwm + stepsum * (max_pwm - min_pwm) / _max_stepsum);
}

uint8_t NonlinearLight::toLevel(int pwm, const int min_pwm, const int max_pwm)
{
    if(pwm>=max_pwm)
        return 100;
    else if(pwm==min_pwm)
        return 1;
    else if(pwm<min_pwm)
        return 0;
    
    pwm = (pwm - min_pwm) * _max_stepsum / (max_pwm - min_pwm);
    
    int tenner = 0;
    while((pwm - _steps_ldb[tenner] * 10) >= 0) {
        pwm = pwm - _steps_ldb[tenner] * 10;
        tenner++;
    }
    
    return 10*tenner + pwm/_steps_ldb[tenner];
}
