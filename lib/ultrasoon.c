#include "ultrasoon.h"
#include "debug.h"
#include "millis.h"
#include <avr/io.h>
#include <util/delay.h>

/*
 * init a motor
 */
void ultrasoon_init(ultrasoon_t ultrasoon)
{
    basic_initInput(ultrasoon.echo);
    basic_initOutput(ultrasoon.trigger);
}

/*
 * set distance of a ultrasoon
 */
void ultrasoon_setDistance(ultrasoon_t* ultrasoon)
{
    uint8_t* echo = basic_portRegister(ultrasoon->trigger.port, BASIC_PIN);

    // if echo is high, is because the ultrasoon is busy;
    if (*echo & _BV(ultrasoon->echo.pin)) {
        return;
    }

    uint8_t* trigger = basic_portRegister(ultrasoon->trigger.port, BASIC_PORT);
    uint32_t time;
    uint32_t timeout = ultrasoon->max_distance * 2.2 / SPEED_OF_SOUND;

    *trigger &= ~_BV(ultrasoon->trigger.pin);
    _delay_us(2);
    *trigger ^= _BV(ultrasoon->trigger.pin);
    _delay_us(10);
    *trigger ^= _BV(ultrasoon->trigger.pin);

    ultrasoon->start_time = micros();
    time = ultrasoon->start_time + timeout;
    while (!(*echo & _BV(ultrasoon->echo.pin))) {
        if (time < micros()) {
            ultrasoon->distance = ultrasoon->max_distance;
            return;
        }
    }

    ultrasoon->start_time = micros();
    time = ultrasoon->start_time + timeout;
    while ((*echo & _BV(ultrasoon->echo.pin))) {
        if (time < micros()) {
            ultrasoon->distance = ultrasoon->max_distance;
            return;
        }
    }

    ultrasoon->end_time = micros();

    ultrasoon->distance = (ultrasoon->end_time - ultrasoon->start_time) * SPEED_OF_SOUND / 2;
}
