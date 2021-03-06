# ILOC Register Allocation with Dead Opcode Eliminator

### ILOC Overview

<p>
    <img src="https://user-images.githubusercontent.com/50348516/168185749-ecebaeff-91d7-49e1-bee0-6a346d77fa7e.png" align="right" height="300" width="225"/> <img src="https://user-images.githubusercontent.com/50348516/168185683-10860c41-ec1d-4dad-bf65-5ac4db4c4907.png" align="right" height="200" width="200"/>  </p>
    
The ILOC instruction set has similar feature parity with the more widely-known Assembly instruction set.
In C code, the compiler takes the higher level language and translates it into a lower level language of Assembly. Which then gets translated to machine code of just 1s and 0s.

More information on the ILOC language can be found [here](https://www.clear.rice.edu/comp512/Labs/SimDoc2015.pdf)

### Register Allocation

One of the key roles of the compiler is deciding how to allocate physical CPU registers most efficiently as it does its translation. If the higher level language involves many arithemetic and memory operations, then it is advatangeous to have as many physical registers as possible to account for all of them. But in the real world, processors only have a limited amount.

<img src="https://user-images.githubusercontent.com/50348516/168216766-ffffbaf8-989e-4edc-82d5-fbc3166da61c.png" align="left" height="370" width="400" /> 

So to solve this issue, the compiler must dedicate a certain number of available physical registers to act as virtual registers. The job of these virtual registers is to give somewhere for the CPU to offload values that aren't immediately needed so that the normal physical registers can be filled with values that are immediately needed for arithmetic operations.

Whenever the compiler needs to spill values from physcial registers to virtual registers, it must produce respective spill code. Spill code inherently has a performance penalty as it implies that processing time that could have been used for arithmetic operations are instead wasted on register-to-register transfers. Minimizing the amount of spill code produced during compilation is crucial for maximizing efficiency of compiled code.

Register allocation typically follows either a bottom-up or top-down approach. The former involves allocating available registers based on when a value will be used further down in the compiled code. The latter makes use of some built-up knowledge of the compiled code after a pass and then allocating registers based on that knowledge.

### Dead Code Elimination

For efficiency, the compiler also needs to do a good job at removing unnecessary opcodes from its code translation. In higher level languages, some examples of dead code would include assignment of variables that are never used in the program or a pointless arithmetic operation where the result is never used afterword.

Consider the code snippet below

```
Original Program    ILOC Opcode generated                       Original Program    New ILOC Opcode
func():             loadI 1024 => r0                            func():             loadI 1024 => r0
    int a = 2       loadI 1 => r1                                   int a = 2       loadI 1 => r1    
    int b = 2       loadI 2 => r2             Dead Code             int b = 2 
                                        ---- Elimination ---->
    int c = a + b   add r1, r2 => r3                                int c = a + b
    
    print a         store r1 => r0                                  print a         store r1 => r0
                    output 1024                                                     output 1024
```

In this example, the compiled code that corresponds to variables *b* & *c* will be eliminated because the final operation has no dependency on these values. However, if a print statement depending on variable *c* were to exist, then their respective opcodes would remain.

To determine which opcodes to include and which to eliminate, the compiler may build a dependecy graph starting from the last opcode where a register is used for fucntion return or print to standard out. Moving backward from the final opcode, opcodes that involve registers included in the final opcode are added to the dependecy graph. Afterwards, opcode and register dependency is traced until the graph cannot be expanded any further. Any opcodes that do no contribute to important output code are then eliminated.
