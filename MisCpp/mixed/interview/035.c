#include <stdio.h>

void get_clock_meet_times()
{
    int hour = 24;
    int minute = 60;
    int second = 60;

    int h_m_s_meet = 0;
    int h_m_meet = 0;
    int m_s_one_hour_meet = 0;

    int h, m, s;
    for(h=0; h<hour; h++)
    {
        for(m=0; m<minute; m++)
        {
            if(h == m)
            {
                h_m_meet++;
                //printf("h_m[%d:%d:%d]\n", h, m, s);
            }

            for(s=0; s<second; s++)
            {
                if(h == m && h == s && m== s)
                {
                    h_m_s_meet++;
                    //printf("h_m_s[%d:%d:%d]\n", h, m, s);
                }
                if(h==0 && m==s)
                {
                    m_s_one_hour_meet++;
                    //printf("m_s[%d:%d:%d]\n", h, m, s);
                }
            }
        }
    }
    printf("h_m_s_meet--->%d\n", h_m_s_meet);
    printf("h_m_meet--->%d\n", h_m_meet);
    printf("m_s_one_hour_meet--->%d\n", m_s_one_hour_meet);
}

int main()
{
   get_clock_meet_times();
}
