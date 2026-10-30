#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Arrays globais para facilitar o acesso nas funções (típico de 2º período)
const int MAX_CONTAS = 100; // limite máximo de 100 contas
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

// Le um numero inteiro; se o usuario digitar texto, limpa o erro e pede de novo
int lerInteiro() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida! Digite um numero: ";
    }
    return x;
}

// Le um valor em reais; se o usuario digitar texto, limpa o erro e pede de novo
double lerValor() {
    double x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida! Digite um valor: R$ ";
    }
    return x;
}

void cadastrarConta() {
    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Erro: Limite maximo de contas atingido!\n";
        return;
    }
    
    cout << "\n--- CADASTRAR CONTA ---\n";
    int num;
    cout << "Numero da conta: ";
    num = lerInteiro();

    // Verifica se ja existe uma conta com esse numero
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == num) {
            cout << "Erro: ja existe uma conta com esse numero!\n";
            return;
        }
    }
    numeroConta[quantidadeContas] = num;
    
    cout << "Nome do cliente: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nomeCliente[quantidadeContas]);
    
    cout << "CPF: ";
    cin >> cpf[quantidadeContas];
    
    cout << "Tipo de conta (1-Corrente, 2-Poupanca): ";
    tipoConta[quantidadeContas] = lerInteiro();
    while (tipoConta[quantidadeContas] != 1 && tipoConta[quantidadeContas] != 2) {
        cout << "Tipo invalido! Digite 1 (Corrente) ou 2 (Poupanca): ";
        tipoConta[quantidadeContas] = lerInteiro();
    }

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
    num = lerInteiro();
    
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
    num = lerInteiro();
    
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == num && contaAtiva[i]) {
            cout << "Valor do deposito: R$ ";
            valor = lerValor();
            if (valor > 0) {
                saldo[i] = saldo[i] + valor; // Atualiza o saldo
                
                // Registar a movimentacao
                if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D'; // D = Deposito
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
    num = lerInteiro();
    
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == num && contaAtiva[i]) {
            cout << "Valor do saque: R$ ";
            valor = lerValor();
            if (valor > 0 && saldo[i] >= valor) {
                saldo[i] = saldo[i] - valor;
                
                if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S'; // S = Saque
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;
                    cout << "Saque realizado com sucesso!\n";
                } else {
                    cout << "Historico de movimentacoes cheio!\n";
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
    numOrigem = lerInteiro();
    cout << "Numero da conta de DESTINO: ";
    numDestino = lerInteiro();

    if (numOrigem == numDestino) {
        cout << "Erro: a conta de origem e a de destino sao a mesma!\n";
        return;
    }

    int indiceOrigem = -1;
    int indiceDestino = -1;

    // Procura os indices das duas contas
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numOrigem && contaAtiva[i]) indiceOrigem = i;
        if (numeroConta[i] == numDestino && contaAtiva[i]) indiceDestino = i;
    }

    if (indiceOrigem != -1 && indiceDestino != -1) {
        cout << "Valor da transferencia: R$ ";
        valor = lerValor();
        
        if (valor > 0 && saldo[indiceOrigem] >= valor) {
            // Verifica se ha espaco para os DOIS registos de movimentacao
            if (quantidadeMovimentacoes + 1 < MAX_MOVIMENTACOES) {
                
                saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
                saldo[indiceDestino] = saldo[indiceDestino] + valor;

                // Registo da saida (Conta Origem)
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                // Registo da entrada (Conta Destino)
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
    num = lerInteiro();
    
    cout << "\n--- EXTRATO DA CONTA " << num << " ---\n";
    bool teveMovimentacao = false;
    
    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        if (contaMovimentacao[i] == num) { // filtra so a conta pedida
            teveMovimentacao = true;
            if (tipoMovimentacao[i] == 'D') { //
                cout << "Deposito: R$ " << valorMovimentacao[i] << endl; //
            } else if (tipoMovimentacao[i] == 'S') { //
                cout << "Saque/Transf: R$ " << valorMovimentacao[i] << endl; //
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
        opcao = lerInteiro();

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