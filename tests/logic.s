ADDI $7, $0, 5598 # -> bianire : 001000 00000 00111 0001010111011110
ADDI $6, $0, 436 # -> binaire : 001000 00000 00110 0000000110110100
ADDI $5, $0, 20067 # -> binaire : 001000 00000 00101 0100111001100011
AND $7, $7, $6 # -> binaire : 000000 00111 00110 00111 00000 100100
OR $6, $6, $5 # -> binaire : 000000 00110 00101 00110 00000 100101
XOR $5, $5, $6 # -> binaire : 000000 00101 00110 00101 00000 100110

# EXPECTED_ASSEMBLY
# 200715DE
# 200601B4
# 20054E63
# 00E63824
# 00C53025
# 00A62826

# EXPECTED_FINAL_STATE
# $05:404
# $06:20471
# $07:404