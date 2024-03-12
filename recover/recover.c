#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;

int number_of_bytes_in_file(string filename, FILE *file);
bool jpegcheck(BYTE copy_of_file_array[], int n);
char *make_jpg_name(int photo_number);

int main(int argc, string argv[])
{
    //check usage
    if (argc != 2)
    {
        printf("Please enter image name.\n");
        return 1;
    }

    string imageFile = argv[1];

    //open the file
    FILE *file = fopen(imageFile, "r");

    if (file == NULL)
    {
        printf("The file cannot be opened.\n");
        return 1;
    }

    int number_of_bytes = number_of_bytes_in_file(imageFile, file);
    BYTE copy_of_file_array[number_of_bytes];
    BYTE c;

    fread(&copy_of_file_array[0], sizeof(BYTE), number_of_bytes, file);

    int photo_number = 0;
    for (int n = 0; n < number_of_bytes; n=n+512)
    {
        if(jpegcheck(copy_of_file_array, n))
        {
            //create a new file
            char *photo_name = make_jpg_name(photo_number);

            //printf("photo name 2: %s\n", photo_name);
            char stupid[8];
            sprintf(stupid, "%s", photo_name);
            //printf("photo name 3: %s\n", stupid);

            FILE *new_photo = fopen(stupid, "w");

            int n_copy = n;
            fwrite(&copy_of_file_array[n_copy], sizeof(BYTE), 512, new_photo);
            n_copy = n_copy + 512;
            while(!jpegcheck(copy_of_file_array, n_copy) && n_copy < number_of_bytes)
            {
                fwrite(&copy_of_file_array[n_copy], sizeof(BYTE), 512, new_photo);
                n_copy = n_copy + 512;
            }

            photo_number++;
            fclose(new_photo);
        }
    }
    fclose(file);
}

int number_of_bytes_in_file(string filename, FILE *file)
{
    //open file
    file = fopen(filename, "r");

    int number_of_bytes = 0;
    char c;

    //read the file
    while (fread(&c, sizeof(BYTE), 1, file))
    {
        number_of_bytes++;
    }

    return number_of_bytes;
    fclose(file);
}

bool jpegcheck(BYTE copy_of_file_array[], int n)
{
    //track the "hits" on the first four bytes of the FAT block
    int jpeg_sig_count = 0;

    if (copy_of_file_array[n] == 0xff)
        {
            jpeg_sig_count++;
        }
    if (copy_of_file_array[n + 1] == 0xd8)
        {
            jpeg_sig_count++;
        }
    if (copy_of_file_array[n + 2] == 0xff)
        {
            jpeg_sig_count++;
        }
    if (copy_of_file_array[n + 3] == 0xe0 ||
        copy_of_file_array[n + 3] == 0xe1 ||
        copy_of_file_array[n + 3] == 0xe2 ||
        copy_of_file_array[n + 3] == 0xe3 ||
        copy_of_file_array[n + 3] == 0xe4 ||
        copy_of_file_array[n + 3] == 0xe5 ||
        copy_of_file_array[n + 3] == 0xe6 ||
        copy_of_file_array[n + 3] == 0xe7 ||
        copy_of_file_array[n + 3] == 0xe8 ||
        copy_of_file_array[n + 3] == 0xe9 ||
        copy_of_file_array[n + 3] == 0xea ||
        copy_of_file_array[n + 3] == 0xeb ||
        copy_of_file_array[n + 3] == 0xec ||
        copy_of_file_array[n + 3] == 0xed ||
        copy_of_file_array[n + 3] == 0xee ||
        copy_of_file_array[n + 3] == 0xef
        )
        {
            jpeg_sig_count++;
        }


    if (jpeg_sig_count == 4)
    {
        //printf("Found a jpeg :)\n");
        return true;
    }
    else
    {
        //printf("Did not find a jpeg :(\n");
        return false;
    }

}

char *make_jpg_name(int photo_number)
{
    char buffer[8];
    char *jpg_name = NULL;

    printf("photo number: %i\n", photo_number);
    if (photo_number < 10)
    {
        sprintf(buffer, "00%i.jpg", photo_number);
        jpg_name = &buffer[0];
    }
    if (photo_number >= 10)
    {
        sprintf(buffer, "0%i.jpg", photo_number);
        jpg_name = &buffer[0];
    }
    //printf("photo name: %s\n", jpg_name);
    return jpg_name;
}

