# Projeto de Interrupções e Controle de LEDs

## Descrição
Este repositório apresenta a resolução da atividade da U4 do EmbarcaTech - da aula 27/01/2025 - visando consolidar o entendimento dos conceitos relacionados ao uso de interrupções no microcontrolador RP2040 e funcionalidades do kit do BitDogLab.

O projeto consiste em um contador interativo, utilizando um LED RGB, uma matriz de LEDs WS2812 e dois botões para interação do usuário. 

## Funcionalidades
1. **LED RGB**:
   - O LED vermelho do LED RGB pisca continuamente a uma taxa de 5 vezes por segundo.

2. **Matriz de LEDs WS2812**:
   - A matriz de LEDs exibe números de 0 a 9, começando inicialmente no 0.

3. **Interação do Usuário**:
   - O projeto funciona como um contador interativo:
     - **Botão A**: Incrementa o número exibido na matriz de LEDs toda vez que é pressionado.
     - **Botão B**: Decrementa o número exibido na matriz de LEDs toda vez que é pressionado.
   - **Limites da Contagem**:
     - O contador tem um limite mínimo de 0 e um máximo de 9.
     - Se o usuário tentar incrementar além de 9 ou decrementar abaixo de 0, a contagem reinicia:
       - Ao pressionar o botão A no número 9, o contador volta para 0.
       - Ao pressionar o botão B no número 0, o contador volta para 9.

## Componentes e Ferramentas Utilizados
- Matriz 5x5 de LEDs WS2812 (endereçáveis), conectada à GPIO 7.
- LED RGB, com os pinos conectados às GPIOs 11, 12 e 13.
- Botão A conectado à GPIO 5.
- Botão B conectado à GPIO 6.
- Simulador Wokwi.
- Placa de desenvolvimento BitDogLab.

## Linguagem Utilizada
- **C**

## Passo a Passo da Implementação
Abaixo encontra-se o resumo dos passos que foram realizados para realização da atividade.
### 1. Configuração do Ambiente
1. Foi configurado no vscode o ambiente para realização da atividade.
2. O Wokwi foi configurado para simular o RP2040 com os componentes mencionados.
3. O repositório foi criado e os arquivos do projeto foram organizados.

### 2. Configuração dos Pinos
- As GPIOs dos botões foram configuradas como **entradas** com resistores **pull-up internos**.
- Os LEDs foram configurados como **saídas**.

### 3. Implementação das Interrupções
- Foram configuradas interrupções (IRQ) para os botões A e B.
- Ao detectar um pressionamento, o valor do contador foi alterado.

### 4. Tratamento de Bouncing (Debouncing)
Os botões mecânicos sofrem com o efeito de bouncing, onde um único pressionamento pode gerar várias detecções de interrupção devido a oscilações elétricas. Para corrigir esse problema, foi implementado um método de debouncing via software:

- **Método Utilizado**:
  - Foi utilizado um delay curto após a detecção de interrupção para ignorar leituras rápidas consecutivas.
  - Uma variável de estado impede a execução da rotina até que o botão seja liberado.

### 5. Exibição dos Números na Matriz WS2812
- Cada número de 0 a 9 é representado por um padrão fixo de LEDs acesos.
- O código traduz o valor do contador para o padrão correspondente na matriz.

### 6. Testes e Validação
- O comportamento dos LEDs e botões foi testado no Wokwi.
- Foi verificado se o debouncing estava funcionando corretamente.
- Foi confirmado se o contador reseta corretamente nos limites.

## Desenvolvedor
- **Camila Ramos Gomes**

## Vídeo Explicativo
[Link do vídeo explicativo]

**LEMBRETE:** Ao clonar o repositório certifique-se de ter o sdk da raspberry pi pico w para importar o projeto da maneira correta.
