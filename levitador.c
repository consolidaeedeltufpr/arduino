// Definição dos pinos do circuito
const int pinoMotor = 9;   // Gate do MOSFET
const int pinoTrig  = 12;  // Trig do Ultrassônico
const int pinoEcho  = 11;  // Echo do Ultrassônico


const float distanciaSensorAoFundo = 49.0; 
const float alturaMaximaTubo = 46.0;

// PARÂMETROS DO CONTROLADOR PI 

const float setpoint = 40.0;       // Altura desejada em centímetros
const int pwmPontoOperacao = 180;   

// Ganhos Ziegler-Nichols através do ponto de 63.2% (17.27cm)
const float Kp = 8.35;   //10,37  bom        8,50 quase bom
const float Ki = 0.110;   //0,156  bom       0,110 ótimo

float somaIntegral = 0.0;

void setup() {
  pinMode(pinoMotor, OUTPUT);
  pinMode(pinoTrig, OUTPUT);
  pinMode(pinoEcho, INPUT);
  
  Serial.begin(2000000); 
}

void loop() {
  //Cálculo da altura 
  float distanciaSensor = lerUltrassonicoRapido();
  float alturaBolinha = distanciaSensorAoFundo - distanciaSensor;
  

  if (alturaBolinha < 0) alturaBolinha = 0;
  if (alturaBolinha > alturaMaximaTubo) alturaBolinha = alturaMaximaTubo;

  // erro da malha
  float erro = setpoint - alturaBolinha;

  //Acúmulo do erro para a ação Integral
  somaIntegral += erro;

  //Cálculo das componentes de controle P + I
  float acaoProporcional = erro * Kp;
  float acaoIntegral = somaIntegral * Ki;
  
  int saidaPWM = pwmPontoOperacao + acaoProporcional + acaoIntegral;

  //Estrutura Anti-Windup para proteção contra saturação do atuador
  if (saidaPWM > 255) {
    saidaPWM = 255;
    somaIntegral -= erro; // Trava o integrador se estourar o limite superior
  }
  if (saidaPWM < 0) {
    saidaPWM = 0;
    somaIntegral -= erro; // Trava o integrador se estourar o limite inferior
  }

  //Envia o sinal corrigido ao motor
  analogWrite(pinoMotor, saidaPWM);

  //Envia os dados para visualização no SerialPlot
  // Canal 1: Linha de Setpoint estável | Canal 2: Altura real da bolinha
  Serial.print(setpoint);
  Serial.print(" ");
  Serial.println(alturaBolinha);

  delay(30); // Amostragem idêntica à taxa do ensaio (~33Hz)
}

float lerUltrassonicoRapido() {
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);
  
  long duracaoPulso = pulseIn(pinoEcho, HIGH, 20000); 
  if (duracaoPulso == 0) return distanciaSensorAoFundo; 
  
  return (duracaoPulso * 0.0343) / 2.0;
}
