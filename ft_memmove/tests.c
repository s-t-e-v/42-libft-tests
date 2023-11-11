/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/11 18:23:50 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include "../../libft.h"
#define FT "ft_memmove"
#define FUNC(a, b, c) ft_memmove(a, b, c)
#define OG_FUNC(a, b, c) memmove(a, b, c)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


/* Test assert function */
static void	test_assert(int condition, const char *message)
{
	if (!condition) {
		tests_failed++;
		printf("FAIL: %s\n", message);
	}
	tests_run++;
}

/* Tests functions */
static void	test1() {
	t_test_data	test;
	char		res;
	char		res_og;
	char 		src = 'A';

	FUNC(&res, &src, sizeof(src));
	OG_FUNC(&res_og, &src, sizeof(src));
	sprintf(test.message, "%s(%s, %d, %ld)", FT, "dest", src, sizeof(src));


	test_assert(memcmp(&res, &res_og, sizeof(src)) == 0, test.message);
}

static void	test2() {
	t_test_data	test;
	char		res[1000];
	char		res_og[1000];
	char 		src[] = "Je suis vieux";

	FUNC(res, src, sizeof(src));
	OG_FUNC(res_og, src, sizeof(src));
	sprintf(test.message, "%s(%s, %s, %ld)", FT, "dest", src, sizeof(src));


	test_assert(memcmp(res, res_og, sizeof(src)) == 0, test.message);
}

static void	test3() {
	t_test_data	test;
	char		res[1000];
	char		res_og[1000];
	char 		*src = res + 3;
	char 		*src_og = res_og + 3;
	char		txt[] = "Je suis tres tres vieux";

	int	i;

	i = 0;
	while (i < strlen(txt))
	{
		src[i] = txt[i];
		src_og[i] = txt[i];
		i++;
	}

	FUNC(res, src, sizeof(txt));
	OG_FUNC(res_og, src_og, sizeof(txt));
	sprintf(test.message, "%s(%s, %s, %ld) ; dest and src overlaps: src before dest", FT, "dest", txt, sizeof(txt));

	test_assert(memcmp(res, res_og, sizeof(txt)) == 0, test.message);
}

static void	test4() {
	t_test_data	test;
	char		bf[1000];
	char		bg_og[1000];
	char 		*src = bf;
	char 		*src_og = bf;
	char		*dest = src + 5;
	char		*dest_og = src_og + 5; 
	char		txt[] = "Je suis vraiment tres vieux";

	int	i;

	i = 0;
	while (i < strlen(txt))
	{
		src[i] = txt[i];
		src_og[i] = txt[i];
		i++;
	}

	FUNC(dest, src, sizeof(txt));
	OG_FUNC(dest_og, src_og, sizeof(txt));
	sprintf(test.message, "%s(%s, %s, %ld) ; dest and src overlaps: dest before src", FT, "dest", txt, sizeof(txt));

	test_assert(memcmp(dest, dest_og, sizeof(txt)) == 0, test.message);
}

static void	test5() {
	t_test_data	test;
	char		bf[1000];
	char		bg_og[1000];
	char 		*src = bf;
	char 		*src_og = bf;
	char		*dest = src;
	char		*dest_og = src_og; 
	char		txt[] = "La vie, la vie, c'est la vie";

	int	i;

	i = 0;
	while (i < strlen(txt))
	{
		src[i] = txt[i];
		src_og[i] = txt[i];
		i++;
	}

	FUNC(dest, src, sizeof(txt));
	OG_FUNC(dest_og, src_og, sizeof(txt));
	sprintf(test.message, "%s(%s, %s, %ld) ; dest and src overlaps: dest = src", FT, "dest", txt, sizeof(txt));

	test_assert(memcmp(dest, dest_og, sizeof(txt)) == 0, test.message);
}

/* Run tests */
static void	run_tests()
{
	test1();
	test2();
	test3();
	test4();
	test5();
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