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

## Registro de Interações TEMPLATE

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
## Registro de Interações

### Interação 1

- **Data:** 22/11/2025
- **Etapa do Projeto:** 1 – Entendimento do código base de Huffman
- **Ferramenta de IA Utilizada:** Ferramenta de IA generativa (ChatGPT)
- **Objetivo da Consulta:**
  Compreender melhor o código existente em C++ responsável por:
  - manipulação de árvores binárias (`arvore.cpp`/`arvore.h`);
  - construção da árvore de Huffman;
  - funções de travessia e geração de códigos (strings de 0/1).

- **Descrição do Tipo de Perguntas:**
  - Explicações linha a linha do código de árvore binária e da parte de construção da árvore de Huffman.
  - Comentários sobre nuances de C++ envolvidas (alocação dinâmica, `std::list`, recursão, ponteiros, etc.).

- **Resumo da Resposta da IA:**
  A ferramenta explicou:
  - Como a estrutura da árvore (`struct arvore`/`typedef Arvore`) é usada para representar os nós, com ponteiros para esquerda e direita.
  - Como as funções de criação, verificação de árvore vazia e liberação funcionam recursivamente.
  - Como a lista de nós de Huffman é ordenada por frequência e combinada até restar uma única árvore.
  - Como a travessia recursiva gera os códigos binários (0 para esquerda, 1 para direita) apenas nos nós folha.

- **Análise e Aplicação:**
  Essa interação foi usada para:
  - ENtender a lógica já existente.
  - Dar segurança para alterar o código

- **Referência no Código:**
  - Arquivos: `cpp/arvore.cpp`, `cpp/arvore.h`, `cpp/compress.cpp`

---

### Interação 2

- **Data:** 22/11/2025
- **Etapa do Projeto:** 1 – Definição do formato do arquivo compactado
- **Ferramenta de IA Utilizada:** Ferramenta de IA generativa (ChatGPT)
- **Objetivo da Consulta:**
  Definir um formato de arquivo para compactação com Huffman, incluindo:
  - Ideia de um cabeçalho mínimo (tamanho do arquivo original, bloco, número de blocos);
  - Como representar a árvore de Huffman dentro do arquivo;
  - Como organizar os dados comprimidos em bits.

- **Descrição do Tipo de Perguntas:**
  - Perguntas sobre como poderia ser um formato binário para um arquivo contendo header, árvore (trie) e stream de bits.
  - Dúvidas específicas sobre o papel de campos como `tamanho_original` e `tamanho_bloco` em um cabeçalho.

- **Resumo da Resposta da IA:**
  A IA sugeriu:
  - Um cabeçalho mínimo com campos para armazenar o tamanho original do arquivo e parâmetros de bloco (para futuras extensões).
  - Uma forma de serializar a árvore de Huffman em pré-ordem utilizando um bit para indicar se o nó é interno ou folha, seguido de um byte para o símbolo no caso das folhas.
  - A importância de registrar `tamanho_original` para que, na descompactação, seja possível saber quando parar de decodificar os bits .
  - Um formato lógico: `[Cabeçalho] [Trie serializada] [Dados comprimidos em bits]`.

- **Análise e Aplicação:**
  A partir dessa interação:
  - Foi adotada a ideia de guardar ao menos o `tamanho_original` no arquivo compactado.

- **Referência no Código:**
  - `cpp/compress.h` – definição da `struct Cabecalho`.
  - `cpp/compress.cpp` – uso de `Cabecalho` na função `compactar` para gravar o tamanho original do arquivo.

---

### Interação 3

- **Data:** 22/11/2025
- **Etapa do Projeto:** 1 – Implementação de bitstream e descompactação + correção de bug
- **Ferramenta de IA Utilizada:** Ferramenta de IA generativa (ChatGPT)
- **Objetivo da Consulta:**
  Implementar:
  - Escrita e leitura de bits (bitstream) em C++ para os códigos de Huffman;
  - Serialização e desserialização da árvore de Huffman em arquivo;
  - Funções de compactação e descompactação com interface de linha de comando.
  Além disso, depurar um bug onde o texto de teste não estava sendo descompactado corretamente.

- **Descrição do Tipo de Perguntas:**
  - Pedido de ajuda para criar classes auxiliares para escrita/leitura de bits.
  - Solicitações para estruturar funções `compactar` e `descompactar` com base no código existente
  - Descrição do bug de descompactação (saída incorreta) e investigação de possíveis causas relacionadas ao bitstream.

- **Resumo da Resposta da IA:**
  A IA:
  - Propôs estruturas de classes para escrita/leitura de bits em C++ (acúmulo de bits em um byte, flush final, leitura bit a bit).
  - Detalhou a lógica de serializar a árvore com `escreverTrie` e reconstruí-la com uma função simétrica `lerTrie` usando recursão.
  - Sugeriu o fluxo de `compactar`: duas passagens no arquivo (contagem de frequências e construção da árvore/códigos; depois escrita da trie e dos dados comprimidos).
  - Sugeriu o fluxo de `descompactar`: ler cabeçalho, reconstruir a árvore com `BitReader`, navegar na árvore com os bits até reconstruir o número correto de bytes.
  - Identificou um bug principal na descompressão: um `flush()` sendo chamado logo após escrever a trie, inserindo bits de padding que eram depois interpretados como início do texto. A correção foi remover o `flush()` intermediário, mantendo apenas o `flush()` final.

- **Análise e Aplicação:**
  - O design das classes `BitWriter` e `BitReader` foi inspirado na estrutura sugerida.
  - As funções `escreverTrie`, `lerTrie`, `escreverTexto`, `compactar` e `descompactar` foram implementadas com base na lógica discutida, sempre revisando manualmente para garantir entendimento de cada passo.
  - A explicação sobre o bug de padding foi essencial para corrigir a descompressão: após remover o `flush()` logo após a trie, os arquivos de teste passaram a ser restaurados corretamente.
  - A interface de linha de comando (`compactar` / `descompactar`) foi ajustada conforme a proposta, facilitando o uso e testes.

- **Referência no Código:**
  - `cpp/bitwriter.h`, `cpp/bitwriter.cpp` – implementação da escrita de bits.
  - `cpp/bitreader.h`, `cpp/bitreader.cpp` – implementação da leitura de bits.
  - `cpp/compress.cpp` – funções:
    - `escreverTrie`, `lerTrie`, `escreverTexto`;
    - `compactar(...)` e `descompactar(...)`;
    - `main` com comandos `compactar` e `descompactar`.
