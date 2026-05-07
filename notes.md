 **Wtf is a `EditingHostManager` and how should that handle removing a word**

**The way we pick how much of a word + whitespace should be included is a bit weird**
- Seems to be decided in `LibUnicode/Segmenter.cpp`
- On Firefox:
    - When forward:
        - Includes all trailing whitespace
            1. `|word word word`
            2. *Ctrl+LeftArrow*
            3. `word |word word`
    - When backward:
        - Doesn't include leading whitespace
            1. `word word word|`
            2. *Ctrl+LeftArrow*
            3. `word word |word`

**Also add undo and redo functionality to text inputs**
- Use stack with changes in `FormAssociatedTextControlElement` and pop/push them onto a stack
- How to represent changes?
  - Just save the state for each snapshot?
- How often should we save changes?
