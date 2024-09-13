#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a struct to represent a string with its length
typedef struct {
    char *data;
    size_t length;
} String;

// Define a struct to represent a list of Strings
typedef struct {
    String *strings;
    size_t size;
    size_t capacity;
} StringList;

// Define a struct to track performance
typedef struct {
    size_t memory_used;
    size_t operations;
} PerformanceTracker;

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
String to_upper_case(const String *str);
String to_lower_case(const String *str);
String capitalize(const String *str);

// StringList operations
StringList create_string_list();
void add_string_to_list(StringList *list, const String *str);
void remove_string_from_list(StringList *list, size_t index);
void print_string_list(const StringList *list);
void free_string_list(StringList *list);

// Performance tracking
PerformanceTracker create_performance_tracker();
void track_memory_usage(PerformanceTracker *tracker, size_t bytes);
void track_operation(PerformanceTracker *tracker);
void print_performance(const PerformanceTracker *tracker);

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

// Function to convert a string to upper case
String to_upper_case(const String *str) {
    if (!str) return create_string("");
    
    String upper = create_string(str->data);
    for (size_t i = 0; i < upper.length; i++) {
        upper.data[i] = toupper(upper.data[i]);
    }
    return upper;
}

// Function to convert a string to lower case
String to_lower_case(const String *str) {
    if (!str) return create_string("");

    String lower = create_string(str->data);
    for (size_t i = 0; i < lower.length; i++) {
        lower.data[i] = tolower(lower.data[i]);
    }
    return lower;
}

// Function to capitalize a string (first letter uppercase, rest lowercase)
String capitalize(const String *str) {
    if (!str) return create_string("");

    String capitalized = to_lower_case(str);
    if (capitalized.length > 0) {
        capitalized.data[0] = toupper(capitalized.data[0]);
    }
    return capitalized;
}

// StringList Operations

// Function to create an empty StringList
StringList create_string_list() {
    StringList list;
    list.size = 0;
    list.capacity = 4; // Initial capacity
    list.strings = (String *)malloc(list.capacity * sizeof(String));
    if (!list.strings) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return list;
}

// Function to add a String to a StringList
void add_string_to_list(StringList *list, const String *str) {
    if (list->size == list->capacity) {
        list->capacity *= 2; // Double the capacity
        list->strings = (String *)realloc(list->strings, list->capacity * sizeof(String));
        if (!list->strings) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    list->strings[list->size] = copy_string(str);
    list->size++;
}

// Function to remove a String from a StringList by index
void remove_string_from_list(StringList *list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    free_string(&list->strings[index]);
    for (size_t i = index; i < list->size - 1; i++) {
        list->strings[i] = list->strings[i + 1];
    }
    list->size--;
}

// Function to print all Strings in a StringList
void print_string_list(const StringList *list) {
    for (size_t i = 0; i < list->size; i++) {
        print_string(&list->strings[i]);
    }
}

// Function to free a StringList and its contents
void free_string_list(StringList *list) {
    for (size_t i = 0; i < list->size; i++) {
        free_string(&list->strings[i]);
    }
    free(list->strings);
}

// Performance tracking

// Function to create a performance tracker
PerformanceTracker create_performance_tracker() {
    PerformanceTracker tracker = {0, 0};
    return tracker;
}

// Function to track memory usage
void track_memory_usage(PerformanceTracker *tracker, size_t bytes) {
    tracker->memory_used += bytes;
}

// Function to track an operation
void track_operation(PerformanceTracker *tracker) {
    tracker->operations++;
}

// Function to print the performance statistics
void print_performance(const PerformanceTracker *tracker) {
    printf("Memory used: %zu bytes\n", tracker->memory_used);
    printf("Operations: %zu\n", tracker->operations);
}


// Function to compress a string using run-length encoding
String compress_string(const String *str) {
    if (str->length == 0) return create_string(""); // Handle empty string
    
    char *compressed = (char *)malloc((2 * str->length) + 1); // Max size if no compression occurs
    size_t index = 0, count;
    
    for (size_t i = 0; i < str->length; i++) {
        compressed[index++] = str->data[i];
        count = 1;
        
        while (i + 1 < str->length && str->data[i] == str->data[i + 1]) {
            count++;
            i++;
        }
        index += sprintf(compressed + index, "%zu", count); // Append count after character
    }
    compressed[index] = '\0'; // Null-terminate compressed string
    String result = {compressed, index};
    return result;
}

// Function to decompress a run-length encoded string
String decompress_string(const String *str) {
    char *decompressed = (char *)malloc((str->length * 2) + 1); // Assume worst case expansion
    size_t index = 0;
    
    for (size_t i = 0; i < str->length; i++) {
        char ch = str->data[i];
        i++;
        
        size_t count = 0;
        while (i < str->length && isdigit(str->data[i])) {
            count = count * 10 + (str->data[i] - '0');
            i++;
        }
        i--; // Adjust since loop over-iterates
        
        for (size_t j = 0; j < count; j++) {
            decompressed[index++] = ch;
        }
    }
    decompressed[index] = '\0'; // Null-terminate decompressed string
    String result = {decompressed, index};
    return result;
}

// Simple Caesar Cipher encryption with a shift key
String encrypt_string(const String *str, int shift) {
    String encrypted;
    encrypted.length = str->length;
    encrypted.data = (char *)malloc(encrypted.length + 1);
    
    for (size_t i = 0; i < str->length; i++) {
        if (isalpha(str->data[i])) {
            char offset = isupper(str->data[i]) ? 'A' : 'a';
            encrypted.data[i] = ((str->data[i] - offset + shift) % 26) + offset;
        } else {
            encrypted.data[i] = str->data[i]; // Non-alphabet characters remain unchanged
        }
    }
    encrypted.data[encrypted.length] = '\0'; // Null-terminate the encrypted string
    return encrypted;
}

// Caesar Cipher decryption
String decrypt_string(const String *str, int shift) {
    return encrypt_string(str, 26 - (shift % 26)); // Decryption is just encryption with reverse shift
}


// Function to split a string by a delimiter, returns an array of Strings
String* split_string(const String *str, char delimiter, size_t *count) {
    size_t num_substrings = 1; // At least one substring
    for (size_t i = 0; i < str->length; i++) {
        if (str->data[i] == delimiter) num_substrings++;
    }

    String *result = (String *)malloc(num_substrings * sizeof(String));
    size_t start = 0, idx = 0;
    
    for (size_t i = 0; i <= str->length; i++) {
        if (str->data[i] == delimiter || i == str->length) {
            size_t substr_len = i - start;
            result[idx++] = substring(str, start, substr_len);
            start = i + 1;
        }
    }
    *count = num_substrings;
    return result;
}

// Function to reverse a string
String reverse_string(const String *str) {
    String reversed;
    reversed.length = str->length;
    reversed.data = (char *)malloc(reversed.length + 1);
    
    for (size_t i = 0; i < str->length; i++) {
        reversed.data[i] = str->data[str->length - i - 1];
    }
    reversed.data[reversed.length] = '\0';
    return reversed;
}

// Function to search for a substring in a string
size_t search_substring(const String *str, const String *substr) {
    char *found = strstr(str->data, substr->data);
    if (found) {
        return found - str->data; // Return index of found substring
    }
    return -1; // Return -1 if not found
}

// Function to replace all occurrences of a substring within a string with another substring
String replace_substring(const String *str, const String *target, const String *replacement) {
    size_t new_length = 0;
    size_t target_len = target->length;
    size_t replacement_len = replacement->length;
    
    // Calculate the size of the new string
    const char *pos = str->data;
    while ((pos = strstr(pos, target->data)) != NULL) {
        new_length += replacement_len;
        pos += target_len;
    }
    new_length += str->length - (target_len * (new_length / replacement_len));
    
    char *new_data = (char *)malloc(new_length + 1);
    char *dest = new_data;
    const char *src = str->data;
    
    while ((pos = strstr(src, target->data)) != NULL) {
        size_t len = pos - src;
        memcpy(dest, src, len);
        dest += len;
        memcpy(dest, replacement->data, replacement_len);
        dest += replacement_len;
        src = pos + target_len;
    }
    strcpy(dest, src); // Copy the rest of the string
    return (String){new_data, new_length};
}

// Function to format a string with placeholders
String format_string(const char *format, ...) {
    char buffer[1024]; // Static buffer, change to dynamic for larger strings
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    return create_string(buffer); // Return formatted string
}


int main() {
    // Example usage of string functions
    String str1 = create_string("Hello");
    String str2 = create_string(" World!");
    
    String concatenated = concatenate_strings(&str1, &str2);
    print_string(&concatenated);

    String upper_str = to_upper_case(&concatenated);
    print_string(&upper_str);

    String trimmed_str = trim_string(&concatenated);
    print_string(&trimmed_str);

    free_string(&str1);
    free_string(&str2);
    free_string(&concatenated);
    free_string(&upper_str);
    free_string(&trimmed_str);

    // Example usage of StringList
    StringList list = create_string_list();
    add_string_to_list(&list, &str1);
    add_string_to_list(&list, &str2);

    print_string_list(&list);
    free_string_list(&list);

    return 0;
}
