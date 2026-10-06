#include <iostream>  // Maneja flujos de entrada y salida
#include <vector>    // Proporciona arreglos dinamicos redimensionables
#include <queue>     // Implementa la estructura de Cola con logica FIFO (primero en entrar, primero en salir)
#include <algorithm> // Contiene funciones optimizadas de manipulacion de datos (fill, min)

using namespace std;

// Valor infinito neutro para aislar correctamente la capacidad del tramo mas estrecho
const int INF = 1000000000; 

// Estructura o molde base que define las propiedades fijas de una arista
struct Arista {  
    int v;             // Nodo destino
    int capacidad;     // Capacidad original o actual de avance
    int flujo;         // Flujo real transportado
    int inverso;       // Indice de la arista residual contraria
};

// Clase principal que encapsula la infraestructura del sistema
class RedFlujo {
	private: //Protege las variables más importantes de sufrir alteraciones externas
    		int V;                          // Numero total de vertices
    		vector<vector<Arista> > adj;    // Lista de adyacencia de la red residual
   	 		vector<bool> visitadoDFS;       // Registro de nodos explorados

	public:  //Metodos autorizados para interactuar con la red
   		
		// Inicializa los casilleros de los V nodos en la memoria RAM
		RedFlujo(int V) { 
	        this->V = V;
	        adj.resize(V);
	        visitadoDFS.resize(V, false);
	    }

	    // Instancia de forma simetrica los canales originales de avance y los residuales inversos
	    void agregarArista(int u, int v, int capacidad) {
	        Arista a = {v, capacidad, 0, (int)adj[v].size()};
	        Arista b = {u, 0, 0, (int)adj[u].size()}; 
	        adj[u].push_back(a);
	        adj[v].push_back(b);
	    }
	
	    // Busqueda en anchura (BFS) para hallar la ruta de aumento mas corta hacia el sumidero
	    bool bfs(int s, int t, vector<int>& padre, vector<int>& indiceArista) {
	        fill(padre.begin(), padre.end(), -1);
	        padre[s] = s;
	        queue<int> q;
	        q.push(s);
	
	        while (!q.empty()) {
	            int u = q.front();
	            q.pop();
	
	            for (size_t i = 0; i < adj[u].size(); i++) {
	                Arista &arista = adj[u][i];
	                // Verifica que el vecino no haya sido visitado y el canal tenga espacio libre
	                if (padre[arista.v] == -1 && arista.capacidad - arista.flujo > 0) {
	                    padre[arista.v] = u;
	                    indiceArista[arista.v] = i;
	                    if (arista.v == t) return true; // Ruta encontrada con exito
	                    q.push(arista.v);
	                }
	            }
	        }
	        return false; // Sistema bloqueado: no hay mas caminos disponibles
	    }
	
	    // Busqueda en profundidad (DFS) para rastrear que nodos siguen alcanzables desde 's' al final
	    void dfsResidual(int u) {
	        visitadoDFS[u] = true;
	        for (size_t i = 0; i < adj[u].size(); i++) {
	            Arista &arista = adj[u][i];
	            if (!visitadoDFS[arista.v] && (arista.capacidad - arista.flujo > 0)) {
	                dfsResidual(arista.v);
	            }
	        }
	    }
	
	    // Motor ejecutor del algoritmo de Edmonds-Karp y verificador del teorema
	    void verificarTeorema(int s, int t) {
	        int flujoMaximo = 0;
	        vector<int> padre(V);
	        vector<int> indiceArista(V);
	
	        // Fase 1: Inyeccion iterativa de flujos a traves de los cuellos de botella
	        while (bfs(s, t, padre, indiceArista)) {
	            int flujoCamino = INF;
	            // Identifica el tramo mas restrictivo de la ruta hallada
	            for (int v = t; v != s; v = padre[v]) {
	                int u = padre[v];
	                int idx = indiceArista[v];
	                flujoCamino = min(flujoCamino, adj[u][idx].capacidad - adj[u][idx].flujo);
	            }
	
	            // Aplica el principio de asimetria: suma al avance y resta al retorno
	            for (int v = t; v != s; v = padre[v]) {
	                int u = padre[v];
	                int idx = indiceArista[v];
	                adj[u][idx].flujo += flujoCamino;
	                int invIdx = adj[u][idx].inverso;
	                adj[v][invIdx].flujo -= flujoCamino;
	            }
	            flujoMaximo += flujoCamino; // Acumula el rendimiento total
	        }
	
	        // Fase 2: Impresion y validacion del Teorema de Flujo Maximo-Corte Minimo
	        cout << "==================================================" << endl;
	        cout << "1. COMPROBACION DE FLUJO MAXIMO" << endl;
	        cout << "   Flujo Maximo calculado en el sumidero: " << flujoMaximo << " unidades." << endl;
	        cout << "==================================================" << endl;
	
	        // Llama a la DFS para segmentar la red bloqueada en los conjuntos L y R
	        fill(visitadoDFS.begin(), visitadoDFS.end(), false);
	        dfsResidual(s);
	
	        cout << "2. PARTICION DEL CORTE MINIMO" << endl;
	        cout << "   Conjunto L (Alcanzables desde s): { ";
	        for (int i = 0; i < V; i++) if (visitadoDFS[i]) cout << i << " ";
	        cout << "}\n   Conjunto R (Aislados):           { ";
	        for (int i = 0; i < V; i++) if (!visitadoDFS[i]) cout << i << " ";
	        cout << "}" << endl;
	        cout << "==================================================" << endl;
	
	        cout << "3. ARISTAS DEL CORTE MINIMO (Saturadas L -> R)" << endl;
	        int capacidadCorteMino = 0;
	        for (int u = 0; u < V; u++) {
	            if (visitadoDFS[u]) { 
	                for (size_t i = 0; i < adj[u].size(); i++) {
	                    Arista &arista = adj[u][i];
	                    // Detecta las fronteras criticas originales que van del bloque L al R
	                    if (!visitadoDFS[arista.v] && arista.capacidad > 0) {
	                        cout << "   Arista (" << u << " -> " << arista.v 
	                             << ") | Capacidad Original: " << arista.capacidad 
	                             << " | Flujo Final: " << arista.flujo << endl;
	                        capacidadCorteMino += arista.capacidad;
	                    }
	                }
	            }
	        }
	        cout << "   Capacidad calculada del Corte Minimo: " << capacidadCorteMino << " unidades." << endl;
	        cout << "==================================================" << endl;
	        
	        // Validacion analitica de la igualdad de la dualidad geometrica
	        if (flujoMaximo == capacidadCorteMino) {
	            cout << " VERIFICACION EXITOSA: Flujo Maximo == Corte Minimo (" 
	                 << flujoMaximo << " == " << capacidadCorteMino << ")" << endl;
	        }
	        cout << "==================================================" << endl;
	    }
};

int main() {
    // Inicializa el plano base de la red con 6 estaciones
    RedFlujo red(6);

    // Mapeo topografico original del ejercicio (origen, destino, capacidad)
    red.agregarArista(0, 1, 16); // s -> 1
    red.agregarArista(0, 3, 13); // s -> 3
    red.agregarArista(1, 2, 12); // 1 -> 2
    red.agregarArista(1, 3, 10);  // 1 -> 3
    red.agregarArista(2, 5, 20); // 2 -> t
    red.agregarArista(3, 1, 4); // 3 -> 1
    red.agregarArista(2, 3, 9);  // 3 -> 2
    red.agregarArista(3, 4, 14); // 3 -> 4
    red.agregarArista(4, 2, 7);  // 4 -> 2
    red.agregarArista(4, 5, 4);  // 4 -> t

    int fuente = 0;   // Nodo s
    int sumidero = 5; // Nodo t

    // Despierta el sistema y ejecuta la simulacion 
    red.verificarTeorema(fuente, sumidero);

    return 0;
}

