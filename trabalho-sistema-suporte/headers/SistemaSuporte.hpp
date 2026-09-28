#ifndef SISTEMA_SUPORTE_HPP
#define SISTEMA_SUPORTE_HPP

#include "ArvoreBST.hpp"
#include "FilaAtendimento.hpp"
#include <string>

class SistemaSuporte{
    private:
        ArvoreBST arvoreChamados;
        FilaAtendimento filaAtendimento;

        int lerInteiro(const std::string& mensagem, int min, int max);

    public:
        SistemaSuporte();
        ~SistemaSuporte();

        void abrirChamado();
        void buscarChamado();
        void removerChamado();
        void listarChamados();
        void listarPorIntervalo();
        void encaminharParaAtendimento();
        void atenderProximo();
        void consultarHistorico();
        void alterarStatus();
        void exibirEstatisticas();
        void preOrdem();
        void posOrdem();
        void emLargura();
        void consultarFrenteFila();
};

#endif