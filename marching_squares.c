#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIGMA 200
#define RS 4

struct rgb {
	int r, g, b;
};

void free_a(int n, struct rgb ***a)
{//free memory a
	if (*a) {
		for (int i = 0; i < n; ++i)
			free((*a)[i]);
		free(*a);
		*a = NULL;
	}
}

void free_grid(int n, int ***grid)
{//free memory grid
	if (*grid) {
		for (int i = 0; i < n / 4 + 1; ++i)
			free((*grid)[i]);
		free(*grid);
		*grid = NULL;
	}
}

void READ(int *n, int *m, int *limit, struct rgb ***a)
{
	char format[10] = {0};
	int pixel_invalid = 0, ret = 0;

	scanf("%s", format);
	if (format[0] == 'P' && format[1] == '3') {
		scanf("%d %d", n, m);
		//alocarea dinamica a imaginii
		*a = (struct rgb **)calloc(*n, sizeof(struct rgb *));
		for (int i = 0; i < *n; ++i)
			(*a)[i] = (struct rgb *)calloc(*m, sizeof(struct rgb));

		scanf("%d", limit);
		//citirea imaginii
		for (int i = 0; i < *n; ++i) {
			for (int j = 0; j < *m; ++j) {
				if (scanf("%d %d %d",
						  &(*a)[i][j].r,
						  &(*a)[i][j].g,
						  &(*a)[i][j].b) == -1)
					ret = 1;
				//daca pixelul are vreo culoare mai mica de 0 sau
				//mai mare de limit este invalid
				if ((*a)[i][j].r < 0 || (*a)[i][j].g < 0 || (*a)[i][j].b < 0) {
					pixel_invalid = 1;
				}
				if ((*a)[i][j].r > *limit || (*a)[i][j].g > *limit) {
					pixel_invalid = 1;
				}
				if ((*a)[i][j].b > *limit) {
					pixel_invalid = 1;
				}
			}
		}
		//verific daca exista pixel invalid
		if (pixel_invalid == 1) {
			printf("Eroare: valoare pixel necorespunzatoare\n");
			free_a(*n, a);
			exit(0);
		}
		//verific daca citeste prea putini pixeli
		if (ret == 1) {
			printf("Eroare: eroare citire pixeli\n");
			free_a(*n, a);
			exit(0);
		}

	} else {//formatul imaginii este gresit
		printf("Eroare: trebuie sa fie P3\n");
		exit(0);
	}
}

void WRITE(int n, int m, int limit, struct rgb **a)
{
	printf("P3\n");
	printf("%d %d\n", n, m);
	printf("%d\n", limit);
	for (int i = 0; i < n; ++i) {//afisez matricea
		for (int j = 0; j < m; ++j) {
			printf("%d %d %d\n", a[i][j].r, a[i][j].g, a[i][j].b);
		}
	}
}

void INIT_CONTUR(struct rgb (*contur)[16][4][4])
{
	struct rgb w = {0, 0, 0};
	struct rgb b = {180, 180, 180};
	struct rgb n = {255, 255, 255};
	//construiesc matricea de pattern-uri
	struct rgb c[16][4][4] = {
		{//0
			{w, w, w, w}, {w, w, w, w}, {w, w, w, w}, {w, w, w, w}
		},
		{//1
			{w, w, w, w}, {w, w, w, w}, {n, w, w, w}, {b, n, w, w}
		},
		{//2
			{w, w, w, w}, {w, w, w, w}, {w, w, w, n}, {w, w, n, b}
		},
		{//3
			{w, w, w, w}, {w, w, w, w}, {n, n, n, n}, {b, b, b, b}
		},
		{//4
			{w, w, n, b}, {w, w, w, n}, {w, w, w, w}, {w, w, w, w}
		},
		{//5
			{w, w, n, b}, {w, w, w, n}, {n, w, w, w}, {b, n, w, w}
		},
		{//6
			{w, w, n, b}, {w, w, n, b}, {w, w, n, b}, {w, w, n, b}
		},
		{//7
			{w, n, b, b}, {n, b, b, b}, {b, b, b, b}, {b, b, b, b}
		},
		{//8
			{b, n, w, w}, {n, w, w, w}, {w, w, w, w}, {w, w, w, w}
		},
		{//9
			{b, n, w, w}, {b, n, w, w}, {b, n, w, w}, {b, n, w, w}
		},
		{//10
			{b, n, w, w}, {n, w, w, w}, {w, w, w, n}, {w, w, n, b}
		},
		{//11
			{b, b, n, w}, {b, b, b, n}, {b, b, b, b}, {b, b, b, b}
		},
		{//12
			{b, b, b, b}, {n, n, n, n}, {w, w, w, w}, {w, w, w, w}
		},
		{//13
			{b, b, b, b}, {b, b, b, b}, {b, b, b, n}, {b, b, n, w}
		},
		{//14
			{b, b, b, b}, {b, b, b, b}, {n, b, b, b}, {w, n, b, b}
		},
		{//15
			{n, n, n, n}, {n, n, n, n}, {n, n, n, n}, {n, n, n, n}
		}
	};

	//copiez matricea initializata mai sus in matricea primita ca
	//parametru cu referinta
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				(*contur)[i][j][k].r = c[i][j][k].r;
				(*contur)[i][j][k].g = c[i][j][k].g;
				(*contur)[i][j][k].b = c[i][j][k].b;
			}
		}
	}
}

int inmat(int n, int m, int i, int j)
{
	//verific daca elementul de pe pozitiile respective
	//se incadreaza in matrice
	return i >= 0 && i < n && j >= 0 && j < m;
}

void GRID(int n, int m, struct rgb **a, int ***grid)
{
	//eliberez memoria gridului anterior
	free_grid(n, grid);

	int ngr = n / 4 + 1;
	int mgr = m / 4 + 1;
	//alocarea dinamica a gridului
	*grid = (int **)calloc(ngr, sizeof(int *));
	for (int i = 0; i < ngr; ++i)
		(*grid)[i] = (int *)calloc(mgr, sizeof(int));
	//calculez media aritmetica a vecinilor valizi
	for (int i = 0; i <= n; i = i + 4) {
		for (int j = 0; j <= m; j = j + 4) {
			int x = i / 4, y = j / 4, cnt = 0, sum = 0;

			if (inmat(n, m, i, j)) { //element mijloc
				cnt++;
				sum = sum + (a[i][j].r + a[i][j].g + a[i][j].b) / 3;
			}
			if (inmat(n, m, i + 1, j + 1)) { //element dreapta jos
				cnt++;
				sum = sum + (a[i + 1][j + 1].r
				+ a[i + 1][j + 1].g + a[i + 1][j + 1].b) / 3;
			}
			if (inmat(n, m, i - 1, j + 1)) { //element dreapta sus
				cnt++;
				sum = sum + (a[i - 1][j + 1].r
				+ a[i - 1][j + 1].g + a[i - 1][j + 1].b) / 3;
			}
			if (inmat(n, m, i + 1, j - 1)) { //element stanga jos
				cnt++;
				sum = sum + (a[i + 1][j - 1].r
				+ a[i + 1][j - 1].g + a[i + 1][j - 1].b) / 3;
			}
			if (inmat(n, m, i - 1, j - 1)) {//element stanga sus
				cnt++;
				sum = sum + (a[i - 1][j - 1].r
				+ a[i - 1][j - 1].g + a[i - 1][j - 1].b) / 3;
			}
			//calculez valoarea propriu-zisa din grid
			if (cnt != 0 && sum / cnt <= SIGMA)
				(*grid)[x][y] = 1;
			else
				(*grid)[x][y] = 0;
		}
	}
}

void MARCH(int n, int m,
		   struct rgb ***a,
		   int ***grid,
		   struct rgb (*contur)[16][4][4])
{
	int pattern = 0;

	//recalculare grid si init_contur
	free_grid(n, grid);
	GRID(n, m, *a, grid);
	INIT_CONTUR(contur);

	for (int i = 0; i < n / 4; ++i) {
		for (int j = 0; j < m / 4; ++j) {
			//calculare indice pattern si adaugarea lui in
			//matricea initiala
			pattern = (*grid)[i + 1][j] + (*grid)[i + 1][j + 1] * 2
					+ (*grid)[i][j + 1] * 4 + (*grid)[i][j] * 8;
			for (int k = i * 4; k < (i + 1) * 4; ++k) {
				for (int l = j * 4; l < (j + 1) * 4; ++l) {
					(*a)[k][l] = (*contur)[pattern][k - i * 4][l - j * 4];
				}
			}
		}
	}
	printf("Marching Squares aplicat cu succes [%d-%d]\n", n, m);
}

void RESIZE(int *n, int *m, struct rgb ***a)
{
	struct rgb **new_a;
	int copyn = *n;

	*n = *n * 4;
	*m = *m * 4;
	//alocare dinamica noua matrice
	new_a = (struct rgb **)calloc(*n, sizeof(struct rgb *));
	for (int i = 0; i < *n; ++i)
		new_a[i] = (struct rgb *)calloc(*m, sizeof(struct rgb));
	//copiere element din matricea initiala de 16 ori in matricea noua
	for (int i = 0; i < *n / 4; ++i) {
		for (int j = 0; j < *m / 4; ++j) {
			for (int k = i * 4; k < (i + 1) * 4; ++k) {
				for (int l = j * 4; l < (j + 1) * 4; ++l)
					new_a[k][l] = (*a)[i][j];
			}
		}
	}
	//copiere in a
	free_a(copyn, a);
	*a = new_a;
	printf("Imagine redimensionata cu succes [%d-%d]\n", *n, *m);
}

void EXIT(int n, struct rgb ***a, int ***grid)
{
	//afisare mesaj si free matrice
	printf("Gigel a terminat\n");
	free_a(n, a);
	free_grid(n, grid);
}

int main(void)
{
	int n = 0, m = 0, limit = 0, read = 0;
	struct rgb **a = NULL, contur[16][4][4] = {0};
	int **grid = NULL;
	char op[15] = {0};

	while (scanf("%s", op) != EOF) {
		//fprintf(stderr, "%s\n", op);
		if (strcmp(op, "READ") == 0) { //citire matrice
			free_a(n, &a);
			free_grid(n, &grid);
			READ(&n, &m, &limit, &a);
			read = 1;
		} else if (strcmp(op, "WRITE") == 0) { //scriere matrice
			if (read == 1) {
				printf("Imagine citita cu succes [%d-%d]\n", n, m);
				read = 0;
			}
			WRITE(n, m, limit, a);
		} else if (strcmp(op, "INIT_CONTUR") == 0) { //init_contur
			if (read == 1) {
				printf("Imagine citita cu succes [%d-%d]\n", n, m);
				read = 0;
			}
			INIT_CONTUR(&contur);
			for (int i = 0; i < 16; ++i) { //afisare pattern
				printf("P3\n");
				printf("4 4\n");
				printf("255\n");
				for (int j = 0; j < 4; ++j) {
					for (int k = 0; k < 4; ++k) {
						printf("%d %d %d\n",
							   contur[i][j][k].r,
							   contur[i][j][k].g,
							   contur[i][j][k].b);
					}
				}
			}
		} else if (strcmp(op, "GRID") == 0) {//calculare grid
			if (read == 1) {
				printf("Imagine citita cu succes [%d-%d]\n", n, m);
				read = 0;
			}
			GRID(n, m, a, &grid);
			printf("Grid calculat cu succes [%d-%d]\n", n / 4, m / 4);
			for (int i = 0; i < n / 4; ++i) {//afisare grid
				for (int j = 0; j < m / 4; ++j)
					printf("%d ", grid[i][j]);
				printf("\n");
			}
		} else if (strcmp(op, "MARCH") == 0) {//aplicarea algoritmului march
			if (read == 1) {
				printf("Imagine citita cu succes [%d-%d]\n", n, m);
				read = 0;
			}
			MARCH(n, m, &a, &grid, &contur);
		} else if (strcmp(op, "RESIZE") == 0) {//redimensionarea matricei
			if (read == 1) {
				printf("Imagine citita cu succes [%d-%d]\n", n, m);
				read = 0;
			}
			RESIZE(&n, &m, &a);
		} else if (strcmp(op, "EXIT") == 0) {//final de program
			if (read == 1) {
				printf("Imagine citita cu succes [%d-%d]\n", n, m);
				read = 0;
			}
			EXIT(n, &a, &grid);
			exit(0);
		} else {//eroare prea multi pixeli
			printf("Eroare: eroare citire pixeli\n");
			free_a(n, &a);
			free_grid(n, &grid);
			exit(0);
		}
	}
	return 0;
}
