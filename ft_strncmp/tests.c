/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/12 23:58:16 by sbandaog           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_strncmp"
#define FUNC(a, b, c) ft_strncmp(a, b, c)
#define OG_FUNC(a, b, c) strncmp(a, b, c)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


/* Test assert function */
static void	test_assert(int condition, t_test_data test)
{
	if (!condition) {
		tests_failed++;
		printf("FAIL: %s\n", test.message);
		printf("    Expected: %s\n", test.expected);
		printf("    Actual: %s\n", test.actual);
	}
	else {
		printf("SUCCESS: %s\n", test.message);
		printf("    Expected: %s\n", test.expected);
		printf("    Actual: %s\n", test.actual);
	}
	tests_run++;
}

/* Tests functions */
static void	test1() {
	t_test_data	test;
	int			res;
	int			res_og;
	char		res_str = 0;
	char		res_str_og = 0;
	char 		s1[] = "Aaa";
	char 		s2[] = "Aaaaa";
	char 		s1_og[] = "Aaa";
	char 		s2_og[] = "Aaaaa";
	size_t		n = 3;
	size_t		n_og = n;
	
	sprintf(test.message, "%s(%s, %s, %ld)", FT, s1, s2, n);
	res = FUNC(s1, s2, n);
	res_og = OG_FUNC(s1_og, s2_og, n_og);
	printf("expected: %d\n", res_og);
	printf("actual: %d\n", res);
	if (res > 0)
    	res_str = '>';
	else if (res < 0)
    	res_str = '<';
	else
    	res_str = '=';
	if (res_og > 0)
		res_str_og = '>';
	else if (res_og < 0)
		res_str_og = '<';
	else
		res_str_og = '=';
	sprintf(test.actual, "return value %c 0", res_str);
	sprintf(test.expected, "return value %c 0", res_str_og);


	test_assert(res_str == res_str_og, test);
}

static void	test2() {
	t_test_data	test;
	int			res;
	int			res_og;
	char		res_str = 0;
	char		res_str_og = 0;
	char 		s1[] = "t";
	char 		s2[] = "";
	char 		s1_og[] = "t";
	char 		s2_og[] = "";
	size_t		n = 0;
	size_t		n_og = n;
	
	sprintf(test.message, "%s(%s, %s, %ld)", FT, s1, s2, n);
	res = FUNC(s1, s2, n);
	res_og = OG_FUNC(s1_og, s2_og, n_og);
	printf("expected: %d\n", res_og);
	printf("actual: %d\n", res);
	if (res > 0)
    	res_str = '>';
	else if (res < 0)
    	res_str = '<';
	else
    	res_str = '=';
	if (res_og > 0)
		res_str_og = '>';
	else if (res_og < 0)
		res_str_og = '<';
	else
		res_str_og = '=';
	sprintf(test.actual, "return value %c 0", res_str);
	sprintf(test.expected, "return value %c 0", res_str_og);


	test_assert(res_str == res_str_og, test);
}


static void	run_tests()
{
	test1();
	test2();
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