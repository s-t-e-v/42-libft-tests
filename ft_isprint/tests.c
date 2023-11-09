/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/09 21:50:25 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include "../../libft.h"
#define FT "ft_isprint"
#define FUNC(c) ft_isprint(c)
#define OG_FUNC(c) isprint(c)

static int tests_run = 0;
static int tests_failed = 0;

/* Test assert function */

static void	test_assert(int condition, const char* message, const char* expected, const char *actual)
{
	if (!condition) {
		tests_failed++;
		printf("FAIL: %s\n", message);
		printf("    Expected: %s\n", expected);
		printf("    Actual: %s\n", actual);
	}
	tests_run++;
}

/* Tests functions */
static void	tests() {
	int i;
	int strs[] = {
		// ---- valid edge cases
		20,
		' ',
		'~',
		// ---- valid normal cases
		'5',
		'\\',
		'f',
		// ---- invalid edge cases
		31,
		127,
		// ---- invalid normal cases
		128,
		174,
		200,
		255,
		3000,
		'\n',
		'\x0a',
		'\x1d',
		0
	};
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message

	// ---- general cases
	i = 0;
	while (1)
	{

		sprintf(expected, "%d", OG_FUNC(strs[i]));
		sprintf(actual, "%d", FUNC(strs[i]));
		sprintf(message, "%s(%d)", FT, strs[i]);
		test_assert(!((FUNC(strs[i]) != 0) ^ (OG_FUNC(strs[i]) != 0)), message, expected, actual);
		if(strs[i] == '\0')
			break;
		i++;
	}
}


static void	tests_valid() {
}

static void	test_invalid() {
}

/* Run tests */
static void	run_tests()
{
	tests();
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