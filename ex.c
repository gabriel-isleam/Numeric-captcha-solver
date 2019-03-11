#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

int pixel[100][100];

int cautarecifra(int l, int c)												// functie de cautare a cifrelor in matricea pixelilor
{
		if (pixel[l][c - 1] == 0)
			if (pixel[l][c - 4] == 0)
				return 1;
			else 
				return 4;
		else
			if (pixel[l + 2][c - 4] == 0)
				return 7;
			else if (pixel[l + 3][c] == 0)
				return 2;
			else if (pixel[l + 2][c - 1] == 0)
				return 0;
			else if (pixel[l + 1][c - 4] == 0)
				return 3;
			else if (pixel[l + 1][c] == 0)
				if (pixel[l + 3][c - 4] == 0)
					return 5;
				else 
					return 6;
			else
			{ 
				if (pixel[l + 3][c - 4] == 0)
					return 9;
				else 
					return 8;
			}
}

void setarecifra(int l, int c, int nr)										// functie ce seteaza elementele unei cifre cu valoarea nr
{																			// acest lucru usureaza salvarea culorilor pentru fiecare cifra
	int i, j;																// util pentru task-ul 3
	for (i = l; i <= l + 4; i++)
		for (j = c; j >= c - 4; j--)
			if (pixel[i][j] == 1)
				pixel[i][j] = nr;
}

void desenare8(int a, int b, int c)											// functie ce formeaza cifra 8 in matricea pixelilor
{
	int x = a + 4, y = b + 4, ok = 1;
	for (; a <= x; a++)
		if (ok % 2 == 1)
		{
			for (b = y - 4; b <= y; b++)
				pixel[a][b] = c;
			ok = 0;
		}
		else 
		{
			pixel[a][y] = c;
			pixel[a][y - 4] = c;
			ok = 1;
		}
}

void scrierecifra(int a, int b, int nr, int c)								// functie ce seteaza cifrele in matricea pixelilor, dupa
{																			// eliminarea celor dorite
	int x = a, y = b;
	if (nr == 1)
	{
		b = b + 4;
		for (; a <= x + 4; a++)
			pixel[a][b] = c;
	}
	else
	{
		desenare8(a, b, c);													// in afara cazului special cand cifra e 1, in restul cazurilor
		if (nr == 0)														// se deseneaza cifra 8 (ce contine toti pixelii posibili pentru  
		{																	// o cifra), apoi pentru fiecare cifra se elimina din pixelii in plus
			pixel[a + 2][b + 1] = 0;
			pixel[a + 2][b + 2] = 0;
			pixel[a + 2][b + 3] = 0;
		}
		else if (nr == 2)
		{
			pixel[a + 1][b] = 0;
			pixel[a + 3][b + 4] = 0;
		}
		else if (nr == 3)
		{
			pixel[a + 1][b] = 0;
			pixel[a + 3][b] = 0;
		}
		else if (nr == 5)
		{
			pixel[a + 1][b + 4] = 0;
			pixel[a + 3][b] = 0;
		}
		else if (nr == 6)
			pixel[a + 1][b + 4] = 0;

		else if (nr == 9)
			pixel[a + 3][b] = 0;
		else if (nr == 4)
		{
			pixel[a + 3][b] = 0;
			pixel[a + 4][b] = 0;
			for (b = y + 1; b <= y + 3; b++)
			{
				pixel[a][b] = 0;
				pixel[a + 4][b] = 0;
			}
		}
		else if (nr == 7)
		{
			for (a = x + 1; a <= x + 4; a++)
				pixel[a][b] = 0;
			for (b = y + 1; b <= y + 3; b++)
			{
				pixel[x + 2][b] = 0;
				pixel[x + 4][b] = 0;
			}
		}
	} 
}

int main()
{
	char input_filename[21];
	char task1[] = "_task1.bmp";											// extensiile corespunzatoare fiecarui task
	char task2[] = "_task2.txt";
	char task3[] = "_task3.bmp";

	fgets(input_filename, 21, stdin);										// citirea numelui fisierului bmp
	int i = 1, BLUE, GREEN, RED;
	scanf("%d%d%d", &BLUE, &GREEN, &RED);									// citirea valorilor corespunzatoare pentru colorare
	
	strcpy(input_filename + strlen(input_filename) - 1, input_filename + strlen(input_filename));		// se elimina din numele fisierului
																										// "\n"
	char output_filename[21];
	char output_filename_task2[21];
	char output_filename_task3[21];
	strcpy(output_filename,input_filename);									// realizarea numelor pentru fisierele ce trebuie realizate
	strcpy(output_filename_task2,input_filename);
	strcpy(output_filename_task3,input_filename);
	strcpy(output_filename + strlen(output_filename) - 4, task1);				// adaugarea extensiilor corespunzatoare
	strcpy(output_filename_task2 + strlen(output_filename_task2) - 4, task2);
	strcpy(output_filename_task3 + strlen(output_filename_task3) - 4, task3);

	FILE *fp1, *fp2, *fp3, *fp4;

	if ((fp1 = fopen(input_filename, "rb")) == NULL)						// se verifica daca fisierele s-au deschis cu succes
	{
		fprintf(stderr, "Can't open %s\n", input_filename);
		return -1;
	}

	if ((fp2 = fopen(output_filename, "wb")) == NULL)
	{
		fprintf(stderr, "Can't open %s\n", output_filename);
		return -1;
	}

	if ((fp4 = fopen(output_filename_task3, "wb")) == NULL)
	{
		fprintf(stderr, "Can't open %s\n", output_filename_task3);
		return -1;
	}

	struct bmp_fileheader infof;
	struct bmp_infoheader infoi;

	fread(&infof, sizeof(infof), 1, fp1);									// se copiaza file header-ul in fisierele de la task 1 si 2
	fwrite(&infof, sizeof(infof), 1, fp2);
	fwrite(&infof, sizeof(infof), 1, fp4);

	fread(&infoi, sizeof(infoi), 1, fp1);									// se copiaza info header-ul in fisierele de la task 1 si 2
	fwrite(&infoi, sizeof(infoi), 1, fp2);
	fwrite(&infoi, sizeof(infoi), 1, fp4);

	int S = infoi.width * infoi.height;										// dimensiunea totala a matricii de pixeli
	
	fseek(fp1, infof.imageDataOffset, SEEK_SET);							// setarea pointer-ului fisierului in dreptul matricii de pixeli
	fseek(fp2, infof.imageDataOffset, SEEK_SET);
	struct pixel p, culoare[S + 1], culoarecifre[100];
	struct coordonate poz[100], aux2;
	int pad;

	if (infoi.width % 4 != 0)												//calculare padding
		pad = 4 - (infoi.width * 3) % 4;
	else
		pad = 0;

	int a = infoi.height, b = 1, k;
	
	while (i <= S)
	{
		fread(&p.blue, sizeof(p.blue), 1, fp1);								// citirea culorilor pixelilor din fisierul sursa
		fread(&p.green, sizeof(p.green), 1, fp1);
		fread(&p.red, sizeof(p.red), 1, fp1);
		culoare[i] = p;														// se salveaza intr-un vector toate culorile, inclusiv alb
		
		if (p.blue != 255 || p.green != 255 || p.red != 255)				// setarea pixelilor diferiti de alb, in culoarea data
		{
			p.blue = BLUE;
			p.green = GREEN;
			p.red = RED;
			pixel[a][b] = 1;												// se formeaza o matrice de pixeli separata
		}

		fwrite(&p.blue, sizeof(p.blue), 1, fp2);							// scrierea pixelilor in fisierul corespunzator task-ului 1
		fwrite(&p.green, sizeof(p.green), 1, fp2);
		fwrite(&p.red, sizeof(p.red), 1, fp2);
		b++;
		if (i % infoi.width == 0)											// la intalnirea padding-ului se scriu in fisier valoarea 0
 		{
			
			fseek(fp1, pad, SEEK_CUR);						
			for (k = 0; k < pad; k++)
				fputc(0x00, fp2);
			a--;
			b = 1;
		}
		i++;
		
	}

	fclose(fp1);															// inchiderea fisierului sursa si a celui pentru task 2
	fclose(fp2);
	
	int nr[100], n = 0;

	for (b = infoi.width; b >= 1 ; b--)										// parcurgerea matricei de pixeli formata anterior
		for (a = 1; a <= infoi.height; a++)
			if (pixel[a][b] == 1)
			{ 
				nr[n] = cautarecifra(a, b);									// formarea vectorului de cifre in ordine inversa aparitiei lor
				poz[n].lin = a;												// salvarea pozitiei pentru fiecare cifra
				poz[n].col = b - 4;
				n++;
				setarecifra(a, b, 2);										// setarea valorii 2 pentru cifrele deja gasite pentru a nu
			}																// incurca restul cautarii

	if ((fp3 = fopen(output_filename_task2, "wt")) == NULL)
	{
		fprintf(stderr, "Can't open %s\n", output_filename_task2);
		return -1;
	}

	for (i = n - 1; i >= 0; i--)											// scrierea cifrelor in fisierul corespunzator task-ului 2
		fprintf(fp3, "%d", nr[i]);
	
	fclose(fp3);

	int aux1, numar;

	for (i = 0; i < n/2; i++)												// intoarcerea vectorului de cifre si in acelasi timp 
	{																		// a vectorului de pozitii, astfel, numerele vor aparea
		aux1 = nr[i];														// in ordinea corecta in vector		
		nr[i] = nr[n - i - 1];
		nr[n - i - 1] = aux1;
		aux2 = poz[i];
		poz[i] = poz[n - i - 1];
		poz[n - i - 1] = aux2;
	}

	for (i = 0; i < n; i++)													// salvarea culorilor numai pentru cifre in ordine
		culoarecifre[i] = culoare[(infoi.height - poz[i].lin) * infoi.width + poz[i].col + 4];

	int j, c = 2;

	while (scanf("%d",&numar) > 0)											// cat timp se citesc numere din fisier, se elimina 
	{																		// din vectorul de numere si de culori, pastrandu-se doar pozitiile
		for (i = 0; i < n; i++)
			if (numar == nr[i])
			{
				j = i;
				for (; i < n - 1; i++)
				{
					nr[i] = nr[i + 1];
					culoarecifre[i] = culoarecifre[i + 1];
				}
			i = j - 1;
			n--;
			}
	}

	i = 0;

	for (a = 1; a <= infoi.height; a++)										// revenirea la valoarea 1 pentru cifrele din matrice
			for (b = 1; b <= infoi.width; b++)
				if (pixel[a][b] == 2)
					pixel[a][b] = 1;

	for (b = 1; b <= infoi.width; b++)										// scrierea cifrelor ramase in locul celor eliminate
		for (a = 1; a <= infoi.height; a++)
			if (i == n)
				break;
			else if (poz[i].lin == a && poz[i].col == b)
			{
				if (cautarecifra(a, b + 4) == nr[i])
				{
					setarecifra(a, b + 4, c);
					c++;
				}
				else
				{
					scrierecifra(a, b, nr[i], c);
					c++;
				}
				i++;
			}

	i = 0; 
	fseek(fp4, infof.imageDataOffset, SEEK_SET);

	for (a = infoi.height; a >= 1; a--)											// scrierea matricei de pixeli in fisierul corespunzator
		for (b = 1; b <= infoi.width; b++)										// task-ului 3
		{
			i++;
			if (pixel[a][b] != 0 && pixel[a][b] != 1)
			{
				fwrite(&culoarecifre[pixel[a][b] - 2].blue, sizeof(p.blue), 1, fp4);
				fwrite(&culoarecifre[pixel[a][b] - 2].green, sizeof(p.green), 1, fp4);
				fwrite(&culoarecifre[pixel[a][b] - 2].red, sizeof(p.red), 1, fp4);
			}
			else
			{
				fputc(0xff, fp4);
				fputc(0xff, fp4);
				fputc(0xff, fp4);
			}
			if (i % infoi.width == 0)
			{
				for (k = 0; k < pad; k++)
					fputc(0x00, fp4);
			}
		}

	fclose(fp4);
	return 0;
}
	

