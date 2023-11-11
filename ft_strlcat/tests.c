/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/11 21:17:34 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_strlcat"
#define FUNC(a, b, c) ft_strlcat(a, b, c)
#define OG_FUNC(a, b, c) strlcat(a, b, c)

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
	size_t		i;
	size_t		res;
	size_t		res_og;
	char 		src[] = "A";
	char 		src_cpy[sizeof(src)];
	char 		src_og[sizeof(src)];
	char		dst[500];
	char		dst_cpy[500];
	char		dst_og[500];
	char		txt[] = "PAP";
	size_t		size[] = {0, 1, 2, 3 , 4, 5, 6, 7, 10, 20, -1};
	
	strlcpy(src_og, src, sizeof(src));
	
	// Initialize to ones
	memset(dst, 49, sizeof(dst));
	memset(dst_og, 49, sizeof(dst_og));
	dst[499] = 0;
	dst_og[499] = 0;
	// Prep dest
	strlcpy(dst, txt, sizeof(txt));
	strlcpy(dst_og, txt, sizeof(txt));
	// Savinf src and dst
	strlcpy(src_cpy, src, sizeof(src));
	strlcpy(dst_cpy, dst, sizeof(dst));

	// printf("len dst: %ld\n", strlen(dst));
	// printf("len src: %ld\n", strlen(src));

	i = 0;
	while (size[i] != -1)
	{
		sprintf(test.message, "%s(%s, %s, %ld) ; src has one char", FT, dst, src, size[i]);
		res = FUNC(dst, src, size[i]);
		res_og = OG_FUNC(dst_og, src_og, size[i]);
		sprintf(test.actual, "return value: %ld, dest:%s", res, dst);
		sprintf(test.expected, "return value: %ld, dest:%s", res_og, dst_og);

		test_assert((memcmp(dst, dst_og, sizeof(dst)) == 0) && (res == res_og), test);

		// Reinitialize dst, dst_og, src, src_og
		memcpy(dst, dst_cpy, sizeof(dst));
		memcpy(dst_og, dst_cpy, sizeof(dst));
		memcpy(src, src_cpy, sizeof(src));
		memcpy(src_og, src_cpy, sizeof(src));

		i++;
	}
}

static void	test2() {
	t_test_data	test;
	size_t		i;
	size_t		res;
	size_t		res_og;
	char 		src[] = "";
	char 		src_cpy[sizeof(src)];
	char 		src_og[sizeof(src)];
	char		dst[500];
	char		dst_cpy[500];
	char		dst_og[500];
	char		txt[] = "Koala RER M14";
	size_t		size[] = {0, 1, 2, 3 , 4, 5, 6, 7, 10, 20, -1};
	
	strlcpy(src_og, src, sizeof(src));
	
	// Initialize to ones
	memset(dst, 49, sizeof(dst));
	memset(dst_og, 49, sizeof(dst_og));
	dst[499] = 0;
	dst_og[499] = 0;
	// Prep dest
	strlcpy(dst, txt, sizeof(txt));
	strlcpy(dst_og, txt, sizeof(txt));
	// Savinf src and dst
	strlcpy(src_cpy, src, sizeof(src));
	strlcpy(dst_cpy, dst, sizeof(dst));

	// printf("len dst: %ld\n", strlen(dst));
	// printf("len src: %ld\n", strlen(src));

	i = 0;
	while (size[i] != -1)
	{
		sprintf(test.message, "%s(%s, %s, %ld) ; src is an empty string", FT, dst, src, size[i]);
		res = FUNC(dst, src, size[i]);
		res_og = OG_FUNC(dst_og, src_og, size[i]);
		sprintf(test.actual, "return value: %ld, dest:%s", res, dst);
		sprintf(test.expected, "return value: %ld, dest:%s", res_og, dst_og);

		test_assert((memcmp(dst, dst_og, sizeof(dst)) == 0) && (res == res_og), test);

		// Reinitialize dst, dst_og, src, src_og
		memcpy(dst, dst_cpy, sizeof(dst));
		memcpy(dst_og, dst_cpy, sizeof(dst));
		memcpy(src, src_cpy, sizeof(src));
		memcpy(src_og, src_cpy, sizeof(src));

		i++;
	}
}

static void	test3() {
	t_test_data	test;
	size_t		i;
	size_t		res;
	size_t		res_og;
	char 		src[] = "Visual Studio Code";
	char 		src_cpy[sizeof(src)];
	char 		src_og[sizeof(src)];
	char		dst[500];
	char		dst_cpy[500];
	char		dst_og[500];
	char		txt[] = "";
	size_t		size[] = {0, 1, 2, 3 , 4, 5, 6, 7, 10, 20, 30, -1};
	
	strlcpy(src_og, src, sizeof(src));
	
	// Initialize to ones
	memset(dst, 49, sizeof(dst));
	memset(dst_og, 49, sizeof(dst_og));
	dst[499] = 0;
	dst_og[499] = 0;
	// Prep dest
	strlcpy(dst, txt, sizeof(txt));
	strlcpy(dst_og, txt, sizeof(txt));
	// Savinf src and dst
	strlcpy(src_cpy, src, sizeof(src));
	strlcpy(dst_cpy, dst, sizeof(dst));

	// printf("len dst: %ld\n", strlen(dst));
	// printf("len src: %ld\n", strlen(src));

	i = 0;
	while (size[i] != -1)
	{
		sprintf(test.message, "%s(%s, %s, %ld); dest is an empty string", FT, dst, src, size[i]);
		res = FUNC(dst, src, size[i]);
		res_og = OG_FUNC(dst_og, src_og, size[i]);
		sprintf(test.actual, "return value: %ld, dest:%s", res, dst);
		sprintf(test.expected, "return value: %ld, dest:%s", res_og, dst_og);

		test_assert((memcmp(dst, dst_og, sizeof(dst)) == 0) && (res == res_og), test);

		// Reinitialize dst, dst_og, src, src_og
		memcpy(dst, dst_cpy, sizeof(dst));
		memcpy(dst_og, dst_cpy, sizeof(dst));
		memcpy(src, src_cpy, sizeof(src));
		memcpy(src_og, src_cpy, sizeof(src));

		i++;
	}
}



static void	test4() {
	t_test_data	test;
	size_t		i;
	size_t		res;
	size_t		res_og;
	char 		src[] = "Visual Studio Code";
	char 		src_cpy[sizeof(src)];
	char 		src_og[sizeof(src)];
	char		dst[500];
	char		dst_cpy[500];
	char		dst_og[500];
	char		txt[] = "Beaucoup de personnes utilisent ";
	size_t		size[] = {0, 1, 2, 3 , 4, 5, 6, 7, 10, 20, 30, 50, 100, 200, -1};
	
	strlcpy(src_og, src, sizeof(src));
	
	// Initialize to ones
	memset(dst, 49, sizeof(dst));
	memset(dst_og, 49, sizeof(dst_og));
	dst[499] = 0;
	dst_og[499] = 0;
	// Prep dest
	strlcpy(dst, txt, sizeof(txt));
	strlcpy(dst_og, txt, sizeof(txt));
	// Savinf src and dst
	strlcpy(src_cpy, src, sizeof(src));
	strlcpy(dst_cpy, dst, sizeof(dst));

	// printf("len dst: %ld\n", strlen(dst));
	// printf("len src: %ld\n", strlen(src));

	i = 0;
	while (size[i] != -1)
	{
		sprintf(test.message, "%s(%s, %s, %ld); dest and src have both length > 1", FT, dst, src, size[i]);
		res = FUNC(dst, src, size[i]);
		res_og = OG_FUNC(dst_og, src_og, size[i]);
		sprintf(test.actual, "return value: %ld, dest:%s", res, dst);
		sprintf(test.expected, "return value: %ld, dest:%s", res_og, dst_og);

		test_assert((memcmp(dst, dst_og, sizeof(dst)) == 0) && (res == res_og), test);

		// Reinitialize dst, dst_og, src, src_og
		memcpy(dst, dst_cpy, sizeof(dst));
		memcpy(dst_og, dst_cpy, sizeof(dst));
		memcpy(src, src_cpy, sizeof(src));
		memcpy(src_og, src_cpy, sizeof(src));

		i++;
	}
}

static void	run_tests()
{
	test1();
	test2();
	test3();
	test4();
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