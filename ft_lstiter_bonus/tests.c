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
#define FT "ft_lstiter"
#define FUNC(a, b) ft_lstiter(a, b)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


// Function to convert an array of integers to a string
void arrayToString(int arr[], int size, char result[]) {
    // Check if the array is empty
    if (size == 0) {
        snprintf(result, 3, "{}");
        return;
    }

    // Initialize the result string with the opening brace
    snprintf(result, 6, "{%d", arr[0]); // Increase the size for the first element

    // Concatenate each element to the string
    for (int i = 1; i < size; i++) {
        snprintf(result + strlen(result), 6, ", %d", arr[i]); // Adjust the width for other elements
    }

    // Add the closing brace
    snprintf(result + strlen(result), 2, "}");
}

void	del_int(void *content)
{
	if (content)
		free(content);
}

void	print_linked_list_int(t_list *lst)
{
	printf ("lst: %p\n", lst);
	if (lst == 0)
		return ;
	while (lst->next)
	{
		printf("node: %p {content: %d, next: %p}\n", lst, *(int *)lst->content, lst->next);
		lst = lst->next;
	}
	printf("node: %p {content: %d, next: %p}\n", lst, *(int *)lst->content, lst->next);
}

void	times10(void *data)
{
	int	*n;

	n = (int *)data;
	*n = *n * 10;
}

int	check_content_int(t_list *lst, int content_expected[], size_t size)
{
	size_t	i;

	if (lst == 0)
		return (0);
	i = 0;
	while (lst->next && i < size)
	{
		if (*(int *)lst->content != content_expected[i])
			return (0);
		lst = lst->next;
		i++;
	}
	if (i < size - 1 || *(int *)lst->content != content_expected[i])
		return (0);
	return (1);
}

/* Test assert function */
static void	test_assert(int condition, t_test_data test)
{
	if (!condition) {
		tests_failed++;
		printf("FAIL: ");
		printf("\n");
		printf("    Expected: ");
		printf("content values: %s\n", test.expected);
		printf("\n");
	}
	else {
		printf("SUCCESS: ");
		printf("\n");
		printf("    Expected: ");
		printf("content values: %s\n", test.expected);
		printf("\n");
	}
	tests_run++;
}



/* Tests functions */
static void	test1() {
	t_test_data	test;
	t_list		*lst;
	t_list		*curr;
	int			data[] = {5, 6, 7, 8, 9};
	int			content_expected[sizeof(data) / sizeof(data[0])];
	int			size = sizeof(data) / sizeof(data[0]);
	int			*content;
	size_t		i;

	// gen a linked list
	content = (int *)malloc(sizeof(int));
	if (content)
		*content = data[0];
	content_expected[0] = data[0] * 10;
	lst = ft_lstnew(content);
	curr = lst;
	i = 1;
	while (i < sizeof(data) / sizeof(data[0]))
	{
		content = (int *)malloc(sizeof(int));
		if (content)
			*content = data[i];
		content_expected[i] = data[i] * 10;
		curr->next = ft_lstnew(content);
		curr = curr->next;
		i++;
	}

	printf("Before:\n");
	print_linked_list_int(lst);
	// Convert the array to a string
    arrayToString(content_expected, size, test.expected);
	
	FUNC(lst, &times10);
	printf("After:\n");
	print_linked_list_int(lst);

	test_assert(check_content_int(lst, content_expected, size), test);

	ft_lstclear(&lst, &del_int);
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