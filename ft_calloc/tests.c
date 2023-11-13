/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbandaog <sbandaog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:35:34 by sbandaog          #+#    #+#             */
/*   Updated: 2023/11/13 18:05:17 by sbandaog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../../libft.h"
#define FT "ft_calloc"
#define FUNC(a, b) ft_calloc(a, b)
#define OG_FUNC(a, b) calloc(a, b)

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
	t_test_data	test;
	
	size_t	nmemb[] = {
		0,
		1,
		5,
		10,
		sizeof(size_t),
	};
	size_t	size = sizeof(char);
	char		*res = 0;
	int			*res_og = 0;
	char		nmemb_og[sizeof(nmemb) / sizeof(nmemb[0])];
	char		nmemb_cpy[sizeof(nmemb) / sizeof(nmemb[0])];
	
	// ---- general cases
	memcpy(nmemb, nmemb, sizeof(nmemb));
	memcpy(nmemb_cpy, nmemb, sizeof(nmemb));

	i = 0;
	while (i < sizeof(nmemb) / sizeof(nmemb[0]))
	{
		sprintf(test.message, "%s(%zu, %zu)", FT, nmemb[i], size);
		// printf("%s\n", test.message);
		res = FUNC(nmemb[i], size);
		res_og = OG_FUNC(nmemb_og[i], size);
		sprintf(test.actual, "\\x%02x", *res);
		sprintf(test.expected, "\\x%02x", *res_og);

		test_assert((res == NULL && res_og == NULL) || ((res != NULL && res_og != NULL) && (memcmp(res, res_og, nmemb[i]*size) == 0)), test);

		// Free allocated values
		if (res)
			free(res);
		if (res_og)
			free(res_og);

		// reinitialize current big and little and og variables
		memcpy(nmemb, nmemb_cpy, sizeof(nmemb_cpy));
		memcpy(nmemb, nmemb_cpy, sizeof(nmemb_cpy));

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