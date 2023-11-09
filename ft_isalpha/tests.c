/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:22:00 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/09 17:13:52 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#define FT "ft_isalpha"
#define FUNC(c) ft_isalpha(c)


int	ft_isalpha(int c);

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
	test_assert(FUNC('A') == 1, FT "('A')");
	test_assert(FUNC('Z') == 1, FT "('Z')");
	test_assert(FUNC('a') == 1, FT "('a')");
	test_assert(FUNC('z') == 1, FT "('z')");
	// ---- normal cases
	test_assert(FUNC('g') == 1, FT "('g')");
	test_assert(FUNC(70) == 1, FT "(70)");
	test_assert(FUNC('\x45') == 1, FT "('\\x45')");
}

static void	test_invalid() {
	// alpha
	// ---- edge cases
	test_assert(FUNC(64) == 0, FT "(64)");
	test_assert(FUNC(91) == 0, FT "(91)");
	test_assert(FUNC(96) == 0, FT "(96)");
	test_assert(FUNC(123) == 0, FT "(123)");

	// ---- num cases
	test_assert(FUNC('1') == 0, FT "('1')");
	test_assert(FUNC('9') == 0, FT "('9')");
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