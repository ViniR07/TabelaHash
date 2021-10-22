// Struct de valores para os itens da Hash
typedef struct {
    int ocorr, chave;
    float valor;
    char nome[50];
} celula;

// Array de structs
// Estrutura para a Tabela Hash
celula* tab;

// Protótipos
void flush_in();
void limpa_hash(int tamanho_tabela);
void insere_hash(int tamanho_tabela);
void contabiliza (int ch, char str[], float preco, int tamanho);
void escreve_hash(int tamanho_tabela);
void consulta_hash(int tamanho_tabela);
int procura_produto(int tamanho, int chave);
int consulta_preco(int tamanho, char str[]);
int hash(int ch, int tamanho);
int valor_string(char str[]);