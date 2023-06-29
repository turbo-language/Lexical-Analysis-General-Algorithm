# Introduction:

Basic Lexical Analysis for the Turbo language.

**What it handles:**
- Basic identifiers (like `x`, `a1`, etc.)
- Comments
- 2 keywords: `return` and `def`
  - More present in the Token Library, but for a general demonstration, only handling two is easier

 **Errors/Things to work on**
 - Being able to recognize and characterize more complicated syntax
 - Being able to recognize and characterize more complicated identifers
 - Being able to recognize a diverse set of keywords and other tokens
 - _Rust implementation_

# General Algorithm:
The Algorithm can be divided into two parts: a Scanner, and a Analyzer.

**Scanning:**
- Take in the source code (main.turbo) as input
- Read the file into a buffer, a vector of characters.

**Analysis:**
- Pseudocode:

```
 Analyzer(buffer, prev_tokens, prev_pos):
        Create tokens = prev_tokens
        Create pos = prev_pos

        Create lastChar <-- Character that was just peaked and consumed
        Create token_string <--String to be checked for token

        If (Nothing is present or at the end of the buffer):
            add a EOF token
            return the vector

        otherwise:
            Skip whitespaces

            Check for Identifiers and reserved words

            Check for Numbers

            Ignore comments

            Recurse Case --> Analyze(buffer, tokens, pos) <-- Call will check if the end is reached and will update tokens

```

The Analysis uses recursion for buffer traversal
