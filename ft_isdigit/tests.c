/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/09 18:18:28 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#define FT "ft_isdigit"
#define FUNC(c) ft_isdigit(c)

int ft_isdigit(int c);

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
	test_assert(FUNC('0') == 1, FT "('0')");
	test_assert(FUNC('9') == 1, FT "('9')");
	// ---- normal cases
	test_assert(FUNC('5') == 1, FT "('5')");
	test_assert(FUNC('8') == 1, FT "('8')");
	test_assert(FUNC('\x33') == 1, FT "('\\x33')");
}

static void	test_invalid() {
	// ---- edge cases
	test_assert(FUNC('/') == 0, FT "('/')");
	test_assert(FUNC(':') == 0, FT "(':')");
	// ---- alpha cases
	test_assert(!FUNC ('a'), FT "('a')");
	test_assert(!FUNC ('U'), FT "('U')");
	// ---- general cases
	test_assert(FUNC('*') == 0, FT "('*')");
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