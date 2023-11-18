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
#define FT "ft_putendl_fd"
#define FUNC(a, b) ft_putendl_fd(a, b)

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

static void str_with_escapes(char *dest, const char *s, size_t size) {
    size_t i = 0;

	if (s == NULL)
	{
		sprintf(dest, "%s", s);
		return ;
	}

    dest[0] = '"';
	dest++;
	i = 0;
    while (i < size) {

		if (isprint((unsigned char)s[i])) {
			sprintf(dest, "%c", s[i]);
		} else {
			sprintf(dest, "\\x%02x", (unsigned char)s[i]);
		}
        // // Move the pointer to the end of the current string
        while (*dest)
            dest++;
		i++;
    }
	sprintf(dest, "\"");
}


/* Tests functions */
static void	test1() {
	size_t i;
	t_test_data test;
	t_params params[] = {
		{NULL, NULL},
		{"", "\n"},
		{"\0", "\n"},
		{"\n", "\n\n"},
		{"0", "0\n"},
		{"Tata", "Tata\n"},
	};
	
	char	*expected;
	char 	*actual; // buffer actual output
	char	input_msg[100] = {0};
	char	*s; // to copy string litteral
	int		fd;
	size_t	len;
	const char* temp_file = "temp_output.txt";
	int		s_not_null;
	
	i = 0;
	while (i < sizeof(params) / sizeof(params[0]))
	{
		actual = 0;
		s = 0;
		// Create a temporary file to capture the output
		fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		s_not_null = (params[i].s != 0);
		if (s_not_null)
			len = strlen(params[i].s);
		str_with_escapes(input_msg, params[i].s, len);
		if (s_not_null)
			sprintf(test.message, "%s(%s, %d)", FT, input_msg, fd);
		else
			sprintf(test.message, "%s(%s, %d)", FT, params[i].s, fd);

		if (s_not_null)
		{
			s = (char *)malloc((len + 1) * sizeof(char));
			if (s)
				memcpy(s, params[i].s, len + 1);
		}
		FUNC(s, fd);

		// Close the file descriptor
		close(fd);

		// Open the file again for reading
		fd = open(temp_file, O_RDONLY);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}

		if (s_not_null)
		{
			actual = (char *)malloc(((len + 1) + 1) * sizeof(char));
			if (actual)
			{
				read(fd, actual, len + 1);
				actual[len + 1] = 0;
			}

		}
		

		// Close and delete the temporary file
		close(fd);
		remove(temp_file);

		expected = (char *)params[i].expected;
		str_with_escapes(test.actual, actual, len + 1);
		str_with_escapes(test.expected, expected, len + 1);

		test_assert((actual == NULL && expected == NULL) || ((actual != NULL && expected != NULL) && (memcmp(actual, expected, len + 1) == 0)), test);

		if (actual)
			free(actual);
		if (s)
			free(s);
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