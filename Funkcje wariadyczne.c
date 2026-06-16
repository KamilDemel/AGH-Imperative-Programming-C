#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int compare_doubles(const void *a, const void *b) {
	double arg1 = *(const double*)a;
	double arg2 = *(const double*)b;
	if (arg1 < arg2) return -1;
	if (arg1 > arg2) return 1;
	return 0;
}

double sum_var (int number, ...) {
	va_list arg;
	double suma = 0;
	va_start(arg,number);
	for (int i = 0; i < number; i++) {
		double kolejna_liczba = va_arg(arg,double);
		suma = suma + kolejna_liczba;
	}
	va_end(arg);
	return suma;
}

double average_var (int number, ...) {
	va_list arg;
	double suma = 0;
	va_start(arg,number);
	for (int i = 0; i < number; i++) {
		double kolejna_liczba = va_arg(arg,double);
		suma = suma + kolejna_liczba;
	}
	va_end(arg);
	return suma / number;
}

double median_var (int number, ...) {
	va_list arg;
	va_start(arg,number);
	double tablica[number];
	for (int i = 0; i < number; i++) {
		double kolejna_liczba = va_arg(arg,double);
		tablica[i] = kolejna_liczba;
	}
	va_end(arg);
	qsort(tablica,number,sizeof(double),compare_doubles);
	int mid_element = number / 2;
	if (number % 2 == 1) {
		return tablica[mid_element];
	}
	return (tablica[mid_element] + tablica[mid_element - 1]) / 2.0;
}

double min_var (int number, ...) {
	va_list arg;
	va_start(arg,number);
	double min_wartosc = va_arg(arg,double);
	for (int i = 1; i < number; i++) {
		double kolejna_liczba = va_arg(arg,double);
		if (kolejna_liczba < min_wartosc) {
			min_wartosc = kolejna_liczba;
		}
	}
	va_end(arg);
	return min_wartosc;
}

double max_var (int number, ...) {
	va_list arg;
	va_start(arg,number);
	double max_wartosc = va_arg(arg,double);
	for (int i = 1; i < number; i++) {
		double kolejna_liczba = va_arg(arg,double);
		if (kolejna_liczba > max_wartosc) {
			max_wartosc = kolejna_liczba;
		}
	}
	va_end(arg);
	return max_wartosc;
}

#define MAX_LINE 256
#define MAX_NUMBER 64
#define MAX_TEXTS 64

double sum (const int number, const double* values) {
	double suma = 0;
	for (int i = 0; i < number; i++) {
		suma = suma + values[i];
	}
	return suma;
}

double average (const int number, const double* values) {
	return sum(number,values) / number;
}

double median (const int number, double* values) {
	qsort(values,number,sizeof(double),compare_doubles);
	int mid_element = number / 2;
	if (number % 2 == 1) {
		return values[mid_element];
	}
	return (values[mid_element] + values[mid_element - 1]) / 2.0;
}

double min (const int number, const double* values) {
	double min = values[0];
	for (int i = 0; i < number; i++) {
		if (values[i] < min) {
			min = values[i];
		}
	}
	return min;
}

double max (const int number, const double* values) {
	double max = values[0];
	for (int i = 0; i < number; i++) {
		if (values[i] > max) {
			max = values[i];
		}
	}
	return max;
}

int read_from_line(char* c_buf, double *values, char** texts, int* text_counter) {
	char *current = c_buf;
	int num_count = 0;
	*text_counter = 0;
	while (*current != '\0') {
		char *next_space;
		double val = strtod(current,&next_space);
		if (current != next_space) {
			values[num_count++] = val;
			current = next_space;
		}
		else {
			char temp_word[MAX_LINE];
			int przesuniecie = 0;
			if (sscanf(current, "%s%n", temp_word, &przesuniecie) == 1) {
				texts[*text_counter] = malloc(strlen(temp_word) + 1);
				strcpy(texts[*text_counter],temp_word);
				(*text_counter)++;
				current+=przesuniecie;
			}
			else {
				break;
			}
		}
	}
	return num_count;
}

int read_int(void) {
	char c_buf[MAX_LINE];
	fgets(c_buf, MAX_LINE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int number;
	double v1, v2, v3, v4, v5;

	char c_buf[MAX_LINE];
	double values[MAX_NUMBER];
	char* texts[MAX_TEXTS];
	int text_counter;

	const int to_do = read_int();

	switch (to_do) {
		case 1:
			number = 3;
			scanf("%lf%lf%lf", &v1, &v2, &v3);
			printf("%.2f %.2f %.2f %.2f %.2f\n",
					sum_var(number, v1, v2, v3),
					average_var(number, v1, v2, v3),
					median_var(number, v1, v2, v3),
					min_var(number, v1, v2, v3),
					max_var(number, v1, v2, v3));

			number = 5;
			scanf("%lf%lf%lf%lf%lf", &v1, &v2, &v3, &v4, &v5);
			printf("%.2f %.2f %.2f %.2f %.2f\n",
					sum_var(number, v1, v2, v3, v4, v5),
					average_var(number, v1, v2, v3, v4, v5),
					median_var(number, v1, v2, v3, v4, v5),
					min_var(number, v1, v2, v3, v4, v5),
					max_var(number, v1, v2, v3, v4, v5));
			break;
		case 2:
			fgets(c_buf, MAX_LINE, stdin);
			number = read_from_line(c_buf, values, texts, &text_counter);
			printf("%.2f %.2f %.2f %.2f %.2f\n",
					sum(number, values),
					average(number, values),
					median(number, values),
					min(number, values),
					max(number, values));

			for (int k = 0; k < text_counter; k++) {
				printf("%s\n", texts[k]);
			}
			break;
		default:
			printf("Nothing to do for n = %d\n", to_do);
			break;
	}

	return EXIT_SUCCESS;
}

