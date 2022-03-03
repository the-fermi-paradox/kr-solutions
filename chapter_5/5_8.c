static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int is_leap(int year)
{
  return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int day_of_year(int year, int month, int day)
{
  int i, leap;
  leap = is_leap(year);
  if (month > 12 || month < 1 || day < 1 || day > daytab[leap][month])
    return -1;
  for (i = 1; i < month; ++i)
    day += daytab[leap][i];
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
  leap = is_leap(year);
  if (yearday > (leap ? 366 : 365) || yearday <= 0)
    return;

  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];

  *pmonth = i;
  *pday = yearday;
}
