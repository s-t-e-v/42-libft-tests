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
#define FT "ft_lstdelone"
#define FUNC(a, b) ft_lstdelone(a, b)

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
		lst = NULL;
	}
}

void	del_int(void *content)
{
	if (content)
		free(content);
}

/* Tests functions */
static void	test1() {
	t_test_data	test;
	t_list		*lst;
	t_list		*curr;
	t_list		*del_expected;
	t_list		*del_next_expected;
	t_list		*del_actual;
	t_list		*del_next_actual;
	t_list		*node_del;
	int			content[4];
	int			*wrong_number;
	size_t		i;

	content[0] = 5;
	content[1] = 6;
	content[2] = 7;
	content[3] = 8;
	wrong_number = (int *)malloc(sizeof(int));
	if(wrong_number)
		*wrong_number = 3;
	
	lst = ft_lstnew(&content[0]);
	curr = lst;
	i = 1;
	while (i < sizeof(content) / sizeof(content[0]))
	{
		if (i == 2)
			curr->next = ft_lstnew(wrong_number);
		else
			curr->next = ft_lstnew(&content[i]);
			
		curr = curr->next;

		if (i == 2)
			node_del = curr;
		i++;
	}

	if (lst)
		sprintf(test.message, "%s(lst = %p {content: %d, next: %p})", FT, node_del, *(int *)node_del->content, node_del->next);

	del_expected = node_del;
	del_next_expected = node_del->next;

	sprintf(test.expected, "last: %p {content: %p, next: %p}", del_expected, NULL, del_next_expected);
	
	FUNC(node_del, &del_int);

	del_actual = node_del;
	del_next_actual = node_del->next;

	sprintf(test.actual, "last: %p {content: %p, next: %p}", del_actual, del_actual->content, del_actual->next);

	test_assert((del_actual ==  0 && del_expected == 0) || 
				(del_actual && del_expected && 
					(del_actual == del_expected) && 
					(del_actual->content == NULL) &&
					(del_next_actual == del_next_expected)), test);

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