

/*// Definição dos pinos do circuito
const int pinoMotor = 9;   // Gate do MOSFET
const int pinoTrig  = 12;  // Trig do Ultrassônico
const int pinoEcho  = 11;  // Echo do Ultrassônico

// NOVA CONFIGURAÇÃO GEOMÉTRICA: 46 cm de tubo + 3 cm de recuo do sensor
const float distanciaSensorAoFundo = 49.0; 
const float alturaMaximaTubo = 46.0;

// Configurações da Janela do Degrau (em milissegundos)
const unsigned long tempoInicioDegrau = 3000;  // Liga o motor em 4 segundos
const unsigned long tempoFimDegrau    = 5000; // Desliga o motor em 10 segundos
const int pwmDegrau = 200;                     // Seu ponto de operação do ensaio

unsigned long tempoInicial = 0;

void setup() {
  pinMode(pinoMotor, OUTPUT);
  pinMode(pinoTrig, OUTPUT);
  pinMode(pinoEcho, INPUT);
  
  analogWrite(pinoMotor, 0); // Garante o motor começará desligado
  
  // Taxa de amostragem ultra rápida em 2MHz para o SerialPlot
  Serial.begin(2000000); 
  tempoInicial = millis();
}

void loop() {
  unsigned long tempoAtual = millis() - tempoInicial;
  int pwmAtual = 0;

  // Lógica da janela temporal do degrau puro
  if (tempoAtual >= tempoInicioDegrau && tempoAtual < tempoFimDegrau) {
    pwmAtual = pwmDegrau;
  } else {
    pwmAtual = 0; 
  }

  // Aplica a potência ao motor
  analogWrite(pinoMotor, pwmAtual);

  // Leitura rápida do sensor ultrassônico
  float distanciaSensor = lerUltrassonicoRapido();
  
  // A altura real da bolinha a partir do fundo do tubo é:
  float alturaBolinha = distanciaSensorAoFundo - distanciaSensor;
  
  // Filtros de restrição física baseados nas novas dimensões
  if (alturaBolinha < 0) alturaBolinha = 0;
  if (alturaBolinha > alturaMaximaTubo) alturaBolinha = alturaMaximaTubo;

  // Envio formatado para o SerialPlot (Separado por espaço)
  // Canal 1: PWM atual | Canal 2: Altura real da bolinha em cm
  Serial.print(pwmAtual);
  Serial.print(" ");
  Serial.println(alturaBolinha);

  delay(30); // Mantém a taxa estável de ~33 Hz
}

float lerUltrassonicoRapido() {
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);
  
  // Timeout de 20ms (limita leituras realistas até ~3,4 metros, evitando ecos tardios)
  long duracaoPulso = pulseIn(pinoEcho, HIGH, 20000); 
  if (duracaoPulso == 0) return distanciaSensorAoFundo; 
  
  return (duracaoPulso * 0.0343) / 2.0;

  */
}/*// Definição dos pinos do circuito
const int pinoMotor = 9;   // Gate do MOSFET
const int pinoTrig  = 12;  // Trig do Ultrassônico
const int pinoEcho  = 11;  // Echo do Ultrassônico

const float alturaTotalTubo = 46.0; 

// ==========================================
// PARÂMETROS DO CONTROLADOR PROPORCIONAL (P)
// ==========================================
const float setpoint = 20.0;      // ALTURA ALVO (cm): Mude para o valor que deseja testar (ex: 15, 20, 25)
const float Kp = 12.0;            // GANHO PROPORCIONAL: Calculado via Ziegler-Nichols
const int pwmPontoOperacao = 180;  // Seu ponto de equilíbrio para o meio do tubo

void setup() {
  pinMode(pinoMotor, OUTPUT);
  pinMode(pinoTrig, OUTPUT);
  pinMode(pinoEcho, INPUT);
  
  // Inicialização na velocidade rápida do seu SerialPlot
  Serial.begin(2000000); 
}

void loop() {
  // 1. Lê a altura atual real da bolinha
  float distanciaSensor = lerUltrassonicoRapido();
  float alturaBolinha = alturaTotalTubo - distanciaSensor;
  
  // Filtros de restrição física para o sensor no mundo real
  if (alturaBolinha < 0) alturaBolinha = 0;
  if (alturaBolinha > alturaTotalTubo) alturaBolinha = alturaTotalTubo;

  // 2. Calcula o Erro instantâneo da malha
  float erro = setpoint - alturaBolinha;

  // 3. Calcula a ação proporcional de controle
  // O PWM parte de 180 (força de flutuação) e soma/subtrai dependendo do erro
  int saidaPWM = pwmPontoOperacao + (erro * Kp);

  // 4. Saturação de segurança (Garante limites de hardware do Arduino)
  if (saidaPWM > 255) saidaPWM = 255;
  if (saidaPWM < 0)   saidaPWM = 0;

  // 5. Atualiza a potência aplicada no MOSFET
  analogWrite(pinoMotor, saidaPWM);

  // 6. Envia os dados formatados para monitoramento no SerialPlot
  // Canal 1: Setpoint (Alvo estático) | Canal 2: Altura dinâmica da Bolinha
  Serial.print(setpoint);
  Serial.print(" ");
  Serial.println(alturaBolinha);

  delay(30); // Mantém os ~33 Hz de amostragem que usamos no ensaio bem-sucedido
}

float lerUltrassonicoRapido() {
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);
  
  // Timeout de 20ms limita a leitura para evitar leituras espúrias fora do tubo
  long duracaoPulso = pulseIn(pinoEcho, HIGH, 20000); 
  if (duracaoPulso == 0) return alturaTotalTubo; 
  
  return (duracaoPulso * 0.0343) / 2.0;
}
*/


/*const int pinoTrig = 12;
const int pinoEcho = 11;
const int pinoPWM = 9;
const float altura_tubo = 46.0; // Altura útil em cm

// --- PARÂMETROS DO SEU PONTO DE OPERAÇÃO ---
const int PWM_EQUILIBRIO = 185;  // PWM para manter a bolinha no meio
const int AMPLITUDE_DEGRAU = 20; // O degrau unitário aplicado (+20 de força)

void setup() {
  pinMode(pinoTrig, OUTPUT);
  pinMode(pinoEcho, INPUT);
  pinMode(pinoPWM, OUTPUT);
  
  // Voltando para 9600 baud para casar com a configuração da sua tela
  Serial.begin(9600); 
  
  // Garante o motor desligado no instante zero
  analogWrite(pinoPWM, 0);
}

void loop() {
  int valorPWM = 0;
  unsigned long tempoAtual = millis(); // Tempo desde que o Arduino ligou

  // 1. Janela de Estabilização (0s a 3s) -> Leva a bolinha para o meio
  if (tempoAtual > 0 && tempoAtual <= 3000) {
    valorPWM = PWM_EQUILIBRIO; 
  }
  // 2. Janela do Degrau Unitário (3s a 6s) -> Aplica a perturbação (+ Degrau)
  else if (tempoAtual > 3000 && tempoAtual <= 6000) {
    valorPWM = PWM_EQUILIBRIO + AMPLITUDE_DEGRAU; // Vai para 205
  }
  // 3. Retorno ao Equilíbrio (6s a 9s) -> Remove o degrau para ver a volta
  else if (tempoAtual > 6000 && tempoAtual <= 9000) {
    valorPWM = PWM_EQUILIBRIO; // Volta para 185
  }
  // 4. Trava Final de Segurança (Após 9s) -> Desliga e envia zeros para o gráfico
  else if (tempoAtual > 9000) {
    analogWrite(pinoPWM, 0);
    while(1) {
      // Envia apenas os zeros puros para manter o gráfico estável no fim
      Serial.println("0.0,0.0");
      delay(1000); 
    }
  }

  // Envia o sinal PWM para o MOSFET
  analogWrite(pinoPWM, valorPWM);

  // Leitura do Sensor Ultrassônico HC-SR04
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);

  long duracao = pulseIn(pinoEcho, HIGH, 30000);
  float distanciadoTOPO = (duracao * 0.0343) / 2.0;

  if(distanciadoTOPO == 0){
    distanciadoTOPO = altura_tubo;
  }

  // Conversão para a altura real em relação à base
  float altura_bolinha = altura_tubo - distanciadoTOPO;
  altura_bolinha = constrain(altura_bolinha, 0.0, altura_tubo);

  // --- FORMATAÇÃO COMPATÍVEL COM O SERIALPLOT (CSV) ---
  // Enviamos: Valor1,Valor2
  Serial.print(valorPWM / 4.5); // Canal 1: PWM escalonado (~41 a ~45)
  Serial.print(",");
  Serial.println(altura_bolinha); // Canal 2: Altura da Bolinha (0 a 46 cm)

  delay(50); // Amostragem constante a cada 50ms
}
*/



/*const int pino_pwm = 9; // Pino com suporte a PWM (como o D9 do Arduino Uno)
float pwm =100.0;
float pwm_valor1 = 120.0;
void setup() {
  pinMode(pino_pwm, OUTPUT); // Corrigido para usar a variável correta
  
  // Inicializa a comunicação serial a 2000000 bps para o Serial Plotter
  Serial.begin(2000000); 
}

void loop() {

  analogWrite(pino_pwm, 185);
  
  // Envia o valor para o Serial Plotter
  Serial.print(pwm);
  Serial.print(" ");
  Serial.print(pwm_valor1);
  Serial.println(" ");
  
  delay(3000); // Espera 5 segundos
  
  // Desliga o motor (0V no Gate)

  analogWrite(pino_pwm, 0);
  
  // Envia o valor para o Serial Plotter

  
  delay(3000); // Espera 5 segundos
}
*/


