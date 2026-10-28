#include <iostream>
#include <string>

using namespace std;

// Arrays globais para facilitar o acesso nas funções (típico de 2º período)
const int MAX_CONTAS = 100; // limite máximo de 100 contas[cite: 2]
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int quantidadeContas = 0;

const int MAX_MOVIMENTACOES = 500;
int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];
int quantidadeMovimentacoes = 0;

void cadastrarConta() {
    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Erro: Limite maximo de contas atingido!\n";
        return;
    }
    
    cout << "\n--- CADASTRAR CONTA ---\n";
    cout << "Numero da conta: ";
    cin >> numeroConta[quantidadeContas];
    
    cout << "Nome do cliente: ";
    cin.ignore();
    getline(cin, nomeCliente[quantidadeContas]);
    
    cout << "CPF: ";
    cin >> cpf[quantidadeContas];
    
    cout << "Tipo de conta (1-Corrente, 2-Poupanca): ";
    cin >> tipoConta[quantidadeContas];

    saldo[quantidadeContas] = 0.0;
    contaAtiva[quantidadeContas] = true;
    quantidadeContas++;
    
    cout << "Conta cadastrada com sucesso!\n";
}

void listarContas() {
    cout << "\n--- LISTA DE CONTAS ---\n";
    for (int i = 0; i < quantidadeContas; i++) {
        if (contaAtiva[i]) {
            cout << "Conta: " << numeroConta[i] 
                 << " | Cliente: " << nomeCliente[i] 
                 << " | Saldo: R$ " << saldo[i] << endl;
        }
    }
}

void consultarConta() {
    int num;
    cout << "\nDigite o numero da conta: ";
    cin >> num;
    
    bool achou = false;
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == num && contaAtiva[i]) {
            cout << "Cliente: " << nomeCliente[i] << endl;
            cout << "CPF: " << cpf[i] << endl;
            cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << endl;
            cout << "Saldo atual: R$ " << saldo[i] << endl;
            achou = true;
            break;
        }
    }
    if (!achou) {
        cout << "Conta nao encontrada ou inativa.\n";
    }
}

void depositar() {
    int num;
    double valor;
    cout << "\nNumero da conta para deposito: ";
    cin >> num;
    
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == num && contaAtiva[i]) {
            cout << "Valor do deposito: R$ ";
            cin >> valor;
            if (valor > 0) {
                saldo[i] = saldo[i] + valor; // Atualiza o saldo[cite: 2]
                
                // Registar a movimentacao
                if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D'; // D = Deposito[cite: 2]
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;
                    cout << "Deposito realizado com sucesso!\n";
                } else {
                    cout << "Historico de movimentacoes cheio!\n";
                }
            } else {
                cout << "Valor invalido!\n";
            }
            return;
        }
    }
    cout << "Conta nao encontrada!\n";
}

void sacar() {
    int num;
    double valor;
    cout << "\nNumero da conta para saque: ";
    cin >> num;
    
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == num && contaAtiva[i]) {
            cout << "Valor do saque: R$ ";
            cin >> valor;
            if (valor > 0 && saldo[i] >= valor) {
                saldo[i] = saldo[i] - valor;
                
                if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S'; // S = Saque[cite: 2]
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;
                    cout << "Saque realizado com sucesso!\n";
                }
            } else {
                cout << "Saldo insuficiente ou valor invalido!\n";
            }
            return;
        }
    }
    cout << "Conta nao encontrada!\n";
}

void transferir() {
    int numOrigem, numDestino;
    double valor;
    
    cout << "\nNumero da conta de ORIGEM: ";
    cin >> numOrigem;
    cout << "Numero da conta de DESTINO: ";
    cin >> numDestino;

    int indiceOrigem = -1;
    int indiceDestino = -1;

    // Procura os indices das duas contas
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numOrigem && contaAtiva[i]) indiceOrigem = i;
        if (numeroConta[i] == numDestino && contaAtiva[i]) indiceDestino = i;
    }

    if (indiceOrigem != -1 && indiceDestino != -1) {
        cout << "Valor da transferencia: R$ ";
        cin >> valor;
        
        if (valor > 0 && saldo[indiceOrigem] >= valor) {
            // Verifica se ha espaco para os DOIS registos de movimentacao[cite: 3]
            if (quantidadeMovimentacoes + 1 < MAX_MOVIMENTACOES) {
                
                saldo[indiceOrigem] = saldo[indiceOrigem] - valor;[cite: 3]
                saldo[indiceDestino] = saldo[indiceDestino] + valor;[cite: 3]

                // Registo da saida (Conta Origem)[cite: 3]
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                // Registo da entrada (Conta Destino)[cite: 3]
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                cout << "Transferencia concluida com sucesso!\n";
            } else {
                cout << "Sem espaco no historico para registrar a transferencia!\n";
            }
        } else {
            cout << "Saldo insuficiente na conta de origem ou valor invalido!\n";
        }
    } else {
        cout << "Uma ou ambas as contas nao foram encontradas!\n";
    }
}

void exibirExtrato() {
    int num;
    cout << "\nNumero da conta para extrato: ";
    cin >> num;
    
    cout << "\n--- EXTRATO DA CONTA " << num << " ---\n";
    bool teveMovimentacao = false;
    
    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        if (contaMovimentacao[i] == num) { // filtra so a conta pedida[cite: 4]
            teveMovimentacao = true;
            if (tipoMovimentacao[i] == 'D') { //[cite: 4]
                cout << "Deposito: R$ " << valorMovimentacao[i] << endl; //[cite: 4]
            } else if (tipoMovimentacao[i] == 'S') { //[cite: 4]
                cout << "Saque/Transf: R$ " << valorMovimentacao[i] << endl; //[cite: 4]
            }
        }
    }
    
    if (!teveMovimentacao) {
        cout << "Nenhuma movimentacao registrada nesta conta.\n";
    }
}

int main() {
    int opcao;
    
    do {
        cout << "\n========== SISTEMA BANCARIO ==========\n";
        cout << "1. Cadastrar conta\n";
        cout << "2. Listar contas\n";
        cout << "3. Consultar conta\n";
        cout << "4. Realizar deposito\n";
        cout << "5. Realizar saque\n";
        cout << "6. Realizar transferencia\n";
        cout << "7. Exibir extrato\n";
        cout << "0. Sair\n";
        cout << "======================================\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: listarContas(); break;
            case 3: consultarConta(); break;
            case 4: depositar(); break;
            case 5: sacar(); break;
            case 6: transferir(); break;
            case 7: exibirExtrato(); break;
            case 0: cout << "Encerrando o sistema...\n"; break;
            default: cout << "Opcao invalida! Tente novamente.\n";
        }
    } while (opcao != 0);

    return 0;
}