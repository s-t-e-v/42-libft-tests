/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/13 13:49:12 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_memcmp"
#define FUNC(a, b, c) ft_memcmp(a, b, c)
#define OG_FUNC(a, b, c) memcmp(a, b, c)

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
static void	test1() {
	size_t		i;
	size_t		j;
	size_t		k;
	t_test_data	test;
	char		data[][100] = {
		"",
		"",
		"a",
		"A",
		"b",
		"]",
		"@",
		"1",
		"0",
		"9",
		"AA",
		"AAaa",
		"AAaaa",
		"AAaaaa",
		"Aa",
		"&aaaa",
		"b&aaa",
		"ba&aa",
		"baa&a",
		"baaa&",
		"rt\x7f fm",
		"rt\x7f em",
		"\x01",
		"\x01\x0b",
	};
	
	size_t 		n[] = {
		0,
		1,
		2,
		3,
		5,
		10
	};
	int			res = 0;
	int			res_og = 0;
	char		res_str = 0;
	char		res_str_og = 0;
	char		data2[sizeof(data) / sizeof(data[0])][100];
	char		data_og[sizeof(data) / sizeof(data[0])][100];
	char		data2_og[sizeof(data) / sizeof(data[0])][100];
	char		data_cpy[sizeof(data) / sizeof(data[0])][100];
	
	// ---- general cases
	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		memcpy(data_cpy[i], data[i], sizeof(data[i]));
		memcpy(data2[i], data[i], sizeof(data[i]));
		memcpy(data_og[i], data[i], sizeof(data[i]));
		memcpy(data2_og[i], data[i], sizeof(data[i]));
		i++;
	}

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		j = i;
		while (j < sizeof(data2) / sizeof(data2[0]))
		{
			k = 0;
			while (k < sizeof(n) / sizeof(n[0]))
			{

				sprintf(test.message, "%s(%s, %s, %ld)", FT, data[i], data2[j], n[k]);
				// printf("%s\n", test.message);
				res = FUNC(data[i], data2[j], n[k]);
				res_og = OG_FUNC(data_og[i], data2_og[j], n[k]);
				if (res > 0)
					res_str = '>';
				else if (res < 0)
					res_str = '<';
				else
					res_str = '=';
				if (res_og > 0)
					res_str_og = '>';
				else if (res_og < 0)
					res_str_og = '<';
				else
					res_str_og = '=';
				sprintf(test.actual, "return value %c 0", res_str);
				sprintf(test.expected, "return value %c 0", res_str_og);

				test_assert(res_str == res_str_og, test);

				// reinitialize current data and data_og
				memcpy(data, data_cpy, sizeof(data));
				memcpy(data_og, data_cpy, sizeof(data));
				memcpy(data2, data_cpy, sizeof(data));
				memcpy(data2_og, data_cpy, sizeof(data));

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