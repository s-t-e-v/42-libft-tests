/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/13 02:17:41 by sbandaog           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_memchr"
#define FUNC(a, b, c) ft_memchr(a, b, c)
#define OG_FUNC(a, b, c) memchr(a, b, c)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;

static int c[] = {
		0,
		'\0',
		1,
		12,
		'e',
		'\n',
		'*',
		'0',
		'5',
		100,
		127,
		128,
		150,
		3000,
		-1,
		-10,
		-50,
		-100,
		-127,
		-128,
		-150,
		-3000
};

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
static void	test1() {
	size_t i;
	size_t j;
	size_t k;
	t_test_data test;
	char	data[][100] = {
		"",
		"ertger",
		"kalle",
		"***",
		"2200",
		"rt\x7f fm",
		"J'ai 5 chevaux",
		"______",
		"\x01",
		";;rer [[[]]]\x0b ]",
		"pt bn 9999 333```!!"
	};
	
	size_t n[] = {
		0,
		1,
		2,
		3,
		5,
		10,
		20,
		sizeof(data[0])
	};
	char *res;
	char *res_og;
	char data_og[sizeof(data) / sizeof(data[0])][100];
	char data_cpy[sizeof(data) / sizeof(data[0])][100];
	
	// ---- general cases
	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		memcpy(data_og[i], data[i], sizeof(data[i]));
		memcpy(data_cpy[i], data[i], sizeof(data[i]));
		i++;
	}

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		j = 0;
		while (j < sizeof(c) / sizeof(c[0]))
		{
			k = 0;
			while (k < sizeof(n) / sizeof(n[0]))
			{

				sprintf(test.message, "%s(%s, %d, %ld)", FT, data[i], c[j], n[k]);
				// printf("%s\n", test.message);
				res = (char *)FUNC(data[i], c[j], n[k]);
				res_og = (char *)OG_FUNC(data_og[i], c[j], n[k]);
				sprintf(test.actual, "%s", res);
				sprintf(test.expected, "%s", res_og);

				test_assert((res == NULL && res_og == NULL) || ((res != NULL && res_og != NULL) && (memcmp(res, res_og, strlen(data[i]) + 1) == 0)), test);
				// reinitialize current data and data_og
				memcpy(data, data_cpy, sizeof(data));
				memcpy(data_og, data_cpy, sizeof(data_og));

				k++;
			}
				
			j++;
		}
		i++;
	}	
}


static void	run_tests()
{
	test1();
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