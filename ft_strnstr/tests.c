/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/13 14:58:27 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_strnstr"
#define FUNC(a, b, c) ft_strnstr(a, b, c)
#define OG_FUNC(a, b, c) strnstr(a, b, c)

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
	char		big[][100] = {
		"",
		"a",
		"ba",
		"bba",
		"bbbaa",
		"nnnaannaaabb",
		"nnnaannaaaaa",
		";;;;;;;;;;;;aaa",
		"AAaaBaaBaaabbb"
	};
	char		little[][100] = {
		"",
		"a",
		"aa",
		"aaa",
		"bba",
		"ba",
		"naan",
		"aaab",
		";;;;;;;;;;;;",
		"Aa",
		"nna",
		"nn",
		"Ba",
		"9",
		"899999",
		"655555555555555555",
		"AAaaBaaBaaabbbbbbbbbbbbb",
	};
	size_t 		len[] = {
		0,
		1,
		2,
		3,
		5,
		10,
		15,
		20,
		30,
		50,
	};
	char			*res = 0;
	char			*res_og = 0;
	char		big_og[sizeof(big) / sizeof(big[0])][100];
	char		little_og[sizeof(little) / sizeof(little[0])][100];
	char		big_cpy[sizeof(big) / sizeof(big[0])][100];
	char		little_cpy[sizeof(little) / sizeof(little[0])][100];
	
	// ---- general cases
	i = 0;
	while (i < sizeof(big) / sizeof(big[0]))
	{
		memcpy(big_cpy[i], big[i], sizeof(big[i]));
		memcpy(big_og[i], big[i], sizeof(big[i]));
		i++;
	}
	i = 0;
	while (i < sizeof(little) / sizeof(little[0]))
	{
		memcpy(little_cpy[i], little[i], sizeof(little[i]));
		memcpy(little_og[i], little[i], sizeof(little[i]));
		i++;
	}

	i = 0;
	while (i < sizeof(big) / sizeof(big[0]))
	{
		j = i;
		while (j < sizeof(little) / sizeof(little[0]))
		{
			k = 0;
			while (k < sizeof(len) / sizeof(len[0]))
			{

				sprintf(test.message, "%s(%s, %s, %ld)", FT, big[i], little[j], len[k]);
				// printf("%s\n", test.message);
				res = FUNC(big[i], little[j], len[k]);
				res_og = OG_FUNC(big_og[i], little_og[j], len[k]);
				sprintf(test.actual, "%s", res);
				sprintf(test.expected, "%s", res_og);

				// test_assert(memcmp(res, res_og, strlen(res) + 1) == 0, test);
				test_assert((res == NULL && res_og == NULL) || ((res != NULL && res_og != NULL) && (memcmp(res, res_og, strlen(res_og) + 1) == 0)), test);

				// reinitialize current big and little and og variables
				memcpy(big, big_cpy, sizeof(big_cpy));
				memcpy(big_og, big_cpy, sizeof(big_cpy));
				memcpy(little, little_cpy, sizeof(little_cpy));
				memcpy(little_og, little_cpy, sizeof(little_cpy));

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