/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/10 15:33:20 by sbandaog         ###   ########.fr       */
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
	char	chars[] = {
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
	char	chars2[] = {
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
	int c[] = {
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

	int n[] = {
		sizeof(chars[0]),
		1,
		// 2,
		// 4,
		// 8,
		// 12
	};
	char *res;
	char *res_og;
	char save_char;
	char save_char2;
	
	// ---- general cases
	i = 0;
	while (i < sizeof(chars) / sizeof(chars[0]))
	{
		save_char = chars[i];
		save_char2 = chars2[i];
		j = 0;
		while (j < sizeof(c) / sizeof(c[0]))
		{
			k = 0;
			while (k < sizeof(n) / sizeof(n[0]))
			{
				sprintf(test.message, "%s(%d, %d, %d)", FT, chars[i], c[j], n[k]);
				res = (char *)FUNC(&chars[i], c[j], n[k]);
				res_og = (char *)OG_FUNC(&chars2[i], c[j], n[k]);
				sprintf(test.actual, "%d (char)", *res);
				sprintf(test.expected, "%d (char)", *res_og);
				test_assert(!memcmp(&res, &res_og, sizeof(res)), test);
				// reinitialize current chars and chars2
				chars[i] = save_char;
				chars2[i] = save_char2;
				k++;
			}
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