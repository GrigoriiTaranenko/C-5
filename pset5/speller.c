/**
 * speller.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a spell-checker.
 */

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"
#undef calculate
#undef getrusage

// default dictionary - Стандартный словарь
#define DICTIONARY "dictionaries/large"

// prototype - образец
double calculate(const struct rusage* b, const struct rusage* a);

int main(int argc, char* argv[])
{
    // check for correct number of args
    // Проверка правильности количества аргументов
    if (argc != 2 && argc != 3)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // structs for timing data
    // Структуры для проверки времени данных
    struct rusage before, after;

    // benchmarks
    // начальные данные времени
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // determine dictionary to use
    // Определить словарь для использования
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // load dictionary
    // Загрузка словарей
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // abort if dictionary not loaded
    // Прервать, если словарь не загружен
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // calculate time to load dictionary
    // Рассчитать время загрузки словаря
    time_load = calculate(&before, &after);

    // try to open text
    // Попытаться отрыть текстовый файл
    char* text = (argc == 3) ? argv[2] : argv[1];
    FILE* fp = fopen(text, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // prepare to report misspellings
    // Подготовка сообщения о нарушении
    printf("\nMISSPELLED WORDS\n\n");

    // prepare to spell-check
    // Подготовка к проверке орфографии LENGTH - размер самого большого слова
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];

    // spell-check each word in text
    // Проверка каждого слова
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // allow only alphabetical characters and apostrophes
        // разрешить только алфавитные символы и апострофы
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            // добавить символ в слово
            word[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            // Игнорировать алфавитные строки слишком долго, чтобы быть словами
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                // потребляем остатки алфавитной строки
                while ((c = fgetc(fp)) != EOF && isalpha(c));

                // prepare for new word
                // Подготовиться к новому слову
                index = 0;
            }
        }

        // ignore words with numbers (like MS Word can)
        // Игнорировать слова с числами (например, MS Word)
        else if (isdigit(c))
        {
            // consume remainder of alphanumeric string
            // Потреблять остаток буквенно-цифровой строки
            while ((c = fgetc(fp)) != EOF && isalnum(c));

            // prepare for new word
            // Подготовиться к новому слову
            index = 0;
        }

        // we must have found a whole word
        // Мы должны были найти целое слово
        else if (index > 0)
        {
            // terminate current word
            // Завершить текущее слово
            word[index] = '\0';

            // update counter
            // счетчик обновлений
            words++;

            // check word's spelling
            // проверка правописание слова
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // update benchmark
            // Контрольный показатель обновления
            time_check += calculate(&before, &after);

            // print word if misspelled
            // Печатать слово, если была ошибка
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // prepare for next word
            // Подготовка к следующему слову
            index = 0;
        }
    }

    // check whether there was an error
    // Проверка, была ли ошибка
    if (ferror(fp))
    {
        fclose(fp);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // close text
    // закрыть текстовый файл
    fclose(fp);

    // determine dictionary's size
    // Определить размер словаря
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // calculate time to determine dictionary's size
    // Рассчитать время, чтобы определить размер словаря
    time_size = calculate(&before, &after);

    // unload dictionary Разгружаем словарь
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // abort if dictionary not unloaded
    // Прервать, если словарь не выгружен
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // calculate time to unload dictionary
    // Рассчитать время для разгрузки словаря
    time_unload = calculate(&before, &after);

    // report benchmarks
    // Контрольные показатели отчета
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n", 
     time_load + time_check + time_size + time_unload);

    // that's all folks
    // Это все люди
    return 0;
}

/**
 * Returns number of seconds between b and a.
 * Возвращает количество секунд между b и a.
 */
double calculate(const struct rusage* b, const struct rusage* a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
