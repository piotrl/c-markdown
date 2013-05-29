c-markdown
==========

Simple command-line *[Markdown](http://daringfireball.net/projects/markdown/) to HTML* parser in C. It supports few markdown commands, which list you can find below. It's just a fun competition, no big deal. ;) You can find other cool libaries like [PEG-markdown](https://github.com/jgm/peg-markdown).

## Installing
Type in your terminal in appropriate directory with program files:
    make

## Usage
    ./markdown [input-file] [output-file]
If you don't specify the _output-file_, program will parse everything to stdout in your terminal.

###Examples

#### Quotes
    > quotes
    > quotes

#### Headers
    # 1st header
    ## 2nd header
    ### 3rd header
    .
    .
    .
    and so on.

#### Inline formating:
    *bold test* and _italics_.

#### Links:
    [link-name](example.com/cats)

#### Lists:
    * No 1
    * Next please!
    * Here I am!