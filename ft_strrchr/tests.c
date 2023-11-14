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
#include <ctype.h>
#include "../../libft.h"
#define FT "ft_strrchr"
#define FUNC(a, b) ft_strrchr(a, b)
#define OG_FUNC(a, b) strrchr(a, b)

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
		-3000,
		'a',
		']',
		'[',
		';',
		'+',
		'~'
};


void print_string_with_escapes(const char *str) {
    while (*str) {
        if (isprint((unsigned char)*str)) {
            putchar(*str);
        } else {
            printf("\\x%02x", (unsigned char)*str);
        }
        str++;
    }
}


/* Test assert function */
static void	test_assert(int condition, t_test_data test)
{
	if (!condition) {
		tests_failed++;
		printf("FAIL: ");
		print_string_with_escapes(test.message);
		printf("\n");
		printf("    Expected: ");
		print_string_with_escapes(test.expected);
		printf("\n");
		printf("    Actual: ");
		print_string_with_escapes(test.actual);
		printf("\n");
	}
	tests_run++;
}

/* Tests functions */
static void	test1() {
	size_t i;
	size_t j;
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
	
	char *res;
	char *res_og;
	char data_og[sizeof(data) / sizeof(data[0])][100];
	char data_cpy[sizeof(data) / sizeof(data[0])][100];
	
	// ---- general cases

	memcpy(data_og, data, sizeof(data));
	memcpy(data_cpy, data, sizeof(data));

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		j = 0;
		while (j < sizeof(c) / sizeof(c[0]))
		{

				sprintf(test.message, "%s(%s, %d)", FT, data[i], c[j]);
				// printf("%s\n", test.message);
				res = FUNC(data[i], c[j]);
				res_og = OG_FUNC(data_og[i], c[j]);
				sprintf(test.actual, "%s", res);
				sprintf(test.expected, "%s", res_og);

				test_assert((res == NULL && res_og == NULL) || ((res != NULL && res_og != NULL) && (memcmp(res, res_og, strlen(res_og) + 1) == 0)), test);
				// reinitialize current data and data_og
				memcpy(data, data_cpy, sizeof(data));
				memcpy(data_og, data_cpy, sizeof(data_og));

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