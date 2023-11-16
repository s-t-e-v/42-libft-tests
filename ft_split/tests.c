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
#define FT "ft_split"
#define FUNC(a, b) ft_split(a, b)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


typedef struct s_params {
	const char	*s;
	const char	c;
	const char	**expected;
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

static int compare_string_arrays(char **strs1, char **strs2, size_t len) {
	size_t i;

	i = 0;
	while (i < len) {
      if (!(strs1[i] == NULL && strs2[i] == NULL) || ((strs1[i] && strs2[i]) && (strcmp(strs1[i], strs2[i]) != 0)))
	  {
          return (1); // Strings are not identical
      }
	  i++;
	}
    return (0); // All strings are identical
}

static size_t	ft_strslen(char **s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static void array_str_to_str(char *str, char **strs) {
    size_t i = 0;

	if (strs == NULL)
	{
		sprintf(str, "(null)");
		return ;
	}

    // Start the string with an opening curly brace
    str[0] = '{';
    str++;

    while (strs[i]) {
        // Add double quotes around each string
        sprintf(str, "\"%s\"", strs[i]);

        // Move the pointer to the end of the current string
        while (*str)
            str++;

        // Add a comma after each string, except the last one
        if (strs[i + 1]) {
            sprintf(str, ", ");
            str++;
        }

        i++;
    }

    // Add a null entry at the end and close the string with a closing curly brace
    sprintf(str, ", (null)}");
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
	t_params params[] = {
		// {NULL, '\0', NULL},
		// {NULL, 'a', NULL},
		// {"", '\0', (const char *[]){"", NULL}},
		// {"", 'a', NULL},
		// {"a", '\0', (const char *[]){"a", NULL}},
		// {"a", 'a', (const char *[]){"", NULL}},
		// {"a", 'b', NULL},
		// {",a", ',', (const char *[]){"", "a", NULL}},
		// {"a,", ',', (const char *[]){"a", "", NULL}},
		{",a,", ',', (const char *[]){"", "a", "", NULL}},
		// {"ab", '\0', (const char *[]){"ab", NULL}},
		// {"ab", ',', NULL},
		// {",ab", ',', (const char *[]){"", "ab", NULL}},
		// {"ab,", ',', (const char *[]){"ab", "", NULL}},
		// {",ab,", ',', (const char *[]){"", "ab", "", NULL}},
		// {",a,b", ',', (const char *[]){"", "a", "b", NULL}},
		// {"a,b,", ',', (const char *[]){"a", "b", "", NULL}},
		// {"a,b", ',', (const char *[]){"a", "b", NULL}},
		// {",a,b,", ',', (const char *[]){"", "a", "b", "", NULL}},
		// {",", ',', (const char *[]){"", "", NULL}},
		// {",,", ',', (const char *[]){"", "", "", NULL}},
	};
	
	char **actual;
	char **expected;
	
	// ---- general cases
	i = 0;
	while (i < sizeof(params) / sizeof(params[0]))
	{
		printf("%ld\n", i);
		if (isprint((unsigned char)params[i].c))
			sprintf(test.message, "%s(\"%s\", '%c')", FT, params[i].s, params[i].c);
		else
			sprintf(test.message, "%s(\"%s\", \\x%02x)", FT, params[i].s, params[i].c);

		// printf("%s\n", test.message);
		actual = FUNC(params[i].s, params[i].c);
		if (actual)
		{

		j = 0;
			while (actual[j])
	{
		printf("strs[%lu]:%s\n", j, actual[j]);
		j++;
	}
			printf("strs[%lu]:%s\n", j, actual[j]);

		}
		expected = (char **)params[i].expected;
		array_str_to_str(test.actual, actual);
		array_str_to_str(test.expected, expected);

		test_assert((actual == NULL && expected == NULL) || ((actual != NULL && expected != NULL) && (compare_string_arrays(actual, expected, ft_strslen(expected) + 1) == 0)), test);
		
		if (actual)
		{
			j = 0;
			while (actual[j])
				free(actual[j++]);
			free(actual);
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