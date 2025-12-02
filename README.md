# Fúria das Capivaras - Jogo de Reação para Arduino

Este projeto é um jogo de reação no estilo "Whac-a-Mole" (Acerte a Toupeira) com uma divertida temática de capivaras, implementado em um Arduino. O objetivo é testar e treinar os reflexos do jogador, que deve pressionar o botão correspondente a um LED que se acende aleatoriamente.

A dificuldade do jogo é progressiva: conforme o jogador pontua, o tempo para reagir diminui e o intervalo entre as rodadas fica mais curto.

## Componentes Necessários

*   1x Placa Arduino (Uno, Nano, etc.)
*   5x LEDs (qualquer cor)
*   5x Push Buttons (botões de pressão)
*   1x Buzzer passivo
*   5x Resistores de 220Ω (para os LEDs)
*   5x Resistores de 10kΩ (pull-down para os botões, opcional se usar `INPUT_PULLUP`)
*   1x Protoboard
*   Jumpers (fios) para as conexões

## Como Jogar

1.  **Início:** Após carregar o código, o jogo aguardará. Pressione qualquer um dos cinco botões para começar a partida.
2.  **Jogabilidade:** Um dos cinco LEDs se acenderá. Você deve pressionar o botão correspondente o mais rápido possível, antes que o LED se apague. O jogador só deve utilizar um dedo indicador para apertar os botões.
3.  **Pontuação:**
    *   **Acerto:** Se pressionar a tempo, você ganha 1 ponto e um som de sucesso é emitido.
    *   **Erro:** Se não pressionar a tempo ou pressionar o botão errado (lógica não implementada, mas pode ser adicionada), você perde uma vida.
4.  **Vidas:** O jogador começa com 3 vidas.
5.  **Fim de Jogo:** O jogo termina quando as vidas chegam a zero. Sua pontuação final será exibida no Monitor Serial, e os LEDs piscarão continuamente. Pressione qualquer botão para reiniciar.