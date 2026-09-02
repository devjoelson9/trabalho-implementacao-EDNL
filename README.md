# EDNL — Estruturas de Dados Não Lineares

Ambiente de compilação de C++ em **Docker**, para não precisar instalar MinGW/GCC no Windows.

## Estrutura

```
EDNL/
├── aula-01/            # seus códigos (.cpp)
├── docker/             # configuração do ambiente
│   ├── Dockerfile          # imagem (gcc:14 + make, cmake, gdb)
│   ├── docker-compose.yml  # container com a pasta do projeto montada
│   └── run.ps1             # compila e executa um arquivo
└── README.md
```

## Pré-requisito

- [Docker Desktop](https://www.docker.com/products/docker-desktop/) instalado e **rodando**.

## Primeira vez (setup)

Na raiz do projeto (`C:\Users\joelson\Documents\EDNL`):

```powershell
docker compose -f docker/docker-compose.yml up -d --build
```

Isso baixa a imagem, compila o container `ednl-cpp` e deixa ele rodando em segundo plano (só precisa fazer uma vez).

## Compilar e rodar um arquivo

Da pasta raiz do projeto:

******************************************************
```powershell
.\docker\run.ps1 aula-01\teste.cpp
```
******************************************************
O script:
1. compila com `g++ -std=c++17 -Wall -g`
2. executa o binário dentro do container

O binário (`teste`) é salvo na mesma pasta do código.

## Outros comandos úteis

| Comando | O que faz |
|---|---|
| `docker compose -f docker/docker-compose.yml exec cpp bash` | abre um terminal Linux dentro do container |
| `docker compose -f docker/docker-compose.yml exec cpp gdb teste` | depura o binário com GDB |
| `docker compose -f docker/docker-compose.yml down` | para o container |
| `docker compose -f docker/docker-compose.yml up -d --build` | reinicia e reconstrói a imagem |

## FAQ

**Preciso reiniciar o container a cada código novo?** Não. A pasta do projeto é montada no container (`..:/workspace`), então qualquer `.cpp` que você criar já aparece dentro dele na hora.

**Meu código usa `make`/`CMake`?** Já estão instalados na imagem. Exemplo com o shell interativo:

```bash
cd /workspace/aula-01
make
./programa
```

**Tradução de caracteres/acentos no terminal?** O container usa Linux, então acentos funcionam normalmente nos `cout`.