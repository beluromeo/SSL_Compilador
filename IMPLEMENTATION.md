# Micro Compiler - Implementation Summary

## Overview
This project implements a complete compiler for the Micro procedural language using Flex and Bison. The compiler translates Micro programs into functional C code.

## Architecture

### 1. Lexical Analysis (scanner.l)
**Tool**: Flex (Fast Lexical Analyzer)
**Purpose**: Tokenization of input

**Tokens recognized**:
- Keywords: `inicio`, `fin`, `leer`, `escribir`
- Operators: `:=`, `+`, `-`, `*`, `/`, `(`, `)`
- Delimiters: `;`, `,`
- Identifiers: `[a-zA-Z][a-zA-Z0-9]*`
- Numeric literals: `[0-9]+`

**Features**:
- Line number tracking for error reporting
- Automatic whitespace handling
- Character validation with error messages

### 2. Syntactic Analysis (parser.y)
**Tool**: Bison (GNU Parser Generator)
**Purpose**: Parse tree construction and semantic actions

**Grammar**:
```
programa → inicio lista_sentencias fin
sentencia → ID := expresion ;
          | leer ( lista_ids ) ;
          | escribir ( lista_expresiones ) ;
expresion → expresion + expresion
          | expresion - expresion  
          | expresion * expresion
          | expresion / expresion
          | ( expresion )
          | ID | NUM
```

**Features**:
- Left-associative operator precedence
- Semantic actions for code generation
- Error recovery with line numbers

### 3. Symbol Table (symtab.c/h)
**Purpose**: Variable tracking and management

**Operations**:
- `inicializar_symtab()`: Initialize empty table
- `agregar_simbolo(nombre)`: Add new symbol (prevents duplicates)
- `buscar_simbolo(nombre)`: Lookup by name
- `obtener_simbolos(count)`: Get all symbols for declaration

**Features**:
- Maximum 1000 symbols
- Hash-free linear search (suitable for small programs)
- Safe string handling

### 4. Code Generation (codegen.c/h)
**Purpose**: Generate C code from parse tree

**Strategy**: Two-pass generation
1. **First pass**: Collect statements in temporary file
2. **Second pass**: Generate complete C program with:
   - Standard includes
   - Variable declarations (from symbol table)
   - Temporary variables (for expressions)
   - Program statements
   - Return statement

**Generated code features**:
- Clean, readable output
- Commented sections
- Proper indentation
- Standard C conformance

### 5. Build System (Makefile)
**Targets**:
- `all`: Build the compiler
- `clean`: Remove generated files
- `cleanall`: Complete cleanup
- `test`: Run automated tests
- `help`: Display usage information

**Build process**:
1. Bison generates parser (parser.tab.c/h)
2. Flex generates scanner (lex.yy.c)
3. Compile all C files
4. Link into executable

## Testing Strategy

### Test Cases
1. **ejemplo.micro**: Basic I/O and arithmetic
2. **ejemplo2.micro**: Multiple operations with I/O
3. **ejemplo3.micro**: Literal assignments
4. **ejemplo4.micro**: All operators (+, -, *, /)
5. **ejemplo5.micro**: Parenthesized expressions

### Test Script (test.sh)
Automated testing with:
- Input simulation
- Output verification
- Exit status checking

## Security Considerations

### Memory Safety
- NULL checks on malloc calls
- Safe string copying with size limits
- Proper buffer size calculations
- No unchecked pointer dereferences

### Input Validation
- Lexical validation of all characters
- Syntactic validation of program structure
- File existence checking
- Bounded symbol table

## Code Quality Features

### Maintainability
- Named constants for buffer sizes
- Modular design with clear separation
- Comprehensive comments
- Consistent naming conventions

### Robustness
- Error messages with line numbers
- Graceful failure on invalid input
- Resource cleanup (file closing)
- Exit codes for error conditions

## Performance Characteristics

### Time Complexity
- Lexical analysis: O(n) where n = input length
- Parsing: O(n) for LL(1) grammar
- Symbol table: O(n) lookup (linear search)
- Code generation: O(n) statements

### Space Complexity
- Symbol table: O(variables)
- Generated code: O(statements + expressions)
- Temporary variables: O(expression depth)

## Limitations and Future Work

### Current Limitations
- Integer types only
- No control structures (if, while)
- No functions/procedures
- No arrays or complex types
- Limited error recovery

### Potential Enhancements
1. **Type system**: Float, string, boolean types
2. **Control flow**: if-then-else, while, for loops
3. **Functions**: User-defined procedures
4. **Data structures**: Arrays, records
5. **Optimization**: Constant folding, dead code elimination
6. **Better errors**: More descriptive messages with suggestions

## Educational Value

This compiler demonstrates:
- Lexical analysis with regular expressions
- Context-free grammar parsing
- Symbol table management
- Code generation techniques
- Two-pass compilation
- Integration of tools (Flex + Bison)

## Conclusion

The Micro compiler successfully implements a complete compilation pipeline from source code to executable C output, providing a solid foundation for understanding compiler construction principles.
