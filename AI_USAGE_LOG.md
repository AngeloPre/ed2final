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
- **Data:** 21/11/2025
- **Etapa do Projeto:** Contrução do script de leitura dos arquivos
- **Ferramenta de IA Utilizada:** GPT-5.1
- **Objetivo da Consulta:** Construir programa de leitura dos arquivos
- **Prompt(s) Utilizado(s):** 
  - make a simple C++ code that reads from a text file and outputs to a buffer with a fixed size
  - Can you show me how to handle the case where the file is larger than the buffer and I need to process it piece by piece?
  - how do i read the buffer get the int value for each byte and store it in this list?
- **Resumo da Resposta da IA:**
  A ferramenta gerou o código base que faz a leitura dos arquivos de texto e como acessar esses dados no buffer
- **Análise e Aplicação:**
  O codigo gerado foi testado e depois incorporado na leitura do arquivo de texto na aplicação.
- **Referência no Código:** `compress.cpp` no início da função compactar (linha 123 à 158).

### Interação 2

- **Data:** 21/11/2025
- **Etapa do Projeto:** Geração da lista de frequências e árvore de huffman
- **Ferramenta de IA Utilizada:** GPT-5.1
- **Objetivo da Consulta:** Entender a API das listas do C++ `std::list`
- **Prompt(s) Utilizado(s):**
  - make a function that sorts this list, ...
- **Resumo da Resposta da IA:** Exemplo de aplicação do método sort da lista.
- **Análise e Aplicação:** Usado quando é necessário ordenar a lista.
- **Referência no Código:** `huffman.cpp` na função compara_por_tamanho.

### Interação 4

- **Data:** 21/11/2025
- **Etapa do Projeto:** Geração da árvore de Huffman
- **Ferramenta de IA Utilizada:** Claude Sonnet 4.5
- **Objetivo da Consulta:** Gerar função para imprimir a árvore gerada para validação do código
- **Prompt(s) Utilizado(s):**
  - make a cpp function that prints this tree vertically in a human readable way in the terminal with all the nodes:
- **Resumo da Resposta da IA:** A IA gerou o código que faz print de uma árvore em C++.
- **Análise e Aplicação:** A função foi usada para validar a construção da árvore de huffman.
- **Referência no Código:** Em `compres.cpp` as funções printTreeHorizontal e printTree

### Interação 5

- **Data:** 21/11/2025
- **Etapa do Projeto:** Salvar dados gerados em disco
- **Ferramenta de IA Utilizada:** Claude Sonnet 4.5
- **Objetivo da Consulta:** Consultar como salvar dados gerados (árvore e códigos) em formato binário
- **Prompt(s) Utilizado(s):** 
  - how do i convert the sequences in this list in to bit sequences to write down to a file for compression:
  - how can save my huffman tree for decompression
- **Resumo da Resposta da IA:** 
  A IA explicou como salvar os códigos gerados que estavam em strings do tipo '010' em binário para salvar no arquivo e sugeriu percorrer a árvore em ordem salvando 0 em nós normais e 1 em nós folha para a recuperação posterior dos dados.
- **Análise e Aplicação:**
  O código gerado para salvar dados binários foi entendido e incorporado na aplicação bem como a estratégia de salvar a árvore em orderm.
- **Referência no Código:**
  A lógica de escrita implementada na classe `BitWriter` com as funções `writeBit`, `writeByte` e `flush`. A lógica de percorrer a árvore está em `compress.cpp` na função `escreverTrie`.
  

### Interação 6

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

### Interação 7

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

### Interação 8

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

### Interação 9

- **Data:** 22/11/2025
- **Etapa do Projeto:** Teste de compactação em arquivos grandes
- **Ferramenta de IA Utilizada:** GPT-5.1
- **Objetivo da Consulta:** Obter um script que gera um arquivo de texto grande para teste de compressão
- **Prompt(s) Utilizado(s):** make a script that writes a 1GB lorem ipsolum in a txt file
- **Resumo da Resposta da IA:** A IA gerou um script python que gera um arquivo txt estilo lorem ipsolum para testes.
- **Análise e Aplicação:** O código foi analisado e incorporado no projeto.
- **Referência no Código:** Arquivo `generate_file.py`

### Interação 10

- **Data:** 22/11/2025
- **Etapa do Projeto:** Debug do algoritmo KMP e otimizações
- **Ferramenta de IA Utilizada:** Claude Sonnet 4.5
- **Objetivo da Consulta:** Validar a implementação do KMP e otimizar a execução do algoritmo.
- **Prompt(s) Utilizado(s):** 
  - does this DFA creation work?
  - How should I implement the resetDFA() method to properly clean up memory?
  - i added the position and state, does this DFA continue working after finding the first substring or do i need to add another line to matrix?
  - couldn’t i just add another line to the DFA such that the automaton finds “string ending with my substring”
  - i got an error for my test, ...
- **Resumo da Resposta da IA:**
  A IA validou e corrigiu pequenos bugs de sintaxe da implementção do DFA além de auxiliar na implementação da função de limpesa de memória. Depois auxiliou a expandir o DFA como foi estudado em outros materiais em que o DFA pode continuar rodando sem reset. Por fim corrigiu um bug na criação do dicionário a partir da substring.
- **Análise e Aplicação:** 
  A IA ajudou no refino do código do DFA e ajudou a corrigir bugs.
- **Referência no Código:** 
  Na classe `KMP` no arquivo `KMP.cpp` ajudou a corrigir bugs no laço da linha 24 o método `resetDFA` e o laço da linha 43.

### Interação 10

- **Data:** 22/11/2025
- **Etapa do Projeto:** 2 – Busca de Substring em Arquivo Grande
- **Ferramenta de IA Utilizada:** Claude (Anthropic)
- **Objetivo da Consulta:**
  Implementar a funcionalidade de busca de substring em arquivos grandes usando o algoritmo KMP já implementado, com:
  - Processamento em chunks para arquivos maiores que a memória RAM;
  - Tratamento de caracteres UTF-8 e valores > 127;
  - Integração com a interface de linha de comando existente.

- **Descrição do Tipo de Perguntas:**
  - Como adaptar o KMP existente para processar arquivos em chunks sem perder matches nas bordas;
  - Diagnóstico e correção de erro std::out_of_range ao processar arquivos com caracteres especiais;
  - Como lidar com caracteres negativos em C++ quando char é signed por padrão.

- **Resumo da Resposta da IA:**
  A IA identificou e propôs soluções para:
  - Processamento em chunks: Implementar overlap entre buffers consecutivos de tamanho pattern_length - 1 para garantir que padrões divididos entre chunks sejam detectados;
  - Bug de caracteres: O problema principal era que caracteres > 127 eram interpretados como negativos (devido ao char signed), causando índices negativos no DFA. A solução foi:
    - Mudar o DFA de 128 para 256 posições;
    - Usar unsigned char na assinatura de stepDFA;
    - Aplicar duplo cast static_cast<int>(static_cast<unsigned char>(c)) em todos os acessos ao DFA;
  - Estrutura da busca: Manter o estado do KMP entre caracteres processados (já estava correto no código original), acumular posições encontradas e calcular offsets absolutos no arquivo.

- **Análise e Aplicação:**
  - Foi implementada a função buscar_simples em compress.cpp com a lógica de chunks e overlap sugerida;
  - O KMP foi corrigido para suportar 256 caracteres ao invés de apenas 128 ASCII básicos;
  - A análise sobre o estado persistente do KMP confirmou que a implementação original já permitia detecção de matches sobrepostos;
  - Foi adicionado #include <vector> em compress.cpp para resolver erro de compilação;
  - A interface de linha de comando foi estendida com o comando buscar_simples.

- **Referência no Código:**
  - `cpp/kmp.h` – mudança na assinatura de stepDFA para unsigned char;
  - `cpp/kmp.cpp` – ajustes no construtor (256 ao invés de 128), initializeDFA com casts corretos, e stepDFA com parâmetro unsigned char;
  - `cpp/compress.cpp` – implementação da função buscar_simples com processamento em chunks e tratamento de overlap;
  - `cpp/compress.cpp` – atualização da função main para suportar o comando buscar_simples.

- **Data:** 23/11/2025
- **Etapa do Projeto:** Configurações de compilação para a versão final
- **Ferramenta de IA Utilizada:** GPT-5.1
- **Objetivo da Consulta:** Gerar um makefile para compilação do projeto
- **Prompt(s) Utilizado(s):** 
  make a simple makefile for compiliing compress.cpp, i put the other files under the lib folder, how do i set the VSCode IDE and clang/g++ to import the header files correcly?
- **Resumo da Resposta da IA:** A IA explicou como configurar o VSCode para lidar com os imports e gerou um makefile para facilitar na compilação do projeto.
- **Análise e Aplicação:** O código foi testado e implementado no workflow.
- **Referência no Código:** Arquivo `makefile`