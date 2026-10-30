/*
 * BANCO INF101 - Etapa 1 - DESAFIO (item 3.5 do enunciado)
 *
 * Versao com cadastro de ate 5 contas.
 * Com variaveis individuais seria necessario repetir cada variavel e cada
 * trecho de codigo 5 vezes (numeroConta1, numeroConta2, ..., numeroConta5).
 * A solucao adotada utiliza arrays paralelos: cada informacao da conta fica
 * em um vetor de 5 posicoes, e o mesmo indice identifica a mesma conta em
 * todos os vetores.
 *
 * A versao principal da Etapa 1, com uma unica conta e somente variaveis
 * individuais, esta no arquivo main.cpp.
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

int main() {
    const int MAX_CONTAS = 5; // Define o limite máximo de contas sugerido no desafio
    
    // Arrays para armazenar até 5 contas simultaneamente
    // O mesmo índice identifica a mesma conta em todos os arrays (arrays paralelos)
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS]; 
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];
    string senha[MAX_CONTAS];          // Variável adicional (desafio 3.5)
    double limiteCredito[MAX_CONTAS];  // Variável adicional (desafio 3.5)
    
    // Variável para rastrear quantas contas foram cadastradas até o momento
    int totalContas = 0; 
    int opcao;

    cout << fixed << setprecision(2);

    do {
        cout << "\n========================================\n";
        cout << "           BANCO INF101                 \n";
        cout << "========================================\n";
        cout << " 1 - Cadastrar nova conta (" << totalContas << "/" << MAX_CONTAS << ")\n";
        cout << " 2 - Consultar dados de uma conta\n";
        cout << " 3 - Verificar saldo disponivel\n";
        cout << " 4 - Alterar tipo de uma conta\n";
        cout << " 5 - Ativar/Desativar uma conta\n";
        cout << " 6 - Encerrar o sistema\n";
        cout << "========================================\n";
        cout << "Escolha uma opcao: ";
        
        // Se o usuário digitar algo que não é número, limpa o erro do cin
        // e descarta o restante da linha, evitando que o programa trave
        if (!(cin >> opcao)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            opcao = 0; 
        }

        switch(opcao) {
            case 1: {
                if (totalContas >= MAX_CONTAS) {
                    cout << "\n[ERRO] O sistema atingiu o limite maximo de " << MAX_CONTAS << " contas.\n";
                    break;
                }
                
                cout << "\n>>> INICIANDO NOVO CADASTRO <<<\n";
                
                bool valido; // Controla a repetição das leituras até que a entrada seja válida
                
                // Leitura do número da conta: deve ser numérico, maior que zero e não repetido
                do {
                    cout << "Digite o numero da conta (maior que zero): ";
                    valido = (cin >> numeroConta[totalContas]) && numeroConta[totalContas] > 0;
                    
                    if (!valido) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Valor invalido. Tente novamente.\n";
                    } else {
                        // Verifica se já existe uma conta cadastrada com o mesmo número
                        for (int i = 0; i < totalContas; i++) {
                            if (numeroConta[i] == numeroConta[totalContas]) {
                                cout << "  -> Ja existe uma conta com esse numero. Escolha outro.\n";
                                valido = false;
                                break;
                            }
                        }
                    }
                } while (!valido);
                
                // Descarta o restante da linha antes de usar getline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Digite o nome completo do titular: ";
                getline(cin, nomeCliente[totalContas]);
                
                cout << "Digite o CPF (apenas numeros): ";
                getline(cin, cpf[totalContas]);

                cout << "Crie uma senha para a conta: ";
                getline(cin, senha[totalContas]);
                
                // Leitura do tipo da conta: deve ser 1 ou 2
                do {
                    cout << "Selecione o tipo (1 = Corrente | 2 = Poupanca): ";
                    valido = (cin >> tipoConta[totalContas]) &&
                             (tipoConta[totalContas] == 1 || tipoConta[totalContas] == 2);
                    
                    if (!valido) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Tipo invalido. Escolha 1 ou 2.\n";
                    }
                } while (!valido);
                
                // Leitura do depósito inicial: deve ser numérico e não negativo
                do {
                    cout << "Digite o deposito inicial (R$): ";
                    valido = (cin >> saldo[totalContas]) && saldo[totalContas] >= 0;
                    
                    if (!valido) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Valor invalido. O deposito deve ser um numero nao negativo.\n";
                    }
                } while (!valido);

                // Conta corrente recebe limite de crédito; poupança não
                if (tipoConta[totalContas] == 1) {
                    limiteCredito[totalContas] = 500.00;
                } else {
                    limiteCredito[totalContas] = 0.0;
                }
                
                contaAtiva[totalContas] = true; 
                
                cout << "\n[SUCESSO] Conta numero " << numeroConta[totalContas] << " cadastrada e ativada!\n";
                
                totalContas++; // Incrementa o contador após o cadastro bem-sucedido
                break;
            }
                
            case 2: 
                if (totalContas == 0) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else {
                    int numBusca;
                    bool encontrada = false;
                    cout << "Digite o numero da conta que deseja consultar: ";
                    
                    // Repete a leitura enquanto a entrada não for numérica
                    while (!(cin >> numBusca)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Entrada invalida. Digite apenas numeros: ";
                    }
                    
                    // Estrutura de busca no Array
                    for (int i = 0; i < totalContas; i++) {
                        if (numeroConta[i] == numBusca) {
                            encontrada = true;
                            cout << "\n>>> DADOS DO CLIENTE <<<\n";
                            cout << " Titular.....: " << nomeCliente[i] << "\n";
                            cout << " CPF.........: " << cpf[i] << "\n";
                            cout << " Conta.......: " << numeroConta[i] << "\n";
                            cout << " Tipo........: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << "\n";
                            cout << " Status......: " << (contaAtiva[i] ? "ATIVA" : "INATIVA") << "\n";
                            if (tipoConta[i] == 1) {
                                cout << " Limite Extra: R$ " << limiteCredito[i] << "\n";
                            }
                            break; // Para de procurar após encontrar
                        }
                    }
                    if (!encontrada) cout << "\n[ERRO] Conta nao encontrada.\n";
                }
                break;
                
            case 3: 
                if (totalContas == 0) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else {
                    int numBusca;
                    bool encontrada = false;
                    cout << "Digite o numero da conta para ver o saldo: ";
                    
                    while (!(cin >> numBusca)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Entrada invalida. Digite apenas numeros: ";
                    }
                    
                    for (int i = 0; i < totalContas; i++) {
                        if (numeroConta[i] == numBusca) {
                            encontrada = true;
                            // Operação depende de conta ativa
                            if (!contaAtiva[i]) {
                                cout << "\n[BLOQUEIO] Conta inativa. Reative a conta para ver o saldo.\n";
                            } else {
                                cout << "\n>>> SALDO DISPONIVEL <<<\n";
                                cout << " Saldo Atual: R$ " << saldo[i] << "\n";
                                if (tipoConta[i] == 1) {
                                    cout << " Limite.....: R$ " << limiteCredito[i] << "\n";
                                    cout << " Total Livre: R$ " << (saldo[i] + limiteCredito[i]) << "\n";
                                }
                            }
                            break;
                        }
                    }
                    if (!encontrada) cout << "\n[ERRO] Conta nao encontrada.\n";
                }
                break;
                
            case 4: 
                if (totalContas == 0) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else {
                    int numBusca;
                    bool encontrada = false;
                    cout << "Digite o numero da conta para alterar o tipo: ";
                    
                    while (!(cin >> numBusca)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Entrada invalida. Digite apenas numeros: ";
                    }
                    
                    for (int i = 0; i < totalContas; i++) {
                        if (numeroConta[i] == numBusca) {
                            encontrada = true;
                            // Operação depende de conta ativa
                            if (!contaAtiva[i]) {
                                cout << "\n[BLOQUEIO] Operacao negada. A conta encontra-se inativa.\n";
                            } else {
                                cout << "\nO tipo atual e: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << "\n";
                                
                                // Lê o novo tipo em uma variável auxiliar para não alterar
                                // o tipo da conta caso a entrada seja inválida
                                int novoTipo;
                                bool valido;
                                do {
                                    cout << "Para qual tipo deseja mudar? (1 = Corrente | 2 = Poupanca): ";
                                    valido = (cin >> novoTipo) && (novoTipo == 1 || novoTipo == 2);
                                    
                                    if (!valido) {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "  -> Tipo invalido. Escolha 1 ou 2.\n";
                                    }
                                } while (!valido);
                                
                                tipoConta[i] = novoTipo;
                                limiteCredito[i] = (tipoConta[i] == 1) ? 500.00 : 0.0;
                                cout << "\n[SUCESSO] O tipo da conta foi atualizado.\n";
                            }
                            break;
                        }
                    }
                    if (!encontrada) cout << "\n[ERRO] Conta nao encontrada.\n";
                }
                break;
                
            case 5: 
                if (totalContas == 0) {
                    cout << "\n[AVISO] Nenhuma conta cadastrada no sistema.\n";
                } else {
                    int numBusca;
                    bool encontrada = false;
                    cout << "Digite o numero da conta para ativar ou desativar: ";
                    
                    while (!(cin >> numBusca)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  -> Entrada invalida. Digite apenas numeros: ";
                    }
                    
                    for (int i = 0; i < totalContas; i++) {
                        if (numeroConta[i] == numBusca) {
                            encontrada = true;
                            contaAtiva[i] = !contaAtiva[i]; // Inverte a situação atual da conta
                            cout << "\n[ATUALIZACAO] A conta foi " << (contaAtiva[i] ? "ATIVADA" : "DESATIVADA") << " com sucesso.\n";
                            break;
                        }
                    }
                    if (!encontrada) cout << "\n[ERRO] Conta nao encontrada.\n";
                }
                break;
                
            case 6: 
                // Nesta etapa os dados ficam apenas em memória (persistência será vista na Etapa 3)
                cout << "\nEncerrando o sistema BANCO INF101. Ate logo!\n";
                break;
                
            default:
                cout << "\n[ERRO] Opcao invalida. Escolha um numero de 1 a 6.\n";
        }
    } while(opcao != 6);

    return 0;
}
