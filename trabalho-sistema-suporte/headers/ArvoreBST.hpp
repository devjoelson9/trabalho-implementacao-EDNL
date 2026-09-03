#ifndef _ARVORE_BST_HPP_
#define _ARVORE_BST_HPP_

#include "Chamado.hpp"
#include "NoBST.hpp"

class ArvoreBST{
    private:
        NoBST* raiz;

    public:
        ArvoreBST();
        ~ArvoreBST();

        bool inserir(Chamado chamado);
        Chamado buscar(int id);
        bool remover(int id);
        void listarEmOrdem();
        Chamado buscarMenorID();
        Chamado buscarMaiorID();
        int getAltura();
        int getQuantidadeTotal();
        void listarPorIntervalo(int idInicio, int idFim);
        void percursoPreOrdem();
        void percursoPosOrdem();
        void percursoEmLargura();
};

#endif