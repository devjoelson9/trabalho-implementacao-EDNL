#include "headers/SistemaSuporte.hpp"
#include <iostream>

void exibirMenu() {
    std::cout << "=====================================" << std::endl;
    std::cout << "SISTEMA DE SUPORTE DE TI" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "1. Abrir chamado" << std::endl;
    std::cout << "2. Buscar chamado" << std::endl;
    std::cout << "3. Remover chamado" << std::endl;
    std::cout << "4. Listar chamados" << std::endl;
    std::cout << "5. Consultar chamados por intervalo" << std::endl;
    std::cout << "6. Encaminhar chamado para atendimento" << std::endl;
    std::cout << "7. Atender proximo chamado" << std::endl;
    std::cout << "8. Consultar historico" << std::endl;
    std::cout << "9. Alterar status" << std::endl;
    std::cout << "10. Estatisticas" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "\nEscolha: ";
}

int main() {
    SistemaSuporte sistema;
    int opcao;

    do {
        std::cout << std::endl;
        exibirMenu();
        std::cin >> opcao;

        switch (opcao) {
            case 1: sistema.abrirChamado(); break;
            case 2: sistema.buscarChamado(); break;
            case 3: sistema.removerChamado(); break;
            case 4: sistema.listarChamados(); break;
            case 5: sistema.listarPorIntervalo(); break;
            case 6: sistema.encaminharParaAtendimento(); break;
            case 7: sistema.atenderProximo(); break;
            case 8: sistema.consultarHistorico(); break;
            case 9: sistema.alterarStatus(); break;
            case 10: sistema.exibirEstatisticas(); break;
            case 0: std::cout << "Saindo..." << std::endl; break;
            default: std::cout << "Opcao invalida!" << std::endl;
        }
    } while (opcao != 0);

    return 0;
}