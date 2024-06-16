/*============================================================================
 Name        : majority_algorithm.c
 Author      : Abdurrahman Nurhakim
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Majority and minority selection for filtering purposed with manual input, manipulating minority value with majority average value (for filter data purpose).
============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "majority_minority_algorithm.h"

// Fungsi untuk menghitung rata-rata dari array
double average(const int *data, size_t size) {
    int total = 0;
    for (size_t i = 0; i < size; ++i) {
        total += data[i];
    }
    return (double)total / size;
}

// Fungsi untuk menghitung rasio konstan dari dua nilai
double constant(double real_value, double raw_value) {
    return real_value / raw_value;
}

// Fungsi perbandingan untuk qsort untuk mengurutkan integer
int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Fungsi untuk mendeteksi outlier dalam data berdasarkan threshold yang diberikan
void detect_outliers(const int *data, size_t size, int threshold, int **majorities, size_t *majority_size, int **minorities, size_t *minority_size, int **major_indices, size_t *major_indices_count, int **minor_indices, size_t *minor_indices_count) {
    // Alokasi memori untuk array, soalnya ini c bukan bahasa uler ygy
    int *sorted_data = (int *)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; ++i) {
        sorted_data[i] = data[i];
    }
    qsort(sorted_data, size, sizeof(int), compare_ints);

    *majorities = (int *)malloc(size * sizeof(int));
    *minorities = (int *)malloc(size * sizeof(int));
    *major_indices = (int *)malloc(size * sizeof(int));
    *minor_indices = (int *)malloc(size * sizeof(int));

    int *temp_majorities = (int *)malloc(size * sizeof(int));
    size_t temp_majorities_size = 1;
    temp_majorities[0] = sorted_data[0];

    size_t majorities_size = 0;
    size_t minorities_size = 0;
    size_t major_indices_size = 0;
    size_t minor_indices_size = 0;

    // Identifikasi kelompok mayoritas berdasarkan threshold
    for (size_t i = 1; i < size; ++i) {
        if (abs(sorted_data[i] - sorted_data[i - 1]) <= threshold) {
            temp_majorities[temp_majorities_size++] = sorted_data[i];
        } else {
            if (temp_majorities_size > majorities_size) {
                for (size_t j = 0; j < temp_majorities_size; ++j) {
                    (*majorities)[j] = temp_majorities[j];
                }
                majorities_size = temp_majorities_size;
            }
            temp_majorities[0] = sorted_data[i];
            temp_majorities_size = 1;
        }
    }

    if (temp_majorities_size > majorities_size) {
        for (size_t j = 0; j < temp_majorities_size; ++j) {
            (*majorities)[j] = temp_majorities[j];
        }
        majorities_size = temp_majorities_size;
    }

    // Tentukan nilai minoritas dan indeksnya berdasarkan nilai mayoritas
    for (size_t i = 0; i < size; ++i) {
        int is_majority = 0;
        for (size_t j = 0; j < majorities_size; ++j) {
            if (data[i] == (*majorities)[j]) {
                is_majority = 1;
                (*major_indices)[major_indices_size++] = i;
                break;
            }
        }
        if (!is_majority) {
            (*minorities)[minorities_size++] = data[i];
            (*minor_indices)[minor_indices_size++] = i;
        }
    }

    *majority_size = majorities_size;
    *minority_size = minorities_size;
    *major_indices_count = major_indices_size;
    *minor_indices_count = minor_indices_size;

    // Bebaskan memori sementara
    free(temp_majorities);
    free(sorted_data);
}

// Fungsi untuk mengganti nilai minoritas dengan rata-rata nilai mayoritas
void replace_minorities(int *data, size_t size, const int *majorities, size_t majority_size, const int *minor_indices, size_t minor_indices_size) {
    if (majority_size == 0) {
        return;
    }

    double major_avg = average(majorities, majority_size);

    for (size_t i = 0; i < minor_indices_size; ++i) {
        data[minor_indices[i]] = (int)major_avg;
    }
}

// Fungsi untuk membaca nilai minoritas, menggantinya, dan menghitung rata-rata total
double read_minority(size_t window_size, int threshold) {
    size_t size;
    
    // Minta pengguna untuk memasukkan ukuran array dan nilai-nilainya
    printf("Enter the number of elements: ");
    scanf("%zu", &size);
    
    int *data = (int *)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; ++i) {
    	printf("Insert the element: ");
        scanf("%d", &data[i]);
    }

    int *majorities, *minorities, *major_indices, *minor_indices;
    size_t majority_size, minority_size, major_indices_count, minor_indices_count;

    // Deteksi outlier dan klasifikasikan data menjadi mayoritas dan minoritas
    detect_outliers(data, size, threshold, &majorities, &majority_size, &minorities, &minority_size, &major_indices, &major_indices_count, &minor_indices, &minor_indices_count);

    // Cetak data mentah dan nilai yang telah diklasifikasikan
    printf("Raw Data: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Majority: ");
    for (size_t i = 0; i < majority_size; ++i) {
        printf("%d ", majorities[i]);
    }
    printf("\n");

    printf("Minority: ");
    for (size_t i = 0; i < minority_size; ++i) {
        printf("%d ", minorities[i]);
    }
    printf("\n");

    printf("List Majority: ");
    for (size_t i = 0; i < major_indices_count; ++i) {
        printf("%zu ", major_indices[i]);
    }
    printf("\n");

    printf("List Minority: ");
    for (size_t i = 0; i < minor_indices_count; ++i) {
        printf("%zu ", minor_indices[i]);
    }
    printf("\n");

    // Ganti nilai minoritas dan hitung rata-rata data yang telah difilter
    replace_minorities(data, size, majorities, majority_size, minor_indices, minor_indices_count);
    double total_measures = average(data, size);

    // Cetak data akhir dan nilai rata-rata
    printf("The whole data after manipulated: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Final average data: %.2f\n", total_measures);

    // Bebaskan memori yang telah dialokasikan
    // jangan sampe kelewat !!
    free(majorities);
    free(minorities);
    free(major_indices);
    free(minor_indices);
    free(data);

    return total_measures;
}

int main() {
    // Panggil fungsi read_minority dengan ukuran window dan threshold yang ditentukan pengguna
    int threshold;
    
    // Minta pengguna untuk memasukkan ukuran array dan nilai-nilainya
    printf("Insert the threshold value : ");
    scanf("%d", &threshold);
    double filtered_value = read_minority(10, threshold);
    printf("FInal filtered value (mode filter): %.2f\n", filtered_value);
    return 0;
}
