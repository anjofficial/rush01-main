#include <unistd.h>
#include <stdlib.h>

int g_input[16];
int g_grid[4][4];

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

void print_grid()
{
    int i = 0;
    int j = 0;

    if (i < 4)
    {
        if (j < 4)
        {
            ft_putchar(g_grid[i][j] + '0');
            ft_putchar(' ');
            j++;
        }
        else
        {
            ft_putchar('\n');
            i++;
            j = 0;
        }
        print_grid();
    }
}

void parse_input(char *input, int idx)
{
    if (idx < 16)
    {
        g_input[idx] = input[idx] - '0';
        parse_input(input, idx + 1);
    }
}

int is_valid(int row, int col, int num, int i)
{
    if (i < 4)
    {
        if (g_grid[row][i] == num || g_grid[i][col] == num)
            return 0;
        return is_valid(row, col, num, i + 1);
    }
    return 1;
}

int check_row_left(int row, int idx, int max, int count)
{
    if (idx < 4)
    {
        if (g_grid[row][idx] > max)
        {
            max = g_grid[row][idx];
            count++;
        }
        return check_row_left(row, idx + 1, max, count);
    }
    return (count == g_input[8 + row]);
}

int check_row_right(int row, int idx, int max, int count)
{
    if (idx >= 0)
    {
        if (g_grid[row][idx] > max)
        {
            max = g_grid[row][idx];
            count++;
        }
        return check_row_right(row, idx - 1, max, count);
    }
    return (count == g_input[12 + row]);
}

int check_col_up(int col, int idx, int max, int count)
{
    if (idx < 4)
    {
        if (g_grid[idx][col] > max)
        {
            max = g_grid[idx][col];
            count++;
        }
        return check_col_up(col, idx + 1, max, count);
    }
    return (count == g_input[col]);
}

int check_col_down(int col, int idx, int max, int count)
{
    if (idx >= 0)
    {
        if (g_grid[idx][col] > max)
        {
            max = g_grid[idx][col];
            count++;
        }
        return check_col_down(col, idx - 1, max, count);
    }
    return (count == g_input[4 + col]);
}

int check_validity(int i)
{
    if (i < 4)
    {
        if (!check_row_left(i, 0, 0, 0) || !check_row_right(i, 3, 0, 0) ||
            !check_col_up(i, 0, 0, 0) || !check_col_down(i, 3, 0, 0))
            return 0;
        return check_validity(i + 1);
    }
    return 1;
}

int solve(int row, int col, int num)
{
    if (row == 4)
        return check_validity(0);
    if (col == 4)
        return solve(row + 1, 0, 1);
    if (num <= 4)
    {
        if (is_valid(row, col, num, 0))
        {
            g_grid[row][col] = num;
            if (solve(row, col + 1, 1))
                return 1;
            g_grid[row][col] = 0;
        }
        return solve(row, col, num + 1);
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_putstr("Error\n");
        return 1;
    }
    parse_input(argv[1], 0);
    if (solve(0, 0, 1))
        print_grid();
    else
        ft_putstr("Error\n");
    return 0;
}
