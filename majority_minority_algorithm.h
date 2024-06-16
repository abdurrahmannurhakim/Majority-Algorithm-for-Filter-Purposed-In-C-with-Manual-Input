/*============================================================================
 Name        : majority_algorithm.h
 Author      : Abdurrahman Nurhakim
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Majority and minority selection for filtering purposed with manual input, manipulating minority value with majority average value (for filter data purpose).
============================================================================*/

#ifndef MAJORITY_MINORITY_ALGORITHM_H
#define MAJORITY_MINORITY_ALGORITHM_H

#include <stddef.h>

// Fungsi untuk menghitung rata-rata dari array
double average(const int *data, size_t size);

// Fungsi untuk menghitung rasio konstan dari dua nilai
double constant(double real_value, double raw_value);

// Fungsi untuk mendeteksi outlier dalam data berdasarkan threshold yang diberikan
void detect_outliers(const int *data, size_t size, int threshold, int **majorities, size_t *majority_size, int **minorities, size_t *minority_size, int **major_indices, size_t *major_indices_count, int **minor_indices, size_t *minor_indices_count);

// Fungsi untuk mengganti nilai minoritas dengan rata-rata nilai mayoritas
void replace_minorities(int *data, size_t size, const int *majorities, size_t majority_size, const int *minor_indices, size_t minor_indices_size);

// Fungsi untuk membaca nilai minoritas, menggantinya, dan menghitung rata-rata total
double read_minority(size_t window_size, int threshold);

#endif
