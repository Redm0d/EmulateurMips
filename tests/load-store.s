LUI $7, 16 # -> binaire : 001111 00000 00111 0000000000010000
SW $7, 48($6) # -> bianire : 101011 00110 00111 0000000000110000
LW $13, 48($6) # -> binaire : 100011 00110 00101 0000000000110000


# Remarque : les instructions MFHI et MFLO sont testées dans arithmetic

# EXPECTED_ASSEMBLY
# 3C070010
# ACC70030
# 8CCD0030

# EXPECTED_FINAL_STATE
# $07: 1048576
# $13 :1048576