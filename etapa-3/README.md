# Banco INF101 — Etapa 3

**Centro Universitário de Viçosa (UNIVIÇOSA)**
**Disciplina:** INF101 — Programação de Computadores I
**Professores:** Anderson R. Lamas e Vanderlea Queiroz
**Aluno:** Maurílio Pereira Santana Oliveira Nunes
**Curso:** Engenharia de Computação

Trabalho: *Implementação de um Sistema de Registro e Gestão de Contas Bancárias (Etapa 3)*, em C++.

---

## 📌 Informações da entrega

| Item | Detalhe |
|---|---|
| Valor | 7 pontos |
| Data | 25/11/2026 |
| Formato | Código organizado no GitHub e link compartilhado na planilha do professor |
| Apresentação | Não é necessária: o professor avalia o código pelo link do GitHub |

O enunciado completo está em [`enunciado-etapa3.pdf`](enunciado-etapa3.pdf).

---

## 📝 O que foi pedido

Até a Etapa 2, contas, saldos e histórico ficavam **só na memória** (arrays) e eram perdidos ao fechar o programa. Na Etapa 3 o sistema passa a **salvar os dados em arquivos de texto** e a **recuperá-los automaticamente** na próxima execução, usando a biblioteca `fstream`:

| Recurso | Uso no programa |
|---|---|
| `ofstream` | Gravar `contas.txt` e `movimentacoes.txt` |
| `ifstream` | Ler os arquivos ao iniciar |
| `is_open()` | Verificar se o arquivo abriu (se não existe, é a primeira execução) |
| `getline()` | Ler cada linha (um registro) do arquivo |
| `close()` | Fechar os arquivos após a leitura/gravação |

> `ios::app` não foi necessário: como o enunciado sugere (itens 2.3 e 2.4), a cada alteração o programa percorre os arrays e **regrava o arquivo inteiro** com os dados atualizados. Por isso o `ofstream` é aberto sem `ios::app`, substituindo o conteúdo antigo — e nenhuma movimentação se perde, porque todas as anteriores já foram carregadas nos arrays no início.

---

## 📂 Arquivos do sistema

Os dois arquivos são criados na **mesma pasta onde o programa é executado**. Os campos são separados por ponto e vírgula (`;`).

### `contas.txt` — uma conta por linha

```
numero;nome;cpf;tipo;saldo;ativa
```

```
1001;Ana Silva;12345678900;1;700.00;1
1002;Bruno Souza;98765432100;2;800.00;1
1003;Carlos Lima;11122233344;1;1300.00;1
```

- `tipo`: 1 = Corrente, 2 = Poupança
- `ativa`: 1 = ativa, 0 = inativa

### `movimentacoes.txt` — uma movimentação por linha

```
conta;tipo;valor
```

```
1001;D;1000.00
1002;D;500.00
1003;D;1500.00
1003;S;200.00
1001;S;300.00
1002;D;300.00
```

| Código | Movimentação |
|:---:|---|
| `D` | Depósito (ou entrada de transferência) |
| `S` | Saque (ou saída de transferência) |

Uma **transferência** gera dois registros: `S` na conta de origem e `D` na conta de destino (as duas últimas linhas acima são a transferência de R$ 300,00 da Ana para o Bruno, igual ao exemplo do item 2.5).

---

## 💻 Como foi implementado

O código parte da Etapa 2 (mesmos arrays globais e mesmas funções do menu) e acrescenta as **funções próprias de arquivo** sugeridas no item 2.7:

| Função | O que faz |
|---|---|
| `carregarContas()` | Abre `contas.txt` com `ifstream`; se não abrir, é a primeira execução e o sistema começa vazio. Lê cada linha com `getline()`, separa os 6 campos pelo `;`, preenche os arrays e atualiza `quantidadeContas` |
| `carregarMovimentacoes()` | Mesmo processo para `movimentacoes.txt`, atualizando `quantidadeMovimentacoes` |
| `salvarContas()` | Percorre os arrays e regrava `contas.txt` com todas as contas (saldo com 2 casas decimais) |
| `salvarMovimentacoes()` | Percorre o histórico e regrava `movimentacoes.txt` |

### Quando os dados são salvos

| Operação | `salvarContas()` | `salvarMovimentacoes()` |
|---|:---:|:---:|
| Cadastrar conta | ✅ | — |
| Depósito | ✅ | ✅ |
| Saque | ✅ | ✅ |
| Transferência | ✅ (os dois saldos) | ✅ (os dois registros) |
| Sair (opção 0) | ✅ | ✅ |

O salvamento acontece **logo após cada operação**, não só ao sair. Assim, mesmo que o programa seja fechado pelo "X" da janela, nada se perde.

### Fluxo do programa

```
main()
 ├── carregarContas()          ← recupera as contas salvas
 ├── carregarMovimentacoes()   ← recupera o histórico salvo
 └── menu (do-while + switch)
      ├── 1 cadastrarConta()   → salvarContas()
      ├── 2 listarContas()
      ├── 3 consultarConta()
      ├── 4 depositar()        → salvarContas() + salvarMovimentacoes()
      ├── 5 sacar()            → salvarContas() + salvarMovimentacoes()
      ├── 6 transferir()       → salvarContas() + salvarMovimentacoes()
      ├── 7 exibirExtrato()
      └── 0 sair               → salvarContas() + salvarMovimentacoes()
```

### Outras melhorias em relação à Etapa 2

- **Funções auxiliares** `buscarConta()` (devolve o índice da conta ou -1) e `registrarMovimentacao()`, eliminando código repetido nas operações.
- **Validação de entradas numéricas** (`lerInteiro()` e `lerValor()`): se o usuário digitar texto onde se espera número, o programa limpa o erro do `cin` e pede de novo, em vez de entrar em loop infinito.
- **Nome e CPF não podem conter `;`**, já que esse é o separador dos campos no arquivo (um `;` no nome quebraria a leitura na próxima execução).
- Tipo da conta só aceita 1 ou 2; número da conta deve ser maior que zero e não pode se repetir.
- Transferência não permite origem e destino iguais.
- Valores exibidos e gravados com 2 casas decimais (`fixed` + `setprecision(2)`).
- O extrato mostra o nome do titular e o saldo atual ao final.

---

## 🧪 Testes realizados (item 2.8)

| Teste | Passos | Resultado |
|---|---|---|
| **1 – Cadastro e recuperação** | Cadastrar 1001 (Ana), 1002 (Bruno) e 1003 (Carlos), sair, executar de novo e listar | ✅ Ao abrir: `Dados carregados: 3 conta(s)...`; as três contas aparecem com todos os dados |
| **2 – Persistência dos saldos** | Depositar na 1003 e sacar R$ 200,00 dela; depositar na 1002; sair e reabrir | ✅ Saldos mantidos (1003 = R$ 1.300,00) |
| **3 – Persistência das transferências** | Ana (R$ 1.000,00) transfere R$ 300,00 para Bruno (R$ 500,00); sair e reabrir | ✅ Ana R$ 700,00 / Bruno R$ 800,00; extrato da Ana mostra a saída e o do Bruno a entrada |
| **4 – Histórico de movimentações** | Novos depósitos, saques e transferências em outra execução; sair e reabrir; extrato da 1001 | ✅ Extrato mostra as movimentações de **todas** as execuções anteriores |

Exemplo da segunda execução (após o Teste 3):

```
Dados carregados: 3 conta(s) e 6 movimentacao(oes).

--- LISTA DE CONTAS ---
Conta: 1001 | Cliente: Ana Silva | Saldo: R$ 700.00
Conta: 1002 | Cliente: Bruno Souza | Saldo: R$ 800.00
Conta: 1003 | Cliente: Carlos Lima | Saldo: R$ 1300.00

--- EXTRATO DA CONTA 1001 (Ana Silva) ---
Deposito/Entrada: + R$ 1000.00
Saque/Saida:      - R$ 300.00
Saldo atual: R$ 700.00

--- EXTRATO DA CONTA 1002 (Bruno Souza) ---
Deposito/Entrada: + R$ 500.00
Deposito/Entrada: + R$ 300.00
Saldo atual: R$ 800.00
```

---

## ▶️ Como compilar e executar

```bash
cd etapa-3
g++ main.cpp -o sistema_bancario
./sistema_bancario
```

No Windows:

```bash
cd etapa-3
g++ main.cpp -o sistema_bancario.exe
sistema_bancario.exe
```

> Se o compilador for antigo, use `g++ -std=c++11 main.cpp -o sistema_bancario` (o programa usa `stoi` e `stod`, do C++11).

Na primeira execução não existem arquivos e o sistema começa vazio. Após cadastrar contas ou fazer movimentações, `contas.txt` e `movimentacoes.txt` aparecem na pasta. Para recomeçar do zero, basta apagar os dois arquivos.

---

## 📂 Estrutura da pasta

```
etapa-3/
├── main.cpp               # Código-fonte do sistema bancário com persistência
├── enunciado-etapa3.pdf   # Enunciado do trabalho
└── README.md
```
