/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/10 21:44:23 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include <strings.h>
#include "../../libft.h"
#define FT "ft_bzero"
#define FUNC(a, b) ft_bzero(a, b)
#define OG_FUNC(a, b) bzero(a, b)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;

/* Test assert function */

static void	test_assert(int condition, t_test_data test)
{
	if (!condition) {
		tests_failed++;
		printf("FAIL: %s\n", test.message);
		printf("    Expected: %s\n", test.expected);
		printf("    Actual: %s\n", test.actual);
	}
	tests_run++;
}

/* Tests functions */
static void	tests_char() {
	size_t i;
	t_test_data test;
	char	data[] = {
		'e',
		'\n',
		'\0',
		'*',
		'0',
		'5',
		127,
		-1,
		-10,
		-50,
		-128
	};
	
	size_t	n = sizeof(data[0]);
	char res;
	char res_og;
	char data2[sizeof(data) / sizeof(data[0])];
	char data_cpy[sizeof(data) / sizeof(data[0])];
	
	// ---- general cases
	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		data2[i] = data[i];
		data_cpy[i] = data[i];
		i++;
	}

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		sprintf(test.message, "%s(%d, %ld)", FT, data[i], n);
		
		FUNC(&data[i], n);
		OG_FUNC(&data2[i], n);
		res =  data[i];
		res_og = data2[i];
		sprintf(test.actual, "%d (char)", res);
		sprintf(test.expected, "%d (char)", res_og);
		test_assert(memcmp(&res, &res_og, sizeof(res)) == 0, test);

		// reinitialize current data and data2
		memcpy(data, data_cpy, sizeof(data));
		memcpy(data2, data_cpy, sizeof(data2));
				
		i++;
	}
}

static void	tests_int() {
	size_t i;
	t_test_data test;
	int	data[] = {
		0,
		10,
		127,
		2147483647,
		-1,
		-50,
		-2147483648,
	};
	
	size_t	n = sizeof(data[0]);
	int res;
	int res_og;
	int data2[sizeof(data) / sizeof(data[0])];
	int data_cpy[sizeof(data) / sizeof(data[0])];
	
	// ---- general cases
	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		data2[i] = data[i];
		data_cpy[i] = data[i];
		i++;
	}

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		sprintf(test.message, "%s(%d, %ld)", FT, data[i], n);
		
		FUNC(&data[i], n);
		OG_FUNC(&data2[i], n);
		res =  data[i];
		res_og = data2[i];
		sprintf(test.actual, "%d (int)", res);
		sprintf(test.expected, "%d (int)", res_og);
		test_assert(memcmp(&res, &res_og, sizeof(res)) == 0, test);

		// reinitialize current data and data2
		memcpy(data, data_cpy, sizeof(data));
		memcpy(data2, data_cpy, sizeof(data2));
				
		i++;
	}
}

// Function to convert an array of integers to a string
void arrayToString(int *arr, int size, char *str, int max_size) {
    int offset = 0;
    int chars_written = 0;
    for (int i = 0; i < size; i++) {
        chars_written = snprintf(str + offset, max_size - offset, "%d", arr[i]);
        if (chars_written >= max_size - offset) {
            break; // To prevent buffer overflow
        }
        offset += chars_written;

        // Add comma and space if it's not the last element
        if (i < size - 1) {
            chars_written = snprintf(str + offset, max_size - offset, ", ");
            if (chars_written >= max_size - offset) {
                break; // To prevent buffer overflow
            }
            offset += chars_written;
        }
    }
}



static void tests_array_int() {
    size_t i;
    t_test_data test;
    int *data[] = {
        (int[]){0, 12, 5, 5},
        (int[]){5},
        (int[]){-2147483648, -1, -50, 2147483647},
        (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
    };
    size_t sizes_data[] = {4, 1, 4, 15}; // Define the sizes of each array in data    

    size_t n;
    int *data_cpy[4];
    char input_str[100];
    char res_str[100];
    char res_og_str[100];

    memcpy(data_cpy, data, sizeof(data));
    
    i = 0;
    while (i < 4) {
        n = sizes_data[i];

        arrayToString(data[i], n, input_str, sizeof(input_str));
        sprintf(test.message, "%s(data[%zu] = {%s}, %zu)", FT, i, input_str, n * sizeof(int));
        
        FUNC(data[i], n * sizeof(int));
        OG_FUNC(data_cpy[i], n * sizeof(int));


        arrayToString(data[i], n, res_str, sizeof(res_str));
        arrayToString(data_cpy[i], n, res_og_str, sizeof(res_og_str));

        sprintf(test.actual, "{%s}", res_str);
        sprintf(test.expected, "{%s}", res_og_str);

        test_assert(memcmp(data[i], data_cpy[i], sizeof(data[i])) == 0, test);

        memcpy(data, data_cpy, sizeof(data));
        i++;
    }
}



/* Run tests */
static void	run_tests()
{
	tests_char();
    tests_int();
    tests_array_int();
}

int	main()
{
	// Print tested function name
	printf("* " FT "\n");

	// Run tests
	run_tests();

	// Result tests
	if (!tests_failed)
	{
		printf("All tests passed (%d/%d)\n", tests_run - tests_failed, tests_run);
		return (0);
    }
	else {
		printf("Tests failed (%d/%d)\n", tests_failed, tests_run);
		return (1);
	}
}