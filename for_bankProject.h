//
// Created by whs on 2/20/23.
//

#ifndef DIV1_PROJECTS_FOR_BANKPROJECT_H
#define DIV1_PROJECTS_FOR_BANKPROJECT_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define SIZE 100 //symbolic constant

//id name nrc email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_Level phNumber current_amount address TransRC

struct trans{
    char note[200];
};
struct data {
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20]; //personal or business
    char loan_status[2];
    unsigned int monthly_income;
    unsigned int loan_amount;
    float loan_rate;
    char acc_status[10]; //account status
    int acc_level;
    char phNumber[15];
    unsigned int cur_amount; //current amount
    char address[100];
    unsigned int transAmoLimitPerDay; //transfer amount limited per day => minimize for our project 5min
    struct trans trc[100]; // transfer record
};

struct data db[SIZE];

//Global variable Declaration
int users = 0;
int eFound = -1;
int pFound = -1;
int phNumberFound = -1;
int is_phNumber_exist = -1;
int phNumberValid = -1;
int checkValid = -1;
int is_TwoCharArray_same = -1;
int nrc_valid = -1;
int guessPass = -1;

//global array
int space_array[30];
char integer_to_char_array[10];
char current_time_array[50];


//Fro function declaration

void loadingAllDataFromFile();
void recording_all_data_to_file();
void easyToGuess(char uPass[50]);
void compare_two_charArray(char first[50], char second[50]);
void nrc_validation(char nrc_toCheck[50]);
void dataPrinting();
void registration();
void space_counter();
void get_current_time();
void transaction_record(int transfer, int receiver, char who,unsigned int amount);
void integer_to_char(unsigned int value);
void gmailValidation(char toValid[50]);
int charCounting(char toCount[50]);
void emailExistChecking(char inputGmail[50]);
void passwordExistChecking(char inputPass[50]);
void phNumberExistChecking(char input_phNumber[15]);
void finding_phone_number(char phNumber[15]);
void phNumberValidation(char inputPhNumber[15]);
void transfer_money(int transfer, int receiver, unsigned int amount);
void addCountryCode(char phNumber[15]);
void copyChar(char fromFirst[50], char toSecond[50]);
void userSector();
void login();
void welcome();

void welcome() {
    char option = 0;
    printf("This is welcome screen.\n");
    printf("Press 1 to Login:\n");
    printf("Press 2 to Register:\n");
    printf("Press 3 to exit:");

    scanf(" %c", &option);

    if(option == 49) {

        login();
    }else if(option == 50) {

        registration();

    }else if(option == 51) {
        recording_all_data_to_file();
        exit(1);
    }else{
        printf("Wrong option!\n");
        welcome();

    }

}



void loadingAllDataFromFile() {
    FILE *fptr = fopen("2-bankDb.txt", "r");
    if(fptr == NULL) {
        printf("Error at loadingAllDataFromFile!\n");
    } else{
        for (int i = 0; i < SIZE; ++i) {
            fscanf(fptr,"%u%s%s%s%s%s%s%u%u%f%s%d%s%u%s%u",&db[i].id, &db[i].name, &db[i].nrc, &db[i].email, &db[i].password, &db[i].pOrb, &db[i].loan_status, &db[i].monthly_income, &db[i].loan_amount, &db[i].loan_rate, &db[i].acc_status, &db[i].acc_level, &db[i].phNumber, &db[i].cur_amount, &db[i].address, &db[i].transAmoLimitPerDay);

            for(int j=0; j < space_array[i]-15; j++){
                fscanf(fptr, "%s",&db[i].trc[j].note[0]);
            }
            if(db[i].email[0] == '\0') {
                break;
            }
            users++;


        }
    }
    fclose(fptr);
}

void dataPrinting() {
    for (int i = 0; i < users; ++i) {
        printf("%s %s %s %s %s %s %u %u %f %s %d %s %u %s %u",db[i].name, db[i].nrc, db[i].email, db[i].password, db[i].pOrb, db[i].loan_status, db[i].monthly_income, db[i].loan_amount, db[i].loan_rate, db[i].acc_status, db[i].acc_level, db[i].phNumber, db[i].cur_amount, db[i].address, db[i].transAmoLimitPerDay);
        for (int j = 0; j < space_array[i]-15; ++j) {
            printf(" %s", db[i].trc[j].note);
        }
        printf("\n");
    }



}

void recording_all_data_to_file() {
    FILE *fptr = fopen("2-bankDb.txt", "w");

    if(fptr == NULL) {
        printf("Error at recording_all_data_to_file function.\n");
    }else{
        for (int i = 0; i < users; ++i) {
            fprintf(fptr,"%u %s %s %s %s %s %s %u %u %f %s %d %s %u %s %u",db[i].id, db[i].name, db[i].nrc, db[i].email, db[i].password, db[i].pOrb, db[i].loan_status, db[i].monthly_income, db[i].loan_amount, db[i].loan_rate, db[i].acc_status, db[i].acc_level, db[i].phNumber, db[i].cur_amount, db[i].address, db[i].transAmoLimitPerDay);
            for (int j = 0; j < space_array[i]-15; ++j) {
                fprintf(fptr, " %s", db[i].trc[j].note);
            }
            fprintf(fptr,"%c", '\n');
        }
    }
    fclose(fptr);
}

void space_counter() {
    FILE *fptr = fopen("2-bankDb.txt", "r");

    if(fptr == NULL) {
        printf("Error at space_counter_function\n");
    }else{
        char c = fgetc(fptr);
        int index = 0;

        while (!feof(fptr)) {
            if(c != '\n') {
                if(c == ' ') {
                    space_array[index] +=1;

                }
                c = fgetc(fptr);
            }else{
                index++;
                c = fgetc(fptr);
            }
        }

        for (int j = 0; j < 30; ++j) {
            printf(" %d ",space_array[j]);
        }
        printf("\n");
    }
}

void registration() {
    printf("This is Registration!\n");
    char reEmail[50];
    char re_name[30];
    char re_nrc[50];
    char re_pass[50];
    char re_phNumber[15];

    checkValid = -1;
    while (checkValid == -1){
        printf("Enter your email: ");
        scanf(" %[^\n]", &reEmail[0]);
        gmailValidation(reEmail);
    }

    eFound = -1;
    emailExistChecking(reEmail);
    if(eFound == -1) {
        printf("Enter your name : ");
        scanf(" %[^\n]", &re_name[0]);

        nrc_valid = -1;
        while (nrc_valid == -1) {
            printf("Enter your nrc number : ");
            scanf(" %[^\n]", &re_nrc[0]);
            nrc_validation(re_nrc);
        }

        guessPass = -1;
        while (guessPass == -1) {
            printf("Enter your password : ");
            scanf(" %[^\n]", &re_pass[0]);
            easyToGuess(re_pass);
        }



        phNumberFound = 1;
        while (phNumberFound == 1) {
            phNumberValid = -1;
            while (phNumberValid == -1) {
                printf("Enter your Phone Number : +959 ");
                scanf(" %[^\n]", &re_phNumber[0]);
                phNumberValidation(re_phNumber);

            }

            addCountryCode(re_phNumber);
            phNumberExistChecking(re_phNumber);
        }

        printf("Enter your monthly income :");
        scanf("%u", &db[users].monthly_income);

        printf("Enter your current amount : ");
        scanf("%u", &db[users].cur_amount);

        printf("Enter your  address : ");
        scanf(" %[^\n]", db[users].address);

        //adding to virtual database
        copyChar(reEmail, db[users].email);
        copyChar(re_name, db[users].name);
        copyChar(re_nrc, db[users].nrc);
        copyChar(re_pass, db[users].password);
        copyChar(re_phNumber, db[users].phNumber);
        copyChar(db[2].pOrb, db[users].pOrb);
        copyChar(db[2].loan_status, db[users].loan_status);
        copyChar(db[2].acc_status, db[users].acc_status);
        copyChar(db[2].trc[0].note, db[users].trc[0].note);
        db[users].loan_amount = db[2].loan_amount;
        db[users].loan_rate = db[2].loan_rate;
        db[users].acc_level = db[2].acc_level;
        db[users].transAmoLimitPerDay = db[2].transAmoLimitPerDay;
        db[users].id = users+1;

        users++;

        dataPrinting();

    }else{
        printf("Your email is already taken!\n");
        registration();
    }
}

void login() {
    printf("This  is Login!\n");
    char lEmail[50];
    char lPass[50];

    checkValid = -1;
    while (checkValid == -1) {
        printf("Enter your email :");
        scanf(" %[^\n]", &lEmail[0]);
        gmailValidation(lEmail);
    }

    printf("Enter your password :");
    scanf(" %[^\n]", &lPass[0]);

    eFound=-1;
    emailExistChecking(lEmail);

    pFound=-1;
    passwordExistChecking(lPass);


    if(eFound != -1 && pFound != -1){
        printf("Welcome Sir : %s \n", db[eFound].name);
        printf("Your current amount : %u\n", db[eFound].cur_amount);
        userSector();
    }else if(eFound == -1){
        int option = 0;
    printf("Email doesn't exist!\n");
        printf("Press 1 to register or 2 to try again!\n");
        scanf("%d", &option);
        if(option == 1) {
            registration();
        }else if(option == 2) {
            login();
        } else{
            printf("wrong option!\n");
        }
    }else if(pFound == -1){
        printf("wrong password\n");
        login();
    }
}

void userSector() {
    char option = 0;
    char phNumber_for_transfer[15];
    unsigned int transfer_amount = 0;
    char confirm_password[50];
    printf("This is userSector\n");
    printf("Press 1 to Transfer Money:\nPress 2 to Withdraw:\nPress 3 to update your information\nPress 4 Cash in :\nPress 5 to Loan:\nPress 6 to view your history:\nPress 7 Exit");
    scanf(" %c", &option);
    if(option == 49) {
        printf("This is for transfer option.\n");
        while (is_phNumber_exist == -1) {
            printf("Enter receiver's phone Number : +959 ");
            scanf(" %[^\n]", &phNumber_for_transfer[0]);
            addCountryCode(phNumber_for_transfer);
            is_TwoCharArray_same = -1;
            compare_two_charArray(phNumber_for_transfer, db[eFound].phNumber);
            if(is_TwoCharArray_same == 1){
                printf("Yon can't transfer money to yourself\n");
                continue;
            }
            finding_phone_number(phNumber_for_transfer);
            if(is_phNumber_exist == -1){
                printf("Account doesn't exist with %s. Try Again!\n",phNumber_for_transfer);
            }
        }


        while (transfer_amount < db[eFound].cur_amount){
            printf("Enter amount to transfer :");
            scanf("%u", &transfer_amount);
            if(db[eFound].cur_amount-1000 > transfer_amount) {
                break;
            }else{
                printf("No sufficient balance:\n");
                transfer_amount = 0;
            }
        }

        int wrong_times_counter = 0;
        pFound = -1;
        while (pFound == -1){
            printf("Enter password to confirm :");
            scanf(" %[^\n]", &confirm_password[0]);
            passwordExistChecking(confirm_password);
            if(pFound == -1) {
                printf("Wrong password . Try again!\n");
            }
            wrong_times_counter++;
            if(wrong_times_counter == 3){
                userSector();
                break;
            }
        }

        transfer_money(eFound,is_phNumber_exist,transfer_amount);
        welcome();

    }else {
        printf("wrong option!\n");
        userSector();
    }
}

void transfer_money(int transfer, int receiver, unsigned int amount) {
    printf("Loading for transfer.....\n");
    db[transfer].cur_amount -= amount;
    db[receiver].cur_amount += amount;
    printf("Transaction complete!\n");
    transaction_record(transfer,receiver,'t',amount);
    transaction_record(transfer,receiver,'r',amount);
}

void transaction_record(int transfer, int receiver, char who,unsigned int amount) {
    int transfer_name_counter = charCounting(db[transfer].name);
    int receiver_name_counter = charCounting(db[receiver].name);
    integer_to_char(amount);
    int amount_counter = charCounting(integer_to_char_array);
// from-WinHtut-to-lonelone-100
    char from[5] = {'f','r','o','m','-'};
    char to[4] = {'-','t','o', '-'};

    get_current_time();
    int current_time_array_counter = charCounting(current_time_array);

    if(who == 't'){
        int counter = 0;

        for (int i = 0; i < 5; ++i) {
            db[transfer].trc[space_array[transfer]-15].note[counter] = from[i];
            counter++;
        }

        for (int j = 0; j < transfer_name_counter; ++j) {
            db[transfer].trc[space_array[transfer]-15].note[counter] = db[transfer].name[j];
            counter++;
        }

        for (int k = 0; k < 4; ++k) {
            db[transfer].trc[space_array[transfer]-15].note[counter] = to[k];
            counter++;
        }

        for (int a = 0; a < receiver_name_counter; ++a) {
            db[transfer].trc[space_array[transfer]-15].note[counter] = db[receiver].name[a];
            counter++;
        }
        db[transfer].trc[space_array[transfer]-15].note[counter] = '-';
        counter++;

        for (int i = 0; i < amount_counter; ++i) {
            db[transfer].trc[space_array[transfer]-15].note[counter] = integer_to_char_array[i];
            counter++;
        }

        db[transfer].trc[space_array[transfer]-15].note[counter] = '-';
        counter++;

        for (int i = 0; i < current_time_array_counter; ++i) {
            db[transfer].trc[space_array[transfer]-15].note[counter] = current_time_array[i];
            counter++;
        }
        space_array[transfer] += 1;
    }else{
        char rec[14]={'-','R','e','c','e','i','v','e','-','F','r','o','m','-'};
        int counter = 0;

        for (int i = 0; i < receiver_name_counter; ++i) {
            db[receiver].trc[space_array[receiver]-15].note[counter] = db[receiver].name[i];
            counter++;
        }

        for (int i = 0; i < 14; ++i) {
            db[receiver].trc[space_array[receiver]-15].note[counter] = rec[i];
            counter++;
        }

        for (int i = 0; i < transfer_name_counter; ++i) {
            db[receiver].trc[space_array[receiver]-15].note[counter] = db[transfer].name[i];
            counter++;
        }

        db[receiver].trc[space_array[receiver]-15].note[counter] = '-';
        counter++;

        for (int i = 0; i < amount_counter; ++i) {
            db[receiver].trc[space_array[receiver]-15].note[counter] = integer_to_char_array[i];
            counter++;
        }

        db[receiver].trc[space_array[receiver]-15].note[counter] = '-';
        counter++;

        for (int i = 0; i < current_time_array_counter; ++i) {
            db[receiver].trc[space_array[receiver]-15].note[counter] = current_time_array[i];
            counter++;
        }

        space_array[receiver] += 1;
    }
}

void integer_to_char(unsigned int value) {
    FILE *fptr = fopen("value.txt", "w");
    if(fptr == NULL) {
        printf("error at integer_to_char function\n");
    }else{
        fprintf(fptr,"%u", value);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("value.txt", "r");
    fscanf(fptr2, "%s", &integer_to_char_array[0]);
}

void get_current_time(){
    FILE* fptr = fopen("time.txt", "w");
    if(fptr == NULL) {
        printf("Error at opening time.txt\n");
    }else{
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        fprintf(fptr,"%s", asctime(tm));
    }
    fclose(fptr);

    FILE *fptr2 = fopen("time.txt", "r");
    if(fptr2== NULL){
        printf("Error at reading time.txt");
    }else{
        for (int i = 0; i < 50; ++i) {
            current_time_array[i] = '\0';
        }
        char c = fgetc(fptr2);
        int index = 0;
        while (!feof(fptr2)){
            if(c == ' '){
                current_time_array[index] = '/';
                c = fgetc(fptr2);
                index++;
            } else{
                current_time_array[index] = c;
                c= fgetc(fptr2);
                index++;
            }
        }

    }
    fclose(fptr2);
}

void emailExistChecking(char inputGmail[50]) {
    int sameCount = 0;
    int inputGmailCount = charCounting(inputGmail);
    for (int i = 0; i < users; ++i) {
        int dbGmailCount = charCounting(db[i].email);
        if(inputGmailCount == dbGmailCount) {
            for (int j = 0; j < inputGmailCount; ++j) {
                if(inputGmail[j] == db[i].email[j]) {
                    sameCount++;
                }else {
                    break;
                }
            }
        }
        if(sameCount == inputGmailCount) {
            eFound = i;
            break;
        }
    }

}

void passwordExistChecking(char inputPass[50]) {
    int same = 0;
    int inputPassCount = charCounting(inputPass);
    int dbPassCount = charCounting(db[eFound].password);
    if(inputPassCount == dbPassCount) {
        for (int i = 0; i < inputPassCount; ++i) {
            if(inputPass[i] == db[eFound].password[i]){
                same++;
            } else{
                break;
            }
        }
    }

    if(same == inputPassCount) {
        pFound=1;
    }
}

void phNumberExistChecking(char input_phNumber[15]) {
    for (int i = 0; i < users; ++i) {
        is_TwoCharArray_same=-1;
        compare_two_charArray(input_phNumber,db[i].phNumber);
        if(is_TwoCharArray_same == 1) {
            phNumberFound = 1;
            break;
        }else{
            phNumberFound = -1;
        }
    }
    if(phNumberFound == 1) {
        printf("Phone number is already exist! try Again!\n");
    }
}

void finding_phone_number(char phNumber[15]) {
    for (int i = 0; i < users; ++i) {
        is_TwoCharArray_same = -1;
        compare_two_charArray(phNumber, db[i].phNumber);
        if(is_TwoCharArray_same == 1) {
            is_phNumber_exist = i;
            break;
        }
    }

}

void gmailValidation(char toValid[50]) {
    char form[10] = {'@','g','m','a', 'i', 'l', '.', 'c', 'o', 'm'};
    int endPoint = charCounting(toValid);
    int formCount = charCounting(form);
    int isValid = 0;
    for (int i = 0; i < endPoint; ++i) {
        if(toValid[i] == ' ') {
            break;
        }else if(toValid[i] == form[0]){
            int index = i;
            if(endPoint-index == 10) {
                for (int j = 0; j < formCount; ++j) {
                    if(toValid[index] == form[j]){
                        isValid++;
                        index++;
                    } else{
                        break;
                    }
                }
            }
        }
    }
    if(isValid == formCount) {
        checkValid = 1;
    }else{
        printf("Invalid gmail!\n");
    }
}

int charCounting(char toCount[50]) {
    int count = 0;
    for (int i = 0; i < 50; ++i) {
        if(toCount[i] == '\0'){
            break;
        } else{
            count++;
        }
    }
    return count;
}

void copyChar(char fromFirst[50], char toSecond[50]) {
    for (int i = 0; i < 50; ++i) {
        toSecond[i] = '\0';
    }
    int fromFirstCount = charCounting(fromFirst);
    for (int j = 0; j < fromFirstCount; ++j) {
        toSecond[j] = fromFirst[j];
    }
}

void compare_two_charArray(char first[50], char second[50]) {
    int firstCount = charCounting(first);
    int secCount = charCounting(second);
    int same = 0;
    if (firstCount == secCount) {
        for (int i = 0; i < firstCount; ++i) {
            if(first[i] == second[i]) {
                same++;
            } else{
                break;
            }
        }
        if(same == firstCount) {
            is_TwoCharArray_same=1;
        }
    }
}

void nrc_validation(char nrc_toCheck[50]) {
//    int nrc_count = charCounting(nrc_toCheck);

    for (int i = 0; i < 3; ++i) {
        is_TwoCharArray_same = -1;
        compare_two_charArray(nrc_toCheck, db[i].nrc);
        if(is_TwoCharArray_same == 1){
            nrc_valid = 1;
            break;
        }
    }
    if(nrc_valid == -1) {
        printf("Invalid nrc. Try again!\n");
    }

}

void easyToGuess(char uPass[50]) {
    int specialCount = 0;
    int numberCount = 0;
    int upperCount = 0;
    int lowerCount = 0;
    int uPassCount = charCounting(uPass);

    if(uPassCount >= 8){
        for (int i = 0; i < uPassCount; ++i) {
            if( (uPass[i] == 64 || uPass[i] >= 33 && uPass[i] <= 47)) {
                specialCount++;
            }else if(uPass[i] >= 48 && uPass[i] <=57){
                numberCount++;
            }else if(uPass[i] >=65 && uPass[i] <= 90) {
                upperCount++;
            }else if(uPass[i] >= 97 && uPass[i] <= 122) {
                lowerCount++;
            }
        }
    }else{
        printf("Must be 8 characters or more\n");
        return;
    }

    if(specialCount > 0 && numberCount > 0 && upperCount > 0 && lowerCount > 0) {
        printf("strong password!\n");
        guessPass = 1;
    }else{
        printf("weak password!\n");
        guessPass = -1;
    }

}

void phNumberValidation(char inputPhNumber[15]) {
    int phNumberCount = charCounting(inputPhNumber);
    if(inputPhNumber[0] == '2' && inputPhNumber[1] == '0'){
        if(phNumberCount == 8) {
            printf("Valid phone number!\n");
            phNumberValid = 1;
        } else{
            printf("Invalid phone number!\n");
        }
    }else {
        if(phNumberCount == 9) {
            printf("Valid phone number!\n");
            phNumberValid = 1;
        } else{
            printf("Invalid phone number!\n");
        }
    }
}

void addCountryCode(char phNumber[15]) {
    char countryCode[4] = {'+', '9', '5', '9'};
    char temp_array[50];
    copyChar(phNumber, temp_array);
    for (int i = 0; i < 15; ++i) {
        phNumber[i] = '\0';
    }
    int last_index_of_countryCode = 0;
        for (int i = 0; i < 4; ++i) {
            phNumber[i] = countryCode[i];
            last_index_of_countryCode++;
        }

        int phNumber_count = charCounting(temp_array);
        for (int j = 0; j < phNumber_count; ++j) {
            phNumber[last_index_of_countryCode] = temp_array[j];
            last_index_of_countryCode++;
        }
}




#endif //DIV1_PROJECTS_FOR_BANKPROJECT_H
