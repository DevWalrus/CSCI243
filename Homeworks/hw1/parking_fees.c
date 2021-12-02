// file: parking_fees.c
// description: faulty, incomplete code that needs repair.
// @author Clinten Hopkins cmh3586
//
// ========================= INSTRUCTIONS =========================
//
// Add an author line above to contain your full name and login ID.
// Put your author line as the last author line.
// <br/>
// What you CAN change/remove:
//     - preprocessor statements
//     - statements in function bodies.
// What you CANNOT change:
//     - the compute function docstrings and declarations.
//

#include <stdio.h>
#include <stdlib.h>          // strtol returns an int from a C string

#define MAXIMUM_FEE 10.0
#define MINIMUM_FEE 2.0
#define FRACTIONAL_RATE 0.50
#define MINUTES_PER_HOUR 60.0
#define MAX_INPUT 80

/// compute_charges calculates and returns dollars charged for minutes
/// @param minutes integer number of minutes parked
/// @return dollars - ammount to charge

double compute_charges( int minutes ) {
    
    double hours = minutes / MINUTES_PER_HOUR;
    double charge = 2.5;
    
    if (hours < 3) {
        return MINIMUM_FEE;
    } else if (hours < 4) {
        return MINIMUM_FEE + FRACTIONAL_RATE;
    }

    while (1) {
        
        hours -= 3;
        
        if (hours >= 0.5) {
        
            hours -= 0.5;
            charge += FRACTIONAL_RATE;
        
        } else {
        
        break;
            
        }
    }

    if (charge >= MAXIMUM_FEE) {
        return MAXIMUM_FEE;
    } else {
        return charge;
    }

}

/// main prompts for minutes parked, calculates charges, and prints a bill 
/// for each car's parking fee. When the user terminates the program 
/// (e.g. enters 0 to quit), the program prints the total number of cars parked, 
/// accumulated hours parked, and accumulated dollars charged.
///
/// **Note: The heading words in the text strings "Car...Charges" are separated by a single TAB character.**
///
/// Below is an example run of the program:
///
/// \code $ ./parking_fees
/// Car 1: Enter minutes parked (control-d or 0 to quit): 245
///
/// Car Hours   Charges
/// 1   4.08    $3.00
/// Car 2: Enter minutes parked (control-d or 0 to quit): 58
///
/// Car Hours   Charges
/// 2   0.97    $2.00
/// Car 3: Enter minutes parked (control-d or 0 to quit): 61
///
/// Car Hours   Charges
/// 3   1.02    $2.00
/// Car 4: Enter minutes parked (control-d or 0 to quit): 0
/// Cars Processed: 3
/// Total Hours Parked: 6.07
/// Total Dollars Charged: $7.00\endcode
///
/// @return status_code - EXIT_SUCCESS or EXIT_FAILURE

int main( void ) {

    char minutes_in[MAX_INPUT] = "-1";
    
    int minutes = strtol(minutes_in, NULL, 10);
    int cars = 0;
    
    double total_charged = 0.0;
    double total_hours = 0.0;
    
    while (1) {
        
        ++cars;
        
        printf("Car %d: Enter minutes parked (control-d or 0 to quit): ", cars);
        
        if (fgets(minutes_in, MAX_INPUT, stdin) == NULL) 
            break;

        minutes = strtol(minutes_in, NULL, 10);
        
        if (minutes <= 0) break;
        
        double curr_charged = compute_charges(minutes);
        double hours = minutes / MINUTES_PER_HOUR;
        
        total_charged += curr_charged;
        total_hours += hours;
        
        printf("\nCar\tHours\tCharges");
        printf("\n%d\t%0.2f\t$%0.2f\n", cars, hours, curr_charged);
    

    }

    printf("Cars Processed: %d\nTotal Hours Parked: %0.2f\nTotal Dollars Charged: $%0.2f\n", cars-1, total_hours, total_charged);
    return 0;
}

