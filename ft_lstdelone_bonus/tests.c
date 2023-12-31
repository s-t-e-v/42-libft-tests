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
	t_list		*node_del;
	int			content[2];
	int			*wrong_number;

	content[0] = 5;
	content[1] = 6;
	wrong_number = (int *)malloc(sizeof(int));
	if(wrong_number)
		*wrong_number = 3;
	
	lst = ft_lstnew(wrong_number);
	curr = lst;
	node_del = lst;
	curr->next = ft_lstnew(&content[1]);

	if (lst)
		sprintf(test.message, "%s(lst = %p {content: %d, next: %p})", FT, node_del, *(int *)node_del->content, node_del->next);

	del_expected = node_del;
	del_next_expected = node_del->next;

	sprintf(test.expected, "del: ? {content: ?, next: %p}", del_next_expected);
	
	FUNC(node_del, &del_int);

	free_list(del_next_expected);

	printf("Done.\n");
	printf("-- Please check if memory was freed correctly with valgrind.\n");
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