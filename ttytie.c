#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ttytie.h"

int read_header (FILE* fp,
                 int* sec, int* usec, int* len);
void write_header (int sec, int usec, int len);

int ttytie (int argc, char const* argv[], double delay)
{
    int alloc_size = 2048;
    char* data = malloc (alloc_size);

    int const delay_sec = (int)floor (delay);
    int const delay_usec = (int)floor ((fmod (delay, 1.0) * 100));

    int sec = 0, usec = 0, len = 0;
    int d_sec = 0, d_usec = 0;

    for (int file_no = 0; file_no < argc; ++file_no)
    {
        FILE* fp = fopen (argv[file_no], "r");

        int first_sec = 0, first_usec = 0;
        if (!read_header (fp, &first_sec, &first_usec, &len))
            continue;

        if (file_no > 0)
        {
            int expected_sec = sec + delay_sec;
            int expected_usec = usec + delay_usec;

            d_sec = expected_sec - first_sec;
            d_usec = expected_usec - first_usec;
        }

        sec = first_sec;
        usec = first_usec;

        do
        {
            sec += d_sec;
            usec += d_usec;
            write_header (sec, usec, len);
            
            if (len > alloc_size)
            {
                free (data);
                data = malloc(len);
            }    

            if (len != fread (data, 1, len, fp))
                break;

            fwrite (data, 1, len, stdout);
        } while (read_header (fp, &sec, &usec, &len));

	fclose (fp);
    } 

    free (data);
    return 0;
}

int read_header (FILE* fp, 
                 int* sec, int* usec, int* len)
{
    unsigned char header[12];
    if (fread(header, 1, 12, fp) != 12)
        return 0;

    unsigned sec_u = 
	    (((((header[3]   << 8)  | 
                 header[2])  << 8)  | 
                 header[1])  << 8)  | 
                 header[0];
    unsigned usec_u =
	    (((((header[7]   << 8)  |
                 header[6])  << 8)  |
                 header[5])  << 8)  | 
                 header[4];
    unsigned len_u =
	    (((((header[11]  << 8)  |
                 header[10]) << 8)  |
                 header[9])  << 8)  |
                 header[8];

    *sec = (int) sec_u;
    *usec = (int) usec_u;
    *len = (int) len_u;

    return 1;
}

void write_header (int sec, int usec, int len)
{
    unsigned char header[12];
    unsigned sec_u = (unsigned) sec;
    unsigned usec_u = (unsigned) usec;
    unsigned len_u = (unsigned) len;

    header[0]  = (sec_u >> 0)  & 0xFF;
    header[1]  = (sec_u >> 8)  & 0xFF;
    header[2]  = (sec_u >> 16) & 0xFF;
    header[3]  = (sec_u >> 24) & 0xFF;

    header[4]  = (usec_u >> 0)  & 0xFF;
    header[5]  = (usec_u >> 8)  & 0xFF;
    header[6]  = (usec_u >> 16) & 0xFF;
    header[7]  = (usec_u >> 24) & 0xFF;

    header[8]  = (len_u >> 0)  & 0xFF;
    header[9]  = (len_u >> 8)  & 0xFF;
    header[10] = (len_u >> 16) & 0xFF;
    header[11] = (len_u >> 24) & 0xFF;

    fwrite (header, 1, 12, stdout);
}
