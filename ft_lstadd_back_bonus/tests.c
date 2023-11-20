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
#define FT "ft_lstadd_back"
#define FUNC(a, b) ft_lstadd_back(a, b)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


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
	else {
		printf("SUCCESS: ");
		print_string_with_escapes(test.message);
		printf("\n");
		printf("    Expected: ");
		print_string_with_escapes(test.expected);
		printf("\n");
		printf("    Actual  : ");
		print_string_with_escapes(test.actual);
		printf("\n");
	}
	tests_run++;
}

static void	free_list(t_list *lst)
{
	if (lst)
	{
		free_list(lst->next);
		free(lst);
	}
}

/* Tests functions */
static void	test1() {
	t_test_data	test;
	t_list		*lst;
	t_list		*curr;
	t_list		*last_expected;
	t_list		*last_actual;
	t_list		*back_node;
	int			content[4];
	int			content_back = 9;
	size_t		i;

	content[0] = 5;
	content[1] = 6;
	content[2] = 7;
	content[3] = 8;
	
	lst = ft_lstnew(&content[0]);
	curr = lst;
	i = 1;
	while (i < sizeof(content) / sizeof(content[0]))
	{
		curr->next = ft_lstnew(&content[i]);
		curr = curr->next;
		i++;
	}

	if (lst)
		sprintf(test.message, "%s(lst = %p)", FT, lst);

	back_node = ft_lstnew(&content_back);
	last_expected = back_node;

	sprintf(test.expected, "last: %p {content: %d, next: %p}", last_expected, *(int *)last_expected->content, last_expected->next);
	
	FUNC(&lst, back_node);

	last_actual = ft_lstlast(lst);

	sprintf(test.actual, "last: %p {content: %d, next: %p}", last_actual, *(int *)last_actual->content, last_actual->next);

	test_assert((last_actual == last_expected), test);

	free_list(lst);
}

/* Tests functions */


static void	run_tests()
{
	test1();
	// test2();
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