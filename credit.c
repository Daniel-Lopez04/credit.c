#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to validate the card number using the Luhn algorithm
int is_valid_luhn(const char *card_number) {
    int length = strlen(card_number);
    int sum = 0;
    int is_second = 0;

    // Traverse the digits from right to left
    for (int i = length - 1; i >= 0; i--) {
        if (!isdigit(card_number[i])) {
            return 0; // If any character is not a digit, return invalid
        }

        int digit = card_number[i] - '0'; // Convert char to int

        // Double every second digit starting from the right
        if (is_second) {
            digit = digit * 2;
            if (digit > 9) {
                digit -= 9; // Subtract 9 if the result is greater than 9
            }
        }

        sum += digit;
        is_second = !is_second; // Toggle the flag for the next second digit
    }

    // If the sum is divisible by 10, the card number is valid
    return sum % 10 == 0;
}

// Function to validate the card type and check length
int is_valid_card_type(const char *card_number) {
    int length = strlen(card_number);

    // Check for AMEX: 15 digits, starts with 34 or 37
    if (length == 15 && card_number[0] == '3' && (card_number[1] == '4' || card_number[1] == '7')) {
        return 1; // AMEX
    }

    // Check for MASTERCARD: 16 digits, starts with 51, 52, 53, 54, or 55
    if (length == 16 && card_number[0] == '5' && (card_number[1] >= '1' && card_number[1] <= '5')) {
        return 2; // MASTERCARD
    }

    // Check for VISA: 13 or 16 digits, starts with 4
    if ((length == 13 || length == 16) && card_number[0] == '4') {
        return 3; // VISA
    }

    return 0; // Invalid card type
}

int main(void) {
    char card_number[20];

    // Get user input
    printf("Enter credit card number: ");
    scanf("%19s", card_number); // Read up to 19 characters to avoid buffer overflow

    // Check if the card number is a valid card type (AMEX, MASTERCARD, or VISA)
    int card_type = is_valid_card_type(card_number);

    // If it's an invalid card type
    if (card_type == 0) {
        printf("INVALID\n");
        return 0;
    }

    // Validate the card number using the Luhn algorithm
    if (!is_valid_luhn(card_number)) {
        printf("INVALID\n");
        return 0;
    }

    // If the card is valid, output the corresponding card type
    switch (card_type) {
        case 1:
            printf("AMEX\n");
            break;
        case 2:
            printf("MASTERCARD\n");
            break;
        case 3:
            printf("VISA\n");
            break;
    }

    return 0;
}
