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
    topo = topo= novoNo;
    
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

// ==========================================
// FUNÇÃO PRINCIPAL (Ponto de Partida do C++)
// ==========================================
int main() {
    // 1. Inicializando os ponteiros de controle das estruturas como vazios
    NoLobby* meuLobby = nullptr;
    FilaLogin minhaFila; 
    NoPilha* meuHistoricoDeJogadas = nullptr;

    std::cout << "=== SIMULACAO DO SERVIDOR - KINGDOMS ONLINE ===\n\n";

    // --- TESTE 1: LOBBY DINÂMICO (Sem limite de 100) ---
    std::cout << "[Testando o Lobby Dinamico]\n";
    entrarNoLobby(meuLobby, 1, "Michelle_Dev");
    entrarNoLobby(meuLobby, 2, "Player_Gamer");
    std::cout << "\n";

    // --- TESTE 2: FILA DE LOGIN JUSTA (FIFO) ---
    std::cout << "[Testando Fila de Login - FIFO]\n";
    entrarNaFila(minhaFila, 10, "Arthur_99");
    entrarNaFila(minhaFila, 11, "Lucas_Gamer");
    entrarNaFila(minhaFila, 12, "Carla_Pro");
    
    std::cout << "\nLiberando acessos:\n";
    realizarLogin(minhaFila); // Deve autorizar o Arthur_99 (chegou primeiro)
    realizarLogin(minhaFila); // Deve autorizar o Lucas_Gamer
    std::cout << "\n";

    // --- TESTE 3: BOTAO DESFAZER (LIFO/Pilha) ---
    std::cout << "[Testando Historico de Acoes - LIFO]\n";
    registrarJogada(meuHistoricoDeJogadas, 101, "Mover_Tropa_A1");
    registrarJogada(meuHistoricoDeJogadas, 102, "Construir_Quartel");
    registrarJogada(meuHistoricoDeJogadas, 103, "Atacar_Castelo_Inimigo");

    std::cout << "\nClicando no botao Desfazer:\n";
    desfazerJogada(meuHistoricoDeJogadas); // Deve desfazer a ultima (Atacar_Castelo_Inimigo)
    desfazerJogada(meuHistoricoDeJogadas); // Deve desfazer a penultima (Construir_Quartel)
    
    std::cout << "\n================================================\n";
    return 0;
}