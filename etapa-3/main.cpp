#include <iostream>
#include <string>
#include <fstream>   // ofstream e ifstream (Etapa 3 - arquivos)
#include <iomanip>   // fixed e setprecision (valores com 2 casas)
#include <limits>    // numeric_limits (limpar entrada invalida)
#include <cstdlib>   // exit

using namespace std;

// ================== ARQUIVOS DO SISTEMA ==================
const string ARQUIVO_CONTAS = "contas.txt";
const string ARQUIVO_MOVIMENTACOES = "movimentacoes.txt";

// ================== DADOS DAS CONTAS (arrays da Etapa 2) ==================
const int MAX_CONTAS = 100; // limite maximo de 100 contas
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int quantidadeContas = 0;

// ================== HISTORICO DE MOVIMENTACOES ==================
const int MAX_MOVIMENTACOES = 500;
int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];
int quantidadeMovimentacoes = 0;

// Prototipos das funcoes de arquivo (definidas mais abaixo)
void salvarContas();
void salvarMovimentacoes();

// ================== FUNCOES AUXILIARES DE LEITURA ==================

// Le um numero inteiro do teclado. Se o usuario digitar texto,
// limpa o erro do cin e pede de novo (evita loop infinito).
int lerInteiro() {
    int valor;
    while (!(cin >> valor)) {
        if (cin.eof()) { // entrada encerrada (Ctrl+D / Ctrl+Z): salva e sai
            salvarContas();
            salvarMovimentacoes();
            exit(0);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida! Digite um numero: ";
    }
    return valor;
}

// Mesma ideia, para valores em reais
double lerValor() {
    double valor;
    while (!(cin >> valor)) {
        if (cin.eof()) { // entrada encerrada (Ctrl+D / Ctrl+Z): salva e sai
            salvarContas();
            salvarMovimentacoes();
            exit(0);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida! Digite um valor: R$ ";
    }
    return valor;
}

// Le uma palavra (ex.: CPF). Se a entrada acabar, salva e sai.
string lerPalavra() {
    string texto;
    if (!(cin >> texto)) {
        salvarContas();
        salvarMovimentacoes();
        exit(0);
    }
    return texto;
}

// Le uma linha inteira (ex.: nome). Se a entrada acabar, salva e sai.
string lerLinha() {
    string texto;
    if (!getline(cin, texto)) {
        salvarContas();
        salvarMovimentacoes();
        exit(0);
    }
    return texto;
}

// Converte texto em numero sem derrubar o programa.
// Devolve false se o texto nao for um numero valido.
bool converterInteiro(const string& texto, int& resultado) {
    try {
        size_t lidos = 0;
        resultado = stoi(texto, &lidos);
        return lidos == texto.size();
    } catch (...) {
        return false;
    }
}

bool converterValor(const string& texto, double& resultado) {
    try {
        size_t lidos = 0;
        resultado = stod(texto, &lidos);
        return lidos == texto.size();
    } catch (...) {
        return false;
    }
}

// Procura a conta pelo numero e devolve o indice no array (ou -1)
int buscarConta(int num) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == num) {
            return i;
        }
    }
    return -1;
}

// ================== FUNCOES DE ARQUIVO (ETAPA 3) ==================

// Grava TODAS as contas em contas.txt.
// Abre sem ios::app, entao o conteudo antigo e substituido pelos dados atualizados.
// Formato de cada linha: numero;nome;cpf;tipo;saldo;ativa
void salvarContas() {
    ofstream arquivo(ARQUIVO_CONTAS.c_str());

    if (arquivo.is_open()) {
        arquivo << fixed << setprecision(2);
        for (int i = 0; i < quantidadeContas; i++) {
            arquivo << numeroConta[i] << ";"
                    << nomeCliente[i] << ";"
                    << cpf[i] << ";"
                    << tipoConta[i] << ";"
                    << saldo[i] << ";"
                    << contaAtiva[i] << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro: nao foi possivel gravar o arquivo " << ARQUIVO_CONTAS << "!\n";
    }
}

// Grava TODO o historico em movimentacoes.txt.
// Formato de cada linha: conta;tipo;valor
void salvarMovimentacoes() {
    ofstream arquivo(ARQUIVO_MOVIMENTACOES.c_str());

    if (arquivo.is_open()) {
        arquivo << fixed << setprecision(2);
        for (int i = 0; i < quantidadeMovimentacoes; i++) {
            arquivo << contaMovimentacao[i] << ";"
                    << tipoMovimentacao[i] << ";"
                    << valorMovimentacao[i] << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro: nao foi possivel gravar o arquivo " << ARQUIVO_MOVIMENTACOES << "!\n";
    }
}

// Le contas.txt e coloca os dados nos arrays.
// Se o arquivo nao existir (primeira execucao), o sistema comeca vazio.
void carregarContas() {
    ifstream arquivo(ARQUIVO_CONTAS.c_str());
    quantidadeContas = 0;

    if (!arquivo.is_open()) {
        return; // primeira execucao: ainda nao ha contas
    }

    string linha;
    while (getline(arquivo, linha) && quantidadeContas < MAX_CONTAS) {
        if (linha.empty()) continue; // ignora linhas em branco

        // Separa os 6 campos usando o ';' como divisor
        string campo[6];
        int qtdCampos = 0;
        string atual = "";
        for (size_t c = 0; c < linha.size(); c++) {
            if (linha[c] == ';' && qtdCampos < 5) {
                campo[qtdCampos] = atual;
                qtdCampos++;
                atual = "";
            } else if (linha[c] != '\r') { // ignora o \r de arquivos do Windows
                atual += linha[c];
            }
        }
        campo[qtdCampos] = atual;
        qtdCampos++;

        // Linha com formato errado ou numero invalido: avisa e pula, sem derrubar o programa
        int num, tipo;
        double valorSaldo;
        if (qtdCampos != 6 || !converterInteiro(campo[0], num) ||
            !converterInteiro(campo[3], tipo) || !converterValor(campo[4], valorSaldo)) {
            cout << "Aviso: linha invalida ignorada em " << ARQUIVO_CONTAS << ": " << linha << "\n";
            continue;
        }

        numeroConta[quantidadeContas] = num;
        nomeCliente[quantidadeContas] = campo[1];
        cpf[quantidadeContas] = campo[2];
        tipoConta[quantidadeContas] = tipo;
        saldo[quantidadeContas] = valorSaldo;
        contaAtiva[quantidadeContas] = (campo[5] == "1");
        quantidadeContas++;
    }

    // Avisa se o arquivo tinha mais contas do que o sistema comporta
    if (quantidadeContas == MAX_CONTAS && getline(arquivo, linha)) {
        cout << "Aviso: " << ARQUIVO_CONTAS << " tem mais de " << MAX_CONTAS
             << " contas; as excedentes foram ignoradas.\n";
    }

    arquivo.close();
}

// Le movimentacoes.txt e coloca o historico nos arrays.
void carregarMovimentacoes() {
    ifstream arquivo(ARQUIVO_MOVIMENTACOES.c_str());
    quantidadeMovimentacoes = 0;

    if (!arquivo.is_open()) {
        return; // primeira execucao: ainda nao ha movimentacoes
    }

    string linha;
    while (getline(arquivo, linha) && quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
        if (linha.empty()) continue;

        // Posicoes dos dois ';' da linha (conta;tipo;valor)
        size_t p1 = linha.find(';');
        size_t p2 = linha.find(';', p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        int conta;
        double valor;
        string textoValor = linha.substr(p2 + 1);
        if (!textoValor.empty() && textoValor[textoValor.size() - 1] == '\r') {
            textoValor.erase(textoValor.size() - 1); // \r de arquivos do Windows
        }
        if (!converterInteiro(linha.substr(0, p1), conta) || !converterValor(textoValor, valor)) {
            cout << "Aviso: linha invalida ignorada em " << ARQUIVO_MOVIMENTACOES << ": " << linha << "\n";
            continue;
        }

        contaMovimentacao[quantidadeMovimentacoes] = conta;
        tipoMovimentacao[quantidadeMovimentacoes] = linha[p1 + 1];
        valorMovimentacao[quantidadeMovimentacoes] = valor;
        quantidadeMovimentacoes++;
    }

    if (quantidadeMovimentacoes == MAX_MOVIMENTACOES && getline(arquivo, linha)) {
        cout << "Aviso: " << ARQUIVO_MOVIMENTACOES << " tem mais de " << MAX_MOVIMENTACOES
             << " movimentacoes; as excedentes foram ignoradas.\n";
    }

    arquivo.close();
}

// Registra uma movimentacao no historico (arrays).
// Devolve false se o historico estiver cheio.
bool registrarMovimentacao(int conta, char tipo, double valor) {
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
        return false;
    }
    contaMovimentacao[quantidadeMovimentacoes] = conta;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;
    quantidadeMovimentacoes++;
    return true;
}

// ================== OPERACOES DO MENU ==================

void cadastrarConta() {
    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Erro: Limite maximo de contas atingido!\n";
        return;
    }

    cout << "\n--- CADASTRAR CONTA ---\n";
    cout << "Numero da conta: ";
    int num = lerInteiro();

    if (num <= 0) {
        cout << "Erro: o numero da conta deve ser maior que zero!\n";
        return;
    }
    // Verifica se ja existe uma conta com esse numero
    if (buscarConta(num) != -1) {
        cout << "Erro: ja existe uma conta com esse numero!\n";
        return;
    }

    string nome;
    cout << "Nome do cliente: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    nome = lerLinha();
    // O ';' e o separador do arquivo, entao nao pode aparecer no nome
    while (nome.empty() || nome.find(';') != string::npos) {
        cout << "Nome invalido (nao pode ser vazio nem conter ';'). Digite novamente: ";
        nome = lerLinha();
    }

    string cpfDigitado;
    cout << "CPF: ";
    cpfDigitado = lerPalavra();
    while (cpfDigitado.find(';') != string::npos) {
        cout << "CPF invalido (nao pode conter ';'). Digite novamente: ";
        cpfDigitado = lerPalavra();
    }

    cout << "Tipo de conta (1-Corrente, 2-Poupanca): ";
    int tipo = lerInteiro();
    while (tipo != 1 && tipo != 2) {
        cout << "Tipo invalido! Digite 1 (Corrente) ou 2 (Poupanca): ";
        tipo = lerInteiro();
    }

    numeroConta[quantidadeContas] = num;
    nomeCliente[quantidadeContas] = nome;
    cpf[quantidadeContas] = cpfDigitado;
    tipoConta[quantidadeContas] = tipo;
    saldo[quantidadeContas] = 0.0;
    contaAtiva[quantidadeContas] = true;
    quantidadeContas++;

    salvarContas(); // grava a nova conta no arquivo

    cout << "Conta cadastrada com sucesso!\n";
}

void listarContas() {
    cout << "\n--- LISTA DE CONTAS ---\n";
    bool temConta = false;
    for (int i = 0; i < quantidadeContas; i++) {
        if (contaAtiva[i]) {
            cout << "Conta: " << numeroConta[i]
                 << " | Cliente: " << nomeCliente[i]
                 << " | Saldo: R$ " << saldo[i] << endl;
            temConta = true;
        }
    }
    if (!temConta) {
        cout << "Nenhuma conta cadastrada.\n";
    }
}

void consultarConta() {
    cout << "\nDigite o numero da conta: ";
    int num = lerInteiro();

    int i = buscarConta(num);
    if (i != -1 && contaAtiva[i]) {
        cout << "Cliente: " << nomeCliente[i] << endl;
        cout << "CPF: " << cpf[i] << endl;
        cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << endl;
        cout << "Saldo atual: R$ " << saldo[i] << endl;
    } else {
        cout << "Conta nao encontrada ou inativa.\n";
    }
}

void depositar() {
    cout << "\nNumero da conta para deposito: ";
    int num = lerInteiro();

    int i = buscarConta(num);
    if (i == -1 || !contaAtiva[i]) {
        cout << "Conta nao encontrada!\n";
        return;
    }

    cout << "Valor do deposito: R$ ";
    double valor = lerValor();
    if (valor <= 0) {
        cout << "Valor invalido!\n";
        return;
    }

    // So altera o saldo se conseguir registrar no historico
    if (registrarMovimentacao(numeroConta[i], 'D', valor)) { // D = Deposito
        saldo[i] = saldo[i] + valor;
        salvarContas();         // grava o saldo novo
        salvarMovimentacoes();  // grava o historico
        cout << "Deposito realizado com sucesso!\n";
    } else {
        cout << "Historico de movimentacoes cheio!\n";
    }
}

void sacar() {
    cout << "\nNumero da conta para saque: ";
    int num = lerInteiro();

    int i = buscarConta(num);
    if (i == -1 || !contaAtiva[i]) {
        cout << "Conta nao encontrada!\n";
        return;
    }

    cout << "Valor do saque: R$ ";
    double valor = lerValor();
    if (valor <= 0 || saldo[i] < valor) {
        cout << "Saldo insuficiente ou valor invalido!\n";
        return;
    }

    if (registrarMovimentacao(numeroConta[i], 'S', valor)) { // S = Saque
        saldo[i] = saldo[i] - valor;
        salvarContas();
        salvarMovimentacoes();
        cout << "Saque realizado com sucesso!\n";
    } else {
        cout << "Historico de movimentacoes cheio!\n";
    }
}

void transferir() {
    cout << "\nNumero da conta de ORIGEM: ";
    int numOrigem = lerInteiro();
    cout << "Numero da conta de DESTINO: ";
    int numDestino = lerInteiro();

    if (numOrigem == numDestino) {
        cout << "Erro: a conta de origem e a de destino devem ser diferentes!\n";
        return;
    }

    // Procura os indices das duas contas
    int indiceOrigem = buscarConta(numOrigem);
    int indiceDestino = buscarConta(numDestino);

    if (indiceOrigem == -1 || indiceDestino == -1 ||
        !contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
        cout << "Uma ou ambas as contas nao foram encontradas!\n";
        return;
    }

    cout << "Valor da transferencia: R$ ";
    double valor = lerValor();

    if (valor <= 0 || saldo[indiceOrigem] < valor) {
        cout << "Saldo insuficiente na conta de origem ou valor invalido!\n";
        return;
    }

    // Verifica se ha espaco para os DOIS registros de movimentacao
    if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
        cout << "Sem espaco no historico para registrar a transferencia!\n";
        return;
    }

    saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
    saldo[indiceDestino] = saldo[indiceDestino] + valor;

    registrarMovimentacao(numeroConta[indiceOrigem], 'S', valor);  // saida na origem
    registrarMovimentacao(numeroConta[indiceDestino], 'D', valor); // entrada no destino

    salvarContas();         // grava os dois saldos atualizados
    salvarMovimentacoes();  // grava os dois registros

    cout << "Transferencia concluida com sucesso!\n";
}

void exibirExtrato() {
    cout << "\nNumero da conta para extrato: ";
    int num = lerInteiro();

    int indice = buscarConta(num);
    if (indice == -1) {
        cout << "Conta nao encontrada!\n";
        return;
    }

    cout << "\n--- EXTRATO DA CONTA " << num << " (" << nomeCliente[indice] << ") ---\n";
    bool teveMovimentacao = false;

    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        if (contaMovimentacao[i] == num) { // filtra so a conta pedida
            teveMovimentacao = true;
            if (tipoMovimentacao[i] == 'D') {
                cout << "Deposito/Entrada: + R$ " << valorMovimentacao[i] << endl;
            } else if (tipoMovimentacao[i] == 'S') {
                cout << "Saque/Saida:      - R$ " << valorMovimentacao[i] << endl;
            }
        }
    }

    if (!teveMovimentacao) {
        cout << "Nenhuma movimentacao registrada nesta conta.\n";
    }
    cout << "Saldo atual: R$ " << saldo[indice] << endl;
}

int main() {
    cout << fixed << setprecision(2); // mostra os valores com 2 casas decimais

    // Ao iniciar, recupera os dados salvos nas execucoes anteriores
    carregarContas();
    carregarMovimentacoes();
    cout << "Dados carregados: " << quantidadeContas << " conta(s) e "
         << quantidadeMovimentacoes << " movimentacao(oes).\n";

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
            case 0:
                // Garante que tudo esta gravado antes de sair
                salvarContas();
                salvarMovimentacoes();
                cout << "Dados salvos. Encerrando o sistema...\n";
                break;
            default: cout << "Opcao invalida! Tente novamente.\n";
        }
    } while (opcao != 0);

    return 0;
}
