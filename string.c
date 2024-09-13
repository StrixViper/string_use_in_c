#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to represent a string with its length
typedef struct {
    char *data;
    size_t length;
} String;

// Function prototypes
String create_string(const char *initial_data);
void free_string(String *str);
size_t get_string_length(const String *str);
String concatenate_strings(const String *str1, const String *str2);
int compare_strings(const String *str1, const String *str2);
void print_string(const String *str);
String substring(const String *str, size_t start, size_t length);
int find_substring(const String *str, const char *substr);
String replace_substring(const String *str, const char *old_sub, const char *new_sub);
String trim_string(const String *str);
String copy_string(const String *str);
String reverse_string(const String *str);

// Function to create a new String
String create_string(const char *initial_data) {
    String str;
    if (!initial_data) {
        str.data = NULL;
        str.length = 0;
        return str;
    }

    str.length = strlen(initial_data);
    str.data = (char *)malloc(str.length + 1); // +1 for null terminator
    if (!str.data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(str.data, initial_data);
    return str;
}

// Function to free the memory allocated for a String
void free_string(String *str) {
    if (str->data) {
        free(str->data);
        str->data = NULL;
        str->length = 0;
    }
}

// Function to get the length of a String
size_t get_string_length(const String *str) {
    return str ? str->length : 0;
}

// Function to concatenate two Strings
String concatenate_strings(const String *str1, const String *str2) {
    if (!str1 || !str2) return create_string(""); // Return empty string if invalid input

    String result;
    result.length = str1->length + str2->length;
    result.data = (char *)malloc(result.length + 1); // +1 for null terminator
    if (!result.data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(result.data, str1->data);
    strcat(result.data, str2->data);
    return result;
}

// Function to compare two Strings
int compare_strings(const String *str1, const String *str2) {
    if (!str1 || !str2) return -1; // Return invalid comparison if one of them is NULL
    return strcmp(str1->data, str2->data);
}

// Function to print a String
void print_string(const String *str) {
    if (str && str->data) {
        printf("The string is: %s\n", str->data);
    } else {
        printf("(null)\n");
    }
}

// Function to create a substring
String substring(const String *str, size_t start, size_t length) {
    if (!str || start >= str->length) return create_string(""); // Return empty string if out of range

    size_t actual_length = (start + length > str->length) ? (str->length - start) : length;
    String sub = create_string("");
    sub.data = (char *)malloc(actual_length + 1); // +1 for null terminator
    if (!sub.data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(sub.data, str->data + start, actual_length);
    sub.data[actual_length] = '\0';
    sub.length = actual_length;

    return sub;
}

// Function to find the index of a substring
int find_substring(const String *str, const char *substr) {
    if (!str || !substr) return -1;

    char *pos = strstr(str->data, substr);
    return pos ? (int)(pos - str->data) : -1;
}

// Function to replace all occurrences of a substring with another substring
String replace_substring(const String *str, const char *old_sub, const char *new_sub) {
    if (!str || !old_sub || !new_sub) return create_string("");

    String result = create_string(str->data);
    char *pos;
    while ((pos = strstr(result.data, old_sub))) {
        size_t new_len = result.length - strlen(old_sub) + strlen(new_sub);
        char *new_data = (char *)malloc(new_len + 1);
        if (!new_data) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        size_t prefix_len = pos - result.data;
        strncpy(new_data, result.data, prefix_len);
        strcpy(new_data + prefix_len, new_sub);
        strcat(new_data + prefix_len + strlen(new_sub), pos + strlen(old_sub));
        free(result.data);
        result.data = new_data;
        result.length = new_len;
    }

    return result;
}

// Function to trim leading and trailing spaces
String trim_string(const String *str) {
    if (!str || !str->data) return create_string("");

    size_t start = 0, end = str->length - 1;
    while (str->data[start] == ' ' && start <= end) start++;
    while (str->data[end] == ' ' && end >= start) end--;

    return substring(str, start, end - start + 1);
}

// Function to copy a string
String copy_string(const String *str) {
    if (!str) return create_string("");
    return create_string(str->data);
}

// Function to reverse a string
String reverse_string(const String *str) {
    if (!str) return create_string("");

    String reversed = create_string("");
    reversed.data = (char *)malloc(str->length + 1);
    if (!reversed.data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < str->length; i++) {
        reversed.data[i] = str->data[str->length - 1 - i];
    }
    reversed.data[str->length] = '\0';
    reversed.length = str->length;

    return reversed;
}

// Main function to demonstrate usage
int main() {
    // Create two Strings
    String str1 = create_string("Hello, ");
    String str2 = create_string("World!");

    // Print the Strings
    print_string(&str1);
    print_string(&str2);

    // Concatenate the Strings
    String concatenated = concatenate_strings(&str1, &str2);
    print_string(&concatenated);

    // Compare the Strings
    int comparison = compare_strings(&str1, &str2);
    printf("Comparison result: %d\n", comparison);

    // Substring example
    String sub = substring(&concatenated, 7, 5);
    print_string(&sub);

    // Replace substring example
    String replaced = replace_substring(&concatenated, "World", "Everyone");
    print_string(&replaced);

    // Trim string example
    String trimmed = trim_string(&replaced);
    print_string(&trimmed);

    // Reverse string example
    String reversed = reverse_string(&trimmed);
    print_string(&reversed);

    // Free the allocated memory
    free_string(&str1);
    free_string(&str2);
    free_string(&concatenated);
    free_string(&sub);
    free_string(&replaced);
    free_string(&trimmed);
    free_string(&reversed);

    return 0;
}
