/* ================================================================== *
 *  Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 *
 *  Disciplina: Introdução à Programação
 *  Prof. Tiago A. Almeida
 *
 *  Lista 01 - Exercício 00 - Nota mínima na P2 para atingir média M
 *
 *  Instruções
 *  ----------
 *
 *	Este arquivo contém o código que auxiliará no desenvolvimento do
 *	exercício. Você precisará completar as partes requisitadas.
 *
 * ================================================================== *
 *	Dados do aluno:
 *
 *  RA:
 *  Nome:
 *
 * ================================================================== */

/* <<< COMPLETE AQUI >>> */
#include <stdio.h>

int main(){
	float M, notaP1, notaLista, notaP2;
	int pesoP1, pesoP2, pesoLista, somaPesos;

	scanf("%f", &M);
	scanf("%f %d", &notaP1, &pesoP1);
	scanf("%f %d", &notaLista, &pesoLista);
	scanf("%d", &pesoP2);
	somaPesos = pesoP1 + pesoP2 + pesoLista;
	notaP2 = ((M * somaPesos) - (notaP1 * pesoP1) - (notaLista * pesoLista)) / pesoP2;

	printf("%.1f\n", notaP2);

	return 0;
}
