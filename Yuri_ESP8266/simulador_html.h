#pragma once
#include <Arduino.h>

const char VJSIM_DATA[] PROGMEM = R"VJSIM(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<title>VagaJá - Simulador</title>
<style>
body{font-family:Arial,sans-serif;background:#f4f4f4;text-align:center;margin:0;padding:24px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(140px,1fr));gap:14px;max-width:850px;margin:24px auto}
.card{background:white;border-radius:12px;padding:18px;box-shadow:0 3px 10px #0002}
.estado{font-weight:bold;margin:12px 0} .livre{color:#16803c} .ocupada{color:#c62828}
button{padding:10px 14px;border:0;border-radius:8px;cursor:pointer}
pre{max-width:820px;margin:24px auto;background:#222;color:#8cff8c;text-align:left;padding:16px;border-radius:10px;white-space:pre-wrap}
</style>
</head>
<body>
<h1>VagaJá</h1>
<p>Simulador local do ESP8266 - 8 vagas</p>
<p><a href="/">Voltar ao painel</a></p>
<div class="grid">
<div class="card"><h2>V1</h2><div id="e1" class="estado">...</div><button onclick="alternar(1)">Alterar</button></div>
<div class="card"><h2>V2</h2><div id="e2" class="estado">...</div><button onclick="alternar(2)">Alterar</button></div>
<div class="card"><h2>V3</h2><div id="e3" class="estado">...</div><button onclick="alternar(3)">Alterar</button></div>
<div class="card"><h2>V4</h2><div id="e4" class="estado">...</div><button onclick="alternar(4)">Alterar</button></div>
<div class="card"><h2>V5</h2><div id="e5" class="estado">...</div><button onclick="alternar(5)">Alterar</button></div>
<div class="card"><h2>V6</h2><div id="e6" class="estado">...</div><button onclick="alternar(6)">Alterar</button></div>
<div class="card"><h2>V7</h2><div id="e7" class="estado">...</div><button onclick="alternar(7)">Alterar</button></div>
<div class="card"><h2>V8</h2><div id="e8" class="estado">...</div><button onclick="alternar(8)">Alterar</button></div>
</div>
<pre id="json">Carregando...</pre>
<script>
let dados={};
async function carregar(){
  const r=await fetch('/vagas',{cache:'no-store'});
  dados=await r.json();
  for(let i=1;i<=8;i++){
    const el=document.getElementById('e'+i);
    const ocupado=dados['V'+i]===1;
    el.textContent=ocupado?'OCUPADA':'LIVRE';
    el.className='estado '+(ocupado?'ocupada':'livre');
  }
  document.getElementById('json').textContent=JSON.stringify(dados,null,2);
}
async function alternar(n){
  const ocupada=dados['V'+n]===0 ? 1 : 0;
  const r=await fetch('/api/vagas/'+n,{
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body:JSON.stringify({ocupada})
  });
  if(!r.ok){alert('Erro ao atualizar a vaga');return;}
  await carregar();
}
carregar();
</script>
</body>
</html>
)VJSIM";
