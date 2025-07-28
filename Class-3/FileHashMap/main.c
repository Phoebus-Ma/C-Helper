/**
 * @brief:
 * Save the hash mapping table of the files, query the files, and print the file contents.
 * 
 * The sample code uses uthash to record the file names, starting addresses,
 * and file sizes of the existing files. After finding the starting address
 * and size of the specified file from the hash table by the file name,
 * read the file from the address and print its contents.
 *
 * License - MIT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// BSD-License.
#include "uthash.h"

#define MAX_NAME_LEN            32
#define SEARCH_FILE_NAME        "test6.log"


typedef struct {
    char *name;        // File name.
    void *start_addr;  // File memory mapping start address.
    size_t size;       // File size.
    UT_hash_handle hh; // uthash handle.
} FileMap;

// Global hash table pointer.
FileMap *file_map = NULL;

/**
 * process_file - Handle a single file.
*/
void process_file(const char *filepath, const char *filename)
{
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return;
    }

    // Get file size.
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat failed");
        close(fd);
        return;
    }

    // Memory mmap file.
    void *addr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return;
    }

    // Create the object properties of the hash table.
    FileMap *entry = malloc(sizeof(FileMap));
    entry->name = strdup(filename);
    entry->start_addr = addr;
    entry->size = st.st_size;

    // Add to the hash table.
    HASH_ADD_KEYPTR(hh, file_map, entry->name, strlen(entry->name), entry);

    close(fd);
}

/**
 * scan_log_files - Traverse the directory to process the '.log' files.
*/
void scan_log_files(const char *dirpath)
{
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("opendir failed");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        // Only handle ordinary files.
        if (entry->d_type == DT_REG) {
            char *ext = strrchr(entry->d_name, '.');
            if (ext && strcmp(ext, ".log") == 0) {
                char fullpath[PATH_MAX];
                snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);
                process_file(fullpath, entry->d_name);
            }
        }
    }

    closedir(dir);
}

/**
 * find_file_info - Match file node.
*/
FileMap *find_file_info(const char *filename)
{
    FileMap *entry;
    HASH_FIND_STR(file_map, filename, entry);

    return entry;
}

/**
 * cleanup - Clean up resources.
*/
void cleanup()
{
    FileMap *current, *tmp;

    HASH_ITER(hh, file_map, current, tmp) {
        HASH_DEL(file_map, current);
        munmap(current->start_addr, current->size);
        free(current->name);
        free(current);
    }
}

/**
 * create_tmp_log - Create test file.
*/
int create_tmp_log()
{
    char filename[MAX_NAME_LEN] = { 0 };

    for (int i = 0; i < 10; i++) {
        snprintf(filename, MAX_NAME_LEN, "/tmp/test%d.log", i);

        FILE *fp = fopen(filename, "w");
        if (fp == NULL) {
            perror("Error in create test file.\n");
            exit(EXIT_FAILURE);
        }
 
        fprintf(fp, "hello %d", i);
        fclose(fp);
    }

    return 0;
}

int main()
{
    // Create test file.
    if (create_tmp_log() < 0) {
        return -1;
    }

    // Scan /tmp folder.
    scan_log_files("/tmp");

    // Search example file.
    FileMap *result = find_file_info(SEARCH_FILE_NAME);
    if (result) {
        printf("\nFile Found:\n");
        printf("Name: %s\n", result->name);
        printf("Size: %zu bytes\n", result->size);
        printf("Content:\n%.*s\n", (int)result->size, (char *)result->start_addr);
    }
    else {
        printf("File not found in map.\n");
    }

    cleanup();

    return 0;
}

