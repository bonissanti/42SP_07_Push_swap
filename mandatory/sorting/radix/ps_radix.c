/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_radix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:16:20 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/02 18:49:56 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

// int find_index(t_stack *stack, int value);
// void	print_index_values(t_stack *stack);
int	ft_pow(int base, int exp);
int	find_max(t_node *head);

void	normalize_sort(t_stack *stack)
{
	int i;
	int count;
	int *array;
	t_node *current;
	t_node *runner;

	array = (int *)malloc(sizeof(int) * stack->size_a);
	if (!array)
		exit(1);

	i = 0;
	current = stack->head_a;
	
	while (current)
	{
		count = 0;
		runner = stack->head_a;
		while (runner)
		{
			if (current->value > runner->value)
				count++;
			runner = runner->next;
			
		}
		array[i++] = count;
		current = current->next;
	}
	i = 0;
	current = stack->head_a;
	while (current)
	{
		current->value = array[i++];
		current = current->next;
	}
	// print_index_values(stack);
	free(array);
}


// int find_index(t_stack *stack, int value)
// {
// 	int index;
// 	t_node *current;

// 	index = 0;
// 	current = stack->head_a;

// 	while (current)
// 	{
// 		if (current->value == value)
// 			return (index);
// 		index++;
// 		current = current->next;
// 	}
// 	return (-1);
// }

// void	print_index_values(t_stack *stack)
// {
// 	t_node *current;

// 	current = stack->head_a;

// 	while (current)
// 	{
// 		ft_printf("Value: %d, Index: %d\n", current->value, find_index(stack, current->value));
// 		current = current->next;
// 	}
// }



void	radix_sort(t_stack *stack)
{
	int i;
	int j;
	int max_num;
	int num_digits;
	t_node *current;

	max_num = find_max(stack->head_a);
	num_digits = 0;
	
	while (max_num > 0)
	{
		max_num /= 10;
		num_digits++;
	}

	i = -1;
	while (++i < num_digits)
	{
		current = stack->head_a;
		while (current)
		{
			j = (current->value) / ft_pow(10, i) % 10;
			if (j % 2 == 0)
				push_a_to_b(stack);
			else
				rotate(&stack->head_a, 'a', stack);
			current = current->next;	
		}
		radix_sort_stack_b(stack, num_digits, i);	
	}
	
}

void	radix_sort_stack_b(t_stack *stack, int num_digits, int i)
{
	int j;
	t_node *current;
	
	current = stack->head_b;
	while (current && i < num_digits && !is_sorted(stack->head_a))
	{
		j = (current->value) / ft_pow(10, i) % 10;
		if (j % 2 == 0)
			rotate(&stack->head_b, 'b', stack);
		else
			push_b_to_a(stack);
		current = current->next;
	}
	if (is_sorted(stack->head_a))
	{
		while (stack->head_b)
			push_b_to_a(stack);
	}
}

int	find_max(t_node *head)
{
	int	max;
	t_node *current;

	current = head;
	max = head->value;

	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);	
}

int	ft_pow(int base, int exp)
{
	int	i;
	int result;
	
	i = 0;
	result = 1;
	while (i++ < exp)
		result *= base;
	return (result);
}