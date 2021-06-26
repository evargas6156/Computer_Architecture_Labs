# Traditional Matrix Multiply program
		.data
matrix_a:
		.word   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12
		.word  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
		.word  25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
		.word  37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48
		.word  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
		.word  61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72
		.word  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84
		.word  85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96
		.word  97, 98, 99,100,101,102,103,104,105,106,107,108
		.word 109,110,111,112,113,114,115,116,117,118,119,120
		.word 121,122,123,124,125,126,127,128,129,130,131,132
		.word 133,134,135,136,137,138,139,140,141,142,143,144

matrix_b:
		.word 133,134,135,136,137,138,139,140,141,142,143,144
		.word 121,122,123,124,125,126,127,128,129,130,131,132
		.word 109,110,111,112,113,114,115,116,117,118,119,120
		.word  97, 98, 99,100,101,102,103,104,105,106,107,108
		.word  85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96
		.word  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84
		.word  61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72
		.word  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
		.word  37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48
		.word  25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
		.word  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
		.word   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12

matrix_c:
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0

bs:		.word 3
n:		.word 12

nline:  .asciiz "\n"				#Define new line string
sp:		.asciiz " "
msga: 	.asciiz "Matrix A is: \n"
msgb: 	.asciiz "Matrix B is: \n"
msgc: 	.asciiz "Matrix C=A*B is: \n"

		.text
		.globl main
main:

		la	$s0, bs	
		lw	$s0, 0($s0)
		la	$s1, n
		lw	$s1, 0($s1)
		la	$s2, matrix_a
		la	$s3, matrix_b
		la	$s4, matrix_c

		la	$a0, msga
		la 	$a1, matrix_a
		jal	PRINT_MAT 
		la	$a0, msgb
		la 	$a1, matrix_b
		jal	PRINT_MAT 

# Your CODE HERE
		
		#initialize i, j, and k to 0
		li $t0, 0 #i
		li $t1, 0 #j
		li $t2, 0 #k
		
		#load in the element size into $t8  and row size intp $t9
		li $t8, 4 #each element is 4 bytes large
		li $t9, 12 #each row contains 12 elements 
		
		#first i loop to iterate over rows
	IFOR:
		beq $t0, $s1, IDONE #check loop condition	
		#i for loop code here 
		
		
		#second nested j loop to iterate over columns
		JFOR:
			beq $t1, $s1, JDONE #check loop condition
			#j for loop code here
			
			
			#third nested k loop to perform multiplication
			KFOR:
				beq $t2, $s1, KDONE #check loop condition 
				#k for loop code here 
				
								#calculate current element address for a[i][k] and store into $s5
				mult $t9, $t0 #multiply it row_size * i
				mflo $t7
				add $t3, $t2, $t7 #add k
				mult $t3, $t8 # multiply by element size
				mflo $t3
				add $t3, $s2, $t3 #add base address 
				lw $s5, 0($t3)
				
				#calculate current element address for b[k][j] and store into $s6
				mult $t9, $t2 #multiply it row_size * k
				mflo $t7
				add $t4, $t1, $t7 #add j
				mult $t4, $t8 # multiply by element size 
				mflo $t4
				add $t4, $s3, $t4 #add base address 				
				lw $s6, 0($t4)
				
				#calculate current element address for c[i][j] and store into $s7
				mult $t9, $t0 #multiply it row_size * i
				mflo $t7
				add $t5, $t1, $t7 #add j
				mult $t5, $t8 # multiply by element size 
				mflo $t5
				add $t5, $s4, $t5 #add base address 				
				lw $s7, 0($t5)
				
				#calculate value to store into c[i][j]
				mult $s5, $s6
				mflo $t7
				add $t6, $t7, $s7
				sw $t6, 0($t5)
				
				addi $t2, $t2, 1 #increment k
				j KFOR
			KDONE:
				
			li $t2, 0 #reset k back to zero
			addi $t1, $t1, 1 #increment j
			j JFOR
		JDONE:
		
		li $t1, 0 #reset j back to zero
		addi $t0, $t0, 1  #increment i
		j IFOR
		
	IDONE:	
		
		

# End CODE

		la	$a0, msgc
		la 	$a1, matrix_c
		jal	PRINT_MAT 

#   Exit
		li	 $v0,10
    	syscall


PRINT_MAT:	li	$v0,4
		syscall
		addi $a2,$0,0	
PL4:	bge	$a2,$s1,PL1
		addi $a3,$0,0
PL3:	bge	$a3,$s1,PL2

		lw	$a0,0($a1)
		li	$v0,1
		syscall
		la	$a0,sp
		li	$v0,4
		syscall
		addi $a1,$a1,4
		addi $a3,$a3,1
		b 	PL3

PL2:	addi	$a2,$a2,1
		la	$a0,nline
		li	$v0,4
		syscall
		b	PL4
PL1:	jr	$ra
