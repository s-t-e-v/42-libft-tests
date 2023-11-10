/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/10 17:11:37 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_memset"
#define FUNC(a, b, c) ft_memset(a, b, c)
#define OG_FUNC(a, b, c) memset(a, b, c)

static int tests_run = 0;
static int tests_failed = 0;
static int c[] = {
		0,
		1,
		10,
		100,
		127,
		128,
		150,
		3000,
		-1,
		-10,
		-100,
		-127,
		-128,
		-150,
		-3000
	};

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
	size_t j;
	size_t k;
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
	
	int n = sizeof(data[0]);
	char *res;
	char *res_og;
	char data2[sizeof(data) / sizeof(data[0])];
	char data_cpy[sizeof(data) / sizeof(data[0])];
    char data2_cpy[sizeof(data2) / sizeof(data2[0])];
	
	// ---- general cases
	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		data2[i] = data[i];
		data_cpy[i] = data[i];
        data2_cpy[i] = data2[i];		
		i++;
	}

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		j = 0;
		while (j < sizeof(c) / sizeof(c[0]))
		{
			sprintf(test.message, "%s(%d, %d, %d)", FT, data[i], c[j], n);
			res = (char *)FUNC(&data[i], c[j], n);
			res_og = (char *)OG_FUNC(&data2[i], c[j], n);
			sprintf(test.actual, "%d (char)", *res);
			sprintf(test.expected, "%d (char)", *res_og);
			test_assert(memcmp(&res, &res_og, sizeof(res)), test);
			// reinitialize current data and data2
			memcpy(data, data_cpy, sizeof(data));
			memcpy(data2, data2_cpy, sizeof(data2));
				
			j++;
		}
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