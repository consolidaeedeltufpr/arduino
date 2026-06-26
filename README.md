# 🎈 Controle de Altura de Bolinha com Controlador PI

Este projeto implementa um **sistema de controle de altura** utilizando um **Arduino**, um **sensor ultrassônico**, um **motor DC** e um **controlador PI (Proporcional-Integral)** para manter uma bolinha de isopor suspensa ("flutuando") dentro de um tubo.

O sistema é um excelente exemplo de aplicação prática de **Controle Automático**, **Eletrônica de Potência** e **Sistemas Embarcados**.

---

## 📌 Funcionamento

O princípio de funcionamento é simples:

- Um **ventilador** instalado na parte inferior do tubo gera um fluxo de ar.
- Esse fluxo faz com que a **bolinha de isopor** suba ou desça.
- Um **sensor ultrassônico**, localizado no topo do tubo, mede continuamente a posição da bolinha.
- O Arduino compara essa posição com a altura desejada (**Setpoint**).
- Caso exista diferença entre a posição medida e a desejada (**erro**), o controlador PI calcula automaticamente uma nova velocidade para o ventilador.

O objetivo é manter a bolinha estável na altura selecionada.

---

## ⚙️ Como o Controle Funciona

O algoritmo utiliza um **Controlador PI (Proporcional-Integral)**.

### 🔹 Ação Proporcional (P)

A parte proporcional reage imediatamente ao erro atual.

- Quanto maior o erro;
- Maior será a correção aplicada;
- Faz a bolinha retornar rapidamente ao ponto desejado.

---

### 🔹 Ação Integral (I)

A parte integral acumula o erro ao longo do tempo.

Ela serve para eliminar pequenos desvios permanentes que a ação proporcional sozinha não consegue corrigir.

Isso permite que a bolinha permaneça exatamente na altura desejada.

---

## 🌬 Controle do Ventilador

A velocidade do ventilador é controlada através de **PWM (Pulse Width Modulation)**.

Em vez de variar diretamente a tensão aplicada ao motor, o Arduino liga e desliga o sinal milhares de vezes por segundo.

Alterando o tempo em que o sinal permanece ligado (Duty Cycle), obtém-se uma velocidade média diferente para o ventilador.

- PWM baixo → ventilador gira lentamente → bolinha desce
- PWM alto → ventilador gira rapidamente → bolinha sobe

---

## ⚡ Acionamento do Motor

O motor DC(15V) consome mais corrente do que o Arduino consegue fornecer diretamente.

Por isso é utilizado um **MOSFET**, que funciona como uma chave eletrônica.

O Arduino envia apenas o sinal PWM para o MOSFET, enquanto o MOSFET fornece a corrente necessária para alimentar o motor de forma eficiente e segura.

---

## 📏 Sensor Ultrassônico

A posição da bolinha é medida utilizando um sensor ultrassônico instalado no topo do tubo.

O sensor:

- emite um pulso ultrassônico;
- recebe o eco refletido pela bolinha;
- calcula a distância até ela.

Essa distância é utilizada como variável de realimentação do sistema de controle.

---

## 📊 Monitoramento

Durante a execução, o Arduino envia continuamente pela **porta serial**:

- posição atual da bolinha;
- altura desejada (Setpoint).

Esses dados podem ser visualizados pelo **Serial Plotter** da IDE do Arduino ou por qualquer software de aquisição serial, permitindo observar:

- estabilidade do sistema;
- resposta ao degrau;
- tempo de acomodação;
- oscilações;
- desempenho do controlador PI.

---

## 🛠 Componentes Utilizados

- Arduino
- Sensor Ultrassônico (HC-SR04)
- Motor DC
- Ventoinha
- MOSFET
- Fonte de alimentação
- Tubo vertical
- Bolinha de isopor

---

## 📈 Diagrama de Controle

```text
          Setpoint
              │
              ▼
      +----------------+
      | Comparador     |
      +----------------+
              │ Erro
              ▼
      +----------------+
      | Controlador PI |
      +----------------+
              │
              ▼
            PWM
              │
              ▼
          MOSFET
              │
              ▼
        Ventilador DC
              │
              ▼
      Fluxo de Ar
              │
              ▼
      Bolinha de Isopor
              │
              ▼
     Sensor Ultrassônico
              │
              └──────────────► Realimentação
```

---

## 🎯 Objetivo

Desenvolver um sistema de controle em malha fechada capaz de manter automaticamente uma bolinha de isopor em uma altura definida pelo usuário, utilizando técnicas clássicas de controle PI, leitura de sensores em tempo real e acionamento de motores via PWM.

---

## 📚 Conceitos Aplicados

- Controle em Malha Fechada
- Controlador PI
- PWM (Pulse Width Modulation)
- Sensores Ultrassônicos
- Sistemas Embarcados
- Controle Automático
- Eletrônica de Potência
- Aquisição de Dados
- Realimentação (Feedback)

---

## 🚀 Resultado Esperado

Após ajustar corretamente os ganhos do controlador PI, o sistema deve:

- ✔ Manter a bolinha estabilizada;
- ✔ Corrigir rapidamente perturbações;
- ✔ Minimizar oscilações;
- ✔ Eliminar erro em regime permanente;
- ✔ Fornecer resposta suave e estável.
