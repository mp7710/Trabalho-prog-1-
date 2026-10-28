# Banco INF101 — Etapa 2

**Centro Universitário de Viçosa (UNIVIÇOSA)**
**Disciplina:** INF101 — Programação de Computadores I
**Professores:** Anderson R. Lamas e Vanderlea Queiroz
**Aluno:** Maurílio Pereira Santana Oliveira Nunes
**Curso:** Engenharia de Computação

Trabalho: *Implementação de um Sistema de Registro e Gestão de Contas Bancárias (Etapa 2)*, em C++.

---

## 📌 Informações da entrega

| Item | Detalhe |
|---|---|
| Valor | 8 pontos |
| Data | 11/11/2026 (ou 04/11/2026, se preferir) |
| Formato | Código organizado no GitHub e link compartilhado na planilha do professor |
| Apresentação | Mostrar o programa funcionando no laboratório |

O enunciado completo está em [`enunciado-etapa2.pdf`](enunciado-etapa2.pdf).

---

## 📝 O que foi pedido

Na Etapa 2 o sistema deve ser ampliado para **trabalhar com várias contas** e **registrar as movimentações em memória**. A ideia é perceber que criar variáveis como `numeroConta1`, `numeroConta2`, `numeroConta3`… não é escalável, e por isso usar **arrays** para representar o conjunto de contas e o histórico de movimentações.

Não é obrigatório criar funções: as operações podem ficar direto no `main()`, com estruturas de decisão e repetição.

### 1. Dados das contas (arrays paralelos)

```cpp
const int MAX_CONTAS = 100;   // limite máximo de 100 contas

int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];

int quantidadeContas = 0;
```

Cada índice `i` representa uma conta: `numeroConta[i]`, `nomeCliente[i]`, `saldo[i]` etc. se referem à mesma conta.

### 2. Histórico de movimentações

```cpp
const int MAX_MOVIMENTACOES = 500;

int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];

int quantidadeMovimentacoes = 0;
```

| Código | Movimentação | Efeito no saldo |
|:---:|---|---|
| `D` | Depósito | + valor |
| `S` | Saque | − valor |
| `T` | Transferência | Pode ser registrada como saída (`S`) e entrada (`D`) |

### 3. Funcionalidades obrigatórias

1. Cadastrar contas
2. Listar as contas cadastradas
3. Consultar uma conta pelo número
4. Realizar depósitos
5. Realizar saques, **verificando saldo suficiente**
6. Realizar transferências entre duas contas
7. Exibir o extrato de uma conta

> **Obs.:** as opções 4, 5 e 6 **devem registrar as movimentações** no histórico.

### 4. Depósito

A operação altera o saldo e registra uma nova movimentação. A conta é buscada pelo número informado pelo usuário.

```cpp
saldo[indice] = saldo[indice] + valor;

contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
tipoMovimentacao[quantidadeMovimentacoes] = 'D';
valorMovimentacao[quantidadeMovimentacoes] = valor;

quantidadeMovimentacoes++;
```

### 5. Transferência entre duas contas

Antes de transferir, o programa deve:

- localizar as duas contas;
- verificar se **ambas existem e estão ativas**;
- confirmar que o **valor é positivo**;
- verificar se a conta de origem tem **saldo suficiente**;
- garantir que há **espaço para dois registros** no histórico.

**Exemplo do enunciado:**

| Conta | Cliente | Saldo inicial | Após transferir R$ 300,00 |
|---|---|---|---|
| 1001 | Ana | R$ 1.000,00 | R$ 700,00 |
| 1002 | Bruno | R$ 500,00 | R$ 800,00 |

A transferência gera **dois registros** no histórico (e `quantidadeMovimentacoes` aumenta em 2):

| Conta | Tipo | Valor |
|---|:---:|---|
| 1001 | S | 300,00 |
| 1002 | D | 300,00 |

```cpp
saldo[indiceOrigem]  = saldo[indiceOrigem]  - valor;
saldo[indiceDestino] = saldo[indiceDestino] + valor;
```

### 6. Extrato

Percorre o histórico e mostra **apenas** as movimentações da conta consultada:

```cpp
for (int i = 0; i < quantidadeMovimentacoes; i++) {
    if (contaMovimentacao[i] == numeroConta) {
        if (tipoMovimentacao[i] == 'D')
            cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
        else if (tipoMovimentacao[i] == 'S')
            cout << "Saque: R$ " << valorMovimentacao[i] << endl;
    }
}
```

### ⚠️ Atenção

Na Etapa 2 os dados ficam **apenas na memória**: ao fechar o programa, contas e movimentações são perdidas. A persistência (salvar em arquivo) fica para a **Etapa 3**.

### 🏆 Desafio (opcional)

Modularizar o programa em funções:

```cpp
void cadastrarConta();
void listarContas();
void consultarConta();
void depositar();
void sacar();
void transferir();
void registrarMovimentacao();
void exibirExtrato();
```

---

## 💻 Como o trabalho foi implementado

O programa foi feito em **C++** usando os arrays globais pedidos no enunciado e **modularizado em funções** (desafio opcional), chamadas a partir de um menu no `main()`:

```
========== SISTEMA BANCARIO ==========
1. Cadastrar conta
2. Listar contas
3. Consultar conta
4. Realizar deposito
5. Realizar saque
6. Realizar transferencia
7. Exibir extrato
0. Sair
======================================
```

| Opção | Função | O que faz |
|:---:|---|---|
| 1 | `cadastrarConta()` | Lê número, nome, CPF e tipo (1-Corrente / 2-Poupança); começa com saldo 0 e conta ativa; respeita o limite de 100 contas |
| 2 | `listarContas()` | Mostra número, cliente e saldo de todas as contas ativas |
| 3 | `consultarConta()` | Busca pelo número e mostra cliente, CPF, tipo e saldo |
| 4 | `depositar()` | Valida valor positivo, soma ao saldo e registra `D` no histórico |
| 5 | `sacar()` | Valida valor positivo e saldo suficiente, subtrai e registra `S` |
| 6 | `transferir()` | Localiza as duas contas, valida valor e saldo, confere espaço para 2 registros, atualiza os saldos e registra `S` (origem) e `D` (destino) |
| 7 | `exibirExtrato()` | Percorre o histórico e mostra só as movimentações da conta informada |

---

## ▶️ Como compilar e executar

```bash
g++ main.cpp -o sistema_bancario
./sistema_bancario
```

No Windows:

```bash
g++ main.cpp -o sistema_bancario.exe
sistema_bancario.exe
```

---

## 📂 Estrutura do repositório

```
.
├── main.cpp               # Código-fonte do sistema bancário
├── enunciado-etapa2.pdf   # Enunciado do trabalho
└── README.md
```
