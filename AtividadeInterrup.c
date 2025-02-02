#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
// Bibliotecas necessárias para funcionamento

// Definição de constantes da matriz de leds
#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define tempo 400

// Variáveis globais para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 0; // Intensidade do vermelho
uint8_t led_g = 0; // Intensidade do verde
uint8_t led_b = 200; // Intensidade do azul

// Definição dos pinos dos leds e botões
#define LED_G_PIN 11
#define LED_B_PIN 12
#define LED_R_PIN 13

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

// Variáveis de controle de estado
static volatile int numero_atual = 0; // Número exibido na matriz de LEDs
static uint32_t last_interrupt_time_a = 0; // Armazena o último tempo de interrupção do botão A
static uint32_t last_interrupt_time_b = 0; // Armazena o último tempo de interrupção do botão B

// Função para inicializar os LEDs e botões
void inicializacaocomponentes() {
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_put(LED_G_PIN, 0);

    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    gpio_put(LED_B_PIN, 0);

    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_put(LED_R_PIN, 0);

    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);
}