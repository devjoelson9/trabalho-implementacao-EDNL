#ifndef SISTEMA_SUPORTE_HPP
#define SISTEMA_SUPORTE_HPP

#include "ArvoreBST.hpp"
#include "FilaAtendimento.hpp"

class SistemaSuporte{
    private:
        ArvoreBST arvoreChamados;
        FilaAtendimento filaAtendimento;

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
};

#endif