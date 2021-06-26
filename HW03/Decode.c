//ATTENTION: PLEASE COMPILE WITH THIS COMMAND BEFORE RUNNING AND USE "./run" TO RUN
// gcc -o run Decode.c -lm -fno-stack-protector

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// function declarations 
void decodeInstruction(char instruction[]);

void decodeTypeI(char instruction[]);

void decodeTypeJ(char instruction[]);

void decodeTypeR(char instruction[]);

int convertFromBinToInt(char binary[]);

int convertFromBinToIntTwosComplement(char twosBinary []);

char* registerName(int registerNumber);

char* functionNameTypeR(int function);

char* operationNameTypeI(int opcode);


int main(){
   
    //ask for input
    printf("Enter an instruction in machine code:\n\n");

    //create a variable to hold the instruction
    char instruction[32]; 

    //get the instruction 
    scanf("%s", instruction);
    printf("\n");

    //call function to convert instruction to MIPS
    decodeInstruction(instruction);

    //testing twos complement function
    // int test = convertFromBinToIntTwosComplement(instruction);
    // printf("Twos complement: %d\n", test);
    // return 0;
}

void decodeInstruction(char  instruction[]){

    //take the substring relevant to the opcode field
    //printf("instruction: %s\n", instruction);
    char opcodeBin[7];
    memcpy(&opcodeBin, &instruction[0], 6);
    opcodeBin[6] = '\0';

    //convert the opcode to be an integer 
    //printf("opcode: %s\n", opcodeBin);
    int opcode = convertFromBinToInt(opcodeBin);

    //check opcode to match instruction to its type
    if(opcode == 0){
        //instruction is R type call function
        decodeTypeR(instruction);
    }else if(opcode == 2 || opcode == 3){
        //instruction is J type call function
        decodeTypeJ(instruction);
    }else{
        //instruction is I type call fuction
        decodeTypeI(instruction);
    }
}

void decodeTypeI(char instruction[]){

    //print the instruction type
    printf("Instruction Type: I\n");

    //grab relevant bits for opcode field 
    char opcodeBin[7]; 
    memcpy(&opcodeBin, &instruction[0], 6);
    opcodeBin[6] = '\0';

    //convert opcode to decimal 
    int opcode = convertFromBinToInt(opcodeBin);
    


    //find the relevant name for the given opcode and print it
    char *functName = operationNameTypeI(opcode);
    printf("Operation: %s\n", functName);

    //grab bits relevant to rs 
    char rsBin[6]; 
    memcpy(&rsBin, &instruction[6], 5);
    rsBin[5] = '\0';

    //convert to decimal and get name, print it 
    int rs = convertFromBinToInt(rsBin);
    char *rsName = registerName(rs);
    printf("Rs: %s (R%d)\n", rsName, rs);

    //grab bits relevant to rt 
    char rtBin[6]; 
    memcpy(&rtBin, &instruction[11], 5);
    rsBin[5] = '\0';

    //convert to decimal and get name, print it 
    int rt = convertFromBinToInt(rtBin);
    char *rtName = registerName(rt);
    printf("Rt: %s (R%d)\n", rtName, rt);

    //grab bits relevant to immediate

    char immBin[17]; 
    memcpy(&immBin, &instruction[16], 16);
    immBin[16] = '\0';

    //printf("Immediate binary: %s\n", immBin);
    
    //convert to decimal and get name, print it 
    //if opcode says unsigned, use default otherwise use 2's comp
    int imm;
    if (opcode == 9 || opcode == 36 || opcode == 37 || opcode == 11){
        imm = convertFromBinToInt(immBin);
        printf("Immediate: %d\n", imm);


    } else {
        if (immBin[0] == '1'){
            imm = convertFromBinToIntTwosComplement(immBin);
            printf("Immediate: %d\n", imm);

        } else {

            imm = convertFromBinToInt(immBin);
            printf("Immediate: %d\n", imm);

        }
    }
    
    





}
 
void decodeTypeJ(char instruction[]){

    //print the instruction type
    printf("Instruction Type: J\n");

    //take the substring relevant to the opcode field
    //printf("instruction: %s\n", instruction);
    char opcodeBin[7];
    memcpy(&opcodeBin, &instruction[0], 6);
    opcodeBin[6] = '\0';

    //convert the opcode to be an integer 
    //printf("opcode: %s\n", opcodeBin);
    int opcode = convertFromBinToInt(opcodeBin);

    //find name for the given function and print it
    
    if (opcode == 2){
        char *functName = "j";
        printf("Operation: %s\n", functName);
    } else {
        char *functName = "jal";
        printf("Operation: %s\n", functName);
    }
    
    



    //grab relevant bits for address field. 
    char addressBin[27];
    memcpy(&addressBin, &instruction[6], 26);
    addressBin[26] = '\0';
    
    //convert address to decimal
    
    int address = convertFromBinToInt(addressBin);
    //print address
    printf("Address: %d\n", address);
}

void decodeTypeR(char instruction[]){

    //print the instruction type
    printf("Instruction Type: R\n");

    //grab relevant bits for function field 
    char functionBin[7]; 
    memcpy(&functionBin, &instruction[26], 6);
    functionBin[6] = '\0';

    //convert function code to decimal 
    int function = convertFromBinToInt(functionBin);
    //printf("function Binary: %s\n",functionBin);
    //printf("function num: %d\n", function);

    //find the relevant name for the given function code and print it
    char *functName = functionNameTypeR(function);
    printf("Operation: %s\n", functName);
    
    //take 
    if(function == 8){

        //this function is jr
        //only utilizes rs

         //grab bits relevant to rs 
        char rsBin[6]; 
        memcpy(&rsBin, &instruction[6], 5);
        rsBin[5] = '\0';
        //convert to decimal and get name, print it 
        int rs = convertFromBinToInt(rsBin);
        char *rsName = registerName(rs);
        printf("Rs: %s (R%d)\n", rsName, rs);

        //rt and rd are not used, print not used
        printf("Rt: NOT USED\n");
        printf("Rd: NOT USED\n");

        //this operation does not use shamt, print it as 0
        printf("Shamt: 0\n");
    }else if(function == 0 || function == 2){

        //these instructions (sll and srl) utilize rd, rt, and shamt

        //since rs is not used, print it is not used
        printf("Rs: NOT USED\n");

        //grab the relevant information for rt and rd

         //grab bits relevant to rt 
        char rtBin[6]; 
        memcpy(&rtBin, &instruction[11], 5);
        rtBin[5] = '\0';
        //convert to decimal and get name, print it
        int rt = convertFromBinToInt(rtBin);
        char *rtName = registerName(rt);
        printf("Rt: %s (R%d)\n", rtName, rt);


        //grab bits relevant to rd 
        char rdBin[6]; 
        memcpy(&rdBin, &instruction[16], 5);
        rdBin[5] = '\0';
        //convert to decimal and get name, print it
        int rd = convertFromBinToInt(rdBin);
        char *rdName = registerName(rd);
        printf("Rd: %s (R%d)\n", rdName, rd);

        //grab relevant bits for shamt
        char shamtBin[6]; 
        memcpy(&shamtBin, &instruction[21], 5);
        rdBin[5] = '\0';
        //convert the shamt to decimal and print
        int shamt = convertFromBinToInt(shamtBin);
        printf("Shamt: %d", shamt);

    }else{

        //the rest of the operations utilize all three registers, no shamt
        
        //grab bits relevant to rs 
        char rsBin[6]; 
        memcpy(&rsBin, &instruction[6], 5);
        rsBin[5] = '\0';
        //convert to decimal and get name, print it 
        int rs = convertFromBinToInt(rsBin);
        char *rsName = registerName(rs);
        printf("Rs: %s (R%d)\n", rsName, rs);

        //grab bits relevant to rt 
        char rtBin[6]; 
        memcpy(&rtBin, &instruction[11], 5);
        rtBin[5] = '\0';
        //convert to decimal and get name, print it
        int rt = convertFromBinToInt(rtBin);
        char *rtName = registerName(rt);
        printf("Rt: %s (R%d)\n", rtName, rt);


        //grab bits relevant to rd 
        char rdBin[6]; 
        memcpy(&rdBin, &instruction[16], 5);
        rdBin[5] = '\0';
        //convert to decimal and get name, print it
        int rd = convertFromBinToInt(rdBin);
        char *rdName = registerName(rd);
        printf("Rd: %s (R%d)\n", rdName, rd);

        //since none of these operations use shamt, print it as 0
        printf("Shamt: 0\n");
    }

  

    //all instructions print out the function code found above 
    printf("Funct: %d\n", function);


}


//helper functions to perform various repetitive and mundane tasks

//a function to convert a binary string to an integer
int convertFromBinToInt(char binary[]){

    //grab the length of the binary string
    int length = strlen(binary);
    //printf("length: %d\n", length);
    //return value 
    double decimal = 0;

    //iterate over the string 
    for(int i = 0; i < length; i++){
        //if the char is 1, apply relevant power of 2 and add to result
        if(binary[length - i - 1] == '1'){
            decimal += pow(2.0, (double) i);
        }
        //printf("Iteration: %d, decimal: %f\n", i, decimal);
    }

    //type cast to integer and return
    return (int) decimal;

}

//a function to convert a binary string to an negative integer using two's complement 
int convertFromBinToIntTwosComplement(char twosBinary []){

    //a variable to hold the converted decimal 
    int decimal = 0;

    //since the given number is already a two's complement reverse the bits and add 1

    //first reverse the bits 
    int length = strlen(twosBinary);

    //printf("length: %d\n", length);
    for(int i = 0; i < length; i++){

        if(twosBinary[i] == '1'){
            
            //if bit is 1 flip it to 0
            twosBinary[i] = '0';

        }else{

            //if bit is 0 then flip it to 1
            twosBinary[i] = '1';
        }
    }
    //printf("twos flipped: %s\n", twosBinary);

    //now add 1 to the reversed bits 
    for(int i = length - 1; i >= 0; i--){

        //starting from the back flip 1's to 0 until a 0 is reached and flip it to a 1
        if(twosBinary[i] == '0'){
            twosBinary[i] = '1';
            break;
        }else{
            twosBinary[i] = '0';
        }
    }
    //printf("Converted twos binary: %s\n", twosBinary);
    //now the twos complement is ready to be converted to decimal and multiplied by -1
    decimal = -1 * convertFromBinToInt(twosBinary);
    return decimal; 
}

//a function to return the name of the register as a string given the registers number
char* registerName(int registerNumber){
    char *name;

    //set name based on register number
    if(registerNumber == 0){
        name = "zero";
    }else if(registerNumber == 1){
        name = "at";
    }else if(registerNumber == 2){
        name = "v0";
    }else if(registerNumber == 3){
        name = "v1";
    }else if(registerNumber == 4){
        name = "a0";
    }else if(registerNumber == 5){
        name = "a1";
    }else if(registerNumber == 6){
        name = "a2";
    }else if(registerNumber == 7){
        name = "a3";
    }else if(registerNumber == 8){
        name = "t0";
    }else if(registerNumber == 9){
        name = "t1";
    }else if(registerNumber == 10){
        name = "t2";
    }else if(registerNumber == 11){
        name = "t3";
    }else if(registerNumber == 12){
        name = "t4";
    }else if(registerNumber == 13){
        name = "t5";
    }else if(registerNumber == 14){
        name = "t6";
    }else if(registerNumber == 15){
        name = "t7";
    }else if(registerNumber == 16){
        name = "s0";
    }else if(registerNumber == 17){
        name = "s1";
    }else if(registerNumber == 18){
        name = "s2";
    }else if(registerNumber == 19){
        name = "s3";
    }else if(registerNumber == 20){
        name = "s4";
    }else if(registerNumber == 21){
        name = "s5";
    }else if(registerNumber == 22){
        name = "s6";
    }else if(registerNumber == 23){
        name = "s7";
    }else if(registerNumber == 24){
        name = "t8";
    }else if(registerNumber == 25){
        name = "t9";
    }else if(registerNumber == 26){
        name = "k0";
    }else if(registerNumber == 27){
        name = "k1";
    }else if(registerNumber == 28){
        name = "gp";
    }else if(registerNumber == 29){
        name = "sp";
    }else if(registerNumber == 30){
        name = "fp";
    }else if(registerNumber == 31){
        name = "ra";
    }

    //return pointer to the name
    return name;
}

//a function to return the name of an r type instructions 
char* functionNameTypeR(int function){
    char *functName;

    switch(function){
        case 32:
            functName = "add";
            break;
        case 33:
            functName = "addu";
            break;
        case 36:
            functName = "and";
            break;
        case 8:
            functName = "jr";
            break;
        case 39:
            functName = "nor";
            break;
        case 37:
            functName = "or";
            break;
        case 42:
            functName = "slt";
            break;
        case 43:
            functName = "sltu";
            break;
        case 0:
            functName = "sll";
            break;
        case 2:
            functName = "srl";
            break;
        case 34:
            functName = "sub";
            break;
        case 35:
            functName = "subu";
            break;
        default :
            functName = "ERROR";
    }

    return functName;
}

//a function to return the name of an r type instructions 
char* operationNameTypeI(int opcode){
    char *operationName;

    switch(opcode){
        case 8:
            operationName = "addi";
            break;
        case 9:
            operationName = "addiu";
            break;
        case 12:
            operationName = "andi";
            break;
        case 4:
            operationName = "beq";
            break;
        case 5:
            operationName = "bne";
            break;
        case 36:
            operationName = "lbu";
            break;
        case 37:
            operationName = "lhu";
            break;
        case 43:
            operationName = "sw";
            break;
        case 15:
            operationName = "lui";
            break;
        case 35:
            operationName = "lw";
            break;
        case 13:
            operationName = "ori";
            break;
        case 48:
            operationName = "ll";
            break;
        case 10:
            operationName = "slti";
            break;
        case 11:
            operationName = "sltiu";
            break;
        case 40:
            operationName = "sb";
            break;
        case 56:
            operationName = "sc";
            break;
        case 41:
            operationName = "sh";
            break;
        default :
            operationName = "ERROR";

        //need load link, SLTI, sltiu, sb, sc, sh
    }

    return operationName;
}