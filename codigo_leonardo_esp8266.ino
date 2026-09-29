#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// =====================================================
// Wi-Fi
// =====================================================

const char* WIFI_SSID  = "NOME_DO_WIFI";
const char* WIFI_SENHA = "SENHA_DO_WIFI";

// Servidor
const char* SERVIDOR = "http://192.168.1.100";

// =====================================================
// LDR + CD4051
// =====================================================

#define LDR A0

#define S0 D5
#define S1 D6
#define S2 D7

// =====================================================
// PCF8574
// =====================================================

#define PCF 0x20

// =====================================================
// Configurações
// =====================================================

int threshold = 500;

const int NUM_VAGAS = 8;

// =====================================================
// Seleciona qual LDR será lido
// =====================================================

void selecionarSensor(int sensor) {

  digitalWrite(S0, sensor & 1);
  digitalWrite(S1, sensor & 2);
  digitalWrite(S2, sensor & 4);
}

// =====================================================
// Envia os LEDs para o PCF8574
// =====================================================

void leds(byte valor) {

  Wire.beginTransmission(PCF);
  Wire.write(valor);
  Wire.endTransmission();
}

// =====================================================
// Envia estado da vaga para o servidor
// =====================================================

bool enviarEstado(int vaga, bool ocupada) {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi desconectado.");
    return false;
  }

  WiFiClient client;
  HTTPClient http;

  // Exemplo:
  // http://192.168.1.100/api/vagas/1

  String url = String(SERVIDOR) +
               "/api/vagas/" +
               String(vaga);

  http.begin(client, url);

  http.setTimeout(2000);

  // JSON enviado:
  // {"ocupada":1}
  // ou
  // {"ocupada":0}

  http.addHeader("Content-Type", "application/json");

  int estado;

  if (ocupada) {
    estado = 1;
  } else {
    estado = 0;
  }

  String json = "{\"ocupada\":" +
                String(estado) +
                "}";

  int codigo = http.POST(json);

  // Mostra no Monitor Serial
  Serial.print("V");
  Serial.print(vaga);
  Serial.print(" = ");
  Serial.print(estado);

  Serial.print(" | HTTP ");
  Serial.println(codigo);

  http.end();

  return codigo == 200;
}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // -----------------------------
  // I2C
  // -----------------------------

  Wire.begin(D2, D1);

  // -----------------------------
  // CD4051
  // -----------------------------

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  // Todos os LEDs desligados
  leds(255);

  // -----------------------------
  // Wi-Fi
  // -----------------------------

  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  Serial.print("Conectando ao Wi-Fi");

  unsigned long inicio = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - inicio < 15000) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Wi-Fi conectado!");

    Serial.print("IP do ESP8266: ");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println("Nao conectou ao Wi-Fi.");
  }
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  byte estadoLED = 255;

  // ===================================================
  // Lê os 8 sensores
  // ===================================================

  for (int sensor = 0; sensor < NUM_VAGAS; sensor++) {

    // Seleciona o LDR
    selecionarSensor(sensor);

    delay(5);

    // Lê o LDR
    int valor = analogRead(LDR);

    Serial.print("Sensor ");
    Serial.print(sensor + 1);
    Serial.print(": ");
    Serial.println(valor);

    // =================================================
    // Pouca luz = vaga ocupada
    // Muita luz = vaga vazia
    // =================================================

    bool ocupada = (valor < threshold);

    // =================================================
    // LED
    // =================================================

    if (ocupada) {

      // LED ligado
      estadoLED = estadoLED & ~(1 << sensor);

    } else {

      // LED desligado
      estadoLED = estadoLED | (1 << sensor);
    }

    // =================================================
    // POST
    // =================================================

    enviarEstado(sensor + 1, ocupada);
  }

  // Atualiza os 8 LEDs
  leds(estadoLED);

  delay(2000);
}