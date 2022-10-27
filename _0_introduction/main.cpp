/*//////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
**cmd
**cmd -->> cmake-gui .
**"/build"
**configure
**MinGW Makefiles
**Specify toolchain file for cross-compiling
**C:/Espressif/frameworks/esp-idf-v5.0/tools/cmake/toolchain-esp32.cmake
**Generate
**cmd continue
**_0_introduction>cd build
**_0_introduction\build>make
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////*/

#include <cstddef>
#include <cstdint>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/platform.h"
#include "pico/time.h"
#include "pico/bootrom.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

#include "draft.hpp"
#include "pico/cyw43_arch.h"

const uint LED_PIN = 25;
char send_data[] = {"HELLO FROM PICO!"};
char read_string[32]={"0"};
char buffer[32]={"0"};

int main() {
    stdio_init_all();
    sleep_ms(1000);

    // GPIO Initialize
    cyw43_arch_init();
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // UART Initialize
    uart_init(uart0, 9600);
    gpio_set_function(0, GPIO_FUNC_UART); //RX
    gpio_set_function(1, GPIO_FUNC_UART); //TX

    while(true){ // LED ON -->> UART WRITE/READ -->> LED OFF
        // LED ON
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);

        // UART WRITE
        for(int i = 0; i < sizeof(send_data); ++i) {
            buffer[i] = send_data[i];
        }
        uart_write_blocking(uart0, (const uint8_t *)buffer, 32);
        sleep_ms(125);

        //LED BLINK
        for(int i=0; i<5; i++) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            sleep_ms(1);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            sleep_ms(1);
        }
        /*
        // UART READ
        uart_read_blocking(uart0, &read_string, sizeof(read_string));
        for(int i = 0; i < sizeof(read_string); i++) {
            buffer[i] = read_string[i];
        }
        uart_write_blocking(uart0, &buffer, sizeof(buffer));
        sleep_ms(125);
        */
        
        // LED OFF
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(1000);
    }
}