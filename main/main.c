#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define LOG_TAG "TEST"

static void print_mac(esp_mac_type_t type) {
    uint8_t a[6] = {};
    esp_read_mac(a, type); 
    for (int i=0; i<6; i++) {
        printf("%02X", a[i]);
    }
    puts("\n"); 
}

void app_main(void)
{
    esp_err_t ret;

    // Initialize NVS.
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    int i = 0;
    while (1) {
        printf("[%d] Hello world!\n", i);
        print_mac(ESP_MAC_WIFI_STA);
        print_mac(ESP_MAC_WIFI_SOFTAP);
        print_mac(ESP_MAC_BT);
        print_mac(ESP_MAC_ETH);

        i++;
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

