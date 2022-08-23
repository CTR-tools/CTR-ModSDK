#define FRAME 32
#define SECOND (30 * FRAME)
#define MINUTE (60 * SECOND)
#define HOUR (60 * MINUTE)

void TimeToString(char * str, int time)
{
    int hours;
    int minutes;
    int seconds;
    int ms;
    int currentTime;

    hours = time / HOUR;

    if (hours < 1)
    {
        str[0] = ' ';
        str[1] = ' ';
    }
    else
    {
        str[1] = ':';

        if (hours > 9)
        {
            str[0] = '9';
            str[2] = '5';
            str[3] = '9';
            str[5] = '5';
            str[6] = '9';
            str[8] = '9';
            str[9] = '9';
            str[10] = '9';
            return;
        }

        str[0] = '0' + hours;
    }

    time -= (hours * HOUR);
    minutes = time / MINUTE;

    str[2] = '0' + (minutes / 10);
    str[3] = '0' + (minutes % 10);

    time -= (minutes * MINUTE);
    seconds = time / SECOND;

    str[5] = '0' + (seconds / 10);
    str[6] = '0' + (seconds % 10);

    time -= (seconds * SECOND);
    time = (time * 1000) / SECOND;

    ms = time / 100;
    str[8] = '0' + ms;

    time -= (ms * 100);
    str[9] = '0' + (time / 10);
    str[10] = '0' + (time % 10);
}