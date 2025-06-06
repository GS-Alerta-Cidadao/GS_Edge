# 🛠️ Sistema de Monitoramento de Nível de Rios com Alertas Visuais e Sonoros

## 📌 Descrição do Problema

Monitorar os níveis dos rios é uma medida importante para evitar tragédias em áreas propensas a inundações. Um aumento repentino nos níveis de água pode causar transbordamentos, colocando em risco vidas humanas, animais, casas e infraestrutura. Os métodos de medição manual são lentos, imprecisos e não fornecem alertas em tempo real, dificultando que cidadãos e autoridades tomem medidas preventivas.

Com esse sistema de alerta, as pessoas terão tempo suficiente para tomar precauções importantes, como evacuar áreas de perigo de forma ordenada, proteger seus pertences, ajudar vizinhos e familiares mais vulneráveis. Além disso, o alerta precoce permite que as autoridades locais e as equipas de Defesa Civil mobilizem recursos, preparem abrigos, optimizem a resposta de emergência e contribuindo para a redução de perdas materiais e, o mais importante, para a preservação de vidas.

## ✅ Visão Geral da Solução

Este projeto implementa um **sistema automatizado de alerta para monitoramento do nível de rios**, utilizando um sensor ultrassônico, um display LCD I2C, LEDs indicativos e um buzzer para alertas sonoros. A solução tem como objetivo **alertar comunidades sobre o risco de trasbordamento de rios**, oferecendo:

- Medição contínua da distância entre a superfície da água do rio e o sensor;
- Cálculo do nível de elevação da água em relação à altura segura pré-definida;
- Exibição em tempo real dessas informações em um **display LCD 20x4**;
- Sinalização com **LEDs coloridos** para indicar níveis de atenção e emergência;
- Ativação de um **alarme sonoro** em situações críticas para permitir uma resposta rápida.


### 🖼️ Ilustração do Sistemas


## 🔧 Componentes Utilizados

- Arduino Uno
- Sensor Ultrassônico HC-SR04
- Display LCD 20x4 com I2C
- LEDs (Verde, Amarelo, Vermelho)
- Buzzer
- Resistores
- Jumpers e Protoboard

---

## ▶️ Simulação Online

### 💡 Wokwi

**🔗 Link do Projeto no Wokwi:**  
[https://wokwi.com/projects/432203878280288257](https://wokwi.com/projects/432203878280288257)  


### 🎬 Vídeo Demonstrativo

**▶️ Veja o sistema em funcionamento no YouTube:**  
[https://youtu.be/39GnUvq20JQ](https://youtu.be/39GnUvq20JQ)  

---

## 🧪 Como Simular no Wokwi

1. Acesse o link acima do projeto no Wokwi.
2. Pressione **"Start Simulation"**.
3. Observe os valores no LCD, os LEDs acendendo e o buzzer tocando conforme o nível da água muda (simulado pelo valor da distância do sensor).
4. Altere a variável de distância manualmente ou utilize o componente virtual para observar os diferentes comportamentos.

---

## 📊 Faixas de Alerta do Sistema

| Faixa              | Nível (%)       | Indicação         |
|--------------------|------------------|--------------------|
| **Seguro**         | < 50%            | LED Verde          |
| **Atenção**        | 50% - 70%        | LED Amarelo (piscando) |
| **Crítico**        | > 70%            | LED Vermelho + Buzzer |
| **Erro Sensor**    | Leitura inválida | Piscar LED Vermelho |

---

## 👥 Integrantes

- Laura Barreto - RM561965
- Matheus Freitas Vieira - RM566198
- Natália Camargo - RM565769

