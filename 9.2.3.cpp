#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stack>
#include <iostream>


void BFSD(int v_start, int n, int** G, int* dist) {
	int v;

	using namespace std;
	queue <int> Q;

	Q.push(v_start);
	dist[v_start] = 0;
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();

		for (int i = 1; i <= n; i++) {
			if ((G[v][i] == 1) && (dist[v] + G[v][i] < dist[i])) {
				Q.push(i);
				dist[i] = dist[v] + G[v][i];
			}
		}
	}

	return;
}

void DFSD(int v, int n, int** G, int* dist) {
	v = 1;
	
	using namespace std;
	stack <int> s;

	dist[v] = 0;
	s.push(v);
	while (!s.empty()) {
		v = s.top();
		s.pop();
		for (int i = n; i > 0; i--) {
			if ((G[v][i] == 1) && (dist[v] + 1 < dist[i])) {
				s.push(i);
				dist[i] = dist[v] + 1;
			}
		}
	}

	return;
}




int main() {
	int n, v_start;
	int comp_sv = 0;
	float Time_DFSD, Time_BFSD;

	setlocale(0, "rus");

	printf("  --------------------------------------------------------------------------------------------------\n");
	printf("  |  порядок графа     |               Time DFSD                |              Time BFSD           | \n");


	n = 100;

	while (n < 1000) {

		int** G = (int**)malloc(n * sizeof(int*));
		for (int i = 1; i <= n; i++) {
			G[i] = (int*)malloc(n * sizeof(int));
		}

		int* dist = (int*)malloc(n * sizeof(int*));
		for (int i = 1; i <= n; i++) {
			dist[i] = 1000;
		}


		srand(time(0));
		for (int i = 1; i <= n; i++) {					//формирование матрицы смежности М
			for (int j = 1; j <= n; j++) {
				if (j >= i) {
					if (i == j) G[i][j] = 0;
					else {
						G[i][j] = rand() % 2;
						G[j][i] = G[i][j];
					}
				}
			}
		}

		clock_t start1 = clock();

		v_start = 1;									//обход в глубину
		DFSD(v_start, n, G, dist);

		clock_t end1 = clock();

		Time_DFSD = ((double)(end1 - start1) / CLOCKS_PER_SEC);
		



		for (int i = 1; i <= n; i++) {
			dist[i] = 1000;
		}



		clock_t start2 = clock();
		
		v_start = 1;										//обход в ширину
		BFSD(v_start, n, G, dist);
		
		clock_t end2 = clock();

		Time_BFSD = ((double)(end2 - start2) / CLOCKS_PER_SEC);



		printf("  ---------------------+----------------------------------------+----------------------------------|\n");
		printf("  |        %d         |                %f                |               %f           |\n", n, Time_DFSD, Time_BFSD);



		n = n + 100;
	}
	printf("  --------------------------------------------------------------------------------------------------\n");

	return 0;
}
