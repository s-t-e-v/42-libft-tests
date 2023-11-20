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
#define FT "ft_lstclear"
#define FUNC(a, b) ft_lstclear(a, b)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


void	del_int(void *content)
{
	if (content)
		free(content);
}



/* Tests functions */
static void	test1() {
	t_list		*lst;
	t_list		*curr;
	int			data[] = {5, 6, 7};
	int			*content;
	size_t		i;

	content = (int *)malloc(sizeof(int));
	if (content)
		*content = data[0];
	lst = ft_lstnew(content);
	curr = lst;
	i = 1;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		content = (int *)malloc(sizeof(int));
		if (content)
			*content = data[i];
		curr->next = ft_lstnew(content);
		curr = curr->next;
		i++;
	}
	
	FUNC(&lst, &del_int);

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