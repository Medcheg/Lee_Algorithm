/**
 * \file cursor.h
 * \brief
 * \brief  *******************************************
 * \brief  ********* Consol cursor movement **********
 * \brief  *******************************************
 * \brief
 * \brief ANSI Escape Sequences
 * \brief
 * \brief Wherever you see '#', that should be replaced by the appropriate number.
 * \brief
 * \brief         ESC code sequence Function
 * \brief        ------------------- ---------------------------
 * \brief Cursor Controls:
 * \brief          ESC[#;#H or ESC[#;#f Moves cusor to line #, column #
 * \brief          ESC[#A Moves cursor up # lines
 * \brief          ESC[#B Moves cursor down # lines
 * \brief          ESC[#C Moves cursor forward # spaces
 * \brief          ESC[#D Moves cursor back # spaces
 * \brief          ESC[#;#R Reports current cursor line & column
 * \brief          ESC[s Saves cursor position for recall later
 * \brief          ESC[u Return to saved cursor position
 * \brief
 * \brief Erase Functions:
 * \brief          ESC[2J Clear screen and home cursor
 * \brief          ESC[K Clear to end of line
 * \brief
 * \brief Set Graphics Rendition:
 * \brief          ESC[#;#;....;#m Set display attributes where # is
 * \brief                                        00 for normal display (or just 0)
 * \brief                                        01 for bold on (or just 1)
 * \brief            02 faint (or just 2)
 * \brief            03 standout (or just 3)
 * \brief                                        04 underline (or just 4)
 * \brief                                        05 blink on (or just 5)
 * \brief                                        07 reverse video on (or just 7)
 * \brief                                        08 nondisplayed (invisible) (or just 8)
 * \brief            22 normal
 * \brief            23 no-standout
 * \brief            24 no-underline
 * \brief            25 no-blink
 * \brief            27 no-reverse
 * \brief                                        30 black foreground
 * \brief                                        31 red foreground
 * \brief                                        32 green foreground
 * \brief                                        33 yellow foreground
 * \brief                                        34 blue foreground
 * \brief                                        35 magenta foreground
 * \brief                                        36 cyan foreground
 * \brief                                        37 white foreground
 * \brief                                        39 default foreground
 * \brief                                        40 black background
 * \brief                                        41 red background
 * \brief                                        42 green background
 * \brief                                        43 yellow background
 * \brief                                        44 blue background
 * \brief                                        45 magenta background
 * \brief                                        46 cyan background
 * \brief                                        47 white background
 * \brief                                        49 default background
 * \brief
 * \brief          ESC[=#;7h or Put screen in indicated mode where # is
 * \brief          ESC[=h or 0 for 40 x 25 black & white
 * \brief          ESC[=0h or 1 for 40 x 25 color
 * \brief          ESC[?7h 2 for 80 x 25 b&w
 * \brief                                     3 for 80 x 25 color
 * \brief                                     4 for 320 x 200 color graphics
 * \brief                                     5 for 320 x 200 b & w graphics
 * \brief                                     6 for 640 x 200 b & w graphics
 * \brief                                     7 to wrap at end of line
 * \brief
 * \brief          ESC[=#;7l or ESC[=l or Resets mode # set with above command
 * \brief          ESC[=0l or ESC[?7l
 * \brief
 * \brief Keyboard Reassignments:
 * \brief
 * \brief          ESC[#;#;...p Keyboard reassignment. The first ASCII
 * \brief          or ESC["string"p code defines which code is to be
 * \brief          or ESC[#;"string";#; changed. The remaining codes define
 * \brief             #;"string";#p what it is to be changed to.
 * \brief
 * \brief    E.g. Reassign the Q and q keys to the A and a keys (and vice versa).
 * \brief
 * \brief          ESC [65;81p A becomes Q
 * \brief          ESC [97;113p a becomes q
 * \brief          ESC [81;65p Q becomes A
 * \brief          ESC [113;97p q becomes a
 * \brief
 * \brief          E.g. Reassign the F10 key to a DIR command.
 * \brief
 * \brief          ESC [0;68;"dir";13p The 0;68 is the extended ASCII code
 * \brief                                    for the F10 key and 13 is the ASCII
 * \brief                                    code for a carriage return.
 * \brief
 * \brief          Other function key codes F1=59,F2=60,F3=61,F4=62,F5=63
 * \brief                                         F6=64,F7=65,F8=66,F9=67,F10=68
 * \brief
**/

#ifndef _CURSOR_H_
#define _CURSOR_H_

//macros
#define CURSOR_MOVE_UP(n)                 printf("\033[%dA", n)
#define CURSOR_MOVE_DOWN(n)               printf("\033[%dB", n)
#define CURSOR_MOVE_FORWARD(n)            printf("\033[%dC", n)
#define CURSOR_SAVE()                     printf("\033[s" )
#define CURSOR_RESTORE()                  printf("\033[u" )
#define CURSOR_GETPOSITION(row, col)    { printf("\033[6n");  } //fscanf(stdin, "\033[%d;%dR\n", &row, &col);
#define CURSOR_CLEAR_LINE()               printf("\033[K")

#endif
