/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/11 19:38:36 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_strlcpy"
#define FUNC(a, b, c) ft_strlcpy(a, b, c)
#define OG_FUNC(a, b, c) strlcpy(a, b, c)

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
	tests_run++;
}

/* Tests functions */
static void	test1() {
	t_test_data	test;
	size_t		res;
	size_t		res_og;
	char 		src[] = "A";
	char 		src_og[sizeof(src)];
	char		dst[100];
	char		dst_og[100];
	
	strlcpy(src_og, src, sizeof(src));
	
	// Initialize to ones
	memset(dst, 49, sizeof(dst));
	memset(dst_og, 49, sizeof(dst_og));
	dst[99] = 0;
	dst_og[99] = 0;

	sprintf(test.message, "%s(%s, %s, %ld)", FT, "dest", src, sizeof(src));
	res = FUNC(dst, src, sizeof(src));
	res_og = OG_FUNC(dst_og, src_og, sizeof(src_og));
	sprintf(test.actual, "return value: %ld, dest:%s", res, dst);
	sprintf(test.expected, "return value: %ld, dest:%s", res_og, dst_og);


	test_assert((memcmp(dst, dst_og, sizeof(src)) == 0) && (res == res_og), test);
}

static void	test2() {
	t_test_data	test;
	size_t		res;
	size_t		res_og;
	char 		src[] = "";
	char 		src_og[] = "";
	char		dst[100];
	char		dst_og[100];
	
	// Initialize to ones
	memset(dst, 49, sizeof(dst));
	memset(dst_og, 49, sizeof(dst_og));
	dst[99] = 0;
	dst_og[99] = 0;
	

	sprintf(test.message, "%s(%s, %s, %ld)", FT, "dest", src, sizeof(src));
	res = FUNC(dst, src, sizeof(src));
	res_og = OG_FUNC(dst_og, src_og, sizeof(src_og));
	sprintf(test.actual, "%ld", res);
	sprintf(test.expected, "%ld", res_og);

	test_assert((memcmp(dst, dst_og, sizeof(src)) == 0) && (res == res_og), test);
}

static void	test3() {
	t_test_data	test;
	size_t		res;
	size_t		res_og;
	char 		src[] = "Je vais faire des pates ce soir";
	char 		src_og[sizeof(src)];
	char		dst[100];
	char		dst_og[100];
	
	strlcpy(src_og, src, sizeof(src));
	sprintf(test.message, "%s(%s, %s, %ld)", FT, "dest", src, sizeof(src));
	
	// Initialize to ones
	memset(dst, 49, sizeof(dst));
	memset(dst_og, 49, sizeof(dst_og));
	dst[99] = 0;
	dst_og[99] = 0;

	res = FUNC(dst, src, sizeof(src));
	res_og = OG_FUNC(dst_og, src_og, sizeof(src_og));
	sprintf(test.actual, "return value: %ld, dest:%s", res, dst);
	sprintf(test.expected, "return value: %ld, dest:%s", res_og, dst_og);

	test_assert((memcmp(dst, dst_og, sizeof(src)) == 0) && (res == res_og), test);
}



static void	run_tests()
{
	test1();
	test2();
	test3();
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