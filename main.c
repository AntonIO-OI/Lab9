#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct record {
    char area_name[50];
    float area;
    int population;
};

void create_file(char *filename) {
    // Open file in binary write mode
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("File created successfully.\n");
    fclose(fp);
}

void load_data(char *filename) {
    // Open file in binary read mode
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Data loaded successfully.\n");
    fclose(fp);
}

void write_data(char *filename) {
    // Open file in binary append mode
    FILE *fp = fopen(filename, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Read data from user
    struct record r;
    printf("Enter area name: ");
    scanf("%s", r.area_name);
    printf("Enter area: ");
    scanf_s("%f", &r.area);
    printf("Enter population: ");
    scanf_s("%d", &r.population);

    // Write data to file
    fwrite(&r, sizeof(struct record), 1, fp);

    // Close file
    fclose(fp);

    printf("Data written successfully.\n");
}

void delete_records(char *filename) {
    // Open file in binary read mode
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Determine size of file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // Calculate number of records in file
    int num_records = (int)(size / sizeof(struct record));

    // Allocate memory for records
    struct record *records = malloc(num_records * sizeof(struct record));

    // Read records from file
    fread(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Display records
    printf("Area name%-10sArea (sq mi)%-10sPopulation\n", "", "");
    for (int i = 0; i < num_records; i++) {
        printf("%d. %-10s%-10s%-10.1f%-10s%d\n", i+1, records[i].area_name, "", records[i].area, "", records[i].population);
    }


    printf("Enter the number of the record(s) you want to delete: ");
    int num_to_delete;
    scanf_s("%d", &num_to_delete);

    // Shift records to the left to delete selected records
    for (int i = num_to_delete - 1; i < num_records - 1; i++) {
        records[i] = records[i + 1];
    }
    num_records--;

    // Open file in binary write mode
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write modified records to file
    fwrite(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Free memory
    free(records);

    printf("Record(s) deleted successfully.\n");
}


void delete_file(char *filename) {
    // Delete file
    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error deleting file!\n");
    }
}

void edit_records(char *filename) {
    // Open file in binary read mode
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Determine size of file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // Calculate number of records in file
    int num_records = (int)(size / sizeof(struct record));

    // Allocate memory for records
    struct record *records = malloc(num_records * sizeof(struct record));

    // Read records from file
    fread(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Display records
    printf("Area name%-10sArea (sq mi)%-10sPopulation\n", "", "");
    for (int i = 0; i < num_records; i++) {
        printf("%d. %-10s%-10s%-10.1f%-10s%d\n", i+1, records[i].area_name, "", records[i].area, "", records[i].population);
    }


    printf("Enter the number of the record you want to edit: ");
    int record_num;
    scanf_s("%d", &record_num);

    // Edit selected record
    printf("Enter new area name: ");
    scanf_s("%s", records[record_num - 1].area_name);
    printf("Enter new area: ");
    scanf_s("%f", &records[record_num - 1].area);
    printf("Enter new population: ");
    scanf_s("%d", &records[record_num - 1].population);

    // Open file in binary write mode
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write modified records to file
    fwrite(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Free memory
    free(records);

    printf("Record edited successfully.\n");
}


int compare_area_name_asc(const void *a, const void *b) {
    struct record *r1 = (struct record *) a;
    struct record *r2 = (struct record *) b;
    return strcmp(r1->area_name, r2->area_name);
}

int compare_area_name_desc(const void *a, const void *b) {
    struct record *r1 = (struct record *) a;
    struct record *r2 = (struct record *) b;
    return strcmp(r2->area_name, r1->area_name);
}

int compare_area_asc(const void *a, const void *b) {
    struct record *r1 = (struct record *) a;
    struct record *r2 = (struct record *) b;
    if (r1->area < r2->area) {
        return -1;
    } else if (r1->area > r2->area) {
        return 1;
    } else {
        return 0;
    }
}

int compare_area_desc(const void *a, const void *b) {
    struct record *r1 = (struct record *) a;
    struct record *r2 = (struct record *) b;
    if (r1->area > r2->area) {
        return -1;
    } else if (r1->area < r2->area) {
        return 1;
    } else {
        return 0;
    }
}

int compare_population_asc(const void *a, const void *b) {
    struct record *r1 = (struct record *) a;
    struct record *r2 = (struct record *) b;
    if (r1->population < r2->population) {
        return -1;
    } else if (r1->population > r2->population) {
        return 1;
    } else {
        return 0;
    }
}

int compare_population_desc(const void *a, const void *b) {
    struct record *r1 = (struct record *) a;
    struct record *r2 = (struct record *) b;
    if (r1->population > r2->population) {
        return -1;
    } else if (r1->population < r2->population) {
        return 1;
    } else {
        return 0;
    }
}

void sort_records(char *filename) {
    // Open file in binary read mode
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Determine size of file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // Calculate number of records in file
    int num_records = (int)(size / sizeof(struct record));

    // Allocate memory for records
    struct record *records = malloc(num_records * sizeof(struct record));

    // Read records from file
    fread(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    printf("Sort by:\n");
    printf("1. Area name\n");
    printf("2. Area (sq mi)\n");
    printf("3. Population\n");
    int sort_field;
    scanf_s("%d", &sort_field);

    printf("Sort in ascending (1) or descending (2) order: ");
    int sort_order;
    scanf_s("%d", &sort_order);

    // Sort records
    if (sort_field == 1) {
        // Sort by area name
        if (sort_order == 1) {
            qsort(records, num_records, sizeof(struct record), compare_area_name_asc);
        } else {
            qsort(records, num_records, sizeof(struct record), compare_area_name_desc);
        }
    } else if (sort_field == 2) {
        // Sort by area
        if (sort_order == 1) {
            qsort(records, num_records, sizeof(struct record), compare_area_asc);
        } else {
            qsort(records, num_records, sizeof(struct record), compare_area_desc);
        }
    } else if (sort_field == 3) {
        // Sort by population
        if (sort_order == 1) {
            qsort(records, num_records, sizeof(struct record), compare_population_asc);
        } else {
            qsort(records, num_records, sizeof(struct record), compare_population_desc);
        }
    }

    // Open file in binary write mode
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write sorted records to file
    fwrite(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Free memory
    free(records);

    printf("Records sorted successfully.\n");
}


void insert_record(char *filename) {
    int choice;

    // Open file in binary read mode
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("It's better to sort file before inserting, do you want to do it:\n1 -> yes\n2 -> no\n");
    scanf_s("%d", &choice);

    if (choice == 1) {
        sort_records(filename);
    }

    printf("You want file to be still sorted by:\n");
    printf("1. Area name\n");
    printf("2. Area (sq mi)\n");
    printf("3. Population\n");

    int sort_field;
    scanf_s("%d", &sort_field);

    printf("You want file to be still sorted in ascending (1) or descending (2) order: ");
    int sort_order;
    scanf_s("%d", &sort_order);

    struct record r;
    printf("Enter area name: ");
    scanf("%s", r.area_name);
    printf("Enter area: ");
    scanf_s("%f", &r.area);
    printf("Enter population: ");
    scanf_s("%d", &r.population);

    // Determine size of file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // Calculate number of records in file
    int num_records = (int)(size / sizeof(struct record));

    // Allocate memory for records
    struct record *records = malloc((num_records + 1) * sizeof(struct record));

    // Read records from file
    fread(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Find position to insert new record
    int i = 0;

    if (sort_field == 1) {
        if (sort_order == 1) {
            for (i = 0; i < num_records; i++) {
                if (strcmp(r.area_name, records[i].area_name) < 0) {
                    break;
                }
            }
        } else if (sort_order == 2) {
            for (i = 0; i < num_records; i++) {
                if (strcmp(r.area_name, records[i].area_name) > 0) {
                    break;
                }
            }
        }
    } else if (sort_field == 2) {
        if (sort_order == 1) {
            for (i = 0; i < num_records; i++) {
                if (r.area < records[i].area) {
                    break;
                }
            }
        } else if (sort_order == 2) {
            for (i = 0; i < num_records; i++) {
                if (r.area > records[i].area) {
                    break;
                }
            }
        }
    } else if (sort_field == 3) {
        if (sort_order == 1) {
            for (i = 0; i < num_records; i++) {
                if (r.population < records[i].population) {
                    break;
                }
            }
        } else if (sort_order == 2) {
            for (i = 0; i < num_records; i++) {
                if (r.population > records[i].population) {
                    break;
                }
            }
        }
    } else {
        printf("Incorrect choice\n");
        return;
    }

    // Shift records to make room for new record
    for (int j = num_records; j > i; j--) {
        records[j] = records[j-1];
    }

    // Insert new record
    records[i] = r;
    num_records++;

    // Open file in binary write mode
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write modified records to file
    fwrite(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Free memory
    free(records);

    printf("Record inserted successfully.\n");
}

void display_records(char *filename) {
    // Open file in binary read mode
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Determine size of file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // Calculate number of records in file
    int num_records = (int)(size / sizeof(struct record));

    // Allocate memory for records
    struct record *records = malloc(num_records * sizeof(struct record));

    // Read records from file
    fread(records, sizeof(struct record), num_records, fp);

    // Close file
    fclose(fp);

    // Display records
    printf("Area name%-10sArea (sq mi)%-10sPopulation\n", "", "");
    for (int i = 0; i < num_records; i++) {
        printf("%d. %-10s%-10s%-10.1f%-10s%d\n", i+1, records[i].area_name, "", records[i].area, "", records[i].population);
    }

    // Free memory
    free(records);
}


int main() {
    char filename[100];
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Create a file\n");
        printf("2. Load data from file\n");
        printf("3. Write data to file\n");
        printf("4. Delete record(s) from file\n");
        printf("5. Delete file\n");
        printf("6. Edit record(s) in file\n");
        printf("7. Sort records in file\n");
        printf("8. Insert record into file\n");
        printf("9. Display records from file\n");
        printf("10. Quit\n");
        scanf_s("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", filename);
                create_file(filename);
                break;
            case 2:
                printf("Enter file name: ");
                scanf("%s", filename);
                load_data(filename);
                break;
            case 3:
                printf("Enter file name: ");
                scanf("%s", filename);
                write_data(filename);
                break;
            case 4:
                printf("Enter file name: ");
                scanf("%s", filename);
                delete_records(filename);
                break;
            case 5:
                printf("Enter file name: ");
                scanf("%s", filename);
                delete_file(filename);
                break;
            case 6:
                printf("Enter file name: ");
                scanf("%s", filename);
                edit_records(filename);
                break;
            case 7:
                printf("Enter file name: ");
                scanf("%s", filename);
                sort_records(filename);
                break;
            case 8:
                printf("Enter file name: ");
                scanf("%s", filename);
                insert_record(filename);
                break;
            case 9:
                printf("Enter file name: ");
                scanf("%s", filename);
                display_records(filename);
                break;
            case 10:
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
