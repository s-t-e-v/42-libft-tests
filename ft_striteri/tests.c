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
#define FT "ft_striteri"
#define FUNC(a, b) ft_striteri(a, b)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


typedef struct s_params {
	char		*s;
	const char	*expected;
	const char	f_name[100];
	void		(*f)(unsigned int, char*);
} t_params;

static void	increment_char_by_one(unsigned int index, char *c)
{
	(void)index;
	*c = (char)(*c + 1);
}

static void	alternate_case(unsigned int index, char *c) {
    if (index % 2 == 0) {
        *c = toupper(*c);
    } else {
        *c = tolower(*c);
    }
}

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

static void str_with_escapes(char *dest, const char *s, size_t size) {
    size_t i = 0;

	if (s == NULL)
	{
		sprintf(dest, "%s", s);
		return ;
	}

    dest[0] = '"';
	dest++;
	i = 0;
    while (i < size) {

		if (isprint((unsigned char)s[i])) {
			sprintf(dest, "%c", s[i]);
		} else {
			sprintf(dest, "\\x%02x", (unsigned char)s[i]);
		}
        // // Move the pointer to the end of the current string
        while (*dest)
            dest++;
		i++;
    }
	sprintf(dest, "\"");
}


/* Tests functions */
static void	test1() {
	size_t i;
	size_t len_ini;
	t_test_data test;
	t_params params[] = {
		{NULL, NULL, "increment_char_by_one", &increment_char_by_one},
		{"", "", "increment_char_by_one", &increment_char_by_one},
		{"a", "b", "increment_char_by_one", &increment_char_by_one},
		{"abc", "bcd", "increment_char_by_one", &increment_char_by_one},
		{"\x7e\x66", "\x7f\x67", "increment_char_by_one", &increment_char_by_one},
		{"\x7f\x64", "\x80\x65", "increment_char_by_one", &increment_char_by_one},
		{"\xff\x60", "\x00\x61", "increment_char_by_one", &increment_char_by_one},
		{"\xff\x5e", "\x00\x5f", "increment_char_by_one", &increment_char_by_one},
		{"", "", "alternate_case", &alternate_case},
		{"aaaa", "AaAa", "alternate_case", &alternate_case},
		{"AAAA***///", "AaAa***///", "alternate_case", &alternate_case},
		{"Hello world!", "HeLlO WoRlD!", "alternate_case", &alternate_case},
	};
	
	char *actual;
	char *expected;
	
	// ---- general cases
	i = 0;
	while (i < sizeof(params) / sizeof(params[0]))
	{
		if (params[i].s)
			sprintf(test.message, "%s(\"%s\", &\%s)", FT, params[i].s, params[i].f_name);
		else
			sprintf(test.message, "%s(%s, &\%s)", FT, params[i].s, params[i].f_name);
		// printf("%s\n", test.message);
		actual = 0;
		len_ini = 0;
		if (params[i].s)
		{
			len_ini = strlen(params[i].s);
			actual = malloc(len_ini + 1);
			memcpy(actual, params[i].s, len_ini + 1);
		}
		FUNC(actual, params[i].f);
		expected = (char *)params[i].expected;
		str_with_escapes(test.actual, actual, len_ini);
		str_with_escapes(test.expected, expected, len_ini);

		test_assert((actual == NULL && expected == NULL) || ((actual != NULL && expected != NULL) && memcmp(actual, expected, len_ini + 1) == 0), test);

		if(actual)
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