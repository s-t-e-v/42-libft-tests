/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/10 17:53:28 by sbandaog         ###   ########.fr       */
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
static void tests_char() {
    size_t i;
    t_test_data test;
    char data[] = {
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

    size_t n = sizeof(data[0]);
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

        int result = memcmp(&data[i], &data2[i], sizeof(data[0]));
        sprintf(test.actual, "%d", result);
        sprintf(test.expected, "0");
        test_assert(result == 0, test);

        // reinitialize current data and data2
        memcpy(data, data_cpy, sizeof(data));
        memcpy(data2, data_cpy, sizeof(data2));

        i++;
    }
}

/* Run tests */
static void	run_tests()
{
	tests_char();
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