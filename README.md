# Banco INF101

> ## 📂 Etapas do trabalho
> | Etapa | Onde está |
> |---|---|
> | Etapa 1 – variáveis, decisão e repetição | Raiz deste repositório (este README) |
> | **Etapa 2 – várias contas com arrays e histórico de movimentações** | [`etapa-2/`](etapa-2/) → [README da Etapa 2](etapa-2/README.md) |

**Centro Universitário de Viçosa (UNIVIÇOSA)**
**Disciplina:** INF101 – Programação de Computadores I
**Professores:** Anderson R. Lamas e Vanderlea Queiroz
**Trabalho:** Implementação de um Sistema de Registro e Gestão de Contas Bancárias – Etapa 1
**Aluno:** Maurílio Pereira-25440

## Sumário

1. [Descrição do projeto](#descrição-do-projeto)
2. [Estrutura do repositório](#estrutura-do-repositório)
3. [Funcionalidades](#funcionalidades)
4. [Variáveis utilizadas](#variáveis-utilizadas)
5. [Validações implementadas](#validações-implementadas)
6. [Desafios propostos](#desafios-propostos)
7. [Justificativa para o uso de arrays](#justificativa-para-o-uso-de-arrays)
8. [Compilação e execução](#compilação-e-execução)
9. [Exemplo de utilização](#exemplo-de-utilização)
10. [Limitações e próximas etapas](#limitações-e-próximas-etapas)

## Descrição do projeto

Este repositório contém a Etapa 1 do trabalho prático da disciplina INF101, que propõe o desenvolvimento incremental, em três etapas, de um Sistema de Registro e Gestão de Contas Bancárias em linguagem C++. Esta primeira etapa tem como objetivo consolidar os fundamentos da linguagem, com ênfase em variáveis, estruturas de controle e estruturas de repetição.

O sistema, denominado **BANCO INF101**, é executado em modo texto e mantém um menu ativo até que o usuário escolha a opção de saída. A seleção das operações é feita por meio da estrutura `switch`, e a repetição do menu é controlada por um laço `do-while`, conforme especificado no enunciado.

## Estrutura do repositório

| Arquivo | Descrição |
|---------|-----------|
| `main.cpp` | Versão principal da Etapa 1. Permite o cadastro de **uma** conta e utiliza **somente variáveis individuais**, conforme exigido no item 3 do enunciado. |
| `desafio_5_contas.cpp` | Resolução do desafio do item 3.5. Permite o cadastro de **até cinco** contas e utiliza **arrays**. |
| `README.md` | Documentação do projeto. |

A separação em dois arquivos foi adotada para atender simultaneamente às duas exigências do enunciado: a versão principal respeita a restrição de uso exclusivo de variáveis individuais, enquanto a versão do desafio implementa a solução solicitada para o cadastro de múltiplas contas.

## Funcionalidades

Ambas as versões oferecem as mesmas operações:

| Opção | Operação | Descrição |
|:-----:|----------|-----------|
| 1 | Cadastrar conta | Solicita número da conta, nome do titular, CPF, senha, tipo da conta e saldo inicial. |
| 2 | Consultar conta | Exibe titular, CPF, número, tipo, situação e, para contas correntes, o limite de crédito. |
| 3 | Verificar saldo | Apresenta o saldo atual e, para contas correntes, o limite de crédito e o total disponível. |
| 4 | Alterar tipo da conta | Altera o tipo entre Corrente e Poupança, atualizando o limite de crédito. |
| 5 | Ativar/Desativar conta | Alterna a situação da conta entre ativa e inativa. |
| 6 | Sair | Encerra a execução do sistema. |

Na versão principal, as operações de 2 a 5 atuam sobre a única conta cadastrada. Na versão do desafio, o sistema solicita o número da conta e a localiza entre as contas cadastradas.

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

Na versão principal (`main.cpp`), essas variáveis são declaradas de forma individual. Na versão do desafio (`desafio_5_contas.cpp`), cada uma delas é declarada como um array de cinco posições.

### Variáveis adicionais

Atendendo à sugestão do item 3.5, foram acrescentadas as seguintes variáveis:

| Variável | Tipo | Versão | Finalidade |
|----------|------|--------|------------|
| `senha` | `string` | ambas | Senha definida pelo titular no cadastro |
| `limiteCredito` | `double` | ambas | Limite de crédito da conta (R$ 500,00 para Corrente; R$ 0,00 para Poupança) |
| `contaCadastrada` | `bool` | principal | Indica se já existe uma conta cadastrada |
| `totalContas` | `int` | desafio | Quantidade de contas cadastradas até o momento |
| `MAX_CONTAS` | `const int` | desafio | Quantidade máxima de contas permitidas (5) |

## Validações implementadas

Conforme o item 3.4 do enunciado, ambas as versões verificam que:

- o número da conta é maior que zero;
- o saldo inicial não é negativo;
- o tipo da conta é 1 (Corrente) ou 2 (Poupança), tanto no cadastro quanto na alteração de tipo;
- a conta está ativa (`contaAtiva`) antes das operações de verificação de saldo e de alteração de tipo.

Adicionalmente:

- a versão principal impede um novo cadastro quando já existe uma conta cadastrada;
- a versão do desafio impede o cadastro de duas contas com o mesmo número e o cadastro de novas contas após o limite de cinco;
- ambas informam quando não há conta cadastrada e, na versão do desafio, quando a conta pesquisada não é encontrada;
- ambas exibem mensagem de erro e solicitam novamente o valor sempre que uma entrada inválida é digitada.

### Tratamento de entradas não numéricas

Quando o usuário digita um texto em um campo que espera um número, a leitura com `cin` falha e o fluxo de entrada permanece em estado de erro. Sem tratamento, todas as leituras seguintes também falham, e o programa entra em um laço infinito.

Para evitar esse problema, todas as leituras numéricas do sistema verificam o resultado da leitura. Em caso de falha, o programa:

1. restaura o estado do fluxo com `cin.clear()`;
2. descarta o conteúdo inválido com `cin.ignore(numeric_limits<streamsize>::max(), '\n')`;
3. exibe uma mensagem de erro e solicita o valor novamente.

Na alteração do tipo da conta, o novo valor é lido em uma variável auxiliar (`novoTipo`) e somente é atribuído à conta após ser validado, de modo que uma entrada inválida não altera os dados já cadastrados.

## Desafios propostos

**Acrescente mais variáveis no cadastro.**
Foram acrescentadas as variáveis `senha` e `limiteCredito`, descritas na seção de variáveis.

**Comente seu código sempre que possível.**
Ambos os arquivos contêm comentários explicando a finalidade das variáveis e dos principais trechos de lógica.

**Se quiséssemos cadastrar até 5 contas, qual solução seria possível? Implemente esta solução.**
A solução adotada foi a utilização de **arrays**, implementada no arquivo `desafio_5_contas.cpp`. A justificativa para essa escolha é apresentada na seção seguinte.

## Justificativa para o uso de arrays

### A limitação das variáveis individuais

Na versão principal, cada informação da conta é armazenada em uma única variável. Por exemplo, `numeroConta` guarda o número de uma única conta. Ao cadastrar uma segunda conta, os valores da primeira seriam sobrescritos. Por esse motivo, a versão principal permite apenas um cadastro.

### A alternativa sem arrays

Para cadastrar cinco contas utilizando somente variáveis individuais, seria necessário declarar cinco cópias de cada variável:

```cpp
int numeroConta1, numeroConta2, numeroConta3, numeroConta4, numeroConta5;
string nomeCliente1, nomeCliente2, nomeCliente3, nomeCliente4, nomeCliente5;
double saldo1, saldo2, saldo3, saldo4, saldo5;
// ... e assim por diante para cada informação da conta
```

Além das declarações, cada operação do menu teria de ser escrita cinco vezes, uma para cada conjunto de variáveis. Para consultar o saldo, por exemplo, seria necessário comparar o número digitado com cada uma das contas separadamente:

```cpp
if (numBusca == numeroConta1) {
    cout << saldo1;
} else if (numBusca == numeroConta2) {
    cout << saldo2;
} else if (numBusca == numeroConta3) {
    cout << saldo3;
}
// ... repetido para as cinco contas e para todas as operações
```

Essa abordagem apresenta os seguintes problemas:

- **Repetição de código:** o mesmo trecho é escrito várias vezes, apenas com nomes de variáveis diferentes.
- **Dificuldade de manutenção:** uma correção ou alteração precisa ser replicada em todas as cópias, o que aumenta a chance de erros.
- **Falta de escalabilidade:** ampliar o limite de cinco para cem contas exigiria centenas de novas variáveis e condições.

### A solução com arrays

Um array permite armazenar vários valores do mesmo tipo sob um único nome, acessados por meio de um índice. Na versão do desafio, cada informação da conta é declarada como um array de tamanho `MAX_CONTAS`:

```cpp
const int MAX_CONTAS = 5;

int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
double saldo[MAX_CONTAS];
// ...
```

Essa organização é conhecida como **arrays paralelos**: o mesmo índice identifica a mesma conta em todos os arrays. Assim, `numeroConta[0]`, `nomeCliente[0]` e `saldo[0]` pertencem à primeira conta; `numeroConta[1]`, `nomeCliente[1]` e `saldo[1]` pertencem à segunda, e assim sucessivamente.

A variável `totalContas` indica quantas posições já foram preenchidas e é utilizada como índice no momento do cadastro. Para localizar uma conta, basta um único laço `for`, independentemente da quantidade de contas:

```cpp
for (int i = 0; i < totalContas; i++) {
    if (numeroConta[i] == numBusca) {
        cout << saldo[i];
        break;
    }
}
```

Com isso, o código de cada operação é escrito uma única vez, e o limite de contas pode ser alterado modificando apenas o valor da constante `MAX_CONTAS`.

### Relação com as etapas do trabalho

Conforme a proposta do trabalho, as limitações de uma etapa servem de motivação para o conteúdo da etapa seguinte. A impossibilidade de cadastrar mais de uma conta com variáveis individuais, observada na versão principal, é justamente a motivação para o uso de arrays, conteúdo previsto para a Etapa 2. A versão do desafio antecipa essa solução, conforme solicitado no item 3.5 do enunciado.

## Compilação e execução

É necessário um compilador C++ compatível com o padrão C++11 ou superior (por exemplo, GCC, Clang ou MSVC).

Clone o repositório e acesse o diretório do projeto:

```bash
git clone https://github.com/mp7710/github-api-exercise
cd banco-inf101
```

Compile e execute a versão principal:

```bash
g++ main.cpp -o banco
./banco          # Linux e macOS
banco.exe        # Windows
```

Compile e execute a versão do desafio:

```bash
g++ desafio_5_contas.cpp -o desafio
./desafio        # Linux e macOS
desafio.exe      # Windows
```

## Exemplo de utilização

Cadastro de uma conta na versão principal:

```
========================================
           BANCO INF101
========================================
 1 - Cadastrar conta
 2 - Consultar conta
 3 - Verificar saldo
 4 - Alterar tipo da conta
 5 - Ativar/Desativar conta
 6 - Sair
========================================
Escolha uma opcao: 1

>>> INICIANDO NOVO CADASTRO <<<
Digite o numero da conta (maior que zero): 1001
Digite o nome completo do titular: Maria Silva
Digite o CPF (apenas numeros): 12345678900
Crie uma senha para a conta: ****
Selecione o tipo (1 = Corrente | 2 = Poupanca): 1
Digite o saldo inicial (R$): 250

[SUCESSO] Conta numero 1001 cadastrada e ativada!
```

Consulta de saldo da conta cadastrada:

```
>>> SALDO DISPONIVEL <<<
 Saldo Atual: R$ 250.00
 Limite.....: R$ 500.00
 Total Livre: R$ 750.00
```

Tentativa de cadastrar uma segunda conta na versão principal:

```
[AVISO] Ja existe uma conta cadastrada (numero 1001).
        Esta versao do sistema permite apenas uma conta.
```

## Limitações e próximas etapas

Na versão atual, observam-se as seguintes limitações, que motivam o conteúdo das próximas etapas:

- **Código concentrado na função `main`:** trechos como a validação de entradas e, na versão do desafio, a busca de conta se repetem em várias opções do menu. Na próxima etapa, com o estudo de funções, essa lógica poderá ser modularizada e reaproveitada.
- **Dados mantidos apenas em memória:** todas as informações são perdidas ao encerrar o programa. A etapa final, que aborda persistência de dados em arquivos, permitirá salvar e recuperar as contas cadastradas.
- **Validações ainda simples:** o formato do CPF não é validado, e a senha cadastrada ainda não é utilizada para autenticar operações.
