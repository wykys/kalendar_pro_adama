/*
 * Kalendář pro Adama
 * wykys 2015
 * verze: 1.0
 * program vypiše kalenddář ve dvouch sloupcích pro jeden rok
 * ovladani:
 * po zapnutí je uživatel vyzvám k tomu, aby zadal, kterým dnem začíná rok,
 * uživatel rok vyere zadáním čísla z intervalu <1;7> , kde 1 odpovídá Pondělí
 * a 7 odpovídá pátku. Dále je uživatel vyzván k tomu, aby zadal, zda-li je vypisovaný
 * rok přestupný či nikoliv.
 * Program se ukončí ztiskem libovolné klávesy po vypsání kalendáře.
 *
 * Tento program je určer, jako ukázka řešenídomárího úkolu na Cčkovská wykysovská sezení :)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROK	12
#define TYDEN	7

#define OBR_X	80
#define OBR_L	8
#define BUFF	OBR_X/2

char obr[OBR_L][OBR_X];
char buffer[OBR_X/2];

unsigned short int delky_mesicu[ROK] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char jmena_mesicu[ROK][9] = {
	"LEDEN",
	"UNOR",
	"BREZEN",
	"DUBEN",
	"KVETEN",
	"CERVEN",
	"CERVENEC",
	"SRPEN",
	"ZARI",
	"RIJEN",
	"LISTOPAD",
	"PROSINEC"
};

const char jmena_dnu[TYDEN][3] = {
	"Po",
	"Ut",
	"St",
	"Ct",
	"Pa",
	"So",
	"Ne"
};

void vycisti_buffer(void)
{
	int i;
	for (i=0; i<BUFF; i++)
		buffer[i] = '\0';
}

void vycisti_obr(void)
{
	int x, y;

	for (y=0; y<OBR_L; y++)
	{
		for (x=0; x<OBR_X; x++)
		{
			obr[y][x] = ' ';
		}
		obr[y][OBR_X-1] = '\0';
	}	
}

void napis_do_obr(int radek, int sloupec)
{
	int i;

	if (radek < OBR_L)
	{	
		for (i=0; buffer[i] != '\0' && i < BUFF; i++)
		{
			// levý půlka
			if (sloupec)
			{
				obr[radek][i+10] = buffer[i];
			}
			// pravý pulka
			else
			{
				obr[radek][i+50] = buffer[i];
			}		
		}
	}
	vycisti_buffer();
}

void vypis_obr(void)
{
	int y;

	putchar('\n');
	for (y=0; y<OBR_L; y++)
		printf("%s\n", obr[y]);		
}

void vypis_zahlavi_tydne(void)
{
	unsigned short int den;

	for (den=0; den<TYDEN; den++)
	{
		strcat(buffer, jmena_dnu[den]);
		strcat(buffer, " ");
	}		

	napis_do_obr(1, 0);

	for (den=0; den<TYDEN; den++)
	{
		strcat(buffer, jmena_dnu[den]);
		strcat(buffer, " ");
	}

	napis_do_obr(1, 1);
}

int main(void)
{
	int mesic, tyden, den, i = 0;
	int radek, sloupec;

	char den_str[5];

	radek = 0;
	sloupec = 1;


	vycisti_buffer();
	vycisti_obr();	
	

	printf("Zadejte, kterym dnem zacina rok (1 = Po az 7 = Ne) >>> ");
	scanf("%d", &tyden);

	printf("Zadejte, je rok prestupny? (1 = Ano, 0 = NE) >>> ");
	scanf("%d", &i);
	if (i)
	{
		delky_mesicu[1] = 29;		
	}
	
	for (mesic=0; mesic<ROK; mesic++)
	{
		radek = 0;
		snprintf(buffer, BUFF, "%s", jmena_mesicu[mesic]);
		napis_do_obr(radek, sloupec);
		vypis_zahlavi_tydne();
		radek = 2;

		
		

		for (i=1; i<tyden; i++)
			strcat(buffer, "   ");
				
		for (den=1; den<=delky_mesicu[mesic]; den++)
		{
			sprintf(den_str, "%2d ", den);
			strcat(buffer, den_str);
			if (tyden == 7)
			{
				napis_do_obr(radek, sloupec);
				radek++;
				tyden = 1;				
			}
			else
			{
				tyden++;
			}			
		}

		if (tyden != 1)
		{
			napis_do_obr(radek, sloupec);
		}

		if (sloupec)
		{
			sloupec--;
		}
		else
		{
			sloupec++;
			vypis_obr();
			vycisti_obr();
		}
	}	

	printf("\n\n");
	system("PAUSE");

	return 0;
}
