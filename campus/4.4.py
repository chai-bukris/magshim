def gen_secs():
    for sec in range(60):
        yield sec


def gen_hours():
    for hour in range(24):
        yield hour


def gen_minutes():
    for minute in range(60):
        yield minute


def gen_time():
    for hour in gen_hours():
        for minute in gen_minutes():
            for second in gen_secs():
                yield f"{hour:02d}:{minute:02d}:{second:02d}"


def gen_years(start=2025):
    while True:
        yield start
        start += 1


def gen_months():
    for month in range(1, 13):
        yield month


def gen_days(month, leap_year=True):
    days = 30
    if month in [1, 3, 5, 7, 8, 10, 12]:
        days = 31
    elif month == 2:
        if leap_year:
            days = 29
        else:
            days = 28
    for day in range(1, days + 1):
        yield day


def gen_date():
    for year in gen_years():
        leap = (year % 4 == 0 and (year % 100 != 0 or year % 400 == 0))
        for month in gen_months():
            for day in gen_days(month, leap):
                for hour in gen_hours():
                    for minute in gen_minutes():
                        for second in gen_secs():
                            yield f"{day:02d}/{month:02d}/{year} {hour:02d}:{minute:02d}:{second:02d}"


date_gen = gen_date()

for i in range(1, 10_000_001):
    current_time = next(date_gen)
    if i % 1_000_000 == 0:
        print(current_time)
