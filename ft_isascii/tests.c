/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:22:00 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/09 17:12:48 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#define FT "ft_isascii"
#define FUNC(c) ft_isascii(c)


int	ft_isascii(int c);

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
	test_assert(FUNC(0) == 1, FT "(0)");
	test_assert(FUNC(127) == 1, FT "(127)");
	// ---- normal cases
	test_assert(FUNC('A') == 1, FT "('A')");
	test_assert(FUNC('z') == 1, FT "('z')");
	test_assert(FUNC('g') == 1, FT "('g')");
	test_assert(FUNC(20) == 1, FT "(20)");
	test_assert(FUNC('\x78') == 1, FT "('\\x78')");
	test_assert(FUNC('\n') == 1, FT "('\\n')");
}

static void	test_invalid() {
	// alpha
	// ---- edge cases
	test_assert(FUNC(-1) == 0, FT "(-1)");
	test_assert(FUNC(128) == 0, FT "(128)");

	// ---- general cases
	test_assert(FUNC(-200) == 0, FT "(-200)");
	test_assert(FUNC(255) == 0, FT "(255)");
	test_assert(FUNC(3000) == 0, FT "(3000)");

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