/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/09 18:22:28 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#define FT "ft_isprint"
#define FUNC(c) ft_isprint(c)

int ft_isprint(int c);

static int tests_run = 0;
static int tests_failed = 0;

/* Test assert function */

static void	test_assert(int condition, const char* message)
{
	if (!condition) {
		tests_failed++;
		printf("FAIL: %s\n", message);
	}
	tests_run++;
}

/* Tests functions */
static void	test_valid() {
	// ---- edge cases
	test_assert(FUNC(' ') == 1, FT "(' ')");
	test_assert(FUNC('~') == 1, FT "('~')");
	// ---- normal cases
	test_assert(FUNC('5') == 1, FT "('5')");
	test_assert(FUNC('\\') == 1, FT "('\\')");
	test_assert(FUNC('f') == 1, FT "('f')");
}

static void	test_invalid() {
	// ---- edge cases
	test_assert(FUNC(31) == 0, FT "(31)");
	test_assert(FUNC(127) == 0, FT "(127)");
	// ---- general cases
	test_assert(FUNC(0) == 0, FT "(0)");
	test_assert(FUNC(3000) == 0, FT "(3000)");
	test_assert(FUNC('\n') == 0, FT "('\\n')");
	test_assert(FUNC('\x0a') == 0, FT "('\\x0a')");
	test_assert(FUNC('\x1d') == 0, FT "('\\x1d')");
}

/* Run tests */
static void	run_tests()
{
	test_valid();
	test_invalid();
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