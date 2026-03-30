#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_types.h"
#include "jsd.h"

float jsd(FileNode *a, FileNode *b) 
{
    WordNode *wa = a->wordList;
    WordNode *wb = b->wordList;

    double kld_a = 0.0;
    double kld_b = 0.0;

    while (wa != NULL || wb != NULL) 
    {
        float fa = 0.0f, fb = 0.0f;
        int cmp;

        if (wa == NULL) 
        {
            cmp = 1;
        } 
        else if (wb == NULL) 
        {
            cmp = -1;
        } 
        else 
        {
            cmp = strcmp(wa->word, wb->word);
        }

        if (cmp < 0) 
        {
            fa = wa->freq;
            fb = 0.0f;
            wa = wa->next;
        } 
        else if (cmp > 0) 
        {
            fa = 0.0f;
            fb = wb->freq;
            wb = wb->next;
        } 
        else 
        {
            fa = wa->freq;
            fb = wb->freq;
            wa = wa->next;
            wb = wb->next;
        }

        double mean = (fa + fb) / 2.0;

        if (fa > 0.0f) 
        {
            kld_a += fa * log2(fa / mean);
        }
        if (fb > 0.0f) 
        {
            kld_b += fb * log2(fb / mean);
        }
    }

    double jsd_squared = 0.5 * kld_a + 0.5 * kld_b;
    return (float)sqrt(jsd_squared);
}

static int file_word_count(FileNode *f) 
{
    return f->word_count;
}

static int cmp_comparisons(const void *x, const void *y) 
{
    const Comparison *cx = (const Comparison *)x;
    const Comparison *cy = (const Comparison *)y;
    return cy->combined_word_count - cx->combined_word_count;
}

int analyze(FileNode *fileList) 
{
    int n = 0;
    FileNode *cur = fileList;
    while (cur != NULL) 
    {
        n++;
        cur = cur->next;
    }

    if (n < 2) 
    {
        fprintf(stderr, "error: need at least 2 files to compare\n");
        return EXIT_FAILURE;
    }

    int num_pairs = n * (n - 1) / 2;
    Comparison *comparisons = malloc(num_pairs * sizeof(Comparison));
    if (comparisons == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int idx = 0;
    FileNode *fi = fileList;
    while (fi != NULL) 
    {
        FileNode *fj = fi->next;
        while (fj != NULL) 
        {
            comparisons[idx].file_a = fi;
            comparisons[idx].file_b = fj;
            comparisons[idx].combined_word_count =
                file_word_count(fi) + file_word_count(fj);
            comparisons[idx].distance = jsd(fi, fj);
            idx++;
            fj = fj->next;
        }
        fi = fi->next;
    }

    qsort(comparisons, num_pairs, sizeof(Comparison), cmp_comparisons);

    for (int i = 0; i < num_pairs; i++) 
    {
        printf("%.5f %s %s\n",
               comparisons[i].distance,
               comparisons[i].file_a->filePath,
               comparisons[i].file_b->filePath);
    }

    free(comparisons);
    return EXIT_SUCCESS;
}
