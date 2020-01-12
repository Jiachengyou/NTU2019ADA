#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>
#include <cstring>

#include "hex.h"
#include <vector>
#include <climits>
#include <set>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <cfloat>
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <cfloat>
#include <cstring>
#include <set>
#include <cstdio>

// reference
// https://github.com/dbittman/hex-montecarlo
// discuss with lairuitao 
using namespace std;
typedef pair<int, int> pii;

const int maxn = 11;

bool taboard[maxn][maxn];

int n;
int num;


const int COLOR_RED   = 1;
const int COLOR_BLUE  = 2;


        

// _--------------Graph.h
class graph
{
	public:
		graph(int n) {
			num = n;
			conn.assign(n, std::vector<double>(n));
			node_color.assign(n, 0);
			node_data.assign(n, -1);
			/* nothing connected */
			for(int i=0;i<n;i++) {
				for(int j=0;j<n;j++) {
					conn[i][j] = conn[j][i] = INFINITY;
				}
			}
		}
		int size() { return num; }
		void connect_nodes(int i, int arg2);
		int get_node_color(int i)
		{
			return node_color[i];
		}
		void set_node_color(int i, int c)
		{
			node_color[i] = c;
		}
		double dijkstra(int start, int end, int, int, std::vector<int> &prev, std::vector<double> &dist);
		int bfs(int start, int end, int num_real, int color);
		int num;
		/* 2-D matrix of path lengths */
		std::vector< std::vector<double> > conn;
		/* colors of nodes */
		std::vector< int > node_color;
		std::vector< int > node_data;
};


// ------------Graph.cpp-----------
double graph::dijkstra(int start, int end, int num_real, int color, vector<int> &prev, vector<double> &dist)
{
	dist.clear();
	dist.assign(num, INFINITY);
	std::set<int>::iterator it;
	
	dist[start] = 0;
	prev.clear();
	prev.assign(num, -1);
	int count=0;
	set<int> unvisited;
	for(int i=0;i<num;i++) {
		unvisited.insert(i);
	}
	
	while(!unvisited.empty())
	{
		/* get lowest value in dist */
		int min=-1;
		for(int i=0;i<num;i++)
		{
			if(((min == -1) || dist[i] < dist[min]) && (unvisited.find(i) != unvisited.end())) min = i;
		}
		/* get and remove the minimum of dist from the unvisited set */
		int current = *(it = unvisited.find(min));
		unvisited.erase(it);
		if(current == end)
			break;
		/* no point in continuing from here */
		if(dist[current] == INFINITY)
			break;
		/* loop through all nodes to find neighbors */
		for (int i=0;i<num;i++)
		{
			
			double length = 0;
			if(node_color[i] == 0)
				length = 1;
			else if(node_color[i] != color)
				length = INFINITY;
			if(conn[i][current] == INFINITY || conn[current][i] == INFINITY)
				length = INFINITY;
			/* if we are connected, and we aren't ignoring this path... */
			if(length != INFINITY && ((i < num_real) || i == end) && i != current)
			{
				/* calculate the distance from here */
				double newdist = dist[current] + length;
				if(newdist < dist[i])
				{
					/* swap it out if we've beaten the previous distance */
					dist[i] = newdist;
					prev[i] = current;
				}
			}
		}
		
	}
	return dist[end];
}

int graph::bfs(int start, int end, int num_real, int color)
{
	if(node_color[start] != node_color[end] && node_color[end] != color) return 0;
	std::set<int>::iterator it;
	queue<int> nodes;
	vector<int> markings;
	markings.assign(num, 0);
	nodes.push(start);
	markings[start] = 1;
	while(!nodes.empty()) {
		int t = nodes.front();
		nodes.pop();
		if(t == end)
			return 1;
		for(int i=0;i<num;i++)
		{
 			if(conn[i][t] != INFINITY && node_color[i] == color && !markings[i]) {
				markings[i] = 1;
				nodes.push(i);
			}
		}
	}
	return 0;
}

/* register these two nodes as connected. Path length doesn't matter, that's calculated via 
 * the colors of the nodes */
void graph::connect_nodes(int a, int b)
{
	conn[a][b] = 1;
 	conn[b][a] = 1;
}


// ------------------------hex.h----------------------------
class hexboard {
public:
	hexboard(int _size)
	{

	}
    void setup(int _size) {
        		if(!_size) return;
		size = _size;
		empty = size*size;
		/* 4 more nodes for the sides of the board */
		board = new graph(size * size + 4);

    }
	/* ~hexboard()
	{
		delete board;
	}*/
	/* if this node is uncolored, we may make a move there */
	bool is_valid_move(int i)
	{
		if(i > size*size) return false;
		return board->get_node_color(i) == 0;
	}
	void generate_connected_graph();
	void print_board();
	int convert_coords(int x, int y);
	int make_move(int node, int);
	double computer_move(int color, int start, int end);
	double montecarlo(int color, int start, int end);
	double computer_move_dijkstra(int color, int start, int end);
	int size;
	int empty;
	graph *board;
	int last;
	hexboard *clone();
	int get_random_move();
	int simulate(int i, int color, int other_player_color, int start, int end, int node);
	void sim_make_move(int node, int color, int current);
};

// ----- hex.cpp
/* which sides are which based on the length of a side of a board */
#define SIDE_TOP(n) n*n
#define SIDE_RIGHT(n) n*n+1
#define SIDE_BOTTOM(n) n*n+2
#define SIDE_LEFT(n) n*n+3
/* set to 1 for TRUE */
int debug = 0;
int num_iterations = 500;

void hexboard::generate_connected_graph()
{
	/* the sides of the board are nodes from size*size through size*size+3 (aka, the 4 nodes
	 * that are greater than 0-n*n).
	 */
	int n = size;
	/*
	 * 0 1 2 3
	 *  4 5 6 7
	 *   8 9 10 11
	 *     12 13 14 15
	 * a node will connect to nodes (N=node, RW=row width)
	 *    N-RW
	 *    N-RW+1
	 *    N-1 
	 *    N+1
	 *    N+RW-1
	 *    N+RW
	 */
	/* Connect each node with it's neighbors */
	for (int i=0;i<n*n;i++)
	{
		if(!((i+1) % n == 0) && !(i < n))
			board->connect_nodes(i, i-n + 1);
		if(!(i%n == 0) && !(i+n >= n*n)/*not on left edge and not bottom row*/)
			board->connect_nodes(i, i+n - 1);
		if(!(i < n)/*not top row*/)
			board->connect_nodes(i, i-n);
		else
			board->connect_nodes(i, SIDE_TOP(n));
		if(!((i+1) % n == 0)/*not on right edge */)
			board->connect_nodes(i, i+1);
		else
			board->connect_nodes(i, SIDE_RIGHT(n));
		if(!(i%n == 0)/*not on left edge */)
			board->connect_nodes(i, i-1);
		else
			board->connect_nodes(i, SIDE_LEFT(n));
		if(!(i+n >= n*n)/*not bottom row*/)
			board->connect_nodes(i, i+n);
		else
			board->connect_nodes(i, SIDE_BOTTOM(n));
		
	}
	/* 'fake' nodes that are the colored sides of the board */
	board->set_node_color(SIDE_BOTTOM(n), COLOR_RED);
	board->set_node_color(SIDE_TOP(n), COLOR_RED);
	board->set_node_color(SIDE_LEFT(n), COLOR_BLUE);
	board->set_node_color(SIDE_RIGHT(n), COLOR_BLUE);
	/* all other nodes are white */
}

/* this ugly-ass function prints out the board in a nice hex-format
 * type of thing. Lots of formatting loops */
void hexboard::print_board()
{
	printf("     ");
	for(int i=0;i<size;i++)
	{
		printf("%-3d ", i);
	}
	printf("\n     ");
	for(int i=0;i<size;i++)
	{
		printf("\x1B[1;31mR   ");
	}
	cout << endl;
	printf("\x1B[37m");
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<i;j++)
			cout << "  ";
		printf("%2d \x1B[34mB", i);
		for(int j=0;j<size;j++)
		{
			cout << " ";
			
			switch(board->get_node_color(convert_coords(j, i)))
			{
				case 0:
					printf("\x1B[37m");
					cout << ".";
					break;
				case COLOR_BLUE:
					printf("\x1B[34mB");
					break;
				case COLOR_RED:
					if(convert_coords(j, i) == last)
						printf("\x1B[4;31mR\x1B[0;1m");
					else
						printf("\x1B[31mR");
					break;
			}
			printf("\x1B[37m");
			cout << "  ";
		}
		printf("\x1B[34mB");
		printf("\x1B[37m %d", i);
		cout << endl;
	}
	
	for(int i=0;i<size-1;i++)
	{
		cout << "  ";
	}
	printf("     ");	
	for(int i=0;i<size;i++)
	{
		printf("\x1B[31mR   ");
	}
	cout << endl;
	printf("\x1B[37m");
	for(int i=0;i<size-1;i++)
	{
		cout << "  ";
	}
	printf("     ");	
	for(int i=0;i<size;i++)
	{
		printf("%-3d ", i);
	}
	printf("\n");
}

int hexboard::convert_coords(int x, int y)
{
 	/* convert from cartesian to array index */
	return x + y*size;
}

int hexboard::make_move(int node, int color)
{
	/* if it's a valid move, set the color of the node */
	if(!is_valid_move(node)) return 0;
	board->set_node_color(node, color);
	board->node_data[node]=0;
	last = node;
	empty--;
	return 1;
}

void hexboard::sim_make_move(int node, int color, int current)
{
	/* if it's a valid move, set the color of the node. here we check if
	 * the "node data" has not been set by 'real' moves or by the current
	 * simulation. This optimizes it quite a bit, since we don't have to 
	 * clone a board for each iteration of the simulation */
	if(!board->node_data[node] || board->node_data[node] == current) return;
	board->set_node_color(node, color);
	board->node_data[node]=0;
	empty--;
}

int hexboard::get_random_move()
{
	vector<int> potential_moves;
	for(int i=0;i<size*size;i++)
	{
		if(is_valid_move(i))
			potential_moves.insert(potential_moves.begin(), i);
	}
	int x = rand() % potential_moves.size();
	int node = potential_moves[x];
	return node;
}

hexboard *hexboard::clone()
{
	/* copy all of the data and return a new hexboard */
	hexboard *h = new hexboard(0);
	h->size = size;
	h->empty = empty;
	h->board = new graph(size * size + 4);
	for (int i = 0;i<size*size+4;i++)
	{
		for (int j = 0;j<size*size+4;j++)
		{
			h->board->conn[i][j] = board->conn[i][j];
		}
		h->board->node_color[i] = board->node_color[i];
		h->board->node_data[i] = board->node_data[i];
	}
	return h;
}

int hexboard::simulate(int sim_num, int color, int other_player_color, int start, int end, int node)
{
	vector<int> potential_moves;
	/* a list of empty spaces on the board */
	for(int i=0;i<size*size;i++)
	{
		/* don't include the initial move */
		if(board->node_data[i] != 0 && i != node)
			potential_moves.insert(potential_moves.begin(), i);
	}
	/* make the initial move */
	sim_make_move(node, color, sim_num);
 	while(potential_moves.size() > 0 && empty > 0)
	{
		/* pick a random move */
		int m = rand() % potential_moves.size();
		node = potential_moves[m];
		vector<int>::iterator it;
		it = potential_moves.begin() + m;
		/* remove it from the empty spaces list */
		potential_moves.erase(it);
		/* other player makes a move */
		sim_make_move(node, other_player_color, sim_num);
		/* record that this move was done by this iteration of the simulation */
		board->node_data[node] = sim_num;
		/* filled up yet? */
		if(empty == 0 || potential_moves.size() == 0) break;
		/* pick a random move for the computer */
		m = rand() % potential_moves.size();
		node = potential_moves[m];
		it = potential_moves.begin() + m;
		potential_moves.erase(it);
		/* make the computer's random move, and record that it was done by this iteration */
		sim_make_move(node, color, sim_num);
		board->node_data[node] = sim_num;
	}
	/* search if we've won or not */
	int result = board->bfs(start, end, size*size, color);
	if(result == 1) 
		return 1;
	else
		return -1;
}

double hexboard::montecarlo(int color, int start, int end)
{
	vector<int> list;
	vector<double> dist;
	/* Make sure that the game wasn't won by the human player yet */
	//double ret = board->dijkstra(start, end, size*size, color, list, dist);
	//if(ret == INFINITY) return -1;
	//else if(ret == 0) return 1;
	/* human's color */
	int other_player_color = (color == COLOR_BLUE ? COLOR_RED : COLOR_BLUE);
	
	/* make a list of all the potential moves */
	set<int> potential_moves;
	for(int i=0;i<size*size;i++)
	{
		if(is_valid_move(i))
			potential_moves.insert(i);
	}
	
	/* go through all of them and find the one with the highest winning probability */
	set<int>::iterator it;
	int best_move=*(potential_moves.begin());
	double best_move_val=0;
	for(it = potential_moves.begin(); it != potential_moves.end(); ++it)
	{
		int node = *it;
		int wins=0, losses=0;
		/* clone the board, and make a a backup of some data so that
		 * we can re-use this cloned board without making a new one
		 * for each simulation */
		hexboard *sim = clone();
		int old_empty = sim->empty;
		for(int i=1;i<=num_iterations;i++) {
			sim->empty = old_empty;
			int res = sim->simulate(i, color, other_player_color, start, end, node);
			if(res == 1) wins++;
			else losses++;
		}
		delete sim;
		double p = ((double)wins*100 / ((double)wins+losses));
		
		//cout << "[" << node << " / " << size*size << "]: " << p;
		//if(debug) cout << endl;
		//else cout << "                                  \r";
		fflush(0);
		/* better than before? */
		if(p > best_move_val) {
			best_move_val = p;
			best_move = node;
		}
	}
	//cout << "                                  \rmoving: " << best_move << " with confidence " << best_move_val << endl;
	/* actually make the move */
	make_move(best_move, color);
	/* Use dijkstra to get a lot more information on if someone has won */
	/*ret = board->dijkstra(start, end, size*size, color, list, dist);
	if(ret == INFINITY) return -1;
	else if(ret == 0) return 1; */
	return best_move;
}

double hexboard::computer_move(int color, int start, int end)
{
	return montecarlo(color, start, end);
}

// -----------------------------------------------
hexboard h(0);
void init(int _n) {
    n = _n;
    //memset(taboard, 0, sizeof taboard);
    srand(0);
    //hexboard h(0);
    h.setup(n);
    h.generate_connected_graph();
}
pii decide(pii p) {
    int cur_position = n*p.first + p.second;
    h.make_move(cur_position, 0);
    int comp = h.computer_move(1, n*n, n*n+2);
    //int first = comp/n;
    //int second = comp%n;
    pii res = make_pair(comp/n, comp%n);
    return res;
}
