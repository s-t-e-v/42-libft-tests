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
#define FT "ft_substr"
#define FUNC(a, b, c) ft_substr(a, b, c)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


typedef struct s_params {
	const char		*s;
	unsigned int	start;
	size_t			len;
	const char		*expected;
} t_params;


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
	t_test_data test;
	t_params	params[] = {
		{"", 0, 0, NULL},
		{"", 0, 1, ""},
		{"", 0, 2, ""},
		{"", 0, 5, ""},
		{"", 1, 0, NULL},
		{"", 1, 1, NULL},
		{"", 1, 2, NULL},
		{"a", 0, 1, "a"},
		{"a", 0, 2, "a"},
		{"a", 1, 1, ""},
		{"a", 1, 2, ""},
		{"a", 1, 5, ""},
		{"a", 2, 0, NULL},
		{"a", 2, 1, NULL},
		{"a", 2, 2, NULL},
		{"a", 2, 5, NULL},
		{"ab", 0, 1, "a"},
		{"ab", 0, 2, "ab"},
		{"ab", 0, 3, "ab"},
		{"ab", 0, 5, "ab"},
		{"ab", 1, 1, "b"},
		{"ab", 1, 3, "b"},
		{"ab", 2, 1, ""},
		{"ab", 2, 2, ""},
		{"ab", 2, 3, ""},
		{"ab", 3, 1, NULL},
		{"ab", 3, 2, NULL},
		{"ab", 3, 5, NULL},
		{"je suis bien", 0, 1, "j"},
		{"je suis bien", 0, 2, "je"},
		{"je suis bien", 0, 3, "je "},
		{"je suis bien", 0, 12, "je suis bien"},
		{"je suis bien", 0, 20, "je suis bien"},
		{"je suis bien", 3, 4, "suis"},
		{"je suis bien", 8, 4, "bien"},
		{"je suis bien", 12, 1, ""},
		{"je suis bien", 12, 3, ""},
		{"je suis bien", 13, 1, NULL},
		{"je suis bien", 13, 2, NULL},
		{"je suis bien", 13, 5, NULL},
	};
	
	char *actual;
	char *expected;
	
	// ---- general cases
	i = 0;
	while (i < sizeof(params) / sizeof(params[0]))
	{
	
		sprintf(test.message, "%s(%s, %d, %ld)", FT, params[i].s, params[i].start, params[i].len);
		// printf("%s\n", test.message);
		actual = FUNC(params[i].s, params[i].start, params[i].len);
		expected = (char *)params[i].expected;
		sprintf(test.actual, "%s", actual);
		sprintf(test.expected, "%s", expected);

		test_assert((actual == NULL && expected == NULL) || ((actual != NULL && expected != NULL) && (memcmp(actual, expected, strlen(expected) + 1) == 0)), test);
		
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