/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/14 18:46:35 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include "../../libft.h"
#define FT "ft_strdup"
#define FUNC(a) ft_strdup(a)
#define OG_FUNC(a) strdup(a)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


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
	size_t		i;
	t_test_data	test;

	bzero(&test, sizeof(test));
	
	char	data[][100] = {
		"",
		"a",
		"aaaa",
		"Argentine c'est cool"
	};
	char		*res = 0;
	char		*res_og = 0;
	char		data_og[sizeof(data) / sizeof(data[0])][100];
	char		data_cpy[sizeof(data) / sizeof(data[0])][100];
	
	// ---- general cases
	memcpy(data_og, data, sizeof(data));
	memcpy(data_cpy, data, sizeof(data));

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		sprintf(test.message, "%s(%s)", FT, data[i]);
		// printf("%s\n", test.message);
		res = FUNC(data[i]);
		// printf("Yo !\n");
		res_og = OG_FUNC(data_og[i]);
		// printf("Bruh\n");
		// if (res == NULL)
		// 	printf("res == null\n");
		if (data[i])
			sprintf(test.actual, "%s", res);
		else
			sprintf(test.actual, "NULL");
		// printf("ptdr...\n");
		if (data_og[i])
			sprintf(test.expected, "%s", res_og);
		else
			sprintf(test.expected, "NULL");

		test_assert((res == NULL && res_og == NULL) || ((res != NULL && res_og != NULL) && (memcmp(res, res_og, strlen(data_og[i]) + 1) == 0)), test);

		// Free allocated values
		if (res)
			free(res);
		if (res_og)
			free(res_og);

		// reinitialize current big and little and og variables
		memcpy(data, data_cpy, sizeof(data_cpy));
		memcpy(data_og, data_cpy, sizeof(data_cpy));

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