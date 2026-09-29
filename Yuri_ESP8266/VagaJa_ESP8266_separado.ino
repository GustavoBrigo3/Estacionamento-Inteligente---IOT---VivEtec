#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "index_html.h"
#include "style_css.h"
#include "script_js.h"
#include "simulador_html.h"

const char* SSID = "VagaJa";
const char* SENHA = "vagaja2026";

IPAddress IP_LOCAL(192, 168, 4, 1);
IPAddress GATEWAY(192, 168, 4, 1);
IPAddress SUBNET(255, 255, 255, 0);

ESP8266WebServer servidor(80);

const uint8_t NUM_VAGAS = 8;

// 0 = livre | 1 = ocupada
uint8_t vagas[NUM_VAGAS] = {0, 0, 0, 0, 0, 0, 0, 0};

void semCache() {
  servidor.sendHeader("Cache-Control", "no-store, no-cache, must-revalidate");
  servidor.sendHeader("Pragma", "no-cache");
  servidor.sendHeader("Expires", "0");
}

void enviarVagas() {
  int disponiveis = 0;

  for (int i = 0; i < NUM_VAGAS; i++) {
    if (vagas[i] == 0) {
      disponiveis++;
    }
  }

  char json[180];
  snprintf(
    json,
    sizeof(json),
    "{\"V1\":%u,\"V2\":%u,\"V3\":%u,\"V4\":%u,"
    "\"V5\":%u,\"V6\":%u,\"V7\":%u,\"V8\":%u,"
    "\"disponiveis\":%d}",
    vagas[0], vagas[1], vagas[2], vagas[3],
    vagas[4], vagas[5], vagas[6], vagas[7],
    disponiveis
  );

  semCache();
  servidor.send(200, "application/json; charset=utf-8", json);
}

void atualizarVaga(uint8_t numero) {
  if (numero < 1 || numero > NUM_VAGAS) {
    servidor.send(400, "application/json", "{\"erro\":\"Vaga invalida\"}");
    return;
  }

  String corpo = servidor.arg("plain");
  corpo.replace(" ", "");
  corpo.replace("\r", "");
  corpo.replace("\n", "");

  int novoEstado = -1;

  // Compatível com true/false e com 1/0 usado no código atual do Leo.
  if (corpo.indexOf("\"ocupada\":true") >= 0 ||
      corpo.indexOf("\"ocupada\":1") >= 0) {
    novoEstado = 1;
  } else if (corpo.indexOf("\"ocupada\":false") >= 0 ||
             corpo.indexOf("\"ocupada\":0") >= 0) {
    novoEstado = 0;
  }

  if (novoEstado < 0) {
    servidor.send(
      400,
      "application/json",
      "{\"erro\":\"Envie ocupada como 0, 1, true ou false\"}"
    );
    return;
  }

  vagas[numero - 1] = novoEstado;

  Serial.print("V");
  Serial.print(numero);
  Serial.print(" -> ");
  Serial.println(novoEstado == 1 ? "OCUPADA" : "LIVRE");

  char resposta[72];
  snprintf(
    resposta,
    sizeof(resposta),
    "{\"status\":\"ok\",\"vaga\":\"V%u\",\"ocupada\":%u}",
    numero,
    novoEstado
  );

  servidor.send(200, "application/json; charset=utf-8", resposta);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(IP_LOCAL, GATEWAY, SUBNET);

  if (!WiFi.softAP(SSID, SENHA)) {
    Serial.println("Erro ao criar a rede Wi-Fi.");
    return;
  }

  servidor.on("/", HTTP_GET, []() {
    semCache();
    servidor.send_P(200, "text/html; charset=utf-8", VJHTML_DATA);
  });

  servidor.on("/style.css", HTTP_GET, []() {
    semCache();
    servidor.send_P(200, "text/css; charset=utf-8", VJCSS_DATA);
  });

  servidor.on("/script.js", HTTP_GET, []() {
    semCache();
    servidor.send_P(200, "application/javascript; charset=utf-8", VJJS_DATA);
  });

  servidor.on("/simulador", HTTP_GET, []() {
    semCache();
    servidor.send_P(200, "text/html; charset=utf-8", VJSIM_DATA);
  });

  servidor.on("/vagas", HTTP_GET, enviarVagas);

  servidor.on("/api/vagas/1", HTTP_POST, []() { atualizarVaga(1); });
  servidor.on("/api/vagas/2", HTTP_POST, []() { atualizarVaga(2); });
  servidor.on("/api/vagas/3", HTTP_POST, []() { atualizarVaga(3); });
  servidor.on("/api/vagas/4", HTTP_POST, []() { atualizarVaga(4); });
  servidor.on("/api/vagas/5", HTTP_POST, []() { atualizarVaga(5); });
  servidor.on("/api/vagas/6", HTTP_POST, []() { atualizarVaga(6); });
  servidor.on("/api/vagas/7", HTTP_POST, []() { atualizarVaga(7); });
  servidor.on("/api/vagas/8", HTTP_POST, []() { atualizarVaga(8); });

  servidor.onNotFound([]() {
    servidor.send(404, "text/plain; charset=utf-8", "404 - Nao encontrado");
  });

  servidor.begin();

  Serial.println();
  Serial.println("VagaJa iniciado!");
  Serial.print("Rede: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Servidor HTTP iniciado para 8 vagas.");
}

void loop() {
  servidor.handleClient();
}
