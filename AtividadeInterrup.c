#include <stdio.h>
#include "pico/stdlib.h"

//Definição dos pinos dos leds RGB, matriz de leds e botões
#define LED_G_PIN 11
#define LED_B_PIN 12
#define LED_R_PIN 13

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

#define MATRIZ_LEDS 7

static volatile uint a = 0; //Contador

//Função para inicializar os leds e botões
void inicializacaocomponentes(){

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

//Rotina da interrupção
static void gpio_irq_handler(uint gpio, uint32_t events){
    if (gpio_get(BUTTON_A_PIN)==0){

    }    
    else (gpio_get(BUTTON_B_PIN)==0);
}

//Função que fará o led vermelho picar 5 vezes por segundo
void blink_red(){
    for (int i = 0; i < 5; i++){
        gpio_put(LED_R_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_R_PIN, 0);
        sleep_ms(100);
    }
}

//Função principal
int main()
{
    inicializacaocomponentes();
    stdio_init_all();

    //Configura a interrupção
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    //Rotina principal
    while (true)
    {
        blink_red();
    }
    return 0;
}