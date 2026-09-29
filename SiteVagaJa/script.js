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
