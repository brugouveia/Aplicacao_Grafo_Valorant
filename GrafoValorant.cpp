// Bruna Gouveia de Morais
// Silvania Alves Oliveira

#include <iostream>
#include <locale.h>
#include <climits>
#include <vector>
#include <stack>
#include <queue>
#include <map>

using namespace std;

#define numLocais 24 // Número de locais do mapa do jogo
typedef pair<int,int> ii;

string local[numLocais] = {
	"Spike site A",
	"Spike site B",
	"Surgimento do lado atacante",
	"Surgimento do lado defensor",
	"Meio superior",
	"Meio inferior",
	"Saguão A",
	"Saguão B",
	"Passarela",
	"Nicho meio",
	"A principal",
	"B principal",
	"Link meio",
	"Pátio do meio",
	"Link A",
	"Jardim A",
	"Pizza meio",
	"Mercado",
	"Barco",
	"Fundos B",
	"Janela A",
	"Vigas A",
	"Corredor",
	"Entrada"
};

map<string, int> localInt;

void inicializaLocais() {
	for(int i = 0; i < numLocais; i++)
		localInt[local[i]] = i;
}

struct Aresta {
    int destino;
    int peso;
};

struct Grafo {
	// cada posicao do vector representa um vertice que pode ter até numLocais arestas
    vector<Aresta> vertice[numLocais];
};

// o grafo é não direcionado, entao é necessario que as arestas tenham o mesmo peso
void insereVerticeNaoDirecionado(Grafo &g, string origem, string destino, int peso) {
	g.vertice[localInt[origem]].push_back({localInt[destino], peso});
	g.vertice[localInt[destino]].push_back({localInt[origem], peso});
}

// constroi o grafo, conectando os locais e definindo a distancia para ir de um ao outro
void insereDadosGrafo(Grafo &g) {
	insereVerticeNaoDirecionado(g, "Spike site A", "Vigas A", 1);
	insereVerticeNaoDirecionado(g, "Spike site A", "Entrada", 2);
	
	insereVerticeNaoDirecionado(g, "Spike site B", "Fundos B", 3);
	insereVerticeNaoDirecionado(g, "Spike site B", "Barco", 5);
	insereVerticeNaoDirecionado(g, "Spike site B", "Corredor", 1);
	
	insereVerticeNaoDirecionado(g, "Surgimento do lado atacante", "Meio superior", 25);
	insereVerticeNaoDirecionado(g, "Surgimento do lado atacante", "Saguão B", 23);
	
	insereVerticeNaoDirecionado(g, "Surgimento do lado defensor", "Jardim A", 15);
	insereVerticeNaoDirecionado(g, "Surgimento do lado defensor", "Vigas A", 20);
	insereVerticeNaoDirecionado(g, "Surgimento do lado defensor", "Pizza meio", 12);
	insereVerticeNaoDirecionado(g, "Surgimento do lado defensor", "Barco", 16);
	
	insereVerticeNaoDirecionado(g, "Meio inferior", "Pizza meio", 3);
	insereVerticeNaoDirecionado(g, "Meio inferior", "Pátio do meio", 2);
	
	insereVerticeNaoDirecionado(g, "Saguão A", "A principal", 15);
	insereVerticeNaoDirecionado(g, "Saguão A", "Meio superior", 11);
	
	insereVerticeNaoDirecionado(g, "Passarela", "Nicho meio", 4);
	insereVerticeNaoDirecionado(g, "Passarela", "Pátio do meio", 2);
	insereVerticeNaoDirecionado(g, "Passarela", "Meio superior", 8);

	insereVerticeNaoDirecionado(g, "Link A", "Nicho meio", 3);
	insereVerticeNaoDirecionado(g, "Link A", "Jardim A", 2);
	insereVerticeNaoDirecionado(g, "Link A", "Entrada", 10);
	
	insereVerticeNaoDirecionado(g, "A principal", "Entrada", 13);

	insereVerticeNaoDirecionado(g, "B principal", "Barco", 7);
	insereVerticeNaoDirecionado(g, "B principal", "Saguão B", 12);
	
	insereVerticeNaoDirecionado(g, "Link meio", "Pátio do meio", 5);
	insereVerticeNaoDirecionado(g, "Link meio", "Saguão B", 9);
	
	insereVerticeNaoDirecionado(g, "Mercado", "Barco", 9);
	insereVerticeNaoDirecionado(g, "Mercado", "Pizza meio", 2);
	
	insereVerticeNaoDirecionado(g, "Barco", "Corredor", 11);
	
	insereVerticeNaoDirecionado(g, "Janela A", "Jardim A", 3);
	insereVerticeNaoDirecionado(g, "Janela A", "Vigas A", 7);
}

// encontra o menor caminho da origem para todos os vertices
void dijkstra(Grafo g, int origem, int destino) {
	int dist[numLocais];   // distancia da origem para cada vertice
	int parent[numLocais];	// armazena o vertice pai de cada vertice
	
	for(int i = 0; i < numLocais; i++) {   // inicializa todas as distancias com o maior inteiro possivel
		dist[i] = INT_MAX;
		parent[i] = i;
	}
	dist[origem] = 0;	// do vertice de origem ate ele mesmo a distancia eh 0
	
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push({0, origem});
	
	while(!pq.empty()) {
		int u = pq.top().second;
        pq.pop();
        	
    	for(int i = 0; i < g.vertice[u].size(); i++) {	// percorre todas as arestas do vertice u
    		Aresta aresta = g.vertice[u][i];
    		int v = aresta.destino;
    		int peso = aresta.peso;
			
			if(dist[v] > dist[u] + peso) {
				dist[v] = dist[u] + peso;
				pq.push({dist[v], v});
				parent[v] = u;
			}
		}
	}
	
	cout << "Menor distancia de " << local[origem] << " até " << local[destino] << ": " << dist[destino] << endl;
	
	stack<int> caminho;
	int node = destino;
	while(parent[node] != node) {
		caminho.push(node);
		node = parent[node];
	}
	caminho.push(origem);
	
	// imprime o menor caminho da origem até o destino
	cout << "Menor caminho de " << local[origem] << " até " << local[destino] << ":\n";
    while(!caminho.empty()) {
    	cout << local[caminho.top()];
    	caminho.pop();
    	if(!caminho.empty()) cout << " -> ";
    	else cout << endl;
	}
}

// constroi a arvore geradora minima
void primMST(Grafo g, int origem) {
    bool visitado[numLocais];
    int pai[numLocais];  // armazena a MST construida
    int chave[numLocais];  // chave usada para escolher o mínimo valor de corte
    
    // inicializa todas as chaves com infinito e visitado com falso
    for(int i = 0; i < numLocais; i++) {
    	chave[i] = INT_MAX;
    	visitado[i] = false;
    	pai[i] = 0;
	}

	// primeiro no eh sempre raiz da MST
    chave[origem] = 0;
    pai[origem] = -1;	// raiz nao tem pai

    for(int count = 0; count < numLocais - 1; count++) {
        int u, minChave = INT_MAX;
		
		// encontrando o vertice com o menor custo ainda nao visitado
        for(int v = 0; v < numLocais; v++) {
            if(!visitado[v] && chave[v] < minChave) {
                minChave = chave[v];
                u = v;
            }
        }

        visitado[u] = true;
		
		for(int i = 0; i < g.vertice[u].size(); i++) {	// percorre todas as arestas do vertice u
			Aresta aresta = g.vertice[u][i];
			int v = aresta.destino;
            int peso = aresta.peso;
            
            if (peso && !visitado[v] && peso < chave[v]) {
                pai[v] = u;
                chave[v] = peso;
            }
		}
    }
	
	// imprime a arvore geradora minima
    cout << "\nÁrvore Geradora Mínima\n" << endl;
    for(int i = 0; i < numLocais; i++) {
    	if(i != origem) {
    		cout << local[i] << " - " << local[pai[i]] << ", distancia: " << chave[i] << endl;
		}
    }
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	inicializaLocais();
	
	Grafo grafo;
	insereDadosGrafo(grafo);  // constroi o grafo
	
	for(int i = 0; i < numLocais; i++) {
		cout << i  << " - " << local[i] << endl;
	}
	int origem, destino;
	cout << "\nSelecione o local de ORIGEM:\n--> ";
	cin >> origem;
	cout << "\nSelecione o local de DESTINO:\n--> ";
	cin >> destino;
	cout << endl;
	
    dijkstra(grafo, origem, destino);
    
    primMST(grafo, origem);
}
