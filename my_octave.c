//Copyright 2022 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <stdlib.h>
#define MOD 10007

//alocarea unei matrici si verificarea daca operatiunea se poate efectua
void alloc_matrix(int n, int m, int ***s)
{
	(*s) = (int **)malloc(n * sizeof(int *));

	if (!(*s)) {
		free(*s);
		return;
	}

	for (int i = 0; i < n; i++) {
		(*s)[i] = (int *)malloc(m * sizeof(int));

		if (!(*s)[i]) {
			for (int j = 0; j < i; j++)
				free((*s)[j]);
			free(*s);
			return;
		}
	}
}

//realocarea unei matrici
void realloc_matrix(int n, int m, int ***s)
{
	(*s) = (int **)realloc((*s), n * sizeof(int *));
	if (!(*s)) {
		free(*s);
		return;
	}

	for (int i = 0; i < n; i++) {
		(*s)[i] = (int *)realloc((*s)[i], m * sizeof(int));
		if (!(*s)[i]) {
			for (int j = 0; j < i; j++)
				free((*s)[j]);
			free(*s);
			return;
		}
	}
}

void read_matrix(int n, int m, int **s)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &s[i][j]);
}

//realocarea blocului de matrice si a vectorior care contin date despre matrice
void realocare(int nr, int ****s, int **i_linie, int **i_coloana, int **suma)
{
	(*s) = (int ***)realloc((*s), (nr + 1) * sizeof(int **));
	if (!(*s))
		return;

	(*i_linie) = (int *)realloc((*i_linie), (nr + 1) * sizeof(int));
	if (!(*i_linie))
		return;

	(*i_coloana) = (int *)realloc((*i_coloana), (nr + 1) * sizeof(int));
	if (!(*i_coloana))
		return;

	(*suma) = (int *)realloc((*suma), (nr + 1) * sizeof(int));
	if (!(*suma))
		return;
}

//eliberarea unei matrice din bloc
void free_matrix(int n, int ***s, int index)
{
	for (int i = 0; i < n; i++)
		free(s[index][i]);
	free(s[index]);
}

//eliberarea unei matrice auxiliare
void free_aux(int n, int **aux)
{
	for (int i = 0; i < n; i++)
		free(aux[i]);
	free(aux);
}

//inmultirea a 2 matrice din bloc
void multiply_mat(int *i_lin, int *i_col, int ***s, int i1, int i2, int index)
{
	int **aux;
	alloc_matrix(i_lin[index], i_col[index], &aux);
	//inmultirea matricelor de la pozitia i1, respectiv i2
	for (int i = 0; i < i_lin[index]; i++) {
		for (int j = 0; j < i_col[index]; j++) {
			aux[i][j] = 0;
			for (int k = 0; k < i_lin[i2]; k++) {
				aux[i][j] += (s[i1][i][k] * s[i2][k][j]);
				aux[i][j] %= MOD;
				if (aux[i][j] < 0)
					aux[i][j] += MOD;
			}
		}
	}
	//pastrarea rezultatului la pozitia data din blocul de matrice
	for (int i = 0; i < i_lin[index]; i++)
		for (int j = 0; j < i_col[index]; j++)
			s[index][i][j] = aux[i][j];

	free_aux(i_lin[index], aux);
}

//transpunerea unei matrice
void transpusa(int ***s, int *i_linie, int *i_coloana, int *index, int nr)
{
	int **aux;
	int i, j;
	scanf("%d", index);
	//abordarea cazului in care operatia nu poate fi efectuata
	if ((*index) < 0 || (*index) >= nr) {
		printf("No matrix with the given index\n");
	} else {
		alloc_matrix(i_coloana[(*index)], i_linie[(*index)], &aux);
		//transpunerea folosind o matrice auxiliara
		for (i = 0; i < i_linie[(*index)]; i++)
			for (j = 0; j < i_coloana[(*index)]; j++)
				aux[j][i] = s[(*index)][i][j];

		free_matrix(i_linie[(*index)], s, (*index));
		alloc_matrix(i_coloana[(*index)], i_linie[(*index)], &s[(*index)]);

		//pastrarea rezultatului la pozitia data din blocul de matrice
		for (i = 0; i < i_coloana[(*index)]; i++)
			for (j = 0; j < i_linie[(*index)]; j++)
				s[(*index)][i][j] = aux[i][j];

	int aux1;
	//interschimbarea valorilor din vectorii de dimensiuni
	aux1 = i_linie[(*index)];
	i_linie[(*index)] = i_coloana[(*index)];
	i_coloana[(*index)] = aux1;

	free_aux(i_linie[(*index)], aux);
	}
}

//redimensionarea unei matrice
void task_c(int ***s, int index, int *i_linie, int *i_coloana, int nr)
{
	int *index_l, *index_c, nl, nc, i, j;
	//abordarea cazului in care operatia nu poate fi efectuata
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");

	int x;

	 scanf("%d", &nl);
	for (i = 0; i < nl ; i++)
		scanf("%d", &x);

	scanf("%d", &nc);
	for (i = 0; i < nc; i++)
		scanf("%d", &x);
	} else {
		//citim si stocam datele
		scanf("%d", &nl);

		index_l = (int *)malloc(nl * sizeof(int));

		for (i = 0; i < nl; i++)
			scanf("%d", &index_l[i]);

		scanf("%d", &nc);

		index_c = (int *)malloc(nc * sizeof(int));

		for (i = 0; i < nc; i++)
			scanf("%d", &index_c[i]);

		int **aux;
		alloc_matrix(nl, nc, &aux);

		//dam auxiliarei valorile de pe liniile si coloanele mentionate
		for (i = 0; i < nl; i++)
			for (j = 0; j < nc; j++)
				aux[i][j] = s[index][index_l[i]][index_c[j]];
		//eliberam matricea dim memorie
		free_matrix(i_linie[index], s, index);
		//reconstruim matricea cu noile dimensiuni
		alloc_matrix(nl, nc, &s[index]);
		//pastrarea rezultatului la pozitia data din blocul de matrice
		for (i = 0; i < nl; i++)
			for (j = 0; j < nc; j++)
				s[index][i][j] = aux[i][j];
		//interschimbarea valorilor din vectorii de dimensiuni
		i_linie[index] = nl;
		i_coloana[index] = nc;
		free(index_l);
		free(index_c);

		free_aux(nl, aux);
	}
}

void suma_matrice(int ***s, int *suma, int index, int *i_linie, int *i_coloana)
{
	suma[index] = 0;
	for (int i = 0; i < i_linie[index]; i++)
		for (int j = 0; j < i_coloana[index]; j++) {
			suma[index] += s[index][i][j];
			suma[index] %= MOD;
			}
	if (suma[index] < 0)
		suma[index] += MOD;
}

//interschimbarea a 2 matrice din bloc
void schimb(int ***s, int *i_linie, int *i_coloana, int k, int l)
{
	int i, j;
	int **aux;
	alloc_matrix(i_linie[k], i_coloana[k], &aux);
	//ne folosim de o matrice auxiliara pentru a pastra valorile
	for (i = 0; i < i_linie[k]; i++)
		for (j = 0; j < i_coloana[k]; j++)
			aux[i][j] = s[k][i][j];

	free_matrix(i_linie[k], s, k);
	//redimensionam matricea
	alloc_matrix(i_linie[l], i_coloana[l], &s[k]);

	for (i = 0; i < i_linie[l]; i++)
		for (j = 0; j < i_coloana[l]; j++)
			s[k][i][j] = s[l][i][j];

	free_matrix(i_linie[l], s, l);

	alloc_matrix(i_linie[k], i_coloana[k], &s[l]);

	for (i = 0; i < i_linie[k]; i++)
		for (j = 0; j < i_coloana[k]; j++)
			s[l][i][j] = aux[i][j];

	free_aux(i_linie[k], aux);
	//interschimbarea valorilor din vectorii de dimensiuni
	int aux1;
	aux1 = i_linie[k];
	i_linie[k] = i_linie[l];
	i_linie[l] = aux1;

	aux1 = i_coloana[k];
	i_coloana[k] = i_coloana[l];
	i_coloana[l] = aux1;
}

//afisarea unei matrice din bloc
void task_p(int *index, int *i_linie, int *i_coloana, int ***s, int nr)
{
	scanf("%d", index);
			if (*index < nr && *index >= 0) {
				for (int i = 0; i < i_linie[(*index)]; i++) {
					for (int j = 0; j < i_coloana[(*index)]; j++)
						printf("%d ", s[(*index)][i][j]);
					printf("\n");
				}
			} else {
				//abordarea cazului in care operatia nu poate fi efectuata
				printf("No matrix with the given index\n");
			}
}

//alocarea blocului de matrice si a vectorior care contin date despre matrice
void alocare(int **i_linie, int **i_coloana, int **suma)
{
		*i_linie = (int *)malloc(sizeof(int));
		if (!(*i_linie))
			return;

		*i_coloana = (int *)malloc(sizeof(int));
		if (!(*i_coloana))
			return;
		*suma = (int *)malloc(sizeof(int));
		if (!(*suma))
			return;
}

//generarea matricei identitate, folosita pentru ridicarea la putere
void identic(int ***s, int *i_linie, int *i_coloana, int index)
{
	for (int i = 0; i < i_linie[index]; i++)
		for (int j = 0; j < i_coloana[index]; j++)
			if (i == j)
				s[index][i][j] = 1;
			else
				s[index][i][j] = 0;
}

//ridicarea la putere in timp logaritmic
void multiply_logarithmic(int n, int *i_l, int *i_c, int ***s, int idx, int nr)
{
	i_l[nr] = i_l[idx];
	i_c[nr] = i_c[idx];
	//am adaugat o matrice auxiliara la finalul blocului
	alloc_matrix(i_l[idx], i_c[idx], &s[nr]);
	//ii dam valoarea matricei identitate
	identic(s, i_l, i_c, nr);

	while (n > 1) {
		if (n % 2 != 0) {
			multiply_mat(i_l, i_c, s, nr, idx, nr);
			//daca numarul este impar, auxiliara devine matricea data
			n--;
		} else {
			//daca numarul este par, se ridica la puterea a 2-a matricea
			multiply_mat(i_l, i_c, s, idx, idx, idx);
			n = n / 2;
		}
	}
	//inmultim matricea cu auxiliara
	multiply_mat(i_l, i_c, s, idx, nr, idx);
	free_matrix(i_l[nr], s, nr);
}

//eliberarea tuturor rerurselor, la finalul programului
void free_final(int ***s, int *i_linie, int *i_coloana, int *suma, int nr)
{
	for (int i = 0; i < nr; i++)
		free_matrix(i_linie[i], s, i);

	free(s);
	free(i_coloana);
	free(i_linie);
	free(suma);
}

//ordonarea matricelor in functie de suma
void task_o(int nr, int ***s, int *suma, int *i_l, int *i_c)
{
	//calcularea sumei pentru toate matricele
	for (int i = 0; i < nr; i++)
		suma_matrice(s, suma, i, i_l, i_c);
	//sortarea
	for (int i = 0; i < nr - 1; i++)
		for (int j = i + 1; j < nr; j++)
			if (suma[i] > suma[j]) {
				//interschimbarea matricelor
				schimb(s, i_l, i_c, i, j);
				//interschimbarea sumelor
				int aux;
				aux = suma[i];
				suma[i] = suma[j];
				suma[j] = aux;
			}
}

//afisarea dimensiunilor unei matrice din bloc
void task_d(int nr, int *i_linie, int *i_coloana)
{
	int index;
	scanf("%d", &index);
			if (index < nr && index >= 0)
				printf("%d %d\n", i_linie[index], i_coloana[index]);
			else
				//abordarea cazului in care operatia nu poate fi efectuata
				printf("No matrix with the given index\n");
}

//abordarea cazului in care operatia de ridicare la putere nu poate fi efectuata
void task_r(int *index, int *pow, int *i_linie, int *i_coloana, int nr, int *ok)
{
	scanf("%d", index);
			if (*index < 0 || *index >= nr) {
				printf("No matrix with the given index\n");
				*ok = 0;
			} else if (i_linie[*index] != i_coloana[*index]) {
				printf("Cannot perform matrix multiplication\n");
				*ok = 0;
			}
			scanf("%d", pow);
			if (*pow <= 0) {
				printf("Power should be positive\n");
				*ok = 0;
			}
}

//operatia de inmultire nu se poate efectua
void task_m(int *i_linie, int *i_coloana, int *index1, int *index2, int *ok)
{
	scanf("%d%d", index1, index2);
			if (*index1 < 0 || *index2 < 0) {
				printf("No matrix with the given index\n");
				*ok = 0;
			} else if (i_coloana[*index1] != i_linie[*index2]) {
				printf("Cannot perform matrix multiplication\n");
				*ok = 0;
			}
}

int main(void)
{
	int n, m, ***s, nr = 0, *i_linie, *i_coloana, *suma;
	int index1, index2, index, pow;
	char x;
	s = (int ***)malloc(sizeof(int **)); //alocarea initiala
	alocare(&i_linie, &i_coloana, &suma);
	scanf("%s", &x);
	while (x != 'Q') {
		if (x == 'L') {
			scanf("%d%d", &n, &m);
			if (nr != 0) //caz in care deja exista o matrice in bloc
				realocare(nr, &s, &i_linie, &i_coloana, &suma);
			//formam matricea si ii dam dimensiunile corespunzatoare
			i_linie[nr] = n, i_coloana[nr] = m;
			alloc_matrix(n, m, &s[nr]);
			read_matrix(n, m, s[nr]);
			nr++;
		} else if (x == 'D') {
			task_d(nr, i_linie, i_coloana);
		} else if (x == 'P')  {
			task_p(&index, i_linie, i_coloana, s, nr);
		} else if (x == 'M') {
			int ok = 1;
			task_m(i_linie, i_coloana, &index1, &index2, &ok);
			if (ok == 1) {
				realocare(nr, &s, &i_linie, &i_coloana, &suma);
				//formam matricea si ii dam dimensiunile corespunzatoare
				i_linie[nr] = i_linie[index1];
				i_coloana[nr] = i_coloana[index2];
				alloc_matrix(i_linie[index1], i_coloana[index2], &s[nr]);
				//inmultirea
				multiply_mat(i_linie, i_coloana, s, index1, index2, nr);
				nr++;
			}
		} else if (x == 'T') {
			transpusa(s, i_linie, i_coloana, &index1, nr);
		} else if (x == 'C') {
			int index;
			scanf("%d", &index);
				{task_c(s, index, i_linie, i_coloana, nr);
			}
		} else if (x == 'O') {
			task_o(nr, s, suma, i_linie, i_coloana);

		} else if (x == 'R') {
			int ok = 1;
			task_r(&index, &pow, i_linie, i_coloana, nr, &ok);
			if (ok == 1) {
				//formam matricea auxiliara
				realocare(nr, &s, &i_linie, &i_coloana, &suma);
				multiply_logarithmic(pow, i_linie, i_coloana, s, index, nr);
				//redimensionam blocul, dupa ce am eliberat matricea auxiliara
				s = (int ***)realloc(s, (nr) * sizeof(int **));
			}
		} else if (x == 'F') {
			scanf("%d", &index);
			if (index >= nr || index < 0) {
				printf("No matrix with the given index\n");
			} else {
				//aducem cu o pozitie in urma toate matricele
				for (int i = index; i < nr - 1; i++)
					schimb(s, i_linie, i_coloana, i, i + 1);
				//eliberam ultima matrice (duplicat)
				free_matrix(i_linie[nr - 1], s, nr - 1);
				//realocam blocul
				s = (int ***)realloc(s, (nr) * sizeof(int **));
				nr--;
			}
		} else {//primirea unui caracter nevalid
			printf("Unrecognized command\n");
		}
		scanf("%s", &x);
	}
	free_final(s, i_linie, i_coloana, suma, nr);
	return 0;
}
