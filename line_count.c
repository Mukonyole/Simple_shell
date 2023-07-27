/**
 * line_count - count no of line in a str
 * @lines: input str
 * Return: Number of lines in str
 */
int line_count(char *lines);

int line_count(char *lines)
{
	int a = 0;

	while (*lines != '\0')
	{
		a++;
		lines++;
	}
	return (a);
}
