# Banco INF101

**Centro Universitário de Viçosa (UNIVIÇOSA)**
**Disciplina:** INF101 – Programação de Computadores I
**Professores:** Anderson R. Lamas e Vanderlea Queiroz
**Trabalho:** Implementação de um Sistema de Registro e Gestão de Contas Bancárias – Etapa 1
**Aluno:** Maurílio Pereira-25440

## Sumário

1. [Descrição do projeto](#descrição-do-projeto)
2. [Funcionalidades](#funcionalidades)
3. [Variáveis utilizadas](#variáveis-utilizadas)
4. [Validações implementadas](#validações-implementadas)
5. [Desafios propostos](#desafios-propostos)
6. [Compilação e execução](#compilação-e-execução)
7. [Exemplo de utilização](#exemplo-de-utilização)
8. [Limitações e próximas etapas](#limitações-e-próximas-etapas)

## Descrição do projeto

Este repositório contém a Etapa 1 do trabalho prático da disciplina INF101, que propõe o desenvolvimento incremental, em três etapas, de um Sistema de Registro e Gestão de Contas Bancárias em linguagem C++. Esta primeira etapa tem como objetivo consolidar os fundamentos da linguagem, com ênfase em variáveis, estruturas de controle e estruturas de repetição.

O sistema, denominado **BANCO INF101**, é executado em modo texto e mantém um menu ativo até que o usuário escolha a opção de saída. A seleção das operações é feita por meio da estrutura `switch`, e a repetição do menu é controlada por um laço `do-while`, conforme especificado no enunciado.

## Funcionalidades

| Opção | Operação | Descrição |
|:-----:|----------|-----------|
| 1 | Cadastrar conta | Solicita número da conta, nome do titular, CPF, senha, tipo da conta e saldo inicial. |
| 2 | Consultar conta | Exibe titular, CPF, número, tipo, situação e, para contas correntes, o limite de crédito. |
| 3 | Verificar saldo | Apresenta o saldo atual e, para contas correntes, o limite de crédito e o total disponível. |
| 4 | Alterar tipo da conta | Altera o tipo entre Corrente e Poupança, atualizando o limite de crédito. |
| 5 | Ativar/Desativar conta | Alterna a situação da conta entre ativa e inativa. |
| 6 | Sair | Encerra a execução do sistema. |

## Variáveis utilizadas

### Variáveis obrigatórias (item 3.1 do enunciado)

| Variável | Tipo | Finalidade |
|----------|------|------------|
| `numeroConta` | `int` | Número da conta |
| `nomeCliente` | `string` | Nome do titular |
| `cpf` | `string` | CPF do titular |
| `tipoConta` | `int` | 1 = Corrente; 2 = Poupança |
| `saldo` | `double` | Saldo atual |
| `contaAtiva` | `bool` | Indica se a conta está ativa |

### Variáveis adicionais

Atendendo à sugestão do item 3.5, foram acrescentadas ao cadastro as seguintes variáveis:

| Variável | Tipo | Finalidade |
|----------|------|------------|
| `senha` | `string` | Senha definida pelo titular no cadastro |
| `limiteCredito` | `double` | Limite de crédito da conta (R$ 500,00 para Corrente; R$ 0,00 para Poupança) |
| `totalContas` | `int` | Quantidade de contas cadastradas até o momento |
| `MAX_CONTAS` | `const int` | Quantidade máxima de contas permitidas (5) |

## Validações implementadas

Conforme o item 3.4 do enunciado:

- O número da conta deve ser maior que zero.
- O saldo inicial não pode ser negativo.
- O tipo da conta deve ser 1 (Corrente) ou 2 (Poupança), tanto no cadastro quanto na alteração de tipo.
- As operações de verificação de saldo e de alteração de tipo verificam previamente se a conta está ativa (`contaAtiva`).

Adicionalmente, o sistema:

- impede o cadastro de duas contas com o mesmo número, o que tornaria a segunda conta inacessível nas buscas;
- impede o cadastro de novas contas quando o limite de cinco contas é atingido;
- informa quando não há contas cadastradas ou quando a conta pesquisada não é encontrada;
- exibe mensagem de erro e solicita novamente o valor sempre que uma entrada inválida é digitada, inclusive na alteração do tipo da conta.

### Tratamento de entradas não numéricas

Quando o usuário digita um texto em um campo que espera um número, a leitura com `cin` falha e o fluxo de entrada permanece em estado de erro. Sem tratamento, todas as leituras seguintes também falham, e o programa entra em um laço infinito.

Para evitar esse problema, todas as leituras numéricas do sistema (opção do menu, número da conta, tipo da conta, depósito inicial e número da conta nas buscas) verificam o resultado da leitura. Em caso de falha, o programa:

1. restaura o estado do fluxo com `cin.clear()`;
2. descarta o conteúdo inválido com `cin.ignore(numeric_limits<streamsize>::max(), '\n')`;
3. exibe uma mensagem de erro e solicita o valor novamente.

Na alteração do tipo da conta, o novo valor é lido em uma variável auxiliar (`novoTipo`) e somente é atribuído à conta após ser validado, de modo que uma entrada inválida não altera os dados já cadastrados.

## Desafios propostos

**Acrescente mais variáveis no cadastro.**
Foram acrescentadas as variáveis `senha` e `limiteCredito`, descritas na seção anterior.

**Comente seu código sempre que possível.**
O código-fonte contém comentários explicando a finalidade das principais variáveis e trechos de lógica.

**Se quiséssemos cadastrar até 5 contas, qual solução seria possível? Implemente esta solução.**
Com o uso exclusivo de variáveis individuais, seria necessário declarar um conjunto de variáveis para cada conta (por exemplo, `numeroConta1`, `numeroConta2`, ..., `numeroConta5`), o que tornaria o código extenso, repetitivo e difícil de manter. A solução adotada foi a utilização de **arrays paralelos**: cada informação da conta é armazenada em um vetor de tamanho `MAX_CONTAS`, e o mesmo índice identifica a mesma conta em todos os vetores. Por exemplo, `nomeCliente[i]`, `cpf[i]` e `saldo[i]` pertencem à mesma conta. A variável `totalContas` controla quantas posições já foram preenchidas, e a localização de uma conta pelo seu número é feita por meio de busca linear com um laço `for`.

## Compilação e execução

É necessário um compilador C++ compatível com o padrão C++11 ou superior (por exemplo, GCC, Clang ou MSVC).

Clone o repositório e acesse o diretório do projeto:

```bash
git clone https://github.com/SEU-USUARIO/banco-inf101.git
cd banco-inf101
```

Compile o código-fonte:

```bash
g++ main.cpp -o banco
```

Execute o programa:

```bash
./banco        # Linux e macOS
banco.exe      # Windows
```

Caso o arquivo-fonte possua outro nome, substitua `main.cpp` pelo nome correspondente.

## Exemplo de utilização

Cadastro de uma nova conta:

```
========================================
           BANCO INF101
========================================
 1 - Cadastrar nova conta (0/5)
 2 - Consultar dados de uma conta
 3 - Verificar saldo disponivel
 4 - Alterar tipo de uma conta
 5 - Ativar/Desativar uma conta
 6 - Encerrar o sistema
========================================
Escolha uma opcao: 1

>>> INICIANDO NOVO CADASTRO <<<
Digite o numero da conta (maior que zero): 1001
Digite o nome completo do titular: Maria Silva
Digite o CPF (apenas numeros): 12345678900
Crie uma senha para a conta: ****
Selecione o tipo (1 = Corrente | 2 = Poupanca): 1
Digite o deposito inicial (R$): 250

[SUCESSO] Conta numero 1001 cadastrada e ativada!
```

Consulta de saldo da conta cadastrada:

```
>>> SALDO DISPONIVEL <<<
 Saldo Atual: R$ 250.00
 Limite.....: R$ 500.00
 Total Livre: R$ 750.00
```

## Limitações e próximas etapas

Conforme a proposta do trabalho, as limitações de cada etapa motivam o conteúdo da etapa seguinte. Na versão atual, observam-se as seguintes limitações:

- **Código concentrado na função `main`:** a lógica de busca de conta é repetida em várias opções do menu. Na próxima etapa, com o estudo de funções, essa lógica poderá ser modularizada e reaproveitada.
- **Dados mantidos apenas em memória:** todas as informações são perdidas ao encerrar o programa. A etapa final, que aborda persistência de dados em arquivos, permitirá salvar e recuperar as contas cadastradas.
- **Código de validação repetido:** o tratamento de entradas inválidas se repete em várias leituras. Com o uso de funções, esse tratamento poderá ser centralizado em uma única rotina de leitura.
- **Validações ainda simples:** o formato do CPF não é validado, e a senha cadastrada ainda não é utilizada para autenticar operações.
