# Homework No. 9

bayan. the file duplicate searcher.

## Command Line parameters

--help Help

--include Directories for scanning

--exclude Exclude from scanning

--depth Maximum directory depth

--minsize Minimum file size in bytes

--blocksize Comparsion block size

--filemask  Set RegEx for filename to match.

Example
```
./bayan --include test_data test_data2 --exclude test_data2/exclude --depth 3 --minsize 10 --blocksize 1024 --filemasks ".*\.txt"

```
