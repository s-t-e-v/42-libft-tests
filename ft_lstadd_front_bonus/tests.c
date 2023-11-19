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
#define FT "ft_lstadd_front"
#define FUNC(a, b) ft_lstadd_front(a, b)

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
	t_list		*lst;
	t_list		*new;
	t_list		*head_expected;
	t_list		*tail_expected;
	int			content1 = 5;
	int			content2 = 6;

	
	lst = ft_lstnew(&content1);
	new = ft_lstnew(&content2);

	if (lst && new)
		sprintf(test.message, "%s(lst = %p {content: %d, next: %p}, new = %p {content: %d, next: %p})", FT, lst, *(int *)lst->content, lst->next, new, *(int *)new->content, new->next);

	head_expected = new;
	tail_expected = lst;

	if (lst && new)
		sprintf(test.expected, "head = %p {content: %d, next: %p}, tail = %p {content: %d, next: %p}", head_expected, *(int *)head_expected->content, tail_expected, tail_expected, *(int *)tail_expected->content, tail_expected->next);
	
	FUNC(&lst, new);

	if (lst && lst->next)
		sprintf(test.actual, "head = %p {content: %d, next: %p}, tail = %p {content: %d, next: %p}", lst, *(int *)lst->content, lst->next, lst->next, *(int *)lst->next->content, lst->next->next);

	test_assert(lst && lst->next && 
				(lst == head_expected) && (lst->next == tail_expected) &&
				(*(int *)lst->content == *(int *)head_expected->content) &&
				(*(int *)lst->next->content ==  *(int *)tail_expected->content), test);

	if (lst)
	{
		free(lst->next);
		free(lst);
	}
}

/* Tests functions */
static void	test2() {
	t_test_data	test;
	t_list		*lst;
	t_list		*new;
	t_list		*head_expected;
	t_list		*tail_expected;
	const char	content1[] = "l'ordre.";
	const char	content2[] = "Dans ";
	char		*content_input;
	char		*content_input2;

	
	content_input = strdup(content1);
	content_input2 = strdup(content2);

	lst = ft_lstnew(content_input);
	new = ft_lstnew(content_input2);

	if (lst && new)
		sprintf(test.message, "%s(lst = %p {content: %s, next: %p}, new = %p {content: %s, next: %p})", FT, lst, (char *)lst->content, lst->next, new, (char *)new->content, new->next);

	head_expected = new;
	tail_expected = lst;

	if (lst && new)
		sprintf(test.expected, "head = %p {content: %s, next: %p}, tail = %p {content: %s, next: %p}", head_expected, (char *)head_expected->content, tail_expected, tail_expected, (char *)tail_expected->content, tail_expected->next);
	
	FUNC(&lst, new);

	if (lst && lst->next)
		sprintf(test.actual, "head = %p {content: %s, next: %p}, tail = %p {content: %s, next: %p}", lst, (char *)lst->content, lst->next, lst->next, (char *)lst->next->content, lst->next->next);

	test_assert(lst && lst->next && 
				(lst == head_expected) && (lst->next == tail_expected) &&
				!strcmp((char *)lst->content, (char *)head_expected->content) &&
				!strcmp((char *)lst->next->content, (char *)tail_expected->content), test);

	if (lst)
	{
		free(lst->next);
		free(lst);
	}
	if (content_input)
		free(content_input);
	if (content_input2)
		free(content_input2);
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