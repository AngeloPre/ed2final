# Relatório de Uso de Inteligência Artificial Generativa

Este documento registra todas as interações significativas com ferramentas de IA generativa (como Gemini, ChatGPT, Copilot, etc.) durante o desenvolvimento deste projeto. O objetivo é promover o uso ético e transparente da IA como ferramenta de apoio, e não como substituta para a compreensão dos conceitos fundamentais.

## Política de Uso
O uso de IA foi permitido para as seguintes finalidades:
- Geração de ideias e brainstorming de algoritmos.
- Explicação de conceitos complexos.
- Geração de código boilerplate (ex: estrutura de classes, leitura de arquivos).
- Sugestões de refatoração e otimização de código.
- Debugging e identificação de causas de erros.
- Geração de casos de teste.

É proibido submeter código gerado por IA sem compreendê-lo completamente e sem adaptá-lo ao projeto. Todo trecho de código influenciado pela IA deve ser referenciado neste log.

---

## Registro de Interações

*Copie e preencha o template abaixo para cada interação relevante.*

### Interação 1

- **Data:** 20/10/2025
- **Etapa do Projeto:** 1 - Compressão de Arquivos
- **Ferramenta de IA Utilizada:** Gemini Advanced
- **Objetivo da Consulta:** Eu estava com dificuldades para entender como gerenciar o dicionário do algoritmo LZW quando ele atinge o tamanho máximo. Precisava de uma estratégia para lidar com isso.

- **Prompt(s) Utilizado(s):**
  1. "No algoritmo de compressão LZW, o que acontece quando o dicionário atinge o tamanho máximo? Quais são as estratégias mais comuns para lidar com isso?"
  2. "Pode me dar um exemplo em Python de como implementar a estratégia de 'resetar o dicionário' no LZW?"

- **Resumo da Resposta da IA:**
  A IA explicou três estratégias: 1) parar de adicionar novas entradas, 2) resetar o dicionário para o estado inicial, e 3) usar uma política de descarte, como LRU (Least Recently Used), que é mais complexa. A IA forneceu um pseudocódigo para a estratégia de reset, que parecia a mais simples e eficaz para este projeto.

- **Análise e Aplicação:**
  A resposta da IA foi extremamente útil para clarear as opções. Optei por implementar a estratégia de resetar o dicionário. O código fornecido pela IA não foi usado diretamente, pois estava muito simplificado e não se encaixava na minha arquitetura de classes. No entanto, a lógica de verificar o tamanho do dicionário e invocar uma função `reset_dictionary()` foi a base para a minha implementação. Isso me poupou tempo de pesquisa em artigos e livros.

- **Referência no Código:**
  A lógica inspirada por esta interação foi implementada no arquivo `compressor/lzw.py`, especificamente na função `compress()`, por volta da linha 85.

---

### Interação 2

- **Data:** ...
- **Etapa do Projeto:** ...
- **Ferramenta de IA Utilizada:** ...
- **Objetivo da Consulta:** ...
- **Prompt(s) Utilizado(s):** ...
- **Resumo da Resposta da IA:** ...
- **Análise e Aplicação:** ...
- **Referência no Código:** ...

---

### Interação 1

- **Data:** 27/10/2025
- **Etapa do Projeto:** 1 - Inicio
- **Ferramenta de IA Utilizada:** GPT Agent Mode
- **Objetivo da Consulta:** Não sei usar Rust então vou começar um projeto Hello World que minha equipe possa contribuir com menos esforço de rodar.

- **Prompt(s) Utilizado(s):**
  1. Aqui fiz algumas perguntas gerais sobre algumas conversas copiadas do whatsapp falando sobre o problema de compressão/busca pra validar se meu pensamento estava correto e alguns nomes das coisas, para ajudar a definir a tecnologia a ser usada entre C++ e Rust.
  2. "Me entregue uma forma de criar um projeto com Rust para resolver esse problema, eu estou pensando em uma forma facilitada, vou usar o WSL e quero uma solução que facilite a instalação para multiplos usuários estou usando uma solução em meu projeto angular, usei npm create @angular@19 nomedoprojeto e ele permite que eu use npm run start por exemplo que roda o ng serve etc, e isso facilitou muito para minha equipe gerenciar a versão do angular só tendo um node 19+ instalado no computador, tem alguma coisa com cargo que eu possa instalar no wsl com linha de comando que inicie um projeto rust facilitado pra cooperação entre pessoas codando um projeto juntas? qual boas práticas vocÊ sugere pra que a gente consiga trabalhar em equipe sem ter muitos problemas ao usar Rust? crie um planejamento completo e bem detalhado para iniciantes em Rust fazerem seu primeiro hello world e compartilhar isso entre os demais integrantes sem problemas pra começar a rodar, alguns processos de automação são bem vindos... vou codar no vscode, valeu!"

- **Resumo da Resposta da IA:**
  Guia para configurar um projeto Rust colaborativo no WSL
  1. Preparar o ambiente no Windows com WSL...
  2. Instalar rustup
  3. Instalar dependências de desenvolvimento
  4. Criar e compartilhar um projeto Rust
  cargo new hello_world --vcs none

- **Análise e Aplicação:**
  A resposta da IA foi extremamente útil para clarear as opções. Optei por implementar a estratégia de resetar o dicionário. O código fornecido pela IA não foi usado diretamente, pois estava muito simplificado e não se encaixava na minha arquitetura de classes. No entanto, a lógica de verificar o tamanho do dicionário e invocar uma função `reset_dictionary()` foi a base para a minha implementação. Isso me poupou tempo de pesquisa em artigos e livros.

- **Referência no Código:**
  A lógica inspirada por esta interação foi implementada no arquivo `compressor/lzw.py`, especificamente na função `compress()`, por volta da linha 85.