/*
 * 
 * Don't forget to west espressif monitor -p /dev/ttyUSB0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>


#define MIN_PERIOD PWM_SEC(1U) / 128U
#define MAX_PERIOD PWM_SEC(1U)

// setting up PWM
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));


int main(void)
{
    uint32_t max_period;
    uint32_t period;
    uint8_t dir = 0U;
    int ret;

    // PWM config
    printk("PWM-based blinky\n");

    if (!pwm_is_ready_dt(&pwm_led0)) {
      printf("Error: PWM device %s is not ready\n", pwm_led0.dev->name);
      return 0;
    }

    printk("Calibrating for channel %d... \n", pwm_led0.channel);
    max_period = MAX_PERIOD;
    while(pwm_set_dt(&pwm_led0, max_period, max_period/20)){
        max_period /= 2U;
        if (max_period < (4U * MIN_PERIOD)){
            printf("Error: PWM device does not support a period at least %lu\n", 4U * MIN_PERIOD);
            return 0;
        }
    }

    printk("Done calibrating; maximum/minimum periods %u/%lu nsec\n", max_period, MIN_PERIOD);
    while(1) {
        ret = pwm_set_dt(&pwm_led0, period, period / 20);
        if(ret){
            printf("Error %d: failed to set pulse width\n", ret);
            return 0;
        }

        period = dir ? (period * 2U) : (period / 2U);
        if (period > max_period) {
			      period = max_period / 2U;
			      dir = 0U;
        } else if (period < MIN_PERIOD) {
            period = MIN_PERIOD * 2U;
            dir = 1U;
        }

		    k_sleep(K_SECONDS(4U));
    }


    return 0;
}
