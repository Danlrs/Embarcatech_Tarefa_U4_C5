# Projeto: Temporizadores com Raspberry Pi Pico

Este repositório contém dois projetos distintos que demonstram o uso de temporizadores no **Raspberry Pi Pico**, podendo ser executados tanto no **Wokwi** quanto na **placa BitDogLab**.

Cada atividade está localizada em uma pasta separada e deve ser executada individualmente, com apenas a respectiva pasta aberta no ambiente de desenvolvimento.

---

## 1️⃣ Temporizador Periódico (`temporizador_periodico`)

### 📌 Descrição
Este programa utiliza um **temporizador periódico** para alternar o estado de três LEDs a cada **3 segundos**, simulando o funcionamento de um semáforo:
- LED **Vermelho** aceso
- LED **Amarelo** aceso (Vermelho + Verde)
- LED **Verde** aceso

A cada ciclo de 3 segundos, o próximo LED é ativado e o anterior é apagado.

### ▶️ Como Executar
Pode ser executado tanto com o simulador Wokwi quanto com a BitDogLab.

---

## 2️⃣ Temporizador One-Shot (`temporizador_one_shot`)

### 📌 Descrição
Este programa utiliza um **temporizador one-shot** para acender e apagar LEDs em sequência quando um botão é pressionado:
- Ao pressionar o botão, **todos os LEDs acendem**.
- Após **3 segundos**, o LED **vermelho** se apaga.
- Após mais **3 segundos**, o LED **verde** se apaga.
- Após mais **3 segundos**, o LED **azul** se apaga e o sistema reinicia.

O botão é protegido contra **debounce**, garantindo que o sistema não reinicie acidentalmente antes de completar o ciclo.

### ▶️ Como Executar
Pode ser executado tanto com o simulador Wokwi quanto com a BitDogLab.

---

## 📢 Observações
- Certifique-se de abrir apenas a pasta do projeto que deseja compilar e executar.
- O código está comentado para facilitar a compreensão.

