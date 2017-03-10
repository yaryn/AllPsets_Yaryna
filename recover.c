// a program called recover that recovers JPEGs from a forensic image
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    { 
        // на stderr (через fprintf),не в stdout как через printf
        fprintf(stderr, "./recover card.raw\n"); // fprintf (to stderr)
        return 1;
    }
    
    char* infile = argv[1];
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", infile);
        return 2;
    }
    
    uint8_t buffer[512];
    int el_to_read = 0;
    FILE* img = NULL;
    
    // repeat until end of card
    while(fread(buffer, 512, 1, inptr) == 1)  // if size < 512 then eof
    {  
        // fread(buffer, 512, 1, inptr); /// читання 512байт  1 блоків кожен
        // &data - покажчик на структуру, яка буде містити байти які читаємо
        // size - розмір кожного елемента що читаємо
        // 1 - кількість елементів для читання; 
        // inptr - покажчик на файл який читаємо
        // printf("(while) buffer[0] = %hhu \n", buffer[0]);
           
        // Найти начало JPEG-файла   
        // if (buffer[0] == 255 && buffer[1] == 8 && 
        // buffer[2] == 255 && (buffer[3] & 240) == 224)    
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && 
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) 
            // four == 0xe0 || four == 0xe1 ||...|| four == 0xef)
        {   
            // printf("(while if) buffer =%s \n", buffer);
            // printf("if ((buffer[0] ==... %hhu \n", buffer[0]);
            
            // Как только находиm начало JPEG, создаеm новый файл на диске 
            // с помощью ф-ии sprint,в которую передается шаблон и аргумент  
            if (img) // якщо був відкритий закриємо
                fclose(img);
            // Construct the filename
            char file_name[8]; 
            sprintf(file_name, "%03i.jpg", el_to_read); // 000.jpg
            // printf("while el_to_read= %i\n", el_to_read);    
            img = fopen(file_name, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Could not open file %s.\n", file_name);
                return 3;
            }
            // block_memory
            
            // их можно записывать, пока входной файл карты памяти не 
            // закончится. fread возвращает количество элементов размера size,
            // которые были успешно прочитаны. В идеале size должно 
            // совпасть c number. 
            // 0рганизовать условный оператор, который позволит посчитать, 
            // сколько элементов на самом деле было прочитанo
            // if size == number true
            // while
            el_to_read++; 
            // count jpeg-s
        }
        if (img) 
            fwrite(buffer, 512, 1, img);
    } 
    // end of card 
    
    if (img)    
        fclose(img);
        
    fclose(inptr);
    return 0;
}