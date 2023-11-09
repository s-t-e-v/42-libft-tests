/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/09 19:14:25 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include <stddef.h>
#define FT "ft_strlen"
#define FUNC(c) ft_strlen(c)
#define OG_FUNC(c) strlen(c)

size_t  ft_strlen(const char *s);

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
static void	tests() {
	int i;
	char *strs[] = {
		"",
		"a",
		"abc def",
		"dwefwef hfiuwehfiuew fewufhiuwehfiuwe weiufiwuefhiuewf ufihiewufhi",
		"\0",
		NULL,
	};
	char message[1000]; // Make sure this is large enough to hold your message

	// ---- general cases
	i = 0;
	while (strs[i])
	{
		sprintf(message, "%s('%s')", FT, strs[i]);
		test_assert(FUNC(strs[i]) == OG_FUNC(strs[i]), message);
		i++;
	}
}

static void	test_valid() {
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