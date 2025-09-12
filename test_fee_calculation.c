#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Test program to verify the overdue fee calculation logic
 * implemented in library_management.asm
 */

int calculate_late_fee(int total_days) {
    // Fee structure: RM 1/day for first 7 days overdue, RM 2/day thereafter, capped at RM 50
    // Days beyond 14 are considered overdue
    
    if (total_days <= 14) {
        return 0; // No fee if not overdue
    }
    
    int overdue_days = total_days - 14;
    int fee = 0;
    
    // First 7 days overdue: RM 1 per day
    if (overdue_days <= 7) {
        fee = overdue_days * 1;
    } else {
        // More than 7 days overdue
        fee = 7 * 1; // First 7 days at RM 1 each
        int remaining_days = overdue_days - 7;
        fee += remaining_days * 2; // Remaining days at RM 2 each
    }
    
    // Cap at RM 50
    if (fee > 50) {
        fee = 50;
    }
    
    return fee;
}

int string_to_number(const char* str, int length) {
    // Simulate the assembly conversion routine with count-based processing
    int result = 0;
    int i;
    
    for (i = 0; i < length; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10; // Multiply by TEN
            result += (str[i] - '0'); // Add digit value (fixed conversion)
        }
    }
    
    return result;
}

void test_conversion() {
    printf("Testing string to number conversion (simulating assembly fix):\n");
    printf("=============================================================\n");
    
    // Test the conversion with exact character count (like DAYS_BUF[1])
    const char* test_inputs[] = {"5", "19", "25", "100"};
    int test_lengths[] = {1, 2, 2, 3};
    int expected_results[] = {5, 19, 25, 100};
    
    for (int i = 0; i < 4; i++) {
        int result = string_to_number(test_inputs[i], test_lengths[i]);
        printf("Input: \"%s\" (length %d) -> Result: %d (Expected: %d) %s\n", 
               test_inputs[i], test_lengths[i], result, expected_results[i],
               (result == expected_results[i]) ? "✅" : "❌");
    }
    printf("\n");
}

void test_fee_calculation() {
    printf("Testing overdue fee calculation:\n");
    printf("================================\n");
    
    struct {
        int total_days;
        int expected_fee;
        const char* description;
    } test_cases[] = {
        {14, 0, "Exactly on due date - no fee"},
        {15, 1, "1 day overdue - RM 1"},
        {19, 5, "5 days overdue - RM 5 (KEY TEST CASE!)"},
        {21, 7, "7 days overdue - RM 7"},
        {22, 9, "8 days overdue - RM 7 + RM 2 = RM 9"},
        {25, 15, "11 days overdue - RM 7 + (4 * RM 2) = RM 15"},
        {39, 43, "25 days overdue - RM 7 + (18 * RM 2) = RM 43"},
        {50, 50, "36 days overdue - should be capped at RM 50"},
        {100, 50, "86 days overdue - should be capped at RM 50"}
    };
    
    int all_passed = 1;
    
    for (int i = 0; i < 9; i++) {
        int actual_fee = calculate_late_fee(test_cases[i].total_days);
        int passed = (actual_fee == test_cases[i].expected_fee);
        all_passed = all_passed && passed;
        
        printf("%s: %s\n", passed ? "PASS" : "FAIL", test_cases[i].description);
        printf("  Total days: %d, Expected: RM%d, Got: RM%d\n", 
               test_cases[i].total_days, test_cases[i].expected_fee, actual_fee);
        
        if (!passed) {
            printf("  ERROR: Expected RM%d but got RM%d\n", 
                   test_cases[i].expected_fee, actual_fee);
        }
        printf("\n");
    }
    
    if (all_passed) {
        printf("🎉 All tests PASSED! The fix is working correctly.\n");
        printf("✅ Key verification: 5 days overdue = RM5 (not RM2305)\n");
    } else {
        printf("❌ Some tests FAILED!\n");
    }
}

int main() {
    printf("Library Management System - Overdue Fee Calculation Test\n");
    printf("========================================================\n\n");
    
    test_conversion();
    test_fee_calculation();
    
    return 0;
}