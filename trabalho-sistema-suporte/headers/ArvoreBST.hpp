#ifndef _ARVORE_BST_HPP_
#define _ARVORE_BST_HPP_

#include "Chamado.hpp"
#include "NoBST.hpp"

class ArvoreBST{
    private:
        NoBST* raiz;

        NoBST* inserirRec(NoBST* no, Chamado chamado);
        NoBST* removerRec(NoBST* no, int id);
        NoBST* transplant(NoBST* alvo, NoBST* substituto);
        NoBST* buscarRec(NoBST* no, int id);
        NoBST* menorNo(NoBST* no);
        void emOrdemRec(NoBST* no);
        void preOrdemRec(NoBST* no);
        void posOrdemRec(NoBST* no);
        int alturaRec(NoBST* no);
        int contarRec(NoBST* no);
        void listarIntervaloRec(NoBST* no, int idInicio, int idFim);
        void contarStatusRecursivo(NoBST* no, int& abertos, int& emAtendimento, int& resolvidos, int& cancelados);
        void liberarRec(NoBST* no);

    public:
        ArvoreBST();
        ~ArvoreBST();

        bool inserir(Chamado chamado);
        Chamado* buscar(int id);
        bool remover(int id);
        bool atualizarStatus(int id, Status novoStatus, const std::string& observacao);
        void listarEmOrdem();
        Chamado* buscarMenorID();
        Chamado* buscarMaiorID();
        int getAltura();
        int getQuantidadeTotal();
        void listarPorIntervalo(int idInicio, int idFim);
        void percursoPreOrdem();
        void percursoPosOrdem();
        void percursoEmLargura();
        void obterContagemStatus(int& abertos, int& emAtendimento, int& resolvidos, int& cancelados);
        NoBST* getRaiz() const;
};

#endif