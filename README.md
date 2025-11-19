# 🕹️ Jogo Bata na Capivara com Arduino

Um jogo de reflexos onde o jogador deve pressionar o botão correspondente ao LED que acender aleatoriamente. O objetivo é acumular a maior pontuação possível antes de perder as 3 vidas.

## 📋 Funcionalidades
* **Sistema de Vidas:** O jogador começa com 3 vidas.
* **Pontuação:** Exibida no Monitor Serial a cada acerto.
* **Feedback Sonoro:** Bipes indicam acertos (agudo).
* **Dificuldade:** O tempo de reação é limitado.

## 🛠️ Lista de Materiais
* 1x Arduino Uno
* 5x LEDs Vermelhos (com resistores de 220Ω)
* 5x Botões / Pushbuttons (com resistores de 10kΩ para pull-down)
* 1x Buzzer (Piezo)
* 1x Protoboard e Jumpers

## 🔌 Esquema de Ligações (Pinout)

| Componente | Pinos no Arduino |
| :--- | :--- |
| **Botões (Entrada)** | Pinos Digitais **3, 4, 5, 6, 7** |
| **LEDs (Saída)** | Pinos Digitais **8, 9, 10, 11, 12** |
| **Buzzer** | Pino Digital **13** |

> **Nota:** Os botões e LEDs devem ser montados na mesma ordem sequencial (o Botão no pino 3 controla o LED no pino 8, e assim por diante).
