# Introdução

## Contexto

Este trabalho foi desenvolvido para a disciplina INF101 – Programação de Computadores I, do Centro Universitário de Viçosa (UNIVIÇOSA), ministrada pelos professores Anderson R. Lamas e Vanderlea Queiroz.

A proposta consiste no desenvolvimento incremental de um Sistema de Registro e Gestão de Contas Bancárias em linguagem C++, dividido em três etapas que acompanham a progressão dos conteúdos da disciplina:

1. **Etapa 1:** variáveis e estruturas de controle;
2. **Etapa 2:** arrays e funções;
3. **Etapa 3:** persistência de dados em arquivos.

As três etapas representam a evolução de um mesmo sistema, e as limitações identificadas em cada uma delas servem de motivação para o conteúdo apresentado na etapa seguinte.

## Objetivo

O objetivo desta primeira etapa é consolidar os fundamentos da linguagem C++ por meio da implementação de um sistema bancário simples, executado em modo texto, capaz de cadastrar uma conta bancária e realizar operações básicas sobre ela.

São objetivos específicos:

- utilizar variáveis de diferentes tipos (`int`, `double`, `string` e `bool`) para representar os dados de uma conta;
- implementar um menu interativo com a estrutura de seleção `switch` e a estrutura de repetição `do-while`;
- validar as entradas do usuário, garantindo a consistência dos dados cadastrados;
- restringir operações de acordo com a situação da conta (ativa ou inativa);
- propor e implementar uma solução para o cadastro de até cinco contas.

## Descrição do sistema

O sistema, denominado **BANCO INF101**, apresenta um menu com seis opções: cadastrar conta, consultar conta, verificar saldo, alterar tipo da conta, ativar ou desativar conta e sair. O menu permanece em execução até que o usuário selecione a opção de saída.

No cadastro, são solicitados o número da conta, o nome do titular, o CPF, uma senha, o tipo da conta (Corrente ou Poupança) e o saldo inicial. Contas do tipo Corrente recebem um limite de crédito de R$ 500,00. O sistema valida os dados informados, impedindo, por exemplo, números de conta não positivos, saldo inicial negativo, tipos de conta inexistentes e a digitação de texto em campos numéricos.

## Organização do trabalho

A implementação foi organizada em duas versões:

- **Versão principal:** atende ao enunciado da Etapa 1, permitindo o cadastro de uma única conta e utilizando somente variáveis individuais.
- **Versão do desafio:** responde ao item 3.5 do enunciado, permitindo o cadastro de até cinco contas por meio de arrays.

A comparação entre as duas versões evidencia a principal limitação desta etapa: com variáveis individuais, o sistema comporta apenas uma conta, e ampliá-lo exigiria a repetição de variáveis e de código para cada nova conta. Essa limitação motiva o uso de arrays, conteúdo previsto para a Etapa 2.

A descrição detalhada das funcionalidades, das validações, da justificativa para o uso de arrays e das instruções de compilação encontra-se no arquivo `README.md`.
