const int pinosLED[] = {8, 9, 10, 11, 12};
const int pinosBotao[] = {3, 4, 5, 6, 7};
const int pinoBuzzer = 13;
const int numToupeiras = 5;

long tempoToupeiraAcesa = 1000;
int vidas = 3;
int pontuacao = 0;
bool jogoRodando = false;

void setup() {
  Serial.begin(9600);

  pinMode(pinoBuzzer, OUTPUT);

  for (int i = 0; i < numToupeiras; i++) {
    pinMode(pinosLED[i], OUTPUT);
    pinMode(pinosBotao[i], INPUT);
    digitalWrite(pinosLED[i], LOW);
  }

  randomSeed(analogRead(A0));
  
  Serial.println("--- Jogo 'Bata na Toupeira' ---");
  Serial.println("Pressione qualquer botao para iniciar!");
}

void loop() {
  if (!jogoRodando) {
    if (algumBotaoPressionado()) {
      jogoRodando = true;
      Serial.println("Jogo comecou! VALENDO!");
      delay(500);
    }
    return;
  }

  if (vidas <= 0) {
    Serial.println("\n--- FIM DE JOGO ---");
    Serial.print("Pontuacao Final: ");
    Serial.println(pontuacao);
    Serial.println("Pressione qualquer botao para reiniciar.");

    while (!algumBotaoPressionado()) {
      piscarTodosLEDs();
    }
    
    vidas = 3;
    pontuacao = 0;
    jogoRodando = false;
    Serial.println("\n\n--- Novo Jogo ---");
    Serial.println("Pressione qualquer botao para iniciar!");
    apagarTodosLEDs();
    delay(1000);
    return;
  }

  int toupeiraSorteada = random(0, numToupeiras);

  digitalWrite(pinosLED[toupeiraSorteada], HIGH);
  long tempoInicio = millis();
  
  bool acertou = false;
  
  while (millis() - tempoInicio < tempoToupeiraAcesa) {
    if (digitalRead(pinosBotao[toupeiraSorteada]) == HIGH) {
      acertou = true;
      break;
    }
  }
  
  digitalWrite(pinosLED[toupeiraSorteada], LOW);

  if (acertou) {
    pontuacao++;
    Serial.print("ACERTOU! ");
    Serial.print("Pontos: ");
    Serial.println(pontuacao);
    
    tone(pinoBuzzer, 2000, 10);
    
  } else {
    vidas--;
    Serial.print("ERROU! ");
    Serial.print("Vidas restantes: ");
    Serial.println(vidas);
  }

  delay(random(500, 1501));
}

bool algumBotaoPressionado() {
  for (int i = 0; i < numToupeiras; i++) {
    if (digitalRead(pinosBotao[i]) == HIGH) {
      return true;
    }
  }
  return false;
}

void piscarTodosLEDs() {
  for (int i = 0; i < numToupeiras; i++) {
    digitalWrite(pinosLED[i], HIGH);
  }
  delay(250);
  for (int i = 0; i < numToupeiras; i++) {
    digitalWrite(pinosLED[i], LOW);
  }
  delay(250);
}

void apagarTodosLEDs() {
    for (int i = 0; i < numToupeiras; i++) {
    digitalWrite(pinosLED[i], LOW);
  }
}