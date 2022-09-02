String inputString = "";
String nome = "nome";
bool stringComplete = false;
int randNumber;
int sorteado[7];
int digitados[7];
int cont1, cont2, cont3, acertos = 0;
int jogar, reiniciar = 1;
int pontuacao = 1000;
#define buzer 2

void setup() {
  pinMode(buzer, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  inputString.reserve(200);
  randomSeed(analogRead(0));
  gerarNumero();
}

void loop() {
  if (stringComplete) {
      if(inputString == "SIM\n"){
      Reiniciar();
      stringComplete = false;
      inputString = "";     
    //Compara Numero Digitado Com Sorteado
     } else if (jogar != -1) {
     if(sorteado[cont2]==digitados[cont2]){
       cont2++;
       acertos++;
       //Impede Novo Sorteio Até cont2 = cont1
       if(cont2 != cont1){
         jogar = 0;
       } else {
        Acertou();
       }
    } else {
      Errou();
    }
     }
  if (jogar == 1) {
      gerarNumero();
    } 
    inputString = "";
    stringComplete = false;
  }
   
}

void serialEvent() {
  while (Serial.available()) {
    //String nome = Serial.readString();
    char inChar = (char)Serial.read();
    inputString += inChar;
    digitados[cont3] = inputString.toInt();
    inputString.toUpperCase();
    if (inChar == '\n' && nome == "nome"){
      nome = inputString;
      Serial.print("Bem-Vindo, Jogador ");
      nome.trim(); //Remove whitespace (" ","\t","\v","\f","\r","\n") from String
      Serial.print(nome);
      Serial.print("!");
      inputString = "";
      delay(2000);
      gerarNumero();
    } else
    if (inChar == '\n' && nome != "nome") {
      stringComplete = true;
      cont3++;
    }
  }
}

void gerarNumero() {
  Ganhar();
  Intro();
  if(nome == "nome"){
    Espaco();
    Serial.println("Digite Seu Nome: ");
  } else
  //Sorteia Um Numero e Salva Na Array
  if(jogar != -1) {
    randNumber = random(0, 10);
    sorteado[cont1] = randNumber;
    cont1++;
    Espaco();
    Sorteados();
    Serial.println("");
    Serial.println("Memorize...");
    delay(1000);
    Serial.print("3, ");
    delay(1000);
    Serial.print("2, ");
    delay(1000);
    Serial.println("1!");
    delay(1000);
    Espaco();
    cont2 = 0;
    Serial.println("Digite a Sequencia...");
    Serial.println("A Cada Número Digitado Pressione a Tecla 'Enter'");
  }
}

void Ganhar(){
  if(acertos == 28) { // 7 rodadas (1+2+3+4+5+6+7) -> 28
      Espaco();
      jogar = -1;
      tone(buzer,600, 50);
      Serial.println(":|");
      delay(200);
      tone(buzer,600, 50);
      delay(200);
      tone(buzer,600, 100);
      delay(200);
      tone(buzer,600, 50);
      delay(200);
      tone(buzer,600, 50);
      delay(200);
      tone(buzer,800, 100);
      delay(200);
      tone(buzer,800, 100);
      Espaco();
      Serial.println(":)");
      delay(200);
      tone(buzer,800, 50);
      delay(200);
      tone(buzer,800, 50);
      delay(200);
      tone(buzer,800, 100);
      delay(200);
      tone(buzer,600, 50);
      delay(200);
      tone(buzer,600, 50);
      Espaco();
      Serial.print("PARABÉNS ");
      Serial.print(nome);
      Serial.println(", VOCÊ GANHOU!!!");
      Serial.println(":D");
      delay(200);
      tone(buzer,800, 100);
      delay(200);
      tone(buzer,600, 50);
      delay(200);
      Serial.println("");
      Serial.println("Digite 'SIM', Para Jogar Novamente.");
  }
}

void Intro() {
  if(reiniciar == 1){
    reiniciar = 2;
    Serial.println("Jogo Começando:");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    tone(buzer,300, 100);
    delay(200);
    tone(buzer,600, 100);
    delay(200);
    tone(buzer,500, 100);
    delay(200);
    Serial.print("Loading");
    tone(buzer,400, 150);
    delay(300);
    Serial.print(".");
    tone(buzer,600, 100);
    delay(200);
    tone(buzer,500, 100);
    delay(200);
    Serial.print(".");
    tone(buzer,400, 150);
    delay(300);
    tone(buzer,400, 150);
    delay(300);
    tone(buzer,600, 100);
    delay(200);
    Serial.print(".");
    tone(buzer,500, 50);
    delay(200);
    Serial.print(".");
    tone(buzer,500, 100);
    delay(200);
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(50);
    Serial.print(".");
    delay(1000);
    Serial.print(". ");
    delay(1000);
    Serial.print("Complete!");
    delay(800);
  }
}

void Acertou() {
  Espaco();
  Serial.println("-> Você Acertou!!!");
  digitalWrite(4, HIGH);
  Sorteados();
  tone(buzer,700, 100);
  delay(200);
  jogar = 1;
  digitalWrite(4, LOW);
  Serial.println("");
  Digitou();
}

void Digitou(){
  Serial.print("Você Digitou: ");
  for(byte x = 0; x < cont3; x++) {
    Serial.print(digitados[x]);
    Serial.print("|");
  }
  cont3 = 0;
  delay(5000); 
  Espaco();    
}

void Errou() {
  Espaco();
  jogar = -1;
  tone(buzer,100, 100);
  digitalWrite(3, HIGH);
  Serial.println(":|");
  delay(300);
  tone(buzer,200, 100);
  digitalWrite(3, LOW);
  delay(300);
  Espaco();
  tone(buzer,100, 100);
  digitalWrite(3, HIGH);
  Serial.println(":/");
  delay(300);
  tone(buzer,300, 200);
  digitalWrite(3, LOW);
  delay(300);
  Espaco();
  Serial.println(":(");
  delay(600);
  Serial.println("");
  Serial.println("-> Você Errou!!!");
  Serial.print("Mais Sorte Na Próxima Vez, ");
  Serial.print(nome);
  Serial.print(".");
  Serial.println("");
  delay(800);
  Sorteados();
  Serial.println("");
  Digitou();
  Serial.println("Digite 'SIM', Para Jogar Novamente.");
}

void Sorteados(){
  Serial.print("Números Sorteados: ");
  for(byte x = 0; x < cont1; x++) {
    Serial.print(sorteado[x]);
    Serial.print("|");
  }
}

void Reiniciar(){
      Serial.println("");
      Serial.println("");
      jogar = 1;
      reiniciar = 1;
      cont1 = 0;
      cont2 = 0;
      cont3 = 0;
      acertos = 0;
      Serial.println("Reiniciando...");
      delay(2500);
      Espaco();
}

void Espaco(){
  for (byte x = 0; x < 20; x++) {
    Serial.println("");
  }
}
