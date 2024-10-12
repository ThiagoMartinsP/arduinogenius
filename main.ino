struct Componentes {
  int led;
  int botao;
};

struct RGB {
  int red;
  int green;
  int blue;
};

Componentes amarelo = {4, 9};
Componentes vermelho = {3, 11};
Componentes azul = {5, 10};
Componentes verde = {2, 12};

RGB ledRGB = {6, 8, 7};

int leds[4] = {amarelo.led, vermelho.led, azul.led, verde.led};

int botoes[4] = {amarelo.botao, vermelho.botao, azul.botao, verde.botao};

///////////////////////////////////

int* sequenciaAleatoria() {
  int* sequencia = new int[84];
  for(int i = 0; i < 84; i++) {
    sequencia[i] = random(0, 4);
  }
  return sequencia;
}


int botaoPressionado() {
  if(digitalRead(amarelo.botao)) {
    return 0;
  }
  else if(digitalRead(azul.botao)) {
    return 2;
  }
  else if(digitalRead(vermelho.botao)) {
    return 1;
  }
  else if(digitalRead(verde.botao)) {
    return 3;
  }
  return -1; // se nenhum botão foi apertado, return -1;
}


void piscaLed(int entradaLed, int tempoAceso) {

  digitalWrite(entradaLed, HIGH);
  delay(tempoAceso);
  digitalWrite(entradaLed, LOW);
  delay(500);
}

void piscaTodosLeds(int tempoAceso) {
  for(int j = 0; j < 4; j++) {
      digitalWrite(leds[j], HIGH);
    }
    delay(tempoAceso);
    for(int k = 0; k < 4; k++) {
      digitalWrite(leds[k], LOW);
    }
    delay(500);
}

//////////////////////////////////////

void setup() {
  
  Serial.begin(9600);
  
  // declara as entradas dos componentes
  pinMode(vermelho.led, OUTPUT);
  pinMode(verde.led, OUTPUT);
  pinMode(amarelo.led, OUTPUT);
  pinMode(azul.led, OUTPUT);
  
  pinMode(vermelho.botao, INPUT);
  pinMode(verde.botao, INPUT);
  pinMode(amarelo.botao, INPUT);
  pinMode(azul.botao, INPUT);

  pinMode(ledRGB.red, OUTPUT);
  pinMode(ledRGB.green, OUTPUT);
  pinMode(ledRGB.blue, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() {

  //pisca todos os leds pra mostrar inicio de uma nova rodada
  for(int i = 0; i < 3; i++) {
    piscaTodosLeds(600);
  }
  
  int* sequenciaBase = sequenciaAleatoria();
  int numRodada = 0;
  int errou = false;

  // inicia jogo
  do{

    int botaoAtivado = -1;

    numRodada++; // numRodada = 1;

    //led rgb pisca amarelo, avisando inicio de uma sequencia
    for(int i = 0; i < 2; i++) {
      analogWrite(ledRGB.red, 170); 
  	  analogWrite(ledRGB.green, 130);
      delay(500);
      analogWrite(ledRGB.red, 0); 
  	  analogWrite(ledRGB.green, 0);
      delay(400);
    }

    // pisca sequencia
    for(int i = 0; i < numRodada; i++) {
      piscaLed(leds[sequenciaBase[i]], 700);
    }

    // tentativa jogador
    for(int i = 0; i < numRodada; i++) {

      // enquanto nenhum botão for apertado, não sairá do loop while
      while(1) {
        botaoAtivado = botaoPressionado();
        if(botaoAtivado != -1) {
          piscaLed(leds[botaoAtivado], 700);
          if(botaoAtivado != sequenciaBase[i]) {
            errou = true;
          }
          break;
        }
      }

      if(errou) {
        // rgb pisca vermelho
        analogWrite(ledRGB.red, 170);
        delay(1500);
        analogWrite(ledRGB.red, 0);
        break;
      }
    }
    if(!errou) {
      // pisca verde se acertou a sequencia
      analogWrite(ledRGB.green, 170);
      delay(600);
      analogWrite(ledRGB.green, 0);
    }
    
  delay(1000);
  } while(!errou);

  delete[] sequenciaBase;
}















