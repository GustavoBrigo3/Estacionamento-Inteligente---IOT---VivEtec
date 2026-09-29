# Estacionamento-Inteligente---IOT---VivEtec

# VagaJá

Sistema de estacionamento inteligente desenvolvido para o projeto **VivETEC**.

O objetivo do VagaJá é permitir o monitoramento das vagas de um estacionamento de forma simples, utilizando um **ESP8266** como parte do sistema de comunicação e uma interface web para visualizar a disponibilidade das vagas.

## Sobre o projeto

Nesta etapa do projeto, o sistema é preparado para monitorar **8 vagas**. O ESP8266 funciona como servidor local e cria sua própria rede Wi-Fi chamada:

```text
VagaJa
```

Ao conectar um celular ou computador nessa rede, é possível acessar o ESP8266 pelo endereço:


O VagaJá é um projeto de estacionamento inteligente desenvolvido por alunos da ETEC Vereador Valdivino Antônio Marcusso para a VivETEC.
A maquete terá oito vagas, de V1 a V8. Cada vaga terá um sensor para detectar a presença do carrinho e um LED vermelho, que ficará aceso quando estiver ocupada e apagado quando estiver livre.
O programa da placa será feito em C. Ela se conectará à internet e enviará os estados das vagas para um servidor também desenvolvido em C, hospedado em uma VPS.
O site utiliza HTML, CSS e JavaScript e mostrará as vagas livres, ocupadas e a quantidade disponível, com atualização automática. Os visitantes poderão acessá-lo pelo QR Code, usando a internet do celular.
Fluxo do sistema:
Sensores → placa → internet → servidor na VPS → site.
Atualmente, o site já possui oito vagas, tema claro e escuro, efeitos visuais e testes com um simulador em Python. Ainda falta substituir esse servidor pelo programa em C, publicar na VPS e testar tudo com a maquete real. Os cards do grupo já foram ajustados para esse novo planejamento.

```text
http://192.168.4.1
```

O microcontrolador disponibiliza duas rotas principais:

```text
/
```

Exibe uma página simples informando que o servidor está funcionando.

```text
/vagas
```

Retorna o estado das **8 vagas** em formato JSON.

Exemplo:

```json
{
  "V1": 0,
  "V2": 1,
  "V3": 0,
  "V4": 1,
  "V5": 0,
  "V6": 0,
  "V7": 1,
  "V8": 0,
  "disponiveis": 5
}
```

No padrão atual:

```text
0 = vaga livre
1 = vaga ocupada
```

> Nesta versão de teste, os estados das vagas ainda estão definidos diretamente no código do ESP8266.

## Tecnologias utilizadas

- ESP8266 / NodeMCU
- Arduino Framework (C++)
- Wi-Fi
- Servidor HTTP local
- HTML
- CSS
- JavaScript
- JSON

## Funcionamento

O funcionamento atual pode ser resumido assim:

```text
ESP8266 é ligado
        ↓
Cria a rede Wi-Fi "VagaJa"
        ↓
Inicia o servidor HTTP
        ↓
Usuário conecta o celular à rede
        ↓
Acessa http://192.168.4.1
        ↓
O navegador pode consultar /vagas
        ↓
O ESP8266 devolve os estados em JSON
```

O código utiliza o modo `WIFI_AP`, portanto o próprio ESP8266 cria o ponto de acesso Wi-Fi.

## Código do ESP8266

O servidor é criado utilizando:

```cpp
ESP8266WebServer servidor(80);
```

A rede Wi-Fi é iniciada com:

```cpp
WiFi.mode(WIFI_AP);
WiFi.softAPConfig(ip, gateway, subnet);
WiFi.softAP(ssid, senha);
```

O endereço configurado para o ESP8266 é:

```text
192.168.4.1
```

A rota principal é:

```cpp
servidor.on("/", HTTP_GET, []() {
    servidor.send(
        200,
        "text/html",
        "<h1>VagaJa</h1><p>Servidor funcionando!</p>"
    );
});
```

E a rota responsável por fornecer os dados das vagas é:

```cpp
servidor.on("/vagas", HTTP_GET, []() {
    String json = "{";
    json += "\"V1\":0,";
    json += "\"V2\":1,";
    json += "\"V3\":0,";
    json += "\"V4\":1,";
    json += "\"V5\":0,";
    json += "\"V6\":0,";
    json += "\"V7\":1,";
    json += "\"V8\":0,";
    json += "\"disponiveis\":5";
    json += "}";

    servidor.send(200, "application/json", json);
});
```

Durante a execução, o `loop()` mantém o servidor preparado para receber novas requisições:

```cpp
void loop() {
    servidor.handleClient();
}
```

## Interface web

O projeto também possui uma interface web desenvolvida em HTML, CSS e JavaScript.

A versão atual da interface já possui estrutura visual para **8 vagas**, organizadas de V1 até V8, além de contador de vagas disponíveis, indicação de conexão e atualização dos estados.

O JavaScript trabalha com o padrão:

```text
V1, V2, V3, V4, V5, V6, V7 e V8
```

e consulta a rota:

```text
/vagas
```

## Como testar

1. Grave o código no ESP8266.
2. Alimente a placa pela USB ou por uma fonte adequada.
3. Aguarde o ESP8266 iniciar.
4. No celular ou computador, procure a rede Wi-Fi:

```text
VagaJa
```

5. Conecte utilizando a senha:

```text
vagaja2026
```

6. Abra o navegador e acesse:

```text
http://192.168.4.1
```

7. Para visualizar diretamente os dados das vagas, acesse:

```text
http://192.168.4.1/vagas
```

## Estrutura sugerida do projeto

```text
VagaJa/
├── firmware/
│   └── esp8266/
│       └── VagaJa.ino
│
├── site/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
└── README.md
```

## Status do projeto

Atualmente o projeto está estruturado para **8 vagas (V1 a V8)** e já possui:

- criação da rede Wi-Fi pelo ESP8266;
- endereço local `192.168.4.1`;
- servidor HTTP na porta 80;
- rota principal `/`;
- rota `/vagas`;
- resposta em JSON com V1 até V8;
- estrutura do site para exibir as oito vagas;
- contador de vagas disponíveis;
- interface preparada para as 8 vagas.

## Próximas etapas

As próximas etapas previstas para a integração completa são:

- integrar os sensores reais ao estado de cada uma das 8 vagas;
- atualizar os dados automaticamente;
- integrar o ESP8266 ao servidor/VPS do projeto;
- disponibilizar o site através de domínio público;
- adicionar tratamento para perda de conexão e dados desatualizados;
- finalizar a comunicação entre placa, servidor e interface web.

## Projeto acadêmico

Projeto desenvolvido para o **VivETEC**, relacionado ao curso de **Desenvolvimento de Sistemas** da **ETEC Vereador Valdivino Antônio Marcusso**.

---

**VagaJá — Estacionamento Inteligente**


# Códigos de cada parte

Abaixo estão os códigos utilizados em cada parte do projeto. Eles foram separados por função para facilitar a consulta e a organização no GitHub.

<details>
<summary><strong>ESP8266 — servidor local e rota /vagas</strong></summary>

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "VagaJa";
const char* senha = "vagaja2026";

IPAddress ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer servidor(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(ssid, senha);

  Serial.println();
  Serial.println("VagaJa iniciado!");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  servidor.on("/", HTTP_GET, []() {
    servidor.send(
      200,
      "text/html",
      "<h1>VagaJa</h1><p>Servidor funcionando!</p>"
    );
  });

  servidor.on("/vagas", HTTP_GET, []() {
    String json = "{";
    json += "\"V1\":0,";
    json += "\"V2\":1,";
    json += "\"V3\":0,";
    json += "\"V4\":1,";
    json += "\"V5\":0,";
    json += "\"V6\":0,";
    json += "\"V7\":1,";
    json += "\"V8\":0,";
    json += "\"disponiveis\":5";
    json += "}";

    servidor.send(200, "application/json", json);
  });

  servidor.begin();

  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  servidor.handleClient();
}
```

</details>

<details>
<summary><strong>HTML — index.html</strong></summary>

```html
<!DOCTYPE html>
<html lang="pt-BR">

<head>
    <meta charset="UTF-8">

    <meta
        name="viewport"
        content="width=device-width, initial-scale=1.0"
    >

    <title>VagaJá | VivETEC</title>

    <link rel="stylesheet" href="style.css?v=8">
    <script src="script.js?v=8" defer></script>
</head>

<body>

<header class="topo">

    <div class="marca">

        <div class="logo">
            VJ
        </div>

        <div>
            <span class="vivetec">
                VivETEC
            </span>

            <h1>
                VagaJá
            </h1>

            <p>
                Estacionamento Inteligente
            </p>
        </div>

    </div>


    <div class="acoes-topo"><button id="alternarTema" type="button" aria-pressed="false">Tema escuro</button><div
        id="statusConexao"
        class="status conectando" role="status"
    >

        <span class="indicador"></span>

        Conectando...

    </div>

</div></header>


<main>

    <section class="apresentacao">

        <div>

            <span class="tag">
                PROJETO VIVETEC
            </span>

            <h2>
                Encontre uma vaga
                <span>em tempo real.</span>
            </h2>

            <p>
                Acompanhe a disponibilidade das
                oito vagas do estacionamento
                diretamente pelo seu celular.
            </p>

        </div>


        <div class="contador">

            <span>
                Vagas disponíveis
            </span>

            <strong id="quantidadeLivre">
                --
            </strong>

            <small>
                de 8 vagas
            </small>

        </div>

    </section>


    <section class="controles" aria-label="Fonte dos dados">
        <label for="modo">Fonte dos dados</label>
        <select id="modo"><option value="demo">Demonstração</option><option value="real" selected>Servidor do Yuri</option></select>
        <a class="link-simulador" href="/simulador" target="_blank" rel="noopener">Abrir simulador ↗</a>
        <p id="avisoModo" role="status">Consultando o servidor. Nesta etapa, os estados são simulados.</p>
    </section>
    <section class="painel">

        <div class="titulo-painel">

            <div>
                <span class="mini-titulo">
                    MONITORAMENTO
                </span>

                <h3>
                    Situação do estacionamento
                </h3>
            </div>

            <p>
                Atualização automática
            </p>

        </div>


        <div class="estacionamento">
<div class="fileira-label">FILEIRA 1 <span>V1 — V4</span></div><div class="vagas">
<div class="vaga desconhecida" id="vaga-v1"><span class="numero">V1</span><span id="led-v1" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
<div class="vaga desconhecida" id="vaga-v2"><span class="numero">V2</span><span id="led-v2" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
<div class="vaga desconhecida" id="vaga-v3"><span class="numero">V3</span><span id="led-v3" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
<div class="vaga desconhecida" id="vaga-v4"><span class="numero">V4</span><span id="led-v4" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
</div>
<div class="corredor" aria-hidden="true"><span>→</span> CIRCULAÇÃO <span>→</span></div>
<div class="fileira-label">FILEIRA 2 <span>V5 — V8</span></div><div class="vagas">
<div class="vaga desconhecida" id="vaga-v5"><span class="numero">V5</span><span id="led-v5" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
<div class="vaga desconhecida" id="vaga-v6"><span class="numero">V6</span><span id="led-v6" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
<div class="vaga desconhecida" id="vaga-v7"><span class="numero">V7</span><span id="led-v7" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
<div class="vaga desconhecida" id="vaga-v8"><span class="numero">V8</span><span id="led-v8" class="led desconhecida" aria-hidden="true"></span><span class="icone" aria-hidden="true">—</span><svg class="carro" viewBox="0 0 64 110" aria-hidden="true"><rect x="9" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="13" width="7" height="22" rx="3" fill="#121820"/><rect x="9" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="48" y="76" width="7" height="22" rx="3" fill="#121820"/><rect x="14" y="3" width="36" height="104" rx="14" fill="currentColor"/><path d="M20 29 Q32 21 44 29 L42 44 H22Z" fill="#192936"/><rect x="22" y="48" width="20" height="29" rx="5" fill="#ffffff33"/><path d="M22 81 H42 L44 92 H20Z" fill="#192936"/><path d="M19 12 H25 M39 12 H45" stroke="#fff6ce" stroke-width="4"/><path d="M19 99 H25 M39 99 H45" stroke="#ff3535" stroke-width="3"/></svg><span class="estado">SEM DADOS</span></div>
</div>
</div>
        <div class="rodape-painel">

            <div class="legenda">

                <div>
                    <span class="circulo led-apagado"></span>
                    Livre · LED apagado
                </div>

                <div>
                    <span class="circulo vermelho"></span>
                    Ocupada · LED vermelho
                </div>

            </div>


            <div class="ultima">

                Última atualização:

                <strong id="ultimaAtualizacao">
                    aguardando...
                </strong>

            </div>

        </div>

    </section>


    <section class="info">

        <div class="info-card">

            <span class="info-numero">
                01
            </span>

            <div>
                <strong>
                    Sensor detecta
                </strong>

                <p>
                    O sensor identifica se existe
                    um veículo na vaga.
                </p>
            </div>

        </div>


        <div class="info-card">

            <span class="info-numero">
                02
            </span>

            <div>
                <strong>
                    ESP32 processa
                </strong>

                <p>
                    A placa recebe o estado de
                    cada uma das vagas.
                </p>
            </div>

        </div>


        <div class="info-card">

            <span class="info-numero">
                03
            </span>

            <div>
                <strong>
                    VagaJá atualiza
                </strong>

                <p>
                    A página mostra as vagas
                    livres e ocupadas.
                </p>
            </div>

        </div>

    </section>

</main>


<footer>

    <strong>
        VagaJá
    </strong>

    <span>
        Projeto VivETEC
    </span>

    <span>
        ETEC Vereador Valdivino Antônio Marcusso
    </span>

</footer>


<noscript>Ative o JavaScript para acompanhar as vagas.</noscript>

</body>
</html>
```

</details>

<details>
<summary><strong>JavaScript — script.js</strong></summary>

```javascript
// Quando o ESP32 servir o site, esta rota funciona sem mudar o front-end.
const API_URL = "/vagas";
const INTERVALO_ATUALIZACAO = 1000;
const TEMPO_LIMITE = 4000;
const TOTAL_VAGAS = 8;
const chaves = Array.from({ length: TOTAL_VAGAS }, (_, i) => "V" + (i + 1));
const dadosTeste = { V1: 0, V2: 1, V3: 0, V4: 1, V5: 0, V6: 0, V7: 1, V8: 0, disponiveis: 5 };
const quantidadeLivre = document.getElementById("quantidadeLivre");
const ultimaAtualizacao = document.getElementById("ultimaAtualizacao");
const statusConexao = document.getElementById("statusConexao");
const seletorModo = document.getElementById("modo");
const avisoModo = document.getElementById("avisoModo");
const botaoTema = document.getElementById("alternarTema");
let temporizador;
let requisicao;
let versaoModo = 0;

// O navegador lembra o tema. Se o armazenamento estiver bloqueado, ainda funciona.
function aplicarTema(escuro) {
    document.documentElement.dataset.tema = escuro ? "escuro" : "claro";
    botaoTema.textContent = escuro ? "☀ Tema claro" : "☾ Tema escuro";
    botaoTema.setAttribute("aria-pressed", String(escuro));
}
let temaSalvo;
try { temaSalvo = localStorage.getItem("vagaja-tema"); } catch { }
aplicarTema(temaSalvo ? temaSalvo === "escuro" : matchMedia("(prefers-color-scheme: dark)").matches);
botaoTema.addEventListener("click", () => {
    const escuro = document.documentElement.dataset.tema !== "escuro";
    aplicarTema(escuro);
    try { localStorage.setItem("vagaja-tema", escuro ? "escuro" : "claro"); } catch { }
});

function definirStatus(classe, texto) {
    statusConexao.className = "status " + classe;
    statusConexao.replaceChildren();
    const indicador = document.createElement("span");
    indicador.className = "indicador";
    indicador.setAttribute("aria-hidden", "true");
    statusConexao.append(indicador, document.createTextNode(texto));
}

// Somente 0 e 1 numéricos são aceitos, conforme o contrato com o ESP32.
function validarDados(dados) {
    if (!dados || !chaves.every(chave => dados[chave] === 0 || dados[chave] === 1)) {
        throw new Error("A API precisa enviar V1 a V8 com valores 0 ou 1");
    }
    const livres = chaves.filter(chave => dados[chave] === 0).length;
    if (dados.disponiveis !== livres) {
        throw new Error("Contagem de vagas inconsistente");
    }
    return livres;
}

function atualizarVaga(numero, estado) {
    const vaga = document.getElementById("vaga-v" + numero);
    const led = document.getElementById("led-v" + numero);
    const classe = estado === 0 ? "livre" : estado === 1 ? "ocupada" : "desconhecida";
    const texto = estado === 0 ? "LIVRE" : estado === 1 ? "OCUPADA" : "SEM DADOS";
    const mudou = vaga.dataset.estado !== String(estado);
    vaga.dataset.estado = String(estado);
    vaga.className = "vaga " + classe;
    // Só anima quando o estado muda, não a cada consulta.
    if (mudou && !matchMedia("(prefers-reduced-motion: reduce)").matches) {
        vaga.getAnimations().forEach(animacao => animacao.cancel());
        vaga.animate([{ opacity: 0.5, transform: "translateY(5px)" },
                      { opacity: 1, transform: "translateY(0)" }], { duration: 450 });
    }
    led.className = "led " + classe;
    vaga.querySelector(".estado").textContent = texto;
    vaga.querySelector(".icone").textContent = estado === 1 ? "×" : estado === 0 ? "P" : "—";
    vaga.setAttribute("aria-label", "Vaga " + numero + ": " + texto +
        (seletorModo.value === "demo" ? ". Alternar estado simulado" : ""));
}

function atualizarInterface(dados) {
    quantidadeLivre.textContent = validarDados(dados);
    chaves.forEach((chave, indice) => atualizarVaga(indice + 1, dados[chave]));
    ultimaAtualizacao.textContent = new Date().toLocaleTimeString("pt-BR");
}

function limparVagas() {
    chaves.forEach((_, indice) => atualizarVaga(indice + 1, null));
    quantidadeLivre.textContent = "—";
    ultimaAtualizacao.textContent = "aguardando dados";
}

// A próxima consulta só começa quando a anterior termina: evita sobreposição.
async function buscarDados(versao) {
    const controle = new AbortController();
    requisicao = controle;
    const limite = setTimeout(() => controle.abort(), TEMPO_LIMITE);
    try {
        const resposta = await fetch(API_URL, { cache: "no-store", signal: controle.signal });
        if (!resposta.ok) throw new Error("HTTP " + resposta.status);
        const dados = await resposta.json();
        if (versao !== versaoModo) return;
        atualizarInterface(dados);
        definirStatus("conectado", "Conectado");
        avisoModo.textContent = "Conectado ao servidor do Yuri • teste com estados simulados.";
    } catch (erro) {
        if (versao !== versaoModo) return;
        limparVagas();
        definirStatus("desconectado", "Sem conexão");
        avisoModo.textContent = "Não foi possível consultar as oito vagas. Confira se o servidor está atualizado para V1 a V8. Tentando novamente…";
    } finally {
        clearTimeout(limite);
        if (versao === versaoModo && seletorModo.value === "real") {
            temporizador = setTimeout(() => buscarDados(versao), INTERVALO_ATUALIZACAO);
        }
    }
}

function mudarModo() {
    versaoModo++;
    clearTimeout(temporizador);
    if (requisicao) requisicao.abort();
    limparVagas();
    const demonstracao = seletorModo.value === "demo";
    chaves.forEach((_, indice) => {
        const vaga = document.getElementById("vaga-v" + (indice + 1));
        if (demonstracao) {
            vaga.setAttribute("role", "button");
            vaga.tabIndex = 0;
        } else {
            vaga.removeAttribute("role");
            vaga.removeAttribute("tabindex");
        }
    });
    if (demonstracao) {
        atualizarInterface(dadosTeste);
        definirStatus("demonstracao", "Demonstração");
        avisoModo.textContent = "Dados simulados. Clique em uma vaga para alternar seu estado.";
    } else {
        definirStatus("conectando", "Conectando…");
        avisoModo.textContent = "Buscando dados do servidor…";
        buscarDados(versaoModo);
    }
}

chaves.forEach((chave, indice) => {
    const vaga = document.getElementById("vaga-v" + (indice + 1));
    function alternar() {
        if (seletorModo.value !== "demo") return;
        dadosTeste[chave] = dadosTeste[chave] === 0 ? 1 : 0;
        dadosTeste.disponiveis = chaves.filter(item => dadosTeste[item] === 0).length;
        atualizarInterface(dadosTeste);
    }
    vaga.addEventListener("click", alternar);
    vaga.addEventListener("keydown", evento => {
        if (evento.key === "Enter" || evento.key === " ") {
            evento.preventDefault();
            alternar();
        }
    });
});
seletorModo.addEventListener("change", mudarModo);
if (location.protocol === "file:") seletorModo.value = "demo";
mudarModo();

```

</details>

<details>
<summary><strong>CSS — style.css</strong></summary>

```css
:root {

    --vermelho: #b5121b;
    --vermelho-escuro: #850d14;
    --vermelho-claro: #e11d2e;

    --branco: #ffffff;
    --cinza: #f4f4f5;
    --cinza-2: #e5e7eb;
    --texto: #252525;
    --texto-claro: #727272;

    --verde: #16a34a;
    --verde-claro: #dcfce7;

    --vermelho-status: #dc2626;
    --vermelho-status-claro: #fee2e2;
}



* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}


body {

    font-family:
        Arial,
        Helvetica,
        sans-serif;

    background: var(--cinza);

    color: var(--texto);

    min-height: 100vh;
}




.topo {

    background: var(--branco);

    border-bottom:
        4px solid var(--vermelho);

    padding:
        18px 7%;

    display: flex;

    justify-content:
        space-between;

    align-items: center;

    gap: 20px;

    box-shadow:
        0 3px 15px
        rgba(0, 0, 0, .06);
}


.marca {

    display: flex;
    align-items: center;
    gap: 14px;
}


.logo {

    width: 54px;
    height: 54px;

    border-radius: 14px;

    display: flex;

    align-items: center;
    justify-content: center;

    background:
        linear-gradient(
            135deg,
            var(--vermelho),
            var(--vermelho-claro)
        );

    color: white;

    font-weight: bold;

    font-size: 21px;

    box-shadow:
        0 8px 20px
        rgba(181, 18, 27, .25);
}


.vivetec {

    font-size: 11px;

    font-weight: bold;

    letter-spacing: 2px;

    color: var(--vermelho);
}


.marca h1 {

    font-size: 25px;

    line-height: 1;
}


.marca p {

    margin-top: 4px;

    font-size: 13px;

    color: var(--texto-claro);
}




.status {

    display: flex;

    align-items: center;

    gap: 8px;

    padding:
        9px 14px;

    border-radius: 100px;

    font-size: 13px;

    font-weight: bold;
}


.indicador {

    width: 9px;
    height: 9px;

    border-radius: 50%;
}


.conectando {

    background: #fff7ed;

    color: #c2410c;
}


.conectando .indicador {

    background: #f97316;
}


.conectado {

    background: var(--verde-claro);

    color: var(--verde);
}


.conectado .indicador {

    background: var(--verde);

    box-shadow:
        0 0 8px
        rgba(22, 163, 74, .6);
}


.desconectado {

    background:
        var(--vermelho-status-claro);

    color:
        var(--vermelho-status);
}


.desconectado .indicador {

    background:
        var(--vermelho-status);
}



main {

    width: 90%;

    max-width: 1150px;

    margin: auto;

    padding:
        45px 0;
}



.apresentacao {

    display: flex;

    justify-content:
        space-between;

    align-items: center;

    gap: 30px;

    margin-bottom: 35px;
}


.tag {

    display: inline-block;

    padding:
        7px 11px;

    border-radius: 7px;

    background:
        #fbeaec;

    color:
        var(--vermelho);

    font-size: 11px;

    font-weight: bold;

    letter-spacing: 1px;

    margin-bottom: 15px;
}


.apresentacao h2 {

    font-size:
        clamp(
            31px,
            5vw,
            47px
        );

    line-height: 1.05;

    max-width: 600px;
}


.apresentacao h2 span {

    color: var(--vermelho);
}


.apresentacao p {

    margin-top: 15px;

    color:
        var(--texto-claro);

    max-width: 520px;

    line-height: 1.6;
}



.contador {

    min-width: 200px;

    background:
        linear-gradient(
            145deg,
            var(--vermelho),
            var(--vermelho-escuro)
        );

    color: white;

    border-radius: 20px;

    padding:
        25px 30px;

    text-align: center;

    box-shadow:
        0 15px 35px
        rgba(181, 18, 27, .25);
}


.contador span {

    font-size: 13px;

    opacity: .9;
}


.contador strong {

    display: block;

    font-size: 55px;

    margin:
        6px 0;
}


.contador small {

    opacity: .8;
}



.painel {

    background:
        var(--branco);

    border-radius: 22px;

    overflow: hidden;

    box-shadow:
        0 15px 45px
        rgba(0, 0, 0, .08);
}


.titulo-painel {

    padding:
        25px 30px;

    display: flex;

    justify-content:
        space-between;

    align-items: center;

    gap: 15px;

    border-bottom:
        1px solid
        var(--cinza-2);
}


.mini-titulo {

    font-size: 10px;

    color:
        var(--vermelho);

    font-weight: bold;

    letter-spacing: 1.5px;
}


.titulo-painel h3 {

    margin-top: 5px;

    font-size: 21px;
}


.titulo-painel p {

    color:
        var(--texto-claro);

    font-size: 13px;
}



.estacionamento {

    margin:
        25px 30px;

    border-radius: 15px;

    overflow: hidden;

    background: #383838;

    border:
        8px solid #282828;

    box-shadow:
        inset 0 0 25px
        rgba(0, 0, 0, .3);
}



.fundo-estacionamento {

    display: grid;

    grid-template-columns:
        repeat(4, 1fr);

    gap: 0;

    background:
        #252525;

    padding:
        18px 8px;

    border-bottom:
        4px solid #181818;
}


.sensor {

    display: flex;

    flex-direction: column;

    align-items: center;

    gap: 7px;

    color:
        #c7c7c7;
}


.sensor small {

    font-size: 10px;
}


.led {

    width: 14px;
    height: 14px;

    border-radius: 50%;

    transition:
        .25s;
}


.led.livre {

    background:
        #3ee16f;

    box-shadow:
        0 0 12px
        #3ee16f;
}


.led.ocupada {

    background:
        #ff3b3b;

    box-shadow:
        0 0 12px
        #ff3b3b;
}



.vagas {

    display: grid;

    grid-template-columns:
        repeat(4, 1fr);

    min-height: 340px;

    background:
        linear-gradient(
            #454545,
            #373737
        );
}


.vaga {

    position: relative;

    display: flex;

    flex-direction: column;

    justify-content: center;

    align-items: center;

    gap: 14px;

    transition:
        .3s;
}


.vaga:not(:last-child) {

    border-right:
        5px solid #f6c500;
}


.numero {

    position: absolute;

    top: 15px;
    left: 15px;

    font-size: 15px;

    font-weight: bold;

    color:
        rgba(255,255,255,.7);
}


.icone {

    width: 62px;
    height: 62px;

    border-radius: 15px;

    display: flex;

    align-items: center;
    justify-content: center;

    font-size: 35px;

    font-weight: bold;

    border:
        3px solid
        rgba(255,255,255,.85);

    color: white;
}


.estado {

    padding:
        7px 14px;

    border-radius:
        100px;

    font-size: 11px;

    font-weight: bold;

    letter-spacing: .5px;
}



.vaga.livre {

    background:
        linear-gradient(
            rgba(22,163,74,.10),
            rgba(22,163,74,.02)
        );
}


.vaga.livre .estado {

    color:
        #4ade80;

    background:
        rgba(22,163,74,.15);

    border:
        1px solid
        #4ade80;
}



.vaga.ocupada {

    background:
        linear-gradient(
            rgba(220,38,38,.20),
            rgba(220,38,38,.04)
        );
}


.vaga.ocupada .estado {

    color:
        #ff7171;

    background:
        rgba(220,38,38,.15);

    border:
        1px solid
        #ff7171;
}



.rodape-painel {

    padding:
        0 30px 25px;

    display: flex;

    align-items: center;

    justify-content:
        space-between;

    gap: 20px;
}


.legenda {

    display: flex;

    gap: 20px;
}


.legenda div {

    display: flex;

    align-items: center;

    gap: 7px;

    font-size: 13px;

    color:
        var(--texto-claro);
}


.circulo {

    width: 10px;
    height: 10px;

    border-radius: 50%;
}


.verde {

    background:
        var(--verde);
}


.vermelho {

    background:
        var(--vermelho-status);
}


.ultima {

    font-size: 12px;

    color:
        var(--texto-claro);
}


.info {

    display: grid;

    grid-template-columns:
        repeat(3, 1fr);

    gap: 18px;

    margin-top: 28px;
}


.info-card {

    background:
        white;

    padding:
        22px;

    border-radius:
        15px;

    display: flex;

    align-items:
        flex-start;

    gap: 15px;

    box-shadow:
        0 8px 25px
        rgba(0,0,0,.05);
}


.info-numero {

    color:
        var(--vermelho);

    font-size: 24px;

    font-weight: bold;
}


.info-card strong {

    display: block;

    margin-bottom: 6px;
}


.info-card p {

    color:
        var(--texto-claro);

    font-size: 13px;

    line-height: 1.45;
}



footer {

    background:
        #1f1f1f;

    color:
        #b9b9b9;

    padding:
        25px 7%;

    display: flex;

    gap: 15px;

    justify-content:
        center;

    flex-wrap: wrap;

    font-size: 12px;
}


footer strong {

    color:
        white;
}



@media(max-width: 750px) {

    .topo {

        align-items:
            flex-start;
    }


    .apresentacao {

        flex-direction:
            column;

        align-items:
            stretch;
    }


    .contador {

        width: 100%;
    }


    .titulo-painel {

        align-items:
            flex-start;

        flex-direction:
            column;
    }


    .estacionamento {

        margin:
            18px 12px;
    }


    .vagas {

        min-height:
            240px;
    }


    .icone {

        width: 45px;
        height: 45px;

        font-size: 26px;
    }


    .vaga:not(:last-child) {

        border-right:
            3px solid
            #f6c500;
    }


    .numero {

        top: 8px;
        left: 8px;

        font-size: 11px;
    }


    .estado {

        padding:
            5px 7px;

        font-size: 8px;
    }


    .rodape-painel {

        align-items:
            flex-start;

        flex-direction:
            column;
    }


    .info {

        grid-template-columns:
            1fr;
    }

}/* Tema: as cores ficam centralizadas para facilitar alterações. */
:root {
    color-scheme: light;
    --pagina: #f4f3f1;
    --superficie: #ffffff;
    --borda: #e3e1df;
    --texto: #23252b;
    --texto-claro: #626671;
    --destaque: #b5121b;
}
:root[data-tema="escuro"] {
    color-scheme: dark;
    --pagina: #111317;
    --superficie: #1b1e24;
    --borda: #323640;
    --texto: #f4f4f6;
    --texto-claro: #b1b6c2;
    --destaque: #ff737b;
}
body { background: var(--pagina); color: var(--texto); font-family: "Segoe UI", Arial, sans-serif; }
.topo { background: var(--superficie); border-bottom: 1px solid var(--borda); padding: 20px max(5%, calc((100% - 1150px)/2)); }
.marca h1 { letter-spacing: -1px; }
.logo { border-radius: 16px 16px 16px 4px; }
.vivetec, .mini-titulo, .info-numero, .apresentacao h2 span { color: var(--destaque); }
.acoes-topo { display: flex; align-items: center; gap: 12px; flex-wrap: wrap; }
button, select { font: inherit; color: var(--texto); background: var(--superficie); border: 1px solid var(--borda); border-radius: 10px; padding: 11px 14px; cursor: pointer; }
button:hover, select:hover { border-color: var(--destaque); }
:focus-visible { outline: 3px solid var(--destaque); outline-offset: 4px; }
main { padding-top: 48px; }
.apresentacao { margin-bottom: 32px; }
.apresentacao h2 { font-weight: 750; letter-spacing: -2px; line-height: 1.13; }
.apresentacao h2 span { display: block; }
.tag { background: var(--superficie); border: 1px solid var(--borda); color: var(--destaque); border-radius: 100px; }
.contador { min-width: 225px; text-align: left; border-radius: 22px; background: linear-gradient(125deg,#c51b28,#850d20); position: relative; overflow: hidden; }
.contador::after { content: "P"; position: absolute; right: -10px; bottom: -35px; font-size: 180px; font-weight: 800; opacity: .08; }
.contador strong { font-size: 68px; line-height: 1.2; }
.controles { display: flex; align-items: center; gap: 12px; margin-bottom: 18px; flex-wrap: wrap; }
.controles label { font-size: 12px; font-weight: 700; }
.controles p { flex: 1; min-width: 200px; font-size: 13px; color: var(--texto-claro); line-height: 1.5; }
.painel, .info-card { background: var(--superficie); border: 1px solid var(--borda); box-shadow: 0 12px 35px #00000008; }
.titulo-painel { border-color: var(--borda); }
.estacionamento { border: 1px solid #373d47; border-radius: 16px; background: #22272e; }
.fundo-estacionamento { background: #20252c; border-bottom: 1px solid #414852; padding: 18px 0; }
.vagas { min-height: 250px; background: #292f37; padding: 0 12px; }
.vaga { margin: 18px 0; gap: 18px; }
.vaga:not(:last-child) { border-right: 2px solid #d3d6da; }
.numero { top: 0; left: 14px; font-size: 16px; color: #fff; }
.icone { border: 2px solid #89919d; color: #d3d8e0; opacity: .75; }
.vaga.livre .icone { color: #75eda1; border-color: #75eda1; }
.vaga.ocupada .icone { color: #ff9393; border-color: #ff9393; }
.vaga[role="button"] { cursor: pointer; }
.vaga[role="button"]:hover { box-shadow: inset 0 0 0 2px #ffffff55; }
.vaga.desconhecida .estado { background: #414854; color: #eef0f4; border: 1px solid #828c9c; }
.led.desconhecida { background: #89919d; box-shadow: none; }
.estacionamento::after { content: "ENTRADA  →"; display: block; padding: 16px 24px; border-top: 2px dashed #8a929e; color: #b9c0cb; font-size: 11px; letter-spacing: 3px; }
.info-card { box-shadow: none; border-radius: 16px; }
.info-numero { font-size: 14px; border: 1px solid var(--borda); padding: 9px; border-radius: 9px; }
.status { white-space: nowrap; }
.demonstracao, .conectando { background: #fff0d0; color: #7c4a00; }
.demonstracao .indicador { background: #b47813; }
.conectado { background: #d8f7e3; color: #126632; }
.desconectado { background: #ffe1e4; color: #a31326; }
footer { background: var(--superficie); color: var(--texto-claro); border-top: 1px solid var(--borda); }
footer strong { color: var(--texto); }
@media (max-width: 750px) {
    .topo { flex-wrap: wrap; padding: 18px 5%; }
    .acoes-topo { width: 100%; justify-content: space-between; }
    main { padding-top: 28px; }
    .apresentacao { gap: 22px; }
    .contador { min-width: 0; padding: 18px 24px; }
    .contador strong { display: inline-block; margin: 0 12px; font-size: 44px; }
    .apresentacao h2 { letter-spacing: -1px; }
    .titulo-painel { padding: 22px 18px; }
    .vagas { min-height: 210px; padding: 0 4px; }
    .vaga:not(:last-child) { border-right: 2px solid #d3d6da; }
    .estado { font-size: 9px; padding: 5px 4px; letter-spacing: 0; }
    .numero { left: 8px; }
    .rodape-painel { padding: 0 18px 20px; }
}
@media (prefers-reduced-motion: reduce) { * { transition: none !important; } }

.link-simulador { color: var(--destaque, #b5121b); font-size: 13px; font-weight: 600; padding: 10px 0; }

/* Oito vagas: duas fileiras de quatro, na ordem V1 até V8. */
body { background: radial-gradient(ellipse at 90% 0%, #c51b2812, transparent 55%), var(--pagina); }
.painel { box-shadow: 0 18px 60px #00000012; }
.apresentacao, .painel, .info { animation: aparecer .65s ease-out both; }
.painel { animation-delay: .1s; } .info { animation-delay: .2s; }
@keyframes aparecer { from { opacity: 0; transform: translateY(16px); } to { opacity: 1; transform: translateY(0); } }
.fileira-label { display: flex; justify-content: space-between; padding: 14px 20px; color: #c1ccd9; font-size: 11px; letter-spacing: 2px; background: #1b222b; }
.fileira-label span { color: #8595a9; }
.vagas { min-height: 205px; gap: 10px; padding: 14px; background: radial-gradient(ellipse at center, #3c4652, #242b34); }
.vaga, .vaga:not(:last-child) { margin: 0; border: 1px solid #ffffff22; border-radius: 12px; gap: 8px; min-height: 180px; padding: 30px 4px 12px; transition: background .4s, box-shadow .3s, border-color .3s; }
.vaga .numero { top: 10px; left: 12px; }
.vaga > .led { position: absolute; top: 12px; right: 12px; width: 10px; height: 10px; }
.vaga.livre { border-color: #4ade8055; box-shadow: inset 0 -18px 35px #16a34a0a; }
.vaga.ocupada { border-color: #ff717155; }
.vaga .icone { height: 83px; width: 52px; font-size: 32px; border-radius: 12px; }
.carro { display: none; width: 49px; height: 83px; color: #dbe3ef; filter: drop-shadow(0 6px 5px #0008); }
.vaga.ocupada .carro { display: block; }
.vaga.ocupada .icone { display: none; }
.vaga:nth-child(even) .carro { color: #9dbfe2; }
.corredor { display:flex; align-items:center; justify-content:space-around; padding:10px; color:#aebbc9; font-size:10px; letter-spacing:3px; border-block:1px dashed #758392; background:#1e252d; }
.corredor span { font-size:24px; }
.contador { box-shadow: 0 16px 40px #b5121b30; border: 1px solid #ff667744; }
.info-card, button, .link-simulador { transition: transform .2s, box-shadow .2s; }
@media (hover:hover) { .info-card:hover { transform:translateY(-4px); box-shadow:0 10px 25px #0001; } button:hover { transform:translateY(-2px); } .vaga[role="button"]:hover { box-shadow:inset 0 0 0 2px #ffffff55, 0 4px 16px #0003; } }
@media(max-width:750px) { .vagas { min-height:170px; gap:5px; padding:8px; } .vaga, .vaga:not(:last-child) { min-height:150px; border-width:1px; } .vaga .numero { left:7px; font-size:13px; } .vaga > .led { right:7px; width:8px; height:8px; } .carro, .vaga .icone { height:65px; width:40px; } .fileira-label { padding:12px; } }
@media(prefers-reduced-motion:reduce) { *, *::before, *::after { animation:none !important; transition:none !important; } }

/* Um LED vermelho por vaga: livre = apagado. */
.led.livre, .led-apagado { background: #434a54; border: 1px solid #8793a3; box-shadow: none; }
.led.ocupada { background: #ff3939; box-shadow: 0 0 7px #ff3939, 0 0 17px #ff393970; }
.led.desconhecida { background: transparent; border: 1px dashed #a6b0bc; box-shadow: none; }

```

</details>

## Organização dos arquivos

```text
VagaJa/
├── firmware/
│   └── esp8266/
│       └── VagaJa.ino
│
├── site/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
└── README.md
```

> Os blocos acima podem ser expandidos no GitHub clicando sobre o título de cada parte.


int ledVermelhoV1 = 13;
int ledVermelhoV2 = 12;
int ledVermelhoV3 = 11;
int ledVermelhoV4 = 10;
int ledVermelhoV5 = 9;
void setup() {
  pinMode(ledVermelhoV1, OUTPUT);
  pinMode(ledVermelhoV2, OUTPUT);
  pinMode(ledVermelhoV3, OUTPUT);
  pinMode(ledVermelhoV4, OUTPUT);
  pinMode(ledVermelhoV5, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int LDRV1 = analogRead(A0);
  Serial.println(LDRV1);
  int LDRV2 = analogRead(A1);
  Serial.println(LDRV2);
  int LDRV3 = analogRead(A2);
  Serial.println(LDRV3);
  int LDRV4 = analogRead(A3);
  Serial.println(LDRV4);
  int LDRV5 = analogRead(A4);
  Serial.println(LDRV5);

  if (LDRV1 > 500) {
    digitalWrite(ledVermelhoV1, HIGH);
  } 
  else {
    digitalWrite(ledVermelhoV1, LOW);
  }
  if (LDRV2 > 500) {
    digitalWrite(ledVermelhoV2, HIGH);
  } 
  else {
    digitalWrite(ledVermelhoV2, LOW);
  }
  if (LDRV3 > 500) {
    digitalWrite(ledVermelhoV3, HIGH);
  } 
  else {
    digitalWrite(ledVermelhoV3, LOW);
  }
  if (LDRV4 > 500) {
    digitalWrite(ledVermelhoV4, HIGH);
  } 
  else {
    digitalWrite(ledVermelhoV4, LOW);
  }
  if (LDRV5 > 500) {
    digitalWrite(ledVermelhoV5, HIGH);
  } 
  else {
    digitalWrite(ledVermelhoV5, LOW);
  }
  delay(200);
}
