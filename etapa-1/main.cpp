/*
 * BANCO INF101 - Etapa 1
 *
 * Versao principal: cadastro de UMA conta utilizando somente variaveis
 * individuais, conforme o item 3 do enunciado.
 *
 * A versao com cadastro de ate 5 contas (desafio do item 3.5), que utiliza
 * arrays, esta no arquivo desafio_5_contas.cpp.
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

int main() {
    // Variaveis obrigatorias (item 3.1 do enunciado)
    int numeroConta = 0;       // Numero da conta
    string nomeCliente;        // Nome do titular
    string cpf;                // CPF do titular
    int tipoConta = 0;         // 1 = Corrente; 2 = Poupanca
    double saldo = 0.0;        // Saldo atual
    bool contaAtiva = false;   // Indica se a conta esta ativa

    // Variaveis adicionais (desafio do item 3.5)
    string senha;                   // Senha definida no cadastro
    double limiteCredito = 0.0;     // Limite de credito (R$ 500,00 para conta corrente)
    bool contaCadastrada = false;   // Indica se ja existe uma conta cadastrada

    int opcao;       // Opcao escolhida no menu
    bool valido;     // Controla a repeticao das leituras ate que a entrada seja valida

    cout << fixed << setprecision(2);

    do {
        cout << "\n========================================\n";
        cout << "           BANCO INF101                 \n";
        cout << "========================================\n";
        cout << " 1 - Cadastrar conta\n";
        cout << " 2 - Consultar conta\n";
        cout << " 3 - Verificar saldo\n";
        cout << " 4 - Alterar tipo da conta\n";
        cout << " 5 - Ativar/Desativar conta\n";
        cout << " 6 - Sair\n";
        cout << "========================================\n";
        cout << "Escolha uma opcao: ";

        // Se o usuario digitar algo que nao e numero, limpa o erro do cin
        // e descarta o restante da linha, evitando que o programa trave
        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = 0;
        }

        switch (opcao) {
            case 1:
                // Com variaveis individuais, o sistema comporta apenas uma conta
                if (contaCadastrada) {
                    cout << "\n[AVISO] Ja existe uma conta cadastrada (numero " << numeroConta << ").\n";
                    cout << "        Esta versao do sistema permite apenas uma conta.\n";
                    break;
                }

                cout << "\n>>> INICIANDO NOVO CADASTRO <<<\n";

                // Leitura do numero da conta: deve ser numerico e maior que zero
                do {
                    cout << "Digite o numero da conta (maior que zero): ";
                    valido = (cin >> numeroConta) && numeroConta > 0;

                    if (!valido) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Valor invalido. Tente novamente.\n";
                    }
                } while (!valido);

                // Descarta o restante da linha antes de usar getline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Digite o nome completo do titular: ";
                getline(cin, nomeCliente);

                cout << "Digite o CPF (apenas numeros): ";
                getline(cin, cpf);

                cout << "Crie uma senha para a conta: ";
                getline(cin, senha);

                // Leitura do tipo da conta: deve ser 1 ou 2
                do {
                    cout << "Selecione o tipo (1 = Corrente | 2 = Poupanca): ";
                    valido = (cin >> tipoConta) && (tipoConta == 1 || tipoConta == 2);

                    if (!valido) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Tipo invalido. Escolha 1 ou 2.\n";
                    }
                } while (!valido);

                // Leitura do saldo inicial: deve ser numerico e nao negativo
                do {
                    cout << "Digite o saldo inicial (R$): ";
                    valido = (cin >> saldo) && saldo >= 0;

                    if (!valido) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Valor invalido. O saldo deve ser um numero nao negativo.\n";
                    }
                } while (!valido);

                // Conta corrente recebe limite de credito; poupanca nao
                limiteCredito = (tipoConta == 1) ? 500.00 : 0.0;

                contaAtiva = true;
                contaCadastrada = true;

                cout << "\n[SUCESSO] Conta numero " << numeroConta << " cadastrada e ativada!\n";
                break;

            case 2:
                if (!contaCadastrada) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else {
                    cout << "\n>>> DADOS DA CONTA <<<\n";
                    cout << " Titular.....: " << nomeCliente << "\n";
                    cout << " CPF.........: " << cpf << "\n";
                    cout << " Conta.......: " << numeroConta << "\n";
                    cout << " Tipo........: " << (tipoConta == 1 ? "Corrente" : "Poupanca") << "\n";
                    cout << " Status......: " << (contaAtiva ? "ATIVA" : "INATIVA") << "\n";
                    if (tipoConta == 1) {
                        cout << " Limite Extra: R$ " << limiteCredito << "\n";
                    }
                }
                break;

            case 3:
                if (!contaCadastrada) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else if (!contaAtiva) {
                    // Operacao depende de conta ativa
                    cout << "\n[BLOQUEIO] Conta inativa. Reative a conta para ver o saldo.\n";
                } else {
                    cout << "\n>>> SALDO DISPONIVEL <<<\n";
                    cout << " Saldo Atual: R$ " << saldo << "\n";
                    if (tipoConta == 1) {
                        cout << " Limite.....: R$ " << limiteCredito << "\n";
                        cout << " Total Livre: R$ " << (saldo + limiteCredito) << "\n";
                    }
                }
                break;

            case 4:
                if (!contaCadastrada) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else if (!contaAtiva) {
                    // Operacao depende de conta ativa
                    cout << "\n[BLOQUEIO] Operacao negada. A conta encontra-se inativa.\n";
                } else {
                    cout << "\nO tipo atual e: " << (tipoConta == 1 ? "Corrente" : "Poupanca") << "\n";

                    // Le o novo tipo em uma variavel auxiliar para nao alterar
                    // o tipo da conta caso a entrada seja invalida
                    int novoTipo;
                    do {
                        cout << "Para qual tipo deseja mudar? (1 = Corrente | 2 = Poupanca): ";
                        valido = (cin >> novoTipo) && (novoTipo == 1 || novoTipo == 2);

                        if (!valido) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "  -> Tipo invalido. Escolha 1 ou 2.\n";
                        }
                    } while (!valido);

                    tipoConta = novoTipo;
                    limiteCredito = (tipoConta == 1) ? 500.00 : 0.0;
                    cout << "\n[SUCESSO] O tipo da conta foi atualizado.\n";
                }
                break;

            case 5:
                if (!contaCadastrada) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else {
                    contaAtiva = !contaAtiva; // Inverte a situacao atual da conta
                    cout << "\n[ATUALIZACAO] A conta foi " << (contaAtiva ? "ATIVADA" : "DESATIVADA") << " com sucesso.\n";
                }
                break;

            case 6:
                // Nesta etapa os dados ficam apenas em memoria (persistencia sera vista na Etapa 3)
                cout << "\nEncerrando o sistema BANCO INF101. Ate logo!\n";
                break;

            default:
                cout << "\n[ERRO] Opcao invalida. Escolha um numero de 1 a 6.\n";
        }
    } while (opcao != 6);

    return 0;
}
