const byte pinosLED[] = { 8, 9, 10, 11, 12 };
const byte pinosBotao[] = { 3, 4, 5, 6, 7 };
const byte pinoBuzzer = 13;
const byte numCapivaras = 5;

const int TEMPO_REACAO_INICIAL = 1000;
const int TEMPO_REACAO_MINIMO = 200;
const int PONTOS_LIMITE_REDUCAO = 40;
const int MAX_DELAY_BASE = 1500;
const int REDUCAO_TOTAL = TEMPO_REACAO_INICIAL - TEMPO_REACAO_MINIMO;

int tempoCapivaraAcesa = TEMPO_REACAO_INICIAL;
byte vidas = 3;
int pontuacao = 0;
bool jogoRodando = false;

bool algumBotaoPressionado();
void piscarTodosLEDs();
void apagarTodosLEDs();
void imprimirTelaInicial();
void imprimirInicioDeJogo();
void imprimirFimDeJogo(int pontuacao);
void imprimirStatus(bool acertou, int pontuacao, byte vidas, int tempoReacao);
void limparConsole();

void setup() {
  Serial.begin(9600);

  pinMode(pinoBuzzer, OUTPUT);

  for (int i = 0; i < numCapivaras; i++) {
    pinMode(pinosLED[i], OUTPUT);
    pinMode(pinosBotao[i], INPUT);
    digitalWrite(pinosLED[i], LOW);
  }

  randomSeed(analogRead(A0));

  imprimirTelaInicial();
}

void loop() {

  if (!jogoRodando) {
    if (algumBotaoPressionado()) {
      jogoRodando = true;
      tone(pinoBuzzer, 2000, 500);
      imprimirInicioDeJogo();
      delay(500);
    }
    return;
  }

  if (vidas <= 0) {
    tone(pinoBuzzer, 2000, 500);
    imprimirFimDeJogo(pontuacao);

    while (!algumBotaoPressionado()) {
      piscarTodosLEDs();
    }

    vidas = 3;
    pontuacao = 0;
    tempoCapivaraAcesa = TEMPO_REACAO_INICIAL;
    jogoRodando = false;
    limparConsole();
    imprimirTelaInicial();
    apagarTodosLEDs();
    delay(1000);
    return;
  }

  long reducao = (long)pontuacao * REDUCAO_TOTAL / PONTOS_LIMITE_REDUCAO;
  tempoCapivaraAcesa = TEMPO_REACAO_INICIAL - reducao;
  if (tempoCapivaraAcesa < TEMPO_REACAO_MINIMO) {
    tempoCapivaraAcesa = TEMPO_REACAO_MINIMO;
  }

  int reducaoMaxDelay = pontuacao * 25;
  int maxDelay = MAX_DELAY_BASE - reducaoMaxDelay;
  if (maxDelay < 500) {
    maxDelay = 500;
  }



  byte capivaraSorteada = random(0, numCapivaras);

  digitalWrite(pinosLED[capivaraSorteada], HIGH);
  long tempoInicio = millis();
  bool acertou = false;

  while (millis() - tempoInicio < tempoCapivaraAcesa) {
    if (digitalRead(pinosBotao[capivaraSorteada]) == HIGH) {
      acertou = true;
      break;
    }
  }

  digitalWrite(pinosLED[capivaraSorteada], LOW);

  if (acertou) {
    pontuacao++;
    tone(pinoBuzzer, 2000, 50);
    imprimirStatus(acertou, pontuacao, vidas, tempoCapivaraAcesa);
  } else {
    vidas--;
    imprimirStatus(acertou, pontuacao, vidas, tempoCapivaraAcesa);
  }

  delay(random(500, maxDelay + 1));
}

bool algumBotaoPressionado() {
  for (int i = 0; i < numCapivaras; i++) {
    if (digitalRead(pinosBotao[i]) == HIGH) {
      return true;
    }
  }
  return false;
}

void piscarTodosLEDs() {
  for (int i = 0; i < numCapivaras; i++) {
    digitalWrite(pinosLED[i], HIGH);
  }
  delay(250);
  for (int i = 0; i < numCapivaras; i++) {
    digitalWrite(pinosLED[i], LOW);
  }
  delay(250);
}

void apagarTodosLEDs() {
  for (int i = 0; i < numCapivaras; i++) {
    digitalWrite(pinosLED[i], LOW);
  }
}

void imprimirTelaInicial() {
  Serial.println(F("  _____  __       _             _              ____            _                          _ "));
  Serial.println(F(" |  ___|/_/_ _ __(_) __ _    __| | __ _ ___   / ___|__ _ _ __ (_)_   ____ _ _ __ __ _ ___| |"));
  Serial.println(F(" | |_ | | | | '__| |/ _` |  / _` |/ _` / __| | |   / _` | '_ \\| | \\ / / _` | '__/ _` / __| |"));
  Serial.println(F(" |  _|| |_| | |  | | (_| | | (_| | (_| \\__ \\ | |__| (_| | |_) | |\\ V / (_| | | | (_| \\__ \\_|"));
  Serial.println(F(" |_|   \\__,_|_|  |_|\\__,_|  \\__,_|\\__,_|___/  \\____\\__,_| .__/|_| \\_/ \\__,_|_|  \\__,_|___(_)"));
  Serial.println(F("                                                        |_|                                 "));
  Serial.println(F("Pressione qualquer botao para iniciar!"));
}

void imprimirInicioDeJogo() {
  Serial.println(F("Jogo comecou! VALENDO!"));
}

void imprimirFimDeJogo(int pontuacao) {
  Serial.println(F("\n###################################"));
  Serial.println(F("#          FIM DE JOGO            #"));
  Serial.println(F("###################################"));
  Serial.print(F("# Pontuacao Final: "));
  Serial.print(pontuacao);
  Serial.println(F("             #"));
  Serial.println(F("###################################"));
  Serial.println(F("Pressione qualquer botao para reiniciar."));
}

void imprimirStatus(bool acertou, int pontuacao, byte vidas, int tempoReacao) {
  if (acertou) {
    Serial.print(F(">> ACERTOU! | Pontos: "));
  } else {
    Serial.print(F(">> ERROU!   | Pontos: "));
  }
  Serial.print(pontuacao);
  Serial.print(F(" | Vidas: "));
  Serial.print(vidas);
  Serial.print(F(" | Reacao: "));
  Serial.print(tempoReacao);
  Serial.println(F("ms"));
}

void limparConsole() {
  for (int i = 0; i < 50; i++) {
    Serial.println();
  }
}