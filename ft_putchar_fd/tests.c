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
#define FT "ft_putchar_fd"
#define FUNC(a, b) ft_putchar_fd(a, b)

static int tests_run = 0;
static int tests_failed = 0;

typedef struct s_test_data {
	char expected[1000];
	char actual[1000];
	char message[1000]; // Make sure this is large enough to hold your message
} t_test_data;


typedef struct s_params {
	const char	c;
	const char	expected;
	const int	fd;
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
		{'\0', '\0'},
		{'\n', '\n'},
		{'0', '0'},
		{'9', '9'},
		{'a', 'a'},
		{'T', 'T'},
	};
	
	char 	actual;
	char	expected;
	int		fd;
	const char* temp_file = "temp_output.txt";
	
	i = 0;
	while (i < sizeof(params) / sizeof(params[0]))
	{
		// Create a temporary file to capture the output
		fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}

		if (isprint((unsigned char)params[i].c))
			sprintf(test.message, "%s('%c', %d)", FT, params[i].c, fd);
		else
			sprintf(test.message, "%s('\\x%02x', %d)", FT, params[i].c, fd);
		

		FUNC(params[i].c, fd);

		// Close the file descriptor
		close(fd);

		// Open the file again for reading
		fd = open(temp_file, O_RDONLY);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}

		read(fd, &actual, 1);

		// Close and delete the temporary file
		close(fd);
		remove(temp_file);

		expected = params[i].expected;
		sprintf(test.actual, isprint((unsigned char)actual) ? "'%c'": "'\\x%02x'", actual);
		sprintf(test.expected, isprint((unsigned char)expected) ? "'%c'": "'\\x%02x'", expected);

		test_assert((memcmp(&actual, &expected, 1) == 0), test);

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