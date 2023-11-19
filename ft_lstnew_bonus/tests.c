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
#include <fcntl.h>
#include "../../libft.h"
#define FT "ft_lstnew"
#define FUNC(a) ft_lstnew(a)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


typedef struct s_params {
	const char	*s;
	const char	*expected;
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

/* Tests functions */
static void	test1() {
	t_test_data	test;
	const int	content = 5;
	int			content_input = content;
	t_list		*lst;
	
	sprintf(test.message, "%s(%d)", FT, content);

	lst = FUNC(&content_input);

	if (lst)
		sprintf(test.actual, "next = %p, content = %d", lst->next, *(int *)lst->content);
	sprintf(test.expected, "next = %p, content = %d", NULL, content);

	test_assert(lst && lst->next == NULL && *(int *)lst->content == content, test);

	if (lst)
		free(lst);
}

static void	test2() {
	t_test_data	test;
	const char	content[] = "Dormir c'est cool";
	char		*content_input;
	t_list		*lst;
	
	sprintf(test.message, "%s(\"%s\")", FT, content);

	content_input = strdup(content);

	lst = FUNC(content_input);

	if (lst)
		sprintf(test.actual, "next = %p, content = %s", lst->next, (char *)lst->content);
	sprintf(test.expected, "next = %p, content = %s", NULL, content);

	test_assert(lst && lst->next == NULL && !strcmp(content, (char *)lst->content), test);

	if (lst)
		free(lst);
	if (content_input)
		free(content_input);
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