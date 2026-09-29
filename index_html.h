#pragma once
#include <Arduino.h>

const char VJHTML_DATA[] PROGMEM = R"VJHTML(
<!DOCTYPE html>
<html lang="pt-BR">

<head>
    <meta charset="UTF-8">

    <meta
        name="viewport"
        content="width=device-width, initial-scale=1.0"
    >

    <title>VagaJá | VivETEC</title>

    <link rel="stylesheet" href="style.css">
    <script src="script.js" defer></script>
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
                <span>no momento.</span>
            </h2>

            <p>
                Acompanhe a disponibilidade das
                quatro vagas do estacionamento
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
                de 4 vagas
            </small>

        </div>

    </section>


    <section class="controles" aria-label="Fonte dos dados">
        <label for="modo">Fonte dos dados</label>
        <select id="modo"><option value="demo">Demonstração</option><option value="real" selected>Placa real</option></select>
        <a class="link-simulador" href="/simulador" target="_blank" rel="noopener">Abrir simulador ↗</a>
        <p id="avisoModo" role="status">Consultando o ESP8266 para obter o estado atual das vagas.</p>
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
                Atualização ao abrir a página
            </p>

        </div>


        <div class="estacionamento">

            <div class="fundo-estacionamento">

                <div class="sensor">
                    <span id="led-v1" class="led desconhecida"></span>
                    <small>Sensor V1</small>
                </div>

                <div class="sensor">
                    <span id="led-v2" class="led desconhecida"></span>
                    <small>Sensor V2</small>
                </div>

                <div class="sensor">
                    <span id="led-v3" class="led desconhecida"></span>
                    <small>Sensor V3</small>
                </div>

                <div class="sensor">
                    <span id="led-v4" class="led desconhecida"></span>
                    <small>Sensor V4</small>
                </div>

            </div>


            <div class="vagas">

                <div
                    class="vaga desconhecida"
                    id="vaga-v1"
                >

                    <span class="numero">
                        V1
                    </span>

                    <span class="icone">
                        P
                    </span>

                    <span class="estado">
                        SEM DADOS
                    </span>

                </div>


                <div
                    class="vaga desconhecida"
                    id="vaga-v2"
                >

                    <span class="numero">
                        V2
                    </span>

                    <span class="icone">
                        P
                    </span>

                    <span class="estado">
                        SEM DADOS
                    </span>

                </div>


                <div
                    class="vaga desconhecida"
                    id="vaga-v3"
                >

                    <span class="numero">
                        V3
                    </span>

                    <span class="icone">
                        P
                    </span>

                    <span class="estado">
                        SEM DADOS
                    </span>

                </div>


                <div
                    class="vaga desconhecida"
                    id="vaga-v4"
                >

                    <span class="numero">
                        V4
                    </span>

                    <span class="icone">
                        P
                    </span>

                    <span class="estado">
                        SEM DADOS
                    </span>

                </div>

            </div>

        </div>


        <div class="rodape-painel">

            <div class="legenda">

                <div>
                    <span class="circulo verde"></span>
                    Livre
                </div>

                <div>
                    <span class="circulo vermelho"></span>
                    Ocupada
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
                    ESP8266 processa
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
                    VagaJá exibe
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
)VJHTML";
