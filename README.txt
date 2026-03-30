Arhan Nagavelli - arn97
Keith Miquela - kvm33

TESTING PLAN:
1. Basic similarity test
Requirement: compare correctly computes and outputs the JSD for a pair of similar files.
Detection method: when successful, compare outputs a small but nonzero JSD value for two files that share most but not all   words.
Test: create two files where one contains "hello world hello" and the other contains "hello world world". Run ./compare a.txt b.txt and verify that the output JSD is small and nonzero.
Result: 0.28584 a.txt b.txt

2. Identical files test
Requirement: compare outputs a JSD of 0 for two identical files.
Detection method: when successful, compare outputs 0.00000 for two files with the same word frequency distribution.
Test: copy a.txt to b.txt to make them identical. Run ./compare a.txt b.txt and verify that the output is 0.00000.
Result: 0.00000 a.txt b.txt

3. Completely different files test
Requirement: compare outputs a JSD of 1 for two files with no words in common.
Detection method: when successful, compare outputs 1.00000 for two files whose word frequency distributions share no overlap.
Test: create two files with completely disjoint vocabularies. Run ./compare a.txt b.txt and verify that the output is 1.00000.
Result: 1.00000 a.txt b.txt

4. Directory traversal test
Requirement: compare recursively traverses directories and adds files with the correct suffix to the analysis set.
Detection method: when successful, compare finds and compares all .txt files within a directory and its subdirectories.
Test: create a directory containing two .txt files. Run ./compare testdir and verify that both files appear in the output.
Result: 1.00000 testdir/b.txt testdir/a.txt ✓

5. Hidden file test
Requirement: compare skips any file or directory whose name begins with a period.
Detection method: when successful, hidden files do not appear in the output.
Test: create a hidden file .hidden.txt inside testdir. Run ./compare testdir and verify that only the non-hidden files appear in the output.
Result: 1.00000 testdir/b.txt testdir/a.txt

6. Fewer than two files test
Requirement: compare reports an error and exits when fewer than two files are found.
Detection method: when successful, compare prints an error message to stderr and exits with a failure status.
Test: run ./compare a.txt with a single file and verify that an error message is printed.
Result: "error: need at least 2 files to compare" 

7. Multiple file comparison test
Requirement: compare correctly computes and outputs the JSD for every unordered pair when given more than two files.
Detection method: when successful, compare outputs exactly n*(n-1)/2 pairs for n files, with no pair appearing more than once and no pair missing.
Test: create three files with distinct but partially overlapping vocabularies. Run ./compare a.txt b.txt c.txt and verify that exactly three pairs appear in the output.
Result: 0.70711 a.txt b.txt / 1.00000 a.txt c.txt / 1.00000 b.txt c.txt 

8. Suffix filtering test
Requirement: compare only adds files with the .txt suffix when traversing directories, but always adds explicitly passed files regardless of suffix.
Detection method: when successful, non-.txt files found during directory traversal are excluded from the analysis set, while explicitly passed files of any suffix are included.
Test: create a .c file inside testdir. Run ./compare testdir and verify that the .c file is excluded. Then run ./compare testdir/file.c testdir/a.txt and verify both are included.

9. Sort order test
Requirement: compare output pairs in decreasing order of combined word count.
Detection method: when successful, the pair with the highest combined word count appears first in the output.
Test: create three files of noticeably different sizes. Run ./compare small.txt medium.txt large.txt and verify that pairs are ordered from largest to smallest combined word count.
