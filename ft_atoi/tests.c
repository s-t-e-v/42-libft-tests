/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/13 16:23:38 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include <ctype.h>
#include "../../libft.h"
#define FT "ft_atoi"
#define FUNC(a) ft_atoi(a)
#define OG_FUNC(a) atoi(a)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


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
	size_t		i;
	size_t		j;
	size_t		k;
	t_test_data	test;
	char		data[][100] = {
		// valid
		"-2147483648",
		"2147483647",
		"0",
		"1",
		"9",
		"10",
		"42",
		"125",
		"5670",
		"60000000",
		"-1",
		"-9",
		"-10",
		"-42",
		"-125",
		"-5670",
		"-60000000",
		"+2147483647",
		"+0",
		"+1",
		"+9",
		"+10",
		"+42",
		"+125",
		"+5670",
		"+60000000",
		" -1",
		"      -9",
		"\n\t\v\r\f -10",
		"\n\n\n\n\n\n\t        -42",
		"-125\t\t\t\t\t",
		"-5670drgdrgdrgdrg",
		" +1",
		"\t\t\v\f\n\r +9",
		"+10ddfd86868",
		"+42\t\t\t+++",
		"           +125,r,,",
		"\v+56\t\r70",
		// invalid
		"",
		"--2147483648",
		"++2147483647",
		"s0",
		"   +*1",
		"-+-+-9",
		"awdwdawd10",
		"\n\t\v-awa42awaw",
		"\r-+125++",
		"fesfsefs",
		"\t\r\v+srsrsrsrs",
		"+ 8,",
	};
	int			res = 0;
	int			res_og = 0;
	char		data_og[sizeof(data) / sizeof(data[0])][100];
	char		data_cpy[sizeof(data) / sizeof(data[0])][100];
	
	// ---- general cases
	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		memcpy(data_cpy[i], data[i], sizeof(data[i]));
		memcpy(data_og[i], data[i], sizeof(data[i]));
		i++;
	}

	i = 0;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		sprintf(test.message, "%s(%s)", FT, data[i]);
		// printf("%s\n", test.message);
		res = FUNC(data[i]);
		res_og = OG_FUNC(data_og[i]);
		sprintf(test.actual, "%d", res);
		sprintf(test.expected, "%d", res_og);

		test_assert(res == res_og, test);

		// reinitialize current big and little and og variables
		memcpy(data, data_cpy, sizeof(data_cpy));
		memcpy(data_og, data_cpy, sizeof(data_cpy));

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