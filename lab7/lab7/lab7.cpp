#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <queue>
#include <locale.h>
#include <malloc.h>
#include <windows.h>

using namespace std;

void rand_Zap_vz_or(int** Matrix, int n) 
{
	srand(time(NULL));
	printf("Взвешаный орентированный граф\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
		{
			if (i == j) 
			{
				Matrix[i][j] = 0;
			}
			if (i < j) 
			{
				if (rand() % 100 > 50) 
				{
					Matrix[i][j] = rand() % 10;
					if (rand() % 100 > 50)
						Matrix[j][i] = 0;
					else
						Matrix[j][i] = Matrix[i][j];
				}
				else
					if (rand() % 100 > 50) 
					{
						Matrix[j][i] = rand() % 10;
						Matrix[i][j] = 0;
					}
					else 
					{
						Matrix[i][j] = 0;
						Matrix[j][i] = 0;
					}
			}
		}
}
void rand_Zap_vz_nor(int** Matrix, int n) 
{
	srand(time(NULL));
	printf("Взвешаный неорентированный граф\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
		{
			if (i == j) 
			{
				Matrix[i][j] = 0;
			}
			if (i < j) 
			{
				if (rand() % 100 > 50)
					Matrix[i][j] = rand() % 10;
				else
					Matrix[i][j] = 0;
				Matrix[j][i] = Matrix[i][j];
			}
		}
}
void rand_Zap_nor(int** Matrix, int n) 
{
	srand(time(NULL));
	printf("Не взвешаный неорентированный граф\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Matrix[i][j] = 0;
			}
			if (i < j) {
				Matrix[i][j] = rand() % 2;
				Matrix[j][i] = Matrix[i][j];
			}
		}
}
void rand_Zap_or(int** Matrix, int n) 
{
	srand(time(NULL));
	printf("Не взвешаный орентированный граф\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Matrix[i][j] = 0;
			}
			if (i < j) 
			{
				if (rand() % 100 > 50) 
				{
					Matrix[i][j] = rand() % 2;
					if (rand() % 100 > 50)
						Matrix[j][i] = 0;
					else
						Matrix[j][i] = Matrix[i][j];
				}
				else
					if (rand() % 100 > 50) 
					{
						Matrix[j][i] = rand() % 2;
						Matrix[i][j] = 0;
					}
					else 
					{
						Matrix[i][j] = 0;
						Matrix[j][i] = 0;
					}
			}
		}
}

void print_G(int** Matrix, int n) 
{
	printf("  ");
	for (int i = 0; i < n; i++)
		printf("%3d", i + 1);
	printf("\n\n");
	for (int i = 0; i < n; i++) {
		printf("%2d", i + 1);
		for (int j = 0; j < n; j++) {

			printf("%3d", Matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");


}

void dsit_0(int* Matrix, int n) 
{
	for (int i = 0; i < n; i++)
		Matrix[i] = -1;
}

void BFSD_vz(int** Matrix, int* dist, int n, int v) 
{
	queue <int> Q;
	Q.push(v);
	dist[v] = 0;
	while (Q.empty() == false) 
	{
		v = Q.front();
		Q.pop();
		printf("%d ", v + 1);
		for (int i = 0; i < n; i++) 
		{
			if ((Matrix[v][i] != 0) && (dist[i] > (dist[v] + Matrix[v][i]))) 
			{
				Q.push(i);
				dist[i] = dist[v] + Matrix[v][i];
			}
		}
	}
	printf("\n");
}

void BFSD(int** Matrix, int* dist, int n, int v)
{
	queue <int> Q;
	Q.push(v);
	dist[v] = 0;
	while (Q.empty() == false) 
	{
		v = Q.front();
		Q.pop();
		printf("%d ", v + 1);
		for (int i = 0; i < n; i++) 
		{
			if ((Matrix[v][i] == 1) && dist[i] == -1) 
			{
				Q.push(i);
				dist[i] = dist[v] + 1;
			}
		}
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	if (argc != 3) 
	{
		printf("Error: found %d arguments. Needs exactly 2", argc - 1);
		exit(1);
	}

	int N = 1;
	printf("введите кол-во вершин\n");
	scanf("%d", &N);

	int** G = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++) {
		G[i] = (int*)malloc(N * sizeof(int));
	}

	int* dist;
	dist = (int*)malloc(N * sizeof(int));

	
	


	switch (atoi(argv[1]))
	{
	case 0: switch (atoi(argv[2])) 
		{
	case 0:rand_Zap_nor(G, N);
		break;
	case 1:rand_Zap_or(G, N);
		break;
		}
		  break;
	case 1:switch (atoi(argv[2])) 
		{
	case 0:rand_Zap_vz_nor(G, N);
		break;
	case 1:rand_Zap_vz_or(G, N);
		break;
		}
		  break;
	}

	print_G(G, N);

	switch (atoi(argv[1]))
	{
	case 0:for (int i = 0; i < N; i++) 
		{
		dsit_0(dist, N);
		printf("от вершины %d\n", i + 1);
		BFSD(G, dist, N, i);
		for (int j = 0; j < N; j++)
			{
			if (dist[j] != -1)
				printf("%d \t", dist[j]);
			else
				printf("нет прохода \t");
			}
		printf("\n");

		}
		  break;
	case 1:for (int i = 0; i < N; i++) 
		{
		dsit_0(dist, N);
		printf("от вершины %d\n", i + 1);
		BFSD_vz(G, dist, N, i);
		for (int j = 0; j < N; j++)
			{
			if (dist[j] != -1)
				printf("%d \t", dist[j]);
			else
				printf("нет прохода \t");
			}
		printf("\n");
		}
		  break;
	}

	for (int i = 0; i < N; i++) {
		free(G[i]);
	}
	free(G);
	free(dist);

	getchar();
}
