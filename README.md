
# Table of Contents

1.  [Weird Vm - The bullshit VM you didn't know you wanted to hack on](#orgd4dce74)
2.  [What this is](#orge49aa88)
3.  [Documentation](#org5ef30a3)
    1.  [Instructions](#org73f7dfd)



<a id="orgd4dce74"></a>

# Weird Vm - The bullshit VM you didn't know you wanted to hack on


<a id="orge49aa88"></a>

# What this is

This is a small bytecode VM.
It comes with an assembler and a disassembler for your programs.
It's silly, really. You'll see.


<a id="org5ef30a3"></a>

# Documentation


<a id="org73f7dfd"></a>

## Instructions

the instructions are 8-bit wide. wow.
They're here:

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-right" />

<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">name</th>
<th scope="col" class="org-right">opcode</th>
<th scope="col" class="org-left">description</th>
<th scope="col" class="org-left">Implemented?</th>
</tr>
</thead>
<tbody>
<tr>
<td class="org-left">NOP</td>
<td class="org-right">0x00</td>
<td class="org-left">NO-OP</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">ADD8</td>
<td class="org-right">0x01</td>
<td class="org-left">Add next two operands as u8s,  put the result in RES registers</td>
<td class="org-left">y</td>
</tr>

<tr>
<td class="org-left">ADD16</td>
<td class="org-right">0x11</td>
<td class="org-left">Add next two operands as u16s, put the result in RES registers</td>
<td class="org-left">y</td>
</tr>

<tr>
<td class="org-left">INC</td>
<td class="org-right">0x21</td>
<td class="org-left">Increment operand (representing register)</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">SUB8</td>
<td class="org-right">0x02</td>
<td class="org-left">Sub next two operands as u8s,  put the result in RES registers</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">SUB16</td>
<td class="org-right">0x12</td>
<td class="org-left">Sub next two operands as u16s, put the result in RES registers</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">DEC</td>
<td class="org-right">0x22</td>
<td class="org-left">Sub next two operands as u8s,  put the result in RES registers</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">MUL8</td>
<td class="org-right">0x03</td>
<td class="org-left">Mul next two operands as u8s,  put the result in RES registers</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">MUL16</td>
<td class="org-right">0x13</td>
<td class="org-left">Mul next two operands as u16s, put the result in RES registers</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">DIV8</td>
<td class="org-right">0x04</td>
<td class="org-left">Div next two operands as u8s,  put the result in RES registers</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">DIV16</td>
<td class="org-right">0x14</td>
<td class="org-left">Div next two operands as u16s, put the result in RES registers</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">PSHDAT</td>
<td class="org-right">0x05</td>
<td class="org-left">Pushes Next n pieces of data on the stack, fist operand defines type</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">POPDAT</td>
<td class="org-right">0x15</td>
<td class="org-left">Pops pieces of data and places it in the RES register</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">PRINT</td>
<td class="org-right">0x06</td>
<td class="org-left">Dumps the register specified in operand</td>
<td class="org-left">y</td>
</tr>

<tr>
<td class="org-left">CMP</td>
<td class="org-right">0x07</td>
<td class="org-left">Compares operand 1 and 2, and sets the CMP register.</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">JIZ</td>
<td class="org-right">0x17</td>
<td class="org-left">If the comparison was to 0 and true, Sets link reg to current PC, sets PC to operand as u16</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">JEQ</td>
<td class="org-right">0x27</td>
<td class="org-left">If the comparison was Equal and true, Sets link reg to current PC, sets PC to operand as u16</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">JIL</td>
<td class="org-right">0x37</td>
<td class="org-left">If the comparison was Lesser than and true, Sets link reg to current PC, sets PC to operand as u16</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">JIG</td>
<td class="org-right">0x47</td>
<td class="org-left">If the comparison was Greater than and true, Sets link reg to current PC, sets PC to operand as u16</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">JTO</td>
<td class="org-right">0x57</td>
<td class="org-left">Unconditionally Jump</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">STO</td>
<td class="org-right">0x08</td>
<td class="org-left">Stores into register (specified as operand 1) value (specified in operand 2)</td>
<td class="org-left">n</td>
</tr>

<tr>
<td class="org-left">DRW</td>
<td class="org-right">0xDD</td>
<td class="org-left">Dumps contents of screen memory zone onto screen</td>
<td class="org-left">n</td>
</tr>
</tbody>
</table>

