/*1. O Lobby dos Jogadores (Substituindo o vetor fixo por Lista Encadeada)
Em vez de Jogador lobby[100], foi criado um nó para cada jogador. O lobby cresce dinamicamente na memória RAM sempre que um novo usuário se conecta.*/

#include <iostream>
#include <string>

// Estrutura que representa o jogador
struct Jogador {
    int id;
    std::string nome;
};

// Estrutura do Nó da Lista Encadeada
struct NoLobby {
    Jogador dado;
    NoLobby* proximo; // Ponteiro para o próximo jogador da lista
};

// Função para adicionar jogador no lobby (Alocação Dinâmica)
void entrarNoLobby(NoLobby*& topo, int id, std::string nome) {
    // Aloca memória dinamicamente para um novo nó
    NoLobby* novoNo = new NoLobby(); 
    novoNo->dado.id = id;
    novoNo->dado.nome = nome;
    
    // Insere no início da lista (Lobby)
    novoNo->proximo = topo;
    topo = novoNo;
    
    std::cout << nome << " entrou no lobby com sucesso!\n";
}


/*2. A Fila de Login Justa (Implementando o conceito FIFO)
Aqui, foi criada uma fila onde quem chega entra no fim (fim) e quem é liberado para jogar sai do início (inicio). Isso mata a "furada de fila".*/

// Estrutura do Nó da Fila de Espera
struct NoFila {
    Jogador dado;
    NoFila* proximo;
};

// Estrutura de controle da Fila (Início e Fim)
struct FilaLogin {
    NoFila* inicio = nullptr;
    NoFila* fim = nullptr;
};

// Função para entrar na fila (Enqueue - no fim)
void entrarNaFila(FilaLogin& fila, int id, std::string nome) {
    NoFila* novoNo = new NoFila();
    novoNo->dado.id = id;
    novoNo->dado.nome = nome;
    novoNo->proximo = nullptr;

    if (fila.fim == nullptr) { // Se a fila estiver vazia
        fila.inicio = fila.fim = novoNo;
    } else {
        fila.fim->proximo = novoNo; // O atual último aponta para o novo
        fila.fim = novoNo;          // O novo se torna o fim da fila
    }
    std::cout << nome << " entrou na fila de espera para login.\n";
}

// Função para autorizar entrada no jogo (Dequeue - do início)
void realizarLogin(FilaLogin& fila) {
    if (fila.inicio == nullptr) {
        std::cout << "Fila de espera vazia.\n";
        return;
    }
    
    NoFila* temp = fila.inicio;
    std::cout << temp->dado.nome << " teve o login autorizado (Ordem FIFO).\n";
    
    fila.inicio = fila.inicio->proximo; // O segundo da fila vira o primeiro
    
    if (fila.inicio == nullptr) {
        fila.fim = nullptr;
    }
    
    delete temp; // Libera a memória RAM do jogador que já logou
}


/*3. O Botão "Desfazer" Rápido (Implementando o conceito LIFO)
Para reverter a última jogada de forma instantânea, empilham-se as ações. O botão "Desfazer" apenas retira o elemento do topo da pilha.*/
// Estrutura que representa uma ação no jogo
struct Jogada {
    int idJogada;
    std::string tipoAcao; // Ex: "Mover_Tropa", "Construir_Quartel"
};

// Estrutura do Nó da Pilha
struct NoPilha {
    Jogada dado;
    NoPilha* proximo;
};

// Função para registrar nova ação (Push - no topo)
void registrarJogada(NoPilha*& topo, int id, std::string acao) {
    NoPilha* novoNo = new NoPilha();
    novoNo->dado.idJogada = id;
    novoNo->dado.tipoAcao = acao;
    
    novoNo->proximo = topo; // O novo nó aponta para o antigo topo
    topo = novoNo;          // O novo nó vira o topo da pilha
}

// Função para o botão Desfazer (Pop - remove do topo)
void desfazerJogada(NoPilha*& topo) {
    if (topo == nullptr) {
        std::cout << "Nenhuma jogada para desfazer.\n";
        return;
    }
    
    NoPilha* temp = topo;
    std::cout << "Desfazendo a ultima acao realizada: " << temp->dado.tipoAcao << "\n";
    
    topo = topo->proximo; // O elemento de baixo vira o novo topo
    delete temp;          // Libera a memória da ação desfeita
}