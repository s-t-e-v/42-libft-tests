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
#include <stdlib.h>
#include <unistd.h>
#include <bsd/string.h>
#include <ctype.h>
#include "../../libft.h"
#define FT "ft_itoa"
#define FUNC(a) ft_itoa(a)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


typedef struct s_params {
	long		n;
	const char	*expected;
} t_params;


static void print_string_with_escapes(const char *str) {
	if (str){
		while (*str) {
			if (isprint((unsigned char)*str)) {
				putchar(*str);
			} else {
				printf("\\x%02x", (unsigned char)*str);
			}
			str++;
		}
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
		printf("    Actual  : ");
		print_string_with_escapes(test.actual);
		printf("\n");
	}
	// else {
	// 	printf("SUCCESS: ");
	// 	print_string_with_escapes(test.message);
	// 	printf("\n");
	// 	printf("    Expected: ");
	// 	print_string_with_escapes(test.expected);
	// 	printf("\n");
	// 	printf("    Actual  : ");
	// 	print_string_with_escapes(test.actual);
	// 	printf("\n");
	// }
	tests_run++;
}

/* Tests functions */
static void	test1() {
	size_t i;
	t_test_data test;
	t_params params[] = {
		{0, "0"},
		{1, "1"},
		{9, "9"},
		{11, "11"},
		{42, "42"},
		{256, "256"},
        {2200, "2200"},
		{2147483647, "2147483647"},
		{2147483648, "-2147483648"},
		{2147483650, "-2147483646"},
		{-1, "-1"},
		{-7, "-7"},
		{-42, "-42"},
		{-498, "-498"},
		{-3600, "-3600"},
		{-2147483648, "-2147483648"},
		{-2147483649, "2147483647"},
		{-2147483650, "2147483646"},
	};
	
	char *actual;
	char *expected;
	
	// ---- general cases
	i = 0;
	while (i < sizeof(params) / sizeof(params[0]))
	{
		sprintf(test.message, "%s(%ld)", FT, params[i].n);

		// printf("%s\n", test.message);
		actual = FUNC((int)params[i].n);
		expected = (char *)params[i].expected;
		sprintf(test.actual, actual ? "\"%s\"" : "%s", actual);
		sprintf(test.expected, "\"%s\"", expected);

		test_assert((actual == NULL && expected == NULL) || ((actual != NULL && expected != NULL) && memcmp(actual, expected, strlen(expected) + 1) == 0), test);
		
		if (actual)
			free(actual);

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